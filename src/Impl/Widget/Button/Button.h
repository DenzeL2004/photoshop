#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Impl/Widget/Widget.h"
#include "Container/Container.h"

class Action
{
    public:
        Action(){}
        
        virtual ~Action(){}

        virtual void operator() () = 0;
    
};

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

class Button;
class ButtonList;

// class ShowButtonList : public Action
// {
//     public:
//         ShowButtonList(Container<Button*> &buttons): m_buttons(buttons){}
//         ~ShowButtonList(){};

//         void operator()() 
//         {
//             size_t size = m_buttons.getSize();
//             for (size_t it = 0; it < size; it++)
//                 m_buttons[it]->m_state = m_buttons[it]->m_prev_state;
//         }

//     private:
//         Container<Button*> &m_buttons; 
// };


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

        Button( const plug::Texture &texture_released, const plug::Texture &texture_covered,
                const plug::Texture &texture_pressed,  const plug::Texture &texture_disabled,
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
//         ButtonList (const plug::Texture &texture_released, const plug::Texture &texture_covered,
//                     const plug::Texture &texture_pressed,  const plug::Texture &texture_disabled,
//                     const plug::LayoutBox& box):
//                     Button( texture_released, texture_covered, 
//                             texture_pressed, texture_disabled, 
//                             box, new ShowButtonList(m_buttons)){}

//         virtual ~ButtonList()
//         {
//             size_t size = m_buttons.getSize();
//             for (size_t it = 0; it < size; it++)
//                 delete m_buttons[it];
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
        
//     protected:

//         Container<Button*> m_buttons;
// };

#endif