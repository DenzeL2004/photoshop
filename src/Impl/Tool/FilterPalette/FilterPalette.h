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
            UNKNOWN = -1,
            LAST = 10001,
        };

        FilterPalette():m_filters(), m_last_filter(UNKNOWN){}
        
        ~FilterPalette()
        {
            size_t cnt = m_filters.getSize();

            for (size_t it = 0; it < cnt; it++)
            {
                if (m_filters[it]) m_filters[it]->release();
            }
        }

        void loadPlugins(Container<plug::Plugin*> &plugins);

        plug::Filter* getLastFilter();
        void setLastFilter(const size_t filter_id);

        plug::Filter* getFilter(const size_t filter_id);
        plug::Filter* getFilter(const char* filter_name);

        bool saveFilter(plug::Filter* filter, const size_t id);

        size_t getSize(){ return m_filters.getSize();}

        FilterPalette(const FilterPalette &other) = delete;
        FilterPalette &operator= (const FilterPalette &other) = delete;
        
    private:
        Container<plug::Filter*> m_filters;
        size_t m_last_filter;

};

#endif