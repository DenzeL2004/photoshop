#ifndef _SELECTION_MASK_H_
#define _SELECTION_MASK_H_

#include "Plug/Canvas/SelectionMask.h"

class SelectionMask : public plug::SelectionMask
{
    public:
        SelectionMask(const size_t width, const size_t height);
        SelectionMask(const size_t width, const size_t height, const SelectionMask &other);


        virtual ~SelectionMask()
        {
            delete[] data_;
        }

        virtual size_t getWidth(void)  const { return width_; }
        virtual size_t getHeight(void) const { return height_; }

        virtual bool getPixel(size_t x, size_t y) const;
        virtual void setPixel(size_t x, size_t y, bool value);

        virtual void fill(bool value);
        virtual void invert(void);

    private:
        size_t width_, height_;
        bool *data_;
};



#endif