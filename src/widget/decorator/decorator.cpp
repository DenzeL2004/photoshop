#include "decorator.h"

//=================================================================================================

Decorator::Decorator(const char *path_texture, const Dot left_up,  Widget *widget):
               left_up_(left_up), width_(0), hieght_(0), background_(), widget_(widget) 
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

void Decorator::SetPos(const Dot &new_left_up)
{
    left_up_ = new_left_up;
    return;
}

bool Decorator::CheckIn(const Dot &mouse_pos)
{
    bool horizontal = (left_up_.GetX() < mouse_pos.GetX() && left_up_.GetX() + width_ > mouse_pos.GetX());
    bool vertical   = (left_up_.GetY() < mouse_pos.GetY() && left_up_.GetY() + hieght_ > mouse_pos.GetY());
   
    return horizontal & vertical;
}

//=================================================================================================


//=================================================================================================