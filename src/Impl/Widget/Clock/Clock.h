#ifndef _CLOCK_H_
#define _CLOCK_H_

#include "Impl/Widget/Widget.h"

class Clock : public Widget
{
    public:

        Clock(  const plug::Color color, const double thickness,
                const plug::LayoutBox& box):
                Widget(box),
                m_seconsd(0.0),
                m_color(color),
                m_thickness(thickness){}
                
        Clock(const Clock &other) = delete;
        Clock& operator= (const Clock &other) = delete;

        virtual ~Clock(){}
        
        virtual void draw (plug::TransformStack& stack, plug::RenderTarget& target);  

    protected:

        void onTick(const plug::TickEvent &event, plug::EHC &context);
        
    private:

        double m_seconsd;
        plug::Color m_color;
        double m_thickness;

};


#endif