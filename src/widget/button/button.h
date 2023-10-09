#ifndef _BUTTON_H_
#define _BUTTON_H_


#include "../widget.h"


//================================================================================

class Action
{
    public:
        Action(){};
        
        virtual ~Action(){};

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

//================================================================================

class Button : public Widget
{
    public:
        Button (const char *released_texture_file, const char *covered_texture_file, 
                const char *pressed_texture_file,  const char *disabled_texture_file,
                const Action *action, 
                const Dot offset, const Vector scale);

        virtual ~Button()
        {
            delete action_;
        }


        Button(const Button &other) = delete;

        virtual Button& operator= (const Button &other) = delete;

        virtual bool OnMousePressed     (const int x, const int y, const MouseKey key, Container<Transform> &stack_transform);
        virtual bool OnMouseMoved       (const int x, const int y, Container<Transform> &stack_transform);
        virtual bool OnMouseReleased    (const int x, const int y, const MouseKey key, Container<Transform> &stack_transform);

        virtual bool OnKeyboardPressed  (const KeyboardKey);
        virtual bool OnKeyboardReleased (const KeyboardKey);

        virtual void Draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform) const override;    
        
        virtual void PassTime           (const time_t delta_time);

        bool CheckIn (const Dot &mouse_pos) const;

        Transform GetTransform() const {return transform_;}

        const Action *action_;
        Button_Status prev_status_;

    protected:
        const sf::Texture* DefineTexture() const;
        void GetNewSize(sf::VertexArray &vertex_array, const Transform &transform) const;

        sf::Texture released_texture_, covered_texture_, 
                    pressed_texture_, disabled_texture_;
                    
        Transform transform_;
        double width_, hieght_;

        Button_Status status_;
        time_t covering_time_;


};



class Click : public Action
{
    public:
        Click(){};
        ~Click(){};

        bool operator() () const
        {
            return true;
        } 
};

//================================================================================

#endif