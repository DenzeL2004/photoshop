

#ifndef _PLUGIN_H_
#define _PLUGIN_H_

#include "../widgets/window/filters/filter.h"

extern "C" Filter* loadPlugin();

class FilterBlackWhite : public Filter
{
    public:
        FilterBlackWhite(){}
        ~FilterBlackWhite() = default;

        virtual void applyFilter(Canvas &canvas);

    private:
};


#endif