#ifndef _FILTER_H_
#define _FILTER_H_

#include "../canvas.h"


class FilterMask
{
    public:
        FilterMask(size_t width, size_t height);
        ~FilterMask()
        {
            delete [] pixels_;
        }

        size_t getWidth() const {return width_;}
        size_t getHeight() const {return height_;}

        bool getPixel(size_t x, size_t y) const;
        void setPixel(size_t x, size_t y, bool value);

        void fill(bool value);

        void invert();

    private: 
        bool *pixels_;
        size_t width_;
        size_t height_;
};

class Filter
{
    public:
        Filter(){}
        ~Filter() = default;

        virtual void applyFilter(Canvas &canvas, const FilterMask &mask) {};
};

class FilterBrightness : public Filter
{
    public:
        FilterBrightness (const float delta):delta_(delta){}
        ~FilterBrightness() = default;

        virtual void applyFilter(Canvas &canvas, const FilterMask &mask);

        void setDelta(const float delta);

    private:
        float delta_;
};

class FilterPalette
{
    public:

        enum FilterType
        {
            NOTHING  = -1,
            LIGHT    = 0, 
        };

        FilterPalette ();
        ~FilterPalette ();

        Filter* getLastFilter();
        void    setLastFilter   (size_t filter_id);

        Filter* getFilter       (size_t filter_id);
        
        size_t  getFilterCount() const {return filters_.getSize();}

        void addFilter      (Filter *ptr);

    private:
        Container<Filter*>  filters_;
        size_t last_filter_;

};

#endif