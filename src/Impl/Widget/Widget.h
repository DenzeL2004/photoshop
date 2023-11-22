/**
 * @file Widget.h
 * @author Kudryashov Ilya (kudriashov.it@phystech.edu)
 * @brief Usable widget template
 * @version 0.1
 * @date 2023-11-17
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __IMPL_WIDGET_H
#define __IMPL_WIDGET_H

#include "Plug/Widget.h"

enum Corner {
  TopLeft = 0,
  TopRight,
  BottomLeft,
  BottomRight,
};

/**
 * @brief Usable widget
 *
 */
class Widget : public plug::Widget {
public:
  explicit Widget(const plug::LayoutBox &box);
  Widget(const Widget &widget);
  Widget &operator=(const Widget &widget);
  ~Widget() override;

  void draw(plug::TransformStack &stack, plug::RenderTarget &target) override;

  void onEvent(const plug::Event &event, plug::EHC &context) override;

  void onParentUpdate(const plug::LayoutBox &parent_box) override;

  plug::LayoutBox &getLayoutBox() override { return *box_; }
  const plug::LayoutBox &getLayoutBox() const override { return *box_; }
  void setLayoutBox(const plug::LayoutBox &box) override;

protected:
  plug::Vec2d getCorner(Corner corner, const plug::TransformStack &stack) const;

  bool covers(plug::TransformStack &stack,
              const plug::Vec2d &position) const override;

private:
  plug::LayoutBox *box_;
};

#endif
