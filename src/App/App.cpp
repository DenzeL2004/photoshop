#include "App.h"

static void runEvent(sf::Event &event, plug::EHC &context, Vec2d mouse_pos, plug::Widget &widget);

static void defineModifierKey(sf::Event &event, bool &shift, bool &ctrl, bool &alt);

// AppWindow::AppWindow(   const char *path_texture,
//                         const Vec2d &size, const Vec2d &pos, 
//                         const Widget *parent, const Vec2d &parent_size, 
//                         const Vec2d &origin, const Vec2d &scale):
//                         Window(path_texture, size, pos, parent, (parent != nullptr) ? parent->getLayoutBox().getSize() : parent_size, origin, scale), 
//                         canvas_manager_(Empty_texture, Dot(size.x, Canvase_manager_size.y * size.y), Canvase_manager_pos, this),
//                         tool_pallette_(), filter_pallette_(), 
//                         colors_(Colors_palette_size, Colors_palette_pos, this)
// {
//     widgets_.pushBack(new Window("src/img/frame2.png", 
//                                 Vec2d(size.x, Menu_size.y), Menu_pos, this));

//     widgets_.pushBack(new Button("src/img/NewCanvasReleased.png", "src/img/NewCanvasPressed.png", 
//                                 "src/img/NewCanvasReleased.png", "src/img/NewCanvasPressed.png", 
//                                 new AddCanvase(&canvas_manager_, &tool_pallette_, &filter_pallette_), 
//                                 Button_create_size, Button_create_pos, this));
    
    
//     {
//         ButtonList *tools_button_ = new ButtonList( "src/img/ToolsReleased.png", "src/img/ToolsPressed.png", 
//                                                     "src/img/ToolsPressed.png", "src/img/ToolsPressed.png", 
//                                                     nullptr, Button_Tools_size, Button_Tools_pos , this);

//         tools_button_->action_ = new ShowButtonList(&(tools_button_->buttons_)); 
                
//         tools_button_->addButton(new Button("src/img/LineReleased.png", "src/img/LinePressed.png", 
//                                             "src/img/LinePressed.png",  "src/img/LinePressed.png", 
//                                             new ChooseTool(ToolPalette::LINE, &tool_pallette_), 
//                                             Button_Line_size, Button_Line_pos, tools_button_));
        
//         tools_button_->addButton(new Button("src/img/BrushReleased.png", "src/img/BrushPressed.png", 
//                                             "src/img/BrushPressed.png",  "src/img/BrushPressed.png", 
//                                             new ChooseTool(ToolPalette::BRUSH, &tool_pallette_), 
//                                             Button_Brush_size, Button_Brush_pos, tools_button_));
        
//         tools_button_->addButton(new Button("src/img/SquareReleased.png", "src/img/SquarePressed.png", 
//                                             "src/img/SquarePressed.png",  "src/img/SquarePressed.png", 
//                                             new ChooseTool(ToolPalette::SQUARE, &tool_pallette_), 
//                                             Button_Square_size, Button_Square_pos, tools_button_));

//         tools_button_->addButton(new Button("src/img/CircleReleased.png", "src/img/CirclePressed.png", 
//                                             "src/img/CirclePressed.png",  "src/img/CirclePressed.png", 
//                                             new ChooseTool(ToolPalette::CIRCLE, &tool_pallette_), 
//                                             Button_Circle_size, Button_Circle_pos, tools_button_));
        
//         tools_button_->addButton(new Button("src/img/PolylineReleased.png", "src/img/PolylinePressed.png", 
//                                             "src/img/PolylinePressed.png",  "src/img/PolylinePressed.png", 
//                                             new ChooseTool(ToolPalette::POLYLINE, &tool_pallette_), 
//                                             Button_Polyline_size, Button_Polyline_pos, tools_button_));

//         tools_button_->addButton(new Button("src/img/PenReleased.png", "src/img/PenPressed.png", 
//                                             "src/img/PenPressed.png",  "src/img/PenPressed.png", 
//                                             new ChooseTool(ToolPalette::PEN, &tool_pallette_), 
//                                             Button_Pen_size, Button_Pen_pos, tools_button_));

//         tools_button_->addButton(new Button("src/img/EraserReleased.png", "src/img/EraserPressed.png", 
//                                             "src/img/EraserPressed.png",  "src/img/EraserPressed.png", 
//                                             new ChooseTool(ToolPalette::ERASER, &tool_pallette_), 
//                                             Button_Eraser_size, Button_Eraser_pos, tools_button_));
        
//         tools_button_->addButton(new Button("src/img/TextReleased.png", "src/img/TextPressed.png", 
//                                             "src/img/TextPressed.png",  "src/img/TextPressed.png", 
//                                             new ChooseTool(ToolPalette::TEXT, &tool_pallette_), 
//                                             Button_Text_size, Button_Text_pos, tools_button_));

//         size_t size = tools_button_->buttons_.getSize();
//         for (size_t it = 0; it < size; it++)
//             tools_button_->buttons_[it]->state_ = Button::ButtonState::DISABLED;
        
