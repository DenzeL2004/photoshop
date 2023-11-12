#include "decorator.h"

const Dot Offset_Title = Dot(0.45, 0.0);
const double Tittle_size  = 10u;

const double Border_width = 10;

//=================================================================================================

Frame::Frame(   const char *path_texture,
                const Title &title,
                const Vec2d &size, const Vec2d &pos, 
                const Widget *parent, const Vec2d &parent_size, 
                const Vec2d &origin, const Vec2d &scale):
                Window(path_texture, size, pos, parent, (parent != nullptr) ? parent->getLayoutBox().getSize() : parent_size, origin, scale),  
                title_(title), widgets_(),
                state_(DEFAULT), hold_pos_({0.0, 0.0}), prev_pos_({0.0, 0.0}){}

void Frame::draw(sf::RenderTarget &target, Container<Transform> &stack_transform)
{
    Transform trf(getLayoutBox().getPosition(), scale_);

    stack_transform.pushBack(trf.combine(stack_transform.getBack()));
    Transform last_trf = stack_transform.getBack();    

    sf::VertexArray vertex_array(sf::Quads, 4);

    getDrawFormat(vertex_array, last_trf);

    target.draw(vertex_array, &texture_);

    Dot abs_pos = last_trf.restore(Dot(0.0, 0.0));

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

bool Frame::onMouseMoved(const Vec2d &pos, Container<Transform> &stack_transform)
{
    Transform trf(getLayoutBox().getPosition(), scale_);

    stack_transform.pushBack(trf.combine(stack_transform.getBack()));
    Transform last_trf = stack_transform.getBack();    

    Dot local_pos = last_trf.apply(pos);

    size_t cnt = widgets_.getSize();
    for (size_t it = 0; it < cnt; it++)
    {
        widgets_[it]->onMouseMoved(pos, stack_transform);
    }

    if(state_)
    {
        if (state_ == Borders::TOP)
            moveFrame(local_pos);
        else
            resizeFrame(local_pos);
    }  
    

    stack_transform.popBack();

    return true;
}

//================================================================================
void Frame::clickOnBorder()
{
    Vec2d size = getLayoutBox().getSize();

    state_ = 0;

    if (hold_pos_.x > Eps && hold_pos_.x < Border_width - Eps)
        state_ |= Frame::Borders::LEFT;

    if (hold_pos_.x > size.x - Border_width + Eps && hold_pos_.x < size.x - Eps)
        state_ |= Frame::Borders::RIGHT;

    if (hold_pos_.y > size.y - Border_width + Eps && hold_pos_.y < size.y - Eps)
        state_ |= Frame::Borders::BOTTOM;
}


void Frame::resizeFrame(const Dot &local_pos)
{
    LayoutBox* layout_box = &getLayoutBox();

    Vec2d size = layout_box->getSize();

    Vec2d pos = layout_box->getPosition();

    Vec2d delta = local_pos - prev_pos_;
   
    if (state_ & Frame::Borders::LEFT) 
    {
        if (size.x <= Size_min_limit.x + Eps) return;
            moveFrame(Dot(local_pos.x, hold_pos_.y));
        
        delta.x = pos.x - layout_box->getPosition().x;
    }    

    Vec2d new_size = size;

    if (state_ & Frame::Borders::LEFT || state_ & Frame::Borders::RIGHT)
        new_size += Vec2d(delta.x, 0.0);

    if (state_ & Frame::Borders::BOTTOM)
        new_size += Vec2d(0.0, delta.y);

    if (new_size.x >= Size_min_limit.x + Eps && new_size.y >= Size_min_limit.y + Eps)
    {
        if (parent_ != nullptr)
        {
            Vec2d parent_size = parent_->getLayoutBox().getSize();
            Vec2d new_pos = layout_box->getPosition();
            if (new_pos.x + new_size.x <= parent_size.x - Eps &&
                new_pos.y + new_size.y <= parent_size.y - Eps)
            {
                layout_box->setSize(new_size);
            }
        }
        else
            layout_box->setSize(new_size);

        prev_pos_ = local_pos;
    }
    else
        layout_box->setPosition(pos);


    size_t cnt = widgets_.getSize();
    for (size_t it = 0; it < cnt; it++)
    {
       widgets_[it]->onUpdate(*layout_box);
    }
}


void Frame::moveFrame(const Dot &local_pos)
{
    LayoutBox* layout_box = &getLayoutBox();

    Vec2d delta = local_pos - hold_pos_;
        
    Vec2d new_pos = getLayoutBox().getPosition() + delta;
    
    if (parent_ != nullptr)
    {
        Vec2d parent_size = parent_->getLayoutBox().getSize();
        Vec2d size = layout_box->getSize();

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

bool Frame::onMousePressed(const Vec2d &pos, const MouseKey key, Container<Transform> &stack_transform)
{
    Transform trf(getLayoutBox().getPosition(), scale_);
    stack_transform.pushBack(trf.combine(stack_transform.getBack()));

    bool flag = false;

    size_t cnt = widgets_.getSize();
    for (size_t it = 0; it < cnt; it++)
    {
        if (!flag) flag = widgets_[it]->onMousePressed(pos, key, stack_transform);
    }

    if (!flag)
    {
        Transform last_trf = stack_transform.getBack(); 

        Dot local_pos = last_trf.apply(pos);
        flag = checkIn(local_pos); 

        if (flag)
        {
            if (key == MouseKey::LEFT)
            {
                hold_pos_ = prev_pos_ = local_pos;
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

bool Frame::onMouseReleased(const Vec2d &pos, const MouseKey key, Container<Transform> &stack_transform)
{
    Transform trf(getLayoutBox().getPosition(), scale_);
    stack_transform.pushBack(trf.combine(stack_transform.getBack()));

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
        widgets_[it]->onKeyboardPressed(key);

    return false;
}

//================================================================================

bool Frame::onKeyboardReleased(const KeyboardKey key)
{
    size_t cnt = widgets_.getSize();
    for (size_t it = 0; it < cnt; it++)
        widgets_[it]->onKeyboardReleased(key);

    return false;
}

//================================================================================

bool Frame::onTick(const float delta_time)
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