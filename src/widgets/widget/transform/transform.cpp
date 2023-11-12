#include "transform.h"

Transform Transform::applyPrev(const Transform &prev) const
{
    Dot new_pos = prev.offset + Vec2d(prev.scale.x * offset.x, prev.scale.y * offset.y);
    Transform res(new_pos, {scale.x * prev.scale.x, scale.y * prev.scale.y});

    return res;
}

Dot Transform::applyTransform(const Dot &pos) const
{
    Dot res = pos - offset;
    
    res.x /= scale.x;
    res.y /= scale.y;

    return res;
}

sf::Vector2f Transform::rollbackTransform (const Dot &vec) const
{
    return sf::Vector2f(vec.x * scale.x + offset.x, vec.y * scale.y + offset.y);
}

//================================================================================
