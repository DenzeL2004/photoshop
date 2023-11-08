#include "widget.h"
#include "../../graphic/graphic.h"


bool Widget::onMousePressed(const Vector &pos, const MouseKey key, Container<Transform> &stack_transform)
{
    return false;
}

//================================================================================

bool Widget::onMouseReleased(const Vector &pos, const MouseKey key, Container<Transform> &stack_transform)
{
    return false;
}

//================================================================================

bool Widget::onMouseMoved(const Vector &pos, Container<Transform> &stack_transform)
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

    stack_transform.pushBack(trf.applyPrev(stack_transform.getBack()));
    Transform last_trf = stack_transform.getBack();

    sf::Vector2f pos = last_trf.rollbackTransform(Dot(0, 0));
    
    Vector abs_pos((double)pos.x, (double)pos.y);
    double abs_width  = last_trf.scale.x * layout_box_->getSize().x;
    double abs_height = last_trf.scale.y * layout_box_->getSize().y;

    drawRectangle(target, abs_pos, Dot(abs_pos.x + abs_width, abs_pos.y + abs_height), Debug_color);

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
    Vector size = layout_box_->getSize();

    bool horizontal = (Eps < local_pos.x && size.x - Eps > local_pos.x);
    bool vertical   = (Eps < local_pos.y && size.y - Eps > local_pos.y);
   
    return horizontal  &vertical;
}

//================================================================================