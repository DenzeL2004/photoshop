#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "../widget.h"
#include "../button/button.h"

#include "../../vector/vector.h"
#include "../../container/container.h"

class Window : public Widget
{

    public:
        Window  (const char *path_texture,
                 const Dot &offset, const Vector &scale);
        virtual ~Window(){}

        virtual bool OnMousePressed     (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform);
        virtual bool OnMouseMoved       (const double x, const double y, Container<Transform> &stack_transform);
        virtual bool OnMouseReleased    (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform);

        virtual bool OnKeyboardPressed  (const KeyboardKey);
        virtual bool OnKeyboardReleased (const KeyboardKey);

        virtual void Draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform) override;  

        virtual void PassTime           (const time_t delta_time);
        
    protected:
        void GetNewSize(sf::VertexArray &vertex_array, const Transform &transform) const;
       
        Transform transform_;

        double width_, hieght_;
        
        sf::Texture background_;

};

#endif