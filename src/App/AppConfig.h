#ifndef _APP_CONFIG_H_
#define _APP_CONFIG_H_

static const double Window_width  = 1840.0; 
static const double Window_height = 1010.0;

static const char* Debug_texture = "src/img/YellowReleased.png";

static const char* App_frame_texture = "src/img/AppFrame.png";

//======================================================================

static const char *Canvas_frame_texture = "src/img/CanvasFrame.png";
static const plug::Vec2d Canvas_frame_title_pos = plug::Vec2d(5, 20);
static const plug::Vec2d Canvas_frame_size = plug::Vec2d(510, 480);
static const plug::Vec2d Canvas_frame_pos  = plug::Vec2d(5, 5);

static const plug::Color Canvas_frame_title_color = plug::White;

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

//==================================================================

static const char *Dialog_window_texture = "src/img/DialogFrame.png";
static const plug::Vec2d Dialog_window_size = plug::Vec2d(480, 180);

static const char *Close_canvas_title = "Do you want to save it?";
static const double Dialog_title_scale = 1.9;
static const plug::Vec2d Close_canvas_title_pos = plug::Vec2d(  Dialog_window_size.x / 2 - strlen(Close_canvas_title) / 2 * Dialog_title_scale * 7, 
                                                                Dialog_window_size.y / 3);

static const plug::Color Canvas_dialog_title_color = plug::White;

static const plug::Vec2d Dialog_button_size = plug::Vec2d(80, 25);

static const char *Dialog_button_cancel_released = "src/img/DialogButtonCancelReleased.png";
static const char *Dialog_button_cancel_pressed  = "src/img/DialogButtonCancelPressed.png";
static const plug::Vec2d Dialog_button_cancel_pos = plug::Vec2d(Dialog_window_size.x * 0.2 - Dialog_button_size.x / 2, Dialog_window_size.y * 0.6);

static const char *Dialog_button_confirm_released = "src/img/DialogButtonConfirmReleased.png";
static const char *Dialog_button_confirm_pressed  = "src/img/DialogButtonConfirmPressed.png";
static const plug::Vec2d Dialog_button_confirm_pos = plug::Vec2d(Dialog_window_size.x * 0.2 - Dialog_button_size.x / 2, Dialog_window_size.y * 0.6);

static const char *Dialog_button_no_released = "src/img/DialogButtonNoReleased.png";
static const char *Dialog_button_no_pressed  = "src/img/DialogButtonNoPressed.png";
static const plug::Vec2d Dialog_button_no_pos = plug::Vec2d(Dialog_window_size.x * 0.5 - Dialog_button_size.x / 2, Dialog_window_size.y * 0.6);

static const char *Dialog_button_yes_released = "src/img/DialogButtonYesReleased.png";
static const char *Dialog_button_yes_pressed  = "src/img/DialogButtonYesPressed.png";
static const plug::Vec2d Dialog_button_yes_pos = plug::Vec2d(Dialog_window_size.x * 0.8 - Dialog_button_size.x / 2, Dialog_window_size.y * 0.6);

//================================================================

static const char *Entry_window_texture = "src/img/DialogFrame.png";
static const plug::Vec2d Entry_window_pos  = plug::Vec2d(-10, -10);
static const plug::Vec2d Entry_window_size = plug::Vec2d(600, 210);

static const char *File_path_name = "File path ";
static const double Entry_title_scale = 1.9;
static const plug::Vec2d Filt_path_title_pos = plug::Vec2d(50, 45);
static const size_t Entry_field_symbol_limit = 30;
static const plug::Color Entry_field_color = plug::Color(255, 255, 255);


static const char *Entry_field_texture = "src/img/EntryWindow.png";
static const plug::Vec2d Entry_field_pos  = plug::Vec2d(20, 50);
static const plug::Vec2d Entry_field_size = plug::Vec2d(Entry_window_size.x * 0.9, Entry_title_scale * 30);

