#ifndef _COLOR_PALETTE_H_
#define _COLOR_PALETTE_H_

#include "../../widget/widget.h"

const double Max_ray = 256.0;
const double Min_ray = 5.0;

class ColorPalette : public Widget
{
    public:
        ColorPalette(   const Vector &size, const Vector &pos, 
                        const Widget *parent, const Vector &parent_size = Vector(1.0, 1.0),
                        const Vector &origin = Vector(0.0, 0.0), const Vector &scale = Vector(1.0, 1.0)):
                        Widget(size, pos, parent, parent_size, origin, scale),
                        colors_(), active_color_(sf::Color::White)
                        {
                            colors_= new sf::Color[256 * 6];
                        }

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

    private:
        
        void getDrawFormat(const sf::Texture &texture, sf::VertexArray &vertex_array, const Transform &trf) const;

        sf::Color *colors_;
        sf::Color active_color_;
};

#endif