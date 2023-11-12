#ifndef _LAYOUTBOX_H_
#define _LAYOUTBOX_H_

#include "../../../vector/vector.h"

class LayoutBox
{
    public:

        ~LayoutBox() = default;

        virtual Vec2d      getPosition() const = 0;
        virtual bool        setPosition(const Vec2d& new_pos) = 0;

        virtual Vec2d      getSize() const = 0;
        virtual bool        setSize(const Vec2d& new_size) = 0;

        virtual void        onParentUpdate(const LayoutBox& parent_layout) = 0;

        virtual LayoutBox*  clone() const = 0;


    private:

        Vec2d pos_;
        Vec2d size_;      
};



class BaseLayoutBox : public LayoutBox
{
    public:

        BaseLayoutBox(const Vec2d& pos, 
                      const Vec2d& size, const Vec2d& parent_size, 
                      const bool resize_flag, const bool save_locals_flag);
        ~BaseLayoutBox() = default;

        virtual Vec2d      getPosition() const;
        virtual bool        setPosition(const Vec2d& new_pos);

        virtual Vec2d      getSize() const;
        virtual bool        setSize(const Vec2d& new_size);

        virtual void        onParentUpdate(const LayoutBox& parent_layout);

        virtual LayoutBox*  clone() const;


    private:

        Vec2d pos_;
        Vec2d size_;      

        Vec2d parent_size_;

        bool resizable_;
        bool save_locals_;
};


#endif