#ifndef _DECORATOR_H_
#define _DECORATOR_H_

#include "../widget.h"
#include "../button/button.h"

class Decorator: public Widget
{
    public:

        Decorator(){}
        ~Decorator(){}

        virtual bool OnMousePressed     (const MouseKey key, Container<Transform> &stack_transform) = 0;
        virtual bool OnMouseMoved       (const int x, const int y, Container<Transform> &stack_transform) = 0;
        virtual bool OnMouseReleased    (const MouseKey key, Container<Transform> &stack_transform) = 0;

        virtual bool OnKeyboardPressed  (const KeyboardKey) = 0;
        virtual bool OnKeyboardReleased (const KeyboardKey) = 0;

        virtual void Draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform) const = 0;  

        virtual void PassTime           (const time_t delta_time) = 0;

        void SetOffset  (const Dot &offset);

        bool CheckIn    (const Dot &mouse_pos) const;

        double GetWidth()  const {return width_;}
        double GetHieght() const {return hieght_;}

    private:
       
        Transform transform_;

        double width_, hieght_;
        
        sf::Texture background_;

        const Widget *decarable_;

};


//=================================================================================================
struct Title
{
    Title():
    msg_(nullptr),  color_(sf::Color::Black){}

    Title(const char *msg, const sf::Color &color):
    msg_(msg),  color_(color){}

    ~Title(){} 

    Title(const Title &other) = default;

    virtual Title& operator= (const Title &other) = default;

    const char* msg_ = nullptr;
    const sf::Color color_ = sf::Color::Black;

};

class Border: public Decorator
{

    public:
        Border  (const char *path_texture, const Button* close_button,
                 const Title &title, const Widget *decarable,
                 const Dot offset, const Vector scale);

        virtual ~Border(){}

        virtual bool OnMousePressed     (const MouseKey key, Container<Transform> &stack_transform);
        virtual bool OnMouseMoved       (const int x, const int y, Container<Transform> &stack_transform);
        virtual bool OnMouseReleased    (const MouseKey key, Container<Transform> &stack_transform);

        virtual bool OnKeyboardPressed  (const KeyboardKey);
        virtual bool OnKeyboardReleased (const KeyboardKey);

        virtual void Draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform) const override;  

        virtual void PassTime           (const time_t delta_time);

    private:
        Dot GetScale(const Transform &transform) const;

        Transform transform_;
        double width_, hieght_;
        
        sf::Texture background_;

        const Button* close_button_;
        const Title title_;

        const Widget *decarable_;
};

#endif