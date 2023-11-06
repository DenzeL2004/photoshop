#include "canvas.h"


void Tool::Draw(sf::RenderTarget &target, const Dot &pos)
{
    switch (type_)
    {
        case Tool::Type::Pen:
            drawPixel(target, pos, color_);
            break;

        case Tool::Type::Brash:
            drawCircle(target, pos, thickness_, color_);
            break;
        
        default:
            break;
    }
}

Canvas::Canvas( Tool *tool, const Vector &canvas_size,
                const Vector &size, const Vector &parent_size,
                const Vector &pos, const Widget *parent,  
                const Vector &origin, const Vector &scale):
                Window(Debug_texture, size, parent_size, pos, parent, origin, scale),
                tool_(tool),
                background_(), canvas_size_(canvas_size), real_pos_(0, 0) 
{
    assert(tool != nullptr && "tool is nullptr");

    background_.create((uint32_t)canvas_size.x, (uint32_t)canvas_size.y);

    sf::RectangleShape rec(sf::Vector2f((float)canvas_size.x, (float)canvas_size.y));
    rec.setPosition(0, 0);
    rec.setFillColor(sf::Color::White);

    background_.draw(rec);
}

//=======================================================================================

void Canvas::draw(sf::RenderTarget &target, Container<Transform>& stack_transform)
{
    Transform trf(getLayoutBox().getPosition(), scale_);

    stack_transform.pushBack(trf.applyPrev(stack_transform.getBack()));
    Transform last_trf = stack_transform.getBack();    

    sf::VertexArray vertex_array(sf::Quads, 4);

    getDrawFormat(vertex_array, last_trf);

    target.draw(vertex_array, &(background_.getTexture()));

    stack_transform.popBack();
}

void Canvas::getDrawFormat(sf::VertexArray &vertex_array, const Transform &trf) const
{
    const LayoutBox* layout_box = &getLayoutBox();

    float abs_width  = (float)(trf.scale.x * layout_box->getSize().x);
    float abs_height = (float)(trf.scale.y * layout_box->getSize().y);

    vertex_array[0].texCoords = sf::Vector2f((float)real_pos_.x, (float)real_pos_.y);
    vertex_array[1].texCoords = sf::Vector2f((float)real_pos_.x + (float)abs_width - 1, (float)real_pos_.y);
    vertex_array[2].texCoords = sf::Vector2f((float)real_pos_.x + (float)abs_width - 1, (float)real_pos_.y + (float)abs_height - 1);
    vertex_array[3].texCoords = sf::Vector2f((float)real_pos_.x, (float)real_pos_.y + (float)abs_height - 1);

     sf::Vector2f pos = trf.rollbackTransform(Dot(0, 0));

    vertex_array[0].position = pos;
    vertex_array[1].position = sf::Vector2f(pos.x + abs_width, pos.y);
    vertex_array[2].position = sf::Vector2f(pos.x + abs_width, pos.y + abs_height);
    vertex_array[3].position = sf::Vector2f(pos.x, pos.y + abs_height);
    
}


//================================================================================

bool Canvas::onMouseMoved(const Vector& pos, Container<Transform> &stack_transform)
{
    Transform trf(getLayoutBox().getPosition(), scale_);

    stack_transform.pushBack(trf.applyPrev(stack_transform.getBack()));
    Transform last_trf = stack_transform.getBack();    

    Dot local_pos = last_trf.applyTransform(pos);

    bool flag = checkIn(local_pos, getLayoutBox().getSize());
    if (flag)
    {
        if (tool_->state_ == Tool::State::Hold)
        {
            Vector canvas_pos = getCanvaseCoord(local_pos);
            tool_->Draw(background_, canvas_pos);
        }
    }

    stack_transform.popBack();

    return flag;
}

//================================================================================

bool Canvas::onMousePressed(const Vector& pos, const MouseKey key, Container<Transform> &stack_transform)
{
    Transform trf(getLayoutBox().getPosition(), scale_);

    stack_transform.pushBack(trf.applyPrev(stack_transform.getBack()));
    Transform last_trf = stack_transform.getBack();    

    Dot local_pos = last_trf.applyTransform(pos);

    bool flag = checkIn(local_pos, getLayoutBox().getSize());
    if (flag)
    {
        tool_->state_ = Tool::State::Hold;
        tool_->hold_pos_ = getCanvaseCoord(local_pos);
    }

    stack_transform.popBack();

    return flag;
}

//================================================================================

