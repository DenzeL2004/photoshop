#include "tools.h"

Dot Tool::ShiftDot (const Dot &pos, Canvas &canvas)
{
    Dot real_pos = canvas.GetRealPos();
    Dot canvas_size = canvas.GetSize();

    Dot canvas_dot = pos + real_pos;
        canvas_dot.y = canvas_size.y - canvas_dot.y;

    return canvas_dot;
}

ToolPalette::ToolPalette():
        tools_(),
        active_tool_(ToolType::NOTHING), 
        color_type_(FOREGROUND), foreground_color_(sf::Color::Transparent), background_color_(sf::Color::Transparent)
{
    tools_.PushBack(new LineTool(&foreground_color_));
    tools_.PushBack(new BrushTool(&foreground_color_));
    tools_.PushBack(new SquareTool(&foreground_color_));
    tools_.PushBack(new CircleTool(&foreground_color_));
    tools_.PushBack(new PolyLineTool(&foreground_color_));
    tools_.PushBack(new BrushTool(&sf::Color::White));
}


//================================================================================

ToolPalette::~ToolPalette()
{
    size_t size = tools_.GetSize();
    for (size_t it = 0; it < size; it++)
        delete tools_[it];
}   

Tool* ToolPalette::GetActiveTool () const
{
    switch (active_tool_)
    {
        case ToolPalette::ToolType::LINE:
            return tools_[ToolPalette::ToolType::LINE];
            break;

        case ToolPalette::ToolType::BRUSH:
            return tools_[ToolPalette::ToolType::BRUSH];
            break;

        case ToolPalette::ToolType::SQUARE:
            return tools_[ToolPalette::ToolType::SQUARE];
            break;

        case ToolPalette::ToolType::CIRCLE:
            return tools_[ToolPalette::ToolType::CIRCLE];
            break;

        case ToolPalette::ToolType::POLYLINE:
            return tools_[ToolPalette::ToolType::POLYLINE];
            break;

        case ToolPalette::ToolType::ERASER:
            return tools_[ToolPalette::ToolType::ERASER];
            break;

        default:
            return nullptr;
            break;
    }
}

void ToolPalette::SetActiveColor (const sf::Color &color) 
{
    if (color_type_ == ToolPalette::ColorType::FOREGROUND)
        foreground_color_ = color;

    if (color_type_ == ToolPalette::ColorType::BACKGROUND)
        background_color_ = color;
}

//================================================================================

void ToolPalette::SetActiveTool(const ToolType tool_type)
{
    active_tool_ = tool_type;
}

//================================================================================

//LINE  

class LineWidget : public Widget
{
    public:
        LineWidget(const Dot *start_pos, const Dot *end_pos, const sf::Color *cur_color):
                    start_pos_(*start_pos), end_pos_(*end_pos), cur_color_(*cur_color){}

        ~LineWidget(){}

        virtual bool OnMousePressed     (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform) {return true;};
        virtual bool OnMouseMoved       (const double x, const double y, Container<Transform> &stack_transform) {return true;}
        virtual bool OnMouseReleased    (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform){return true;}

        bool OnKeyboardPressed  (const KeyboardKey){return true;}
        bool OnKeyboardReleased (const KeyboardKey){return true;}

        void PassTime           (const time_t delta_time){}

        void Draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform)
        {
            
            Transform last_trf = stack_transform.GetBack();
            DrawLine(targert, start_pos_ + last_trf.offset, end_pos_ + last_trf.offset, cur_color_);
        }
    
        sf::Color GetColor() const {return cur_color_;}

    private:
       const Dot &start_pos_;
       const Dot &end_pos_;
       const sf::Color &cur_color_;
};

LineTool::LineTool(const sf::Color *cur_color):
                  using_(false), start_pos_(), end_pos_(), 
                  preview_(new LineWidget(&start_pos_, &end_pos_, cur_color)), cur_color_(*cur_color){}


//================================================================================
void LineTool::OnMainButton(ButtonState key, const Dot &pos, Canvas &canvas)
{
    if (key != ButtonState::PRESSED)
        return;

    if (using_)
        return;

    start_pos_ = end_pos_ = pos;

    using_ = true;
}

void LineTool::OnMove(const Dot &pos, Canvas &canvas)
{
    if (!using_)
        return;
    
    end_pos_ = pos; 
}

