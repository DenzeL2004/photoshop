#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Impl/Widget/Widget.h"
// #include "Impl/Graphics/Graphic.h"

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

        enum ButtonState
        {
            RELEASED, 
            COVERED,
            PRESSED,
            DISABLED,
        };

        Button( plug::Texture texture_released, plug::Texture texture_covered,
                plug::Texture texture_pressed,  plug::Texture texture_disabled,
                const plug::LayoutBox& box,
                const Action *action, 
                const Widget *parent = nullptr,
                const plug::Vec2d &scale = Vec2d(1.0, 1.0)):
                Widget(box),
                texture_released_(texture_released.width, texture_released.height, texture_released.data),
                texture_covered_(texture_covered.width, texture_covered.height, texture_covered.data),
                texture_pressed_(texture_pressed.width, texture_pressed.height, texture_pressed.data),
                texture_disabled_(texture_disabled.width, texture_disabled.height, texture_disabled.data),
                action_(action),
                state_(RELEASED), prev_state_(RELEASED),
                parent_(parent),             
                scale_(scale),
                covering_time_(0){}    


        virtual ~Button()
        {
            delete action_;

            delete texture_released_.data;
            delete texture_covered_.data;
            delete texture_pressed_.data;
            delete texture_disabled_.data;
        }

        Button(const Button &other) = delete;
        Button& operator= (const Button &other) = delete;

        Action const *action_;

        ButtonState state_;
        ButtonState prev_state_;

        virtual void draw(plug::TransformStack &stack, plug::RenderTarget &target);

    protected:

        virtual void onTick             (const plug::TickEvent &event, plug::EHC &context);

        virtual void onMouseMove        (const plug::MouseMoveEvent &event, plug::EHC &context);
        virtual void onMousePressed     (const plug::MousePressedEvent &event,plug::EHC &context);
        virtual void onMouseReleased    (const plug::MouseReleasedEvent &event, plug::EHC &context);

        bool covers(plug::TransformStack &stack, const plug::Vec2d &position) const;

        void getDrawFormat(const plug::Texture &texture, plug::VertexArray &vertex_array, Transform &transform) const;

        const plug::Texture* defineTexture() const;

        plug::Texture texture_released_, texture_covered_, 
                      texture_pressed_, texture_disabled_;

        const plug::Widget *parent_;

        plug::Vec2d scale_;
    
        double covering_time_;
};


// class ButtonList : public Button
// {
//     public:
//         ButtonList (const char *released_texture_file, const char *covered_texture_file, 
//                     const char *pressed_texture_file,  const char *disabled_texture_file,
//                     const Action *action, 
//                     const Vec2d &size, const Vec2d &pos, 
//                     const Widget *parent, const Vec2d &parent_size = Vec2d(1.0, 1.0),
//                     const Vec2d &origin = Vec2d(0.0, 0.0), const Vec2d &scale = Vec2d(1.0, 1.0)):
//                     Button(released_texture_file, covered_texture_file, 
//                            pressed_texture_file, disabled_texture_file, 
//                            action, size, pos, parent, (parent != nullptr) ? parent->getLayoutBox().getSize() : parent_size, origin, scale), buttons_(){}

//         virtual ~ButtonList()
//         {
//             size_t size = buttons_.getSize();
//             for (size_t it = 0; it < size; it++)
//                 delete buttons_[it];

//             delete action_;
//         }


//         ButtonList(const ButtonList &other) = delete;

//         virtual ButtonList &operator= (const ButtonList &other) = delete;

//         virtual bool onMousePressed     (const Vec2d &pos, const MouseKey key, Container<Transform> &stack_transform);
//         virtual bool onMouseMoved       (const Vec2d &pos, Container<Transform> &stack_transform);
//         virtual bool onMouseReleased    (const Vec2d &pos, const MouseKey key, Container<Transform> &stack_transform);

//         virtual bool onKeyboardPressed  (const KeyboardKey);
//         virtual bool onKeyboardReleased (const KeyboardKey);

//         virtual bool onTick             (const time_t delta_time);

//         virtual void draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform) override;    
        
//         void addButton                  (Button *button);


//         const Action *action_;
//         Container<Button*> buttons_;
        
//     protected:

        
        
// };

//================================================================================

class Click : public Action
{
    public:
        Click(bool &ptr): flag_(ptr){};
        ~Click(){};

        void operator() () const
        {
            flag_ = true;
        }

    private:
        bool &flag_; 
};

//================================================================================

// class ShowButtonList : public Action
// {
//     public:
//         ShowButtonList(Container<Button*> *buttons): buttons_(buttons){};
//         ~ShowButtonList(){};

//         void operator() () const
//         {
//             size_t size = buttons_->getSize();
//             for (size_t it = 0; it < size; it++)
//                 (*buttons_)[it]->state_ = (*buttons_)[it]->prev_state_;
//         }

//     private:
//         Container<Button*> *buttons_; 
// };

//================================================================================

#endif