//         widgets_.pushBack(tools_button_);
//     }    

//     {
//         ButtonList *filters_button = new ButtonList("src/img/FilterReleased.png", "src/img/FilterPressed.png", 
//                                                     "src/img/FilterPressed.png", "src/img/FilterPressed.png", 
//                                                     nullptr, Button_Filter_size, Button_Filter_pos, this);

//         filters_button->action_ = new ShowButtonList(&(filters_button->buttons_)); 


// void AppWindow::draw(sf::RenderTarget &target, Container<Transform> &stack_transform)
// {
//     Window::draw(target, stack_transform);
   
//     Transform trf(getLayoutBox().getPosition(), scale_);
//     stack_transform.pushBack(trf.combine(stack_transform.getBack()));

//     canvas_manager_.draw(target, stack_transform);
    
//     size_t size = widgets_.getSize(); 
//     for (size_t it = 0; it < size; it++)
//     {
//         widgets_[it]->draw(target, stack_transform);
//     }

//     colors_.draw(target, stack_transform);
    
//     stack_transform.popBack();

//     return;
// }

// //================================================================================

// bool AppWindow::onMouseMoved(const Vec2d &pos, Container<Transform> &stack_transform)
// {
//     Transform trf(getLayoutBox().getPosition(), scale_);
//     stack_transform.pushBack(trf.combine(stack_transform.getBack()));

//     size_t size = widgets_.getSize(); 
//     for (size_t it = 0; it < size; it++)
//     {
//         widgets_[it]->onMouseMoved(pos, stack_transform);
//     }

//     canvas_manager_.onMouseMoved(pos, stack_transform);
    
//     stack_transform.popBack();

//     return true;
// }

// //================================================================================

// bool AppWindow::onMousePressed(const Vec2d &pos, const MouseKey key, Container<Transform> &stack_transform)
// {
//     Transform trf(getLayoutBox().getPosition(), scale_);
//     stack_transform.pushBack(trf.combine(stack_transform.getBack()));
    
//     Transform last_trf = stack_transform.getBack();
//     Dot local_pos = last_trf.restore(pos);

//     bool flag = checkIn(local_pos);
//     if (flag)
//     {
//         flag = false;

//         if (colors_.onMousePressed(pos, key, stack_transform))
//         {
//             tool_pallette_.setActiveColor(colors_.getActiveColor());
//             flag = true;
//         }

//         size_t size = widgets_.getSize(); 
//         for (size_t it = 0; it < size; it++)
//         {
//             flag = widgets_[it]->onMousePressed(pos, key, stack_transform);
//         }

//         if (!flag) flag |= canvas_manager_.onMousePressed(pos, key, stack_transform);   
//     }

//     stack_transform.popBack();

//     return flag;
// }

// //================================================================================

// bool AppWindow::onMouseReleased(const Vec2d &pos, const MouseKey key, Container<Transform> &stack_transform)
// {
//     Transform trf(getLayoutBox().getPosition(), scale_);
//     stack_transform.pushBack(trf.combine(stack_transform.getBack()));

//     size_t size = widgets_.getSize(); 
//     for (size_t it = 0; it < size; it++)
//     {
//         widgets_[it]->onMouseReleased(pos, key, stack_transform);
//     }
//     canvas_manager_.onMouseReleased(pos, key, stack_transform);

//     stack_transform.popBack();
//     return true;
// }

// //================================================================================

// bool AppWindow::onKeyboardPressed(const KeyboardKey key)
// {
//     if (isAltPressed(key))
//     {
//         return switchTool(key);
//     }
//     return canvas_manager_.onKeyboardPressed(key);;
// }

// //================================================================================

// bool AppWindow::switchTool(const KeyboardKey key)
// {
//     switch (getKeyCode(key))
//     {
//         case Hot_key_brush:
//             tool_pallette_.setActiveTool(ToolPalette::BRUSH);
//             break;

//         case Hot_key_line:
//             tool_pallette_.setActiveTool(ToolPalette::LINE);
//             break;

//         case Hot_key_circle:
//             tool_pallette_.setActiveTool(ToolPalette::CIRCLE);
//             break;

//         case Hot_key_square:
//             tool_pallette_.setActiveTool(ToolPalette::SQUARE);
//             break;

//         case Hot_key_polyline:
//             tool_pallette_.setActiveTool(ToolPalette::POLYLINE);
//             break;
        
//         case Hot_key_eraser:
//             tool_pallette_.setActiveTool(ToolPalette::ERASER);
//             break;

//         case Hot_key_pen:
//             tool_pallette_.setActiveTool(ToolPalette::PEN);
//             break;

//         case Hot_key_text:
//             tool_pallette_.setActiveTool(ToolPalette::TEXT);
//             break;
        
//         default:
//             return false;
//     }

//     return true;
// }

// //================================================================================

// bool AppWindow::onKeyboardReleased(const KeyboardKey key)
// {
//     return canvas_manager_.onKeyboardReleased(key);
// }

