#include "window.h"

Window::Window (const char *path_texture,
                const Dot offset, const Vector scale):
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

void Window::Move(const Dot &offset)
{
    transform_.offset += offset;
    return;
}

//================================================================================

void Window::Draw(sf::RenderTarget &target, Container<Transform> &stack_transform) const
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

bool Window::CheckIn(const Dot &mouse_pos)
{
    bool horizontal = (Eps < mouse_pos.x && 1 - Eps >= mouse_pos.x);
    bool vertical   = (Eps < mouse_pos.y && 1 - Eps >= mouse_pos.y);
   
    return horizontal & vertical;
}

//================================================================================

bool Window::OnMouseMoved(const int x, const int y, Container<Transform> &stack_transform)
{
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    Transform last_trf = stack_transform.GetBack();
    
    Dot new_coord = last_trf.ApplyTransform({(double)x, (double)y});

    bool flag = CheckIn(new_coord);

    stack_transform.PopBack();

    return flag;
}

//================================================================================

bool Window::OnMousePressed(const int x, const int y, const MouseKey key, Container<Transform> &stack_transform)
{
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    Transform last_trf = stack_transform.GetBack();
    
    Dot new_coord = last_trf.ApplyTransform({(double)x, (double)y});

    bool flag = CheckIn(new_coord);

    stack_transform.PopBack();

    return flag;
}

//================================================================================

bool Window::OnMouseReleased(const int x, const int y, const MouseKey key, Container<Transform> &stack_transform)
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