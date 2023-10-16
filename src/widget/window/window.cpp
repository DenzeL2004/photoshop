#include "window.h"
#include "../decorator/decorator.h"

Window::Window (const char *path_texture,
                const Dot &offset, const Vector &scale):
               transform_({offset, scale}),
               width_(0), hieght_(0), background_() 
{

    if (!background_.loadFromFile(path_texture))   
    {
        PROCESS_ERROR(LOAD_TEXTURE_ERR, "failed load tetxure from %s\n", path_texture);
        return;
    }

    width_  = background_.getSize().x;
    hieght_ = background_.getSize().y;

    return;
}

//================================================================================

void Window::Draw(sf::RenderTarget &target, Container<Transform> &stack_transform)
{
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    Transform last_trf = stack_transform.GetBack();

    sf::VertexArray vertex_array(sf::Quads, 4);

    GetNewSize(vertex_array, last_trf);
    
    target.draw(vertex_array, &background_);

    stack_transform.PopBack();

    return;
}

void Window::GetNewSize(sf::VertexArray &vertex_array, const Transform &transform) const
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

//================================================================================

bool Window::OnMouseMoved(const double x, const double y, Container<Transform> &stack_transform)
{
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    Transform last_trf = stack_transform.GetBack();
    
    Dot new_coord = last_trf.ApplyTransform({x, y});

    bool flag = CheckIn(new_coord);

    stack_transform.PopBack();

    return flag;
}

//================================================================================

bool Window::OnMousePressed(const double x, const double y, const MouseKey key, Container<Transform> &stack_transform)
{
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    Transform last_trf = stack_transform.GetBack();
    
    Dot new_coord = last_trf.ApplyTransform({x, y});

    bool flag = CheckIn(new_coord);

    stack_transform.PopBack();

    return flag;
}

//================================================================================

bool Window::OnMouseReleased(const double x, const double y, const MouseKey key, Container<Transform> &stack_transform)
{
    printf("Window: mouse released\n");
    return false;
}

//================================================================================

bool Window::OnKeyboardPressed(const KeyboardKey key)
{
    printf("Window: mouse keyboard kye pressed\n");
    return false;
}

//================================================================================

bool Window::OnKeyboardReleased(const KeyboardKey key)
{
    printf("Window: mouse keyboard kye released\n");
    return false;
}

//================================================================================

void Window::PassTime(const time_t delta_time)
{
    printf("Window: mouse keyboard kye released\n");
    return;
}

//=======================================================================================

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

    return;
}

//=======================================================================================
//CANVASE

Canvas::Canvas(const double width, const double hieght, Tool *tool, 
                 const Dot &offset, const Vector &scale):
                  transform_({offset, scale}),
                  width_(width), hieght_(hieght), tool_(tool),
                  background_(), real_pos_(20, 20) 
{
    assert(tool != nullptr && "tool is nullptr");

    background_.create((int)width, (int)hieght);

    sf::RectangleShape rec(sf::Vector2f((float)width, (float)hieght));
    rec.setPosition(0, 0);
    rec.setFillColor(sf::Color::White);

    background_.draw(rec);

    return;
}

//=======================================================================================

void Canvas::Draw(sf::RenderTarget &target, Container<Transform> &stack_transform)
{
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    Transform last_trf = stack_transform.GetBack();

    sf::VertexArray vertex_array(sf::Quads, 4);

    CorrectRealCoord(last_trf);
    GetNewSize(vertex_array, last_trf);

    target.draw(vertex_array, &(background_.getTexture()));

    stack_transform.PopBack();

    return;
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

    return;
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
    return;
}

//================================================================================

void Canvas::Move(const Dot &offset)
{
    real_pos_ += offset;
    return;
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

    Button *top_button = new Button("src/img/left.png", "src/img/left.png", 
                                    "src/img/left.png", "src/img/left.png", 
                                    new ScrollCanvas(Dot(-10, 0), new_canvase), 
                                    Dot(0.025, 0), Vector(0.03, 0.03));

    Button *bottom_button = new Button("src/img/right.png", "src/img/right.png", 
                                       "src/img/right.png", "src/img/right.png", 
                                       new ScrollCanvas(Vector(10, 0), new_canvase), 
                                       Dot(0.995, 0), Vector(0.03, 0.03));

    Button *center_button = new Button("src/img/horizontal.png", "src/img/horizontal.png", 
                                       "src/img/horizontal.png", "src/img/horizontal.png", 
                                       new ScrollCanvas(Dot(0, 0), new_canvase), 
                                       Dot(0.05, 0.0), Vector(0.1, 0.03));

    Scrollbar *scroll = new Scrollbar(top_button, bottom_button, center_button, new_canvase, Dot(0, 0.05), Vector(0.95, 0.87));

    Widget *new_frame = new Frame(Frame_Texture, close_button, {buf, sf::Color::Black}, 
                                  scroll, Canvase_Frame_Offset, Canvase_Frame_Scale);

    canvases_.PushBack(new_frame);
}
