#include "canvas.h"


void Tool::Draw(sf::RenderTarget &target, const Dot &pos)
{
    switch (type_)
    {
        case Tool::Type::Pen:
            DrawPixel(target, pos, color_);
            break;

        case Tool::Type::Brash:
            DrawCircle(target, pos, thickness_, color_);
            break;
        
        default:
            break;
    }
}


Canvas::Canvas  (const double width, const double hieght, Tool *tool, 
                const Dot &offset, const Vector &scale):
                transform_({offset, scale}),
                width_(width), hieght_(hieght), tool_(tool),
                background_(), real_pos_(0, 0) 
{
    assert(tool != nullptr && "tool is nullptr");

    background_.create((int)width, (int)hieght);

    sf::RectangleShape rec(sf::Vector2f((float)width, (float)hieght));
    rec.setPosition(0, 0);
    rec.setFillColor(sf::Color::White);

    background_.draw(rec);
}

//=======================================================================================

void Canvas::Draw(sf::RenderTarget &target, Container<Transform> &stack_transform)
{
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    Transform last_trf = stack_transform.GetBack();

    sf::VertexArray vertex_array(sf::Quads, 4);

    GetNewSize(vertex_array, last_trf);

    target.draw(vertex_array, &(background_.getTexture()));

    stack_transform.PopBack();
}

void Canvas::GetNewSize(sf::VertexArray &vertex_array, const Transform &transform) const
{
    vertex_array[0].position = transform.RollbackTransform({0, 0});
    vertex_array[1].position = transform.RollbackTransform({1, 0});
    vertex_array[2].position = transform.RollbackTransform({1, 1});
    vertex_array[3].position = transform.RollbackTransform({0, 1});

    float new_width  = vertex_array[1].position.x - vertex_array[0].position.x;
    float new_hieght = vertex_array[2].position.y - vertex_array[1].position.y;

    vertex_array[0].texCoords = sf::Vector2f((float)real_pos_.x, (float)real_pos_.y);
    vertex_array[1].texCoords = sf::Vector2f((float)real_pos_.x + (float)new_width - 1, (float)real_pos_.y);
    vertex_array[2].texCoords = sf::Vector2f((float)real_pos_.x + (float)new_width - 1, (float)real_pos_.y + (float)new_hieght - 1);
    vertex_array[3].texCoords = sf::Vector2f((float)real_pos_.x, (float)real_pos_.y + (float)new_hieght - 1);
}

//================================================================================

bool Canvas::OnMouseMoved(const double x, const double y, Container<Transform> &stack_transform)
{
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    Transform last_trf = stack_transform.GetBack();

    Dot new_coord = last_trf.ApplyTransform({x, y});
    

    bool flag = CheckIn(new_coord);
    if (flag)
    {
        if (tool_->state_ == Tool::State::Hold)
        {
            tool_->Draw(background_, GetCanvaseCoord(x, y, last_trf));
        }
    }

    stack_transform.PopBack();

    return flag;
}

//================================================================================

bool Canvas::OnMousePressed(const double x, const double y, const MouseKey key, Container<Transform> &stack_transform)
{
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    Transform last_trf = stack_transform.GetBack();
    
    Dot new_coord = last_trf.ApplyTransform({x, y});

    bool flag = CheckIn(new_coord);
    if (flag)
    {
        tool_->state_ = Tool::State::Hold;
        tool_->hold_pos_ = GetCanvaseCoord(x, y, stack_transform.GetBack());
    }

    stack_transform.PopBack();

    return flag;
}

//================================================================================

bool Canvas::OnMouseReleased(const double x, const double y, const MouseKey key, Container<Transform> &stack_transform)
{
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));

    tool_->state_ = Tool::State::Default;

    stack_transform.PopBack();

    return true;
}

Dot Canvas::GetCanvaseCoord(double x, double y, const Transform &transform) const
{
    return Dot(real_pos_.x + x - transform.offset.x, hieght_ - (real_pos_.y + y - transform.offset.y));
}

//================================================================================

