
#ifndef _BASE_LAYOUT_BOX_
#define _BASE_LAYOUT_BOX_

#include "Plug/LayoutBox.h"
#include "Plug/Math.h"

class BaseLayoutBox : public plug::LayoutBox
{
    public:
        BaseLayoutBox(const plug::Vec2d &pos, 
                      const plug::Vec2d &size, const plug::Vec2d &parent_size, 
                      const bool resize_flag, const bool save_locals_flag);


        virtual Vec2d getPosition() const;
        virtual bool setPosition(const plug::Vec2d &new_pos);

        virtual Vec2d getSize() const;
        virtual bool setSize(const plug::Vec2d &new_size);

        virtual void onParentUpdate(const LayoutBox &parent_layout);

        virtual plug::LayoutBox* clone() const;

    private:
        plug::Vec2d m_pos;
        plug::Vec2d m_size, m_parent_size;  
        
        bool m_resizable, m_save_locals;
 
};

#endif 
