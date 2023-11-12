#include "widget.h"
#include "../../graphic/graphic.h"


bool Widget::onMousePressed(const Vec2d &pos, const MouseKey key, Container<Transform> &stack_transform)
{
    return false;
}

//================================================================================

bool Widget::onMouseReleased(const Vec2d &pos, const MouseKey key, Container<Transform> &stack_transform)
{
    return false;
}

//================================================================================

bool Widget::onMouseMoved(const Vec2d &pos, Container<Transform> &stack_transform)
{
    return false;
}

//================================================================================

bool Widget::onKeyboardPressed(const KeyboardKey key)
{
    return false;
}

//================================================================================

bool Widget::onKeyboardReleased(const KeyboardKey key)
{
    return false;
}

//================================================================================

bool Widget::onTick(const float delta_time)
{
    return false;
}

//================================================================================

void Widget::draw(sf::RenderTarget &target, Container<Transform> &stack_transform)
{
    Transform trf(layout_box_->getPosition(), scale_);

    stack_transform.pushBack(trf.combine(stack_transform.getBack()));
    Transform last_trf = stack_transform.getBack();

    Vec2d pos = last_trf.restore(Dot(0, 0));
    
    Vec2d size = last_trf.getScale() * getLayoutBox().getSize();

    drawRectangle(target, pos, Dot(pos.x + size.x, pos.y + size.y), Debug_color);

    stack_transform.popBack();
}

//================================================================================

void Widget::onUpdate(const LayoutBox &parent_layout)
{
    layout_box_->onParentUpdate(parent_layout);
}

//================================================================================

bool Widget::getFocus() const 
{
    return focused_;
}

//================================================================================

void Widget::setFocus(bool value)
{
    focused_ = value;
}

//================================================================================

LayoutBox& Widget::getLayoutBox()
{
    return *layout_box_;
}

//================================================================================

const LayoutBox& Widget::getLayoutBox() const
{
    return *layout_box_;
}

//================================================================================

void Widget::setLayoutBox(const LayoutBox &layout_box)
{
    delete layout_box_;
    layout_box_ = layout_box.clone();
}

bool Widget::checkIn(const Dot &local_pos)
{
    Vec2d size = layout_box_->getSize();

    bool horizontal = (Eps < local_pos.x && size.x - Eps > local_pos.x);
    bool vertical   = (Eps < local_pos.y && size.y - Eps > local_pos.y);
   
    return horizontal  &vertical;
}

//================================================================================