bool Canvas::OnKeyboardPressed(const KeyboardKey key)
{
    printf("Canvas: mouse keyboard kye pressed\n");
    return false;
}

//================================================================================

bool Canvas::OnKeyboardReleased(const KeyboardKey key)
{
    printf("Canvas: mouse keyboard kye released\n");
    return false;
}

//================================================================================

void Canvas::PassTime(const time_t delta_time)
{
    printf("Canvas: mouse keyboard kye released\n");
}

//================================================================================

Dot Canvas::GetSize() const
{
    return Dot(width_, hieght_);
}


void Canvas::Move(const Dot &offset)
{
    real_pos_ += offset;
}

//================================================================================

Transform Canvas::GetTransform() const
{
    return transform_;
}


//================================================================================

Dot Canvas::GetRealPos () const
{
    return real_pos_;
}


void Canvas::CorrectRealCoord(const Transform &transform)
{
    if (real_pos_.x < Eps)
        real_pos_.x = Eps;

    if (real_pos_.y < Eps)
        real_pos_.y = Eps;

    if (real_pos_.x + transform.scale.x  > width_ - Eps)
        real_pos_.x =  width_ - Eps - transform.scale.x;

    if (real_pos_.y + transform.scale.y > hieght_ - Eps)
        real_pos_.y = hieght_ - Eps - transform.scale.y;    
}

//=======================================================================================
// //CONTAINER WINDOW

void CanvaseManager::Draw(sf::RenderTarget &target, Container<Transform> &stack_transform)
{
    Window::Draw(target, stack_transform);

    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));

    size_t size = canvases_.GetSize();
    for (size_t it = 0; it < size; it++)
        canvases_[it]->Draw(target, stack_transform);

    stack_transform.PopBack();

    return;
}

//=======================================================================================

bool CanvaseManager::OnMouseMoved(const double x, const double y, Container<Transform> &stack_transform)
{
    size_t size = canvases_.GetSize();
    if (size == 0) return false;
    
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    Transform last_trf = stack_transform.GetBack();
    
    Dot new_coord = last_trf.ApplyTransform({x, y});

    canvases_[size - 1]->OnMouseMoved(x, y, stack_transform);
    
    stack_transform.PopBack();

    return true;
}

//================================================================================

bool CanvaseManager::OnMousePressed(const double x, const double y, const MouseKey key, Container<Transform> &stack_transform)
{
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    Transform last_trf = stack_transform.GetBack();
    
    Dot new_coord = last_trf.ApplyTransform({x, y});

    bool flag = CheckIn(new_coord);

    if (flag)
    {
        int size = (int)canvases_.GetSize();
        for (int it = size - 1; it >= 0; it--)
        {
            delte_canvase_ = false;
            if (canvases_[it]->OnMousePressed(x, y, key, stack_transform))
            {
                canvases_.Drown(it);
                if (delte_canvase_)
                    canvases_.PopBack();

                break;
            }
        }
    }

    stack_transform.PopBack();

    return flag;
}

//================================================================================

bool CanvaseManager::OnMouseReleased(const double x, const double y, const MouseKey key, Container<Transform> &stack_transform)
{
    
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    Transform last_trf = stack_transform.GetBack();
    Dot new_coord = last_trf.ApplyTransform({x, y});

    int size = (int)canvases_.GetSize();
    for (int it = size - 1; it >= 0; it--)
    {
        canvases_[it]->OnMouseReleased(x, y, key, stack_transform);
    }

    stack_transform.PopBack();

    return true;
}
       Dot position_;
//================================================================================

bool CanvaseManager::OnKeyboardPressed(const KeyboardKey key)
{
    return false;
}

//================================================================================

bool CanvaseManager::OnKeyboardReleased(const KeyboardKey key)
{
    printf("Window: mouse keyboard kye released\n");
    return false;
}
//================================================================================

