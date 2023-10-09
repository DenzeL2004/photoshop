#ifndef _BUTTON_H_
#define _BUTTON_H_


#include "../widget.h"
//================================================================================

class Action
{
    public:
        Action(){};
        
        virtual ~Action() = default;

        virtual bool operator() () const = 0;
    
};

//================================================================================

enum Button_Status
{
    RELEASED, 
    COVERED,
    PRESSED,
    DISABLED,
};


class Button : public Widget
{
    public:
        Button (const char *released_texture_file, const char *covered_texture_file, 
                const char *pressed_texture_file,  const char *disabled_texture_file,
                const Action *action, const Dot offset, 
                const double scale_x, const double scale_y);

        virtual ~Button()
        {
            delete action_;
        }


        Button(const Button &other) = delete;

        virtual Button& operator= (const Button &other) = delete;

        virtual bool OnMousePressed     (const MouseKey key, Container<Transform> &stack_transform);
        virtual bool OnMouseMoved       (const int x, const int y, Container<Transform> &stack_transform);
        virtual bool OnMouseReleased    (const MouseKey key, Container<Transform> &stack_transform);

        virtual bool OnKeyboardPressed  (const KeyboardKey);
        virtual bool OnKeyboardReleased (const KeyboardKey);

        virtual void Draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform) const override;    
        
        virtual void PassTime           (const time_t delta_time);

        bool CheckIn (const Dot &mouse_pos) const;

        void SetState(const Button_Status new_status) 
        {
            status_ = new_status;
            return;
        }

        const Action *action_;
        Button_Status status_;
        Button_Status prev_status_;

    protected:
        void DefineSprite(sf::Sprite &sprite) const;

        sf::Texture released_texture_, covered_texture_, 
                    pressed_texture_, disabled_texture_;
                    
        Transform transform_;
        double width_, hieght_;

        time_t covering_time_;
};

#endif