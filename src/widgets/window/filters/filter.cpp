#include <dlfcn.h>

#include "filter.h"

//==========================================================================


FilterPalette::FilterPalette():
        filters_(),
        last_filter_(FilterType::NOTHING)
{
    
    void* plugin = dlopen("plugins/plugin.so", RTLD_NOW | RTLD_LOCAL | RTLD_NODELETE);
    assert(plugin != nullptr);

    plugint_t* load_plugin = (plugint_t*)dlsym(plugin, "pluginBlackWhite");

    Filter* filter = load_plugin();

    filters_.pushBack(filter);

    dlclose(plugin);

}

FilterPalette::~FilterPalette()
{
    size_t size = filters_.getSize();
    for (size_t it = 0; it < size; it++)
        delete filters_[it];
}

Filter* FilterPalette::getFilter(size_t filter_id)
{
    if (filter_id == FilterPalette::FilterType::NOTHING || filter_id >= filters_.getSize()) 
        return nullptr;
    
    return filters_[filter_id];;
}

Filter* FilterPalette::getLastFilter()
{
    return getFilter(last_filter_);
}


void FilterPalette::setLastFilter(size_t filter_id)
{
    last_filter_ = filter_id;
}

void FilterPalette::addFilter(Filter *ptr)
{
    filters_.pushBack(ptr);
}
