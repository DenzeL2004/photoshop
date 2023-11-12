#include "tools.h"


static void correctPos(Vec2d &pos, const Canvas &canvas);

static void correctPos(Vec2d &pos, const Canvas &canvas)
{
    pos += canvas.getRealPos();
    pos.y = canvas.getCanvasSize().y - pos.y;
}

ToolPalette::ToolPalette():
        tools_(),
        active_tool_(ToolType::NOTHING), 
        color_type_(FOREGROUND), foreground_color_(sf::Color::White), background_color_(sf::Color::White)
{
    tools_.pushBack(new LineTool(&foreground_color_));
    tools_.pushBack(new BrushTool(&foreground_color_));
    tools_.pushBack(new SquareTool(&foreground_color_));
    tools_.pushBack(new CircleTool(&foreground_color_));
    tools_.pushBack(new PolyLineTool(&foreground_color_));
    tools_.pushBack(new BrushTool(&background_color_));
    tools_.pushBack(new PenTool(&foreground_color_));
    tools_.pushBack(new TextTool(&foreground_color_));
}


//================================================================================

ToolPalette::~ToolPalette()
{
    size_t size = tools_.getSize();
    for (size_t it = 0; it < size; it++)
        delete tools_[it];
}   

Tool* ToolPalette::getActiveTool () const
{
    if (active_tool_ == ToolPalette::ToolType::NOTHING)
        return nullptr;

    return tools_[active_tool_];
}

void ToolPalette::setActiveColor (const sf::Color &color) 
{
    if (color_type_ == ToolPalette::ColorType::FOREGROUND)
        foreground_color_ = color;

    if (color_type_ == ToolPalette::ColorType::BACKGROUND)
        background_color_ = color;
}

sf::Color ToolPalette::getActiveColor () const
{
    if (color_type_ == ToolPalette::ColorType::FOREGROUND)
        return foreground_color_;

    if (color_type_ == ToolPalette::ColorType::BACKGROUND)
        return background_color_;
}

//================================================================================

void ToolPalette::setActiveTool(const ToolType tool_type)
{
    active_tool_ = tool_type;
}

//================================================================================

//LINE  

class LineWidget : public Widget
{
    public:
        LineWidget( const Dot *start_pos, const Dot *end_pos, const sf::Color *cur_color):
                    Widget(Vec2d(1.0, 1.0), Vec2d(0.0,  0.0), nullptr),
                    start_pos_(*start_pos), end_pos_(*end_pos), cur_color_(*cur_color){}

        ~LineWidget(){}

        virtual bool onMousePressed     (const Vec2d &pos, const MouseKey key, Container<Transform> &stack_transform) {return true;};
        virtual bool onMouseMoved       (const Vec2d &pos, Container<Transform> &stack_transform) {return true;}
        virtual bool onMouseReleased    (const Vec2d &pos, const MouseKey key, Container<Transform> &stack_transform){return true;}

        virtual bool onKeyboardPressed  (const KeyboardKey){return true;}
        virtual bool onKeyboardReleased (const KeyboardKey){return true;}

        bool onTick             (const time_t delta_time){}

        void draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform)
        {
            
            Transform last_trf = stack_transform.getBack();
            drawLine(targert, start_pos_ + last_trf.offset, end_pos_ + last_trf.offset, cur_color_);
        }
    
        

    private:
       const Dot &start_pos_;
       const Dot &end_pos_;
       const sf::Color &cur_color_;
};

LineTool::LineTool(const sf::Color *cur_color):
                  using_(false), start_pos_(), end_pos_(), 
                  preview_(new LineWidget(&start_pos_, &end_pos_, cur_color)), cur_color_(*cur_color){}


//================================================================================
void LineTool::onMainButton(ControlState state, const Dot &pos, Canvas &canvas)
{
    if (state.state != ControlState::ButtonState::PRESSED)
        return;

    if (using_)
        return;

    start_pos_ = end_pos_ = pos;

    using_ = true;
}

void LineTool::onMove(const Dot &pos, Canvas &canvas)
{
    if (!using_)
        return;
    
    end_pos_ = pos; 
}

