#include <QString>
#include <QFileInfo>
#include <QDir>
#include <iostream>
#include <iterator>
#include <string>
#include "fib_data.hpp"
#include "tracking/region/Regions.h"
#include "TIPL/tipl.hpp"
#include "libs/dsi/image_model.hpp"
#include "libs/gzip_interface.hpp"
#include "reconstruction/reconstruction_window.h"
#include "program_option.hpp"
#include "reg.hpp"
#include <filesystem>

extern std::vector<std::string> fa_template_list,iso_template_list;
bool need_scheme_balance(const std::vector<unsigned int>& shell);
bool get_src(std::string filename,ImageModel& src2,std::string& error_msg);
/**
 perform reconstruction
 */
int rec(program_option& po)
{
    std::string file_name = po.get("source");
    ImageModel src;
    if (!src.load_from_file(file_name.c_str()))
    {
        show_progress() << "ERROR: " << src.error_msg << std::endl;
        return 1;
    }
    {
        progress prog("reconstruction parameters:");
        src.voxel.method_id = uint8_t(po.get("method",4));
        src.voxel.odf_resolving = po.get("odf_resolving",int(0));
        src.voxel.output_odf = po.get("record_odf",int(0));
        src.voxel.dti_no_high_b = po.get("dti_no_high_b",src.is_human_data());
        src.voxel.check_btable = po.get("check_btable",0);
        src.voxel.other_output = po.get("other_output","fa,ad,rd,md,nqa,iso,rdi,nrdi");
        src.voxel.r2_weighted = po.get("r2_weighted",int(0));
        src.voxel.thread_count = po.get("thread_count",uint32_t(std::thread::hardware_concurrency()));
        src.voxel.half_sphere = po.get("half_sphere",src.is_dsi_half_sphere());
        src.voxel.scheme_balance = po.get("scheme_balance",src.need_scheme_balance());
        src.voxel.qsdr_reso = po.get("qsdr_reso",src.voxel.vs[0]);
        src.voxel.param[0] = po.get("param0",src.voxel.param[0]);
        src.voxel.param[1] = po.get("param1",src.voxel.param[1]);
        src.voxel.param[2] = po.get("param2",src.voxel.param[2]);

        if(src.voxel.method_id == 7) // is qsdr
        {
            for(size_t id = 0;id < fa_template_list.size();++id)
                show_progress() << "template " << id << ":" << std::filesystem::path(fa_template_list[id]).stem() << std::endl;
            src.voxel.template_id = size_t(po.get("template",src.voxel.template_id));
        }
    }
    {
        progress prog("specify mask");
        std::string mask_file = po.get("mask","1");

        if(mask_file == "1")
            src.voxel.mask = 1;
        else
        {
            show_progress() << "reading mask file: " << mask_file << std::endl;
            gz_nifti nii;
            if(!nii.load_from_file(mask_file) || !nii.toLPS(src.voxel.mask))
            {
                show_progress() << "ERROR:" << nii.error_msg << std::endl;
                return 1;
            }
            if(src.voxel.mask.shape() != src.voxel.dim)
            {
                show_progress() << "ERROR: The mask dimension is different. terminating..." << std::endl;
                return 1;
            }
        }
    }
    {
        progress prog("preprocessing");
        if(po.get("preprocessing",0))
            src.preprocessing();
        else
        {
            if(po.has("rev_pe") && !src.run_topup_eddy(po.get("rev_pe")))
            {
                show_progress() << "ERROR:" << src.error_msg << std::endl;
                return 1;
            }
            if(po.get("motion_correction",0))
                src.correct_motion();
        }
    }

    if(po.has("other_image"))
    {
        QStringList file_list = QString(po.get("other_image").c_str()).split(",");
        for(int i = 0;i < file_list.size();++i)
        {
            QStringList name_value = file_list[i].split(":");
            if(name_value.size() == 1)
            {
                show_progress() << "invalid parameter: " << file_list[i].toStdString() << std::endl;
                return 1;
            }
            if(name_value.size() == 3) // handle windows directory with drive letter
            {
                name_value[1] += ":";
                name_value[1] += name_value[2];
            }
            show_progress() << name_value[0].toStdString() << ":" << name_value[1].toStdString() << std::endl;
            if(!add_other_image(&src,name_value[0],name_value[1]))
                return 1;
        }
    }

    {
        progress prog("additional processing steps");
        if (po.has("cmd"))
        {
            QStringList cmd_list = QString(po.get("cmd").c_str()).split("+");
            for(int i = 0;i < cmd_list.size();++i)
            {
                QStringList run_list = QString(cmd_list[i]).split("=");
                if(!src.command(run_list[0].toStdString(),
                                    run_list.count() > 1 ? run_list[1].toStdString():std::string()))
                {
                    show_progress() << "ERROR:" << src.error_msg << std::endl;
                    return 1;
                }
            }
        }

        if(src.voxel.method_id != 7)
        {
            if(po.has("rotate_to") || po.has("align_to"))
            {
                std::string file_name = po.has("rotate_to") ? po.get("rotate_to"):po.get("align_to");
                gz_nifti in;
                if(!in.load_from_file(file_name.c_str()))
                {
                    show_progress() << "failed to read " << file_name << std::endl;
                    return 1;
                }
                tipl::image<3,unsigned char> I;
                tipl::vector<3> vs;
                in.get_voxel_size(vs);
                in >> I;
                if(po.has("rotate_to"))
                    show_progress() << "running rigid body transformation" << std::endl;
                else
                    show_progress() << "running affine transformation" << std::endl;

                tipl::transformation_matrix<float> T;
                bool terminated = false;

                tipl::filter::gaussian(I);
                tipl::filter::gaussian(src.dwi);

                linear_with_mi(I,vs,src.dwi,src.voxel.vs,T,po.has("rotate_to") ? tipl::reg::rigid_body : tipl::reg::affine,terminated);

                show_progress() << "DWI rotated." << std::endl;
                src.rotate(I.shape(),vs,T);
            }
            else
            if(po.get("align_acpc",src.is_human_data() && src.voxel.vs[0] == src.voxel.vs[2]))
                src.align_acpc();
        }
    }


    if(po.has("save_src") || po.has("save_nii"))
    {
        std::string new_src_file = po.has("save_src") ? po.get("save_src") : po.get("save_nii");
        if(!src.save_to_file(new_src_file.c_str()))
        {
            show_progress() << "ERROR:" << src.error_msg << std::endl;
            return -1;
        }
        return 0;
    }

    if(po.has("output"))
    {
        std::string output = po.get("output");
        if(QFileInfo(output.c_str()).isDir())
            src.file_name = output + "/" + std::filesystem::path(src.file_name).filename().string();
        else
            src.file_name = output;
    }
    if (!src.reconstruction())
    {
        show_progress() << "ERROR:" << src.error_msg << std::endl;
        return 1;
    }
    return 0;
}
