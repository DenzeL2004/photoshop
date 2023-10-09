#include "widget.h"

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


//=======================================================================================

// void WidgetManager::Draw(sf::RenderTarget &target) const
// {

//     int size = (int)widgets_.GetSize();

//     for (int it = size - 1; it >= 0; --it)
//         widgets_[it]->Draw(target);

//     return;
// }

// //=======================================================================================

// bool WidgetManager::OnMouseMoved(const int x, const int y)
// {
//     bool flag = false;

//     size_t size = widgets_.GetSize();
//     for (size_t it = 0; it < size; it++)
//         flag |= widgets_[it]->OnMouseMoved(x, y);

    
//     return flag;
// }

// //=======================================================================================

// bool WidgetManager::OnMousePressed(const MouseKey key)
// {
//     bool flag = false;

//     size_t size = widgets_.GetSize();
//     for (size_t it = 0; it < size; it++)
//         flag |= widgets_[it]->OnMousePressed(key);

    
//     return flag;
// }

// //=======================================================================================

// bool WidgetManager::OnMouseReleased(const MouseKey key)
// {
//     bool flag = false;

//     size_t size = widgets_.GetSize();
//     for (size_t it = 0; it < size; it++)
//         flag |= widgets_[it]->OnMouseReleased(key);

    
//     return flag;
// }

// //=======================================================================================

// bool WidgetManager::OnKeyboardPressed(const KeyboardKey key)
// {
//     bool flag = false;

//     size_t size = widgets_.GetSize();
//     for (size_t it = 0; it < size; it++)
//         flag |= widgets_[it]->OnKeyboardPressed(key);

    
//     return flag;
// }

// //=======================================================================================


// bool WidgetManager::OnKeyboardReleased(const KeyboardKey key)
// {
//     bool flag = false;

//     size_t size = widgets_.GetSize();
//     for (size_t it = 0; it < size; it++)
//         flag |= widgets_[it]->OnKeyboardReleased(key);

    
//     return flag;
// }
