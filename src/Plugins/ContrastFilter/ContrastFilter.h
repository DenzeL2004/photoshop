#ifndef _FILTER_CONTRAST_H_
#define _FILTER_CONTRAST_H_

#include "Impl/Tool/PluginUtil.h"

class ContrastFilter : public DefFilter
{
    public:
        ContrastFilter(const int correction = 0):
                        DefFilter("Contrast", "ERROR_PATH"),
                        m_correction(correction){}

        virtual void applyFilter(plug::Canvas &canvas) const;

        virtual plug::Widget *getWidget(void) { return nullptr; }     

        virtual ~ContrastFilter(){}

        ContrastFilter(const ContrastFilter &other) = delete;
        ContrastFilter &operator= (const ContrastFilter &other) = delete;

    private:
        int m_correction;

        const double Cf_r = 0.299;
        const double Cf_g = 0.587;
        const double Cf_b = 0.114; 
};

extern "C" plug::Plugin* loadPlugin(void);

#endif