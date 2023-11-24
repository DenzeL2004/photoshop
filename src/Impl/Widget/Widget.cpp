#include "Widget.h"

Widget::Widget(const plug::LayoutBox& box) : m_box(box.clone()) {}

Widget::Widget(const Widget& widget) : m_box(widget.getLayoutBox().clone()) {}

Widget& Widget::operator=(const Widget& widget)
{
  delete m_box;
  m_box = widget.m_box->clone();
  return *this;
}

Widget::~Widget() { delete m_box; }

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
  m_box->onParentUpdate(parent_box);
}

void Widget::setLayoutBox(const plug::LayoutBox& box)
{
  delete m_box;
  m_box = box.clone();
}

plug::Vec2d Widget::getCorner(Corner corner, const plug::TransformStack& stack) const
{
  plug::Vec2d direction((corner & 1) ? 0.5 : -0.5, (corner & 2) ? -0.5 : 0.5);
  plug::Vec2d corner_pos = m_box->getPosition() + m_box->getSize() * direction;

  return stack.top().apply(corner_pos);
}

static inline bool isSmall(double a) { return fabs(a) < 1e-6; }

bool Widget::covers(plug::TransformStack& stack,
                    const plug::Vec2d&    position) const
{
  Vec2d local_pos = stack.restore(position);

  Vec2d size = getLayoutBox().getSize() * stack.top().getScale();;

  bool horizontal = (Eps < local_pos.x && size.x - Eps > local_pos.x);
  bool vertical   = (Eps < local_pos.y && size.y - Eps > local_pos.y);
  
  return horizontal & vertical;
}
