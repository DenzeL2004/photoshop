#ifndef _COLOR_VIEW_H_
#define _COLOR_VIEW_H_

#include "Impl/Widget/Widget.h"
#include "Plug/Tool/ColorPalette.h"

class ColorView : public Widget
{
    public:

        ColorView(  plug::ColorPalette &color_palette,
                    const plug::LayoutBox& box):
                    Widget(box), 
                    m_color_palette(color_palette){}
                
        ColorView(const ColorView &other) = delete;
        ColorView& operator= (const ColorView &other) = delete;

        virtual ~ColorView(){}
        
        virtual void draw (plug::TransformStack& stack, plug::RenderTarget& target);  

    protected:

        void onMousePressed(const plug::MousePressedEvent &event, plug::EHC &context);
        
    private:

        plug::ColorPalette &m_color_palette;
};

#endif