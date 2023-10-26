#include "tools.h"

ToolPalette::ToolPalette():
        tools_(),
        active_tool_(ToolType::NOTHING), 
        color_type_(FOREGROUND), foreground_color_(sf::Color::White), background_color_(sf::Color::Transparent)
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
            

        case ToolPalette::ToolType::BRUSH:
            return tools_[ToolPalette::ToolType::BRUSH];
            

        case ToolPalette::ToolType::SQUARE:
            return tools_[ToolPalette::ToolType::SQUARE];
            

        case ToolPalette::ToolType::CIRCLE:
            return tools_[ToolPalette::ToolType::CIRCLE];
            

        case ToolPalette::ToolType::POLYLINE:
            return tools_[ToolPalette::ToolType::POLYLINE];


        case ToolPalette::ToolType::ERASER:
            return tools_[ToolPalette::ToolType::ERASER];

        case ToolPalette::ToolType::FILL:
            return tools_[ToolPalette::ToolType::FILL];

        default:
            return nullptr;
    }
}

void ToolPalette::SetActiveColor (const sf::Color &color) 
{
    if (color_type_ == ToolPalette::ColorType::FOREGROUND)
        foreground_color_ = color;

    if (color_type_ == ToolPalette::ColorType::BACKGROUND)
        background_color_ = color;
}

