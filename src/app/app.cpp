#include "app.h"

const double WIDTH = 1600.0; 
const double HIEGHT = 900.0;

AppWindow::AppWindow(   const char *path_texture,
                        const Vector &size, const Vector &pos, 
                        const Widget *parent, const Vector &parent_size, 
                        const Vector &origin, const Vector &scale):
                        Window(path_texture, size, pos, parent, (parent != nullptr) ? parent->getLayoutBox().getSize() : parent_size, origin, scale), 
                        canvas_manager_(Empty_texture, Dot(size.x, Canvase_manager_size.y * size.y), Canvase_manager_pos, this),
                        tool_pallette_(), filter_pallette_(), 
                        colors_(Colors_palette_size, Colors_palette_pos, this),
                        active_hot_key_(false)
{

    widgets_.pushBack(new Window("src/img/frame2.png", 
                                Vector(size.x, Menu_size.y), Menu_pos, this));

    widgets_.pushBack(new Button("src/img/NewCanvasReleased.png", "src/img/NewCanvasPressed.png", 
                                "src/img/NewCanvasReleased.png", "src/img/NewCanvasPressed.png", 
                                new AddCanvase(&canvas_manager_, &tool_pallette_, &filter_pallette_), 
                                Button_create_size, Button_create_pos, this));
    
    
    {
        ButtonList *tools_button_ = new ButtonList( "src/img/ToolsReleased.png", "src/img/ToolsPressed.png", 
                                                    "src/img/ToolsPressed.png", "src/img/ToolsPressed.png", 
                                                    nullptr, Button_Tools_size, Button_Tools_pos , this);

        tools_button_->action_ = new ShowButtonList(&(tools_button_->buttons_)); 
                
        tools_button_->addButton(new Button("src/img/LineReleased.png", "src/img/LinePressed.png", 
                                            "src/img/LinePressed.png",  "src/img/LinePressed.png", 
                                            new ChooseTool(ToolPalette::LINE, &tool_pallette_), 
                                            Button_Line_size, Button_Line_pos, tools_button_));
        
        tools_button_->addButton(new Button("src/img/BrushReleased.png", "src/img/BrushPressed.png", 
                                            "src/img/BrushPressed.png",  "src/img/BrushPressed.png", 
                                            new ChooseTool(ToolPalette::BRUSH, &tool_pallette_), 
                                            Button_Brush_size, Button_Brush_pos, tools_button_));
        
        tools_button_->addButton(new Button("src/img/SquareReleased.png", "src/img/SquarePressed.png", 
                                            "src/img/SquarePressed.png",  "src/img/SquarePressed.png", 
                                            new ChooseTool(ToolPalette::SQUARE, &tool_pallette_), 
                                            Button_Square_size, Button_Square_pos, tools_button_));

        tools_button_->addButton(new Button("src/img/CircleReleased.png", "src/img/CirclePressed.png", 
                                            "src/img/CirclePressed.png",  "src/img/CirclePressed.png", 
                                            new ChooseTool(ToolPalette::CIRCLE, &tool_pallette_), 
                                            Button_Circle_size, Button_Circle_pos, tools_button_));
        
        tools_button_->addButton(new Button("src/img/PolylineReleased.png", "src/img/PolylinePressed.png", 
                                            "src/img/PolylinePressed.png",  "src/img/PolylinePressed.png", 
                                            new ChooseTool(ToolPalette::POLYLINE, &tool_pallette_), 
                                            Button_Polyline_size, Button_Polyline_pos, tools_button_));

        tools_button_->addButton(new Button("src/img/BrushReleased.png", "src/img/BrushPressed.png", 
                                            "src/img/BrushPressed.png",  "src/img/BrushPressed.png", 
                                            new ChooseTool(ToolPalette::PEN, &tool_pallette_), 
                                            Button_Pen_size, Button_Pen_pos, tools_button_));

        tools_button_->addButton(new Button("src/img/EraserReleased.png", "src/img/EraserPressed.png", 
                                            "src/img/EraserPressed.png",  "src/img/EraserPressed.png", 
                                            new ChooseTool(ToolPalette::ERASER, &tool_pallette_), 
                                            Button_Eraser_size, Button_Eraser_pos, tools_button_));

        size_t size = tools_button_->buttons_.getSize();
        for (size_t it = 0; it < size; it++)
            tools_button_->buttons_[it]->state_ = Button::ButtonState::DISABLED;
        
        widgets_.pushBack(tools_button_);
    }    

    {
        ButtonList *filters_button = new ButtonList("src/img/FilterReleased.png", "src/img/FilterPressed.png", 
                                                    "src/img/FilterPressed.png", "src/img/FilterPressed.png", 
                                                    nullptr, Button_Filter_size, Button_Filter_pos, this);

        filters_button->action_ = new ShowButtonList(&(filters_button->buttons_)); 


        filters_button->addButton(new Button("src/img/IncBrightReleased.png", "src/img/IncBrightPressed.png", 
                                                "src/img/IncBrightPressed.png",  "src/img/IncBrightPressed.png", 
                                                new ChangeBrightness(&filter_pallette_, &canvas_manager_, 0.05f), 
                                                Button_Inclight_size, Button_Inclight_pos, filters_button));

        filters_button->addButton(new Button("src/img/DecBrightReleased.png", "src/img/DecBrightPressed.png", 
                                                "src/img/DecBrightPressed.png",  "src/img/DecBrightPressed.png", 
                                                new ChangeBrightness(&filter_pallette_, &canvas_manager_, -0.05f),
                                                Button_Declight_size, Button_Declight_pos, filters_button));

        size_t size = filters_button->buttons_.getSize();
        for (size_t it = 0; it < size; it++)
            filters_button->buttons_[it]->state_ = Button::ButtonState::DISABLED;

        widgets_.pushBack(filters_button);
    }
} 


