#include "LineTool.h"

#include "Impl/Widget/Widget.h"
#include "Impl/LayoutBox/BaseLayoutBox/BaseLayoutBox.h"

class LineToolPreview : public Widget
{
    public:
        LineToolPreview(const plug::Vec2d &begin_pos, const plug::Vec2d &end_pos, const plug::Color &color):
                        Widget(BaseLayoutBox(plug::Vec2d(0, 0), plug::Vec2d(1, 1), plug::Vec2d(1, 1), false, false)),
                        m_begin_pos(begin_pos), 
                        m_end_pos(end_pos),
                        m_color(color){}
        
        virtual ~LineToolPreview(){}

        virtual void draw(plug::TransformStack &stack, plug::RenderTarget &target)
        {
        
            plug::VertexArray line(plug::PrimitiveType::Lines, 2);

            line[0].position = stack.apply(m_begin_pos);
            line[1].position = stack.apply(m_end_pos);

            line[0].color = line[1].color = m_color;
            line[0].tex_coords = line[1].tex_coords = plug::Vec2d(0, 0);

            target.draw(line);
        }

    protected:
    
        virtual bool covers(plug::TransformStack &stack, const plug::Vec2d &position) const { return false; }
    
    private:
        const plug::Vec2d &m_begin_pos;
        const plug::Vec2d &m_end_pos; 
        const plug::Color &m_color;
};

LineTool::LineTool():
                DefTool("Line", "Plugins/LineTool/LineReleased.png"),
                m_color_palette(nullptr),
                m_canvas(nullptr), 
                m_active(false),
                m_begin_pos(0, 0), m_end_pos(0, 0), m_color(plug::Color(255, 255, 255)), 
                m_preview(new LineToolPreview(m_begin_pos, m_end_pos, m_color)){}

LineTool::~LineTool()
{
    delete m_preview;
}

void LineTool::setColorPalette(plug::ColorPalette &palette)
{
    m_color_palette = &palette;
}

void LineTool::setActiveCanvas(plug::Canvas &canvas)
{
    onCancel();
    m_canvas = &canvas;
}

void LineTool::onMainButton(const plug::ControlState &state, const plug::Vec2d &pos)
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

void LineTool::onMove(const plug::Vec2d &pos)
{
    if (!m_active) return;

    m_end_pos = pos;
}

void LineTool::onCancel(void)
{
    m_active = false;
    m_begin_pos = m_end_pos = plug::Vec2d(0, 0);
}

void LineTool::onConfirm(void)
{
    if (!m_canvas || !m_color_palette)
    {
        m_active = false;

        #ifdef DEBUG_PALGINS
        
        printf("Somthing is nullptr. Canva pointer:%p\n Color palette pointer%p\n:", m_canvas, m_color_palette);
        
        #endif
    }

    plug::VertexArray line(plug::PrimitiveType::Lines, 2);

    m_color = m_color_palette->getFGColor();

    line[0] = {m_begin_pos, Vec2d(0, 0), m_color};
    line[1] = {m_end_pos,   Vec2d(0, 0), m_color};

    m_begin_pos = m_end_pos = plug::Vec2d(0, 0);

    m_canvas->draw(line);

    m_active = false;
}

plug::Widget* LineTool::getWidget(void) 
{
    if (m_active)
        return m_preview;

    return nullptr;
};

plug::Plugin* loadPlugin(void)
{
    return new LineTool();
}