void LineTool::onConfirm (Canvas &canvas)
{
    if (!using_)
        return;

    correctPos(start_pos_, canvas);
    correctPos(end_pos_, canvas);

    drawLine(canvas.getBackground(), start_pos_, end_pos_, cur_color_);
    start_pos_  = end_pos_ = {0, 0};

    using_ = false;
}

void LineTool::onCancel ()
{
    start_pos_  = end_pos_ = {0, 0};
    using_ = false;
}

Widget* LineTool::getWidget() const
{
    return preview_;
}

//================================================================================

//SQUARE
class SquareWidget : public Widget
{
    public:
        SquareWidget(   const Dot *start_pos, const Dot *end_pos, const sf::Color *cur_color):
                        Widget(Vec2d(1.0, 1.0), Vec2d(0.0,  0.0), nullptr),
                        start_pos_(*start_pos), end_pos_(*end_pos), cur_color_(*cur_color){}

        ~SquareWidget(){}

        virtual bool onMousePressed     (const Vec2d &pos, const MouseKey key, Container<Transform> &stack_transform) {return true;};
        virtual bool onMouseMoved       (const Vec2d &pos, Container<Transform> &stack_transform) {return true;}
        virtual bool onMouseReleased    (const Vec2d &pos, const MouseKey key, Container<Transform> &stack_transform){return true;}

        virtual bool onKeyboardPressed  (const KeyboardKey){return true;}
        virtual bool onKeyboardReleased (const KeyboardKey){return true;}

        bool onTick             (const time_t delta_time){}

        void draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform)
        {
            Transform last_trf = stack_transform.getBack();
            drawRectangle(targert, start_pos_ + last_trf.offset, end_pos_ + last_trf.offset, cur_color_);     
        }
    
        

    private:
       const Dot &start_pos_;
       const Dot &end_pos_;
       const sf::Color &cur_color_;
};

//================================================================================

SquareTool::SquareTool(const sf::Color *cur_color):
                  using_(false), start_pos_(), end_pos_(), 
                  preview_(new SquareWidget(&start_pos_, &end_pos_, cur_color)), cur_color_(*cur_color){}

void SquareTool::onMainButton(ControlState state, const Dot &pos, Canvas &canvas)
{
    if (state.state != ControlState::ButtonState::PRESSED)
        return;

    if (using_)
        return;

    start_pos_ = end_pos_ = pos;

    using_ = true;
}

void SquareTool::onMove(const Dot &pos, Canvas &canvas)
{
    if (!using_)
        return;
    
    end_pos_ = pos;
}

void SquareTool::onConfirm (Canvas &canvas)
{
    if (!using_)
        return;
    
    correctPos(start_pos_, canvas);
    correctPos(end_pos_, canvas);

    drawRectangle(canvas.getBackground(), start_pos_, end_pos_, cur_color_);
    
    start_pos_  = end_pos_ = {0, 0};

    using_ = false;
}

void SquareTool::onCancel ()
{
    start_pos_  = end_pos_ = {0, 0};
    using_ = false;
}


Widget* SquareTool::getWidget() const
{
    return preview_;
}

//================================================================================

//Circle

class CircleWidget : public Widget
{
    public:
        CircleWidget(   const Dot *start_pos, const Dot *end_pos, const sf::Color *cur_color):
                        Widget(Vec2d(1.0, 1.0), Vec2d(0.0,  0.0), nullptr),
                        start_pos_(*start_pos), end_pos_(*end_pos), cur_color_(*cur_color){}

        ~CircleWidget(){}

        virtual bool onMousePressed     (const Vec2d &pos, const MouseKey key, Container<Transform> &stack_transform) {return true;};
        virtual bool onMouseMoved       (const Vec2d &pos, Container<Transform> &stack_transform) {return true;}
        virtual bool onMouseReleased    (const Vec2d &pos, const MouseKey key, Container<Transform> &stack_transform){return true;}

        virtual bool onKeyboardPressed  (const KeyboardKey){return true;}
        virtual bool onKeyboardReleased (const KeyboardKey){return true;}

