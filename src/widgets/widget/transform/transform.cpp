#include "transform.h"

Vec2d Transform::getOffset() const
{
    return offset_;
}

Vec2d Transform::setOffset(const Vec2d &offset)
{
    offset_ = offset;
}

Vec2d Transform::getScale() const
{
    return scale_;
}

Vec2d Transform::setScale(const Vec2d &scale)
{
    scale_ = scale;
}

Transform Transform::combine(const Transform &parent_transform)
{
    Dot new_pos = parent_transform.offset_ + Vec2d(parent_transform.scale_.x * offset_.x, parent_transform.scale_.y * offset_.y);
    Transform res(new_pos, {scale_.x * parent_transform.scale_.x, scale_.y * parent_transform.scale_.y});

    return res;
}

Dot Transform::apply(const Vec2d &vec)
{
    Dot res = vec - offset_;
    
    res.x /= scale_.x;
    res.y /= scale_.y;

    return res;
}

Vec2d Transform::restore(const Vec2d &vec)
{
    return vec * scale_ + offset_;
}
