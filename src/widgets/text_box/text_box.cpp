
#include "text_box.h"

TextBox::TextBox(   const size_t limit_cnt_symbols, const size_t thicknesses, const sf::Color *color, 
                    const Vec2d &pos, 
                    const Widget *parent, const Vec2d &parent_size,
                    const Vec2d &origin, const Vec2d &scale):
                    Widget(Vec2d(0, thicknesses), pos, parent, parent_size, origin, scale), 
                    font_(),  
                    thicknesses_(thicknesses), color_(*color), 
                    cnt_symbols_(0), limit_cnt_symbols_(limit_cnt_symbols), 
                    buf_(new char[limit_cnt_symbols_]), cursor_(), acume_time_(0)
{

    if (!font_.loadFromFile("src/graphic/font/Anonymous_Pro_B.ttf"))
    {
        PROCESS_ERROR(ERR_FILE_OPEN, "load font from file failed\n");
        return;
    }    

    for (size_t it = 0; it < limit_cnt_symbols_; it++)
        buf_[it] = '\0';
}


void TextBox::draw(sf::RenderTarget &target, Container<Transform> &stack_transform)
{   
    Transform trf(getLayoutBox().getPosition(), scale_);
    stack_transform.pushBack(trf.combine(stack_transform.getBack()));
    
    Transform last_trf = stack_transform.getBack();
    Dot pos = last_trf.apply(Dot(0, 0));

    Vec2d scale = last_trf.getScale();

    sf::Text text(buf_, font_, thicknesses_ * scale.y);
    text.setFillColor(color_);
    text.setPosition((float)pos.x, (float)pos.y);

    double width_symbol = text.getLocalBounds().width / cnt_symbols_;

    target.draw(text);

    sf::Color cursor_color = color_;
    if (acume_time_ > 0.5f)
    {
        cursor_color = sf::Color::Transparent;
    }

    drawRectangle(target,   Dot(pos.x + width_symbol * cursor_.x      , pos.y + thicknesses_ * scale.y + 2), 
                            Dot(pos.x + width_symbol * (cursor_.x + 1), pos.y + thicknesses_ * scale.y + 5), cursor_color);
  

    stack_transform.popBack();
}


sf::Text TextBox::getText()
{
    return sf::Text(buf_, font_, thicknesses_);
}

//================================================================================

bool TextBox::onMousePressed(const Vec2d &pos, const MouseKey key, Container<Transform> &stack_transform)
{
    if (cnt_symbols_ == 0) return false;

    LayoutBox *layout_box = &getLayoutBox();

    Transform trf(layout_box->getPosition(), scale_);
    stack_transform.pushBack(trf.combine(stack_transform.getBack()));
    
    Transform last_trf = stack_transform.getBack();
    Dot local_pos = last_trf.restore(pos);

    Vec2d scale = last_trf.getScale();

    sf::Text text(buf_, font_, thicknesses_ * scale.y);
    double width_symbol = text.getLocalBounds().width / cnt_symbols_;

    bool flag = false;

    if (local_pos.x > Eps && (int)(local_pos.x / width_symbol) <= (int)cnt_symbols_ &&
        local_pos.y > Eps && local_pos.y  < thicknesses_ * scale.y - Eps)
    {
        cursor_.x = (int)(local_pos.x / width_symbol);
        flag = true;
    }
    
    stack_transform.popBack();

    return flag;
}

//================================================================================

bool TextBox::onKeyboardPressed  (const KeyboardKey key)
{
    int key_code = getKeyCode(key);

    bool flag = (key_code >= sf::Keyboard::A && key_code <= sf::Keyboard::Z)        || 
                (key_code >= sf::Keyboard::Num0 && key_code <= sf::Keyboard::Num9)  ||
                (key_code == sf::Keyboard::Left || key_code == sf::Keyboard::Right  || key_code == sf::Keyboard::BackSpace);

    if (!flag) return false;


    if (key_code == sf::Keyboard::Left)
    {
        if (cursor_.x > 0)
        {
            cursor_.x--;
        }
        return true;
    }

    if (key_code == sf::Keyboard::Right)
    {
        if (cursor_.x < cnt_symbols_)
        {
            cursor_.x++;
        }
        return true;
    }
    
    if (key_code == sf::Keyboard::BackSpace)
    {
        if (cnt_symbols_ == 0.0 || cursor_.x == 0.0) return false;
        
        cnt_symbols_--;
        cursor_.x--;
        
        for (size_t it = cursor_.x; it < cnt_symbols_; it++)
        {
            std::swap(buf_[it], buf_[it + 1]);
        }

        buf_[cnt_symbols_] = '\0';

        getLayoutBox().setSize(Vec2d(cnt_symbols_, thicknesses_));
        return true;
        
    }

    if (cnt_symbols_ == limit_cnt_symbols_)
        return false;

    char symbol = '\0';
    if (key_code >= sf::Keyboard::A && key_code <= sf::Keyboard::Z)
    {
        if (isShiftPressed(key))
            symbol = 'A' + key_code - sf::Keyboard::A;
        else
            symbol = 'a' + key_code - sf::Keyboard::A;
    }

    if (key_code >= sf::Keyboard::Num0 && key_code <= sf::Keyboard::Num9)
    {
        symbol = '0' + key_code - sf::Keyboard::Num0;
    }

    for (size_t it = cnt_symbols_; it >= (size_t)cursor_.x + 1; it--)
    {
        std::swap(buf_[it], buf_[it - 1]);
    }

    buf_[(size_t)cursor_.x] = symbol;
    cursor_.x++;
    cnt_symbols_++;

    getLayoutBox().setSize(Vec2d(cnt_symbols_, thicknesses_));

    return true;
}

bool TextBox::onKeyboardReleased (const KeyboardKey key)
{
    return false;
}

bool TextBox::onTick (const float delta_time)
{
    acume_time_ += delta_time;

    if (acume_time_ > 1.0f)
        acume_time_ = 0.0f;

    return false;
}

void TextBox::clear()
{
    for (size_t it = 0; it < limit_cnt_symbols_; it++)
        buf_[it] = '\0';
    
    cursor_.x = 0.0;
    cnt_symbols_ = 0;
}