#ifndef _DECORATOR_H_
#define _DECORATOR_H_

#include "../button/button.h"
#include "../window/window.h"

enum DecoratorState
{
    DEFAULT = 0, 
    HOLD,
};


static const Vec2d Size_min_limit = Vec2d(400, 400);


//=================================================================================================

struct Title
{
    Title():
            pos_(Dot(0.0, 0.0)), 
            msg_(""),  len_msg_(0), 
            color_(sf::Color::Black){}

    Title(  const Vec2d &pos, const char *msg, const sf::Color &color):
            pos_(pos),
            msg_(msg), 
            len_msg_(strlen(msg)), 
            color_(color){}

    ~Title(){} 

    Title(const Title &other) = default;
    Title &operator= (const Title &other) = default;

    Vec2d pos_;

    const char* msg_;
    size_t len_msg_;
    const sf::Color color_;
};

class Frame: public Window
{

    public:

        enum Borders
        {
            LEFT    = 1 << 1,
            RIGHT   = 1 << 2,
            TOP     = 1 << 3,
            BOTTOM  = 1 << 4,
        };

        Frame(  const char *path_texture,
                const Title &title,
                const Vec2d &size, const Vec2d &pos, 
                const Widget *parent, const Vec2d &parent_size = Vec2d(1.0, 1.0),
                const Vec2d &origin = Vec2d(0.0, 0.0), const Vec2d &scale = Vec2d(1.0, 1.0));

        virtual ~Frame()
        {
            size_t cnt = widgets_.getSize();
            for (size_t it = 0; it < cnt; it++)
                delete widgets_[it];
        }

        virtual bool onMousePressed     (const Vec2d &pos, const MouseKey key, Container<Transform> &stack_transform);
        virtual bool onMouseMoved       (const Vec2d &pos, Container<Transform> &stack_transform);
        virtual bool onMouseReleased    (const Vec2d &pos, const MouseKey key, Container<Transform> &stack_transform);
        
        virtual bool onKeyboardPressed  (const KeyboardKey);
        virtual bool onKeyboardReleased (const KeyboardKey);

        virtual bool onTick             (const float delta_time);
        virtual void onUpdate           (const LayoutBox &parent_layout);

        virtual void draw               (sf::RenderTarget &target, Container<Transform> &stack_transform);  

        virtual void setFocus (const bool flag); 

        void addWidget(Widget* widget);


    private:
        
        void clickOnBorder();

        void resizeFrame        (const Dot &new_coord);
        void moveFrame          (const Dot &new_coord);

        const Title title_;

        Container<Widget*> widgets_;

        size_t state_;

        Dot hold_pos_;
        Dot prev_pos_;
};

#endif