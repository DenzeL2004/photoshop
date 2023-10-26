#include "app.h"

const double WIDTH = 1600.0; 
const double HIEGHT = 900.0;

AppWindow::AppWindow(const char *path_texture, const Dot &offset, const Vector &scale):
           Window(path_texture, offset, scale), canvas_manager_(Empty_texture, Canvase_Manager_Offset, Canvase_Manager_Scale),
           tool_pallette_(), filter_pallette_()
{
    button_create_ = new Button("src/img/NewCanvasReleased.png", "src/img/NewCanvasPressed.png", 
                                "src/img/NewCanvasReleased.png", "src/img/NewCanvasPressed.png", 
                                new AddCanvase(&canvas_manager_, &tool_pallette_, &filter_pallette_), 
                                Button_Create_Offset, Button_Create_Scale);
    {
        tools_button_ = new WidgetContainer(Button_Tools_Offset, Button_Tools_Scale);
                
        tools_button_->AddWidget(new Button("src/img/LineReleased.png", "src/img/LinePressed.png", 
                                            "src/img/LinePressed.png",  "src/img/LinePressed.png", 
                                            new ChooseTool(ToolPalette::LINE, &tool_pallette_), 
                                            Button_Line_Offset, Button_Line_Scale));
        
        tools_button_->AddWidget(new Button("src/img/BrushReleased.png", "src/img/BrushPressed.png", 
                                            "src/img/BrushPressed.png",  "src/img/BrushPressed.png", 
                                            new ChooseTool(ToolPalette::BRUSH, &tool_pallette_), 
                                            Button_Brush_Offset, Button_Brush_Scale));
        
        tools_button_->AddWidget(new Button("src/img/SquareReleased.png", "src/img/SquarePressed.png", 
                                            "src/img/SquarePressed.png",  "src/img/SquarePressed.png", 
                                            new ChooseTool(ToolPalette::SQUARE, &tool_pallette_), 
                                            Button_Square_Offset, Button_Square_Scale));

        tools_button_->AddWidget(new Button("src/img/CircleReleased.png", "src/img/CirclePressed.png", 
                                            "src/img/CirclePressed.png",  "src/img/CirclePressed.png", 
                                            new ChooseTool(ToolPalette::CIRCLE, &tool_pallette_), 
                                            Button_Circle_Offset, Button_Circle_Scale));
        
        tools_button_->AddWidget(new Button("src/img/PolylineReleased.png", "src/img/PolylinePressed.png", 
                                            "src/img/PolylinePressed.png",  "src/img/PolylinePressed.png", 
                                            new ChooseTool(ToolPalette::POLYLINE, &tool_pallette_), 
                                            Button_Polyline_Offset, Button_Polyline_Scale));

        tools_button_->AddWidget(new Button("src/img/EraserReleased.png", "src/img/EraserPressed.png", 
                                            "src/img/EraserPressed.png",  "src/img/EraserPressed.png", 
                                            new ChooseTool(ToolPalette::ERASER, &tool_pallette_), 
                                            Button_Eraser_Offset, Button_Eraser_Scale));
    }

    {
        colors_button_ = new ButtonList("src/img/ColorsReleased.png", "src/img/ColorsCovered.png", 
                                       "src/img/ColorsCovered.png",   "src/img/ColorsCovered.png", 
                                        nullptr, Button_Colors_Offset, Button_Colors_Scale);
        
        colors_button_->action_ = new ShowButtonList(&(colors_button_->buttons_)); 

        
        colors_button_->buttons_.PushBack(new Button("src/img/RedReleased.png", "src/img/RedCovered.png", 
                                                    "src/img/RedCovered.png",  "src/img/RedCovered.png", 
                                                    new ChooseColor(sf::Color::Red, &tool_pallette_), 
                                                    Button_Red_Offset, Button_Red_Scale));

        colors_button_->buttons_.PushBack(new Button("src/img/BlueReleased.png", "src/img/BlueCovered.png", 
                                                    "src/img/BlueCovered.png",  "src/img/BlueCovered.png", 
                                                    new ChooseColor(sf::Color::Blue, &tool_pallette_), 
                                                    Button_Blue_Offset, Button_Blue_Scale));

        colors_button_->buttons_.PushBack(new Button("src/img/GreenReleased.png", "src/img/GreenCovered.png", 
                                                    "src/img/GreenCovered.png",  "src/img/GreenCovered.png", 
                                                    new ChooseColor(sf::Color::Green, &tool_pallette_), 
                                                    Button_Green_Offset, Button_Green_Scale));
        
        
        size_t size = colors_button_->buttons_.GetSize();
        for (size_t it = 0; it < size; it++)
            colors_button_->buttons_[it]->state_ = Button::ButtonState::DISABLED;
    }

} 


