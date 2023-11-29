#include "ColorPalette.h"

plug::Color ColorPalette::getFGColor(void) const
{
    return m_fg_color;
}

plug::Color ColorPalette::getBGColor(void) const
{
    return m_bg_color;
}

void ColorPalette::setFGColor(plug::Color new_fg_color)
{
    m_fg_color = new_fg_color;
}

void ColorPalette::setBGColor(plug::Color new_bg_color)
{
    m_bg_color = new_bg_color;
}