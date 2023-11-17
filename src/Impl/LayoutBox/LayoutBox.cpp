#include "Impl/LayoutBox/LayoutBox.h"

#include "Impl/LayoutBox/Units.h"
#include "Plug/Math.h"

static double getPixels(const Length& len, double parent_len)
{
  if (len.unit == Unit::Percent)
    return parent_len * len.value / 100;
  return (double)len;
}

static Length fromPixels(double pixels, Unit unit, double parent_pixels)
{
  double value = 0;
  switch (unit)
  {
  case Unit::Pixel:
    value = pixels;
    break;
  case Unit::Centimeter:
    value = pixels / PixelsPerInch * CentimetersPerInch;
    break;
  case Unit::Millimeter:
    value =
        pixels / PixelsPerInch * CentimetersPerInch * MillimitersPerCentimeter;
    break;
  case Unit::Inch:
    value = pixels / PixelsPerInch;
    break;
  case Unit::Percent:
    value = pixels / parent_pixels * 100;
    break;
  default:
    value = 0;
    break;
  }

  return Length(value, unit);
}

static double clampToZero(double val)
{
  if (val < 0)
    return 0;
  return val;
}

void LayoutBox::updateParent(const plug::LayoutBox& parent_box)
{
  m_parentSize = parent_box.getSize();

  if (m_align == Align::Free)
  {
    return;
  }

  plug::Vec2d full_size(getPixels(m_width, m_parentSize.x),
                        getPixels(m_height, m_parentSize.y));

  const double pad_left = getPixels(m_paddingLeft, m_parentSize.x);
  const double pad_top  = getPixels(m_paddingTop, m_parentSize.y);

  const double unit_x = fabs(m_parentSize.x - full_size.x) / 2;
  const double unit_y = fabs(m_parentSize.y - full_size.y) / 2;

  double start_x = m_parentSize.x < full_size.x ? -2 * unit_x : 0;
  double start_y = m_parentSize.y < full_size.y ? -2 * unit_y : 0;

  plug::Vec2d pos(start_x, start_y);

  switch (m_align)
  {
    // clang-format off
  case Align::TopLeft:      pos += plug::Vec2d(       0,        0); break;
  case Align::TopCenter:    pos += plug::Vec2d(  unit_x,        0); break;
  case Align::TopRight:     pos += plug::Vec2d(2*unit_x,        0); break;
  case Align::CenterLeft:   pos += plug::Vec2d(       0,   unit_y); break;
  case Align::Center:       pos += plug::Vec2d(  unit_x,   unit_y); break;
  case Align::CenterRight:  pos += plug::Vec2d(2*unit_x,   unit_y); break;
  case Align::BottomLeft:   pos += plug::Vec2d(       0, 2*unit_y); break;
  case Align::BottomCenter: pos += plug::Vec2d(  unit_x, 2*unit_y); break;
  case Align::BottomRight:  pos += plug::Vec2d(2*unit_x, 2*unit_y); break;
    // clang-format on

  case Align::Free:
  default:
    break;
  }

  m_posX = fromPixels(pos.x + pad_left, m_posX.unit, m_parentSize.x);
  m_posY = fromPixels(pos.y + pad_top, m_posY.unit, m_parentSize.y);
}

bool LayoutBox::setSize(const plug::Vec2d& size)
{
  if (!m_resizable)
  {
    return false;
  }

  m_width  = fromPixels(size.x, m_width.unit, m_parentSize.x);
  m_height = fromPixels(size.y, m_height.unit, m_parentSize.y);

  return true;
}

bool LayoutBox::setPosition(const plug::Vec2d& position)
{
  if (m_align != Align::Free)
  {
    return false;
  }

  m_posX = fromPixels(position.x, m_posX.unit, m_parentSize.x);
  m_posY = fromPixels(position.y, m_posY.unit, m_parentSize.y);

  return true;
}

plug::Vec2d LayoutBox::getSize() const
{
  const double full_width  = getPixels(m_width, m_parentSize.x);
  const double full_height = getPixels(m_height, m_parentSize.y);

  const double pad_horiz = getPixels(m_paddingLeft, m_parentSize.x) +
                           getPixels(m_paddingRight, m_parentSize.x);
  const double pad_vert = getPixels(m_paddingTop, m_parentSize.y) +
                          getPixels(m_paddingBottom, m_parentSize.y);

  return plug::Vec2d(clampToZero(full_width - pad_horiz),
                     clampToZero(full_height - pad_vert));
}

plug::Vec2d LayoutBox::getPosition() const
{
  return plug::Vec2d(getPixels(m_posX, m_parentSize.x),
                     getPixels(m_posY, m_parentSize.y));
}
