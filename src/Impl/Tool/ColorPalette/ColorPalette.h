
#ifndef _PLUG_TOOL_COLOR_PALETTE_H_
#define _PLUG_TOOL_COLOR_PALETTE_H_

#include "Plug/Tool/ColorPalette.h"
#include "Impl/Graphic/GraphicConfig.h"


class ColorPalette : public plug::ColorPalette
{
    public:

        ColorPalette():m_bg_color(plug::White), m_fg_color(plug::Black){}
        ~ColorPalette(){}
  
        plug::Color getFGColor(void) const;
        plug::Color getBGColor(void) const;


        void setFGColor(plug::Color new_fg_color);
        void setBGColor(plug::Color new_bg_color);

        ColorPalette(const ColorPalette &other) = delete;
        ColorPalette &operator= (const ColorPalette &other) = delete;

    private:

        plug::Color m_bg_color;
        plug::Color m_fg_color;
};

#endif 
