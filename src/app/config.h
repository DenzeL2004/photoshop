#ifndef _CONFIG_H_
#define _CONFIG_H_

static const char* Debug_texture = "src/img/YellowReleased.png";

static const char *Frame_Texture = "src/img/border.png";

static const char *Cross_Button_Release = "src/img/closeReleased.png";
static const char *Cross_Button_Covered = "src/img/closePressed.png";

static Dot    Cross_Button_Offset   = Dot(0.965, 0.005);
static Vector Cross_Button_Scale    = Vector(0.035, 0.05);

static double Width_Canvase  = 2000.0;
static double Hieght_Canvase = 2000.0;

static Dot    Canvase_Offset = Dot(0.00, 0.05);
static Vector Canvase_Scale  = Vector(0.95, 0.95);

static Dot    Canvase_Frame_Offset = Dot(0.1, 0.1);
static Vector Canvase_Frame_Scale  = Vector(0.6, 0.6);

static const char *Empty_texture = "src/img/empty.png";

static Dot    Canvase_Manager_Offset = Dot(0.0, 0.1);
static Vector Canvase_Manager_Scale  = Vector(1, 0.9);

static Dot    Button_Create_Offset = Dot(0.0, 0.0);
static Vector Button_Create_Scale  = Vector(0.04, 0.05);

static Vector Menu_Button_Scale = Vector(0.04, 0.05);

//Tools
static Dot    Button_Tools_Offset = Dot(0.04, 0.0);
static Vector Button_Tools_Scale  = Menu_Button_Scale;

static Dot    Button_Brush_Offset = Dot(0.04, 0.05);
static Vector Button_Brush_Scale  = Menu_Button_Scale;

static Dot    Button_Circle_Offset = Dot(0.08, 0.05);
static Vector Button_Circle_Scale  = Menu_Button_Scale;

static Dot    Button_Square_Offset = Dot(0.12, 0.05);
static Vector Button_Square_Scale  = Menu_Button_Scale;


static Dot    Button_Line_Offset = Dot(0.04, 0.1);
static Vector Button_Line_Scale  = Menu_Button_Scale;

static Dot    Button_Polyline_Offset = Dot(0.08, 0.1);
static Vector Button_Polyline_Scale  = Menu_Button_Scale;

static Dot    Button_Eraser_Offset = Dot(0.12, 0.1);
static Vector Button_Eraser_Scale  = Menu_Button_Scale;


//Colors
static Dot    Button_Colors_Offset = Dot(0.08, 0.0);
static Vector Button_Colors_Scale  = Menu_Button_Scale;

static Dot    Button_Red_Offset = Dot(0.08, 0.05);
static Vector Button_Red_Scale  = Menu_Button_Scale;

static Dot    Button_Blue_Offset = Dot(0.12, 0.05);
static Vector Button_Blue_Scale  = Menu_Button_Scale;

static Dot    Button_Green_Offset = Dot(0.16, 0.05);
static Vector Button_Green_Scale  = Menu_Button_Scale;

static Dot    Button_Yellow_Offset = Dot(0.08, 0.1);
static Vector Button_Yellow_Scale  = Menu_Button_Scale;

//Filters

static Dot    Button_Filter_Offset = Dot(0.12, 0.0);
static Vector Button_Filter_Scale  = Menu_Button_Scale;

static Dot    Button_Inclight_Offset = Dot(0.12, 0.05);
static Vector Button_Inclight_Scale  = Menu_Button_Scale;

static Dot    Button_Declight_Offset = Dot(0.12, 0.1);
static Vector Button_Declight_Scale  = Menu_Button_Scale;



#endif