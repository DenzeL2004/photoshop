#ifndef _TEXT_BOX_H_
#define _TEXT_BOX_H_

#include <cstring>

#include "Impl/Widget/Widget.h"
#include "Impl/Util/Sfml.h"
#include "Impl/Graphic/Graphic.h"

class TextBox : public Widget
{
    public:
        TextBox(    const size_t limit_cnt_symbols, const size_t thicknesses,
                    const plug::LayoutBox &box):
                Widget(box),
                m_thicknesses(thicknesses), m_limit_cnt_symbols(limit_cnt_symbols), m_color(plug::Color(0, 0, 0)),
                m_cnt_symbols(0), m_acume_time(0), 
                m_cursor_pos_x(0), m_cursor_pos_y(0),
                m_buf(limit_cnt_symbols, '\0'){}

        virtual ~TextBox(){}


        TextBox(const TextBox &other) = delete;
        TextBox& operator= (const TextBox &other) = delete;

        

        virtual void draw(plug::TransformStack &stack, plug::RenderTarget &target);

        void clear(void);
        void setColor(plug::Color color) { m_color = color; }

        const std::string& getString(void) const {return m_buf;}

    protected:

        virtual void onTick             (const plug::TickEvent &event, plug::EHC &context);
        
        virtual void onMousePressed     (const plug::MousePressedEvent &event, plug::EHC &context);
    
        virtual void onKeyboardPressed  (const plug::KeyboardPressedEvent &event, plug::EHC &context);
    
    private:
        size_t m_thicknesses;
        
        size_t m_limit_cnt_symbols;
        plug::Color m_color;
        
        size_t m_cnt_symbols;

        float m_acume_time;

        size_t m_cursor_pos_x;
        size_t m_cursor_pos_y;

        std::string m_buf;
};

#endif