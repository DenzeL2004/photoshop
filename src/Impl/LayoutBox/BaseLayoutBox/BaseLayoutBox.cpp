#include "BaseLayoutBox.h"

BaseLayoutBox::BaseLayoutBox(const plug::Vec2d& pos, 
                             const plug::Vec2d& size, const plug::Vec2d& parent_size, 
                             const bool resize_flag, const bool save_locals_flag):
                            pos_(pos), 
                            size_(size), parent_size_(parent_size), 
                            resizable_(resize_flag), save_locals_(save_locals_flag){}

Vec2d BaseLayoutBox::getPosition() const
{
    return pos_;
}

bool BaseLayoutBox::setPosition(const plug::Vec2d& new_pos)
{
    pos_ = new_pos;
    return true;
}

Vec2d BaseLayoutBox::getSize() const
{
    return size_;
}

bool BaseLayoutBox::setSize(const plug::Vec2d& new_size)
{
    size_ = new_size;
    return true;
}

void BaseLayoutBox::onParentUpdate(const LayoutBox& parent_layout)
{
    plug::Vec2d new_parent_size = parent_layout.getSize();

    if (resizable_)
    {
        double new_w = new_parent_size.x - parent_size_.x + size_.x;
        double new_h = new_parent_size.y - parent_size_.y + size_.y;

        size_ = plug::Vec2d(new_w, new_h);
    }

    if (save_locals_)
    {
        double offset_x = std::min(pos_.x, parent_size_.x - pos_.x);
        double offset_y = std::min(pos_.y, parent_size_.y - pos_.y);

        if (parent_size_.x / 2 <= pos_.x)
            pos_.x = new_parent_size.x - offset_x;

        if (parent_size_.y / 2 <= pos_.y)
            pos_.y = new_parent_size.y - offset_y;
    }

    parent_size_ = new_parent_size;

    return;
}

plug::LayoutBox* BaseLayoutBox::clone() const
{
    return (LayoutBox*) new BaseLayoutBox(pos_, size_, parent_size_, resizable_, save_locals_);
}