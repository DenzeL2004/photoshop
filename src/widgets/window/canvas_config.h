#ifndef _CANVAS_CONFIG_H_
#define _CANVAS_CONFIG_H_

char *Up_Scl_Prs    = "src/img/arrowUpPressed.png";
char *Up_Scl_Rel    = "src/img/arrowUpReleased.png";

char *Down_Scl_Prs  = "src/img/arrowDownPressed.png";
char *Down_Scl_Rel  = "src/img/arrowDownReleased.png";

char *Left_Scl_Prs  = "src/img/arrowLeftPressed.png";
char *Left_Scl_Rel  = "src/img/arrowLeftReleased.png";

char *Right_Scl_Prs = "src/img/arrowRightPressed.png";
char *Right_Scl_Rel = "src/img/arrowRightReleased.png";

char *Ver_Scl   = "src/img/scroll.png";

char *Hor_Scl   = "src/img/scroll.png";

//====================================================================

static const Dot Title_offset = Dot(10.0, 5.0);
static const Dot Frame_size   = Dot(730, 540.0); 
static const Dot Frame_pos    = Dot(10.0, 10.0);

static const Dot Close_button_size = Dot(25.0, 25.0);
static const Dot Close_button_pos  = Dot(705.0, 0.0);

//====================================================================
//Canvas

static const Dot Canvas_size = Dot(2000.0, 2000.0);
static const Dot Canvas_view_size = Vector(680, 470.0);
static const Dot Canvas_pos       = Vector(10.0, 60.0);

//====================================================================
//Scrollbars

static const Dot Scroll_hor_size = Dot(680.0, 20.0);
static const Dot Scroll_hor_pos  = Dot(10.0, 30.0);

static const Dot Scroll_ver_size = Dot(20, 470.0);
static const Dot Scroll_ver_pos  = Dot(695.0, 60.0);

static const Dot Buttons_scroll_size = Vector(20.0, 20.0);

static const Dot Left_pos   = Vector(0.0, 0.0);
static const Dot Right_pos  = Vector(660.0, 0.0);

static const Dot Up_pos     = Vector(0.0, 0.0);
static const Dot Down_pos   = Vector(0.0, 450.0);

//====================================================================


#endif