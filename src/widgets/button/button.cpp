#include "button.h"


Button::Button (const char *released_texture_file, const char *covered_texture_file, 
                const char *pressed_texture_file,  const char *disabled_texture_file,
                const Action *action, 
                const Vector &size, const Vector &parent_size,
                const Vector &pos, const Widget *parent, 
                const Vector &origin, const Vector &scale):
                action_(action), 
                state_(ButtonState::RELEASED), prev_state_(ButtonState::RELEASED),
                released_texture_(), covered_texture_(), 
                pressed_texture_(), disabled_texture_(), 
                Widget(size, parent_size, pos, parent, origin, scale),
                covering_time_(0)
{
    setLayoutBox(*(new BaseLayoutBox(pos, size, parent_size, false, true)));   

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

    return;

}

//================================================================================

void Button::draw(sf::RenderTarget &target, Container<Transform> &stack_transform)
{
    Transform trf(getLayoutBox().getPosition(), scale_);

    stack_transform.pushBack(trf.applyPrev(stack_transform.getBack()));
    Transform last_trf = stack_transform.getBack();    

    sf::VertexArray vertex_array(sf::Quads, 4);

    getDrawFormat(vertex_array, last_trf);

    target.draw(vertex_array, defineTexture());

    stack_transform.popBack();

    return;
}

void Button::getDrawFormat(sf::VertexArray &vertex_array, const Transform &trf) const
{
    sf::Vector2u texture_size = defineTexture()->getSize();

    vertex_array[0].texCoords = sf::Vector2f(0, 0);
    vertex_array[1].texCoords = sf::Vector2f((float)texture_size.x, 0);
    vertex_array[2].texCoords = sf::Vector2f((float)texture_size.x, (float)texture_size.y);
    vertex_array[3].texCoords = sf::Vector2f(0, (float)texture_size.y);
    
    sf::Vector2f pos = trf.rollbackTransform(Dot(0, 0));

    const LayoutBox* layout_box = &getLayoutBox();

    float abs_width  = (float)(trf.scale.x * layout_box->getSize().x);
    float abs_height = (float)(trf.scale.y * layout_box->getSize().y);

    vertex_array[0].position = pos;
    vertex_array[1].position = sf::Vector2f(pos.x + abs_width, pos.y);
    vertex_array[2].position = sf::Vector2f(pos.x + abs_width, pos.y + abs_height);
    vertex_array[3].position = sf::Vector2f(pos.x, pos.y + abs_height);
}

const sf::Texture* Button::defineTexture() const
{
    switch (state_)
    {
        case  Button::ButtonState::RELEASED:
            return &released_texture_;

        case  Button::ButtonState::PRESSED:
            return &pressed_texture_;
    
        case  Button::ButtonState::DISABLED:
            return &disabled_texture_;

        case  Button::ButtonState::COVERED:
            return &covered_texture_;

        default:
            break;
    }

    return nullptr;
}


bool Button::onMouseMoved(const Vector &pos, Container<Transform> &stack_transform)
{
    if (state_ ==  Button::ButtonState::DISABLED)
        return false;

    Transform trf(getLayoutBox().getPosition(), scale_);

    stack_transform.pushBack(trf.applyPrev(stack_transform.getBack()));
    Transform last_trf = stack_transform.getBack();
    
    Dot new_pos = last_trf.applyTransform(pos);

    bool flag = checkIn(new_pos, getLayoutBox().getSize());

    stack_transform.popBack();


    if (!flag)
    { 
        covering_time_ = 0;
        state_ = prev_state_;
    }
    else
    {
        if (state_ !=  Button::ButtonState::COVERED)
        {
            prev_state_ = state_;
            state_ =  Button::ButtonState::COVERED;
        }
    }

    return flag;
}

//================================================================================

bool Button::onMousePressed(const Vector &pos, const MouseKey key, Container<Transform> &stack_transform)
{
    if (state_ == Button::ButtonState::DISABLED)
        return false;

    Transform trf(getLayoutBox().getPosition(), scale_);

    stack_transform.pushBack(trf.applyPrev(stack_transform.getBack()));
    Transform last_trf = stack_transform.getBack();
    
    Dot new_pos = last_trf.applyTransform(pos);

    bool flag = checkIn(new_pos, getLayoutBox().getSize());

    stack_transform.popBack();
    
    if (flag && key == MouseKey::LEFT)
    {
        
        if (action_ != nullptr) (*action_)();
        state_ = Button::ButtonState::PRESSED;
    }
    else
    {
        flag = false;

        state_ = Button::ButtonState::RELEASED;
        prev_state_ = Button::ButtonState::RELEASED;
    }

    return flag;
}

//================================================================================

bool Button::onMouseReleased(const Vector &pos, const MouseKey key, Container<Transform> &stack_transform)
{
    if (state_ == Button::ButtonState::DISABLED)
        return false;

    state_ = Button::ButtonState::RELEASED;
    prev_state_ = Button::ButtonState::RELEASED;
    
    return true;
}

