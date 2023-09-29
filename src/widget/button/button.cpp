#include "button.h"


Button::Button (const char *released_texture_file, const char *covered_texture_file, 
                const char *pressed_texture_file,  const char *disabled_texture_file,
                const Dot &pos, const Action *action):
                action_(nullptr), released_texture_(), covered_texture_(), 
                                  pressed_texture_(), disabled_texture_(), 
                left_up_(), flag_pressed_(false), flag_disabled_(false)
{
    assert(action != nullptr && "action is nullptr");

    if (!released_texture_.loadFromFile(released_texture_file))   
    {
        PROCESS_ERROR(LOAD_TEXTURE_TO_STAT, "failed load teture from %s\n", released_texture_file);
        return;
    }

    if (!covered_texture_.loadFromFile(covered_texture_file))   
    {
        PROCESS_ERROR(LOAD_TEXTURE_TO_PRESS, "failed load teture from %s\n", covered_texture_file);
        return;
    }

    if (!pressed_texture_.loadFromFile(pressed_texture_file))   
    {
        PROCESS_ERROR(LOAD_TEXTURE_TO_PRESS, "failed load teture from %s\n", pressed_texture_file);
        return;
    }

    if (!disabled_texture_.loadFromFile(disabled_texture_file))   
    {
        PROCESS_ERROR(LOAD_TEXTURE_TO_PRESS, "failed load teture from %s\n", disabled_texture_file);
        return;
    }

    left_up_ = pos;

    action_ = action;

    return;

}

//================================================================================

void Button::Draw(sf::RenderWindow &window) const
{
    const sf::Texture *texture = this->DefineTexture();
    
    sf::Sprite button_sprite;
    button_sprite.setTexture(*texture);
    button_sprite.setPosition((float)left_up_.GetX(), (float)left_up_.GetY());

    window.draw(button_sprite);

    return;
}

//================================================================================

bool Button::CheckCursorOnButton() const
{
    const sf::Texture *texture = &disabled_texture_;

    double width  = (double)texture->getSize().x;
    double hieght = (double)texture->getSize().y;

    double mouse_x = (double)sf::Mouse::getPosition().x;
    double mouse_y = (double)sf::Mouse::getPosition().y - 65.0;

    bool res = (left_up_.GetX() < mouse_x  && mouse_x < left_up_.GetX() + width &&
                left_up_.GetY() < mouse_y  && mouse_y < left_up_.GetY() + hieght);

    return res;
}

//================================================================================

const sf::Texture* Button::DefineTexture() const
{
    if (flag_disabled_) return &disabled_texture_;

    if (flag_pressed_) return &pressed_texture_;

    if (this->CheckCursorOnButton()) return &covered_texture_;

    return &released_texture_;

    return nullptr;
}

//================================================================================

void ButtonsManager::ShowButtons(sf::RenderWindow &window) const
{
    size_t size = buttons_.GetSize();

    for (size_t it = 0 ; it < size; it++)
    {
        buttons_[it]->Draw(window);
    }    

    return;
}

//================================================================================

void ButtonsManager::DetectPresse(const sf::Event event) const
{

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        size_t size = buttons_.GetSize();

        for (size_t it = 0 ; it < size; it++)
        {
            if(buttons_[it]->CheckCursorOnButton()) 
            {
                buttons_[it]->SetState((*buttons_[it]->action_)());
            }
        }    

    }

    return;
}

//================================================================================