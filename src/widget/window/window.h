#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "../widget.h"
#include "../../vector/vector.h"

#include "../../container/container.h"

class Window : public Widget
{

    public:

        Window  (const char *path_texture, const Dot offset, 
                 const double scale_x, const double scale_y);
        ~Window(){};

        virtual bool OnMousePressed     (const MouseKey key, Container<Transform> &stack_transform);
        virtual bool OnMouseMoved       (const int x, const int y, Container<Transform> &stack_transform);
        virtual bool OnMouseReleased    (const MouseKey key, Container<Transform> &stack_transform);

        virtual bool OnKeyboardPressed  (const KeyboardKey);
        virtual bool OnKeyboardReleased (const KeyboardKey);

        virtual void Draw(sf::RenderTarget &targert, Container<Transform> &stack_transform) const override;    

        void SetOffset (const Dot &offset);

        bool CheckIn(const Dot &mouse_pos);

        double GetWidth()  const {return width_;}
        double GetHieght() const {return hieght_;}

    private:
       
        Transform transform_;

        double width_, hieght_;
        
        sf::Texture background_;

};

// class ContainerWindow : public Window
// {

//     public:

//         ContainerWindow(const char *path_texture, const Dot left_up):
//                                  Window(path_texture, left_up), window_manager_(){}
//         ~ContainerWindow(){};

//         virtual bool OnMousePressed     (const MouseKey key);
//         virtual bool OnMouseMoved       (const int x, const int y);
//         virtual bool OnMouseReleased    (const MouseKey key);

//         virtual bool OnKeyboardPressed  (const KeyboardKey);
//         virtual bool OnKeyboardReleased (const KeyboardKey);

//         virtual void Draw(sf::RenderTarget &targert) const override;    

//     private:
//         WidgetManager window_manager_;
               

// }; 

#endif