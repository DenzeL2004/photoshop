#ifndef _FILTER_NEGATIVE_H_
#define _FILTER_NEGATIVE_H_

#include "Impl/Tool/PluginUtil.h"

class NegativeFilter : public DefFilter
{
    public:
        NegativeFilter():DefFilter("Negative", "ERROR_PATH"){}

        ~NegativeFilter() = default;

        virtual void applyFilter(plug::Canvas &canvas) const;

        virtual plug::Widget *getWidget(void) { return nullptr; }        
};

extern "C" plug::Plugin* loadPlugin(void);

#endif