        bool onTick             (const time_t delta_time){}

        void draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform)
        {
            
            Transform last_trf = stack_transform.getBack();

            Dot center = start_pos_ + last_trf.offset;
            Dot other  = end_pos_ + last_trf.offset;

            double rad = (center - other).length();

            drawCircle(targert, center, (float)rad, cur_color_);
        }
    
        

    private:
       const Dot &start_pos_;
       const Dot &end_pos_;
       const sf::Color &cur_color_;
};

//================================================================================

CircleTool::CircleTool(const sf::Color *cur_color):
                  using_(false), start_pos_(), end_pos_(), 
                  preview_(new CircleWidget(&start_pos_, &end_pos_, cur_color)), cur_color_(*cur_color){}

void CircleTool::onMainButton(ControlState state, const Dot &pos, Canvas &canvas)
{
    if (state.state != ControlState::ButtonState::PRESSED)
        return;

    if (using_)
        return;

    start_pos_ = end_pos_ = pos;

    using_ = true;
}

void CircleTool::onMove(const Dot &pos, Canvas &canvas)
{
    if (!using_)
        return;
    
    end_pos_ = pos;
}

void CircleTool::onConfirm (Canvas &canvas)
{
    if (!using_)
        return;

    double rad = (start_pos_ - end_pos_).length();

    correctPos(start_pos_, canvas);

    drawCircle(canvas.getBackground(), start_pos_, (float)rad, cur_color_);
    start_pos_  = end_pos_ = {0, 0};

    using_ = false;
}

void CircleTool::onCancel ()
{
    start_pos_  = end_pos_ = {0, 0};
    using_ = false;
}

Widget* CircleTool::getWidget() const
{
    return preview_;
}

//================================================================================
//Brushh

BrushTool::BrushTool(const sf::Color *cur_color):
                    using_(false), cur_color_(*cur_color){}


void BrushTool::onMainButton(ControlState state, const Dot &pos, Canvas &canvas)
{
    if (state.state != ControlState::ButtonState::PRESSED)
        return;

    if (using_)
        return;

    using_ = true;

    Vec2d tmp_pos = pos;
    correctPos(tmp_pos, canvas);

    drawForm(tmp_pos, canvas);
}

void BrushTool::onMove(const Dot &pos, Canvas &canvas)
{
    if (!using_)
        return;

    Vec2d tmp_pos = pos;
    correctPos(tmp_pos, canvas);
    
    drawForm(tmp_pos, canvas);
}

void BrushTool::onConfirm (Canvas &canvas)
{
    if (!using_)
        return;

    using_ = false;
}

Widget* BrushTool::getWidget() const
{
    return nullptr;
}

void BrushTool::drawForm (const Dot &pos, Canvas &canvas)
{
    drawCircle(canvas.getBackground(), pos, 10, cur_color_);
}

//================================================================================
PenTool::PenTool(const sf::Color *cur_color):
                    using_(false), cur_color_(*cur_color){}


void PenTool::onMainButton(ControlState state, const Dot &pos, Canvas &canvas)
{
    if (state.state != ControlState::ButtonState::PRESSED)
        return;

    if (using_)
        return;

    using_ = true;

    prev_pos_ = pos;
    correctPos(prev_pos_, canvas);

    drawPixel(canvas.getBackground(), prev_pos_, cur_color_);
}

void PenTool::onMove(const Dot &pos, Canvas &canvas)
{
    if (!using_)
        return;

    Vec2d tmp_pos = pos;
    correctPos(tmp_pos, canvas);

    drawLine(canvas.getBackground(), prev_pos_, tmp_pos, cur_color_);

    prev_pos_ = tmp_pos;
}

void PenTool::onConfirm (Canvas &canvas)
{
    if (!using_)
        return;

    using_ = false;
}

Widget* PenTool::getWidget() const
{
    return nullptr;
}

//================================================================================
//Fill

// FillTool::FillTool(const sf::Color *cur_color):
//                     using_(false), cur_color_(*cur_color){}


