#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "../widget.h"
#include "../../vector/vector.h"

class Window : public Widget
{

    public:

        Window(const char *path_texture, const Dot left_up);
        ~Window(){};

        virtual bool OnMousePressed     (const MouseKey key);
        virtual bool OnMouseMoved       (const int x, const int y);
        virtual bool OnMouseReleased    (const MouseKey key);

        virtual bool OnKeyboardPressed  (const KeyboardKey);
        virtual bool OnKeyboardReleased (const KeyboardKey);

        virtual void Draw(sf::RenderTarget &targert) const override;    

        virtual bool CheckIn(const Dot &mouse_pos);

        double GetWidth()  const {return width_;}
        double GetHieght() const {return hieght_;}

    private:
        
        Dot left_up_;

        double width_, hieght_;
        
        sf::Texture background_;

}; 

#endif