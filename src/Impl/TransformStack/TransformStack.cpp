#include "Impl/TransformStack/TransformStack.h"
#include "Plug/Math.h"


void TransformStack::enter(const plug::Transform &transform)
{
    if (m_stack.getSize() == 0)
    {
        m_stack.pushBack(transform);
        return;
    }

    m_stack.pushBack(transform.combine(m_stack.getBack()));
}


void TransformStack::leave()
{
    if (m_stack.getSize() == 0)
        return;

    m_stack.popBack();
}


plug::Transform TransformStack::top() const
{
    if (m_stack.getSize() == 0)
        return Transform(Vec2d(0.0, 0.0), Vec2d(1.0, 1.0));

    return m_stack.getBack();
}

plug::Vec2d TransformStack::apply(const plug::Vec2d &vec) const
{
    if (m_stack.getSize() == 0)
        return vec;

    return m_stack.getBack().apply(vec);
} 


plug::Vec2d TransformStack::restore(const plug::Vec2d &vec) const
{
    if (m_stack.getSize() == 0)
        return vec;

    return m_stack.getBack().restore(vec);
}