bool Canvas::onMouseReleased(const Vector& pos, const MouseKey key, Container<Transform> &stack_transform)
{
    tool_->state_ = Tool::State::Default;

    return true;
}

Dot Canvas::getCanvaseCoord(const Vector &local_pos) const
{

    return Dot(real_pos_.x + local_pos.x, canvas_size_.y - (real_pos_.y + local_pos.y) );
}

//================================================================================

bool Canvas::onKeyboardPressed(const KeyboardKey key)
{
    printf("Canvas: mouse keyboard kye pressed\n");
    return false;
}

//================================================================================

bool Canvas::onKeyboardReleased(const KeyboardKey key)
{
    printf("Canvas: mouse keyboard kye released\n");
    return false;
}


//================================================================================

// //=======================================================================================
// // //CONTAINER WINDOW

// void CanvaseManager::Draw(sf::RenderTarget &target, Container<Transform> &stack_transform)
// {
//     Window::Draw(target, stack_transform);

//     stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));

//     size_t size = canvases_.GetSize();
//     for (size_t it = 0; it < size; it++)
//         canvases_[it]->Draw(target, stack_transform);

//     stack_transform.PopBack();

//     return;
// }

// //=======================================================================================

// bool CanvaseManager::onMouseMoved(const Vector& pos, Container<Transform> &stack_transform)
// {
//     size_t size = canvases_.GetSize();
//     if (size == 0) return false;
    
//     stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
//     Transform last_trf = stack_transform.GetBack();
    
//     Dot new_coord = last_trf.ApplyTransform({x, y});

//     canvases_[size - 1]->onMouseMoved(x, y, stack_transform);
    
//     stack_transform.PopBack();

//     return true;
// }

// //================================================================================

// bool CanvaseManager::onMousePressed(const Vector& pos, const MouseKey key, Container<Transform> &stack_transform)
// {
//     stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
//     Transform last_trf = stack_transform.GetBack();
    
//     Dot new_coord = last_trf.ApplyTransform({x, y});

//     bool flag = CheckIn(new_coord);

//     if (flag)
//     {
//         int size = (int)canvases_.GetSize();
//         for (int it = size - 1; it >= 0; it--)
//         {
//             delte_canvase_ = false;
//             if (canvases_[it]->onMousePressed(x, y, key, stack_transform))
//             {
//                 canvases_.Drown(it);
//                 if (delte_canvase_)
//                     canvases_.PopBack();

//                 break;
//             }
//         }
//     }

//     stack_transform.PopBack();

//     return flag;
// }

// //================================================================================

// bool CanvaseManager::onMouseReleased(const Vector& pos, const MouseKey key, Container<Transform> &stack_transform)
// {
    
//     stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
//     Transform last_trf = stack_transform.GetBack();
//     Dot new_coord = last_trf.ApplyTransform({x, y});

//     int size = (int)canvases_.GetSize();
//     for (int it = size - 1; it >= 0; it--)
//     {
//         canvases_[it]->onMouseReleased(x, y, key, stack_transform);
//     }

//     stack_transform.PopBack();

//     return true;
// }
//        Dot position_;
// //================================================================================

// bool CanvaseManager::onKeyboardPressed(const KeyboardKey key)
// {
//     return false;
// }

// //================================================================================

// bool CanvaseManager::onKeyboardReleased(const KeyboardKey key)
// {
//     printf("Window: mouse keyboard kye released\n");
//     return false;
// }
// //================================================================================

// void CanvaseManager::CreateCanvase(Tool *tool)
// {
//     assert(tool != nullptr && "tool is nullptr");

//     char *buf = (char*)calloc(BUFSIZ, sizeof(char));
//     if (!buf)
//     {
//         PROCESS_ERROR(ERR_MEMORY_ALLOC, "allocate memory to buf failed\n");
//         return;
//     }

//     cnt_++;
//     sprintf(buf, "canvas %lu", cnt_);

//     Button *close_btn = new Button(Cross_Button_Release, Cross_Button_Covered, 
//                                       Cross_Button_Release, Cross_Button_Covered, 
//                                       new Click(&delte_canvase_), 
//                                       Cross_Button_Offset, Cross_Button_Scale);

//     Canvas *new_canvase = new Canvas(Width_Canvase, Hieght_Canvase, tool, Canvase_Offset, Canvase_Scale);

//     WidgetContainer *scrolls = new WidgetContainer(Dot(0.02, 0.05), Vector(0.95, 0.87));
    