void CanvaseManager::CreateCanvase(Tool *tool)
{
    assert(tool != nullptr && "tool is nullptr");

    char *buf = (char*)calloc(BUFSIZ, sizeof(char));
    if (!buf)
    {
        PROCESS_ERROR(ERR_MEMORY_ALLOC, "allocate memory to buf failed\n");
        return;
    }

    cnt_++;
    sprintf(buf, "canvas %lu", cnt_);

    Button *close_button = new Button(Cross_Button_Release, Cross_Button_Covered, 
                                      Cross_Button_Release, Cross_Button_Covered, 
                                      new Click(&delte_canvase_), 
                                      Cross_Button_Offset, Cross_Button_Scale);

    Canvas *new_canvase = new Canvas(Width_Canvase, Hieght_Canvase, tool, Canvase_Offset, Canvase_Scale);


    Scrollbar *scroll = new Scrollbar(new_canvase, Scrollbar::Scroll_Type::Horizontal, Dot(0.02, 0.05), Vector(0.95, 0.87));

    Widget *new_frame = new Frame(Frame_Texture, close_button, {buf, sf::Color::Black}, 
                                  scroll, Canvase_Frame_Offset, Canvase_Frame_Scale);

    canvases_.PushBack(new_frame);
}

//================================================================================


Scrollbar::Scrollbar(Canvas *canvas, Scroll_Type type, const Dot &offset, const Vector &scale):
                     top_button_(nullptr), bottom_button_(nullptr), center_button_(nullptr),
                     canvas_(canvas), transform_({offset, scale}), pos_press_(offset), type_(type)
{
    top_button_ = new Button("src/img/left.png", "src/img/left.png", 
                            "src/img/left.png", "src/img/left.png", 
                            new ScrollCanvas(Dot(-0.05, 0), canvas), 
                            Dot(0.0, 0), Vector(0.03, 0.03));

    bottom_button_ = new Button("src/img/right.png", "src/img/right.png", 
                                "src/img/right.png", "src/img/right.png", 
                                new ScrollCanvas(Vector(0.05, 0), canvas), 
                                Dot(0.97, 0), Vector(0.03, 0.03));

    center_button_ = new Button("src/img/horizontal.png", "src/img/horizontal.png", 
                                "src/img/horizontal.png", "src/img/horizontal.png", 
                                new ScrollCanvas(Dot(0, 0), canvas), 
                                Dot(0.032, 0.0), Vector(0.4, 0.03));

    return;

}

void Scrollbar::Draw(sf::RenderTarget &target, Container<Transform> &stack_transform)
{
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    Transform last_trf = stack_transform.GetBack();


    ResizeCenterButton(canvas_->GetTransform().ApplyPrev(last_trf));
    

    top_button_->Draw(target, stack_transform);
    bottom_button_->Draw(target, stack_transform);
    center_button_->Draw(target, stack_transform);
    
    canvas_->Draw(target, stack_transform);

    stack_transform.PopBack();

    return;
}


void Scrollbar::ResizeCenterButton(const Transform &canvas_trf)
{
   
    Dot size = canvas_->GetSize();

    Transform center_trf = center_button_->GetTransform();
    
    if (type_ == Scrollbar::Scroll_Type::Horizontal)
        center_trf.scale.x = canvas_trf.scale.x / size.x; 
    
    if (type_ == Scrollbar::Scroll_Type::Vertical)
        center_trf.scale.y = canvas_trf.scale.y / size.y; 
    
    center_button_->SetTransform(center_trf);
    canvas_->CorrectRealCoord(canvas_trf);

    Dot prev = canvas_->GetRealPos();
    MoveCenter(prev);

}



//================================================================================

