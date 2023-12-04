
#include "TextBox.h"

void TextBox::draw(plug::TransformStack &stack, plug::RenderTarget &target)
{   
    plug::Transform trf(getLayoutBox().getPosition(), Default_scale);
    stack.enter(trf);
    
    Transform last_trf = stack.top();
    plug::Vec2d pos = last_trf.apply(plug::Vec2d(0, 0));

    plug::Vec2d scale = last_trf.getScale();

    writeText(target, pos, m_buf, m_thicknesses * scale.x, m_color);

    plug::Color cursor_color = m_color;
    if (m_acume_time > 0.5f)
    {
        cursor_color = plug::Transparent;
    }

    double thicknesses_x = m_thicknesses * scale.x * plug::Symbol_width;
    double thicknesses_y = m_thicknesses * scale.y * plug::Symbol_height;

    drawRectangle(target,   plug::Vec2d(pos.x + thicknesses_x * m_cursor_pos_x      , pos.y + thicknesses_y + 2), 
                            plug::Vec2d(pos.x + thicknesses_x * (m_cursor_pos_x + 1), pos.y + thicknesses_y + 5), cursor_color);
  

    stack.leave();
}


void TextBox::onMousePressed(const plug::MousePressedEvent &event, plug::EHC &context)
{
    context.stopped = false;

    if (m_cnt_symbols == 0) return;

    plug::Transform trf(getLayoutBox().getPosition(), Default_scale);
    context.stack.enter(trf);

    plug::Transform last_trf = context.stack.top();
    plug::Vec2d local_pos = context.stack.restore(event.pos);

    plug::Vec2d scale = last_trf.getScale();

    double thicknesses_x =  m_thicknesses * scale.x * plug::Symbol_width;
    double thicknesses_y =  m_thicknesses * scale.y * plug::Symbol_height;

    if (local_pos.x > Eps && (int)(local_pos.x / thicknesses_x) <= static_cast<int>(m_cnt_symbols) &&
        local_pos.y > Eps && local_pos.y  < thicknesses_y - Eps)
    {
        m_cursor_pos_x = static_cast<size_t>(local_pos.x / thicknesses_x);
        context.stopped = true;
    }
    
    context.stack.leave();
}

void TextBox::onKeyboardPressed(const plug::KeyboardPressedEvent &event, plug::EHC &context)
{    
    plug::KeyCode key_code = event.key_id;

    bool flag = (key_code >= plug::KeyCode::A && key_code <= plug::KeyCode::Z)        || 
                (key_code >= plug::KeyCode::Num0 && key_code <= plug::KeyCode::Num9)  ||
                (key_code == plug::KeyCode::Left || key_code == plug::KeyCode::Right  || key_code == plug::KeyCode::Backspace);

    context.stopped = false;

    if (!flag) return;

    if (key_code == plug::KeyCode::Left)
    {
        if (m_cursor_pos_x > 0)
        {
            m_cursor_pos_x--;
        }

        context.stopped = true;
        return;
    }

    if (key_code == plug::KeyCode::Right)
    {
        if (m_cursor_pos_x < m_cnt_symbols)
        {
            m_cursor_pos_x++;
        }

        context.stopped = true;
        return;
    }
    
    if (key_code == plug::KeyCode::Backspace)
    {
        if (m_cnt_symbols == 0u || m_cursor_pos_x == 0u)
        {
            context.stopped = false;
            return;
        }
        
        m_cnt_symbols--;
        m_cursor_pos_x--;
        
        for (size_t it = m_cursor_pos_x; it < m_cnt_symbols; it++)
        {
            std::swap(m_buf[it], m_buf[it + 1]);
        }

        m_buf[m_cnt_symbols] = '\0';

        getLayoutBox().setSize(Vec2d(m_cnt_symbols, m_thicknesses));
        
        context.stopped = true;
        return;
    }

    if (m_cnt_symbols == m_limit_cnt_symbols)
    {
        context.stopped = false;
        return;
    }

    char symbol = '\0';
    if (key_code >= plug::KeyCode::A && key_code <= plug::KeyCode::Z)
    {
        if (event.shift)
            symbol = static_cast<size_t>(key_code) - static_cast<size_t>(plug::KeyCode::A) + 'A';
        else
            symbol = static_cast<size_t>(key_code) - static_cast<size_t>(plug::KeyCode::A) + 'a';
    }

    if (key_code >= plug::KeyCode::Num0 && key_code <= plug::KeyCode::Num9)
    {
        symbol = static_cast<size_t>(key_code) - static_cast<size_t>(plug::KeyCode::Num0) + '0';
    }

    for (size_t it = m_cnt_symbols; it >= m_cursor_pos_x + 1; it--)
    {
        std::swap(m_buf[it], m_buf[it - 1]);
    }

    m_buf[m_cursor_pos_x] = symbol;
    m_cursor_pos_x++;
    m_cnt_symbols++;

    getLayoutBox().setSize(Vec2d(m_cnt_symbols, m_thicknesses));

    context.stopped = true;
}

void TextBox::onTick(const plug::TickEvent &event, plug::EHC &context)
{
    m_acume_time += event.delta_time;

    if (m_acume_time > 1.0f)
    {
        m_acume_time = 0.0f;
    }
}

void TextBox::clear(void)
{
    for (size_t it = 0; it < m_limit_cnt_symbols; it++)
        m_buf[it] = '\0';
    
    m_cursor_pos_x = 0;
    m_cnt_symbols = 0;
}