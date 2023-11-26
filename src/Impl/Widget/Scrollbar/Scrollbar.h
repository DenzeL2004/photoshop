#ifndef _SCROLLBAR_H_
#define _SCROLLBAR_H_

#include "Impl/Widget/Button/Button.h"
#include "Impl/Widget/CanvasView/CanvasView.h"

// class Scrollbar: public Widget
// {

//     public:
//         enum Type
//         {
//             HORIZONTAL,
//             VERTICAL,
//         };

//         Scrollbar(  CanvasView *canvas_view, const Type type,
//                     const plug::LayoutBox& box, 
//                     const plug::Vec2d &scale = Vec2d(1.0, 1.0),
//                     Button *top_button, Button *bottom_button, Button *center_button):
//                     Widget(box),
//                     m_top_button(top_button), m_bottom_button(bottom_button), m_center_button(center_button),
//                     m_canvas_view(canvas_view),
//                     m_type(type),
//                     m_prev_canvas_pos(0, 0),
//                     m_hold_pos(0, 0){}

//         virtual ~Scrollbar()
//         {
//             delete m_top_button;
//             delete m_bottom_button;
//             delete m_center_button;
//         }

//         virtual bool onMousePressed     (const Vec2d& pos, const MouseKey key, Container<Transform> &stack_transform);
//         virtual bool onMouseMoved       (const Vec2d& pos, Container<Transform> &stack_transform);
//         virtual bool onMouseReleased    (const Vec2d& pos, const MouseKey key, Container<Transform> &stack_transform);

//         virtual void draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform);  

//         virtual bool onKeyboardPressed  (const KeyboardKey);
//         virtual bool onKeyboardReleased (const KeyboardKey);

//         virtual void onUpdate           (const LayoutBox &parent_layout);

//         void addButtons(Button *top_button, Button *bottom_button, Button *center_button);

//     private:

//         void moveCenter();
//         void resizeCenter();
        
//         Button *m_top_button, *m_bottom_button, *m_center_button;
//         CanvasView *m_canvas_view;

//         plug::Vec2d m_hold_pos;
//         plug::Vec2d m_prev_canvas_pos;

//         plug::Vec2d m_scale;
        
//         Type m_type;
// };


#endif