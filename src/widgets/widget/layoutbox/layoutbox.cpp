#include "layoutbox.h"

BaseLayoutBox::BaseLayoutBox(const Vector& pos, 
                             const Vector& size, const Vector& parent_size, 
                             const bool resizeble_flag):
                            pos_(pos), size_(size), resizable_(resizeble_flag), parent_size_(parent_size){}

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
    if (!resizable_) return;

    Vector cur_parent_size = parent_layout.getSize();

    double cf_x = cur_parent_size.x / parent_size_.x;
    double cf_y = cur_parent_size.y / parent_size_.y;

    parent_size_ = cur_parent_size;

    size_ = Vector(size_.x * cf_x, size_.y * cf_y);

    return;
}

LayoutBox* BaseLayoutBox::clone() const
{
    return (LayoutBox*) new BaseLayoutBox(pos_, size_, parent_size_, resizable_);
}