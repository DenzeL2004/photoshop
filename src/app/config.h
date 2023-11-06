#ifndef _CONFIG_H_
#define _CONFIG_H_

static const char* Debug_texture = "src/img/YellowReleased.png";

static const char *Frame_Texture = "src/img/frame.png";

static const char *Cross_Button_Release = "src/img/closeReleased.png";
static const char *Cross_Button_Covered = "src/img/closePressed.png";


static Dot Canvase_Offset = Dot(0.00, 0.05);
static Dot Canvase_Scale  = Dot(0.95, 0.95);

static Dot Canvase_Frame_Offset = Dot(0.1, 0.1);
static Dot Canvase_Frame_Scale  = Dot(0.6, 0.6);

static const char *Empty_texture = "src/img/empty.png";

static Dot Canvase_manager_pos  = Dot(0.0, 50);
static Dot Canvase_manager_size = Dot(1, 0.93);



static Dot Menu_Button_Scale = Dot(50, 50);

static Dot Button_create_pos    = Dot(0.0, 0.0);
static Dot Button_create_size   = Menu_Button_Scale;

//Tools
static Dot Button_Tools_Offset = Dot(50.0, 0.0);
static Dot Button_Tools_Scale  = Menu_Button_Scale;

static Dot Button_Brush_Offset = Dot(Button_Tools_Offset.x, Button_Tools_Offset.y + Menu_Button_Scale.y);
static Dot Button_Brush_Scale  = Menu_Button_Scale;

static Dot Button_Line_Offset = Dot(Button_Tools_Offset.x + Menu_Button_Scale.x, Button_Tools_Offset.y + Menu_Button_Scale.y);
static Dot Button_Line_Scale  = Menu_Button_Scale;


static Dot Button_Square_Offset = Dot(Button_Tools_Offset.x + 2 * Menu_Button_Scale.x, Button_Tools_Offset.y + Menu_Button_Scale.y);
static Dot Button_Square_Scale  = Menu_Button_Scale;


static Dot Button_Circle_Offset = Dot(Button_Tools_Offset.x, Button_Tools_Offset.y + 2 * Menu_Button_Scale.y);
static Dot Button_Circle_Scale  = Menu_Button_Scale;

static Dot Button_Polyline_Offset = Dot(Button_Tools_Offset.x + Menu_Button_Scale.x, Button_Tools_Offset.y + 2 * Menu_Button_Scale.y);
static Dot Button_Polyline_Scale  = Menu_Button_Scale;

static Dot Button_Eraser_Offset = Dot(Button_Tools_Offset.x + 2 * Menu_Button_Scale.x, Button_Tools_Offset.y + 2 * Menu_Button_Scale.y);
static Dot Button_Eraser_Scale  = Menu_Button_Scale;


//Colors
static Dot    Button_Colors_Offset = Dot(0.08, 0.0);
static Dot Button_Colors_Scale  = Menu_Button_Scale;

static Dot    Button_Red_Offset = Dot(0.08, 0.05);
static Dot Button_Red_Scale  = Menu_Button_Scale;

static Dot    Button_Blue_Offset = Dot(0.12, 0.05);
static Dot Button_Blue_Scale  = Menu_Button_Scale;

static Dot    Button_Green_Offset = Dot(0.16, 0.05);
static Dot Button_Green_Scale  = Menu_Button_Scale;

static Dot    Button_Yellow_Offset = Dot(0.08, 0.1);
static Dot Button_Yellow_Scale  = Menu_Button_Scale;

//Filters

static Dot Button_Filter_Offset = Dot(100.0, 0.0);
static Dot Button_Filter_Scale  = Menu_Button_Scale;

static Dot Button_Inclight_Offset = Dot(Button_Filter_Offset.x, Button_Filter_Offset.y + Menu_Button_Scale.y);
static Dot Button_Inclight_Scale  = Menu_Button_Scale;

static Dot Button_Declight_Offset = Dot(Button_Filter_Offset.x, Button_Filter_Offset.y + 2 * Menu_Button_Scale.y);
static Dot Button_Declight_Scale  = Menu_Button_Scale;



#endif