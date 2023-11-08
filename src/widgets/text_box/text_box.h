#ifndef _TEXT_BOX_H_
#define _TEXT_BOX_H_

#include "../widget/widget.h"

class TextBox : public Widget
{
    public:
        TextBox(    const size_t limit_cnt_symbols, const size_t thicknesses, const sf::Color *color,
                    const Vector &pos, 
                    const Widget *parent, const Vector &parent_size = Vector(1.0, 1.0),
                    const Vector &origin = Vector(0.0, 0.0), const Vector &scale = Vector(1.0, 1.0));

        virtual ~TextBox()
        {
            delete[] buf_;
        }


        TextBox(const TextBox &other) = delete;
        TextBox& operator= (const TextBox &other) = delete;

        virtual bool onMousePressed     (const Vector &pos, const MouseKey key, Container<Transform> &stack_transform);
    
        virtual bool onKeyboardPressed  (const KeyboardKey key);
        virtual bool onKeyboardReleased (const KeyboardKey key);

        virtual void draw               (sf::RenderTarget &target, Container<Transform> &stack_transform);  

        virtual bool onTick             (const float delta_time);

        void clear();

        sf::Text getText                ();

    private:
        
        sf::Font font_;
        size_t thicknesses_;
        
        size_t cnt_symbols_;
        size_t limit_cnt_symbols_;
        char *buf_;

        Vector cursor_;

        const sf::Color &color_;

        float acume_time_;
};

#endif