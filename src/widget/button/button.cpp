#include "button.h"


Button::Button (const char *released_texture_file, const char *covered_texture_file, 
                const char *pressed_texture_file,  const char *disabled_texture_file,
                const Action *action, 
                const Dot offset, const Vector scale):
                action_(nullptr), status_(RELEASED), prev_status_(RELEASED),
                released_texture_(), covered_texture_(), 
                pressed_texture_(), disabled_texture_(), 
                transform_({offset, scale}), width_(0), hieght_(0),
                covering_time_(0)
{
    assert(action != nullptr && "action is nullptr");

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

    return;

}

//================================================================================

void Button::Draw(sf::RenderTarget &target, Container<Transform> &stack_transform) const
{
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    Transform last_trf = stack_transform.GetBack();

    sf::VertexArray vertex_array(sf::Quads, 4);

    GetNewSize(vertex_array, last_trf);
    
    target.draw(vertex_array, DefineTexture());

    stack_transform.PopBack();

    return;
}

void Button::GetNewSize(sf::VertexArray &vertex_array, const Transform &transform) const
{
    vertex_array[0].texCoords = sf::Vector2f(0, 0);
    vertex_array[1].texCoords = sf::Vector2f((float)width_ - 1, 0);
    vertex_array[2].texCoords = sf::Vector2f((float)width_ - 1, (float)hieght_ - 1);
    vertex_array[3].texCoords = sf::Vector2f(0, (float)hieght_ - 1);
    
    vertex_array[0].position = transform.RollbackTransform({0, 0});
    vertex_array[1].position = transform.RollbackTransform({1, 0});
    vertex_array[2].position = transform.RollbackTransform({1, 1});
    vertex_array[3].position = transform.RollbackTransform({0, 1});

    return;
}

const sf::Texture* Button::DefineTexture() const
{
    switch (status_)
    {
        case RELEASED:
            return &released_texture_;

        case PRESSED:
            return &pressed_texture_;
    
        case DISABLED:
            return &disabled_texture_;

        case COVERED:
            return &covered_texture_;

        default:
            break;
    }

    return nullptr;
}

//================================================================================

bool Button::CheckIn(const Dot &mouse_pos) const
{
    bool horizontal = (Eps < mouse_pos.x && 1 - Eps > mouse_pos.x);
    bool vertical   = (Eps < mouse_pos.y && 1 - Eps > mouse_pos.y);
   
    return horizontal & vertical;
}

bool Button::OnMouseMoved(const int x, const int y, Container<Transform> &stack_transform)
{
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    Transform last_trf = stack_transform.GetBack();
    
    Dot new_coord = last_trf.ApplyTransform({(double)x, (double)y});

    bool flag = CheckIn(new_coord);

    if (!flag)
    { 
        covering_time_ = 0;
        status_ = prev_status_;
    }
    else
    {
        if (status_ != COVERED)
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
    if (status_ == COVERED && key == Left)
    {
        *action_;
        return true;
    }

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