void LineTool::OnConfirm (const Dot &pos, Canvas &canvas)
{
    if (!using_)
        return;

    Dot begin   = ShiftDot(start_pos_, canvas);
    Dot end     = ShiftDot(end_pos_, canvas);

    DrawLine(canvas.background_, begin, end, cur_color_);
    start_pos_  = end_pos_ = {0, 0};

    using_ = false;
}

Widget* LineTool::GetWidget() const
{
    return preview_;
}

//================================================================================

//SQUARE
class SquareWidget : public Widget
{
    public:
        SquareWidget(const Dot *start_pos, const Dot *end_pos, const sf::Color *cur_color):
                    start_pos_(*start_pos), end_pos_(*end_pos), cur_color_(*cur_color){}

        ~SquareWidget(){}

        virtual bool OnMousePressed     (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform) {return true;};
        virtual bool OnMouseMoved       (const double x, const double y, Container<Transform> &stack_transform) {return true;}
        virtual bool OnMouseReleased    (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform){return true;}

        bool OnKeyboardPressed  (const KeyboardKey){return true;}
        bool OnKeyboardReleased (const KeyboardKey){return true;}

        void PassTime           (const time_t delta_time){}

        void Draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform)
        {
            Transform last_trf = stack_transform.GetBack();
            DrawRectangle(targert, start_pos_ + last_trf.offset, end_pos_ + last_trf.offset, cur_color_);     
        }
    
        sf::Color GetColor() const {return cur_color_;}

    private:
       const Dot &start_pos_;
       const Dot &end_pos_;
       const sf::Color &cur_color_;
};

//================================================================================

SquareTool::SquareTool(const sf::Color *cur_color):
                  using_(false), start_pos_(), end_pos_(), 
                  preview_(new SquareWidget(&start_pos_, &end_pos_, cur_color)), cur_color_(*cur_color){}

void SquareTool::OnMainButton(ButtonState key, const Dot &pos, Canvas &canvas)
{
    if (key != ButtonState::PRESSED)
        return;

    if (using_)
        return;

    start_pos_ = end_pos_ = pos;

    using_ = true;
}

void SquareTool::OnMove(const Dot &pos, Canvas &canvas)
{
    if (!using_)
        return;
    
    end_pos_ = pos; 
}

void SquareTool::OnConfirm (const Dot &pos, Canvas &canvas)
{
    if (!using_)
        return;

    Dot left_up     = ShiftDot(start_pos_, canvas);
    Dot right_down  = ShiftDot(end_pos_, canvas);

    DrawRectangle(canvas.background_, left_up, right_down, cur_color_);
    start_pos_  = end_pos_ = {0, 0};

    using_ = false;
}

Widget* SquareTool::GetWidget() const
{
    return preview_;
}

//================================================================================

//Circle

class CircleWidget : public Widget
{
    public:
        CircleWidget(const Dot *start_pos, const Dot *end_pos, const sf::Color *cur_color):
                    start_pos_(*start_pos), end_pos_(*end_pos), cur_color_(*cur_color){}

        ~CircleWidget(){}

        virtual bool OnMousePressed     (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform) {return true;};
        virtual bool OnMouseMoved       (const double x, const double y, Container<Transform> &stack_transform) {return true;}
        virtual bool OnMouseReleased    (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform){return true;}

        bool OnKeyboardPressed  (const KeyboardKey){return true;}
        bool OnKeyboardReleased (const KeyboardKey){return true;}

        void PassTime           (const time_t delta_time){}

        void Draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform)
        {
            
            Transform last_trf = stack_transform.GetBack();

            Dot center = start_pos_ + last_trf.offset;
            Dot other  = end_pos_ + last_trf.offset;

            double rad = (center - other).Len();

            DrawCircle(targert, center, (float)rad, cur_color_);
        }
    
        sf::Color GetColor() const {return cur_color_;}

    private:
       const Dot &start_pos_;
       const Dot &end_pos_;
       const sf::Color &cur_color_;
};

//================================================================================

CircleTool::CircleTool(const sf::Color *cur_color):
                  using_(false), start_pos_(), end_pos_(), 
                  preview_(new CircleWidget(&start_pos_, &end_pos_, cur_color)), cur_color_(*cur_color){}

void CircleTool::OnMainButton(ButtonState key, const Dot &pos, Canvas &canvas)
{
    if (key != ButtonState::PRESSED)
        return;

    if (using_)
        return;

    start_pos_ = end_pos_ = pos;

    using_ = true;
}

