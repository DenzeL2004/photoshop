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
                const Vector &size, const Vector &pos, 
                const Widget *parent, const Vector &parent_size, 
                const Vector &origin, const Vector &scale):
                Window(Debug_texture, size, pos, parent, (parent != nullptr) ? parent->getLayoutBox().getSize() : parent_size, origin, scale),
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


void Canvas::setRealPos (const Vector &new_pos)
{
    real_pos_ = new_pos;
}  

Vector Canvas::getRealPos () const
{
    return real_pos_;
}  

Vector Canvas::getCanvasSize () const
{
    return canvas_size_;
}

void Canvas::correctCanvasRealPos(const Vector &abs_size)
{
    if (real_pos_.x < Eps)
        real_pos_.x = 0.0;

    if (real_pos_.y < Eps)
        real_pos_.y = 0;

    if (real_pos_.x + abs_size.x >= canvas_size_.x - Eps)
        real_pos_.x = canvas_size_.x - abs_size.x;

    if (real_pos_.y + abs_size.y >= canvas_size_.y - Eps)
        real_pos_.y = canvas_size_.y - abs_size.y;
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
    
//     Dot local_pos = last_trf.ApplyTransform({pos});

//     canvases_[size - 1]->onMouseMoved(pos, stack_transform);
    
//     stack_transform.PopBack();

//     return true;
// }

// //================================================================================

// bool CanvaseManager::onMousePressed(const Vector& pos, const MouseKey key, Container<Transform> &stack_transform)
// {
//     stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
//     Transform last_trf = stack_transform.GetBack();
    
//     Dot local_pos = last_trf.ApplyTransform({pos});

//     bool flag = CheckIn(local_pos);

//     if (flag)
//     {
//         int size = (int)canvases_.GetSize();
//         for (int it = size - 1; it >= 0; it--)
//         {
//             delte_canvase_ = false;
//             if (canvases_[it]->onMousePressed(pos, key, stack_transform))
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
//     Dot local_pos = last_trf.ApplyTransform({pos});

//     int size = (int)canvases_.GetSize();
//     for (int it = size - 1; it >= 0; it--)
//     {
//         canvases_[it]->onMouseReleased(pos, key, stack_transform);
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
//                                      Scrollbar::Type::HORIZONTAL, Dot(0.00, 0.00), Vector(1.0, 1.0));

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
//                                      Scrollbar::Type::VERTICAL, Dot(0.96, 0.05), Vector(1.0, 1.0));
   

//     scrolls->AddWidget(new_canvase);
//     scrolls->AddWidget(scroll_hor);
//     scrolls->AddWidget(scroll_ver);

//     Widget *new_frame = new Frame(Frame_Texture, close_btn, {buf, sf::Color::Black}, 
//                                   scrolls, Canvase_Frame_Offset, Canvase_Frame_Scale);

//     canvases_.PushBack(new_frame);
// }

// //================================================================================

Scrollbar::Scrollbar(   Canvas *canvas, const Type type,
                        const Vector &size, const Vector &pos, 
                        const Widget *parent, const Vector &parent_size,  
                        const Vector &origin, const Vector &scale):
                        Widget(size, pos, parent, (parent != nullptr) ? parent->getLayoutBox().getSize() : parent_size, origin, scale),
                        top_button_(nullptr), bottom_button_(nullptr), center_button_(nullptr),
                        canvas_(canvas), hold_pos_(Dot(0.0, 0.0)), prev_canvas_real_pos_(0.0, 0.0), type_(type)
{
    setLayoutBox(*(new BaseLayoutBox(pos, size, (parent != nullptr) ? parent->getLayoutBox().getSize() : parent_size, true, true))); 
}


void Scrollbar::addButtons(Button *top_button, Button *bottom_button, Button *center_button)
{
    assert(top_button != nullptr && bottom_button != nullptr && center_button != nullptr);

    top_button_= top_button;
    bottom_button_ = bottom_button;
    center_button_ = center_button;
}

//================================================================================

void Scrollbar::draw(sf::RenderTarget &target, Container<Transform> &stack_transform)
{
    Transform trf(getLayoutBox().getPosition(), scale_);

    stack_transform.pushBack(trf.applyPrev(stack_transform.getBack()));
    Transform last_trf = stack_transform.getBack();    

    float abs_width  = (float)(trf.scale.x * getLayoutBox().getSize().x);
    float abs_height = (float)(trf.scale.y * getLayoutBox().getSize().y);
    
    canvas_->correctCanvasRealPos(Vector(abs_width, abs_height));
    
    top_button_->draw(target, stack_transform);
    bottom_button_->draw(target, stack_transform);
    center_button_->draw(target, stack_transform);

    stack_transform.popBack();

    return;
}

//================================================================================

bool Scrollbar::onMouseMoved(const Vector& pos, Container<Transform> &stack_transform)
{
    Transform trf(getLayoutBox().getPosition(), scale_);

    stack_transform.pushBack(trf.applyPrev(stack_transform.getBack()));
    Transform last_trf = stack_transform.getBack();    

    top_button_->onMouseMoved(pos, stack_transform);
    bottom_button_->onMouseMoved(pos, stack_transform);
    center_button_->onMouseMoved(pos, stack_transform);

    Dot local_pos = last_trf.applyTransform(pos);
    
    if (center_button_->prev_state_ == Button::ButtonState::PRESSED || 
        center_button_->state_ == Button::ButtonState::PRESSED)
    {
        Dot real_pos = canvas_->getRealPos();
        Dot center_button_pos = center_button_->getLayoutBox().getPosition();
        
        Vector scrollbar_size = getLayoutBox().getSize() - top_button_->getLayoutBox().getSize() - bottom_button_->getLayoutBox().getSize();

        if (type_ == Scrollbar::Type::HORIZONTAL)
        {
            canvas_->setRealPos(Dot(prev_canvas_real_pos_.x + (local_pos.x - hold_pos_.x) / scrollbar_size.x * canvas_->getCanvasSize().x, real_pos.y));
            center_button_->getLayoutBox().setPosition(Dot(local_pos.x - hold_pos_.x, center_button_pos.y));
        }

        if (type_ == Scrollbar::Type::VERTICAL)
        {
            canvas_->setRealPos(Dot(real_pos.x, prev_canvas_real_pos_.y + (local_pos.y - hold_pos_.y) / scrollbar_size.y * canvas_->getCanvasSize().y));
            center_button_->getLayoutBox().setPosition(Dot(center_button_pos.x, local_pos.y - hold_pos_.y));
        }

        float abs_width  = (float)(trf.scale.x * getLayoutBox().getSize().x);
        float abs_height = (float)(trf.scale.y * getLayoutBox().getSize().y);

        canvas_->correctCanvasRealPos(Vector(abs_width, abs_height));
        moveCenter();
    }
    
    stack_transform.popBack();

    return true;
}

void Scrollbar::moveCenter()
{
    Vector canvas_size = canvas_->getCanvasSize();
    Vector canvas_pos = canvas_->getRealPos();

    double cf_x = canvas_pos.x / canvas_size.x;
    double cf_y = canvas_pos.y / canvas_size.y;
    
    Vector center_button_pos = center_button_->getLayoutBox().getPosition();

    Vector scrollbar_size = getLayoutBox().getSize() - top_button_->getLayoutBox().getSize() - bottom_button_->getLayoutBox().getSize();

    if (type_ == Scrollbar::Type::HORIZONTAL)
        center_button_pos = Vector(cf_x * scrollbar_size.x + top_button_->getLayoutBox().getSize().x, center_button_pos.y); 

    if (type_ == Scrollbar::Type::VERTICAL)
        center_button_pos = Vector(center_button_pos.x, cf_y * scrollbar_size.y + top_button_->getLayoutBox().getSize().y); 
    
    center_button_->getLayoutBox().setPosition(center_button_pos);
}

void Scrollbar::resizeCenter()
{
    Vector canvas_size = canvas_->getCanvasSize();
    
    double cf_x = std::min(1.0, getLayoutBox().getSize().x / canvas_size.x);
    double cf_y = std::min(1.0, getLayoutBox().getSize().y / canvas_size.y);
    
    Vector center_button_size = center_button_->getLayoutBox().getSize();

    Vector scrollbar_size = getLayoutBox().getSize() - top_button_->getLayoutBox().getSize() - bottom_button_->getLayoutBox().getSize();

    if (type_ == Scrollbar::Type::HORIZONTAL)
        center_button_size = Vector(cf_x * scrollbar_size.x, center_button_size.y); 

    if (type_ == Scrollbar::Type::VERTICAL)
        center_button_size = Vector(center_button_size.x, cf_y * scrollbar_size.y); 
    
    center_button_->getLayoutBox().setSize(center_button_size);
}

//================================================================================

bool Scrollbar::onMousePressed(const Vector& pos, const MouseKey key, Container<Transform> &stack_transform)
{
    LayoutBox *layout_box =  &getLayoutBox();

    Transform trf(layout_box->getPosition(), scale_);

    stack_transform.pushBack(trf.applyPrev(stack_transform.getBack()));
    Transform last_trf = stack_transform.getBack();    

    Dot local_pos = last_trf.applyTransform(pos);
 
    prev_canvas_real_pos_ = canvas_->getRealPos();

    bool flag = false;

    if (checkIn(local_pos, layout_box->getSize()))
    {
        

        flag |= center_button_->onMousePressed(pos, key, stack_transform);
        flag |= top_button_->onMousePressed(pos, key, stack_transform);
        flag |= bottom_button_->onMousePressed(pos, key, stack_transform);

        if (flag)
            hold_pos_ = local_pos;

        if (!flag)
        {
            Dot offset = local_pos - center_button_->getLayoutBox().getPosition();

            if (type_ == Scrollbar::Type::HORIZONTAL)
                offset.y = 0.0;
            if (type_ == Scrollbar::Type::VERTICAL)
                offset.x = 0.0;

            if (offset.x < -Eps || offset.y < -Eps)
                (*top_button_->action_)();
            
            if (offset.x > Eps || offset.y > Eps)
                (*bottom_button_->action_)();

            flag = true;
        }
        

        float abs_width  = (float)(trf.scale.x * layout_box->getSize().x);
        float abs_height = (float)(trf.scale.y * layout_box->getSize().y);

        canvas_->correctCanvasRealPos(Vector(abs_width, abs_height));
    }
    
    moveCenter();

    stack_transform.popBack();

    return flag;
}

//================================================================================

bool Scrollbar::onMouseReleased(const Vector& pos, const MouseKey key, Container<Transform> &stack_transform)
{
    Transform trf(getLayoutBox().getPosition(), scale_);
    stack_transform.pushBack(trf.applyPrev(stack_transform.getBack()));

    hold_pos_ = Dot(0.0, 0.0);

    top_button_->onMouseReleased(pos, key, stack_transform);
    bottom_button_->onMouseReleased(pos, key, stack_transform);
    center_button_->onMouseReleased(pos, key, stack_transform);

    stack_transform.popBack();

    return true;
}

//================================================================================

bool Scrollbar::onKeyboardPressed(const KeyboardKey key)
{
    printf("Scrollbar: mouse keyboard kye pressed\n");
    return false;
}

//================================================================================

bool Scrollbar::onKeyboardReleased(const KeyboardKey key)
{
    printf("Scrollbar: mouse keyboard kye released\n");
    return false;
}

//=================================================================================

void Scrollbar::onUpdate (const LayoutBox &parent_layout)
{
    LayoutBox *layout_box =  &getLayoutBox();
    Vector size = layout_box->getSize();

    layout_box->onParentUpdate(parent_layout);

    if (type_ == Scrollbar::Type::VERTICAL)
        layout_box->setSize(Vector(size.x, layout_box->getSize().y));
    
    bottom_button_->onUpdate(*layout_box);
    center_button_->onUpdate(*layout_box);
    top_button_->onUpdate(*layout_box);

    moveCenter();
    resizeCenter();
}
