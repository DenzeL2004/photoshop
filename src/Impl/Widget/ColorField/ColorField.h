#ifndef _COLOR_FIELD_H_
#define _COLOR_FIELD_H_

#include "Impl/Widget/Widget.h"
#include "Impl/Tool/ColorPalette/ColorPalette.h"
#include "Impl/LayoutBox/BaseLayoutBox/BaseLayoutBox.h"
#include "Impl/RenderTarget/SfmlRenderTarget/RenderTarget.h"

#include "Impl/Graphic/Graphic.h"

#include <SFML/Graphics.hpp>

static size_t Color_field_size = 256;
static size_t Hue_limit = 360;


class SelectionHue: public Widget
{
    public:
        SelectionHue( const plug::Vec2d pos, const plug::Vec2d scale, uint16_t &hue):
                    Widget(BaseLayoutBox(pos, plug::Vec2d(Hue_limit, 30), plug::Vec2d(1, 1), false, false)),
                    m_hue(hue),
                    m_texture(Hue_limit, 1),
                    m_scale(scale)
        {
            for (size_t it = 0; it < Hue_limit; it++)
            {
                m_texture.setPixel(it, 0, HSV2RGB(it, Color_field_size - 1, Color_field_size - 1));
            }
        }   
                
        virtual ~SelectionHue(){}

        virtual void draw(plug::TransformStack &stack, plug::RenderTarget &target);

        SelectionHue(const SelectionHue &other) = delete;
        virtual SelectionHue &operator= (const SelectionHue &other) = delete;

    protected:

        virtual void onMousePressed     (const plug::MousePressedEvent &event, plug::EHC &context);

    private:
        
        uint16_t &m_hue;

        plug::Texture m_texture;
        plug::Vec2d m_scale;
};


class ColorField: public Widget
{
    public:
        ColorField( const plug::Vec2d pos, const plug::Vec2d scale, plug::ColorPalette &color_palette):
                    Widget(BaseLayoutBox(pos, plug::Vec2d(Color_field_size, Color_field_size), plug::Vec2d(1, 1), false, false)),
                    m_color_palette(color_palette),
                    m_hue(0),
                    m_x(Color_field_size - 1), m_y(Color_field_size - 1),
                    m_texture(Color_field_size, Color_field_size),
                    m_scale(scale),
                    selection_hue(plug::Vec2d(0, -50), plug::Vec2d(0.73, 1), m_hue)
        {
            defineTexture();
        }   
                
        virtual ~ColorField(){}

        virtual void draw(plug::TransformStack &stack, plug::RenderTarget &target);

        ColorField(const ColorField &other) = delete;
        ColorField &operator= (const ColorField &other) = delete;

    protected:

        virtual void onMousePressed     (const plug::MousePressedEvent &event, plug::EHC &context);

    private:
        void defineTexture(void);

        plug::ColorPalette &m_color_palette;
        uint16_t m_hue;
        
        size_t m_x;
        size_t m_y;

        plug::Texture m_texture;
        plug::Vec2d m_scale;

        SelectionHue selection_hue;
};


#endif