// void FillTool::onMainButton(ControlState state, const Dot &pos, Canvas &canvas)
// {
//     if (state.state != ControlState::ButtonState::PRESSED)
//         return;

//     if (using_)
//         return;

//     using_ = true;
//     sf::Image image = canvas.getBackground().getTexture().copyToImage();
    
//     sf::Color fill_color = image.getPixel(size_t(pos.x), canvas.getSize().y - size_t(pos.y));
   
//     for (size_t it = 10; it < 200; it++)
//     {
//         image.setPixel(130, 2000 - it, sf::Color::Cyan);
//         image.setPixel(131, 2000 - it, sf::Color::Cyan);
//         image.setPixel(132, 2000 - it, sf::Color::Cyan);
//         image.setPixel(133, 2000 - it, sf::Color::Cyan);
//     }
    
//     Fill(fill_color, {size_t(pos.x), canvas.getSize().y - size_t(pos.y)}, canvas, &image);

//     sf::Texture texture;
//     texture.loadFromImage(image);
//     sf::Sprite sprite(texture);
//     sprite.scale(1.f, -1.f);

//     canvas.getBackground().draw(sprite);

//     onConfirm(canvas);
// }


// void FillTool::onConfirm (Canvas &canvas)
// {
//     if (!using_)
//         return;

//     using_ = false;
// }

// void FillTool::onCancel ()
// {
//     using_ = false;
// }


// Widget* FillTool::getWidget() const
// {
//     return nullptr;
// }

// void FillTool::Fill(sf::Color &fill_color, const Dot &start_pos, Canvas &canvas, sf::Image *image)
// {
//     Container<sf::Vector2u> dots_;

//     const size_t x_limit = canvas.getSize().x;
//     const size_t y_limit = canvas.getSize().y;

//     dots_.pushBack(sf::Vector2u((size_t)start_pos.x, (size_t)start_pos.y));

    

//     while (!dots_.IsEmpty())
//     {
//         sf::Vector2u cur_dot = dots_.getBack();
//         dots_.PopBack();

//         // printf("%u %u %u\n", fill_color.r, fill_color.b, fill_color.g);
//         // printf("%u %u %u\n", image.getPixel(cur_dot.x - 1, start_pos.y).r, image.getPixel(cur_dot.x - 1, start_pos.y).b, image.getPixel(cur_dot.x - 1, start_pos.y).g);

//         // printf("%u %u\n\n", cur_dot.x, cur_dot.y);

//         // image.setPixel(cur_dot.x, cur_dot.y, cur_color_);

//         // if (cur_dot.x > 0 && image.getPixel(cur_dot.x - 1, start_pos.y) == fill_color) 
//         // {
//         //     image.setPixel(cur_dot.x - 1, cur_dot.y, cur_color_);
//         //     dots_.pushBack(sf::Vector2u(cur_dot.x - 1, cur_dot.y)); 
//         // }

//         // if (cur_dot.y > 0 && image.getPixel(cur_dot.x, start_pos.y - 1) == fill_color) 
//         // {
//         //     image.setPixel(cur_dot.x, cur_dot.y - 1, cur_color_);
//         //     dots_.pushBack(sf::Vector2u(cur_dot.x, cur_dot.y - 1));
//         // }

//         // if (cur_dot.x < x_limit && image.getPixel(cur_dot.x + 1, start_pos.y) == fill_color) 
//         // {
//         //     image.setPixel(cur_dot.x + 1, cur_dot.y, cur_color_);
//         //     dots_.pushBack(sf::Vector2u(cur_dot.x + 1, cur_dot.y));  
//         // }

//         // if (cur_dot.y + 1 < y_limit && image.getPixel(cur_dot.x, start_pos.y + 1) == fill_color) 
//         // {
//         //     image.setPixel(cur_dot.x, cur_dot.y + 1, cur_color_);
//         //     dots_.pushBack(sf::Vector2u(cur_dot.x, cur_dot.y + 1)); 
//         // }
//     }
    
// }


//================================================================================

