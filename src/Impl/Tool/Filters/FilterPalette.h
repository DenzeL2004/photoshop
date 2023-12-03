#ifndef _FILTER_PALETTE_H_
#define _FILTER_PALETTE_H_

#include "Container/Container.h"
#include "Plug/Filter.h"
#include "Impl/Tool/PluginUtil.h"

static const size_t Filters_cout_max = 20;

class FilterPalette
{
    public:

        enum FilterType
        {
            NEGATIVE,
        };

        FilterPalette():    m_filters(Filters_cout_max), m_last_filter(UINT64_MAX)
        {
            saveFilter(static_cast<plug::Filter*>(loadPlugin("obj/Plugins/Negative.so")->tryGetInterface(static_cast<size_t>(plug::PluginGuid::Filter))), FilterType::NEGATIVE);
        }
        
        ~FilterPalette()
        {
            size_t size = m_filters.getSize();
            for (size_t it = 0; it < size; it++)
            {
                if (m_filters[it]) m_filters[it]->release();
            }
        }

        plug::Filter* getLastFilter();
        void setLastFilter(const size_t filter_id);

        plug::Filter* getFilter(const size_t filter_id);
        plug::Filter* getFilter(const char* filter_name);

        bool saveFilter(plug::Filter* filter, const size_t id);
        
    private:
        Container<plug::Filter*> m_filters;
        size_t m_last_filter;

};

#endif