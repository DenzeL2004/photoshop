#include "RectTool.h"

#include "Impl/Widget/Widget.h"
#include "Impl/LayoutBox/BaseLayoutBox/BaseLayoutBox.h"


static void drawRect(   plug::VertexArray &form, 
                        const plug::Vec2d &begin, const plug::Vec2d &end,  
                        const bool type,
                        const plug::Color color);

class RectToolPreview : public Widget
{
    public:
        RectToolPreview(const plug::Vec2d &begin_pos, const plug::Vec2d &end_pos, const plug::Color &color, 
                        const bool &modifier1):
                        Widget(BaseLayoutBox(plug::Vec2d(0, 0), plug::Vec2d(1, 1), plug::Vec2d(1, 1), false, false)),
                        m_begin_pos(begin_pos), 
                        m_end_pos(end_pos),
                        m_color(color), 
                        m_modifier1(modifier1){}
        
        virtual ~RectToolPreview(){}

        virtual void draw(plug::TransformStack &stack, plug::RenderTarget &target)
        {
            plug::VertexArray rect(plug::PrimitiveType::LinesStrip);

            plug::Vec2d new_begin_pos = stack.apply(m_begin_pos);
            plug::Vec2d new_end_pos   = stack.apply(m_end_pos);

            drawRect(rect, new_begin_pos, new_end_pos, m_modifier1, m_color);
            
            target.draw(rect);
        }

    protected:
    
        virtual bool covers(plug::TransformStack &stack, const plug::Vec2d &position) const { return false; }
    
    private:
        const plug::Vec2d &m_begin_pos;
        const plug::Vec2d &m_end_pos; 
        const plug::Color &m_color;

        const bool &m_modifier1;
};

RectTool::RectTool():
                DefTool("Rect", "Plugins/RectTool/RectReleased.png"),
                m_color_palette(nullptr),
                m_canvas(nullptr), 
                m_active(false),
                m_begin_pos(0, 0), m_end_pos(0, 0), m_color(plug::Color(255, 255, 255)),
                m_modifier1(false), 
                m_preview(new RectToolPreview(m_begin_pos, m_end_pos, m_color,  m_modifier1)){}

RectTool::~RectTool()
{
    delete m_preview;
}

void RectTool::setColorPalette(plug::ColorPalette &palette)
{
    m_color_palette = &palette;
}

void RectTool::setActiveCanvas(plug::Canvas &canvas)
{
    m_canvas = &canvas;
}

void RectTool::onModifier1(const plug::ControlState &state)
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

void RectTool::onMainButton(const plug::ControlState &state, const plug::Vec2d &pos)
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

void RectTool::onMove(const plug::Vec2d &pos)
{
    if (!m_active) return;

    m_end_pos = pos;
}

void RectTool::onCancel(void)
{
    m_active = false;
    m_begin_pos = m_end_pos = plug::Vec2d(0, 0);
}

void RectTool::onConfirm(void)
{
    if (!m_canvas || !m_color_palette)
    {
        m_active = false;

        #ifdef DEBUG_PALGINS
        
        printf("Somthing is nullptr. Canva pointer:%p\n Color palette pointer%p\n:", m_canvas, m_color_palette);
        
        #endif
    }

    plug::VertexArray rect(plug::PrimitiveType::LinesStrip);
    drawRect(rect, m_begin_pos, m_end_pos, m_modifier1, m_color);

    m_canvas->draw(rect);

    m_active = false;
}

plug::Widget* RectTool::getWidget(void) 
{
    if (m_active)
        return m_preview;

    return nullptr;
};

plug::Plugin* loadPlugin(void)
{
    return new RectTool();
}

static void drawRect(   plug::VertexArray &form, 
                        const plug::Vec2d &begin, const plug::Vec2d &end,  
                        const bool type,
                        const plug::Color color)
{
    double width  = fabs(end.x - begin.x);
    double height = fabs(end.y - begin.y);

    if (type)
    {
        width = height = std::min(width, height);
    }

    plug::Vec2d pos(std::min(begin.x, end.x), std::min(begin.y, end.y));

    form.resize(5);

    form[0].position = form[4].position = pos;
    form[1].position = plug::Vec2d(pos.x + width, pos.y);
    form[2].position = plug::Vec2d(pos.x + width, pos.y + height);
    form[3].position = plug::Vec2d(pos.x, pos.y + height);

    form[0].color = form[2].color = form[4].color = color;
    form[1].color = form[3].color = color;
}