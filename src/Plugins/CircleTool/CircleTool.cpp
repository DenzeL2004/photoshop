#include "CircleTool.h"

#include "Impl/Widget/Widget.h"
#include "Impl/LayoutBox/BaseLayoutBox/BaseLayoutBox.h"

static void drawCircle( plug::VertexArray &form, 
                        const plug::Vec2d &begin,  const plug::Vec2d &end,  
                        const bool type,
                        const plug::Color color);

class CircleToolPreview : public Widget
{
    public:
        CircleToolPreview(  const plug::Vec2d &begin_pos, const plug::Vec2d &end_pos, const plug::Color &color, 
                            bool &m_modifier1):
                            Widget(BaseLayoutBox(plug::Vec2d(0, 0), plug::Vec2d(1, 1), plug::Vec2d(1, 1), false, false)),
                            m_begin_pos(begin_pos), 
                            m_end_pos(end_pos),
                            m_color(color),
                            m_modifier1(m_modifier1){}
        
        virtual ~CircleToolPreview(){}

        virtual void draw(plug::TransformStack &stack, plug::RenderTarget &target)
        {        
            plug::VertexArray circle(plug::PrimitiveType::LineStrip, 0);

            plug::Vec2d new_begin_pos = stack.apply(m_begin_pos);
            plug::Vec2d new_end_pos   = stack.apply(m_end_pos);

            drawCircle(circle, new_begin_pos, new_end_pos, m_modifier1, m_color);

            target.draw(circle);
        }

    protected:
    
        virtual bool covers(plug::TransformStack &stack, const plug::Vec2d &position) const { return false; }
    
    private:
        const plug::Vec2d &m_begin_pos;
        const plug::Vec2d &m_end_pos; 
        const plug::Color &m_color;

        const bool &m_modifier1;
};

CircleTool::CircleTool():
                DefTool("Circle", "Plugins/CircleTool/CircleReleased.png"),
                m_color_palette(nullptr),
                m_canvas(nullptr), 
                m_active(false),
                m_begin_pos(0, 0), m_end_pos(0, 0), m_color(plug::Color(255, 255, 255)),
                m_radius_a(0.0), m_radius_b(0.0), 
                m_modifier1(false),
                m_preview(new CircleToolPreview(m_begin_pos, m_end_pos, m_color, m_modifier1))
                {}

CircleTool::~CircleTool()
{
    delete m_preview;
}

void CircleTool::setColorPalette(plug::ColorPalette &palette)
{
    m_color_palette = &palette;
}

void CircleTool::setActiveCanvas(plug::Canvas &canvas)
{
    onCancel();
    m_canvas = &canvas;
}

void CircleTool::onMainButton(const plug::ControlState &state, const plug::Vec2d &pos)
{
    if (m_active && state.state == plug::State::Released)
    {
        onConfirm();
    }

    if (!m_active && state.state == plug::State::Pressed)
    {
        m_begin_pos = m_end_pos = pos;

        m_active = true;

        if (!m_color_palette)
        {
            m_active = false;

            #ifdef DEBUG_PALGINS
            
            printf("Color palette is nullptr");
            
            #endif
        }

        m_color = m_color_palette->getFGColor();
    }
}

void CircleTool::onMove(const plug::Vec2d &pos)
{
    if (!m_active) return;

    m_end_pos = pos;
}

void CircleTool::onCancel(void)
{
    m_active = false;
    m_begin_pos = m_end_pos = plug::Vec2d(0, 0);
    m_radius_a = m_radius_b = 0;
}

void CircleTool::onConfirm(void)
{
    if (!m_canvas || !m_color_palette)
    {
        m_active = false;

        #ifdef DEBUG_PALGINS
        
        printf("Somthing is nullptr. Canva pointer:%p\n Color palette pointer%p\n:", m_canvas, m_color_palette);
        
        #endif
    }
    m_color = m_color_palette->getFGColor();

    plug::VertexArray circle(plug::PrimitiveType::LineStrip, 0);
    drawCircle(circle, m_begin_pos, m_end_pos, m_modifier1, m_color);

    m_canvas->draw(circle);

    onCancel();
}

void CircleTool::onModifier1(const plug::ControlState &state)
{
    if (state.state == plug::State::Pressed)
    {
        m_modifier1 = true;
    }

    if (state.state == plug::State::Released)
    {
        m_modifier1 = false;
    }
}

plug::Widget* CircleTool::getWidget(void) 
{
    if (m_active)
        return m_preview;

    return nullptr;
};

plug::Plugin* loadPlugin(void)
{
    return new CircleTool();
}

static void drawCircle( plug::VertexArray &form, 
                        const plug::Vec2d &begin,  const plug::Vec2d &end,  
                        const bool type,
                        const plug::Color color)
{
    const size_t cnt = 360;

    form.resize(0);

    double radius_a = fabs(begin.x - end.x);
    double radius_b = fabs(begin.y - end.y);   

    if (type)
    {
        radius_a = radius_b = (begin - end).length();
    } 

    double step = 2.0 * M_PI / static_cast<double>(cnt);

    double alpha = 0;
    for (size_t it = 0; it <= cnt; it++)
    {
        form.appendVertex({plug::Vec2d(cos(alpha) * radius_a + begin.x, sin(alpha) * radius_b + begin.y), Vec2d(0, 0), color});
        alpha += step;
    }
}