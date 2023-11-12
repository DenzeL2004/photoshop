#ifndef _GRAPHIC_CONFIG_H_
#define _GRAPHIC_CONFIG_H_

const uint32_t Default_window_height = 1200;
const uint32_t Default_window_width  = 1604;

const uint32_t Default_plane_height  = (uint32_t)((double)Default_window_height  / 1.1);
const uint32_t Default_plane_width  = (uint32_t)((double)Default_window_width / 1.75);

const double X_plane_start = 10.0;
const double Y_plane_start = 10.0;

const Dot Left_corner  = Dot(X_plane_start, Y_plane_start);
const Dot Right_corner = Dot(X_plane_start + Default_window_width + 50, Y_plane_start);


//===============================================================================

const uint32_t Max_limit_vector_cnt = 100;

const float Stroke_radius = 1.5f;

const double Len_tendril = 1.0;

const sf::Color Default_vec_color = sf::Color::Red;
const sf::Color Default_axis_color = sf::Color::Black;
const sf::Color Default_plane_color = sf::Color::White;

const useconds_t Mouse_press_delay = 50U;




#endif //#endif _GRAPHIC_CONFIG_H_