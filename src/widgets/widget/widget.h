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

enum WidgetErr
{
    LOAD_TEXTURE_ERR,
};


bool checkIn(const Dot &mouse_pos, const Vector &size);

class Widget
{
    public:
        Widget( const Vector &size, const Vector &pos, 
                const Widget* parent, const Vector &parent_size = Vector(1.0, 1.0), 
                const Vector &origin = Vector(0.0, 0.0), const Vector &scale = Vector(1.0, 1.0)):
                parent_(parent),
                layout_box_(new BaseLayoutBox(pos, size, (parent != nullptr) ? parent->getLayoutBox().getSize() : parent_size, true, false)),
                origin_(origin), scale_(scale), focused_(false){}

        ~Widget()
        {
            delete layout_box_;
        }

        Widget& operator=(const Widget&) = delete;

        virtual bool onMousePressed     (const Vector &pos, const MouseKey key, Container<Transform> &stack_transform);
        virtual bool onMouseMoved       (const Vector &pos, Container<Transform> &stack_transform);
        virtual bool onMouseReleased    (const Vector &pos, const MouseKey key, Container<Transform> &stack_transform);

        virtual bool onKeyboardPressed  (const KeyboardKey);
        virtual bool onKeyboardReleased (const KeyboardKey);

        virtual bool onTick             (const time_t delta_time);

        virtual void draw               (sf::RenderTarget &target, Container<Transform> &stack_transform);  

        virtual void onUpdate           (const LayoutBox &parent_layout);

                bool getFocus() const;     
        virtual void setFocus(const bool flag);

        LayoutBox&         getLayoutBox();
        const LayoutBox&   getLayoutBox() const;
        void                setLayoutBox(const LayoutBox &layout_box);

    protected:
        const Widget *parent_;

        Vector origin_;
        Vector scale_; 

        bool focused_;

    private:
        LayoutBox* layout_box_;
        
        
};

class WidgetContainer: public Widget
{

    public:
        WidgetContainer(const Vector &size, const Vector &pos, 
                        const Widget* parent, const Vector &parent_size = Vector(1.0, 1.0), 
                        const Vector &origin = Vector(0.0, 0.0), const Vector &scale = Vector(1.0, 1.0)):
                        Widget(size, pos, parent, (parent != nullptr) ? parent->getLayoutBox().getSize() : parent_size, origin, scale),
                        widgets_(){}


        ~WidgetContainer()
        {
            size_t size = widgets_.getSize();
            for (size_t it = 0; it < size; it++)
                delete widgets_[it];
        }

        virtual bool onMousePressed     (const Vector &pos, const MouseKey key, Container<Transform> &stack_transform);
        virtual bool onMouseMoved       (const Vector &pos, Container<Transform> &stack_transform);
        virtual bool onMouseReleased    (const Vector &pos, const MouseKey key, Container<Transform> &stack_transform); 

        virtual bool onKeyboardPressed  (const KeyboardKey);
        virtual bool onKeyboardReleased (const KeyboardKey);

        virtual void draw               (sf::RenderTarget &target, Container<Transform> &stack_transform); 

        virtual bool onTick             (const time_t delta_time);

        void addWidget                  (Widget *ptr);
        virtual void SetFocus           (bool value);
       
    private:

        Container<Widget*> widgets_;
};

#endif