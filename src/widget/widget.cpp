#include "widget.h"

//=======================================================================================

Transform Transform::ApplyPrev(const Transform &prev) const
{
    Dot new_pos = prev.offset_ + Vector(prev.scale_.GetX() * offset_.GetX(), prev.scale_.GetY() * offset_.GetY());
    Transform tmp(new_pos, Vector(scale_.GetX() * prev.scale_.GetX(), scale_.GetY() * prev.scale_.GetY()));

    return tmp;
}

Vector Transform::ApplyTransform(const Dot &pos) const
{
    Dot tmp = pos - offset_;
    Dot res(tmp.GetX() / scale_.GetX(), tmp.GetY() / scale_.GetY());

    return res;
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
