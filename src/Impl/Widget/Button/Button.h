#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Impl/Widget/Widget.h"
// #include "Impl/Graphics/Graphic.h"

//================================================================================

class Action
{
    public:
        Action(){}
        
        virtual ~Action(){}

        virtual void operator() () = 0;
    
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
                Action *action):
                Widget(box),
                m_texture_released(texture_released.width, texture_released.height, texture_released.data),
                m_texture_covered(texture_covered.width, texture_covered.height, texture_covered.data),
                m_texture_pressed(texture_pressed.width, texture_pressed.height, texture_pressed.data),
                m_texture_disabled(texture_disabled.width, texture_disabled.height, texture_disabled.data),
                m_action(action),
                m_state(RELEASED), m_prev_state(RELEASED),         
                m_covering_time(0){}    


        virtual ~Button()
        {
            delete m_action;
        }

        Button(const Button &other) = delete;
        Button& operator= (const Button &other) = delete;

        ButtonState m_state;
        ButtonState m_prev_state;

        virtual void draw(plug::TransformStack &stack, plug::RenderTarget &target);

        void doAction(void);

    protected:

        virtual void onTick             (const plug::TickEvent &event, plug::EHC &context);

        virtual void onMouseMove        (const plug::MouseMoveEvent &event, plug::EHC &context);
        virtual void onMousePressed     (const plug::MousePressedEvent &event,plug::EHC &context);
        virtual void onMouseReleased    (const plug::MouseReleasedEvent &event, plug::EHC &context);

        const plug::Texture* defineTexture() const;

        plug::Texture m_texture_released, m_texture_covered, 
                      m_texture_pressed, m_texture_disabled;

        double m_covering_time;

        Action *m_action;
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

//             delete m_action;
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


//         const Action *m_action;
//         Container<Button*> buttons_;
        
//     protected:

        
        
// };

//================================================================================

class Click : public Action
{
    public:
        Click(bool &ptr): m_flag(ptr){};
        ~Click(){};

        void operator() ()
        {
            m_flag ^= true;
        }

    private:
        bool &m_flag; 
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
//                 (*buttons_)[it]->m_state = (*buttons_)[it]->m_prev_state;
//         }

//     private:
//         Container<Button*> *buttons_; 
// };

//================================================================================

#endif