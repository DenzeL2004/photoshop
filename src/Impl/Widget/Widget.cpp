#include "Widget.h"

Widget::Widget(const plug::LayoutBox& box) : box_(box.clone()) {}

Widget::Widget(const Widget& widget) : box_(widget.getLayoutBox().clone()) {}

Widget& Widget::operator=(const Widget& widget)
{
  delete box_;
  box_ = widget.box_->clone();
  return *this;
}

Widget::~Widget() { delete box_; }

void Widget::draw(plug::TransformStack& stack, plug::RenderTarget& target)
{
  static plug::VertexArray vertices(plug::PrimitiveType::LinesStrip, 5);

  // clang-format off
  vertices[0].position = stack.apply(getCorner(Corner::TopLeft,     stack));
  vertices[1].position = stack.apply(getCorner(Corner::TopRight,    stack));
  vertices[2].position = stack.apply(getCorner(Corner::BottomRight, stack));
  vertices[3].position = stack.apply(getCorner(Corner::BottomLeft,  stack));
  // clang-format on

  vertices[4] = vertices[0];

  for (size_t id = 0; id < vertices.getSize(); ++id)
  {
    vertices[id].color = plug::Color(255, 0, 255, 255);
  }

  target.draw(vertices);
}

void Widget::onEvent(const plug::Event& event, plug::EHC& context)
{
  switch (event.getType())
  {
  case plug::EventType::Tick:
  {
    onTick((const plug::TickEvent&)event, context);
  }
  break;
  case plug::EventType::KeyboardPressed:
  {
    onKeyboardPressed((const plug::KeyboardPressedEvent&)event, context);
  }
  break;
  case plug::EventType::KeyboardReleased:
  {
    onKeyboardReleased((const plug::KeyboardReleasedEvent&)event, context);
  }
  break;
  case plug::EventType::MousePressed:
  {
    onMousePressed((const plug::MousePressedEvent&)event, context);
  }
  break;
  case plug::EventType::MouseReleased:
  {
    onMouseReleased((const plug::MouseReleasedEvent&)event, context);
  }
  break;
  case plug::EventType::MouseMove:
  {
    onMouseMove((const plug::MouseMoveEvent&)event, context);
  }
  break;
  default:
    break;
  }
}

void Widget::onParentUpdate(const plug::LayoutBox& parent_box)
{
  box_->onParentUpdate(parent_box);
}

void Widget::setLayoutBox(const plug::LayoutBox& box)
{
  delete box_;
  box_ = box.clone();
}

plug::Vec2d Widget::getCorner(Corner corner, const plug::TransformStack& stack) const
{
  plug::Vec2d direction((corner & 1) ? 0.5 : -0.5, (corner & 2) ? -0.5 : 0.5);
  plug::Vec2d corner_pos = box_->getPosition() + box_->getSize() * direction;

  return stack.top().apply(corner_pos);
}

static inline bool isSmall(double a) { return fabs(a) < 1e-6; }

bool Widget::covers(plug::TransformStack& stack,
                    const plug::Vec2d&    position) const
{
  if (isSmall(box_->getSize().x) || isSmall(box_->getSize().y))
  {
    return false;
  }

  // clang-format off
  plug::Vec2d tl = getCorner(TopLeft,     stack);
  plug::Vec2d tr = getCorner(TopRight,    stack);
  plug::Vec2d br = getCorner(BottomRight, stack);
  plug::Vec2d bl = getCorner(BottomLeft,  stack);

  bool top_check      = plug::cross(tl - tr, position - tr) <= 0.0;
  bool right_check    = plug::cross(tr - br, position - br) <= 0.0;
  bool bottom_check   = plug::cross(br - bl, position - bl) <= 0.0;
  bool left_check     = plug::cross(bl - tl, position - tl) <= 0.0;
  // clang-format on

  return top_check && right_check && bottom_check && left_check;
}
