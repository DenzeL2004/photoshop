#include "ColorView.h"
#include "Impl/Graphic/Graphic.h"

void ColorView::draw(plug::TransformStack& stack, plug::RenderTarget& target)
{
    stack.enter(plug::Transform(getLayoutBox().getPosition(), Default_scale));
    
    plug::Transform trf = stack.top();
    
    plug::Vec2d size = trf.getScale() * getLayoutBox().getSize();
    plug::Vec2d pos  = trf.getOffset();

    plug::Color fg_color = m_color_palette.getFGColor();
    plug::Color bg_color = m_color_palette.getBGColor();

    drawRectangle(target, pos + size * 0.25, pos + size, bg_color);
    drawRectangle(target, pos, pos + size * 0.75, fg_color);

    stack.leave();
}

void ColorView::onMousePressed(const plug::MousePressedEvent &event, plug::EHC &context)
{
    if (context.stopped) return;

    context.stack.enter(plug::Transform(getLayoutBox().getPosition(), Default_scale));
    

    context.stopped = covers(context.stack, event.pos);

    if (context.stopped)
    {
        plug::Color fg_color = m_color_palette.getFGColor();
        plug::Color bg_color = m_color_palette.getBGColor();

        m_color_palette.setFGColor(bg_color);
        m_color_palette.setBGColor(fg_color);
    }

    context.stack.leave();
}