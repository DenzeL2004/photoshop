#ifndef _CONFIG_H_
#define _CONFIG_H_

static const char *Frame_Texture = "src/img/border.png";

static const char *Cross_Button_Release = "src/img/CloseResCrossReleased.png";
static const char *Cross_Button_Covered = "src/img/CloseResCrossCovered.png";

static Dot    Cross_Button_Offset   = Dot(0.98, 0.0);
static Vector Cross_Button_Scale    = Vector(0.02, 0.025);

static double Width_Canvase  = 2000.0;
static double Hieght_Canvase = 2000.0;

static Dot    Canvase_Offset = Dot(0.00, 0.05);
static Vector Canvase_Scale  = Vector(0.95, 1.0);

static Dot    Canvase_Frame_Offset = Dot(0.1, 0.1);
static Vector Canvase_Frame_Scale  = Vector(0.6, 0.6);

static const char *Empty_texture = "src/img/empty.png";

static Dot    Canvase_Manager_Offset = Dot(0.0, 0.1);
static Vector Canvase_Manager_Scale  = Vector(1, 0.9);

static Dot    Button_Create_Offset = Dot(0.0, 0.0);
static Vector Button_Create_Scale  = Vector(0.1, 0.1);


//Tools
static Dot    Button_Tools_Offset = Dot(0.1, 0.0);
static Vector Button_Tools_Scale  = Vector(0.1, 0.1);

static Dot    Button_Line_Offset = Dot(0.1, 0.1);
static Vector Button_Line_Scale  = Vector(0.1, 0.1);

static Dot    Button_Brush_Offset = Dot(0.1, 0.2);
static Vector Button_Brush_Scale  = Vector(0.1, 0.1);

static Dot    Button_Square_Offset = Dot(0.1, 0.3);
static Vector Button_Square_Scale  = Vector(0.1, 0.1);

static Dot    Button_Circle_Offset = Dot(0.1, 0.4);
static Vector Button_Circle_Scale  = Vector(0.1, 0.1);

static Dot    Button_Polyline_Offset = Dot(0.1, 0.5);
static Vector Button_Polyline_Scale  = Vector(0.1, 0.1);


static Dot    Button_Eraser_Offset = Dot(0.1, 0.6);
static Vector Button_Eraser_Scale  = Vector(0.1, 0.1);


//Colors
static Dot    Button_Colors_Offset = Dot(0.2, 0.0);
static Vector Button_Colors_Scale  = Vector(0.1, 0.1);

static Dot    Button_Red_Offset = Dot(0.2, 0.1);
static Vector Button_Red_Scale  = Vector(0.1, 0.1);

static Dot    Button_Blue_Offset = Dot(0.2, 0.2);
static Vector Button_Blue_Scale  = Vector(0.1, 0.1);

static Dot    Button_Green_Offset = Dot(0.2, 0.3);
static Vector Button_Green_Scale  = Vector(0.1, 0.1);


#endif