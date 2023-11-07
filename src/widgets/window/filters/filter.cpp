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

    return pixels_[width_ * y + x];
}

void FilterMask::setPixel(size_t x, size_t y, bool value)
{
    if (x  >= width_ || y >= height_)
        return;

    pixels_[width_ * y + x] = value;
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

void FilterBrightness::applyFilter(Canvas &canvas, const FilterMask &mask)
{
    
    sf::Image image = canvas.getBackground().getTexture().copyToImage();

    size_t width  = mask.getWidth();
    size_t height = mask.getHeight();

    for (size_t it = 0; it < width; it++)
    {
        for (size_t jt = 0; jt < height; jt++)
        {

            if (mask.getPixel(it, jt))
            {
                sf::Color color = image.getPixel(it, jt);
                
                float r_ray = (float)color.r / 255.f;
                float g_ray = (float)color.g / 255.f;
                float b_ray = (float)color.b / 255.f;

                float c_max = std::max(std::max(r_ray, g_ray), b_ray);
                float c_min = std::min(std::min(r_ray, g_ray), b_ray);

                float delta = c_max - c_min;
                
                float hue = -1.f;
                if (fabs(delta) < Eps)
                    hue = 0;
                else if (fabs(c_max - r_ray) < Eps)
                    hue = 60 * ((g_ray - b_ray) / delta + 0);
                else if (fabs(c_max - g_ray) < Eps)
                    hue = 60 * ((b_ray - r_ray) / delta + 2);
                else if (fabs(c_max - b_ray) < Eps)
                    hue = 60 * ((r_ray - g_ray) / delta + 4);

                float lightness = (c_min + c_max) / 2;

                float saturation = -1;
                if (fabs(delta) < Eps)
                    saturation = 0;
                else
                    saturation = delta / (1 - fabs(2 * lightness - 1));

                lightness += delta_;

                float c = (1 - fabs(2 * lightness - 1)) * saturation;
                float x = c * (1 - fabs(fmod(hue / 60, 2) - 1));
                float m = lightness - c / 2;
                
                if (hue < 60 + Eps)
                {
                    r_ray = c;
                    g_ray = x;
                    b_ray = 0;
                }
                else if (hue < 120 + Eps)
                {
                    r_ray = x;
                    g_ray = c;
                    b_ray = 0;
                }
                else if (hue < 180 + Eps)
                {
                    r_ray = 0;
                    g_ray = c;
                    b_ray = x;
                }
                else if (hue < 240 + Eps)
                {
                    r_ray = 0;
                    g_ray = x;
                    b_ray = c;
                }
                else if (hue < 300 + Eps)
                {
                    r_ray = x;
                    g_ray = 0;
                    b_ray = c;
                }
                else if (hue < 360 + Eps)
                {
                    r_ray = c;
                    g_ray = 0;
                    b_ray = x;
                }

                color.r = std::max(0, std::min(255, int32_t((r_ray + m) * 255)));
                color.g = std::max(0, std::min(255, int32_t((g_ray + m) * 255)));
                color.b = std::max(0, std::min(255, int32_t((b_ray + m) * 255)));
                    
                image.setPixel(it, jt, color);
            }
        }
    }

    sf::Texture texture;
    texture.loadFromImage(image);
    
    sf::Sprite sprite(texture);
    sprite.setTextureRect(sf::IntRect(0, height, width, -height));
    
    canvas.getBackground().clear();
    canvas.getBackground().draw(sprite);
}

void FilterBrightness::setDelta(const float delta)
{
    delta_ = delta;
}

//==========================================================================

FilterPalette::FilterPalette():
        filters_(),
        last_filter_(FilterType::NOTHING)
{
    filters_.pushBack(new FilterBrightness(0.0));   
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
