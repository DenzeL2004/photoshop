#ifndef _FRAME_H_
#define _FRAME_H_

#include <cstring>

#include "Impl/Widget/Window/Window.h"
#include "Container/Container.h"

struct Title
{
    Title():
            pos(plug::Vec2d(0.0, 0.0)), 
            msg(""), 
            width(0),
            color(0, 0, 0, 255){}

    Title(  const plug::Vec2d &pos_, const char *msg_, const double width_, const plug::Color &color_):
            pos(pos_),
            msg(msg_), 
            width(width_),
            color(color_){}

    ~Title(){} 

    Title(const Title &other) = default;
    Title &operator= (const Title &other) = default;

    plug::Vec2d pos;

    const char* msg;
    double width;

    const plug::Color color;
};

//=================================================================================================

static const plug::Vec2d Size_min_limit = plug::Vec2d(400, 400);

class Frame: public Window
{
    public:

        enum DecoratorState
        {
            DEFAULT = 0, 
            HOLD,
        };

        enum Borders
        {
            LEFT    = 1 << 1,
            RIGHT   = 1 << 2,
            TOP     = 1 << 3,
            BOTTOM  = 1 << 4,
        };

        Frame(  plug::Texture texture,
                const Title &title,
                const plug::LayoutBox& box, 
                const Widget *parent = nullptr):
                Window(texture, box, parent),
                m_title(title),
                m_widgets(),
                m_hold_pos(0.0, 0.0), m_prev_pos(0.0 ,0.0), m_state(DEFAULT){}
                
        virtual ~Frame()
        {
            size_t cnt = m_widgets.getSize();
            for (size_t it = 0; it < cnt; it++)
                delete m_widgets[it];
        }

        virtual void draw(plug::TransformStack &stack, plug::RenderTarget &target);

        virtual void onParentUpdate(const plug::LayoutBox &parent_box);

        void addWidget(Widget* widget);

        void onEvent(const plug::Event &event, plug::EHC &context);

    protected:

        virtual void onTick             (const plug::TickEvent &event, plug::EHC &context);

        virtual void onMouseMove        (const plug::MouseMoveEvent &event, plug::EHC &context);
        virtual void onMousePressed     (const plug::MousePressedEvent &event, plug::EHC &context);
        virtual void onMouseReleased    (const plug::MouseReleasedEvent &event, plug::EHC &context);

        virtual void onKeyboardPressed  (const plug::KeyboardPressedEvent &event, plug::EHC &context);
        virtual void onKeyboardReleased (const plug::KeyboardReleasedEvent &event, plug::EHC &context);

    private:

        void clickOnBorder(void);

        void resizeFrame    (const plug::Vec2d &new_coord);
        void moveFrame      (const plug::Vec2d &new_coord);

        const Title m_title;

        Container<Widget*> m_widgets;

        size_t m_state;

        plug::Vec2d m_hold_pos;
        plug::Vec2d m_prev_pos;
};

#endif