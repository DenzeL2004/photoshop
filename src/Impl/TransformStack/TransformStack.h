
#ifndef _TRANSFORM_STACK_H_
#define _TRANSFORM_STACK_H_

#include "Container/Container.h"
#include "Plug/Math.h"

class TransformStack : public plug::TransformStack
{
    public:

    TransformStack():m_stack(){}

    virtual ~TransformStack(){}

    virtual void enter(const Transform &transform);
    virtual void leave();

    virtual Transform top () const;
 
    virtual Vec2d apply     (const Vec2d &vec) const;
    virtual Vec2d restore   (const Vec2d &vec) const;

    private:
    
    Container<Transform> m_stack;

};

#endif