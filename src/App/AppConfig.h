#ifndef _APP_CONFIG_H_
#define _APP_CONFIG_H_

static const double App_width  = 1840.0; 
static const double App_height = 1035.0;

static const char* Debug_texture = "src/img/YellowReleased.png";

static const char *Canvas_frame_texture = "src/img/frame2.png";
static const plug::Vec2d Canvas_frame_title_pos = plug::Vec2d(5, 20);
static const plug::Vec2d Canvas_frame_size = plug::Vec2d(510, 480);
static const plug::Vec2d Canvas_frame_pos  = plug::Vec2d(5, 5);

static const char *Cross_button_released = "src/img/closeReleased.png";
static const char *Cross_button_pressed  = "src/img/closePressed.png";
static const plug::Vec2d Cross_button_size = plug::Vec2d(25.0, 25.0);

static const size_t Default_canvas_width  = 800u;
static const size_t Default_canvas_height = 600u;

static const plug::Vec2d Canvas_view_pos  = plug::Vec2d(5, 80); 
static const plug::Vec2d Canvas_view_size = plug::Vec2d(470, 395);

static const char *Scrollbar_up_released = "src/img/arrowUpReleased.png";
static const char *Scrollbar_up_pressed  = "src/img/arrowUpPressed.png";

static const char *Scrollbar_down_released = "src/img/arrowDownReleased.png";
static const char *Scrollbar_down_pressed  = "src/img/arrowDownPressed.png";

static const char *Scrollbar_left_released = "src/img/arrowLeftReleased.png";
static const char *Scrollbar_left_pressed  = "src/img/arrowLeftPressed.png";

static const char *Scrollbar_right_released = "src/img/arrowRightReleased.png";
static const char *Scrollbar_right_pressed  = "src/img/arrowRightPressed.png";

static const char *Scrollbar_released = "src/img/scroll.png";
static const char *Scrollbar_pressed  = "src/img/scroll2.png";


static const char *Empty_texture = "src/img/empty.png";

static plug::Vec2d Canvase_manager_pos  = plug::Vec2d(0.0, 50);
static plug::Vec2d Canvase_manager_size = plug::Vec2d(1, 0.93);

static plug::Vec2d Menu_size = plug::Vec2d(1, 50);
static plug::Vec2d Menu_pos  = plug::Vec2d(0, 0);

static plug::Vec2d Colors_palette_size = plug::Vec2d(200, Menu_size.y - 20);
static plug::Vec2d Colors_palette_pos  = plug::Vec2d(160, 10);



static plug::Vec2d Menu_Button_size = plug::Vec2d(50, Menu_size.y);



static plug::Vec2d Button_create_pos    = plug::Vec2d(0.0, 0.0);
static plug::Vec2d Button_create_size   = Menu_Button_size;

//Tools
static plug::Vec2d Button_Tools_pos   = plug::Vec2d(50.0, 0.0);
static plug::Vec2d Button_Tools_size  = Menu_Button_size;

static plug::Vec2d Button_Brush_pos   = plug::Vec2d(Button_Tools_pos.x, Button_Tools_pos.y + Menu_Button_size.y);
static plug::Vec2d Button_Brush_size  = Menu_Button_size;

static plug::Vec2d Button_Line_pos   = plug::Vec2d(Button_Tools_pos.x + Menu_Button_size.x, Button_Tools_pos.y + Menu_Button_size.y);
static plug::Vec2d Button_Line_size  = Menu_Button_size;


static plug::Vec2d Button_Square_pos   = plug::Vec2d(Button_Tools_pos.x + 2 * Menu_Button_size.x, Button_Tools_pos.y + Menu_Button_size.y);
static plug::Vec2d Button_Square_size  = Menu_Button_size;


static plug::Vec2d Button_Circle_pos   = plug::Vec2d(Button_Tools_pos.x + 2 * Menu_Button_size.x, Button_Tools_pos.y + 2 * Menu_Button_size.y);
static plug::Vec2d Button_Circle_size  = Menu_Button_size;

static plug::Vec2d Button_Polyline_pos   = plug::Vec2d(Button_Tools_pos.x + Menu_Button_size.x, Button_Tools_pos.y + 2 * Menu_Button_size.y);
static plug::Vec2d Button_Polyline_size  = Menu_Button_size;

static plug::Vec2d Button_Pen_pos   = plug::Vec2d(Button_Tools_pos.x, Button_Tools_pos.y + 2 * Menu_Button_size.y);
static plug::Vec2d Button_Pen_size  = Menu_Button_size;

static plug::Vec2d Button_Eraser_pos   = plug::Vec2d(Button_Tools_pos.x, Button_Tools_pos.y + 3 * Menu_Button_size.y);
static plug::Vec2d Button_Eraser_size  = Menu_Button_size;

static plug::Vec2d Button_Text_pos   = plug::Vec2d(Button_Tools_pos.x + Menu_Button_size.x, Button_Tools_pos.y + 3 * Menu_Button_size.y);
static plug::Vec2d Button_Text_size  = Menu_Button_size;


//Filters

static plug::Vec2d Button_Filter_pos   = plug::Vec2d(100.0, 0.0);
static plug::Vec2d Button_Filter_size  = Menu_Button_size;

static plug::Vec2d Button_Inclight_pos   = plug::Vec2d(Button_Filter_pos.x, Button_Filter_pos.y + Menu_Button_size.y);
static plug::Vec2d Button_Inclight_size  = Menu_Button_size;

static plug::Vec2d Button_Declight_pos   = plug::Vec2d(Button_Filter_pos.x, Button_Filter_pos.y + 2 * Menu_Button_size.y);
static plug::Vec2d Button_Declight_size  = Menu_Button_size;

static plug::Vec2d Button_Blackwhite_pos   = plug::Vec2d(Button_Filter_pos.x + Menu_Button_size.x, Button_Filter_pos.y + 1 * Menu_Button_size.y);
static plug::Vec2d Button_Blackwhite_size  = Menu_Button_size;

static plug::Vec2d Button_Invert_pos   = plug::Vec2d(Button_Filter_pos.x + Menu_Button_size.x, Button_Filter_pos.y + 2 * Menu_Button_size.y);
static plug::Vec2d Button_Invert_size  = Menu_Button_size;


static plug::Vec2d Button_Redfilter_pos   = plug::Vec2d(Button_Filter_pos.x + 2 * Menu_Button_size.x, Button_Filter_pos.y + 1 * Menu_Button_size.y);
static plug::Vec2d Button_Redfilter_size  = Menu_Button_size;

static plug::Vec2d Button_Greenfilter_pos   = plug::Vec2d(Button_Filter_pos.x + 2 * Menu_Button_size.x, Button_Filter_pos.y + 2 * Menu_Button_size.y);
static plug::Vec2d Button_Greenfilter_size  = Menu_Button_size;

static plug::Vec2d Button_Bluefilter_pos   = plug::Vec2d(Button_Filter_pos.x + 2 * Menu_Button_size.x, Button_Filter_pos.y + 3 * Menu_Button_size.y);
static plug::Vec2d Button_Bluefilter_size  = Menu_Button_size;


#endif