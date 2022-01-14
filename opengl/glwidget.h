#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <QTimer>
#include <QTime>
#include <QOpenGLTexture>
//#include <QOpenGLShaderProgram>
#define NOMINMAX
#include <memory>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif
#include "tracking/region/RegionModel.h"
#include "tracking/tracking_window.h"

class RenderingTableWidget;
class GluQua{
private:
    GLUquadricObj* ptr;
public:
    GluQua(void):ptr(gluNewQuadric())
    {
    }
    ~GluQua(void)
    {
        gluDeleteQuadric(ptr);
    }
    GLUquadricObj* get(void) {return ptr;}
};

class GLWidget :  public QOpenGLWidget, protected QOpenGLFunctions
{
Q_OBJECT

 public:
     GLWidget(tracking_window& cur_tracking_window_,
              RenderingTableWidget* renderWidget_,
              QWidget *parent = nullptr);
     ~GLWidget() override
     {
         clean_up();
     }

     void clean_up(void);
 public:// editing
     enum {none = 0,selecting = 1, moving = 2, dragging = 3} editing_option = none;
     tipl::vector<3,float> pos,dir1,dir2;
     std::vector<tipl::vector<3,float> > dirs;
     bool angular_selection;
     void get_pos(void);
     void set_view(unsigned char view_option);
     void scale_by(float scale);
     void move_by(int x,int y);
 private:

     tipl::vector<3,float> accumulated_dis;
     float slice_distance;
     unsigned char moving_at_slice_index;
     float slice_dx,slice_dy;
     void slice_location(unsigned char dim,std::vector<tipl::vector<3,float> >& points);
     float get_slice_projection_point(unsigned char dim,
                                      const tipl::vector<3,float>& pos,const tipl::vector<3,float>& dir,
                                      float& dx,float& dy);
     void get_view_dir(QPoint p,tipl::vector<3,float>& dir);

 private:
     bool region_selected,slice_selected,device_selected;
     float device_selected_length;
     size_t selected_index;
     float object_distance;
     bool select_object(void);
 public:// other slices
     std::chrono::high_resolution_clock::time_point time;
     int last_time;
     bool get_mouse_pos(QMouseEvent *mouseEvent,tipl::vector<3,float>& position);
     void paintGL() override;
     bool no_update = true;

 public://surface
     std::shared_ptr<RegionModel> surface;
     std::shared_ptr<QTimer> video_timer,rotate_timer;
 private:
     std::shared_ptr<tipl::io::avi> video_handle;
     bool video_capturing = false;
     size_t video_frames = 0;
 private://odf
     std::vector<tipl::vector<3,float> >odf_points;
     std::vector<tipl::vector<3,float> >odf_norm;
     std::vector<float> odf_color1,odf_color2,odf_color3;
     int odf_dim = 0;
     int odf_slide_pos = 0;
     void add_odf(const std::vector<tipl::pixel_index<3> >& odf_pos);
private: //glu
     std::shared_ptr<GluQua> RegionSpheres;
     std::shared_ptr<GluQua> DeviceQua;
public:
     tipl::image<2,float> connectivity;
     float max_connectivity = 0.0f;
     bool two_color_connectivity = false;
 private:
     void rotate_angle(float angle,float x,float y,float z);
     void copyToClipboardEach(QTableWidget* widget,unsigned int col_size);
 public slots:
     void makeTracts(void);
     void addSurface(void);
     void catchScreen(void);
     void catchScreen2(void);
     void saveCamera(void);
     void loadCamera(void);
     void saveRotationSeries(void);
     void save3ViewImage(void);
     void copyToClipboard(void);
     void copyToClipboardEachTract(void);
     void copyToClipboardEachRegion(void);
     void rotate(void);
     void record_video(void);
     void renderLR(void);
 signals:
     void edited();
     void region_edited();
 protected:
     void initializeGL() override;
     void resizeGL(int width, int height) override;
     void setFrustum(void);
 public:
     bool edit_right;
     QPoint convert_pos(QMouseEvent *event);
     void mousePressEvent(QMouseEvent *event) override;
     void mouseReleaseEvent(QMouseEvent *event) override;
     void mouseMoveEvent(QMouseEvent *event) override;
     void mouseDoubleClickEvent(QMouseEvent *event) override;
     void wheelEvent ( QWheelEvent * event ) override;
 private:
     tracking_window& cur_tracking_window;
     RenderingTableWidget* renderWidget;
     int cur_width = 1,cur_height = 1;
 private:
     int get_param(const char* name);
     template<typename value_type>
     int check_param(const char* name,value_type& value)
     {
         if(int(value) != get_param(name))
         {
            value = value_type(get_param(name));
            return 1;
         }
         return 0;
     }
     int check_param(const char* name,float& value)
     {
         if(value < get_param_float(name) || value > get_param_float(name))
         {
            value = get_param_float(name);
            return 1;
         }
         return 0;
     }
     float get_param_float(const char* name);
     bool check_change(const char* name,unsigned char& var);
     bool check_change(const char* name,float& var);
 private:
     std::vector<tipl::vector<2> > text_pos;
     std::vector<QColor> text_color;
     std::vector<QFont> text_font;
     std::vector<QString> text_str;
     void renderText(float x,float y, const QString &str, const QFont & font = QFont());
     void renderText(float x, float y, float z, const QString &str, const QFont & font = QFont());
 private:
     float tract_alpha;
     float tract_color_saturation;
     float tract_color_brightness;
     unsigned char scale_voxel;
     unsigned char slice_match_bkcolor = 0;
     unsigned char tract_alpha_style;
     unsigned char tract_style;
     unsigned char tract_color_style;
     float tube_diameter;
     unsigned char tract_color_contrast;
     unsigned char tract_tube_detail;
     unsigned char tract_variant_size;
     unsigned char tract_variant_color;
     unsigned char tract_shader;
     unsigned char end_point_shift;
     unsigned char odf_position;
     unsigned char odf_skip;
     unsigned char odf_shape = 0;
     unsigned char odf_color;
     float odf_scale;
public:
     bool keep_slice = false;
     std::vector<tipl::vector<3,float> > keep_slice_points;
public:
     GLuint tracts = 0;
     std::vector<std::shared_ptr<QOpenGLTexture> > slice_texture;

     int slice_pos[3] = {-1,-1,-1};
     QPoint lastPos,curPos,last_select_point;
     tipl::matrix<4,4> mat,transformation_matrix,transformation_matrix2,rotation_matrix,rotation_matrix2;
     enum class view_mode_type { single, two, stereo} view_mode = view_mode_type::single;

     bool set_view_flip = false;
     void get3View(QImage& I,unsigned int type);
     QImage grab_image(void){update();return grabFramebuffer();}
     void update_slice(void)
     {
         slice_pos[0] = slice_pos[1] = slice_pos[2] = -1;
         update();
     }
     bool command(QString cmd,QString param = "",QString param2 = "");
 };

#endif // GLWIDGET_H
