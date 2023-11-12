#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "../../../graphic/graphic.h"
#include "../../../vector/vector.h"

struct Transform
{
    public:
        Transform():
        offset_(0, 0), scale_(1.0, 1.0){}

        Transform(  const Vec2d& offset = Vec2d(0.0, 0.0), 
                    const Vec2d& scale = Vec2d(1.0, 1.0)):
                    offset_(offset), scale_(scale){}

        ~Transform() = default;

        Transform(const Transform &other) = default;
        Transform& operator= (const Transform &other) = default;

        Vec2d getOffset () const;
        Vec2d setOffset (const Vec2d &offset);
        
        Vec2d getScale  () const;
        Vec2d setScale  (const Vec2d &scale);

        Vec2d apply     (const Vec2d &vec);
        Vec2d restore   (const Vec2d &vec);

        Transform combine (const Transform &parent_transform);

    private:
        Vec2d offset_;
        Vec2d scale_;

};

#endif

