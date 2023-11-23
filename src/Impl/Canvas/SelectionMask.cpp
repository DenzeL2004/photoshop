#include "Impl/Canvas/SelectionMask.h"

#include <algorithm>

plug::SelectionMask::~SelectionMask(){}

SelectionMask::SelectionMask(const size_t width, const size_t height):
                            width_(width), height_(height), data_(new bool[width * height])
{
    for (size_t it = 0; it < height_; it++)
    {
        for (size_t jt = 0; jt < width_; jt++)
        {
            data_[it * width_ + jt] = false;
        }
    }
}

SelectionMask::SelectionMask(const size_t width, const size_t height, const SelectionMask &other):  
                            SelectionMask(width, height)
{
    size_t min_width  = std::min(width_, other.getWidth());
    size_t min_height = std::min(width_, other.getWidth());

    for (size_t it = 0; it < min_height; it++)
    {
        for (size_t jt = 0; jt < min_width; jt++)
        {
            data_[it * width_ + jt] = other.getPixel(jt, it);
        }
    }
}

bool SelectionMask::getPixel(size_t x, size_t y) const
{
    if (x >= width_ || y >= height_) return false;

    return data_[y * width_ + x];
}

void SelectionMask::setPixel(size_t x, size_t y, bool value)
{
    if (x >= width_ || y >= height_) return;

    data_[y * width_ + x] = value;
}

void SelectionMask::fill(bool value)
{
    for (size_t it = 0; it < height_; it++)
    {
        for (size_t jt = 0; jt < width_; jt++)
        {
            data_[it * width_ + jt] = value;
        }
    }
}

void SelectionMask::invert(void)
{
    for (size_t it = 0; it < height_; it++)
    {
        for (size_t jt = 0; jt < width_; jt++)
        {
            data_[it * width_ + jt] ^= true;
        }
    }
}