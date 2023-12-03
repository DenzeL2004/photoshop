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
                    const BaseLayoutBoc &box):
                Widget(box),
                m_thicknesses(thicknesses), m_limit_cnt_symbols(limit_cnt_symbols), m_color(plug::Color(0, 0, 0))
                m_cnt_symbols(0), m_acume_time(0), m_cursor_pos(plug::Vec2d(0, 0)), buf(limit_cnt_symbols){}

        virtual ~TextBox(){}


        TextBox(const TextBox &other) = delete;
        TextBox& operator= (const TextBox &other) = delete;

        

        virtual void draw(plug::TransformStack &stack, plug::RenderTarget &target);

        void clear(void);
        void setColor(plug::Color color) { m_color = color; }

        const std::string& getString(void) const {return buf;}

    protected:

        virtual void onTick             (const plug::TickEvent &event, plug::EHC &context);
        
        virtual void onMousePressed     (const plug::MousePressedEvent &event,plug::EHC &context);
    
        virtual void onKeyboardPressed  (const plug::KeyboardPressedEvent &event, plug::EHC &context);
    
    private:
        size_t m_thicknesses;
        
        size_t m_cnt_symbols;
        size_t m_limit_cnt_symbols;
        std::string buf;

        plug::Vec2d m_cursor_pos;

        plug::Color m_color;

        float m_acume_time;
};

#endif