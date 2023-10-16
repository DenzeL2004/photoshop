#ifndef _DECORATOR_H_
#define _DECORATOR_H_

#include "../widget.h"
#include "../button/button.h"

enum Decorator_State
{
    Default, 
    Hold,
};

static const Transform Left_Border    = Transform({0, 0.05}, {0.015, 1});
static const Transform Top_Border     = Transform({0, 0}, {1, 0.015});

static const Transform Right_Border   = Transform({0.982, 0.05}, {0.02, 1});
static const Transform Bottom_Border  = Transform({0, 0.975}, {1, 0.2});

static const Vector Scale_Limit = Vector(0.4, 0.4);


//=================================================================================================

struct Title
{
    Title():
    msg_(""),  len_msg_(0), color_(sf::Color::Black){}

    Title(const char *msg, const sf::Color &color):
    msg_(msg), len_msg_(strlen(msg)), color_(color){}

    ~Title(){} 

    Title(const Title &other) = default;

    Title& operator= (const Title &other) = default;

    const char* msg_;
    size_t len_msg_;
    const sf::Color color_;

};



class Frame: public Widget
{

    public:
        Frame  (const char *path_texture, Button* close_button,
                 const Title &title, Widget *decarable,
                 const Dot &offset, const Vector &scale);

        virtual ~Frame()
        {
            delete close_button_;
            delete decarable_;
        }

        virtual bool OnMousePressed     (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform);
        virtual bool OnMouseMoved       (const double x, const double y, Container<Transform> &stack_transform);
        virtual bool OnMouseReleased    (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform);

        virtual bool OnKeyboardPressed  (const KeyboardKey);
        virtual bool OnKeyboardReleased (const KeyboardKey);

        virtual void Draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform) override;  

        virtual void PassTime           (const time_t delta_time);
        
        Transform GetTransform() const {return transform_;}

    private:
        void GetNewSize (sf::VertexArray &vertex_array, const Transform &transform) const;

        void DrawTitle  (sf::RenderTarget &target, const Transform &border_trf) const;

        void Move       (const Dot &new_coord);
        
        uint8_t ClickOnBorder   (double x, double y, const Transform &Last_transform) const;
        void Scale              (const Dot &new_coord, uint8_t mask);

        Transform transform_;
        double width_, hieght_;
        
        sf::Texture background_;

        Button* close_button_;
        const Title title_;

        Widget *decarable_;

        Decorator_State state_;
        Dot hold_pos_;

        enum Borders
        {
            Left    = 1 << 1,
            Right   = 1 << 2,
            Top     = 1 << 3,
            Bottom  = 1 << 4,
        };

        Transform left_border_, top_border_, right_border_, bottom_border_;
};


class Scrollbar: public Widget
{

    public:
        Scrollbar  (Button *top_button, Button *bottom_button, Button *center_button, 
                    Widget *decarable, const Dot &offset, const Vector &scale);

        virtual ~Scrollbar()
        {
            delete top_button_;
            delete bottom_button_;
            delete center_button_;
        }

        virtual bool OnMousePressed     (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform);
        virtual bool OnMouseMoved       (const double x, const double y, Container<Transform> &stack_transform);
        virtual bool OnMouseReleased    (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform);

        virtual bool OnKeyboardPressed  (const KeyboardKey);
        virtual bool OnKeyboardReleased (const KeyboardKey);

        virtual void Draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform) override;  

        virtual void PassTime           (const time_t delta_time);

    private:

        void MoveCenter (const Dot &new_coord);

        Button *top_button_, *bottom_button_, *center_button_;
        Widget *decarable_;

        Transform transform_;
};


#endif