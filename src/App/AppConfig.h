#ifndef _APP_CONFIG_H_
#define _APP_CONFIG_H_

static const double App_width  = 1800.0; 
static const double App_height = 1000.0;

static const char* Debug_texture = "src/img/YellowReleased.png";

static const char *Frame_Texture = "src/img/frame.png";

static const char *Cross_Button_Release = "src/img/closeReleased.png";
static const char *Cross_Button_Covered = "src/img/closePressed.png";


static Vec2d Canvase_pos   = Vec2d(0.00, 0.05);
static Vec2d Canvase_size  = Vec2d(0.95, 0.95);

static Vec2d Canvase_Frame_pos   = Vec2d(0.1, 0.1);
static Vec2d Canvase_Frame_size  = Vec2d(0.6, 0.6);

static const char *Empty_texture = "src/img/empty.png";

static Vec2d Canvase_manager_pos  = Vec2d(0.0, 50);
static Vec2d Canvase_manager_size = Vec2d(1, 0.93);

static Vec2d Menu_size = Vec2d(1, 50);
static Vec2d Menu_pos  = Vec2d(0, 0);

static Vec2d Colors_palette_size = Vec2d(200, Menu_size.y - 20);
static Vec2d Colors_palette_pos  = Vec2d(160, 10);



static Vec2d Menu_Button_size = Vec2d(50, Menu_size.y);



static Vec2d Button_create_pos    = Vec2d(0.0, 0.0);
static Vec2d Button_create_size   = Menu_Button_size;

//Tools
static Vec2d Button_Tools_pos   = Vec2d(50.0, 0.0);
static Vec2d Button_Tools_size  = Menu_Button_size;

static Vec2d Button_Brush_pos   = Vec2d(Button_Tools_pos.x, Button_Tools_pos.y + Menu_Button_size.y);
static Vec2d Button_Brush_size  = Menu_Button_size;

static Vec2d Button_Line_pos   = Vec2d(Button_Tools_pos.x + Menu_Button_size.x, Button_Tools_pos.y + Menu_Button_size.y);
static Vec2d Button_Line_size  = Menu_Button_size;


static Vec2d Button_Square_pos   = Vec2d(Button_Tools_pos.x + 2 * Menu_Button_size.x, Button_Tools_pos.y + Menu_Button_size.y);
static Vec2d Button_Square_size  = Menu_Button_size;


static Vec2d Button_Circle_pos   = Vec2d(Button_Tools_pos.x + 2 * Menu_Button_size.x, Button_Tools_pos.y + 2 * Menu_Button_size.y);
static Vec2d Button_Circle_size  = Menu_Button_size;

static Vec2d Button_Polyline_pos   = Vec2d(Button_Tools_pos.x + Menu_Button_size.x, Button_Tools_pos.y + 2 * Menu_Button_size.y);
static Vec2d Button_Polyline_size  = Menu_Button_size;

static Vec2d Button_Pen_pos   = Vec2d(Button_Tools_pos.x, Button_Tools_pos.y + 2 * Menu_Button_size.y);
static Vec2d Button_Pen_size  = Menu_Button_size;

static Vec2d Button_Eraser_pos   = Vec2d(Button_Tools_pos.x, Button_Tools_pos.y + 3 * Menu_Button_size.y);
static Vec2d Button_Eraser_size  = Menu_Button_size;

static Vec2d Button_Text_pos   = Vec2d(Button_Tools_pos.x + Menu_Button_size.x, Button_Tools_pos.y + 3 * Menu_Button_size.y);
static Vec2d Button_Text_size  = Menu_Button_size;


//Filters

static Vec2d Button_Filter_pos   = Vec2d(100.0, 0.0);
static Vec2d Button_Filter_size  = Menu_Button_size;

static Vec2d Button_Inclight_pos   = Vec2d(Button_Filter_pos.x, Button_Filter_pos.y + Menu_Button_size.y);
static Vec2d Button_Inclight_size  = Menu_Button_size;

static Vec2d Button_Declight_pos   = Vec2d(Button_Filter_pos.x, Button_Filter_pos.y + 2 * Menu_Button_size.y);
static Vec2d Button_Declight_size  = Menu_Button_size;

static Vec2d Button_Blackwhite_pos   = Vec2d(Button_Filter_pos.x + Menu_Button_size.x, Button_Filter_pos.y + 1 * Menu_Button_size.y);
static Vec2d Button_Blackwhite_size  = Menu_Button_size;

static Vec2d Button_Invert_pos   = Vec2d(Button_Filter_pos.x + Menu_Button_size.x, Button_Filter_pos.y + 2 * Menu_Button_size.y);
static Vec2d Button_Invert_size  = Menu_Button_size;


static Vec2d Button_Redfilter_pos   = Vec2d(Button_Filter_pos.x + 2 * Menu_Button_size.x, Button_Filter_pos.y + 1 * Menu_Button_size.y);
static Vec2d Button_Redfilter_size  = Menu_Button_size;

static Vec2d Button_Greenfilter_pos   = Vec2d(Button_Filter_pos.x + 2 * Menu_Button_size.x, Button_Filter_pos.y + 2 * Menu_Button_size.y);
static Vec2d Button_Greenfilter_size  = Menu_Button_size;

static Vec2d Button_Bluefilter_pos   = Vec2d(Button_Filter_pos.x + 2 * Menu_Button_size.x, Button_Filter_pos.y + 3 * Menu_Button_size.y);
static Vec2d Button_Bluefilter_size  = Menu_Button_size;


#endif