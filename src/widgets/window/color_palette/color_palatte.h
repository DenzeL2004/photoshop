#ifndef _COLOR_PALETTE_H_
#define _COLOR_PALETTE_H_

#include "../../widget/widget.h"

const size_t Color_limit = 256;

class ColorPalette : public Widget
{
    public:
        ColorPalette(   const Vector &size, const Vector &pos, 
                        const Widget *parent, const Vector &parent_size = Vector(1.0, 1.0),
                        const Vector &origin = Vector(0.0, 0.0), const Vector &scale = Vector(1.0, 1.0));

        virtual ~ColorPalette()
        {
            delete[] colors_;
        }


        ColorPalette(const ColorPalette &other) = delete;
        ColorPalette& operator= (const ColorPalette &other) = delete;

        virtual bool onMousePressed     (const Vector &pos, const MouseKey key, Container<Transform> &stack_transform);
        virtual bool onMouseMoved       (const Vector &pos, Container<Transform> &stack_transform);
        virtual bool onMouseReleased    (const Vector &pos, const MouseKey key, Container<Transform> &stack_transform);

        virtual void draw               (sf::RenderTarget &target, Container<Transform> &stack_transform);  

        sf::Color getActiveColor () {return active_color_;}

    private:
        
        void getDrawFormat(sf::VertexArray &vertex_array, const Transform &trf) const;

        sf::Texture texture_;

        sf::Color *colors_;
        sf::Color active_color_;
};

#endif