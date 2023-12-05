#ifndef _SCROLLBAR_H_
#define _SCROLLBAR_H_

#include "Impl/Util/Sfml.h"

#include "Impl/Widget/Button/Button.h"
#include "Impl/Widget/CanvasView/CanvasView.h"
#include "Impl/LayoutBox/BaseLayoutBox/BaseLayoutBox.h"

class ScrollCanvas : public Action
{
    public:
        ScrollCanvas(const plug::Vec2d &offset, CanvasView &canvas_view): 
                m_offset(offset), m_canvas_view(canvas_view){};
        ~ScrollCanvas(){};

        void operator() ()
        {
            m_canvas_view.setCanvasPos(m_offset + m_canvas_view.getCanvasPos());
        }

        ScrollCanvas(const ScrollCanvas &other) = delete;
        virtual ScrollCanvas &operator= (const ScrollCanvas &other) = delete;

    private:
        plug::Vec2d m_offset;
        CanvasView &m_canvas_view;
};

class Scrollbar: public Widget
{
    public:
        enum Type
        {
            HORIZONTAL,
            VERTICAL,
        };

        Scrollbar(  CanvasView &canvas_view, const Type type,
                    const plug::LayoutBox& box, 
                    const char *top_released_texure, const char *top_covered_texure,
                    const char *btm_released_texure, const char *btm_covered_texure,
                    const char *ctr_released_texure, const char *ctr_covered_texure):
                    Widget(box),
                    m_top_button(nullptr), m_bottom_button(nullptr), m_center_button(nullptr),
                    m_canvas_view(canvas_view),
                    m_type(type),
                    m_prev_canvas_pos(0, 0),
                    m_hold_pos(0, 0),
                    m_update_center_button(true)
                {
                    
                    plug::Vec2d size = box.getSize();
                    double min_side = std::min(size.x, size.y);
                    plug::Vec2d buttons_size(min_side, min_side);

                    plug::Vec2d bottom_pos(0.0, 0.0);
                    plug::Vec2d center_pos(0.0, 0.0);
                    plug::Vec2d offset(0.0, 0.0);

                    if (type == Scrollbar::Type::HORIZONTAL)
                    {
                        center_pos.x = min_side;
                        bottom_pos.x = size.x - min_side;
                        offset.x = 10.0;
                    }

                    if (type == Scrollbar::Type::VERTICAL)
                    {
                        center_pos.y = min_side;
                        bottom_pos.y = size.y - min_side;
                        offset.y = 10.0;
                    }
                    
                    m_top_button = new Button(  getPlugTexture(top_released_texure), getPlugTexture(top_covered_texure),
                                                getPlugTexture(top_released_texure), getPlugTexture(top_covered_texure),
                                                BaseLayoutBox(Vec2d(0, 0), buttons_size, size, false, true),
                                                new ScrollCanvas(-1 * offset, canvas_view));

                    m_center_button = new Button(   getPlugTexture(ctr_released_texure), getPlugTexture(ctr_covered_texure),
                                                    getPlugTexture(ctr_released_texure), getPlugTexture(ctr_covered_texure),
                                                    BaseLayoutBox(center_pos, buttons_size, size, false, true),
                                                    nullptr);

                    m_bottom_button = new Button(   getPlugTexture(btm_released_texure), getPlugTexture(btm_covered_texure),
                                                    getPlugTexture(btm_released_texure), getPlugTexture(btm_covered_texure),
                                                    BaseLayoutBox(bottom_pos, buttons_size, size, false, true),
                                                    new ScrollCanvas(offset, canvas_view));

                }

        virtual ~Scrollbar()
        {
            delete m_top_button;
            delete m_bottom_button;
            delete m_center_button;
        }

        virtual void draw(plug::TransformStack &stack, plug::RenderTarget &target);

        virtual void onParentUpdate(const plug::LayoutBox &parent_box);

        Scrollbar(const Scrollbar &other) = delete;
        virtual Scrollbar &operator= (const Scrollbar &other) = delete;


    protected:
       
        virtual void onMouseMove        (const plug::MouseMoveEvent &event, plug::EHC &context);
        virtual void onMousePressed     (const plug::MousePressedEvent &event, plug::EHC &context);
        virtual void onMouseReleased    (const plug::MouseReleasedEvent &event, plug::EHC &context);

        virtual void onKeyboardPressed  (const plug::KeyboardPressedEvent &event, plug::EHC &context);
        
    private:

        void moveCenter(void);
        void resizeCenter(void);
        
        Button *m_top_button, *m_bottom_button, *m_center_button;
        CanvasView &m_canvas_view;

        plug::Vec2d m_hold_pos;
        plug::Vec2d m_prev_canvas_pos;

        bool m_update_center_button;
        
        Type m_type;
};

#endif