void CircleTool::OnMove(const Dot &pos, Canvas &canvas)
{
    if (!using_)
        return;
    
    end_pos_ = pos; 
}

void CircleTool::OnConfirm (const Dot &pos, Canvas &canvas)
{
    if (!using_)
        return;

    Dot center = ShiftDot(start_pos_, canvas);
    Dot other  = ShiftDot(end_pos_, canvas);

    double rad = (center - other).Len();

    DrawCircle(canvas.background_, center, (float)rad, cur_color_);
    start_pos_  = end_pos_ = {0, 0};

    using_ = false;
}

Widget* CircleTool::GetWidget() const
{
    return preview_;
}

//================================================================================
//Brushh

BrushTool::BrushTool(const sf::Color *cur_color):
                    using_(false), cur_color_(*cur_color){}


void BrushTool::OnMainButton(ButtonState key, const Dot &pos, Canvas &canvas)
{
    if (key != ButtonState::PRESSED)
        return;

    if (using_)
        return;

    using_ = true;

    DrawForm(pos, canvas);
}

void BrushTool::OnMove(const Dot &pos, Canvas &canvas)
{
    if (!using_)
        return;

    DrawForm(pos, canvas);
}

void BrushTool::OnConfirm (const Dot &pos, Canvas &canvas)
{
    if (!using_)
        return;

    using_ = false;
}

Widget* BrushTool::GetWidget() const
{
    return nullptr;
}


void BrushTool::DrawForm (const Dot &pos, Canvas &canvas)
{
    Dot canvas_dot  =  ShiftDot(pos, canvas);
    DrawCircle(canvas.background_, canvas_dot, 10, cur_color_);
}

//================================================================================
// //Eraeser

// EreaserTool::EreaserTool(const sf::Color *cur_color):
//                 using_(false), cur_color_(*cur_color){}


// void EreaserTool::OnMainButton(ButtonState key, const Dot &pos, Canvas &canvas)
// {
//     if (key != ButtonState::PRESSED)
//         return;

//     if (using_)
//         return;

//     using_ = true;

//     DrawForm(pos, canvas);
// }

// void EreaserTool::OnMove(const Dot &pos, Canvas &canvas)
// {
//     if (!using_)
//         return;

//     DrawForm(pos, canvas);
// }

// void EreaserTool::OnConfirm (const Dot &pos, Canvas &canvas)
// {
//     if (!using_)
//         return;

//     using_ = false;
// }

// Widget* EreaserTool::GetWidget() const
// {
//     return nullptr;
// }


// void EreaserTool::DrawForm (const Dot &pos, Canvas &canvas)
// {
//     Dot canvas_dot  =  ShiftDot(pos, canvas);
//     DrawCircle(canvas.background_, canvas_dot, 10, cur_color_);
// }


//================================================================================
//Fill

FillTool::FillTool(const sf::Color *cur_color):
                    using_(false), cur_color_(*cur_color){}


void FillTool::OnMainButton(ButtonState key, const Dot &pos, Canvas &canvas)
{
    if (key != ButtonState::PRESSED)
        return;

    if (using_)
        return;

    using_ = true;
    sf::Image image = canvas.background_.getTexture().copyToImage();

    Dot new_pos = ShiftDot(pos, canvas);
    sf::Color fill_color = image.getPixel(size_t(new_pos.x), size_t(new_pos.y));

    Fill(fill_color, new_pos, canvas, image);

    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite(texture);
    sprite.scale(-1.f, 1.f);

    canvas.background_.draw(sprite);

    OnConfirm(pos, canvas);
}


void FillTool::OnConfirm (const Dot &pos, Canvas &canvas)
{
    if (!using_)
        return;

    using_ = false;
}

Widget* FillTool::GetWidget() const
{
    return nullptr;
}

