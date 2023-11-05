#include "layoutbox.h"

BaseLayoutBox::BaseLayoutBox(const Vector& pos, 
                             const Vector& size, const Vector& parent_size, 
                             const bool resize_flag, const bool save_locals_flag):
                            pos_(pos), 
                            size_(size), parent_size_(parent_size), 
                            resizable_(resize_flag), save_locals_(save_locals_flag){}

Vector BaseLayoutBox::getPosition() const
{
    return pos_;
}

bool BaseLayoutBox::setPosition(const Vector& new_pos)
{
    pos_ = new_pos;

    return true;
}

Vector BaseLayoutBox::getSize() const
{
    return size_;
}

bool BaseLayoutBox::setSize(const Vector& new_size)
{
    if (!resizable_) return false;

    pos_ = new_size;

    return true;
}

void BaseLayoutBox::onParentUpdate(const LayoutBox& parent_layout)
{
    Vector cur_parent_size = parent_layout.getSize();

    double cf__resize_w = cur_parent_size.x / parent_size_.x;
    double cf__resize_h = cur_parent_size.y / parent_size_.y;

    double cf_offset_x = pos_.x / parent_size_.x;
    double cf_offset_y = pos_.y / parent_size_.y;

    parent_size_ = cur_parent_size;

    if (resizable_)
    {
        size_ = Vector(size_.x * cf__resize_w, size_.y * cf__resize_h);
    }

    if (save_locals_)
    {
        pos_ = Vector(cur_parent_size.x * cf_offset_x, cur_parent_size.y * cur_parent_size.y);
    }

    return;
}

LayoutBox* BaseLayoutBox::clone() const
{
    return (LayoutBox*) new BaseLayoutBox(pos_, size_, parent_size_, resizable_, save_locals_);
}