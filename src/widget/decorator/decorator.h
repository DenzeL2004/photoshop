#ifndef _DECORATOR_H_
#define _DECORATOR_H_

#include "../widget.h"
#include "../button/button.h"

enum Decorator_State
{
    DEFAULT, 
    HOLD,
};

class Decorator: public Widget
{
    public:

        Decorator(){}
        ~Decorator(){}

        virtual bool OnMousePressed     (const int x, const int y, const MouseKey key, Container<Transform> &stack_transform) = 0;
        virtual bool OnMouseMoved       (const int x, const int y, Container<Transform> &stack_transform) = 0;
        virtual bool OnMouseReleased    (const int x, const int y, const MouseKey key, Container<Transform> &stack_transform) = 0;

        virtual bool OnKeyboardPressed  (const KeyboardKey) = 0;
        virtual bool OnKeyboardReleased (const KeyboardKey) = 0;

        virtual void Draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform) const = 0;  

        virtual void PassTime           (const time_t delta_time) = 0;

        void Move       (const Dot &offset);

        bool CheckIn    (const Dot &mouse_pos) const;

        double GetWidth()  const {return width_;}
        double GetHieght() const {return hieght_;}

    protected:

        void GetNewSize(sf::VertexArray &vertex_array, const Transform &transform) const;

        Transform transform_;
        double width_, hieght_;
        
        sf::Texture background_;
        const Widget *decarable_;

        Decorator_State state_;
};

//=================================================================================================

struct Title
{
    Title():
    msg_(""),  len_msg_(0), color_(sf::Color::Black){}

    Title(const char *msg, const sf::Color &color):
    msg_(msg), len_msg_(strlen(msg)), color_(color){}

    ~Title(){} 

    Title(const Title &other) = default;

    virtual Title& operator= (const Title &other) = default;

    const char* msg_;
    size_t len_msg_;
    const sf::Color color_;

};

class Border: public Decorator
{

    public:
        Border  (const char *path_texture, Button* close_button,
                 const Title &title, Widget *decarable,
                 const Dot offset, const Vector scale);

        virtual ~Border(){}

        virtual bool OnMousePressed     (const int x, const int y, const MouseKey key, Container<Transform> &stack_transform);
        virtual bool OnMouseMoved       (const int x, const int y, Container<Transform> &stack_transform);
        virtual bool OnMouseReleased    (const int x, const int y, const MouseKey key, Container<Transform> &stack_transform);

        virtual bool OnKeyboardPressed  (const KeyboardKey);
        virtual bool OnKeyboardReleased (const KeyboardKey);

        virtual void Draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform) const override;  

        virtual void PassTime           (const time_t delta_time);
        
        Transform GetTransform() const {return transform_;}

    private:
        void DrawTitle(sf::RenderTarget &target, const Transform &border_trf) const;
       
        Transform transform_;
        double width_, hieght_;
        
        sf::Texture background_;

        Button* close_button_;
        const Title title_;

        Widget *decarable_;

        Decorator_State state_;
        Dot hold_pos_;
};

#endif