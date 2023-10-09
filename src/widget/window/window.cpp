#include "window.h"

Window::Window (const char *path_texture, const Dot offset, 
                const double scale_x, const double scale_y):
               transform_(),
               width_(0), hieght_(0), background_() 
{

    if (!background_.loadFromFile(path_texture))   
    {
        PROCESS_ERROR(LOAD_TEXTURE_ERR, "failed load tetxure from %s\n", path_texture);
        return;
    }

    width_  = background_.getSize().x;
    hieght_ = background_.getSize().y;

    transform_.offset_ = offset;

    transform_.scale_ = Vector(scale_x / width_,
                               scale_y / hieght_);

    return;
}

void Window::SetOffset(const Dot &offset)
{
    transform_.offset_ = offset;
    return;
}

void Window::Draw(sf::RenderTarget &target, Container<Transform> &stack_transform) const
{
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    Transform res_transform = stack_transform.GetBack();
    
    sf::Sprite sprite;
    sprite.setTexture(background_);

    sprite.setPosition((float)res_transform.offset_.GetX(), (float)res_transform.offset_.GetY());
    sprite.setScale   ((float)res_transform.scale_.GetX(),  (float)res_transform.scale_.GetY());

    target.draw(sprite);

    stack_transform.PopBack();

    return;
}


bool Window::CheckIn(const Dot &mouse_pos)
{
    bool horizontal = (0 <= mouse_pos.GetX() && width_  >= mouse_pos.GetX());
    bool vertical   = (0 <= mouse_pos.GetY() && hieght_ >= mouse_pos.GetY());
   
    return horizontal & vertical;
}

bool Window::OnMouseMoved(const int x, const int y, Container<Transform> &stack_transform)
{
    Dot mouse_coord((double)x, double(y));
   
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    Transform res_transform = stack_transform.GetBack();
    
    Dot new_coord = res_transform.ApplyTransform(mouse_coord);

    bool flag = CheckIn(new_coord);

    stack_transform.PopBack();

    return flag;
}

bool Window::OnMousePressed(const MouseKey key, Container<Transform> &stack_transform)
{
    printf("Window: mouse pressed\n");
    return false;
}


bool Window::OnMouseReleased(const MouseKey key, Container<Transform> &stack_transform)
{
    printf("Window: mouse released\n");
    return false;
}

bool Window::OnKeyboardPressed(const KeyboardKey key)
{
    printf("Window: mouse keyboard kye pressed\n");
    return false;
}


bool Window::OnKeyboardReleased(const KeyboardKey key)
{
    printf("Window: mouse keyboard kye released\n");
    return false;
}

void Window::PassTime(const time_t delta_time)
{
    printf("Window: mouse keyboard kye released\n");
    return;
}

//=======================================================================================
// //CONTAINER WINDOW

// void ContainerWindow::Draw(sf::RenderTarget &target) const
// {
//     this->Draw(target);
//     window_manager_.Draw(target);

//     return;
// }


// bool ContainerWindow::OnMouseMoved(const int x, const int y)
// {
//     if (this->OnMouseMoved(x, y))
//     {
//         return window_manager_.OnMouseMoved(x, y);
//     }

//     return false;
// }

// bool ContainerWindow::OnMousePressed(const MouseKey key)
// {
//     printf("ContainerWindow: mouse pressed\n");
//     return false;
// }


// bool ContainerWindow::OnMouseReleased(const MouseKey key)
// {
//     printf("ContainerWindow: mouse released\n");
//     return false;
// }

// bool ContainerWindow::OnKeyboardPressed(const KeyboardKey key)
// {
//     printf("ContainerWindow: mouse keyboard kye pressed\n");
//     return false;
// }


// bool ContainerWindow::OnKeyboardReleased(const KeyboardKey key)
// {
//     printf("ContainerWindow: mouse keyboard kye released\n");
//     return false;
// }