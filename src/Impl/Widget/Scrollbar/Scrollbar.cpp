#include "Scrollbar.h"

// void Scrollbar::draw(sf::RenderTarget &target, Container<Transform> &stack_transform)
// {
//     Transform trf(getLayoutBox().getPosition(), scale_);

//     stack_transform.pushBack(trf.combine(stack_transform.getBack()));
//     Transform last_trf = stack_transform.getBack();    

//     Vec2d size = last_trf.getScale() * getLayoutBox().getSize();
    
//     canvas_->correctCanvasRealPos(size);
    
//     top_button_->draw(target, stack_transform);
//     bottom_button_->draw(target, stack_transform);
//     center_button_->draw(target, stack_transform);

//     stack_transform.popBack();

//     return;
// }

// bool Scrollbar::onMouseMoved(const Vec2d& pos, Container<Transform> &stack_transform)
// {
//     Transform trf(getLayoutBox().getPosition(), scale_);

//     stack_transform.pushBack(trf.combine(stack_transform.getBack()));
//     Transform last_trf = stack_transform.getBack();    

//     top_button_->onMouseMoved(pos, stack_transform);
//     bottom_button_->onMouseMoved(pos, stack_transform);
//     center_button_->onMouseMoved(pos, stack_transform);

//     Dot local_pos = last_trf.restore(pos);
    
//     if (center_button_->prev_state_ == Button::ButtonState::PRESSED || 
//         center_button_->state_ == Button::ButtonState::PRESSED)
//     {
//         Dot real_pos = canvas_->getRealPos();
//         Dot center_button_pos = center_button_->getLayoutBox().getPosition();
        
//         Vec2d scrollbar_size = getLayoutBox().getSize() - top_button_->getLayoutBox().getSize() - bottom_button_->getLayoutBox().getSize();

//         if (type_ == Scrollbar::Type::HORIZONTAL)
//         {
//             canvas_->setRealPos(Dot(prev_canvas_real_pos_.x + (local_pos.x - hold_pos_.x) / scrollbar_size.x * canvas_->getCanvasSize().x, real_pos.y));
//             center_button_->getLayoutBox().setPosition(Dot(local_pos.x - hold_pos_.x, center_button_pos.y));
//         }

//         if (type_ == Scrollbar::Type::VERTICAL)
//         {
//             canvas_->setRealPos(Dot(real_pos.x, prev_canvas_real_pos_.y + (local_pos.y - hold_pos_.y) / scrollbar_size.y * canvas_->getCanvasSize().y));
//             center_button_->getLayoutBox().setPosition(Dot(center_button_pos.x, local_pos.y - hold_pos_.y));
//         }

//         Vec2d size = last_trf.getScale() * getLayoutBox().getSize();

//         canvas_->correctCanvasRealPos(size);
//         moveCenter();
//     }
    
//     stack_transform.popBack();

//     return true;
// }

// void Scrollbar::moveCenter()
// {
//     Vec2d canvas_size = canvas_->getCanvasSize();
//     Vec2d canvas_pos = canvas_->getRealPos();

//     double cf_x = canvas_pos.x / canvas_size.x;
//     double cf_y = canvas_pos.y / canvas_size.y;
    
//     Vec2d center_button_pos = center_button_->getLayoutBox().getPosition();

//     Vec2d scrollbar_size = getLayoutBox().getSize() - top_button_->getLayoutBox().getSize() - bottom_button_->getLayoutBox().getSize();

//     if (type_ == Scrollbar::Type::HORIZONTAL)
//         center_button_pos = Vec2d(cf_x * scrollbar_size.x + top_button_->getLayoutBox().getSize().x, center_button_pos.y); 

//     if (type_ == Scrollbar::Type::VERTICAL)
//         center_button_pos = Vec2d(center_button_pos.x, cf_y * scrollbar_size.y + top_button_->getLayoutBox().getSize().y); 
    
//     center_button_->getLayoutBox().setPosition(center_button_pos);
// }

