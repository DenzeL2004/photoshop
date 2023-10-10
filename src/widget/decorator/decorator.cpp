#include "decorator.h"

const Dot Offset_Title = Dot(0.45, 0.0);
const double Scale_Title  = 0.02;

//=================================================================================================

void Decorator::Move(const Dot &offset)
{
    transform_.offset += offset;
    return;
}


bool Decorator::CheckIn(const Dot &mouse_pos) const
{
    bool horizontal = (Eps < mouse_pos.x && 1 - Eps > mouse_pos.x);
    bool vertical   = (Eps < mouse_pos.y && 1 - Eps > mouse_pos.y);
   
    return horizontal & vertical;
}


void Decorator::GetNewSize(sf::VertexArray &vertex_array, const Transform &transform) const
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

//=================================================================================================

Border::Border( const char *path_texture, Button* close_button,
                const Title &title, Widget *decarable,
                const Dot offset, const Vector scale):
                transform_({offset, scale}),
                width_(0), hieght_(0), background_(), 
                title_(title), close_button_(close_button), decarable_(decarable), 
                state_(DEFAULT), hold_pos_({0.0, 0.0})
{
    assert(close_button != nullptr && "close button is nullptr");
    assert(decarable    != nullptr && "decarable is nullptr");
 
    if (!background_.loadFromFile(path_texture))   
    {
        PROCESS_ERROR(LOAD_TEXTURE_ERR, "failed load tetxure from %s\n", path_texture);
        return;
    }

    width_  = background_.getSize().x;
    hieght_ = background_.getSize().y;

    return;
}

void Border::Draw(sf::RenderTarget &target, Container<Transform> &stack_transform) const
{
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    Transform last_trf = stack_transform.GetBack();
    
    sf::VertexArray vertex_array(sf::Quads, 4);

    GetNewSize(vertex_array, last_trf);
    
    target.draw(vertex_array, &background_);

    DrawTitle(target, last_trf);
    close_button_->Draw(target, stack_transform);

    decarable_->Draw(target, stack_transform);
    stack_transform.PopBack();

    return;
}

//================================================================================

void Border::DrawTitle(sf::RenderTarget &target, const Transform &border_trf) const
{
    sf::Vector2f new_coord =  border_trf.RollbackTransform(Offset_Title);
    WriteText(target, Dot(new_coord.x - title_.len_msg_, new_coord.y), title_.msg_, 
              Oldtimer_font_path, (uint32_t)(border_trf.scale.y * Scale_Title), title_.color_);

    return;
}

//================================================================================

bool Border::OnMouseMoved(const int x, const int y, Container<Transform> &stack_transform)
{
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    Transform last_trf = stack_transform.GetBack();

    close_button_->OnMouseMoved(x, y, stack_transform);
    decarable_->OnMouseMoved(x, y, stack_transform);

    Dot new_coord = last_trf.ApplyTransform({(double)x, (double)y});
    
    if(state_ == HOLD)
    {
        Vector delta = new_coord - hold_pos_;
        
        delta.x *= transform_.scale.x;
        delta.y *= transform_.scale.y;

        transform_.offset += delta;
        if (transform_.offset.x < Eps                           || transform_.offset.y < Eps ||
            transform_.offset.x + transform_.scale.x > 1 - Eps  || transform_.offset.y + transform_.scale.y > 1 - Eps)
            transform_.offset -= delta;
    }  
    

    stack_transform.PopBack();

    return true;
}

//================================================================================

bool Border::OnMousePressed(const int x, const int y, const MouseKey key, Container<Transform> &stack_transform)
{
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    Transform last_trf = stack_transform.GetBack();

    Dot new_coord = last_trf.ApplyTransform({(double)x, (double)y});

    bool flag = CheckIn(new_coord);
    if (flag)
    {
        bool flag  = close_button_->OnMousePressed(x, y, key, stack_transform);
             flag |= decarable_->OnMousePressed(x, y, key, stack_transform);

        if (!flag)
        {
            if (key == Left)
            {
                state_ = HOLD;
                hold_pos_ = new_coord;
            }
        }    

    }

    stack_transform.PopBack();

    return flag;
}

//================================================================================

bool Border::OnMouseReleased(const int x, const int y, const MouseKey key, Container<Transform> &stack_transform)
{
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    Transform last_trf = stack_transform.GetBack();

    state_ = DEFAULT;

    stack_transform.PopBack();

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