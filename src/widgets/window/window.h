#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "../widget/widget.h"

class Window : public Widget
{
    public:

        Window( const char *path_texture,
                const Vec2d &size, const Vec2d &pos, 
                const Widget *parent, const Vec2d &parent_size = Vec2d(1.0, 1.0), 
                const Vec2d &origin = Vec2d(0.0, 0.0), const Vec2d &scale = Vec2d(1.0, 1.0));
                

        Window(const Window &other) = delete;
        Window& operator= (const Window &other) = delete;

        virtual ~Window(){}
        
        virtual void draw               (sf::RenderTarget &target, Container<Transform> &stack_transform);  

    protected:
        void getDrawFormat(sf::VertexArray &vertex_array, Transform &transform) const;
        sf::Texture texture_; 

    private:
               
};



#endif