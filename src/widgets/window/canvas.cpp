#include "canvas.h"
#include "canvas_config.h"
#include "../../app/config.h"

#include "tools/tools.h"
#include "filters/filter.h"


Canvas::Canvas( ToolPalette *tool_palette, FilterPalette *filter_palette,
                const Vector &canvas_size,
                const Vector &size, const Vector &pos, 
                const Widget *parent, const Vector &parent_size, 
                const Vector &origin, const Vector &scale):
                Window(Debug_texture, size, pos, parent, (parent != nullptr) ? parent->getLayoutBox().getSize() : parent_size, origin, scale),
                tool_palette_(*tool_palette), filter_palette_(*filter_palette), 
                filter_mask_(*(new FilterMask(canvas_size.x, canvas_size.y))),
                background_(), canvas_size_(canvas_size), real_pos_(0, 0) 
{
    background_.create((uint32_t)canvas_size.x, (uint32_t)canvas_size.y);

    sf::RectangleShape rec(sf::Vector2f((float)canvas_size.x, (float)canvas_size.y));
    rec.setPosition(0, 0);
    rec.setFillColor(sf::Color::White);

    background_.draw(rec);

    filter_mask_.fill(true);
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

    if (focused_)
    {
        Tool *active_tool = tool_palette_.getActiveTool(); 
        if (active_tool) 
        {
            Widget *preview = active_tool->getWidget();
            if (preview) preview->draw(target, stack_transform);
        }
    }

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
        Tool *active_tool = tool_palette_.getActiveTool(); 
        if (active_tool) active_tool->onMove(local_pos, *this);
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
    if (flag && key == MouseKey::LEFT)
    {
        Tool *active_tool = tool_palette_.getActiveTool(); 
        if (active_tool) active_tool->onMainButton({ControlState::ButtonState::PRESSED}, local_pos, *this);
    }
    
    focused_ = flag;

    stack_transform.popBack();

    return flag;
}

//================================================================================

bool Canvas::onMouseReleased(const Vector& pos, const MouseKey key, Container<Transform> &stack_transform)
{
    if (key == MouseKey::LEFT)
    {
        Tool *active_tool = tool_palette_.getActiveTool(); 
        if (active_tool) active_tool->onConfirm(*this);
    }

    return true;
}

Dot Canvas::getCanvaseCoord(const Vector &local_pos) const
{
    return Dot(real_pos_.x + local_pos.x, canvas_size_.y - (real_pos_.y + local_pos.y) );
}

//================================================================================

bool Canvas::onKeyboardPressed(const KeyboardKey key)
{
    printf("asddsa\n");
    if (filter_palette_.getActive())
    {
       
        Filter *filter = nullptr;
        if (key == KeyboardKey::L)
        {
            filter  = filter_palette_.getFilter(FilterPalette::FilterType::LIGHT);
            filter_palette_.setLastFilter(FilterPalette::FilterType::LIGHT);
        }

        if (key == KeyboardKey::F)
            filter  = filter_palette_.getLastFilter();
        
        if (filter)
        {
            filter->applyFilter(*this, filter_mask_);
            return true;
        }
    }

    return false;
}

//================================================================================

