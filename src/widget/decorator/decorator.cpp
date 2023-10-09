#include "decorator.h"

//=================================================================================================



void Decorator::SetOffset(const Dot &offset)
{
    transform_.offset_ = offset;
    return;
}


bool Decorator::CheckIn(const Dot &mouse_pos) const
{
    bool horizontal = (0 <= mouse_pos.GetX() && 1  >= mouse_pos.GetX());
    bool vertical   = (0 <= mouse_pos.GetY() && 1 >= mouse_pos.GetY());
   
    return horizontal & vertical;
}

//=================================================================================================

Border::Border( const char *path_texture, const Button* close_button,
                const Title &title, const Widget *decarable,
                const Dot offset, const Vector scale):
                transform_(), background_(), 
                title_(title), close_button_(close_button), decarable_(decarable)
{
    assert(close_button != nullptr && "close button is nullptr");
    assert(decarable    != nullptr && "decarable is nullptr");
 
    if (!background_.loadFromFile(path_texture))   
    {
        PROCESS_ERROR(LOAD_TEXTURE_ERR, "failed load tetxure from %s\n", path_texture);
        return;
    }

    transform_.offset_ = offset;

    transform_.scale_ = Vector(scale.GetX(),
                               scale.GetY());

    return;
}

void Border::Draw(sf::RenderTarget &target, Container<Transform> &stack_transform) const
{
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    Transform res_transform = stack_transform.GetBack();
    
    sf::Sprite sprite;
    sprite.setTexture(background_);

    sprite.setPosition((float)res_transform.offset_.GetX(), (float)res_transform.offset_.GetY());

    Dot size = GetScale(res_transform);
    sprite.setScale((float)size.GetX(),  (float)size.GetY());

    target.draw(sprite);

    WriteText(target, res_transform.offset_, title_.msg_, Oldtimer_font_path, 15u, title_.color_);
    close_button_->Draw(target, stack_transform);

    decarable_->Draw(target, stack_transform);
    stack_transform.PopBack();

    return;
}

Dot Border::GetScale(const Transform &transform) const
{
    return Dot(transform.scale_.GetX() / background_.getSize().x, 
               transform.scale_.GetY() / background_.getSize().y);
}

//================================================================================

bool Border::OnMouseMoved(const int x, const int y, Container<Transform> &stack_transform)
{
    Dot mouse_coord((double)x, double(y));
   
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    Transform res_transform = stack_transform.GetBack();
    
    Dot new_coord = res_transform.ApplyTransform(mouse_coord);

    bool flag = CheckIn(new_coord);

    stack_transform.PopBack();

    return flag;
}

//================================================================================

bool Border::OnMousePressed(const MouseKey key, Container<Transform> &stack_transform)
{
    printf("Border: mouse pressed\n");
    return false;
}

//================================================================================

bool Border::OnMouseReleased(const MouseKey key, Container<Transform> &stack_transform)
{
    printf("Border: mouse released\n");
    return false;
}

//================================================================================

bool Border::OnKeyboardPressed(const KeyboardKey key)
{
    printf("Border: mouse keyboard kye pressed\n");
    return false;
}

//================================================================================

bool Border::OnKeyboardReleased(const KeyboardKey key)
{
    printf("Border: mouse keyboard kye released\n");
    return false;
}

//================================================================================

void Border::PassTime(const time_t delta_time)
{
    printf("Border: mouse keyboard kye released\n");
    return;
}

//================================================================================