#include "Clock.h"
#include "Impl/Graphic/Graphic.h"

#include <ctime>

void Clock::draw(plug::TransformStack& stack, plug::RenderTarget& target)
{
    //if (m_seconsd <= Eps) return;

    stack.enter(Transform(getLayoutBox().getPosition(), Default_scale));
    
    
    time_t now = time(0);
    tm *ltm = localtime(&now);

    plug::Vec2d pos = stack.apply(Vec2d(0, 0));
    plug::Vec2d scale = stack.top().getScale() * m_thickness;

    char time[9];

    time[0] = ((ltm->tm_hour) / 10) + '0';
    time[1] = ((ltm->tm_hour) % 10) + '0';
    time[2] = '.';
    time[3] = ((ltm->tm_min) / 10) + '0';
    time[4] = ((ltm->tm_min) % 10) + '0';
    time[5] = '.';
    time[6] = ((ltm->tm_sec) / 10) + '0';
    time[7] = ((ltm->tm_sec) % 10) + '0';
    time[8] = '\0';
    writeText(target, pos, time, m_thickness, m_color);

    stack.leave();
}

#include <iostream>

void Clock::onTick(const plug::TickEvent &event, plug::EHC &context)
{
    m_seconsd += event.delta_time;

    if (m_seconsd >= 0.5) m_seconsd = -0.5;
}