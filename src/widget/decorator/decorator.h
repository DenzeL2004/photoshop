#ifndef _DECORATOR_H_
#define _DECORATOR_H_

#include "../widget.h"

class Decorator: public Widget
{


    public:

        Decorator(const char *path_texture, const Dot left_up,  Widget *widget);
        ~Decorator(){};

        virtual bool OnMousePressed     (const MouseKey key);
        virtual bool OnMouseMoved       (const int x, const int y);
        virtual bool OnMouseReleased    (const MouseKey key);

        virtual bool OnKeyboardPressed  (const KeyboardKey);
        virtual bool OnKeyboardReleased (const KeyboardKey);

        virtual void Draw   (sf::RenderTarget &targert) const;    

        void SetPos     (const Dot &new_left_up);

        bool CheckIn    (const Dot &mouse_pos);

        double GetWidth()  const {return width_;}
        double GetHieght() const {return hieght_;}

    private:
        
        Dot left_up_;

        double width_, hieght_;
        
        sf::Texture background_;

        Widget* widget_;


};


//=================================================================================================


class Border: public Widget
{

    public:

        Border(const char *path_texture, const Dot left_up, const Widget *widget);
        ~Border(){};

        virtual bool OnMousePressed     (const MouseKey key);
        virtual bool OnMouseMoved       (const int x, const int y);
        virtual bool OnMouseReleased    (const MouseKey key);

        virtual bool OnKeyboardPressed  (const KeyboardKey);
        virtual bool OnKeyboardReleased (const KeyboardKey);

        virtual void Draw(sf::RenderTarget &targert) const override;    

    private:
        
        Dot left_up_;

        double width_, hieght_;
        
        sf::Texture background_;

        const Widget* widget_;


};

#endif