#ifndef _CONFIG_H_
#define _CONFIG_H_

static const char* Debug_texture = "src/img/YellowReleased.png";

static const char *Frame_Texture = "src/img/frame.png";

static const char *Cross_Button_Release = "src/img/closeReleased.png";
static const char *Cross_Button_Covered = "src/img/closePressed.png";


static Dot Canvase_pos   = Dot(0.00, 0.05);
static Dot Canvase_size  = Dot(0.95, 0.95);

static Dot Canvase_Frame_pos   = Dot(0.1, 0.1);
static Dot Canvase_Frame_size  = Dot(0.6, 0.6);

static const char *Empty_texture = "src/img/empty.png";

static Dot Canvase_manager_pos  = Dot(0.0, 50);
static Dot Canvase_manager_size = Dot(1, 0.93);



static Dot Menu_Button_size = Dot(50, 50);

static Dot Button_create_pos    = Dot(0.0, 0.0);
static Dot Button_create_size   = Menu_Button_size;

//Tools
static Dot Button_Tools_pos   = Dot(50.0, 0.0);
static Dot Button_Tools_size  = Menu_Button_size;

static Dot Button_Brush_pos   = Dot(Button_Tools_pos  .x, Button_Tools_pos  .y + Menu_Button_size.y);
static Dot Button_Brush_size  = Menu_Button_size;

static Dot Button_Line_pos   = Dot(Button_Tools_pos  .x + Menu_Button_size.x, Button_Tools_pos  .y + Menu_Button_size.y);
static Dot Button_Line_size  = Menu_Button_size;


static Dot Button_Square_pos   = Dot(Button_Tools_pos  .x + 2 * Menu_Button_size.x, Button_Tools_pos  .y + Menu_Button_size.y);
static Dot Button_Square_size  = Menu_Button_size;


static Dot Button_Circle_pos   = Dot(Button_Tools_pos  .x + 2 * Menu_Button_size.x, Button_Tools_pos  .y + 2 * Menu_Button_size.y);
static Dot Button_Circle_size  = Menu_Button_size;

static Dot Button_Polyline_pos   = Dot(Button_Tools_pos  .x + Menu_Button_size.x, Button_Tools_pos  .y + 2 * Menu_Button_size.y);
static Dot Button_Polyline_size  = Menu_Button_size;

static Dot Button_Pen_pos   = Dot(Button_Tools_pos  .x, Button_Tools_pos  .y + 2 * Menu_Button_size.y);
static Dot Button_Pen_size  = Menu_Button_size;

static Dot Button_Eraser_pos   = Dot(Button_Tools_pos  .x, Button_Tools_pos  .y + 3 * Menu_Button_size.y);
static Dot Button_Eraser_size  = Menu_Button_size;


//Colors
static Dot    Button_Colors_pos   = Dot(0.08, 0.0);
static Dot Button_Colors_size  = Menu_Button_size;

static Dot    Button_Red_pos   = Dot(0.08, 0.05);
static Dot Button_Red_size  = Menu_Button_size;

static Dot    Button_Blue_pos   = Dot(0.12, 0.05);
static Dot Button_Blue_size  = Menu_Button_size;

static Dot    Button_Green_pos   = Dot(0.16, 0.05);
static Dot Button_Green_size  = Menu_Button_size;

static Dot    Button_Yellow_pos   = Dot(0.08, 0.1);
static Dot Button_Yellow_size  = Menu_Button_size;

//Filters

static Dot Button_Filter_pos   = Dot(100.0, 0.0);
static Dot Button_Filter_size  = Menu_Button_size;

static Dot Button_Inclight_pos   = Dot(Button_Filter_pos  .x, Button_Filter_pos  .y + Menu_Button_size.y);
static Dot Button_Inclight_size  = Menu_Button_size;

static Dot Button_Declight_pos   = Dot(Button_Filter_pos  .x, Button_Filter_pos  .y + 2 * Menu_Button_size.y);
static Dot Button_Declight_size  = Menu_Button_size;



#endif