//     Button *left_btn = new Button(  Left_Scl, Left_Scl, Left_Scl, Left_Scl, 
//                                     new ScrollCanvas(Dot(-0.05, 0), new_canvase), 
//                                     Dot(0.0, 0.0), Vector(0.03, 0.03));

//     Button *right_btn = new Button( Right_Scl, Right_Scl, Right_Scl, Right_Scl, 
//                                     new ScrollCanvas(Vector(0.05, 0), new_canvase), 
//                                     Dot(0.92, 0), Vector(0.03, 0.03));

//     Button *hor_btn = new Button(   Hor_Scl, Hor_Scl, Hor_Scl, Hor_Scl, 
//                                     new ScrollCanvas(Dot(0, 0), new_canvase), 
//                                     Dot(0.03, 0.0), Vector(1.0, 0.03));

//     Scrollbar *scroll_hor = new Scrollbar(left_btn, right_btn, hor_btn, new_canvase, 
//                                      Scrollbar::Scroll_Type::Horizontal, Dot(0.00, 0.00), Vector(1.0, 1.0));

//     Button *up_btn = new Button(Up_Scl, Up_Scl, Up_Scl, Up_Scl, 
//                                 new ScrollCanvas(Dot(0.0, -0.05), new_canvase), 
//                                 Dot(0.0, 0.0), Vector(0.03, 0.03));

//     Button *down_btn = new Button(Down_Scl, Down_Scl, Down_Scl, Down_Scl, 
//                                 new ScrollCanvas(Vector(0.0, 0.05), new_canvase), 
//                                 Dot(0, 0.97), Vector(0.03, 0.03));

//     Button *ver_btn = new Button(Ver_Scl, Ver_Scl, Ver_Scl, Ver_Scl, 
//                                 new ScrollCanvas(Dot(0, 0), new_canvase), 
//                                 Dot(0.0, 0.03), Vector(0.03, 1.0));

//     Scrollbar *scroll_ver = new Scrollbar(up_btn, down_btn, ver_btn, new_canvase, 
//                                      Scrollbar::Scroll_Type::Vertical, Dot(0.96, 0.05), Vector(1.0, 1.0));
   

//     scrolls->AddWidget(new_canvase);
//     scrolls->AddWidget(scroll_hor);
//     scrolls->AddWidget(scroll_ver);

//     Widget *new_frame = new Frame(Frame_Texture, close_btn, {buf, sf::Color::Black}, 
//                                   scrolls, Canvase_Frame_Offset, Canvase_Frame_Scale);

//     canvases_.PushBack(new_frame);
// }

// //================================================================================


// void Scrollbar::Draw(sf::RenderTarget &target, Container<Transform> &stack_transform)
// {
//     stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
//     Transform last_trf = stack_transform.GetBack();

//     ResizeCenterButton(canvas_->GetTransform().ApplyPrev(last_trf));
    
//     top_button_->Draw(target, stack_transform);
//     bottom_button_->Draw(target, stack_transform);
//     center_button_->Draw(target, stack_transform);

//     stack_transform.PopBack();

//     return;
// }


// void Scrollbar::ResizeCenterButton(const Transform &canvas_trf)
// {
   
//     Dot size = canvas_->GetSize();

//     Transform center_trf = center_button_->GetTransform();
    
//     if (type_ == Scrollbar::Scroll_Type::Horizontal)
//         center_trf.scale.x = canvas_trf.scale.x / size.x; 
    
//     if (type_ == Scrollbar::Scroll_Type::Vertical)
//         center_trf.scale.y = canvas_trf.scale.y / size.y; 
    
//     center_button_->SetTransform(center_trf);
//     canvas_->CorrectRealCoord(canvas_trf);

//     Dot prev = canvas_->GetRealPos();
//     MoveCenter(prev);
// }

// //================================================================================

// bool Scrollbar::onMouseMoved(const Vector& pos, Container<Transform> &stack_transform)
// {
//     stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
//     Transform last_trf = stack_transform.GetBack();

//     top_button_->onMouseMoved(x, y, stack_transform);
//     bottom_button_->onMouseMoved(x, y, stack_transform);
//     center_button_->onMouseMoved(x, y, stack_transform);

//     Dot new_coord = last_trf.ApplyTransform({x, y});
    
//     if (center_button_->prev_state_ == Button::Button_State::Pressed || 
//         center_button_->state_ == Button::Button_State::Pressed)
//     {
//         Dot prev_real_pos = canvas_->GetRealPos();
        
//         if (type_ == Scrollbar::Scroll_Type::Horizontal)
//             canvas_->Move(Dot((new_coord.x - pos_press_.x) * canvas_->GetSize().x, 0));

