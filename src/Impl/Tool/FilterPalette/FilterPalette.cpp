#include "FilterPalette.h"

void FilterPalette::loadPlugins(Container<plug::Plugin*> &plugin_list)
{
    size_t cnt_plugins = plugin_list.getSize();
    for (size_t it = 0; it < cnt_plugins; it++)
    {
        plug::Filter *filter = static_cast<plug::Filter*>(plugin_list[it]->tryGetInterface(static_cast<size_t>(plug::PluginGuid::Filter)));
        if (filter)
        {
            m_filters.pushBack(filter);
        }
    }
}

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

bool FilterPalette::saveFilter(plug::Filter* filter, const size_t filter_id)
{
    if (!filter)
        return PROCESS_ERROR(false, "add filer is nullptr");
    
    if (filter_id >= Filters_cout_max)
        return PROCESS_ERROR(false, "Can't save filter by ID(%lu). Max filters count(%lu)\n", filter_id, Filters_cout_max);        

    if (!m_filters[filter_id])
    {
        m_filters[filter_id] = filter;
    }
    else
    {
        PROCESS_ERROR(true, "release plugin(%s) by ptr(%p)\n", m_filters[filter_id]->getPluginData()->getName(), m_filters[filter_id]);
        m_filters[filter_id]->release();
        m_filters[filter_id] = filter;
    }

    return true;
}