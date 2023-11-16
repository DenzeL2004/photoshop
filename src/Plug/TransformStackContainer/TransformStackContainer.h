
#ifndef _TRANSFORM_STACK_CONTAINER_H_
#define _TRANSFORM_STACK_CONTAINER_H_

#include "../Math.h"
#include "../../container/container.h"

class TransformStack : public plug::TransformStack
{
    public:

    TransformStack():stack_(){}

    virtual ~TransformStack() = default;

    virtual void enter (const Transform &transform)
    {
        if (stack_.getSize() == 0)
        {
            stack_.pushBack(transform);
            return;
        }

        stack_.pushBack(transform.combine(stack_.getBack()));
    }


    virtual void leave ()
    {
        if (stack_.getSize() == 0)
            return;

        stack_.popBack();
    }
    
    
    virtual Transform top () const
    {
        if (stack_.getSize() == 0)
            return Transform(Vec2d(0.0, 0.0), Vec2d(1.0, 1.0));

        return stack_.getBack();
    }

    virtual Vec2d apply(const Vec2d &vec) const
    {
        if (stack_.getSize() == 0)
            return vec;

        return stack_.getBack().apply(vec);
    
    } 

   
    virtual Vec2d restore(const Vec2d &vec) const
    {
        if (stack_.getSize() == 0)
            return vec;

        return stack_.getBack().restore(vec);
    }

    private:
    
    Container<Transform> stack_;

};

#endif