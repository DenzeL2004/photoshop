#include "FilterPalette.h"

// FilterPalette::FilterPalette():
//         m_filters(),
//         m_last_filter(FilterType::NOTHING)
// {
//     filters_.pushBack(new FilterBrightness(0.0));
//     filters_.pushBack(new FilterBlackWhite());      
//     filters_.pushBack(new FilterInvert());
//     filters_.pushBack(new FilterColorMask(sf::Color::Red));
//     filters_.pushBack(new FilterColorMask(sf::Color::Green));
//     filters_.pushBack(new FilterColorMask(sf::Color::Blue));      
// }

// FilterPalette::~FilterPalette()
// {
//     size_t size = filters_.getSize();
//     for (size_t it = 0; it < size; it++)
//         delete filters_[it];
// }

// Filter* FilterPalette::getFilter(size_t filter_id)
// {
//     if (filter_id == FilterPalette::FilterType::NOTHING || filter_id >= filters_.getSize()) 
//         return nullptr;
    
//     return filters_[filter_id];;
// }

// Filter* FilterPalette::getLastFilter()
// {
//     return getFilter(last_filter_);
// }


// void FilterPalette::setLastFilter(size_t filter_id)
// {
//     last_filter_ = filter_id;
// }

// void FilterPalette::addFilter(Filter *ptr)
// {
//     filters_.pushBack(ptr);
// }