sf::Color ToolPalette::GetActiveColor () const
{
    if (color_type_ == ToolPalette::ColorType::FOREGROUND)
        return foreground_color_;

    if (color_type_ == ToolPalette::ColorType::BACKGROUND)
        return background_color_;
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
void LineTool::OnMainButton(ControlState state, const Dot &pos, Canvas &canvas)
{
    
    if (state.state != ControlState::ButtonState::PRESSED)
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

void LineTool::OnConfirm (Canvas &canvas)
{
    if (!using_)
        return;

    Dot real_pos = canvas.GetRealPos();
    DrawLine(canvas.background_, start_pos_ + real_pos, end_pos_ + real_pos, cur_color_);
    start_pos_  = end_pos_ = {0, 0};

    using_ = false;
}

void LineTool::OnCancel ()
{
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

void SquareTool::OnMainButton(ControlState state, const Dot &pos, Canvas &canvas)
{
    if (state.state != ControlState::ButtonState::PRESSED)
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

void SquareTool::OnConfirm (Canvas &canvas)
{
    if (!using_)
        return;
    
    Dot real_pos = canvas.GetRealPos();
    DrawRectangle(canvas.background_, start_pos_ + real_pos, end_pos_ + real_pos, cur_color_);
    
    start_pos_  = end_pos_ = {0, 0};

    using_ = false;
}

void SquareTool::OnCancel ()
{
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

void CircleTool::OnMainButton(ControlState state, const Dot &pos, Canvas &canvas)
{
    if (state.state != ControlState::ButtonState::PRESSED)
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

void CircleTool::OnConfirm (Canvas &canvas)
{
    if (!using_)
        return;

    double rad = (start_pos_ - end_pos_).Len();

    Dot real_pos = canvas.GetRealPos();
    DrawCircle(canvas.background_, start_pos_ + real_pos, (float)rad, cur_color_);
    start_pos_  = end_pos_ = {0, 0};

    using_ = false;
}

void CircleTool::OnCancel ()
{
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


void BrushTool::OnMainButton(ControlState state, const Dot &pos, Canvas &canvas)
{
     printf("%d\n", state.state);
    if (state.state != ControlState::ButtonState::PRESSED)
        return;

    if (using_)
        return;

    using_ = true;

    DrawForm(pos + canvas.GetRealPos(), canvas);
}

void BrushTool::OnMove(const Dot &pos, Canvas &canvas)
{
    if (!using_)
        return;

    DrawForm(pos + canvas.GetRealPos(), canvas);
}

void BrushTool::OnConfirm (Canvas &canvas)
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
    DrawCircle(canvas.background_, pos, 10, cur_color_);
}

//================================================================================
//Fill

FillTool::FillTool(const sf::Color *cur_color):
                    using_(false), cur_color_(*cur_color){}


void FillTool::OnMainButton(ControlState state, const Dot &pos, Canvas &canvas)
{
    if (state.state != ControlState::ButtonState::PRESSED)
        return;

    if (using_)
        return;

    using_ = true;
    sf::Image image = canvas.background_.getTexture().copyToImage();
    
    sf::Color fill_color = image.getPixel(size_t(pos.x), canvas.GetSize().y - size_t(pos.y));
   
    for (size_t it = 10; it < 200; it++)
    {
        image.setPixel(130, 2000 - it, sf::Color::Cyan);
        image.setPixel(131, 2000 - it, sf::Color::Cyan);
        image.setPixel(132, 2000 - it, sf::Color::Cyan);
        image.setPixel(133, 2000 - it, sf::Color::Cyan);
    }
    
    Fill(fill_color, {size_t(pos.x), canvas.GetSize().y - size_t(pos.y)}, canvas, &image);

    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite(texture);
    sprite.scale(1.f, -1.f);

    canvas.background_.draw(sprite);

    OnConfirm(canvas);
}


void FillTool::OnConfirm (Canvas &canvas)
{
    if (!using_)
        return;

    using_ = false;
}

void FillTool::OnCancel ()
{
    using_ = false;
}


Widget* FillTool::GetWidget() const
{
    return nullptr;
}

void FillTool::Fill(sf::Color &fill_color, const Dot &start_pos, Canvas &canvas, sf::Image *image)
{
    Container<sf::Vector2u> dots_;

    const size_t x_limit = canvas.GetSize().x;
    const size_t y_limit = canvas.GetSize().y;

    dots_.PushBack(sf::Vector2u((size_t)start_pos.x, (size_t)start_pos.y));

    

    while (!dots_.IsEmpty())
    {
        sf::Vector2u cur_dot = dots_.GetBack();
        dots_.PopBack();

        // printf("%u %u %u\n", fill_color.r, fill_color.b, fill_color.g);
        // printf("%u %u %u\n", image.getPixel(cur_dot.x - 1, start_pos.y).r, image.getPixel(cur_dot.x - 1, start_pos.y).b, image.getPixel(cur_dot.x - 1, start_pos.y).g);

        // printf("%u %u\n\n", cur_dot.x, cur_dot.y);

        // image.setPixel(cur_dot.x, cur_dot.y, cur_color_);

        // if (cur_dot.x > 0 && image.getPixel(cur_dot.x - 1, start_pos.y) == fill_color) 
        // {
        //     image.setPixel(cur_dot.x - 1, cur_dot.y, cur_color_);
        //     dots_.PushBack(sf::Vector2u(cur_dot.x - 1, cur_dot.y)); 
        // }

        // if (cur_dot.y > 0 && image.getPixel(cur_dot.x, start_pos.y - 1) == fill_color) 
        // {
        //     image.setPixel(cur_dot.x, cur_dot.y - 1, cur_color_);
        //     dots_.PushBack(sf::Vector2u(cur_dot.x, cur_dot.y - 1));
        // }

        // if (cur_dot.x < x_limit && image.getPixel(cur_dot.x + 1, start_pos.y) == fill_color) 
        // {
        //     image.setPixel(cur_dot.x + 1, cur_dot.y, cur_color_);
        //     dots_.PushBack(sf::Vector2u(cur_dot.x + 1, cur_dot.y));  
        // }

        // if (cur_dot.y + 1 < y_limit && image.getPixel(cur_dot.x, start_pos.y + 1) == fill_color) 
        // {
        //     image.setPixel(cur_dot.x, cur_dot.y + 1, cur_color_);
        //     dots_.PushBack(sf::Vector2u(cur_dot.x, cur_dot.y + 1)); 
        // }
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

void PolyLineTool::OnMainButton(ControlState state, const Dot &pos, Canvas &canvas)
{
    if (state.state != ControlState::ButtonState::PRESSED)
        return;


    start_pos_ = end_pos_ = pos;
    preview_->arr_.append(sf::Vector2f(start_pos_.x, start_pos_.y));

    using_ = true;
}

void PolyLineTool::OnMove (const Dot &pos, Canvas &canvas)
{
    end_pos_ = pos; 
}

void PolyLineTool::OnConfirm (Canvas &canvas)
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

    Dot real_pos = canvas.GetRealPos();
    
    Dot cur(0.0, 0.0); Dot next = Dot(preview_->arr_[size - 1].position.x, preview_->arr_[size - 1].position.y);

    for (size_t it = 0; it < size - 1; it++)
    {
        cur  = Dot(preview_->arr_[it].position.x, preview_->arr_[it].position.y);
        next = Dot(preview_->arr_[it + 1].position.x, preview_->arr_[it + 1].position.y);
        DrawLine(canvas.background_, cur + real_pos,  next + real_pos, cur_color_);
    }

    start_pos_ = end_pos_ = {0, 0};
    preview_->arr_.clear();
}

void PolyLineTool::OnCancel ()
{
    using_ = false;

    preview_->arr_.clear();
    start_pos_ = end_pos_ = {0, 0};
}

Widget* PolyLineTool::GetWidget() const
{
    return preview_;
}

//================================================================================