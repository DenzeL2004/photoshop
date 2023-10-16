#include "button.h"


Button::Button (const char *released_texture_file, const char *covered_texture_file, 
                const char *pressed_texture_file,  const char *disabled_texture_file,
                const Action *action, 
                const Dot &offset, const Vector &scale):
                action_(action), state_(Released), prev_state_(Released),
                released_texture_(), covered_texture_(), 
                pressed_texture_(), disabled_texture_(), 
                transform_({offset, scale}), width_(0), hieght_(0),
                covering_time_(0)
{

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

void Button::Draw(sf::RenderTarget &target, Container<Transform> &stack_transform)
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
    switch (state_)
    {
        case  Button::Button_State::Released:
            return &released_texture_;

        case  Button::Button_State::Pressed:
            return &pressed_texture_;
    
        case  Button::Button_State::Disabled:
            return &disabled_texture_;

        case  Button::Button_State::Covered:
            if (prev_state_ == Button::Button_State::Pressed)
                return &pressed_texture_;
            else
                return &covered_texture_;

        default:
            break;
    }

    return nullptr;
}


bool Button::OnMouseMoved(const double x, const double y, Container<Transform> &stack_transform)
{
    if (state_ ==  Button::Button_State::Disabled)
        return false;

    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    Transform last_trf = stack_transform.GetBack();
    
    Dot new_coord = last_trf.ApplyTransform({x, y});
    stack_transform.PopBack();

    bool flag = CheckIn(new_coord);

    if (!flag)
    { 
        covering_time_ = 0;
        state_ = prev_state_;
        
    }
    else
    {
        if (state_ !=  Button::Button_State::Covered)
        {
            prev_state_ = state_;
            state_ =  Button::Button_State::Covered;
        }
    }

    return flag;
}

//================================================================================

bool Button::OnMousePressed(const double x, const double y, const MouseKey key, Container<Transform> &stack_transform)
{
    if (state_ == Button::Button_State::Disabled)
        return false;

    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    Transform last_trf = stack_transform.GetBack();
    
    Dot new_coord = last_trf.ApplyTransform({x, y});

    bool flag = CheckIn(new_coord);

    if (flag && key == Left)
    {
        if (action_ != nullptr) (*action_)();
        state_ = Button::Button_State::Pressed;
    }
    else
    {
        flag = false;
        state_ = Button::Button_State::Released;
    }

    stack_transform.PopBack();

    return flag;
}

//================================================================================

bool Button::OnMouseReleased(const double x, const double y, const MouseKey key, Container<Transform> &stack_transform)
{
    if (state_ == Button::Button_State::Disabled)
        return false;

    state_ = Button::Button_State::Released;
    prev_state_ = Button::Button_State::Released;

    return true;
}

//================================================================================

bool Button::OnKeyboardPressed(const KeyboardKey key)
{
    printf("Button: mouse keyboard kye pressed\n");
    return false;
}

//================================================================================

bool Button::OnKeyboardReleased(const KeyboardKey key)
{
    printf("Button: mouse keyboard kye released\n");
    return false;
}

//================================================================================

void Button::PassTime(const time_t delta_time)
{
    covering_time_ += delta_time;
    return;
}


void Button::SetTransform (const Transform &transform)
{
    transform_ = transform;
}

//================================================================================

void ButtonList::Draw(sf::RenderTarget &target, Container<Transform> &stack_transform)
{
    Button::Draw(target, stack_transform);
    
    size_t size = buttons_.GetSize();
    for (size_t it = 0; it < size; it++)
    {
        if (buttons_[it]->state_ != Button::Button_State::Disabled)
            buttons_[it]->Draw(target, stack_transform); 
    }
}

//================================================================================

bool ButtonList::OnMouseMoved(const double x, const double y, Container<Transform> &stack_transform)
{
    if (state_ ==  Button::Button_State::Disabled)
        return false;

    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    Transform last_trf = stack_transform.GetBack();
    
    Dot new_coord = last_trf.ApplyTransform({x, y});
    stack_transform.PopBack();

    bool flag = CheckIn(new_coord);

    if (!flag)
    { 
        covering_time_ = 0;
        state_ = prev_state_;
    }
    else
    {
        if (state_ !=  Button::Button_State::Covered)
        {
            prev_state_ = state_;
            state_ =  Button::Button_State::Covered;
        }
    }


    size_t size = buttons_.GetSize();
    for (size_t it = 0; it < size; it++)
    {
        if (state_ == Button::Button_State::Covered || state_ == Button::Button_State::Pressed)
        {
            buttons_[it]->state_ = buttons_[it]->prev_state_;
            buttons_[it]->OnMouseMoved(x, y, stack_transform);
        }
        else
            buttons_[it]->state_ = Button::Button_State::Disabled;

            
    }
    
    return flag;
}

//================================================================================

bool ButtonList::OnMousePressed(const double x, const double y, const MouseKey key, Container<Transform> &stack_transform)
{
    if (state_ == Button::Button_State::Disabled)
        return false;
    
    bool flag = false;
    
    if (state_ == Button::Button_State::Pressed)
    {
        size_t size = buttons_.GetSize();

        int last_presed = -1;
        for (size_t it = 0; it < size; it++)
        {
            if (buttons_[it]->state_ == Button::Button_State::Pressed) last_presed = it;
            flag |= buttons_[it]->OnMousePressed(x, y, key, stack_transform);
            

            buttons_[it]->prev_state_ = buttons_[it]->state_;
            buttons_[it]->state_ = Button::Button_State::Disabled;
        }

        if (!flag && last_presed != -1)
            buttons_[last_presed]->prev_state_ = Button::Button_State::Pressed;


        state_      = Button::Button_State::Released;
        prev_state_ = Button::Button_State::Released;
        
    }
   
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    Transform last_trf = stack_transform.GetBack();
    
    Dot new_coord = last_trf.ApplyTransform({x, y});

    flag = CheckIn(new_coord);
    stack_transform.PopBack();

    if (flag && state_ != Button::Button_State::Pressed)
    {
        if (key == Left)
        {
            if (action_ != nullptr) (*action_)();
            state_ =  Button::Button_State::Pressed;
        }
    }
    else
        state_ =  Button::Button_State::Released;
    

    return flag;
}

//================================================================================


bool ButtonList::OnMouseReleased(const double x, const double y, const MouseKey key, Container<Transform> &stack_transform)
{
    if (state_ == Button::Button_State::Disabled)
        return false;

    // if (state_ == Button::Button_State::Released)
    // {
    //     size_t size = buttons_.GetSize();
    //     for (size_t it = 0; it < size; it++)
    //     {
    //         buttons_[it]->prev_state_ = buttons_[it]->state_;
    //         buttons_[it]->state_ = Button::Button_State::Disabled;       
    //     }
    // }

    return true;
}

//================================================================================

bool ButtonList::OnKeyboardPressed(const KeyboardKey key)
{
    printf("ButtonList: mouse keyboard kye pressed\n");
    return false;
}

//================================================================================

bool ButtonList::OnKeyboardReleased(const KeyboardKey key)
{
    printf("ButtonList: mouse keyboard kye released\n");
    return false;
}

//================================================================================

void ButtonList::PassTime(const time_t delta_time)
{
    covering_time_ += delta_time;
}