// void Scrollbar::resizeCenter()
// {
//     Vec2d canvas_size = canvas_->getCanvasSize();
    
//     double cf_x = std::min(1.0, getLayoutBox().getSize().x / canvas_size.x);
//     double cf_y = std::min(1.0, getLayoutBox().getSize().y / canvas_size.y);
    
//     Vec2d center_button_size = center_button_->getLayoutBox().getSize();

//     Vec2d scrollbar_size = getLayoutBox().getSize() - top_button_->getLayoutBox().getSize() - bottom_button_->getLayoutBox().getSize();

//     if (type_ == Scrollbar::Type::HORIZONTAL)
//         center_button_size = Vec2d(cf_x * scrollbar_size.x, center_button_size.y); 

//     if (type_ == Scrollbar::Type::VERTICAL)
//         center_button_size = Vec2d(center_button_size.x, cf_y * scrollbar_size.y); 
    
//     center_button_->getLayoutBox().setSize(center_button_size);
// }

// bool Scrollbar::onMousePressed(const Vec2d& pos, const MouseKey key, Container<Transform> &stack_transform)
// {
//     LayoutBox *layout_box =  &getLayoutBox();

//     Transform trf(layout_box->getPosition(), scale_);

//     stack_transform.pushBack(trf.combine(stack_transform.getBack()));
//     Transform last_trf = stack_transform.getBack();    

//     Dot local_pos = last_trf.restore(pos);
 
//     prev_canvas_real_pos_ = canvas_->getRealPos();

//     bool flag = checkIn(local_pos);

//     if (flag)
//     {
//         flag = false;
//         flag |= center_button_->onMousePressed(pos, key, stack_transform);
//         flag |= top_button_->onMousePressed(pos, key, stack_transform);
//         flag |= bottom_button_->onMousePressed(pos, key, stack_transform);

//         if (flag)
//             hold_pos_ = local_pos;

//         if (!flag)
//         {
//             Dot offset = local_pos - center_button_->getLayoutBox().getPosition();

//             if (type_ == Scrollbar::Type::HORIZONTAL)
//                 offset.y = 0.0;
//             if (type_ == Scrollbar::Type::VERTICAL)
//                 offset.x = 0.0;

//             if (offset.x < -Eps || offset.y < -Eps)
//                 (*top_button_->action_)();
            
//             if (offset.x > Eps || offset.y > Eps)
//                 (*bottom_button_->action_)();

//             flag = true;
//         }

//         Vec2d size = last_trf.getScale() * getLayoutBox().getSize();
//         canvas_->correctCanvasRealPos(size);
//     }
    
//     moveCenter();

//     stack_transform.popBack();

//     return flag;
// }

// bool Scrollbar::onMouseReleased(const Vec2d& pos, const MouseKey key, Container<Transform> &stack_transform)
// {
//     Transform trf(getLayoutBox().getPosition(), scale_);
//     stack_transform.pushBack(trf.combine(stack_transform.getBack()));

//     hold_pos_ = Dot(0.0, 0.0);

//     top_button_->onMouseReleased(pos, key, stack_transform);
//     bottom_button_->onMouseReleased(pos, key, stack_transform);
//     center_button_->onMouseReleased(pos, key, stack_transform);

//     stack_transform.popBack();

//     return true;
// }

// void Scrollbar::onUpdate (const LayoutBox &parent_layout)
// {
//     LayoutBox *layout_box = &getLayoutBox();
//     Vec2d size = layout_box->getSize();

//     layout_box->onParentUpdate(parent_layout);

//     if (type_ == Scrollbar::Type::VERTICAL)
//         layout_box->setSize(Vec2d(size.x, layout_box->getSize().y));

//     if (type_ == Scrollbar::Type::HORIZONTAL)
//         layout_box->setSize(Vec2d(layout_box->getSize().x, size.y));
    
//     bottom_button_->onUpdate(*layout_box);
//     center_button_->onUpdate(*layout_box);
//     top_button_->onUpdate(*layout_box);

//     moveCenter();
//     resizeCenter();
// }