void AppWindow::draw(sf::RenderTarget &target, Container<Transform> &stack_transform)
{
    Window::draw(target, stack_transform);
   
    Transform trf(getLayoutBox().getPosition(), scale_);
    stack_transform.pushBack(trf.applyPrev(stack_transform.getBack()));

    canvas_manager_.draw(target, stack_transform);
    
    size_t size = widgets_.getSize(); 
    for (size_t it = 0; it < size; it++)
    {
        widgets_[it]->draw(target, stack_transform);
    }

    colors_.draw(target, stack_transform);
    
    stack_transform.popBack();

    return;
}

//================================================================================

bool AppWindow::onMouseMoved(const Vector &pos, Container<Transform> &stack_transform)
{
    Transform trf(getLayoutBox().getPosition(), scale_);
    stack_transform.pushBack(trf.applyPrev(stack_transform.getBack()));

    size_t size = widgets_.getSize(); 
    for (size_t it = 0; it < size; it++)
    {
        widgets_[it]->onMouseMoved(pos, stack_transform);
    }

    canvas_manager_.onMouseMoved(pos, stack_transform);
    
    stack_transform.popBack();

    return true;
}

//================================================================================

bool AppWindow::onMousePressed(const Vector &pos, const MouseKey key, Container<Transform> &stack_transform)
{
    Transform trf(getLayoutBox().getPosition(), scale_);
    stack_transform.pushBack(trf.applyPrev(stack_transform.getBack()));
    
    Transform last_trf = stack_transform.getBack();
    Dot new_coord = last_trf.applyTransform(pos);

    bool flag = checkIn(new_coord, getLayoutBox().getSize());
    if (flag)
    {
        flag = false;

        if (colors_.onMousePressed(pos, key, stack_transform))
        {
            tool_pallette_.setActiveColor(colors_.getActiveColor());
            flag = true;
        }

        size_t size = widgets_.getSize(); 
        for (size_t it = 0; it < size; it++)
        {
            flag = widgets_[it]->onMousePressed(pos, key, stack_transform);
        }

        if (!flag) flag |= canvas_manager_.onMousePressed(pos, key, stack_transform);   
    }

    stack_transform.popBack();

    return flag;
}

//================================================================================

bool AppWindow::onMouseReleased(const Vector &pos, const MouseKey key, Container<Transform> &stack_transform)
{
    Transform trf(getLayoutBox().getPosition(), scale_);
    stack_transform.pushBack(trf.applyPrev(stack_transform.getBack()));

    size_t size = widgets_.getSize(); 
    for (size_t it = 0; it < size; it++)
    {
        widgets_[it]->onMouseReleased(pos, key, stack_transform);
    }
    canvas_manager_.onMouseReleased(pos, key, stack_transform);

    stack_transform.popBack();
    return true;
}

//================================================================================

bool AppWindow::onKeyboardPressed(const KeyboardKey key)
{
    bool flag = handlHotKey(key);

    if (!active_hot_key_)
        return canvas_manager_.onKeyboardPressed(key);

    return flag;
}

//================================================================================

bool AppWindow::handlHotKey(const KeyboardKey key)
{
    if (key == KeyboardKey::CTRL)
    {
        filter_pallette_.setActive(true);
        return true;
    }

    // if (active_hot_key_)
    // {
    //     switch (key)
    //     {
    //         case /* constant-expression */:
    //             /* code */
    //             break;
            
    //         default:
    //             break;
    //     }
    // }

    // if (key == KeyboardKey::ALT)
    // {
    //     active_hot_key_ = true;
    //     return true;
    // }
    
    return canvas_manager_.onKeyboardPressed(key);
}

//================================================================================

bool AppWindow::onKeyboardReleased(const KeyboardKey key)
{
    if (key == KeyboardKey::CTRL)
    {
        filter_pallette_.setActive(false);
        return true;
    }

    // if (key == KeyboardKey::ALT)
    //     active_hot_key_ = false;

    return canvas_manager_.onKeyboardPressed(key);
}

//================================================================================

bool AppWindow::onTick(const time_t delta_time)
{
    return false;
}

void useApp()
{
    sf::RenderWindow window(sf::VideoMode((uint32_t)WIDTH, (uint32_t)HIEGHT), "window manager");

    Widget widget(Vector(0, 0), Vector(WIDTH, HIEGHT), nullptr, Vector(WIDTH, HIEGHT));

    Frame border(   Frame_Texture, Title({10.0, 10.0}, "window manager", sf::Color::Black), 
                    Vector(WIDTH, HIEGHT), Vector(0, 0), &widget);

    bool close_window = false;
    Button *close_button = new Button(  Cross_Button_Release, Cross_Button_Covered,
                                        Cross_Button_Release, Cross_Button_Covered, 
                                        new Click(&close_window),
                                        Vector(25.0, 25.0), Vector(WIDTH - 25.0, 0), &border);
 

    AppWindow *app = new AppWindow("src/img/window.jpg",Vector(WIDTH - 20 , HIEGHT - 40), Vector(10, 30), &border); 

    border.addWidget(close_button);
    border.addWidget(app);

    Container<Transform> stack;
    stack.pushBack(Transform({0.0, 0.0}, {1.0, 1.0}));

    border.onUpdate(widget.getLayoutBox());

    while (window.isOpen())
    {   
        window.clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            sf::Mouse mouse;
            eventAdapter(border, mouse.getPosition(window).x, mouse.getPosition(window).y, event, stack);

            if (close_window)
                window.close();
        }

        border.draw(window, stack);
    
        window.display();
    }

    return;
}