static const plug::Vec2d Entry_button_cancel_pos = plug::Vec2d(Entry_window_size.x * 0.65 - Dialog_button_size.x / 2, Entry_window_size.y * 0.55);
static const plug::Vec2d Entry_button_confirm_pos = plug::Vec2d(Entry_window_size.x * 0.8 - Dialog_button_size.x / 2, Entry_window_size.y * 0.55);

//================================================================

static const plug::KeyCode Last_filter_use = plug::KeyCode::L;

//================================================================

static const char* Background_window_texture    = "src/img/Background.png";
static const plug::Vec2d Background_window_pos  = plug::Vec2d(2, 20); 
static const plug::Vec2d Background_window_size = plug::Vec2d(Window_width - 9, Window_height - 45);

static const char* Config_bar_texture    = "src/img/ConfigBarTexture.png";
static const plug::Vec2d Config_bar_pos  = Background_window_pos; 
static const plug::Vec2d Config_bar_size = plug::Vec2d(Background_window_size.x, 20);

static const plug::Vec2d Menu_button_size = plug::Vec2d(Config_bar_size.y * 1.33, Config_bar_size.y);

static const char *Menu_file_released = "src/img/ButtonFileReleased.png";
static const char *Menu_file_pressed  = "src/img/ButtonFilePressed.png";
static const plug::Vec2d File_button_size = Menu_button_size;
static const plug::Vec2d File_button_pos  = Background_window_pos;

static const plug::Vec2d Menu_list_size = plug::Vec2d(200, 30);


static const char *Menu_button_released = "src/img/MenuButtonsBackgroundReleased.png";
static const char *Menu_button_pressed  = "src/img/MenuButtonsBackgroundPressed.png";

static const double Menu_button_scale = 1.5;
static const plug::Color Menu_button_color = plug::Color(255, 255, 255);
static const plug::Vec2d Menu_title_pos = plug::Vec2d(3,  File_button_size.y / 2);

static const char *Menu_file_open_released = Menu_button_released;
static const char *Menu_file_open_pressed  = Menu_button_pressed;
static const plug::Vec2d File_button_open_size = Menu_list_size;
static const plug::Vec2d File_button_open_pos  = plug::Vec2d(File_button_pos.x, File_button_size.y);


static const char *Menu_file_new_released = Menu_button_released;
static const char *Menu_file_new_pressed  = Menu_button_released;
static const plug::Vec2d File_button_new_size = Menu_list_size;
static const plug::Vec2d File_button_new_pos  = plug::Vec2d(File_button_pos.x, File_button_size.y + + File_button_open_size.y);

static const plug::Vec2d Tool_bar_pos  = plug::Vec2d(0, Config_bar_size.y); 
static const plug::Vec2d Tool_bar_size = plug::Vec2d(60, Background_window_size.y - Tool_bar_pos.y);

static const plug::Vec2d Canvase_manager_pos  = plug::Vec2d(Tool_bar_size.x, Config_bar_pos.y + Config_bar_size.y); 
static const plug::Vec2d Canvase_manager_size = Background_window_size - Canvase_manager_pos;


//================================================================


// static plug::Vec2d Menu_size = plug::Vec2d(1, 50);
// static plug::Vec2d Menu_pos  = plug::Vec2d(0, 0);

// static plug::Vec2d Colors_palette_size = plug::Vec2d(200, Menu_size.y - 20);
// static plug::Vec2d Colors_palette_pos  = plug::Vec2d(160, 10);



// static plug::Vec2d Menu_Button_size = plug::Vec2d(50, Menu_size.y);



// static plug::Vec2d Button_create_pos    = plug::Vec2d(0.0, 0.0);
// static plug::Vec2d Button_create_size   = Menu_Button_size;

// //Tools
// static plug::Vec2d Button_Tools_pos   = plug::Vec2d(50.0, 0.0);
// static plug::Vec2d Button_Tools_size  = Menu_Button_size;

// static plug::Vec2d Button_Brush_pos   = plug::Vec2d(Button_Tools_pos.x, Button_Tools_pos.y + Menu_Button_size.y);
// static plug::Vec2d Button_Brush_size  = Menu_Button_size;

