#include "ContainerWidget.h"


void ContainerWidget::draw(plug::TransformStack &stack, plug::RenderTarget &target)
{   
    plug::Transform trf(getLayoutBox().getPosition(), Default_scale);
    stack.enter(trf);

    size_t cnt = m_widgets.getSize();
    for (size_t it = 0; it < cnt; it++)
    {
        m_widgets[it]->draw(stack, target);
    }

    stack.leave();
}

void ContainerWidget::onParentUpdate(const plug::LayoutBox &parent_box)
{
    plug::LayoutBox *layout_box =  &getLayoutBox();
    layout_box->onParentUpdate(parent_box);
    
    size_t size = m_widgets.getSize();
    for (size_t it = 0; it < size; it++)
    {
        m_widgets[it]->onParentUpdate(*layout_box);
    }
}

void ContainerWidget::onEvent(const plug::Event &event, plug::EHC &context)
{
    plug::Transform trf(getLayoutBox().getPosition(), Default_scale);    
    context.stack.enter(trf);

    int size = static_cast<int>(m_widgets.getSize());
    for (int it = size - 1; it >= 0; it--)
    {
        m_widgets[it]->onEvent(event, context);
    }

    context.stack.leave();
}

void ContainerWidget::insertWidget(plug::Widget* widget)
{
    m_widgets.pushBack(widget);
}

void ContainerWidget::eraseWidget()
{
    m_widgets.popBack();
}