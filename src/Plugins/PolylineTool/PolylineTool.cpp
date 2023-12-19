#include "PolylineTool.h"

#include "Impl/Widget/Widget.h"
#include "Impl/LayoutBox/BaseLayoutBox/BaseLayoutBox.h"
#include "Impl/Util/Sfml.h"
#include "Impl/Graphic/Graphic.h"

class PolylineToolPreview : public Widget
{
    public:
        PolylineToolPreview(const plug::VertexArray &vertexs, const plug::Vec2d &mouse_pos, const double &radius):
                            Widget(BaseLayoutBox(plug::Vec2d(0, 0), plug::Vec2d(1, 1), plug::Vec2d(1, 1), false, false)),
                            m_vertexs(vertexs), 
                            m_mouse_pos(mouse_pos), 
                            m_radius(radius){}
        
        virtual ~PolylineToolPreview(){}

        virtual void draw(plug::TransformStack &stack, plug::RenderTarget &target)
        {
            plug::VertexArray vertexs(plug::PrimitiveType::LineStrip, 0);
            size_t size = m_vertexs.getSize();

            for (size_t it = 0; it < size; it++)
            {
                vertexs.appendVertex({stack.apply(m_vertexs[it].position), m_vertexs[it].tex_coords, m_vertexs[it].color});
            }
        
            plug::Color color(0, 0, 0);
            if (size > 0)
            {
                vertexs.appendVertex({stack.apply(m_mouse_pos), plug::Vec2d(0, 0), m_vertexs[0].color});
                color = m_vertexs[0].color;
            }

            drawCircle(target, stack.apply(m_mouse_pos), m_radius, plug::PrimitiveType::LinesStrip, color);
            
            target.draw(vertexs);
        }

    protected:
    
        virtual bool covers(plug::TransformStack &stack, const plug::Vec2d &position) const { return false; }
    
    private:
        const plug::VertexArray &m_vertexs;
        const plug::Vec2d &m_mouse_pos;
        const double &m_radius;
};

PolylineTool::PolylineTool():
                DefTool("PolylineTool", "Plugins/PolylineTool/PolylineTool.png"),
                m_color_palette(nullptr),
                m_canvas(nullptr), 
                m_active(false),
                m_vertexs(plug::PrimitiveType::LineStrip, 0), 
                m_mouse_pos(0, 0), 
                m_color(),
                m_radius(5.),
                m_preview(new PolylineToolPreview(m_vertexs, m_mouse_pos, m_radius)), 
                m_setting_flags(false), 
                m_setting_radius(m_radius){}

PolylineTool::~PolylineTool()
{
    delete m_preview;
}

void PolylineTool::setColorPalette(plug::ColorPalette &palette)
{
    m_color_palette = &palette;
}

void PolylineTool::setActiveCanvas(plug::Canvas &canvas)
{
    onCancel();
    m_canvas = &canvas;
}

void PolylineTool::onMainButton(const plug::ControlState &state, const plug::Vec2d &pos)
{
    if (m_active && state.state == plug::State::Released)
    {
        m_active = false;
    }

    if (!m_active && state.state == plug::State::Pressed)
    {
        m_active = true;

        if (!m_color_palette)
        {
            m_active = false;

            #ifdef DEBUG_PALGINS
            
            fprintf(stderr, "Color palette is nullptr");
            
            #endif
        }

        m_color = m_color_palette->getFGColor();
        m_vertexs.appendVertex({pos, plug::Vec2d(0, 0), m_color});
        m_mouse_pos = pos;
    }
}

void PolylineTool::onMove(const plug::Vec2d &pos)
{
    size_t cnt = m_vertexs.getSize();

    m_mouse_pos = pos;

    if (cnt > 0 && !checkColors(m_color, m_vertexs[0].color))
    {
        for (size_t it = 0; it < cnt; it++)
        {
            m_vertexs[it].color = m_color;
        }
    }
}

void PolylineTool::onCancel(void)
{
    m_active = false;

    m_mouse_pos = plug::Vec2d(0, 0);
    m_vertexs.resize(0);
}

void PolylineTool::onConfirm(void)
{
    if (!m_canvas || !m_color_palette)
    {
        m_active = false;

        #ifdef DEBUG_PALGINS
        
        sprintf(stderr, "Somthing is nullptr. Canva pointer:%p\n Color palette pointer%p\n:", m_canvas, m_color_palette);
        
        #endif
    }

    drawLine();
    onCancel();
}

void PolylineTool::drawLine(void)
{
    if (!m_canvas || !m_color_palette)
    {
        m_active = false;

        #ifdef DEBUG_PALGINS
        
        sprintf(stderr, "Somthing is nullptr. Canva pointer:%p\n Color palette pointer%p\n:", m_canvas, m_color_palette);
        
        #endif
    }

    size_t size = m_vertexs.getSize();

    for (size_t it = 1; it < size; it++)
    {
        const size_t      point_count = 20;
        plug::Vec2d end = m_vertexs[it].position, start = m_vertexs[it - 1].position;
        const plug::Vec2d direction = end - start;

        plug::VertexArray array(plug::TriangleFan, point_count + 1);

        for (size_t i = 0; i < point_count; ++i)
        {
            const double      angle = i * (2 * M_PI / point_count);
            const plug::Vec2d offset(cos(angle), sin(angle));

            if (dot(offset, direction) < 0)
            {
            array[i] = plug::Vertex{.position   = start + m_radius * offset,
                                    .tex_coords = plug::Vec2d(),
                                    .color      = m_color};
            }
            else
            {
            array[i] = plug::Vertex{.position   = end + m_radius * offset,
                                    .tex_coords = plug::Vec2d(),
                                    .color      = m_color};
            }
        }

        array[point_count] = array[0];

        m_canvas->draw(array);
    }

    onCancel();
}

void PolylineTool::onSecondaryButton(const plug::ControlState &state, const plug::Vec2d &position)
{
    if (!m_active) return;
    
    if (state.state == plug::State::Pressed)
    {
        m_setting_flags = true;
        m_setting_radius = m_radius;
    }
}

plug::Widget* PolylineTool::getWidget(void) 
{
    return m_preview;
};

plug::Plugin* loadPlugin(void)
{
    return new PolylineTool();
}