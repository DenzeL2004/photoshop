#ifndef _FILTER_H_
#define _FILTER_H_

#include "../canvas.h"




class Filter
{
    public:
        Filter(){}
        ~Filter() = default;

        virtual void applyFilter(Canvas &canvas) = 0;
};

typedef Filter* plugint_t(void);


class FilterPalette
{
    public:

        enum FilterType
        {
            NOTHING     = -1,
            BLACKWHITE  = 0, 
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