
#ifndef _TRANSFORM_STACK_H_
#define _TRANSFORM_STACK_H_

#include "Container/Container.h"
#include "Plug/Math.h"

class TransformStack : public plug::TransformStack
{
    public:

        TransformStack():m_stack(){}

        virtual ~TransformStack(){}

        virtual void enter(const plug::Transform &transform);
        virtual void leave();

        virtual plug::Transform top () const;
    
        virtual plug::Vec2d apply     (const plug::Vec2d &vec) const;
        virtual plug::Vec2d restore   (const plug::Vec2d &vec) const;

    private:
    
        Container<Transform> m_stack;

};

#endif