void AppWindow::Draw(sf::RenderTarget &target, Container<Transform> &stack_transform)
{
    Window::Draw(target, stack_transform);
   
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));

    canvas_manager_.Draw(target, stack_transform);
    button_create_->Draw(target, stack_transform);
    colors_button_->Draw(target, stack_transform);
    tools_button_->Draw(target, stack_transform);
    
    stack_transform.PopBack();

    return;
}

//================================================================================

bool AppWindow::OnMouseMoved(const double x, const double y, Container<Transform> &stack_transform)
{
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    Transform last_trf = stack_transform.GetBack();
    
    Dot new_coord = last_trf.ApplyTransform({x, y});

    button_create_->OnMouseMoved(x, y, stack_transform);
    tools_button_->OnMouseMoved(x, y, stack_transform);
    colors_button_->OnMouseMoved(x, y, stack_transform);
    canvas_manager_.OnMouseMoved(x, y, stack_transform);
    
    stack_transform.PopBack();

    return true;
}

//================================================================================

bool AppWindow::OnMousePressed(const double x, const double y, const MouseKey key, Container<Transform> &stack_transform)
{
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));
    Transform last_trf = stack_transform.GetBack();
    
    Dot new_coord = last_trf.ApplyTransform({x, y});

    bool flag = CheckIn(new_coord);
    if (flag)
    {
        flag = false;
        flag |= button_create_->OnMousePressed(x, y, key, stack_transform);
        flag |= tools_button_->OnMousePressed(x, y, key, stack_transform);
        flag |= colors_button_->OnMousePressed(x, y, key, stack_transform);
        if (!flag) flag |= canvas_manager_.OnMousePressed(x, y, key, stack_transform);
        
    }

    stack_transform.PopBack();

    return flag;
}

//================================================================================

bool AppWindow::OnMouseReleased(const double x, const double y, const MouseKey key, Container<Transform> &stack_transform)
{
    stack_transform.PushBack(transform_.ApplyPrev(stack_transform.GetBack()));

    button_create_->OnMouseReleased(x, y, key, stack_transform);
    tools_button_->OnMouseReleased(x, y, key, stack_transform);
    colors_button_->OnMouseReleased(x, y, key, stack_transform);
    canvas_manager_.OnMouseReleased(x, y, key, stack_transform);

    stack_transform.PopBack();
    return true;
}

//================================================================================

bool AppWindow::OnKeyboardPressed(const KeyboardKey key)
{
    if (key == KeyboardKey::CTRL)
    {
        filter_pallette_.setActive(true);
        return true;
    }

    return canvas_manager_.OnKeyboardPressed(key);
}

//================================================================================

bool AppWindow::OnKeyboardReleased(const KeyboardKey key)
{
    if (key == KeyboardKey::CTRL)
    {
        filter_pallette_.setActive(false);
        return true;
    }

    bool flag = canvas_manager_.OnKeyboardReleased(key);
    return flag;
}

//================================================================================

void AppWindow::PassTime(const time_t delta_time)
{
    printf("AppWindow: mouse keyboard kye released\n");
    return;
}

void UseApp()
{
    sf::RenderWindow window(sf::VideoMode((uint32_t)WIDTH, (uint32_t)HIEGHT), "window manager");

    

    bool close_window = false;
    Button *close_button = new Button(Cross_Button_Release, Cross_Button_Covered,
                                      Cross_Button_Release, Cross_Button_Covered, new Click(&close_window),
                                      Dot(0.98, 0.0), Vector(0.02, 0.025));
 

    AppWindow *app = new AppWindow("src/img/window.jpg", {0.025, 0.03}, Vector(0.95, 0.91)); 

    Frame border("src/img/border.png", close_button, Title("window manager", sf::Color::Black), app, Dot(0.0, 0.0), Vector(1, 1));

    Container<Transform> stack;
    stack.PushBack(Transform({0.0, 0.0}, {WIDTH, HIEGHT}));

    while (window.isOpen())
    {   
        window.clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            sf::Mouse mouse;
            EventAdapter(border, mouse.getPosition(window).x, mouse.getPosition(window).y, event, stack);

            if (close_window)
                window.close();
        }

        border.Draw(window, stack);
    
        window.display();
    }

    return;
}