#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "../../../graphic/graphic.h"
#include "../../../vector/vector.h"

struct Transform
{
    public:
        Transform():
        offset(0, 0), scale(1.0, 1.0){}

        Transform (const Vec2d& offset_ = Vec2d(0.0, 0.0), const Vec2d& scale_ = Vec2d(1.0, 1.0)):
                  offset(offset_), scale(scale_){}

        ~Transform() = default;

        Transform (const Transform &other) = default;
        Transform& operator= (const Transform &other) = default;

        Transform       applyPrev         (const Transform &prev) const;
        Vec2d          applyTransform    (const Dot &pos) const;
        
        sf::Vector2f    rollbackTransform (const Dot &vec) const;

        Vec2d offset;
        Vec2d scale;

};

#endif

