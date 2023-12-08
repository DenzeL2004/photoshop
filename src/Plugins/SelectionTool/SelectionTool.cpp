#include "SelectionTool.h"

#include "Impl/Widget/Widget.h"
#include "Impl/LayoutBox/BaseLayoutBox/BaseLayoutBox.h"

class SelectionToolPreview : public Widget
{
    public:
        SelectionToolPreview(const plug::Vec2d &begin_pos, const plug::Vec2d &end_pos, const plug::Color &color):
                        Widget(BaseLayoutBox(plug::Vec2d(0, 0), plug::Vec2d(1, 1), plug::Vec2d(1, 1), false, false)),
                        m_begin_pos(begin_pos), 
                        m_end_pos(end_pos),
                        m_color(color){}
        
        virtual ~SelectionToolPreview(){}

        virtual void draw(plug::TransformStack &stack, plug::RenderTarget &target)
        {
        
            plug::VertexArray rect(plug::PrimitiveType::LinesStrip, 5);

            plug::Vec2d new_begin_pos = stack.apply(m_begin_pos);
            plug::Vec2d new_end_pos   = stack.apply(m_end_pos);

            rect[0].position = rect[4].position = new_begin_pos;
            rect[1].position = plug::Vec2d(new_end_pos.x, new_begin_pos.y);
            rect[2].position = new_end_pos;
            rect[3].position = plug::Vec2d(new_begin_pos.x, new_end_pos.y);

            rect[0].color = rect[2].color = rect[4].color = m_color;
            rect[1].color = rect[3].color = m_color;

            
            target.draw(rect);
        }

    protected:
    
        virtual bool covers(plug::TransformStack &stack, const plug::Vec2d &position) const { return false; }
    
    private:
        const plug::Vec2d &m_begin_pos;
        const plug::Vec2d &m_end_pos; 
        const plug::Color &m_color;
};

SelectionTool::SelectionTool():
                DefTool("Selection", "Plugins/SelectionTool/SelectionReleased.png"),
                m_color_palette(nullptr),
                m_canvas(nullptr), 
                m_active(false),
                m_begin_pos(0, 0), m_end_pos(0, 0), m_color(plug::Color(255, 255, 255)), 
                m_preview(new SelectionToolPreview(m_begin_pos, m_end_pos, m_color)){}

SelectionTool::~SelectionTool()
{
    delete m_preview;
}

void SelectionTool::setColorPalette(plug::ColorPalette &palette)
{
    m_color_palette = &palette;
}

void SelectionTool::setActiveCanvas(plug::Canvas &canvas)
{
    m_canvas = &canvas;
}

void SelectionTool::onMainButton(const plug::ControlState &state, const plug::Vec2d &pos)
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

void SelectionTool::onMove(const plug::Vec2d &pos)
{
    if (!m_active) return;

    m_end_pos = pos;
}

void SelectionTool::onCancel(void)
{
    m_active = false;
    m_begin_pos = m_end_pos = plug::Vec2d(0, 0);
}

void SelectionTool::onConfirm(void)
{
    if (!m_canvas || !m_color_palette)
    {
        m_active = false;

        #ifdef DEBUG_PALGINS
        
        printf("Somthing is nullptr. Canva pointer:%p\n Color palette pointer%p\n:", m_canvas, m_color_palette);
        
        #endif
    }

    size_t begin_x = static_cast<size_t>(std::min(m_begin_pos.x, m_end_pos.x));
    size_t end_x   = static_cast<size_t>(std::max(m_begin_pos.x, m_end_pos.x));

    size_t begin_y = static_cast<size_t>(std::min(m_begin_pos.y, m_end_pos.y));
    size_t end_y   = static_cast<size_t>(std::max(m_begin_pos.y, m_end_pos.y));  

    plug::SelectionMask &mask = m_canvas->getSelectionMask();  

    mask.fill(false);
    for (size_t y = begin_y; y <= end_y; y++)
    {
        for (size_t x = begin_x; x <= end_x; x++)
        {
            mask.setPixel(x, y, true);
        }
    }

    m_active = false;
}

plug::Widget* SelectionTool::getWidget(void) 
{
    if (m_active)
        return m_preview;

    return nullptr;
};

plug::Plugin* loadPlugin(void)
{
    return new SelectionTool();
}