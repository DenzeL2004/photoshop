#ifndef _WIDGET_H_
#define _WIDGET_H_

#include "../../generals_func/generals.h"
#include "../../log_info/log_errors.h"

#include "../../container/container.h"

#include "../../graphic/graphic.h"

#include "transform/transform.h"
#include "layoutbox/layoutbox.h"

#include "../event/event.h"

const sf::Color Debug_color = sf::Color(255, 20, 147);

const double Default_width  = 720.0;
const double Default_height = 480.0;

using KeyMask = uint32_t;

enum WidgetErr
{
    LOAD_TEXTURE_ERR,
};

class Widget
{
    public:
        Widget( const Vec2d &size, const Vec2d &pos, 
                const Widget* parent, const Vec2d &parent_size = Vec2d(1.0, 1.0), 
                const Vec2d &origin = Vec2d(0.0, 0.0), const Vec2d &scale = Vec2d(1.0, 1.0)):
                parent_(parent),
                layout_box_(new BaseLayoutBox(pos, size, (parent != nullptr) ? parent->getLayoutBox().getSize() : parent_size, true, false)),
                origin_(origin), scale_(scale), focused_(false){}

        ~Widget()
        {
            delete layout_box_;
        }

        Widget(const Widget &other) = delete;
        Widget& operator=(const Widget&) = delete;

        virtual bool onMousePressed     (const Vec2d &pos, const MouseKey key, Container<Transform> &stack_transform);
        virtual bool onMouseMoved       (const Vec2d &pos, Container<Transform> &stack_transform);
        virtual bool onMouseReleased    (const Vec2d &pos, const MouseKey key, Container<Transform> &stack_transform);

        virtual bool onKeyboardPressed  (const KeyboardKey);
        virtual bool onKeyboardReleased (const KeyboardKey);

        virtual bool onTick             (const float delta_time);

        virtual void draw               (sf::RenderTarget &target, Container<Transform> &stack_transform);  

        virtual void onUpdate           (const LayoutBox &parent_layout);

                bool getFocus() const;     
        virtual void setFocus(const bool flag);

        LayoutBox&         getLayoutBox();
        const LayoutBox&   getLayoutBox() const;
        void               setLayoutBox(const LayoutBox &layout_box);

    protected:
        virtual bool checkIn(const Dot &local_pos);

        const Widget *parent_;

        Vec2d origin_;
        Vec2d scale_; 

        bool focused_;

    private:
        LayoutBox* layout_box_;
        
        
};

#endif