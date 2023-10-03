#include "widget.h"

//=======================================================================================
Transform StackTransform::GetTransformation () const
{
    return data_[data_.GetSize() - 1];
}

size_t StackTransform::GetSize () const
{
    return data_.GetSize();
}

//=======================================================================================

void StackTransform::AddTransform (const Transform &transform)
{
    if (data_.GetSize() == 0)
    {
        data_.PushBack(transform);
        return;
    }

    Transform tmp = this->GetTransformation();
    
    tmp.pos_= Dot(transform.pos_.GetX() * tmp.scale_x_, 
                  transform.pos_.GetY() * tmp.scale_y_);

    tmp.scale_x_ *= transform.scale_x_;
    tmp.scale_y_ *= transform.scale_y_;

    data_.PushBack(tmp);

    return;
}

void StackTransform::EraseTransform ()
{
    data_.PopBack();
    return;
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
