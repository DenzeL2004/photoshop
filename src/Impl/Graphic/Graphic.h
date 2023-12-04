#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_

#include <cassert>
#include <cstring>
#include <string>

#include "Plug/Math.h"
#include "Plug/Graphics.h"

#include "Plug/Color.h"

#include "GraphicConfig.h"


void    drawLine        (plug::RenderTarget &target, 
                         const plug::Vec2d &begin, const plug::Vec2d &end, const plug::Color color = plug::White);
                         
void    drawCircle      (plug::RenderTarget &target, const plug::Vec2d &pos, 
                         const float radius, const plug::Color color = plug::White);

void    drawRectangle   (plug::RenderTarget &target, 
                         const plug::Vec2d &left_up, const plug::Vec2d &right_down, const plug::Color color = plug::White);

void    writeText       (plug::RenderTarget &target, const plug::Vec2d &pos, 
                         const char *text, const double thicknesses,
                         const plug::Color color = plug::White);


#endif 