bool Canvas::onKeyboardReleased(const KeyboardKey key)
{
   if (key == KeyboardKey::ENTER)
    {
        Tool *active_tool = tool_palette_.getActiveTool(); 
        if (active_tool) active_tool->onConfirm(*this);

        return true;
    }

    if (key == KeyboardKey::ESC)
    {
        Tool *active_tool = tool_palette_.getActiveTool(); 
        if (active_tool) active_tool->onCancel();

        return true;
    }

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

FilterMask& Canvas::getFilterMask ()
{
    return filter_mask_;
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

sf::RenderTexture& Canvas::getBackground()
{
    return background_;
}

// //=======================================================================================
// // //CONTAINER WINDOW

CanvasManager::CanvasManager(   const char *path_texture,
                                const Vector &size, const Vector &pos, 
                                const Widget *parent, const Vector &parent_size,  
                                const Vector &origin, const Vector &scale):
                                Window(path_texture, size, pos, parent, (parent != nullptr) ? parent->getLayoutBox().getSize() : parent_size, origin, scale),
                                canvases_(), delete_canvas_(false), cnt_(){}



void CanvasManager::draw(sf::RenderTarget &target, Container<Transform> &stack_transform)
{
    Window::draw(target, stack_transform);

    Transform trf(getLayoutBox().getPosition(), scale_);
    stack_transform.pushBack(trf.applyPrev(stack_transform.getBack()));

    size_t size = widgets_.getSize();
    for (size_t it = 0; it < size; it++)
        widgets_[it]->draw(target, stack_transform);

    stack_transform.popBack();

    return;
}

//=======================================================================================

bool CanvasManager::onMouseMoved(const Vector &pos, Container<Transform> &stack_transform)
{
    size_t size = widgets_.getSize();
    if (size == 0) return false;
    
    Transform trf(getLayoutBox().getPosition(), scale_);
    stack_transform.pushBack(trf.applyPrev(stack_transform.getBack()));

    widgets_[size - 1]->onMouseMoved(pos, stack_transform);
    
    stack_transform.popBack();

    return true;
}

//================================================================================

bool CanvasManager::onMousePressed(const Vector &pos, const MouseKey key, Container<Transform> &stack_transform)
{
    Transform trf(getLayoutBox().getPosition(), scale_);
    stack_transform.pushBack(trf.applyPrev(stack_transform.getBack()));

    bool flag = false;

    int size = (int)widgets_.getSize();
    for (int it = size - 1; it >= 0; it--)
        widgets_[it]->setFocus(false);

    for (int it = size - 1; it >= 0; it--)
    {
        delete_canvas_ = false;
        if (widgets_[it]->onMousePressed(pos, key, stack_transform))
        {
            widgets_.drown(it);
            canvases_.drown(it);
            
            if (delete_canvas_)
            {
                widgets_.popBack();
                canvases_.popBack();
            }

            break;
        }
    }

    stack_transform.popBack();

    return flag;
}

//================================================================================

bool CanvasManager::onMouseReleased(const Vector &pos, const MouseKey key, Container<Transform> &stack_transform)
{
    Transform trf(getLayoutBox().getPosition(), scale_);
    stack_transform.pushBack(trf.applyPrev(stack_transform.getBack()));

    int size = (int)widgets_.getSize();
    for (int it = size - 1; it >= 0; it--)
    {
        widgets_[it]->onMouseReleased(pos, key, stack_transform);
    }

    stack_transform.popBack();

    return true;
}

//================================================================================

bool CanvasManager::onKeyboardPressed(const KeyboardKey key)
{
    size_t size = widgets_.getSize();
    if (size == 0)
        return false;

    return widgets_[size - 1]->onKeyboardPressed(key);
}

//================================================================================

bool CanvasManager::onKeyboardReleased(const KeyboardKey key)
{
    size_t size = widgets_.getSize();
    if (size == 0)
        return false;

    return widgets_[size - 1]->onKeyboardReleased(key);
}
//================================================================================

void CanvasManager::createCanvas(ToolPalette *tool_palette, FilterPalette *filter_palette)
{
    assert(tool_palette != nullptr && "tool_palette is nullptr");
    assert(filter_palette != nullptr && "filter_palette is nullptr");

    char *buf = (char*)calloc(BUFSIZ, sizeof(char));
    if (!buf)
    {
        PROCESS_ERROR(ERR_MEMORY_ALLOC, "allocate memory to buf failed\n");
        return;
    }

    cnt_++;
    sprintf(buf, "canvas %lu", cnt_);

    Frame *frame = new Frame(   "src/img/frame.png", Title(Title_offset, buf, sf::Color::Black), 
                                Frame_size, Frame_pos, this);

    Button *close_btn = new Button( Cross_Button_Release, Cross_Button_Covered, 
                                    Cross_Button_Release, Cross_Button_Covered, 
                                    new Click(&delete_canvas_), 
                                    Close_button_size, Close_button_pos, frame);

    Canvas *canvas = new Canvas(    tool_palette, filter_palette, Canvas_size,
                                    Canvas_view_size, Canvas_pos, frame);

    canvases_.pushBack(canvas);

    
    Scrollbar *scroll_hor = new Scrollbar(  canvas, Scrollbar::Type::HORIZONTAL, 
                                            Scroll_hor_size, Scroll_hor_pos, frame);

    Button *left_btn = new Button(  Left_Scl_Rel, Left_Scl_Prs, Left_Scl_Rel, Left_Scl_Prs,
                                    new ScrollCanvas(Dot(-5.0, 0.0), canvas), 
                                    Buttons_scroll_size, Left_pos, scroll_hor);

    Button *right_btn = new Button( Right_Scl_Rel, Right_Scl_Prs, Right_Scl_Rel, Right_Scl_Prs, 
                                    new ScrollCanvas(Vector(5.0, 0.0), canvas), 
                                    Buttons_scroll_size, Right_pos, scroll_hor);

    Button *hor_btn = new Button(   Hor_Scl, Hor_Scl, Hor_Scl, Hor_Scl, 
                                    new ScrollCanvas(Dot(0, 0), canvas), 
                                    Buttons_scroll_size, Vector(0.0, 0.0), scroll_hor);
    
    Scrollbar *scroll_ver = new Scrollbar(  canvas, Scrollbar::Type::VERTICAL, 
                                            Scroll_ver_size, Scroll_ver_pos, frame);

    Button *up_btn = new Button(    Up_Scl_Rel, Up_Scl_Prs, Up_Scl_Rel, Up_Scl_Prs, 
                                    new ScrollCanvas(Dot(0.0, -5.0), canvas), 
                                    Buttons_scroll_size, Up_pos, scroll_ver);

    Button *down_btn = new Button(  Down_Scl_Rel, Down_Scl_Prs, Down_Scl_Rel, Down_Scl_Prs, 
                                    new ScrollCanvas(Vector(0.0, 5.0), canvas), 
                                    Buttons_scroll_size, Down_pos, scroll_ver);

    Button *ver_btn = new Button(   Ver_Scl, Ver_Scl, Ver_Scl, Ver_Scl, 
                                    new ScrollCanvas(Dot(0, 0), canvas), 
                                    Buttons_scroll_size, Vector(0.0, 0.0), scroll_ver);


    scroll_hor->addButtons(left_btn, right_btn, hor_btn);
    scroll_ver->addButtons(up_btn, down_btn, ver_btn);

    frame->addWidget(close_btn);
    frame->addWidget(scroll_hor);
    frame->addWidget(scroll_ver);
    frame->addWidget(canvas);
    
    frame->onUpdate(getLayoutBox());

    widgets_.pushBack(frame);
}

//================================================================================

Canvas* CanvasManager::getActiveCanvas()
{
    size_t size = canvases_.getSize();
    if (size == 0)
        return nullptr;

    return canvases_[size - 1];
}

//================================================================================

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

    if (type_ == Scrollbar::Type::HORIZONTAL)
        layout_box->setSize(Vector(layout_box->getSize().x, size.y));
    
    bottom_button_->onUpdate(*layout_box);
    center_button_->onUpdate(*layout_box);
    top_button_->onUpdate(*layout_box);

    moveCenter();
    resizeCenter();
}
