#ifndef SliceModelH
#define SliceModelH
#include <future>
#include "zlib.h"
#include "TIPL/tipl.hpp"

// ---------------------------------------------------------------------------
class fib_data;
class SliceModel {
public:
    fib_data* handle = nullptr;
    uint32_t view_id = 0;
    bool is_diffusion_space = true;
    tipl::matrix<4,4> T,invT; // T: image->diffusion iT: diffusion->image
    tipl::shape<3> dim;
    tipl::vector<3> vs;
public:
    bool is_overlay = false;
public:
    // for directx
    tipl::vector<3,int> slice_pos;
    bool slice_visible[3];
public:
    SliceModel(fib_data* new_handle,uint32_t view_id_);
    virtual ~SliceModel(void){}
public:
    std::pair<float,float> get_value_range(void) const;
    std::pair<float,float> get_contrast_range(void) const;
    std::pair<unsigned int,unsigned int> get_contrast_color(void) const;
    void set_contrast_range(float min_v,float max_v);
    void set_contrast_color(unsigned int min_c,unsigned int max_c);
    virtual void get_slice(tipl::color_image& image,
                           unsigned char,
                           const std::vector<std::shared_ptr<SliceModel> >& overlay_slices) const;
    void get_high_reso_slice(tipl::color_image& image,unsigned char) const;
    tipl::const_pointer_image<3> get_source(void) const;
    std::string get_name(void) const;
public:
    auto toDiffusionSpace(unsigned char cur_dim,int x,int y) const
    {
        auto v = tipl::slice2space<tipl::vector<3> >(cur_dim, x, y, slice_pos[cur_dim]);
        if(!is_diffusion_space)
        {
            v.to(T);
            v.round();           
        }
        return v;
    }
    auto toOtherSlice(std::shared_ptr<SliceModel> other_slice,
                      unsigned char cur_dim,int x,int y) const
    {
        auto v = tipl::slice2space<tipl::vector<3> >(cur_dim, x, y, slice_pos[cur_dim]);
        if(!is_diffusion_space)
            v.to(T);
        if(!other_slice->is_diffusion_space)
            v.to(other_slice->invT);
        return v;
    }
    template<typename U,typename V>
    auto to3DSpace(unsigned char cur_dim,V x, V y) const
    {
        return tipl::slice2space<U>(cur_dim, x, y, slice_pos[cur_dim]);
    }
public:

    void get_other_slice_pos(unsigned char cur_dim,int& x, int& y) const {
            x = slice_pos[(cur_dim + 1) % 3];
            y = slice_pos[(cur_dim + 2) % 3];
            if (cur_dim == 1)
                    std::swap(x, y);
    }
    bool set_slice_pos(int x,int y,int z)
    {
        if(!dim.is_valid(x,y,z))
            return false;
        bool has_updated = false;
        if(slice_pos[0] != x)
        {
            slice_pos[0] = x;
            has_updated = true;
        }
        if(slice_pos[1] != y)
        {
            slice_pos[1] = y;
            has_updated = true;
        }
        if(slice_pos[2] != z)
        {
            slice_pos[2] = z;
            has_updated = true;
        }
        return has_updated;
    }
    void get_slice_positions(unsigned int cur_dim,std::vector<tipl::vector<3,float> >& points)
    {
        points.resize(4);
        tipl::get_slice_positions(cur_dim, slice_pos[cur_dim],dim,points);
        if(!is_diffusion_space)
            for(auto p : points)
                p.to(T);
    }
    void apply_overlay(tipl::color_image& show_image,
                       unsigned char dim,
                       std::shared_ptr<SliceModel> other_slice) const;
};

class CustomSliceModel : public SliceModel {
public:
    std::string source_file_name,name,error_msg = "unknown error";
public:
    std::shared_ptr<std::thread> thread;
    tipl::affine_transform<float> arg_min;
    bool terminated = true;
    bool running = false;
    void terminate(void);
    void wait(void);
    void argmin(tipl::reg::reg_type reg_type);
    void update_transform(void);
public:
    CustomSliceModel(fib_data* new_handle);
    ~CustomSliceModel(void)
    {
        terminate();
    }


    bool save_mapping(const char* file_name);
    bool load_mapping(const char* file_name);
public:
    tipl::matrix<4,4> trans;
    bool is_mni = false;
    tipl::image<3> source_images;
    tipl::image<3> skull_removed_images;
    tipl::color_image picture;
    void update_image(void);
    virtual void get_slice(tipl::color_image& image,
                           unsigned char,
                           const std::vector<std::shared_ptr<SliceModel> >& overlay_slices) const;
public:
    bool load_slices(const std::vector<std::string>& files,bool is_mni = false);
    bool load_slices(const std::string& file,bool is_mni = false)
    {
        std::vector<std::string> files;
        files.push_back(file);
        return load_slices(files,is_mni);
    }
};

#endif
