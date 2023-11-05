#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "../widget/widget.h"

class Window : public Widget
{
    public:

        Window( const char *path_texture,
                const Vector& size, const Vector& parent_size,
                const Vector& pos, const Vector& origin = Vector(0.0, 0.0), 
                const Vector& scale = Vector(1.0, 1.0));
                

        ~Window()
        {
            delete layout_box_;
        }
        
        virtual void draw               (sf::RenderTarget &target, Container<Transform> &stack_transform);  

    private:

        void getDrawFormat(sf::VertexArray &vertex_array, const Transform &transform) const;
        
        LayoutBox* layout_box_;

        Vector origin_;
        Vector scale_; 

        bool focused_;

        sf::Texture texture_;        
};



#endif