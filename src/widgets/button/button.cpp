#include "button.h"


Button::Button (const char *released_texture_file, const char *covered_texture_file, 
                const char *pressed_texture_file,  const char *disabled_texture_file,
                const Action *action, 
                const Vec2d &size, const Vec2d &pos, 
                const Widget *parent, const Vec2d &parent_size, 
                const Vec2d &origin, const Vec2d &scale):
                action_(action), 
                state_(ButtonState::RELEASED), prev_state_(ButtonState::RELEASED),
                released_texture_(), covered_texture_(), 
                pressed_texture_(), disabled_texture_(), 
                Widget(size, pos, parent, parent_size, origin, scale),
                covering_time_(0)
{
    setLayoutBox(*(new BaseLayoutBox(pos, size, (parent != nullptr) ? parent->getLayoutBox().getSize() : parent_size, false, true)));   

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

    stack_transform.pushBack(trf.combine(stack_transform.getBack()));
    Transform last_trf = stack_transform.getBack();    

    sf::VertexArray vertex_array(sf::Quads, 4);

    getdrawFormat(vertex_array, last_trf);

    target.draw(vertex_array, defineTexture());

    stack_transform.popBack();

    return;
}

void Button::getdrawFormat(sf::VertexArray &vertex_array, Transform &trf) const
{
    sf::Vector2u texture_size = defineTexture()->getSize();

    vertex_array[0].texCoords = sf::Vector2f(0, 0);
    vertex_array[1].texCoords = sf::Vector2f(texture_size.x, 0);
    vertex_array[2].texCoords = sf::Vector2f(texture_size.x, texture_size.y);
    vertex_array[3].texCoords = sf::Vector2f(0, texture_size.y);
    
    Vec2d pos = trf.apply(Dot(0, 0));

    Vec2d size = trf.getScale() * getLayoutBox().getSize();

    vertex_array[0].position = sf::Vector2f(pos.x, pos.y);
    vertex_array[1].position = sf::Vector2f(pos.x + size.x, pos.y);
    vertex_array[2].position = sf::Vector2f(pos.x + size.x, pos.y + size.y);
    vertex_array[3].position = sf::Vector2f(pos.x, pos.y + size.y);
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


bool Button::onMouseMoved(const Vec2d &pos, Container<Transform> &stack_transform)
{
    if (state_ ==  Button::ButtonState::DISABLED)
        return false;

    Transform trf(getLayoutBox().getPosition(), scale_);
    stack_transform.pushBack(trf.combine(stack_transform.getBack()));
    
    Transform last_trf = stack_transform.getBack();
    Dot local_pos = last_trf.restore(pos);

    bool flag = checkIn(local_pos);

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

bool Button::onMousePressed(const Vec2d &pos, const MouseKey key, Container<Transform> &stack_transform)
{
    if (state_ == Button::ButtonState::DISABLED)
        return false;

    Transform trf(getLayoutBox().getPosition(), scale_);

    stack_transform.pushBack(trf.combine(stack_transform.getBack()));
    Transform last_trf = stack_transform.getBack();
    
    Dot local_pos = last_trf.restore(pos);

    bool flag = checkIn(local_pos);

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

bool Button::onMouseReleased(const Vec2d &pos, const MouseKey key, Container<Transform> &stack_transform)
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

void ButtonList::draw(sf::RenderTarget &target, Container<Transform> &stack_transform)
{
    Button::draw(target, stack_transform);
    
    size_t size = buttons_.getSize();
    for (size_t it = 0; it < size; it++)
    {
        if (buttons_[it]->state_ != Button::ButtonState::DISABLED)
            buttons_[it]->draw(target, stack_transform); 
    }
}

//================================================================================

bool ButtonList::onMouseMoved(const Vec2d &pos, Container<Transform> &stack_transform)
{
    if (state_ ==  Button::ButtonState::DISABLED)
        return false;

    Transform trf(getLayoutBox().getPosition(), scale_);
    stack_transform.pushBack(trf.combine(stack_transform.getBack()));
    
    Transform last_trf = stack_transform.getBack();
    Dot local_pos = last_trf.restore(pos);

    stack_transform.popBack();

    bool flag = checkIn(local_pos);

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

    size_t size = buttons_.getSize();
    for (size_t it = 0; it < size; it++)
    {
        if (prev_state_ == Button::ButtonState::PRESSED)
        {
            buttons_[it]->state_ = buttons_[it]->prev_state_;
            buttons_[it]->onMouseMoved(pos, stack_transform);
        }
        else
            buttons_[it]->state_ = Button::ButtonState::DISABLED;
    }
    
    return flag;
}

//================================================================================

bool ButtonList::onMousePressed(const Vec2d &pos, const MouseKey key, Container<Transform> &stack_transform)
{
    if (state_ == Button::ButtonState::DISABLED)
        return false;
    
    bool flag = false;
    
    if (state_ == Button::ButtonState::PRESSED)
    {
        size_t size = buttons_.getSize();

        int last_presed = -1;
        for (size_t it = 0; it < size; it++)
        {
            if (buttons_[it]->state_ == Button::ButtonState::PRESSED) last_presed = it;
            flag |= buttons_[it]->onMousePressed(pos, key, stack_transform);
            

            buttons_[it]->prev_state_ = buttons_[it]->state_;
            buttons_[it]->state_ = Button::ButtonState::DISABLED;
        }

        if (!flag && last_presed != -1)
            buttons_[last_presed]->prev_state_ = Button::ButtonState::PRESSED;


        state_      = Button::ButtonState::RELEASED;
        prev_state_ = Button::ButtonState::RELEASED;
        
    }
   
    if (flag) return true;

    Transform trf(getLayoutBox().getPosition(), scale_);
    stack_transform.pushBack(trf.combine(stack_transform.getBack()));
    
    Transform last_trf = stack_transform.getBack();
    Dot local_pos = last_trf.restore(pos);

    flag = checkIn(local_pos);
    stack_transform.popBack();

    if (flag && state_ != Button::ButtonState::PRESSED)
    {
        if (key == MouseKey::LEFT)
        {
            if (action_ != nullptr) (*action_)();
            state_ =  Button::ButtonState::PRESSED;
        }
    }
    else
        state_ =  Button::ButtonState::RELEASED;
    
    return flag;
}

//================================================================================


bool ButtonList::onMouseReleased(const Vec2d &pos, const MouseKey key, Container<Transform> &stack_transform)
{
    if (state_ == Button::ButtonState::DISABLED)
        return false;

    return true;
}

//================================================================================

bool ButtonList::onKeyboardPressed(const KeyboardKey key)
{
    printf("ButtonList: mouse keyboard kye pressed\n");
    return false;
}

//================================================================================

bool ButtonList::onKeyboardReleased(const KeyboardKey key)
{
    printf("ButtonList: mouse keyboard kye released\n");
    return false;
}

//================================================================================

bool ButtonList::onTick(const time_t delta_time)
{
    covering_time_ += delta_time;

    size_t size = buttons_.getSize();
    for (size_t it = 0; it < size; it++)
    {
        buttons_[it]->onTick(delta_time);
    }

    return false;
}

//================================================================================

void ButtonList::addButton(Button *button)
{
    buttons_.pushBack(button);
}