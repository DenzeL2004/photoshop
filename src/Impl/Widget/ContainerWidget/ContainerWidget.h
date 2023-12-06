#ifndef _CONTAINER_WIDGET_H_
#define _CONTAINER_WIDGET_H_

#include "Container/Container.h"

#include "Impl/Widget/Widget.h"
#include "Impl/Widget/Button/Button.h"

class ContainerWidget: public Widget
{
    public:
        ContainerWidget(const plug::LayoutBox &box):
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

        ContainerWidget(const ContainerWidget &other) = delete;
        virtual ContainerWidget &operator= (const ContainerWidget &other) = delete;

        virtual void draw(plug::TransformStack &stack, plug::RenderTarget &target);

        virtual void onParentUpdate(const plug::LayoutBox &parent_box);

        virtual void onEvent(const plug::Event &event, plug::EHC &context);

        virtual void insertWidget(plug::Widget* widget);
        virtual void eraseWidget();

        virtual plug::Widget* getLastWidget();

        virtual plug::Widget* getWidget(const size_t id);

    protected:

        Container<plug::Widget*> m_widgets;
};

class EraseLastWidget : public Action
{
    public:
        EraseLastWidget(ContainerWidget &container): 
                        m_container(container){}
        ~EraseLastWidget(){};

        void operator() ()
        {
            m_container.eraseWidget();
        }        

        EraseLastWidget(const EraseLastWidget &other) = delete;
        EraseLastWidget &operator= (const EraseLastWidget &other) = delete;

    private:
        ContainerWidget &m_container; 
};

#endif
