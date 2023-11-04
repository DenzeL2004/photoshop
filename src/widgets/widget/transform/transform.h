#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "../../../graphic/graphic.h"
#include "../../../vector/vector.h"

struct Transform
{
    public:
        Transform():
        offset(0, 0), scale(1.0, 1.0){}

        Transform (const Vector& offset_ = Vector(0.0, 0.0), const Vector& scale_ = Vector(1.0, 1.0)):
                  offset(offset_), scale(scale_){}

        ~Transform() = default;

        Transform (const Transform &other) = default;
        Transform& operator= (const Transform &other) = default;

        Transform       applyPrev         (const Transform &prev) const;
        Vector          applyTransform    (const Dot &pos) const;
        
        sf::Vector2f    rollbackTransform (const Dot &vec) const;

        Vector offset;
        Vector scale;

};

#endif

