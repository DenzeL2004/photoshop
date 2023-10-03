#include "window.h"

Window::Window(const char *path_texture, const Dot left_up,
               const double scale_x, const double scale_y):
               left_up_(left_up), scale_x_(scale_x), scale_y_(scale_y),
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

void Window::SetPos(const Dot &new_left_up)
{
    left_up_ = new_left_up;
    return;
}

void Window::Draw(sf::RenderTarget &target, StackTransform &stack_transform) const
{
    stack_transform.AddTransform(Transform(left_up_, scale_x_, scale_y_));

    Transform tmp = stack_transform.GetTransformation();

    sf::Sprite sprite;
    sprite.setTexture(background_);


    sprite.setPosition((float)tmp.pos_.GetX(), (float)tmp.pos_.GetY());
    sprite.setScale((float)(tmp.scale_x_), (float)(tmp.scale_y_));

    target.draw(sprite);

    stack_transform.EraseTransform();

    return;
}


bool Window::CheckIn(const Dot &mouse_pos)
{
    bool horizontal = (left_up_.GetX() < mouse_pos.GetX() && left_up_.GetX() + width_ > mouse_pos.GetX());
    bool vertical   = (left_up_.GetY() < mouse_pos.GetY() && left_up_.GetY() + hieght_ > mouse_pos.GetY());
   
    return horizontal & vertical;
}

bool Window::OnMouseMoved(const int x, const int y, StackTransform &stack_transform)
{
    Vector mouse_pos((double)x, (double)y);

    return CheckIn(mouse_pos);
}

bool Window::OnMousePressed(const MouseKey key, StackTransform &stack_transform)
{
    printf("Window: mouse pressed\n");
    return false;
}


bool Window::OnMouseReleased(const MouseKey key, StackTransform &stack_transform)
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