// //================================================================================

// bool AppWindow::onTick(const float delta_time)
// {
//     size_t size = widgets_.getSize(); 
//     for (size_t it = 0; it < size; it++)
//     {
//         widgets_[it]->onTick(delta_time);
//     }
    
//     canvas_manager_.onTick(delta_time);
//     return false;
// }

void useApp()
{
    sf::RenderWindow window(sf::VideoMode((size_t)App_width, (size_t)App_height), "- _ -");

    SfmlRenderTarget plug_window(window);
    
    BaseLayoutBox base(Vec2d(0, 0), Vec2d(App_width, App_height), Vec2d(1, 1), false, false);
    Widget base_widget(base);

    Frame frame(getPlugTexture("src/img/frame.png"),
                 Title(Vec2d(App_width / 2 - 10 * plug::Symbol_width, 5), "photostore", 1.9, plug::Color(0, 0, 0, 255)),
                 BaseLayoutBox(Vec2d(0, 0), Vec2d(App_width, App_height), base.getSize(), true, true), &base_widget);


    bool close_window_flag = false;
    Button *close_button = new Button(  getPlugTexture("src/img/closeReleased.png"), getPlugTexture("src/img/closePressed.png"),
                                        getPlugTexture("src/img/closeReleased.png"), getPlugTexture("src/img/closePressed.png"), 
                                        BaseLayoutBox(Vec2d(App_width - 25.0, 0), Vec2d(25.0, 25.0), base.getSize(), false, true),
                                        new Click(close_window_flag));
 

    CanvasManager *manager = new CanvasManager(BaseLayoutBox(Vec2d(5, 50), Vec2d(App_width - 10, App_height - 55), base.getSize(), true, true));
    manager->createCanvas(nullptr);
    manager->createCanvas("src/img/pika.png");

    frame.addWidget(close_button);
    frame.addWidget(manager);

    TransformStack stack;
    plug::EHC context = {(plug::TransformStack&)stack, false, false};

    context.stack.enter(Transform(Vec2d(0.0, 0.0), Vec2d(1.0, 1.0)));

    frame.onParentUpdate(base);
    while (window.isOpen())
    {   
        plug_window.clear(plug::Color(0, 0, 0));

        sf::Event event;

        context.overlapped = false;
        context.stopped = false;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

    
            sf::Mouse mouse;
            Vec2d mouse_pos(mouse.getPosition(window).x, mouse.getPosition(window).y);
            runEvent(event, context, mouse_pos, frame);

            if (close_window_flag)
                window.close();
        }

        frame.draw(context.stack, plug_window);
        window.display();
    }
}


static void runEvent(sf::Event &event, plug::EHC &context, Vec2d mouse_pos, plug::Widget &widget)
{
    static bool shift = false;
    static bool ctrl  = false;
    static bool alt   = false;
    
    defineModifierKey(event, shift, ctrl, alt);    

    if (event.type == sf::Event::MouseMoved)
    {   
        widget.onEvent( plug::MouseMoveEvent(mouse_pos, shift, ctrl, alt), 
                        context);
    }
    else if (event.type == sf::Event::MouseButtonPressed)
    {
        widget.onEvent( plug::MousePressedEvent(static_cast<plug::MouseButton>(event.mouseButton.button), 
                        mouse_pos, shift, ctrl, alt), 
                        context);
    }
    else if (event.type == sf::Event::MouseButtonReleased)
    {
        widget.onEvent( plug::MouseReleasedEvent(static_cast<plug::MouseButton>(event.mouseButton.button), 
                        mouse_pos, shift, ctrl, alt), 
                        context);
    }   
    else if (event.type == sf::Event::KeyReleased)
    {
        widget.onEvent( plug::KeyboardReleasedEvent(static_cast<plug::KeyCode>(event.key.code), 
                        shift, ctrl, alt), 
                        context);
    }
    else if (event.type == sf::Event::KeyPressed)
    {
        widget.onEvent( plug::KeyboardPressedEvent(static_cast<plug::KeyCode>(event.key.code), 
                        shift, ctrl, alt), 
                        context);
    }

    {
        static sf::Clock timer;

        widget.onEvent(plug::TickEvent(timer.getElapsedTime().asSeconds()), context);

        timer.restart();
    }
}

static void defineModifierKey(  sf::Event &event, 
                                bool &shift, bool &ctrl, bool &alt)
{
    if (event.key.code == sf::Keyboard::RShift || event.key.code == sf::Keyboard::LShift)
    {
        shift = (event.type == sf::Event::KeyPressed);
    }
    
    if (event.key.code == sf::Keyboard::RControl || event.key.code == sf::Keyboard::LControl)
    {
        ctrl = (event.type == sf::Event::KeyPressed);
    }

    if (event.key.code == sf::Keyboard::RAlt || event.key.code == sf::Keyboard::LAlt)
    {
        alt = (event.type == sf::Event::KeyPressed);
    }  
}