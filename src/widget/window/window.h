#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "../widget.h"
#include "../../vector/vector.h"

#include "../../container/container.h"

class Window : public Widget
{

    public:

        Window  (const char *path_texture,
                 const Dot offset, const Vector scale);
        virtual ~Window(){}

        virtual bool OnMousePressed     (const int x, const int y, const MouseKey key, Container<Transform> &stack_transform);
        virtual bool OnMouseMoved       (const int x, const int y, Container<Transform> &stack_transform);
        virtual bool OnMouseReleased    (const int x, const int y, const MouseKey key, Container<Transform> &stack_transform);

        virtual bool OnKeyboardPressed  (const KeyboardKey);
        virtual bool OnKeyboardReleased (const KeyboardKey);

        virtual void Draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform) const override;  

        virtual void PassTime           (const time_t delta_time);

        void Move       (const Dot &offset);

        bool CheckIn    (const Dot &mouse_pos);

        double GetWidth()  const {return width_;}
        double GetHieght() const {return hieght_;}

        Transform GetTransform() const {return transform_;}

    protected:
        void GetNewSize(sf::VertexArray &vertex_array, const Transform &transform) const;
       
        Transform transform_;

        double width_, hieght_;
        
        sf::Texture background_;

};

class CanvaseManager : public Window
{

    public:

        CanvaseManager(const char *path_texture,
                        const Dot offset, const Vector scale):Window(path_texture, offset, scale), 
                        canvases_(), delte_canvase_(false){}
        ~CanvaseManager(){};

        virtual bool OnMousePressed     (const int x, const int y, const MouseKey key, Container<Transform> &stack_transform);
        virtual bool OnMouseMoved       (const int x, const int y, Container<Transform> &stack_transform);
        virtual bool OnMouseReleased    (const int x, const int y, const MouseKey key, Container<Transform> &stack_transform);

        virtual bool OnKeyboardPressed  (const KeyboardKey);
        virtual bool OnKeyboardReleased (const KeyboardKey);


        virtual void Draw               (sf::RenderTarget &target, Container<Transform> &stack_transform) const;

        //virtual void PassTime           (const time_t delta_time);

    private:
        Container<Widget*> canvases_;
        bool delte_canvase_;
               

}; 

#endif