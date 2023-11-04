#ifndef _LAYOUTBOX_H_
#define _LAYOUTBOX_H_

#include "../../../vector/vector.h"

class LayoutBox
{
    public:

        ~LayoutBox() = default;

        virtual Vector      getPosition() const = 0;
        virtual bool        setPosition(const Vector& new_pos) = 0;

        virtual Vector      getSize() const = 0;
        virtual bool        setSize(const Vector& new_size) = 0;

        virtual void        onParentUpdate(const LayoutBox& parent_layout) = 0;

        virtual LayoutBox*  clone() const = 0;


    private:

        Vector pos_;
        Vector size_;      
};



class BaseLayoutBox
{
    public:

        BaseLayoutBox(const Vector& pos, 
                      const Vector& size, const Vector& parent_size, 
                      const bool resizeble_flag);
        ~BaseLayoutBox() = default;

        virtual Vector      getPosition() const;
        virtual bool        setPosition(const Vector& new_pos);

        virtual Vector      getSize() const;
        virtual bool        setSize(const Vector& new_size);

        virtual void        onParentUpdate(const LayoutBox& parent_layout);

        virtual LayoutBox*  clone() const;


    private:

        Vector pos_;
        Vector size_;      

        Vector parent_size_;

        bool resizable_;
};


#endif