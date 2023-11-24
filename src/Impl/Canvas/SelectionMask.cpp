#include "Impl/Canvas/SelectionMask.h"

#include <algorithm>

SelectionMask::SelectionMask(const size_t width, const size_t height):
                            m_width(width), m_height(height), m_data(new bool[width * height])
{
    for (size_t it = 0; it < m_height; it++)
    {
        for (size_t jt = 0; jt < m_width; jt++)
        {
            m_data[it * m_width + jt] = false;
        }
    }
}

SelectionMask::SelectionMask(const size_t width, const size_t height, const plug::SelectionMask &init_mask):  
                            SelectionMask(width, height)
{
    size_t min_width  = std::min(m_width, init_mask.getWidth());
    size_t min_height = std::min(m_width, init_mask.getWidth());

    for (size_t it = 0; it < min_height; it++)
    {
        for (size_t jt = 0; jt < min_width; jt++)
        {
            m_data[it * m_width + jt] = init_mask.getPixel(jt, it);
        }
    }
}

bool SelectionMask::getPixel(size_t x, size_t y) const
{
    if (x >= m_width || y >= m_height) return false;

    return m_data[y * m_width + x];
}

void SelectionMask::setPixel(size_t x, size_t y, bool value)
{
    if (x >= m_width || y >= m_height) return;

    m_data[y * m_width + x] = value;
}

void SelectionMask::fill(bool value)
{
    for (size_t it = 0; it < m_height; it++)
    {
        for (size_t jt = 0; jt < m_width; jt++)
        {
            m_data[it * m_width + jt] = value;
        }
    }
}

void SelectionMask::invert(void)
{
    for (size_t it = 0; it < m_height; it++)
    {
        for (size_t jt = 0; jt < m_width; jt++)
        {
            m_data[it * m_width + jt] ^= true;
        }
    }
}