//         if (type_ == Scrollbar::Scroll_Type::Vertical)
//             canvas_->Move(Dot(0.0, (new_coord.y - pos_press_.y) * canvas_->GetSize().y));

//         canvas_->CorrectRealCoord(canvas_->GetTransform().ApplyPrev(last_trf));

//         MoveCenter(prev_real_pos);
//         pos_press_ = new_coord;

//     }
    
//     stack_transform.PopBack();

//     return true;
// }

// void Scrollbar::MoveCenter(Dot &prev_pos)
// {
//     Transform center_trf = center_button_->GetTransform();

//     Transform top_trf    = top_button_->GetTransform();
//     Transform bottom_trf = bottom_button_->GetTransform();


//     Dot offset(0.0, 0.0);
//     if (type_ == Scrollbar::Scroll_Type::Horizontal)
//     { 
//         offset = Dot((canvas_->GetRealPos().x - prev_pos.x) / canvas_->GetSize().x, 0.0);
//         offset.x = std::min(bottom_trf.offset.x - Eps - (center_trf.offset.x + center_trf.scale.x), 
//                         std::max(top_trf.offset.x + top_trf.scale.x + Eps - center_trf.offset.x, offset.x));
//     }

//     if (type_ == Scrollbar::Scroll_Type::Vertical)
//     {
//         offset = Dot(0.0, (canvas_->GetRealPos().y - prev_pos.y) / canvas_->GetSize().y);
//         offset.y = std::min(bottom_trf.offset.y - Eps - (center_trf.offset.y + center_trf.scale.y), 
//                         std::max(top_trf.offset.y + top_trf.scale.y + Eps - center_trf.offset.y, offset.y));
//     }
    
//     center_trf.offset += offset;

//     center_button_->SetTransform(center_trf);
    
//     return;
// }

// //================================================================================

// bool Scrollbar::onMousePressed(const Vector& pos, const MouseKey key, Container<Transform> &stack_transform)
// {
//     stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
//     Transform last_trf = stack_transform.GetBack();

//     Dot new_coord = last_trf.ApplyTransform({x, y});
//     pos_press_ = new_coord;

//     Dot prev_real_pos = canvas_->GetRealPos();

//     Dot area_coord = press_area_.ApplyPrev(last_trf).ApplyTransform({x, y});
//     bool flag = false;

//     if (CheckIn(area_coord))
//     {
//         flag |= top_button_->onMousePressed(x, y, key, stack_transform);
//         flag |= bottom_button_->onMousePressed(x, y, key, stack_transform);

//         flag |= center_button_->onMousePressed(x, y, key, stack_transform);

//         if (!flag)
//         {
//             Dot offset = new_coord - center_button_->GetTransform().offset;

//             if (type_ == Scrollbar::Scroll_Type::Horizontal)
//                 offset.y = 0.0;
//             if (type_ == Scrollbar::Scroll_Type::Vertical)
//                 offset.x = 0.0;

//             if (offset.x < -Eps || offset.y < -Eps)
//                 (*top_button_->action_)();
            
//             if (offset.x > Eps || offset.y > Eps)
//                 (*bottom_button_->action_)();
//         }
//     }
    
//     canvas_->CorrectRealCoord(canvas_->GetTransform().ApplyPrev(last_trf));
//     MoveCenter(prev_real_pos);

//     stack_transform.PopBack();

//     return flag;
// }

// //================================================================================

// bool Scrollbar::onMouseReleased(const Vector& pos, const MouseKey key, Container<Transform> &stack_transform)
// {
//     stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));

//     top_button_->onMouseReleased(x, y, key, stack_transform);
//     bottom_button_->onMouseReleased(x, y, key, stack_transform);
//     center_button_->onMouseReleased(x, y, key, stack_transform);

//     stack_transform.PopBack();

//     return true;
// }

// //================================================================================

// bool Scrollbar::onKeyboardPressed(const KeyboardKey key)
// {
//     printf("Scrollbar: mouse keyboard kye pressed\n");
//     return false;
// }

// //================================================================================

// bool Scrollbar::onKeyboardReleased(const KeyboardKey key)
// {
//     printf("Scrollbar: mouse keyboard kye released\n");
//     return false;
// }

// //================================================================================

// void Scrollbar::PassTime(const time_t delta_time)
// {
//     printf("Scrollbar: mouse keyboard kye released\n");
//     return;
// }

// //=================================================================================

