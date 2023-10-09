#include "button.h"


Button::Button (const char *released_texture_file, const char *covered_texture_file, 
                const char *pressed_texture_file,  const char *disabled_texture_file,
                const Action *action, const Dot offset, 
                const double scale_x, const double scale_y):
                action_(nullptr), status_(RELEASED), prev_status_(RELEASED),
                released_texture_(), covered_texture_(), 
                pressed_texture_(), disabled_texture_(), 
                transform_(), width_(0), hieght_(0),
                covering_time_(0)
{
    //assert(action != nullptr && "action is nullptr");

    if (!released_texture_.loadFromFile(released_texture_file))   
    {
        PROCESS_ERROR(LOAD_TEXTURE_ERR, "failed load teture from %s\n", released_texture_file);
        return;
    }

    if (!covered_texture_.loadFromFile(covered_texture_file))   
    {
        PROCESS_ERROR(LOAD_TEXTURE_ERR, "failed load teture from %s\n", covered_texture_file);
        return;
    }

    if (!pressed_texture_.loadFromFile(pressed_texture_file))   
    {
        PROCESS_ERROR(LOAD_TEXTURE_ERR, "failed load teture from %s\n", pressed_texture_file);
        return;
    }

    if (!disabled_texture_.loadFromFile(disabled_texture_file))   
    {
        PROCESS_ERROR(LOAD_TEXTURE_ERR, "failed load teture from %s\n", disabled_texture_file);
        return;
    }

    width_  = released_texture_.getSize().x;
    hieght_ = released_texture_.getSize().y;

    transform_.offset_ = offset;

    transform_.scale_ = Vector(scale_x / width_,
                               scale_y / hieght_);

    return;

}

//================================================================================

void Button::Draw(sf::RenderTarget &target, Container<Transform> &stack_transform) const
{
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    Transform res_transform = stack_transform.GetBack();

    sf::Sprite sprite = {};
    DefineSprite(sprite);

    sprite.setPosition((float)res_transform.offset_.GetX(), (float)res_transform.offset_.GetY());
    sprite.setScale   ((float)res_transform.scale_.GetX(),  (float)res_transform.scale_.GetY());

    target.draw(sprite);

    stack_transform.PopBack();

    return;
}

void Button::DefineSprite(sf::Sprite &sprite) const
{
    // if (covering_time_ > 0 && status_ != COVERED)
    // {
    //     sprite.setTexture(covered_texture_);

    //     uint8_t alpha = (uint8_t)std::min(254l, covering_time_ / 1500);
    //     sprite.setColor(sf::Color(255, 255, 255, alpha));
    //     return;
    // }

    switch (status_)
    {
        case RELEASED:
            sprite.setTexture(released_texture_);
            break;

        case PRESSED:
            sprite.setTexture(pressed_texture_);
            break;
    
        case DISABLED:
            sprite.setTexture(disabled_texture_);
            break;

        case COVERED:
            sprite.setTexture(covered_texture_);
            break;

        default:
            break;
    }

    return;
}

//================================================================================

bool Button::CheckIn(const Dot &mouse_pos) const
{
    bool horizontal = (0 <= mouse_pos.GetX() && width_  >= mouse_pos.GetX());
    bool vertical   = (0 <= mouse_pos.GetY() && hieght_ >= mouse_pos.GetY());
   
    return horizontal & vertical;
}

bool Button::OnMouseMoved(const int x, const int y, Container<Transform> &stack_transform)
{
    Dot mouse_coord((double)x, double(y));
   
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    Transform res_transform = stack_transform.GetBack();
    
    Dot new_coord = res_transform.ApplyTransform(mouse_coord);

    bool flag = CheckIn(new_coord);

    if (!flag)
    { 
        covering_time_ = 0;
        status_ = prev_status_;
    }
    else
    {
        if (covering_time_ / 1000 >= 255 && status_ != COVERED)
        {
            prev_status_ = status_;
            status_ = COVERED;
        }
    }

    stack_transform.PopBack();

    return flag;
}


//================================================================================


void Button::PassTime(const time_t delta_time)
{
    covering_time_ += delta_time;
    return;
}

//================================================================================


bool Button::OnMousePressed(const MouseKey key, Container<Transform> &stack_transform)
{
    printf("Button: mouse pressed\n");
    return false;
}


bool Button::OnMouseReleased(const MouseKey key, Container<Transform> &stack_transform)
{
    printf("Button: mouse released\n");
    return false;
}

bool Button::OnKeyboardPressed(const KeyboardKey key)
{
    printf("Button: mouse keyboard kye pressed\n");
    return false;
}


bool Button::OnKeyboardReleased(const KeyboardKey key)
{
    printf("Button: mouse keyboard kye released\n");
    return false;
}