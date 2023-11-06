#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "../widget/widget.h"

class Window : public Widget
{
    public:

        Window( const char *path_texture,
                const Vector &size, const Vector &pos, 
                const Widget *parent, const Vector &parent_size, 
                const Vector &origin = Vector(0.0, 0.0), const Vector &scale = Vector(1.0, 1.0));
                

        Window(const Window &other) = delete;
        Window& operator= (const Window &other) = delete;

        virtual ~Window(){}
        
        virtual void draw               (sf::RenderTarget &target, Container<Transform> &stack_transform);  

    protected:
        void getDrawFormat(sf::VertexArray &vertex_array, const Transform &transform) const;
        sf::Texture texture_; 

    private:
               
};



#endif