bool Scrollbar::OnMouseMoved(const double x, const double y, Container<Transform> &stack_transform)
{
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    Transform last_trf = stack_transform.GetBack();

    bool flag = flag = canvas_->OnMouseMoved(x, y, stack_transform);;

    top_button_->OnMouseMoved(x, y, stack_transform);
    bottom_button_->OnMouseMoved(x, y, stack_transform);
    center_button_->OnMouseMoved(x, y, stack_transform);

    Dot new_coord = last_trf.ApplyTransform({x, y});
    
    if (center_button_->prev_state_ == Button::Button_State::Pressed || 
        center_button_->state_ == Button::Button_State::Pressed)
    {
        Dot prev_real_pos = canvas_->GetRealPos();
        
        if (type_ == Scrollbar::Scroll_Type::Horizontal)
            canvas_->Move(Dot((new_coord.x - pos_press_.x) * canvas_->GetSize().x, 0));
        if (type_ == Scrollbar::Scroll_Type::Vertical)
            canvas_->Move(Dot(0.0, (new_coord.y - pos_press_.y) * canvas_->GetSize().y));

        canvas_->CorrectRealCoord(canvas_->GetTransform().ApplyPrev(last_trf));

        MoveCenter(prev_real_pos);
        pos_press_ = new_coord;

    }
    
    stack_transform.PopBack();

    return flag;
}

void Scrollbar::MoveCenter(Dot &prev_pos)
{
    Transform center_trf = center_button_->GetTransform();

    Transform top_trf    = top_button_->GetTransform();
    Transform bottom_trf = bottom_button_->GetTransform();


    Dot offset((canvas_->GetRealPos().x - prev_pos.x) / canvas_->GetSize().x, 0.0);

    offset.x = std::min(bottom_trf.offset.x - Eps - (center_trf.offset.x + center_trf.scale.x), 
                        std::max(top_trf.offset.x + top_trf.scale.x + Eps - center_trf.offset.x, offset.x));
  
    center_trf.offset += offset;

    center_button_->SetTransform(center_trf);
    
    return;
}

//================================================================================

bool Scrollbar::OnMousePressed(const double x, const double y, const MouseKey key, Container<Transform> &stack_transform)
{
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    Transform last_trf = stack_transform.GetBack();

    Dot new_coord = last_trf.ApplyTransform({x, y});
    pos_press_ = new_coord;

    Dot prev_real_pos = canvas_->GetRealPos();

    bool flag = false;
    flag |= top_button_->OnMousePressed(x, y, key, stack_transform);
    flag |= bottom_button_->OnMousePressed(x, y, key, stack_transform);

    flag |= center_button_->OnMousePressed(x, y, key, stack_transform);
    flag |= canvas_->OnMousePressed(x, y, key, stack_transform);;

    if (!flag)
    {
        flag = CheckIn(new_coord);

        if (flag)
        {

            Dot offset = new_coord - center_button_->GetTransform().offset;

            if (type_ == Scrollbar::Scroll_Type::Horizontal)
                offset.y = 0.0;
            if (type_ == Scrollbar::Scroll_Type::Vertical)
                offset.x = 0.0;
           

            if (offset.x < -Eps || offset.y < -Eps)
                (*top_button_->action_)();
            
            if (offset.x > Eps || offset.y > Eps)
                (*bottom_button_->action_)();
        }
    } 

    canvas_->CorrectRealCoord(canvas_->GetTransform().ApplyPrev(last_trf));
    MoveCenter(prev_real_pos);

    stack_transform.PopBack();

    return flag;
}

//================================================================================

bool Scrollbar::OnMouseReleased(const double x, const double y, const MouseKey key, Container<Transform> &stack_transform)
{
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));

    top_button_->OnMouseReleased(x, y, key, stack_transform);
    bottom_button_->OnMouseReleased(x, y, key, stack_transform);
    center_button_->OnMouseReleased(x, y, key, stack_transform);
    
    canvas_->OnMouseReleased(x, y, key, stack_transform);

    stack_transform.PopBack();

    return true;
}

//================================================================================

bool Scrollbar::OnKeyboardPressed(const KeyboardKey key)
{
    printf("Scrollbar: mouse keyboard kye pressed\n");
    return false;
}

//================================================================================

bool Scrollbar::OnKeyboardReleased(const KeyboardKey key)
{
    printf("Scrollbar: mouse keyboard kye released\n");
    return false;
}

//================================================================================

void Scrollbar::PassTime(const time_t delta_time)
{
    printf("Scrollbar: mouse keyboard kye released\n");
    return;
}