void FillTool::Fill(sf::Color &fill_color, const Dot &start_pos, Canvas &canvas, sf::Image &image)
{
    Container<sf::Vector2u> dots_;

    const size_t x_limit = canvas.GetSize().x;
    const size_t y_limit = canvas.GetSize().y;

    dots_.PushBack(sf::Vector2u((size_t)start_pos.x, (size_t)start_pos.y));

    while (!dots_.IsEmpty())
    {
        sf::Vector2u cur_dot = dots_.GetBack();
        dots_.PopBack();

        if (cur_dot.x > 0 && image.getPixel(cur_dot.x - 1, start_pos.y) == fill_color) 
        {
            image.setPixel(cur_dot.x - 1, cur_dot.y, cur_color_);
            dots_.PushBack(sf::Vector2u(cur_dot.x - 1, cur_dot.y)); 
        }

        if (cur_dot.y > 0 && image.getPixel(cur_dot.x, start_pos.y - 1) == fill_color) 
        {
            image.setPixel(cur_dot.x, cur_dot.y - 1, cur_color_);
            dots_.PushBack(sf::Vector2u(cur_dot.x, cur_dot.y - 1));
        }

        if (cur_dot.x < x_limit && image.getPixel(cur_dot.x + 1, start_pos.y) == fill_color) 
        {
            image.setPixel(cur_dot.x + 1, cur_dot.y, cur_color_);
            dots_.PushBack(sf::Vector2u(cur_dot.x + 1, cur_dot.y));  
        }

        if (cur_dot.y + 1 < y_limit && image.getPixel(cur_dot.x, start_pos.y + 1) == fill_color) 
        {
            image.setPixel(cur_dot.x, cur_dot.y + 1, cur_color_);
            dots_.PushBack(sf::Vector2u(cur_dot.x, cur_dot.y + 1)); 
        }
    }
    
}


//================================================================================

class PolyLineWidget : public Widget
{
    public:
        PolyLineWidget(const Dot *end_pos, const sf::Color *cur_color):
                        end_pos_(*end_pos), cur_color_(*cur_color){}

        ~PolyLineWidget(){}

        virtual bool OnMousePressed     (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform) {return true;};
        virtual bool OnMouseMoved       (const double x, const double y, Container<Transform> &stack_transform) {return true;}
        virtual bool OnMouseReleased    (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform){return true;}

        bool OnKeyboardPressed  (const KeyboardKey){return true;}
        bool OnKeyboardReleased (const KeyboardKey){return true;}

        void PassTime           (const time_t delta_time){}

        void Draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform)
        {
            Transform last_trf = stack_transform.GetBack();
            size_t size = arr_.getVertexCount();

            if (size == 0)
                return;

            Dot cur(0.0, 0.0); 
            Dot next = Dot(arr_[size - 1].position.x, arr_[size - 1].position.y);

            for (size_t it = 0; it < size - 1; it++)
            {
                cur  = Dot(arr_[it].position.x, arr_[it].position.y);
                next = Dot(arr_[it + 1].position.x, arr_[it + 1].position.y);
                DrawLine(targert, cur + last_trf.offset, next + last_trf.offset, cur_color_);
            }

            DrawLine(targert, next + last_trf.offset,  end_pos_ + last_trf.offset, cur_color_);

        }
    
        sf::Color GetColor() const {return cur_color_;}

        sf::VertexArray arr_;
    private:
        const Dot &end_pos_;
       
        const sf::Color &cur_color_;
};


PolyLineTool::PolyLineTool(const sf::Color *cur_color):
                  using_(false), start_pos_(), end_pos_(), 
                  preview_(new PolyLineWidget(&end_pos_, cur_color)), cur_color_(*cur_color){}

void PolyLineTool::OnMainButton(ButtonState key, const Dot &pos, Canvas &canvas)
{
    if (key != ButtonState::PRESSED)
        return;


    start_pos_ = end_pos_ = pos;
    preview_->arr_.append(sf::Vector2f(start_pos_.x, start_pos_.y));

    using_ = true;
}

void PolyLineTool::OnMove(const Dot &pos, Canvas &canvas)
{
    end_pos_ = pos; 
}

void PolyLineTool::OnConfirm (const Dot &pos, Canvas &canvas)
{
    if (using_) 
    {
        using_ = false;
        return;
    }

    size_t size = preview_->arr_.getVertexCount();
    
    if (size == 0)
    {
        using_ = false;
        return;
    }
 
    
    Dot cur(0.0, 0.0); Dot next = Dot(preview_->arr_[size - 1].position.x, preview_->arr_[size - 1].position.y);

    for (size_t it = 0; it < size - 1; it++)
    {
        cur  = Dot(preview_->arr_[it].position.x, preview_->arr_[it].position.y);
        next = Dot(preview_->arr_[it + 1].position.x, preview_->arr_[it + 1].position.y);
        DrawLine(canvas.background_, ShiftDot(cur, canvas),  ShiftDot(next, canvas), cur_color_);
    }

    start_pos_ = end_pos_ = Dot(0, 0);
    preview_->arr_.clear();
}

Widget* PolyLineTool::GetWidget() const
{
    return preview_;
}

//================================================================================