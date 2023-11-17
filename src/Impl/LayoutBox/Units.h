/**
 * @file Units.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 *
 * @brief
 *
 * @version 0.1
 * @date 2023-11-16
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef __IMPL_LAYOUT_BOX_UNITS_H
#define __IMPL_LAYOUT_BOX_UNITS_H

enum class Unit
{
  Percent,
  Pixel,
  Centimeter,
  Millimeter,
  Inch
};

static constexpr double PixelsPerInch            = 96;
static constexpr double CentimetersPerInch       = 2.54;
static constexpr double MillimitersPerCentimeter = 10;

struct Length
{
  double value;
  Unit   unit;

  Length() : Length(0, Unit::Pixel) {}
  Length(double val, Unit type) : value(val), unit(type) {}

  Length(const Length& other) : Length(other.value, other.unit) {}

  Length& operator=(const Length& other)
  {
    this->value = other.value;
    this->unit  = other.unit;
    return *this;
  }

  operator double() const
  {
    switch (unit)
    {
    case Unit::Pixel:
      return value;
    case Unit::Centimeter:
      return value / CentimetersPerInch * PixelsPerInch;
    case Unit::Millimeter:
      return value / MillimitersPerCentimeter / CentimetersPerInch *
             PixelsPerInch;
    case Unit::Inch:
      return value * PixelsPerInch;

    case Unit::Percent:
    default:
      return 0;
    }
  }
};

enum class Align
{
  // clang-format off
  TopLeft,    TopCenter,    TopRight,
  CenterLeft, Center,       CenterRight,
  BottomLeft, BottomCenter, BottomRight,
  // clang-format on
  Free
};

inline Length operator""_per(long double val)
{
  return Length(val, Unit::Percent);
}
inline Length operator""_px(long double val)
{
  return Length(val, Unit::Pixel);
}
inline Length operator""_cm(long double val)
{
  return Length(val, Unit::Centimeter);
}
inline Length operator""_mm(long double val)
{
  return Length(val, Unit::Millimeter);
}
inline Length operator""_in(long double val) { return Length(val, Unit::Inch); }

inline Length operator""_per(unsigned long long val)
{
  return Length(val, Unit::Percent);
}
inline Length operator""_px(unsigned long long val)
{
  return Length(val, Unit::Pixel);
}
inline Length operator""_cm(unsigned long long val)
{
  return Length(val, Unit::Centimeter);
}
inline Length operator""_mm(unsigned long long val)
{
  return Length(val, Unit::Millimeter);
}
inline Length operator""_in(unsigned long long val)
{
  return Length(val, Unit::Inch);
}

#endif /* Units.h */
