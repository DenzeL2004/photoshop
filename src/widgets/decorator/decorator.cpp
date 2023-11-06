#include "decorator.h"

const Dot Offset_Title = Dot(0.45, 0.0);
const double Tittle_size  = 10u;

const double Border_width = 10;

//=================================================================================================

Frame::Frame(   const char *path_texture,
                const Title &title,
                const Vector &size, const Vector &pos, 
                const Widget *parent, const Vector &parent_size, 
                const Vector &origin, const Vector &scale):
                Window(path_texture, size, pos, parent, (parent != nullptr) ? parent->getLayoutBox().getSize() : parent_size, origin, scale),  
                title_(title), widgets_(),
                state_(DEFAULT), hold_pos_({0.0, 0.0}), prev_pos_({0.0, 0.0}){}

void Frame::draw(sf::RenderTarget &target, Container<Transform> &stack_transform)
{
    Transform trf(getLayoutBox().getPosition(), scale_);

    stack_transform.pushBack(trf.applyPrev(stack_transform.getBack()));
    Transform last_trf = stack_transform.getBack();    

    sf::VertexArray vertex_array(sf::Quads, 4);

    getDrawFormat(vertex_array, last_trf);

    target.draw(vertex_array, &texture_);

    sf::Vector2f abs_pos = last_trf.rollbackTransform(Dot(0.0, 0.0));

    writeText(target, Dot(abs_pos.x + title_.pos_.x, abs_pos.y + title_.pos_.y), 
              title_.msg_, Oldtimer_font_path, Tittle_size, title_.color_);

    size_t cnt = widgets_.getSize();
    for (size_t it = 0; it < cnt; it++)
    {
       widgets_[it]->draw(target, stack_transform);
    }

    stack_transform.popBack();
}

//================================================================================

bool Frame::onMouseMoved(const Vector &pos, Container<Transform> &stack_transform)
{
    Transform trf(getLayoutBox().getPosition(), scale_);

    stack_transform.pushBack(trf.applyPrev(stack_transform.getBack()));
    Transform last_trf = stack_transform.getBack();    

    Dot new_coord = last_trf.applyTransform(pos);
    
    if(state_)
    {
        if (state_ == Borders::TOP)
            moveFrame(new_coord);
        else
            resizeFrame(new_coord);
    }  
    else
    {
        size_t cnt = widgets_.getSize();
        for (size_t it = 0; it < cnt; it++)
        {
            widgets_[it]->onMouseMoved(pos, stack_transform);
        }
    }

    stack_transform.popBack();

    return true;
}

//================================================================================
void Frame::clickOnBorder()
{
    Vector size = getLayoutBox().getSize();

    state_ = 0;

    if (hold_pos_.x > Eps && hold_pos_.x < Border_width - Eps)
        state_ |= Frame::Borders::LEFT;

    if (hold_pos_.x > size.x - Border_width + Eps && hold_pos_.x < size.x - Eps)
        state_ |= Frame::Borders::RIGHT;

    if (hold_pos_.y > size.y - Border_width + Eps && hold_pos_.y < size.y - Eps)
        state_ |= Frame::Borders::BOTTOM;
}


void Frame::resizeFrame(const Dot &new_coord)
{
    LayoutBox* layout_box = &getLayoutBox();

    Vector size = layout_box->getSize();

    Vector pos = layout_box->getPosition();

    Vector delta = new_coord - prev_pos_;
   
    if (state_ & Frame::Borders::LEFT) 
    {
        if (size.x <= Size_min_limit.x + Eps) return;
        moveFrame(Dot(new_coord.x, hold_pos_.y));
        
        delta.x = pos.x - layout_box->getPosition().x;
    }    

    Vector new_size = size;

    if (state_ & Frame::Borders::LEFT || state_ & Frame::Borders::RIGHT)
        new_size += Vector(delta.x, 0.0);

    if (state_ & Frame::Borders::BOTTOM)
        new_size += Vector(0.0, delta.y);

    if (new_size.x >= Size_min_limit.x + Eps && new_size.y >= Size_min_limit.y + Eps)
    {
        if (parent_ != nullptr)
        {
            Vector parent_size = parent_->getLayoutBox().getSize();
            Vector new_pos = layout_box->getPosition();
            if (new_pos.x + new_size.x <= parent_size.x - Eps &&
                new_pos.y + new_size.y <= parent_size.y - Eps)
            {
                layout_box->setSize(new_size);
            }
        }
        else
            layout_box->setSize(new_size);

        prev_pos_ = new_coord;
    }
    else
        layout_box->setPosition(pos);


    size_t cnt = widgets_.getSize();
    for (size_t it = 0; it < cnt; it++)
    {
       widgets_[it]->onUpdate(*layout_box);
    }
}


