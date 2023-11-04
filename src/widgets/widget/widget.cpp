#include "widget.h"
#include "../../graphic/graphic.h"


bool Widget::onMousePressed(const Vector& pos, const MouseKey key, Container<Transform> &stack_transform)
{
    Transform trf(layout_box_->getPosition(), scale_);

    stack_transform.pushBack(trf.applyPrev(stack_transform.getBack()));
    Transform last_trf = stack_transform.getBack();
    
    Dot new_coord = last_trf.applyTransform(pos);

    bool flag = CheckIn(new_coord);

    stack_transform.popBack();

    return flag;
}

//================================================================================

bool Widget::onMouseReleased(const Vector& pos, const MouseKey key, Container<Transform> &stack_transform)
{
    bool flag = false;

    //fprintf(stderr, "Widget: onMouseReleased\n");

    return flag;
}

//================================================================================

bool Widget::onMouseMoved(const Vector& pos, Container<Transform> &stack_transform)
{
    bool flag = false;

    //fprintf(stderr, "Widget: onMouseMove\n");

    return flag;
}

//================================================================================

bool Widget::onKeyboardPressed(const KeyboardKey key)
{
    fprintf(stderr, "Widget: mouse keyboard kye pressed\n");
    return false;
}

//================================================================================

bool Widget::onKeyboardReleased(const KeyboardKey key)
{
    fprintf(stderr, "Widget: mouse keyboard kye released\n");
    return false;
}

//================================================================================

bool Widget::onTick(const time_t delta_time)
{
    fprintf(stderr, "Widget: mouse keyboard kye released\n");
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

void Widget::onUpdate(const LayoutBox& parent_layout)
{
    fprintf(stderr, "Widget: onUpdate\n");
}

//================================================================================


bool Widget::CheckIn(const Dot &mouse_pos)
{
    Vector size = layout_box_->getSize();

    bool horizontal = (Eps < mouse_pos.x && size.x - Eps > mouse_pos.x);
    bool vertical   = (Eps < mouse_pos.y && size.y - Eps > mouse_pos.y);
   
    return horizontal & vertical;
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

LayoutBox&  Widget::getLayoutBox()
{
    return *layout_box_;
}

//================================================================================

const LayoutBox& Widget::getLayoutBox() const
{
    return *layout_box_;
}

//================================================================================

void Widget::setLayoutBox(const LayoutBox& layout_box)
{
    delete layout_box_;
    layout_box_ = layout_box.clone();
}

//================================================================================
// void WidgetContainer::draw(sf::RenderTarget &target, Container<Transform> &stack_transform)
// {
//     stack_transform.PushBack(transform_.applyRrev(stack_transform.GetBack()));

//     size_t size = widgets_.GetSize();
//     for (size_t it = 0; it < size; it++)
//         widgets_[it]->draw(target, stack_transform);

//     stack_transform.PopBack();

//     return;
// }


// //================================================================================

// bool WidgetContainer::onMouseMoved(const double x, const double y, Container<Transform> &stack_transform)
// {
//     stack_transform.PushBack(transform_.applyRrev(stack_transform.GetBack()));
    
//     size_t size = widgets_.GetSize();
//     bool flag = false;
//     for (size_t it = 0; it < size; it++)
//         flag |= widgets_[it]->onMouseMoved(x, y, stack_transform);

//     stack_transform.PopBack();

//     return flag;
// }

// //================================================================================

// bool WidgetContainer::onMousePressed(const double x, const double y, const MouseKey key, Container<Transform> &stack_transform)
// {
//     stack_transform.PushBack(transform_.applyRrev(stack_transform.GetBack()));
    
//     Transform last_trf = stack_transform.GetBack();
//     Dot new_coord = last_trf.applyTransform({x, y});
    
//     bool flag = CheckIn(new_coord);

//     if (flag)
//     {
//         size_t size = widgets_.GetSize();
    
//         for (size_t it = 0; it < size; it++)
//             flag |= widgets_[it]->onMousePressed(x, y, key, stack_transform);
//     }
    
//     stack_transform.PopBack();

//     return flag;
// }

// //================================================================================

// bool WidgetContainer::onMouseReleased(const double x, const double y, const MouseKey key, Container<Transform> &stack_transform)
// {
//     stack_transform.PushBack(transform_.applyRrev(stack_transform.GetBack()));

//     size_t size = widgets_.GetSize();
//     bool flag = false;
//     for (size_t it = 0; it < size; it++)
//         flag |= widgets_[it]->onMouseReleased(x, y, key, stack_transform);

//     stack_transform.PopBack();

//     return false;
// }

// //================================================================================

// bool WidgetContainer::onKeyboardPressed(const KeyboardKey key)
// {
//     size_t size = widgets_.GetSize();
//     for (size_t it = 0; it < size; it++)
//     {
//         if (widgets_[it]->onKeyboardPressed(key))
//             return true;
//     }

//     return false;
// }

// //================================================================================

// bool WidgetContainer::onKeyboardReleased(const KeyboardKey key)
// {
//     size_t size = widgets_.GetSize();
//     for (size_t it = 0; it < size; it++)
//     {
//         if (widgets_[it]->onKeyboardReleased(key))
//             return true;
//     }

//     return false;
// }

// //================================================================================

// void WidgetContainer::onTick(const time_t delta_time)
// {
//     printf("WidgetContainer: mouse keyboard kye released\n");
//     return;
// }

// //================================================================================

// void WidgetContainer::AddWidget(Widget *ptr)
// {
//     widgets_.PushBack(ptr);
// }

// //================================================================================

// void WidgetContainer::SetFocus(bool value)
// {
//     size_t size = widgets_.GetSize();
//     for (size_t it = 0; it < size; it++)
//         widgets_[it]->SetFocus(value);
// }
