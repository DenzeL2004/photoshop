#include "PolylineTool.h"

#include "Impl/Widget/Widget.h"
#include "Impl/LayoutBox/BaseLayoutBox/BaseLayoutBox.h"
#include "Impl/Util/Sfml.h"

class PolylineToolPreview : public Widget
{
    public:
        PolylineToolPreview(const plug::VertexArray &vertexs, const plug::Vec2d &mouse_pos):
                            Widget(BaseLayoutBox(plug::Vec2d(0, 0), plug::Vec2d(1, 1), plug::Vec2d(1, 1), false, false)),
                            m_vertexs(vertexs), 
                            m_mouse_pos(mouse_pos){}
        
        virtual ~PolylineToolPreview(){}

        virtual void draw(plug::TransformStack &stack, plug::RenderTarget &target)
        {
            plug::VertexArray vertexs(plug::PrimitiveType::LineStrip, 0);
            size_t size = m_vertexs.getSize();

            for (size_t it = 0; it < size; it++)
            {
                vertexs.appendVertex({stack.apply(m_vertexs[it].position), m_vertexs[it].tex_coords, m_vertexs[it].color});
            }
        
            if (size > 0)
            {
                vertexs.appendVertex({stack.apply(m_mouse_pos), plug::Vec2d(0, 0), m_vertexs[0].color});
            }
            target.draw(vertexs);
        }

    protected:
    
        virtual bool covers(plug::TransformStack &stack, const plug::Vec2d &position) const { return false; }
    
    private:
        const plug::VertexArray &m_vertexs;
        const plug::Vec2d &m_mouse_pos;
};

PolylineTool::PolylineTool():
                DefTool("PolylineTool", "Plugins/PolylineTool/PolylineTool.png"),
                m_color_palette(nullptr),
                m_canvas(nullptr), 
                m_active(false),
                m_vertexs(plug::PrimitiveType::LineStrip, 0), 
                m_mouse_pos(0, 0), 
                m_preview(new PolylineToolPreview(m_vertexs, m_mouse_pos)){}

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

    m_canvas->draw(m_vertexs);

    onCancel();
}

plug::Widget* PolylineTool::getWidget(void) 
{
    return m_preview;
};

plug::Plugin* loadPlugin(void)
{
    return new PolylineTool();
}