
#include "text_box.h"

void TextBox::draw(sf::RenderTarget &target, Container<Transform> &stack_transform)
{   
    plug::Transform trf(getLayoutBox().getPosition(), Default_scale);
    context.stack.enter(trf);
    
    Transform last_trf = stack_transform.getBack();
    Dot pos = last_trf.apply(Dot(0, 0));

    Vec2d scale = last_trf.getScale();

    double width_symbol = text.getLocalBounds().width / m_cnt_symbols;

    writeText(targetm )

    if (acume_time_ > 0.5f)
    {
        m_cursor_poscolor = plug::Transparent;
    }

    // drawRectangle(target,   Dot(pos.x + width_symbol * m_cursor_pos.x      , pos.y + m_thicknesses * scale.y + 2), 
    //                         Dot(pos.x + width_symbol * (m_cursor_pos.x + 1), pos.y + m_thicknesses * scale.y + 5), m_cursor_poscolor);
  

    stack_transform.popBack();
}

//================================================================================

void TextBox::onMousePressed(const plug::MousePressedEvent &event,plug::EHC &context)
{
    context.stopped = false;

    if (m_cnt_symbols == 0) return;

    plug::Transform trf(getLayoutBox().getPosition(), Default_scale);
    context.stack.enter(trf);

    //Transform last_trf = stack_transform.getBack();
    plug::Vec2d local_pos = context.stack.restore(pos);

    plug::Vec2d scale = last_trf.getScale();

    sf::Text text(buf, font_, m_thicknesses * scale.y);
    double width_symbol =  m_thicknesses * scale.y * plug::Symbol_width;

    if (local_pos.x > Eps && (int)(local_pos.x / width_symbol) <= (int)m_cnt_symbols &&
        local_pos.y > Eps && local_pos.y  < m_thicknesses * scale.y - Eps)
    {
        m_cursor_pos.x = (int)(local_pos.x / width_symbol);
        context.stopped = true;
    }
    
    context.stack.leave();
}

void TextBox::onKeyboardPressed(const plug::KeyboardPressedEvent &event, plug::EHC &context)
{
    plug::Transform trf(getLayoutBox().getPosition(), Default_scale);
    context.stack.enter(trf);
    
    plug::KeyCode key_code = event.key_id;

    bool flag = (key_code >= plug::KeyCode::A && key_code <= plug::KeyCode::Z)        || 
                (key_code >= plug::KeyCode::Num0 && key_code <= plug::KeyCode::Num9)  ||
                (key_code == plug::KeyCode::Left || key_code == plug::KeyCode::Right  || key_code == plug::KeyCode::BackSpace);

    context.stopped = false;

    if (!flag) return;

    if (key_code == plug::KeyCode::Left)
    {
        if (m_cursor_pos.x > 0)
        {
            m_cursor_pos.x--;
        }
        return true;
    }

    if (key_code == plug::KeyCode::Right)
    {
        if (m_cursor_pos.x < m_cnt_symbols)
        {
            m_cursor_pos.x++;
        }

        context.stopped = true;
        return;
    }
    
    if (key_code == plug::KeyCode::BackSpace)
    {
        if (m_cnt_symbols == 0.0 || m_cursor_pos.x == 0.0)
        {
            context.stopped = false;
            return;
        }
        
        m_cnt_symbols--;
        m_cursor_pos.x--;
        
        for (size_t it = m_cursor_pos.x; it < m_cnt_symbols; it++)
        {
            std::swap(buf[it], buf[it + 1]);
        }

        buf[m_cnt_symbols] = '\0';

        getLayoutBox().setSize(Vec2d(m_cnt_symbols, m_thicknesses));
        
        context.stopped = true;
        return;
    }

    if (m_cnt_symbols == limit_m_cnt_symbols)
    {
        context.stopped = false;
        return;
    }

    char symbol = '\0';
    if (key_code >= plug::KeyCode::A && key_code <= plug::KeyCode::Z)
    {
        if (event.shift)
            symbol = 'A' + key_code - plug::KeyCode::A;
        else
            symbol = 'a' + key_code - plug::KeyCode::A;
    }

    if (key_code >= plug::KeyCode::Num0 && key_code <= plug::KeyCode::Num9)
    {
        symbol = '0' + key_code - plug::KeyCode::Num0;
    }

    for (size_t it = m_cnt_symbols; it >= static_cast<size_t>(m_cursor_pos.x) + 1; it--)
    {
        std::swap(buf[it], buf[it - 1]);
    }

    buf[static_cast<size_t>(m_cursor_pos.x)] = symbol;
    m_cursor_pos.x += 1;
    m_cnt_symbols++;

    getLayoutBox().setSize(Vec2d(m_cnt_symbols, m_thicknesses));

    context.stopped = true;

    context.stack.leave();
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
        buf[it] = '\0';
    
    m_cursor_pos.x = 0.0;
    m_cnt_symbols = 0;
}