#ifndef _APP_H_
#define _APP_H_

#include "Plug/Math.h"
#include "Impl/Util/Sfml.h"

#include "Impl/RenderTarget/SfmlRenderTarget/RenderTarget.h"
#include "Impl/Graphic/Graphic.h"

#include "Impl/TransformStack/TransformStack.h"

#include "Impl/LayoutBox/BaseLayoutBox/BaseLayoutBox.h"
#include "Impl/Widget/Widget.h"

#include "Impl/Widget/Window/Window.h"
#include "Impl/Widget/Frame/Frame.h"
#include "Impl/Widget/Button/Button.h"

#include "Impl/Canvas/Canvas.h"

#include "Impl/Widget/CanvasManager/CanvasManager.h"

#include "Impl/Tool/ColorPalette/ColorPalette.h"

#include "Impl/Tool/FilterPalette/FilterPalette.h"

#include "AppConfig.h"

class AppWidget : public Widget
{
    public:

        AppWidget();

        virtual ~AppWidget()
        {
            size_t cnt = m_widgets.getSize();
            for (size_t it = 0; it < cnt; it++)
                delete m_widgets[it];
        }

        virtual void draw(plug::TransformStack &stack, plug::RenderTarget &target);

        virtual void onParentUpdate(const plug::LayoutBox &parent_box);

        void addWidget(Widget* widget);

        void onEvent(const plug::Event &event, plug::EHC &context);

    protected:

        virtual void onTick             (const plug::TickEvent &event, plug::EHC &context);

        virtual void onMouseMove        (const plug::MouseMoveEvent &event, plug::EHC &context);
        virtual void onMousePressed     (const plug::MousePressedEvent &event, plug::EHC &context);
        virtual void onMouseReleased    (const plug::MouseReleasedEvent &event, plug::EHC &context);

        virtual void onKeyboardPressed  (const plug::KeyboardPressedEvent &event, plug::EHC &context);
        virtual void onKeyboardReleased (const plug::KeyboardReleasedEvent &event, plug::EHC &context);

    private:

        Container<plug::Widget*> m_widgets; 
        
        FilterPalette m_filter_palette;
        ColorPalette  m_color_palette;


};


void useApp();

#endif