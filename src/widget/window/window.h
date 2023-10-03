#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "../widget.h"
#include "../../vector/vector.h"

#include "../../container/container.h"

class Window : public Widget
{

    public:

        Window(const char *path_texture, const Dot left_up, 
               const double scale_x, const double scale_y);
        ~Window(){};

        virtual bool OnMousePressed     (const MouseKey key, StackTransform &stack_transform);
        virtual bool OnMouseMoved       (const int x, const int y, StackTransform &stack_transform);
        virtual bool OnMouseReleased    (const MouseKey key, StackTransform &stack_transform);

        virtual bool OnKeyboardPressed  (const KeyboardKey);
        virtual bool OnKeyboardReleased (const KeyboardKey);

        virtual void Draw(sf::RenderTarget &targert, StackTransform &stack_transform) const override;    

        void SetPos (const Dot &new_left_up);

        bool CheckIn(const Dot &mouse_pos);

        double GetWidth()  const {return width_;}
        double GetHieght() const {return hieght_;}

    private:
        
        Dot left_up_;

        double scale_x_, scale_y_;

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