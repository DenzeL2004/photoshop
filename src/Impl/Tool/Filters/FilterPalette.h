#ifndef _FILTER_PALETTE_H_
#define _FILTER_PALETTE_H_

#include "Container/Container.h"
#include "Plug/Filter.h"
#include "Impl/Tool/PluginUtil.h"

class FilterPalette
{
    public:

        FilterPalette():    m_filters(), m_last_filter(UINT64_MAX)
        {
            plug::Plugin* plugin = loadPlugin("obj/Plugins/test_filter.so")->tryGetInterface(static_cast<size_t>(plug::PluginGuid::Filter));
            addFilter(static_cast<plug::Filter*>(plugin));
        }
        
        ~FilterPalette()
        {
            size_t size = m_filters.getSize();
            for (size_t it = 0; it < size; it++)
            {
                m_filters[it]->release();
            }
        }

        plug::Filter* getLastFilter();
        void setLastFilter(const size_t filter_id);

        plug::Filter* getFilter(const size_t filter_id);
        plug::Filter* getFilter(const char* filter_name);

        size_t addFilter(plug::Filter*);
        
    private:
        Container<plug::Filter*> m_filters;
        size_t m_last_filter;

};

#endif