class PolyLineWidget : public Widget
{
    public:
        PolyLineWidget( const Dot *end_pos, const sf::Color *cur_color):
                        Widget(Vec2d(1.0, 1.0), Vec2d(0.0,  0.0), nullptr),
                        end_pos_(*end_pos), cur_color_(*cur_color){}

        ~PolyLineWidget(){}

        virtual bool onMousePressed     (const Vec2d &pos, const MouseKey key, Container<Transform> &stack_transform) {return true;};
        virtual bool onMouseMoved       (const Vec2d &pos, Container<Transform> &stack_transform) {return true;}
        virtual bool onMouseReleased    (const Vec2d &pos, const MouseKey key, Container<Transform> &stack_transform){return true;}

        virtual bool onKeyboardPressed  (const KeyboardKey){return true;}
        virtual bool onKeyboardReleased (const KeyboardKey){return true;}

        bool onTick             (const time_t delta_time){}

        void draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform)
        {
            Transform last_trf = stack_transform.getBack();
            size_t size = arr_.getVertexCount();

            if (size == 0)
                return;

            Dot cur(0.0, 0.0); 
            Dot next = Dot(arr_[size - 1].position.x, arr_[size - 1].position.y);

            for (size_t it = 0; it < size - 1; it++)
            {
                cur  = Dot(arr_[it].position.x, arr_[it].position.y);
                next = Dot(arr_[it + 1].position.x, arr_[it + 1].position.y);
                drawLine(targert, cur + last_trf.offset, next + last_trf.offset, cur_color_);
            }

            drawLine(targert, next + last_trf.offset,  end_pos_ + last_trf.offset, cur_color_);

        }
    
        

        sf::VertexArray arr_;

    private:
        const Dot &end_pos_;
       
        const sf::Color &cur_color_;
};


PolyLineTool::PolyLineTool(const sf::Color *cur_color):
                  using_(false), start_pos_(), end_pos_(), 
                  preview_(new PolyLineWidget(&end_pos_, cur_color)), cur_color_(*cur_color){}

void PolyLineTool::onMainButton(ControlState state, const Dot &pos, Canvas &canvas)
{
    if (state.state != ControlState::ButtonState::PRESSED)
        return;

    start_pos_ = end_pos_ = pos;
    preview_->arr_.append(sf::Vector2f(start_pos_.x, start_pos_.y));

    using_ = true;
}

void PolyLineTool::onMove (const Dot &pos, Canvas &canvas)
{
    end_pos_ = pos; 
}

void PolyLineTool::onConfirm (Canvas &canvas)
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
        
        correctPos(cur, canvas);
        correctPos(next, canvas);
        
        drawLine(canvas.getBackground(), cur,  next, cur_color_);
    }

    start_pos_ = end_pos_ = {0, 0};
    preview_->arr_.clear();
}

void PolyLineTool::onCancel ()
{
    using_ = false;

    preview_->arr_.clear();
    start_pos_ = end_pos_ = {0, 0};
}

Widget* PolyLineTool::getWidget() const
{
    return preview_;
}

//================================================================================


TextTool::TextTool(const sf::Color *cur_color):
                  using_(false), start_pos_(), 
                  preview_(new TextBox(50, 40, cur_color, Vec2d(0.0,  0.0), nullptr)), cur_color_(*cur_color){}

void TextTool::onMainButton(ControlState state, const Dot &pos, Canvas &canvas)
{
    if (state.state != ControlState::ButtonState::PRESSED)
        return;

    start_pos_ = pos;

    preview_->getLayoutBox().setPosition(start_pos_);

    using_ = true;
}

void TextTool::onConfirm (Canvas &canvas)
{
    if (using_) 
    {
        using_ = false;
        return;
    }

    correctPos(start_pos_, canvas);

    sf::Text text = preview_->getText();
    text.setPosition(start_pos_.x, start_pos_.y);
    text.setColor(cur_color_);

    text.scale(1.0f, -1.0f);

    canvas.getBackground().draw(text);
    preview_->clear();   
}

void TextTool::onCancel ()
{
    using_ = false;

    preview_->clear();
}

Widget* TextTool::getWidget() const
{
    return preview_;
}
