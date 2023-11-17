#include "Impl/TransformStack/TransformStack.h"
#include "Plug/Math.h"


void TransformStack::enter(const Transform &transform)
{
    if (stack_.getSize() == 0)
    {
        stack_.pushBack(transform);
        return;
    }

    stack_.pushBack(transform.combine(stack_.getBack()));
}


void TransformStack::leave()
{
    if (stack_.getSize() == 0)
        return;

    stack_.popBack();
}


Transform TransformStack::top() const
{
    if (stack_.getSize() == 0)
        return Transform(Vec2d(0.0, 0.0), Vec2d(1.0, 1.0));

    return stack_.getBack();
}

Vec2d TransformStack::apply(const Vec2d &vec) const
{
    if (stack_.getSize() == 0)
        return vec;

    return stack_.getBack().apply(vec);
} 


Vec2d TransformStack::restore(const Vec2d &vec) const
{
    if (stack_.getSize() == 0)
        return vec;

    return stack_.getBack().restore(vec);
}