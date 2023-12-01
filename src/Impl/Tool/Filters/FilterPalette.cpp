#include "FilterPalette.h"

plug::Filter* FilterPalette::getFilter(const size_t filter_id)
{
    if (filter_id >= m_filters.getSize()) 
    {
        PROCESS_ERROR(ERR_NULLPTR, "undefine ID: %lu\n", filter_id);
        return nullptr;
    }

    plug::Plugin *ret_filter = m_filters[filter_id]->tryGetInterface(static_cast<size_t>(plug::PluginGuid::Filter));
    return reinterpret_cast<plug::Filter*>(ret_filter);
}

plug::Filter* FilterPalette::getFilter(const char* filter_name)
{
    assert(filter_name != nullptr && "filter_name is nullptr");
    
    size_t size = m_filters.getSize();
    for (size_t it = 0; it < size; it++)
    {
        if (!strcmp(filter_name, m_filters[it]->getPluginData()->getName()))
        {
            plug::Plugin *ret_filter = m_filters[it]->tryGetInterface(static_cast<size_t>(plug::PluginGuid::Filter));
            return reinterpret_cast<plug::Filter*>(ret_filter);
        }
    }

    PROCESS_ERROR(ERR_NULLPTR, "undefine filter by name: %s\n", filter_name);
    return nullptr;
}

plug::Filter* FilterPalette::getLastFilter()
{
    return getFilter(m_last_filter);
}

void FilterPalette::setLastFilter(const size_t filter_id)
{
    m_last_filter = filter_id;
}

size_t FilterPalette::addFilter(plug::Filter* filter)
{
    assert(filter != nullptr && "adding filter is nullptr");
    
    m_filters.pushBack(filter);
    return m_filters.getSize();
}