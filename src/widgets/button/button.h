#ifndef _BUTTON_H_
#define _BUTTON_H_


#include "../widget/widget.h"


//================================================================================

class Action
{
    public:
        Action(){};
        
        virtual ~Action(){};

        virtual void operator() () const = 0;
    
};

//================================================================================

class Button : public Widget
{
    public:
        Button( const char *released_texture_file, const char *covered_texture_file, 
                const char *pressed_texture_file,  const char *disabled_texture_file,
                const Action *action, 
                const Vector &size, const Vector &pos, 
                const Widget *parent, const Vector &parent_size = Vector(1.0, 1.0),
                const Vector &origin = Vector(0.0, 0.0), const Vector &scale = Vector(1.0, 1.0));

        virtual ~Button()
        {
            delete action_;
        }


        Button(const Button &other) = delete;
        Button& operator= (const Button &other) = delete;

        virtual bool onMousePressed     (const Vector &pos, const MouseKey key, Container<Transform> &stack_transform);
        virtual bool onMouseMoved       (const Vector &pos, Container<Transform> &stack_transform);
        virtual bool onMouseReleased    (const Vector &pos, const MouseKey key, Container<Transform> &stack_transform);

        virtual bool onKeyboardPressed  (const KeyboardKey);
        virtual bool onKeyboardReleased (const KeyboardKey);

        virtual bool onTick             (const time_t delta_time);

        virtual void draw               (sf::RenderTarget &target, Container<Transform> &stack_transform);  

        const Action *action_;

        enum ButtonState
        {
            RELEASED, 
            COVERED,
            PRESSED,
            DISABLED,
        };

        ButtonState state_;
        ButtonState prev_state_;

    private:

        const sf::Texture* defineTexture() const;
        void getDrawFormat(sf::VertexArray &vertex_array, const Transform &transform) const;

        sf::Texture released_texture_, covered_texture_, 
                    pressed_texture_, disabled_texture_;
        
        time_t covering_time_;
};


// class ButtonList : public Button
// {
//     public:
//         ButtonList (const char *released_texture_file, const char *covered_texture_file, 
//                     const char *pressed_texture_file,  const char *disabled_texture_file,
//                     const Action *action, 
//                     const Dot &offset, const Vector &scale):
//                     Button(released_texture_file, covered_texture_file, 
//                            pressed_texture_file, disabled_texture_file, 
//                            action, offset, scale), buttons_(){}

//         virtual ~ButtonList()
//         {
//             size_t size = buttons_.GetSize();
//             for (size_t it = 0; it < size; it++)
//                 delete buttons_[it];

//             delete action_;
//         }


//         ButtonList(const ButtonList &other) = delete;

//         virtual ButtonList &operator= (const ButtonList &other) = delete;

//         virtual bool OnMousePressed     (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform);
//         virtual bool OnMouseMoved       (const double x, const double y, Container<Transform> &stack_transform);
//         virtual bool OnMouseReleased    (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform);

//         virtual bool OnKeyboardPressed  (const KeyboardKey);
//         virtual bool OnKeyboardReleased (const KeyboardKey);

//         virtual void Draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform) override;    
        
//         virtual void PassTime           (const time_t delta_time);

//         void AddButton                  (Button *button);

//         Transform GetTransform() const {return transform_;}

//         const Action *action_;
//         Container<Button*> buttons_;
        
//     protected:

        
        
// };

//================================================================================

class Click : public Action
{
    public:
        Click(bool *ptr): flag_(ptr){};
        ~Click(){};

        void operator() () const
        {
            *flag_ = true;
        }

    private:
        bool *flag_; 
};

//================================================================================

// class ShowButtonList : public Action
// {
//     public:
//         ShowButtonList(Container<Button*> *buttons): buttons_(buttons){};
//         ~ShowButtonList(){};

//         void operator() () const
//         {
//             size_t size = buttons_->GetSize();
//             for (size_t it = 0; it < size; it++)
//                 (*buttons_)[it]->state_ = (*buttons_)[it]->prev_state_;
//         }

//     private:
//         Container<Button*> *buttons_; 
// };

//================================================================================

#endif