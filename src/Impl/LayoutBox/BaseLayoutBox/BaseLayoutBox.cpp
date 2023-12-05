#include "BaseLayoutBox.h"

BaseLayoutBox::BaseLayoutBox(const plug::Vec2d& pos, 
                             const plug::Vec2d& size, const plug::Vec2d& parent_size, 
                             const bool resize_flag, const bool save_locals_flag):
                             m_pos(pos), 
                             m_size(size), m_parent_size(parent_size), 
                             m_resizable(resize_flag), m_save_locals(save_locals_flag){}

Vec2d BaseLayoutBox::getPosition() const
{
    return m_pos;
}

bool BaseLayoutBox::setPosition(const plug::Vec2d& new_pos)
{
    m_pos = new_pos;
    return true;
}

Vec2d BaseLayoutBox::getSize() const
{
    return m_size;
}

bool BaseLayoutBox::setSize(const plug::Vec2d& new_size)
{
    m_size = new_size;
    return true;
}

void BaseLayoutBox::onParentUpdate(const LayoutBox& parent_layout)
{
    plug::Vec2d new_parent_size = parent_layout.getSize();

    if (m_resizable)
    {
        double new_w = new_parent_size.x - m_parent_size.x + m_size.x;
        double new_h = new_parent_size.y - m_parent_size.y + m_size.y;

        m_size = plug::Vec2d(new_w, new_h);
    }

    if (m_save_locals)
    {
        double offset_x = std::min(m_pos.x, m_parent_size.x - m_pos.x);
        double offset_y = std::min(m_pos.y, m_parent_size.y - m_pos.y);

        if (m_parent_size.x / 2 <= m_pos.x)
            m_pos.x = new_parent_size.x - offset_x;

        if (m_parent_size.y / 2 <= m_pos.y)
            m_pos.y = new_parent_size.y - offset_y;
    }

    m_parent_size = new_parent_size;

    return;
}

plug::LayoutBox* BaseLayoutBox::clone() const
{
    return (LayoutBox*) new BaseLayoutBox(m_pos, m_size, m_parent_size, m_resizable, m_save_locals);
}