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

        Click(const Click &other) = delete;
        Click& operator= (const Click &other) = delete;


    private:
        bool &m_flag; 
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

        Button( const plug::Texture &texture_released, const plug::Texture &texture_covered,
                const plug::Texture &texture_pressed,  const plug::Texture &texture_disabled,
                const plug::LayoutBox& box,
                Action *action):
                Widget(box),
                m_state(RELEASED), m_prev_state(RELEASED),   
                m_texture_released(texture_released.width, texture_released.height, texture_released.data),
                m_texture_covered(texture_covered.width, texture_covered.height, texture_covered.data),
                m_texture_pressed(texture_pressed.width, texture_pressed.height, texture_pressed.data),
                m_texture_disabled(texture_disabled.width, texture_disabled.height, texture_disabled.data),      
                m_covering_time(0),
                m_action(action){}    

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

class TextButton : public Button
{
    public:

        TextButton( const plug::Texture &texture_released, const plug::Texture &texture_covered,
                    const plug::Texture &texture_pressed,  const plug::Texture &texture_disabled,
                    const Title &title_released, const Title &title_pressed,
                    const plug::LayoutBox& box, Action *action):
                    Button( texture_released, texture_covered, 
                            texture_pressed, texture_disabled, 
                            box, action),
                    m_title_released(title_released), m_title_pressed(title_pressed){}    

        TextButton(const TextButton &other) = delete;
        TextButton& operator= (const Button &other) = delete;

        virtual ~TextButton(){}

        virtual void draw(plug::TransformStack &stack, plug::RenderTarget &target);

    protected:

        Title m_title_released;
        Title m_title_pressed;
};

class ShowButtonList : public Action
{
    public:
        ShowButtonList(Container<Button*> &buttons): m_buttons(buttons){}
        ~ShowButtonList(){};

        void operator()() 
        {
            size_t size = m_buttons.getSize();
            for (size_t it = 0; it < size; it++)
            {
                m_buttons[it]->m_state = m_buttons[it]->m_prev_state;
            }
        }

        ShowButtonList(const ShowButtonList &other) = delete;
        ShowButtonList& operator= (const ShowButtonList &other) = delete;

    private:
        Container<Button*> &m_buttons; 
};

class ButtonList : public Button
{
    public:
        ButtonList (const plug::Texture &texture_released, const plug::Texture &texture_covered,
                    const plug::Texture &texture_pressed,  const plug::Texture &texture_disabled,
                    const plug::LayoutBox& box):
                    Button( texture_released, texture_covered, 
                            texture_pressed, texture_disabled, 
                            box, nullptr),
                    m_buttons(){}

        virtual ~ButtonList()
        {
            size_t size = m_buttons.getSize();
            for (size_t it = 0; it < size; it++)
                delete m_buttons[it];
        }

        ButtonList(const ButtonList &other) = delete;
        ButtonList &operator= (const ButtonList &other) = delete;

    public:

        virtual void draw(plug::TransformStack &stack, plug::RenderTarget &target);
        virtual void onParentUpdate(const plug::LayoutBox &parent_box);

        void addButton(Button *button);

    protected:

        virtual void onTick             (const plug::TickEvent &event, plug::EHC &context);

        virtual void onMouseMove        (const plug::MouseMoveEvent &event, plug::EHC &context);
        virtual void onMousePressed     (const plug::MousePressedEvent &event,plug::EHC &context);
        virtual void onMouseReleased    (const plug::MouseReleasedEvent &event, plug::EHC &context);

        Container<Button*> m_buttons;
};

#endif