void Frame::moveFrame(const Dot &new_coord)
{
    LayoutBox* layout_box = &getLayoutBox();

    Vector delta = new_coord - hold_pos_;
        
    Vector new_pos = getLayoutBox().getPosition() + delta;
    
    if (parent_ != nullptr)
    {
        Vector parent_size = parent_->getLayoutBox().getSize();
        Vector size = layout_box->getSize();
        if (new_pos.x > Eps && new_pos.x + size.x <= parent_size.x && 
            new_pos.y > Eps && new_pos.y + size.y <= parent_size.y)
        {
            layout_box->setPosition(new_pos);
        }
    }
    else    
        layout_box->setPosition(new_pos);
}


//================================================================================

bool Frame::onMousePressed(const Vector &pos, const MouseKey key, Container<Transform> &stack_transform)
{
    Transform trf(getLayoutBox().getPosition(), scale_);
    stack_transform.pushBack(trf.applyPrev(stack_transform.getBack()));

    Transform last_trf = stack_transform.getBack();    

    bool flag = false;

    size_t cnt = widgets_.getSize();
    for (size_t it = 0; it < cnt; it++)
    {
        if (!flag) flag = widgets_[it]->onMousePressed(pos, key, stack_transform);
    }

    if (!flag)
    {
        Dot new_coord = last_trf.applyTransform(pos);
        flag = checkIn(new_coord, getLayoutBox().getSize());    

        if (flag)
        {
            if (key == MouseKey::LEFT)
            {
                hold_pos_ = prev_pos_ = new_coord;
                clickOnBorder();

                if (!state_) state_ = Borders::TOP;

                flag = true;
            }
        }
    }

    stack_transform.popBack();

    return flag;
}

//================================================================================

bool Frame::onMouseReleased(const Vector &pos, const MouseKey key, Container<Transform> &stack_transform)
{
    Transform trf(getLayoutBox().getPosition(), scale_);
    stack_transform.pushBack(trf.applyPrev(stack_transform.getBack()));

    size_t cnt = widgets_.getSize();
    for (size_t it = 0; it < cnt; it++)
        widgets_[it]->onMouseReleased(pos, key, stack_transform);

    state_ = DecoratorState::DEFAULT;

    stack_transform.popBack();

    return false;
}

//================================================================================

bool Frame::onKeyboardPressed(const KeyboardKey key)
{
    size_t cnt = widgets_.getSize();
    for (size_t it = 0; it < cnt; it++)
        widgets_[it]->onKeyboardReleased(key);
}

//================================================================================

bool Frame::onKeyboardReleased(const KeyboardKey key)
{
    size_t cnt = widgets_.getSize();
    for (size_t it = 0; it < cnt; it++)
        widgets_[it]->onKeyboardReleased(key);
}

//================================================================================

bool Frame::onTick(const time_t delta_time)
{
    size_t cnt = widgets_.getSize();
    for (size_t it = 0; it < cnt; it++)
        widgets_[it]->onTick(delta_time);


    return false;
} 

//================================================================================

void Frame::onUpdate (const LayoutBox &parent_layout)
{
    LayoutBox *layout_box =  &getLayoutBox();
    layout_box->onParentUpdate(parent_layout);
    
    size_t cnt = widgets_.getSize();
    for (size_t it = 0; it < cnt; it++)
        widgets_[it]->onUpdate(*layout_box);
}

//================================================================================

void Frame::setFocus (const bool flag)
{
    focused_ = flag;

    size_t cnt = widgets_.getSize();
    for (size_t it = 0; it < cnt; it++)
        widgets_[it]->setFocus(flag);
}

//================================================================================

void Frame::addWidget(Widget* widget_ptr)
{
    widgets_.pushBack(widget_ptr);
}