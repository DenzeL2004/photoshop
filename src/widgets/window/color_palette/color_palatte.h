#ifndef _COLOR_PALETTE_H_
#define _COLOR_PALETTE_H_

#include "../../widget/widget.h"

const size_t Color_limit = 256;

class ColorPalette : public Widget
{
    public:
        ColorPalette(   const Vec2d &size, const Vec2d &pos, 
                        const Widget *parent, const Vec2d &parent_size = Vec2d(1.0, 1.0),
                        const Vec2d &origin = Vec2d(0.0, 0.0), const Vec2d &scale = Vec2d(1.0, 1.0));

        virtual ~ColorPalette()
        {
            delete[] colors_;
        }


        ColorPalette(const ColorPalette &other) = delete;
        ColorPalette& operator= (const ColorPalette &other) = delete;

        virtual bool onMousePressed     (const Vec2d &pos, const MouseKey key, Container<Transform> &stack_transform);
        virtual bool onMouseMoved       (const Vec2d &pos, Container<Transform> &stack_transform);
        virtual bool onMouseReleased    (const Vec2d &pos, const MouseKey key, Container<Transform> &stack_transform);

        virtual void draw               (sf::RenderTarget &target, Container<Transform> &stack_transform);  

        sf::Color getActiveColor () {return active_color_;}

    private:
        
        void getDrawFormat(sf::VertexArray &vertex_array, Transform &trf) const;

        sf::Texture texture_;

        sf::Color *colors_;
        sf::Color active_color_;
};

#endif