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

        FilterPalette():m_filters(), m_last_filter(2)
        {
            Container<plug::Plugin*> plugin_list;
            loadePlugins(plugin_list);

            size_t cnt_plugins = plugin_list.getSize();
            for (size_t it = 0; it < cnt_plugins; it++)
            {
                plug::Filter *filter = static_cast<plug::Filter*>(plugin_list[it]->tryGetInterface(static_cast<size_t>(plug::PluginGuid::Filter)));
                if (filter)
                {
                    m_filters.pushBack(filter);
                    filter->release();
                }
            }
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

        size_t getSize(){ return m_filters.getSize();}

        FilterPalette(const FilterPalette &other) = delete;
        FilterPalette &operator= (const FilterPalette &other) = delete;
        
    private:
        Container<plug::Filter*> m_filters;
        size_t m_last_filter;

};

#endif