// static plug::Vec2d Button_Line_pos   = plug::Vec2d(Button_Tools_pos.x + Menu_Button_size.x, Button_Tools_pos.y + Menu_Button_size.y);
// static plug::Vec2d Button_Line_size  = Menu_Button_size;


// static plug::Vec2d Button_Square_pos   = plug::Vec2d(Button_Tools_pos.x + 2 * Menu_Button_size.x, Button_Tools_pos.y + Menu_Button_size.y);
// static plug::Vec2d Button_Square_size  = Menu_Button_size;


// static plug::Vec2d Button_Circle_pos   = plug::Vec2d(Button_Tools_pos.x + 2 * Menu_Button_size.x, Button_Tools_pos.y + 2 * Menu_Button_size.y);
// static plug::Vec2d Button_Circle_size  = Menu_Button_size;

// static plug::Vec2d Button_Polyline_pos   = plug::Vec2d(Button_Tools_pos.x + Menu_Button_size.x, Button_Tools_pos.y + 2 * Menu_Button_size.y);
// static plug::Vec2d Button_Polyline_size  = Menu_Button_size;

// static plug::Vec2d Button_Pen_pos   = plug::Vec2d(Button_Tools_pos.x, Button_Tools_pos.y + 2 * Menu_Button_size.y);
// static plug::Vec2d Button_Pen_size  = Menu_Button_size;

// static plug::Vec2d Button_Eraser_pos   = plug::Vec2d(Button_Tools_pos.x, Button_Tools_pos.y + 3 * Menu_Button_size.y);
// static plug::Vec2d Button_Eraser_size  = Menu_Button_size;

// static plug::Vec2d Button_Text_pos   = plug::Vec2d(Button_Tools_pos.x + Menu_Button_size.x, Button_Tools_pos.y + 3 * Menu_Button_size.y);
// static plug::Vec2d Button_Text_size  = Menu_Button_size;


// //Filters

// static plug::Vec2d Button_Filter_pos   = plug::Vec2d(100.0, 0.0);
// static plug::Vec2d Button_Filter_size  = Menu_Button_size;

// static plug::Vec2d Button_Inclight_pos   = plug::Vec2d(Button_Filter_pos.x, Button_Filter_pos.y + Menu_Button_size.y);
// static plug::Vec2d Button_Inclight_size  = Menu_Button_size;

// static plug::Vec2d Button_Declight_pos   = plug::Vec2d(Button_Filter_pos.x, Button_Filter_pos.y + 2 * Menu_Button_size.y);
// static plug::Vec2d Button_Declight_size  = Menu_Button_size;

// static plug::Vec2d Button_Blackwhite_pos   = plug::Vec2d(Button_Filter_pos.x + Menu_Button_size.x, Button_Filter_pos.y + 1 * Menu_Button_size.y);
// static plug::Vec2d Button_Blackwhite_size  = Menu_Button_size;

// static plug::Vec2d Button_Invert_pos   = plug::Vec2d(Button_Filter_pos.x + Menu_Button_size.x, Button_Filter_pos.y + 2 * Menu_Button_size.y);
// static plug::Vec2d Button_Invert_size  = Menu_Button_size;


// static plug::Vec2d Button_Redfilter_pos   = plug::Vec2d(Button_Filter_pos.x + 2 * Menu_Button_size.x, Button_Filter_pos.y + 1 * Menu_Button_size.y);
// static plug::Vec2d Button_Redfilter_size  = Menu_Button_size;

// static plug::Vec2d Button_Greenfilter_pos   = plug::Vec2d(Button_Filter_pos.x + 2 * Menu_Button_size.x, Button_Filter_pos.y + 2 * Menu_Button_size.y);
// static plug::Vec2d Button_Greenfilter_size  = Menu_Button_size;

// static plug::Vec2d Button_Bluefilter_pos   = plug::Vec2d(Button_Filter_pos.x + 2 * Menu_Button_size.x, Button_Filter_pos.y + 3 * Menu_Button_size.y);
// static plug::Vec2d Button_Bluefilter_size  = Menu_Button_size;


static const char *Empty_texture = "src/img/empty.png";

#endif