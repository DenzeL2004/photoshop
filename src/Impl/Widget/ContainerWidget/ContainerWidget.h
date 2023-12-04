#ifndef _CONTAINER_WIDGET_H_
#define _CONTAINER_WIDGET_H_

#include "Impl/Widget/Widget.h"
#include "Container/Container.h"

class ContainerWidget: public Widget
{
    public:
        ContainerWidget(  const plug::LayoutBox &box):
                Widget(box),
                m_widgets(){}

        virtual ~ContainerWidget()
        {
            size_t size = m_widgets.getSize();
            for (size_t it = 0; it < size; it++)
            {
                delete m_widgets[it];
            }
        }

        virtual void draw(plug::TransformStack &stack, plug::RenderTarget &target);

        virtual void onParentUpdate(const plug::LayoutBox &parent_box);

        virtual void onEvent(const plug::Event &event, plug::EHC &context);

        void insertWidget(plug::Widget* widget);
        void eraseWidget();

        plug::Widget* getLastWidget();

        plug::Widget* getWidget(const size_t id);

    protected:

        Container<plug::Widget*> m_widgets;
};

#endif
