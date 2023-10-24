#include "filter.h"

FilterMask::FilterMask(size_t width, size_t height):
                       width_(width), height_(height), pixels_(nullptr)
{
    pixels_ = new bool [height_ * width_];

    fill(false);
}

bool FilterMask::getPixel(size_t x, size_t y) const
{
    if (x  >= width_ || y >= height_)
        return false;

    return pixels_[width_ * x + y];
}

void FilterMask::setPixel(size_t x, size_t y, bool value)
{
    if (x  >= width_ || y >= height_)
        return;

    pixels_[width_ * x + y] = value;
}


void FilterMask::fill(bool value)
{
    for (size_t it = 0; it < width_; it++)
        for (size_t jt = 0; jt < height_; jt++)
            pixels_[width_ * it + jt] = value;
}

void FilterMask::invert()
{
    for (size_t it = 0; it < width_; it++)
        for (size_t jt = 0; jt < height_; jt++)
            pixels_[width_ * it + jt] = !pixels_[width_ * it + jt];
}

//==========================================================================

void FilterLight::applyFilter(Canvas &canvas, const FilterMask &mask)
{
    sf::Image image = canvas.background_.getTexture().copyToImage();

    size_t width  = mask.getWidth();
    size_t height = mask.getHeight();

    for (size_t it = 0; it < width; it++)
    {
        for (size_t jt = 0; jt < height; jt++)
        {
            sf::Color color = image.getPixel(it, jt);
            color.a += alpha_;
            image.setPixel(it, jt, color);
        }
    }

    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite(texture);
    sprite.scale(1.f, -1.f);

    canvas.background_.draw(sprite);
}

//==========================================================================

FilterPalette::FilterPalette():
        filters_(),
        last_filter_(FilterType::NOTHING)
{
    filters_.PushBack(new FilterLight(-10));
    
}

FilterPalette::~FilterPalette()
{
    size_t size = filters_.GetSize();
    for (size_t it = 0; it < size; it++)
        delete filters_[it];
}

Filter* FilterPalette::getFilter(size_t filter_id)
{
    switch (filter_id)
    {
        case FilterPalette::FilterType::LIGHT:
            return filters_[FilterPalette::FilterType::LIGHT];
        default:
            return nullptr;
    }

    return nullptr;
}

Filter* FilterPalette::getLastFilter()
{
    return getFilter(last_filter_);
}


void FilterPalette::setLastFilter(size_t filter_id)
{
    last_filter_ = filter_id;
}