//================================================================================

bool Button::onKeyboardPressed(const KeyboardKey key)
{
    printf("Button: mouse keyboard kye pressed\n");
    return false;
}

//================================================================================

bool Button::onKeyboardReleased(const KeyboardKey key)
{
    printf("Button: mouse keyboard kye released\n");
    return false;
}

//================================================================================

bool Button::onTick(const time_t delta_time)
{
    covering_time_ += delta_time;
}



//================================================================================

// void ButtonList::Draw(sf::RenderTarget &target, Container<Transform> &stack_transform)
// {
//     Button::Draw(target, stack_transform);
    
//     size_t size = buttons_.GetSize();
//     for (size_t it = 0; it < size; it++)
//     {
//         if (buttons_[it]->state_ != Button::ButtonState::DISABLED)
//             buttons_[it]->Draw(target, stack_transform); 
//     }
// }

// //================================================================================

// bool ButtonList::OnMouseMoved(const double x, const double y, Container<Transform> &stack_transform)
// {
//     if (state_ ==  Button::ButtonState::DISABLED)
//         return false;

//     stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
//     Transform last_trf = stack_transform.GetBack();
    
//     Dot new_pos = last_trf.ApplyTransform({x, y});
//     stack_transform.PopBack();

//     bool flag = checkIn(new_pos);

//     if (!flag)
//     { 
//         covering_time_ = 0;
//         state_ = prev_state_;
//     }
//     else
//     {
//         if (state_ !=  Button::ButtonState::COVERED)
//         {
//             prev_state_ = state_;
//             state_ =  Button::ButtonState::COVERED;
//         }
//     }


//     size_t size = buttons_.GetSize();
//     for (size_t it = 0; it < size; it++)
//     {
//         if (state_ == Button::ButtonState::COVERED || state_ == Button::ButtonState::PRESSED)
//         {
//             buttons_[it]->state_ = buttons_[it]->prev_state_;
//             buttons_[it]->OnMouseMoved(x, y, stack_transform);
//         }
//         else
//             buttons_[it]->state_ = Button::ButtonState::DISABLED;

            
//     }
    
//     return flag;
// }

// //================================================================================

// bool ButtonList::OnMousePressed(const double x, const double y, const MouseKey key, Container<Transform> &stack_transform)
// {
//     if (state_ == Button::ButtonState::DISABLED)
//         return false;
    
//     bool flag = false;
    
//     if (state_ == Button::ButtonState::PRESSED)
//     {
//         size_t size = buttons_.GetSize();

//         int last_presed = -1;
//         for (size_t it = 0; it < size; it++)
//         {
//             if (buttons_[it]->state_ == Button::ButtonState::PRESSED) last_presed = it;
//             flag |= buttons_[it]->OnMousePressed(x, y, key, stack_transform);
            

//             buttons_[it]->prev_state_ = buttons_[it]->state_;
//             buttons_[it]->state_ = Button::ButtonState::DISABLED;
//         }

//         if (!flag & &last_presed != -1)
//             buttons_[last_presed]->prev_state_ = Button::ButtonState::PRESSED;


//         state_      = Button::ButtonState::RELEASED;
//         prev_state_ = Button::ButtonState::RELEASED;
        
//     }
   
//     if (flag) return true;

//     stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
//     Transform last_trf = stack_transform.GetBack();
    
//     Dot new_pos = last_trf.ApplyTransform({x, y});

//     flag = checkIn(new_pos);
//     stack_transform.PopBack();

//     if (flag & &state_ != Button::ButtonState::PRESSED)
//     {
//         if (key == MouseKey::LEFT)
//         {
//             if (action_ != nullptr) (*action_)();
//             state_ =  Button::ButtonState::PRESSED;
//         }
//     }
//     else
//         state_ =  Button::ButtonState::RELEASED;
    
  

//     return flag;
// }

// //================================================================================


// bool ButtonList::OnMouseReleased(const double x, const double y, const MouseKey key, Container<Transform> &stack_transform)
// {
//     if (state_ == Button::ButtonState::DISABLED)
//         return false;

//     return true;
// }

// //================================================================================

// bool ButtonList::OnKeyboardPressed(const KeyboardKey key)
// {
//     printf("ButtonList: mouse keyboard kye pressed\n");
//     return false;
// }

// //================================================================================

// bool ButtonList::OnKeyboardReleased(const KeyboardKey key)
// {
//     printf("ButtonList: mouse keyboard kye released\n");
//     return false;
// }

// //================================================================================

// void ButtonList::PassTime(const time_t delta_time)
// {
//     covering_time_ += delta_time;
// }

// //================================================================================

// void ButtonList::AddButton(Button *button)
// {
//     buttons_.PushBack(button);
// }