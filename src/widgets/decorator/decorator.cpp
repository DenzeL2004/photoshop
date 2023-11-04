#include "decorator.h"

const Dot Offset_Title = Dot(0.45, 0.0);
const double Scale_Title  = 0.02;


void Frame::GetNewSize(sf::VertexArray &vertex_array, const Transform &transform) const
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

Frame::Frame( const char *path_texture, Button* close_button,
                const Title &title, Widget *decarable,
                const Dot &offset, const Vector &scale):
                transform_({offset, scale}),
                width_(0), hieght_(0), background_(), 
                title_(title), close_button_(close_button), decarable_(decarable), 
                state_(Default), hold_pos_({0.0, 0.0}),
                left_border_(Left_Border),   top_border_(Top_Border),
                right_border_(Right_Border), bottom_border_(Bottom_Border)
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

void Frame::Draw(sf::RenderTarget &target, Container<Transform> &stack_transform)
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

void Frame::DrawTitle(sf::RenderTarget &target, const Transform &border_trf) const
{
    sf::Vector2f new_coord =  border_trf.RollbackTransform(Offset_Title);
    WriteText(target, Dot(new_coord.x - title_.len_msg_, new_coord.y), title_.msg_, 
              Oldtimer_font_path, (uint32_t)(border_trf.scale.y * Scale_Title), title_.color_);

    return;
}

//================================================================================

bool Frame::OnMouseMoved(const double x, const double y, Container<Transform> &stack_transform)
{
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    Transform last_trf = stack_transform.GetBack();

    close_button_->OnMouseMoved(x, y, stack_transform);

    Dot new_coord = last_trf.ApplyTransform({x, y});
    
    if(state_ == Hold)
    {
        uint8_t mask = ClickOnBorder(x, y, last_trf);
        if (mask)
            Scale(new_coord, mask);
        else
            Move(new_coord);        
    }  

    decarable_->OnMouseMoved(x, y, stack_transform);
    
    stack_transform.PopBack();

    return true;
}

//================================================================================
uint8_t Frame::ClickOnBorder(double x, double y, const Transform &Last_transform) const
{
    uint8_t mask = 0;

    Transform tmp = left_border_.ApplyPrev(Last_transform);
    Dot new_coord = tmp.ApplyTransform({x, y});
    if (CheckIn(new_coord)) mask |= Frame::Borders::LEFT;

    tmp = right_border_.ApplyPrev(Last_transform);
    new_coord = tmp.ApplyTransform({x, y});
    if (CheckIn(new_coord)) mask |= Frame::Borders::RIGHT;

    tmp = bottom_border_.ApplyPrev(Last_transform);
    new_coord = tmp.ApplyTransform({x, y});
    if (CheckIn(new_coord)) mask |= Frame::Borders::BOTTOM;
    
    return mask;
}


void Frame::Scale(const Dot &new_coord, uint8_t mask)
{

    if (transform_.scale.x <= Scale_Limit.x + Eps || transform_.scale.y <= Scale_Limit.y + Eps)
        return;
    Vector delta = new_coord - hold_pos_;
    
    delta.x *= transform_.scale.x;
    delta.y *= transform_.scale.y;
    
    Dot cur = transform_.offset;
    
    if (mask & Frame::Borders::LEFT || mask & Frame::Borders::RIGHT)
    {
        if (mask & Frame::Borders::LEFT) 
        {
            Move({new_coord.x, hold_pos_.y});
            if (transform_.offset == cur) return;   
                delta.x *= -1.0;
        }

        if (transform_.offset.x + transform_.scale.x + delta.x < 1 - Eps && 
            transform_.scale.x + delta.x > Scale_Limit.x + Eps)
            transform_.scale.x += delta.x;
    }

    if (mask & Frame::Borders::BOTTOM)
    {
        if (transform_.offset.y + transform_.scale.y + delta.y < 1 - Eps && 
            transform_.scale.y + delta.y > Scale_Limit.y + Eps)
            transform_.scale.y += delta.y;
    }

    return;
}


void Frame::Move(const Dot &new_coord)
{
    Vector delta = new_coord - hold_pos_;
        
    delta.x *= transform_.scale.x;
    delta.y *= transform_.scale.y;

    transform_.offset += delta;
    if (transform_.offset.x < Eps                           || transform_.offset.y < Eps ||
        transform_.offset.x + transform_.scale.x > 1 - Eps  || transform_.offset.y + transform_.scale.y > 1 - Eps)
        transform_.offset -= delta;

    return;
}


//================================================================================

bool Frame::OnMousePressed(const double x, const double y, const MouseKey key, Container<Transform> &stack_transform)
{
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    Transform last_trf = stack_transform.GetBack();

    bool flag  = close_button_->OnMousePressed(x, y, key, stack_transform);
         flag |= decarable_->OnMousePressed(x, y, key, stack_transform);

    if (!flag)
    {
        Dot new_coord = last_trf.ApplyTransform({x, y});
        flag = CheckIn(new_coord);    

        if (flag)
        {
            if (key == MouseKey::LEFT)
            {
                state_ = Hold;
                hold_pos_ = new_coord;

                flag = true;
            }
        }
    }

    stack_transform.PopBack();

    return flag;
}

//================================================================================

bool Frame::OnMouseReleased(const double x, const double y, const MouseKey key, Container<Transform> &stack_transform)
{
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));

    close_button_->OnMouseReleased(x, y, key, stack_transform);
    decarable_->OnMouseReleased(x, y, key, stack_transform);

    state_ = Default;

    stack_transform.PopBack();

    return false;
}

//================================================================================

bool Frame::OnKeyboardPressed(const KeyboardKey key)
{
    return decarable_->OnKeyboardPressed(key);
}

//================================================================================

bool Frame::OnKeyboardReleased(const KeyboardKey key)
{
    bool flag = decarable_->OnKeyboardReleased(key);

    return flag;
}

//================================================================================

void Frame::PassTime(const time_t delta_time)
{
    printf("Frame: mouse keyboard kye released\n");
    return;
}

//================================================================================

void Frame::SetFocus(bool value)
{
    decarable_->SetFocus(value);
}
