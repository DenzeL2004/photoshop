#include "widget.h"

static MouseKey     GetMouseKey     (sf::Event &event);

//=======================================================================================

Transform Transform::ApplyPrev(const Transform &prev) const
{
    Dot new_pos = prev.offset + Vector(prev.scale.x * offset.x, prev.scale.y * offset.y);
    Transform res(new_pos, {scale.x * prev.scale.x, scale.y * prev.scale.y});

    return res;
}

Dot Transform::ApplyTransform(const Dot &pos) const
{
    Dot res = pos - offset;
    
    res.x /= scale.x;
    res.y /= scale.y;

    return res;
}

sf::Vector2f Transform::RollbackTransform (const Vector &vec) const
{
    return sf::Vector2f(vec.x * scale.x + offset.x, vec.y * scale.y + offset.y);
}

//================================================================================

void EventAdapter(Widget &widget, int mouse_x, int mouse_y, sf::Event &event, Container<Transform> &stack_transform)
{
    if (event.type == sf::Event::MouseMoved)
    {
        widget.OnMouseMoved((double)mouse_x, (double)mouse_y, stack_transform);
    }
    else
    {
        if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased)
        {
            
            MouseKey mouse_key = GetMouseKey(event);
            if (event.type == sf::Event::MouseButtonPressed)
                widget.OnMousePressed((double)mouse_x, (double)mouse_y, mouse_key, stack_transform);
            
            if (event.type == sf::Event::MouseButtonReleased)
                widget.OnMouseReleased((double)mouse_x, (double)mouse_y, mouse_key, stack_transform);
        }
    }

    return;
}

static MouseKey GetMouseKey(sf::Event &event)
{
    switch (event.mouseButton.button)
    {
        case sf::Mouse::Left:
            return MouseKey::Left;
        
        case sf::Mouse::Right:
            return MouseKey::Right;

        default:
            break;
    }

    return MouseKey::Nothing;
}


bool CheckIn(const Dot &mouse_pos)
{
    bool horizontal = (Eps < mouse_pos.x && 1 - Eps > mouse_pos.x);
    bool vertical   = (Eps < mouse_pos.y && 1 - Eps > mouse_pos.y);
   
    return horizontal & vertical;
}

//================================================================================
void WidgetContainer::Draw(sf::RenderTarget &target, Container<Transform> &stack_transform)
{
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));

    size_t size = widgets_.GetSize();
    for (size_t it = 0; it < size; it++)
        widgets_[it]->Draw(target, stack_transform);

    stack_transform.PopBack();

    return;
}


//================================================================================

bool WidgetContainer::OnMouseMoved(const double x, const double y, Container<Transform> &stack_transform)
{
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    
    size_t size = widgets_.GetSize();
    bool flag = false;
    for (size_t it = 0; it < size; it++)
        flag |= widgets_[it]->OnMouseMoved(x, y, stack_transform);

    stack_transform.PopBack();

    return flag;
}

//================================================================================

bool WidgetContainer::OnMousePressed(const double x, const double y, const MouseKey key, Container<Transform> &stack_transform)
{
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    
    size_t size = widgets_.GetSize();
    bool flag = false;
    for (size_t it = 0; it < size; it++)
        flag |= widgets_[it]->OnMousePressed(x, y, key, stack_transform);

    stack_transform.PopBack();

    return flag;
}

//================================================================================

bool WidgetContainer::OnMouseReleased(const double x, const double y, const MouseKey key, Container<Transform> &stack_transform)
{
    size_t size = widgets_.GetSize();
    bool flag = false;
    for (size_t it = 0; it < size; it++)
        flag |= widgets_[it]->OnMouseReleased(x, y, key, stack_transform);

    return false;
}

//================================================================================

bool WidgetContainer::OnKeyboardPressed(const KeyboardKey key)
{
    printf("WidgetContainer: mouse keyboard kye pressed\n");
    return false;
}

//================================================================================

bool WidgetContainer::OnKeyboardReleased(const KeyboardKey key)
{
    printf("WidgetContainer: mouse keyboard kye released\n");
    return false;
}

//================================================================================

void WidgetContainer::PassTime(const time_t delta_time)
{
    printf("WidgetContainer: mouse keyboard kye released\n");
    return;
}

//================================================================================

void WidgetContainer::AddWidget(Widget *ptr)
{
    widgets_.PushBack(ptr);
}
