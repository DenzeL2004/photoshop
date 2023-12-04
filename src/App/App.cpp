#include "App.h"



static void runEvent(sf::Event &event, plug::EHC &context, Vec2d mouse_pos, plug::Widget &widget);

static void defineModifierKey(sf::Event &event, bool &shift, bool &ctrl, bool &alt);

AppWidget::AppWidget():
                    Widget(BaseLayoutBox(Background_window_pos, Background_window_size, plug::Vec2d(Window_width, Window_height), false, false)), 
                    m_widgets(), 
                    m_filter_palette(),
                    m_color_palette()
{
    plug::LayoutBox &box = getLayoutBox();
    m_color_palette.setBGColor(plug::White);
    m_color_palette.setFGColor(plug::Green);

    m_widgets.pushBack( new Window( getPlugTexture(Background_window_texture), 
                                    Title(),
                                    BaseLayoutBox(Background_window_pos, 
                                                  Background_window_size, 
                                                  box.getSize(), 
                                                  true, true)));

    CanvasManager* manager = new CanvasManager(BaseLayoutBox(Canvase_manager_pos, Canvase_manager_size, box.getSize(), false, false));


    manager->createCanvas(m_filter_palette, m_color_palette, nullptr);
    manager->createCanvas(m_filter_palette, m_color_palette, "src/img/pika.png");

    m_widgets.pushBack(manager);

    m_widgets.pushBack(new TextBox(100, 2.0, BaseLayoutBox(Canvase_manager_pos, Canvase_manager_size, box.getSize(), false, true)));

    // widgets_.pushBack(new Button("src/img/NewCanvasReleased.png", "src/img/NewCanvasPressed.png", 
    //                             "src/img/NewCanvasReleased.png", "src/img/NewCanvasPressed.png", 
    //                             new AddCanvase(&canvas_manager_, &tool_pallette_, &filter_pallette_), 
    //                             Button_create_size, Button_create_pos, this));
    
    
    // {
    //     ButtonList *tools_button_ = new ButtonList( "src/img/ToolsReleased.png", "src/img/ToolsPressed.png", 
    //                                                 "src/img/ToolsPressed.png", "src/img/ToolsPressed.png", 
    //                                                 nullptr, Button_Tools_size, Button_Tools_pos , this);

    //     tools_button_->action_ = new ShowButtonList(&(tools_button_->buttons_)); 
                
    //     tools_button_->addButton(new Button("src/img/LineReleased.png", "src/img/LinePressed.png", 
    //                                         "src/img/LinePressed.png",  "src/img/LinePressed.png", 
    //                                         new ChooseTool(ToolPalette::LINE, &tool_pallette_), 
    //                                         Button_Line_size, Button_Line_pos, tools_button_));
        
    //     tools_button_->addButton(new Button("src/img/BrushReleased.png", "src/img/BrushPressed.png", 
    //                                         "src/img/BrushPressed.png",  "src/img/BrushPressed.png", 
    //                                         new ChooseTool(ToolPalette::BRUSH, &tool_pallette_), 
    //                                         Button_Brush_size, Button_Brush_pos, tools_button_));
        
    //     tools_button_->addButton(new Button("src/img/SquareReleased.png", "src/img/SquarePressed.png", 
    //                                         "src/img/SquarePressed.png",  "src/img/SquarePressed.png", 
    //                                         new ChooseTool(ToolPalette::SQUARE, &tool_pallette_), 
    //                                         Button_Square_size, Button_Square_pos, tools_button_));

    //     tools_button_->addButton(new Button("src/img/CircleReleased.png", "src/img/CirclePressed.png", 
    //                                         "src/img/CirclePressed.png",  "src/img/CirclePressed.png", 
    //                                         new ChooseTool(ToolPalette::CIRCLE, &tool_pallette_), 
    //                                         Button_Circle_size, Button_Circle_pos, tools_button_));
        
    //     tools_button_->addButton(new Button("src/img/PolylineReleased.png", "src/img/PolylinePressed.png", 
    //                                         "src/img/PolylinePressed.png",  "src/img/PolylinePressed.png", 
    //                                         new ChooseTool(ToolPalette::POLYLINE, &tool_pallette_), 
    //                                         Button_Polyline_size, Button_Polyline_pos, tools_button_));

    //     tools_button_->addButton(new Button("src/img/PenReleased.png", "src/img/PenPressed.png", 
    //                                         "src/img/PenPressed.png",  "src/img/PenPressed.png", 
    //                                         new ChooseTool(ToolPalette::PEN, &tool_pallette_), 
    //                                         Button_Pen_size, Button_Pen_pos, tools_button_));

    //     tools_button_->addButton(new Button("src/img/EraserReleased.png", "src/img/EraserPressed.png", 
    //                                         "src/img/EraserPressed.png",  "src/img/EraserPressed.png", 
    //                                         new ChooseTool(ToolPalette::ERASER, &tool_pallette_), 
    //                                         Button_Eraser_size, Button_Eraser_pos, tools_button_));
        
    //     tools_button_->addButton(new Button("src/img/TextReleased.png", "src/img/TextPressed.png", 
    //                                         "src/img/TextPressed.png",  "src/img/TextPressed.png", 
    //                                         new ChooseTool(ToolPalette::TEXT, &tool_pallette_), 
    //                                         Button_Text_size, Button_Text_pos, tools_button_));

    //     size_t size = tools_button_->buttons_.getSize();
    //     for (size_t it = 0; it < size; it++)
    //         tools_button_->buttons_[it]->state_ = Button::ButtonState::DISABLED;
        
    //     widgets_.pushBack(tools_button_);
    // }    

    // {
    //     ButtonList *filters_button = new ButtonList("src/img/FilterReleased.png", "src/img/FilterPressed.png", 
    //                                                 "src/img/FilterPressed.png", "src/img/FilterPressed.png", 
    //                                                 nullptr, Button_Filter_size, Button_Filter_pos, this);

    //     filters_button->action_ = new ShowButtonList(&(filters_button->buttons_)); 

    // }

}

void AppWidget::draw(plug::TransformStack &stack, plug::RenderTarget &target)
{
    plug::Transform trf(getLayoutBox().getPosition(), Default_scale);
    stack.enter(trf);

    size_t cnt = m_widgets.getSize();
    for (size_t it = 0; it < cnt; it++)
    {
        m_widgets[it]->draw(stack, target);
    }

    stack.leave();
}

void AppWidget::onEvent(const plug::Event &event, plug::EHC &context)
{
    plug::Transform trf(getLayoutBox().getPosition(), Default_scale);    
    context.stack.enter(trf);

    bool handel_event = false;

    size_t size = m_widgets.getSize();

    for (size_t it = 0; it < size; it++)
    {
        context.stopped = false;
        m_widgets[it]->onEvent(event, context);

        if (context.stopped)
        {
            handel_event = true;
        }
    }

    if (!handel_event)
    {
        Widget::onEvent(event, context);
    }

    context.stopped |= handel_event;

    context.stack.leave();
}

void AppWidget::onParentUpdate(const plug::LayoutBox &parent_box)
{
    plug::LayoutBox *layout_box =  &getLayoutBox();
    layout_box->onParentUpdate(parent_box);
    
    size_t cnt = m_widgets.getSize();
    for (size_t it = 0; it < cnt; it++)
        m_widgets[it]->onParentUpdate(*layout_box);
}

void AppWidget::onMouseMove(const plug::MouseMoveEvent &event, plug::EHC &context)
{
    context.stopped = false;
}

void AppWidget::onMousePressed(const plug::MousePressedEvent &event, plug::EHC &context)
{
    context.stopped = false;
}

void AppWidget::onMouseReleased(const plug::MouseReleasedEvent &event, plug::EHC &context)
{
   
    context.stopped = false;
}

void AppWidget::onKeyboardPressed(const plug::KeyboardPressedEvent &event, plug::EHC &context)
{
    context.stopped = false;
}

void AppWidget::onKeyboardReleased(const plug::KeyboardReleasedEvent &event, plug::EHC &context)
{
    context.stopped = false;
}

void AppWidget::onTick(const plug::TickEvent &event, plug::EHC &context)
{
    context.stopped = false;
} 

void AppWidget::addWidget(Widget* widget)
{
    m_widgets.pushBack(widget);
}

void useApp()
{
    sf::RenderWindow window(sf::VideoMode((size_t)Window_width, (size_t)Window_height), "- _ -");

    SfmlRenderTarget plug_window(window);
    
    BaseLayoutBox base(Vec2d(0, 0), Vec2d(Window_width, Window_height), Vec2d(1, 1), false, false);
    Widget base_widget(base);

    Frame frame(getPlugTexture(App_frame_texture),
                 Title(Vec2d(Window_width / 2 - 10 * plug::Symbol_width, 5), "Photostore", 1.9, plug::White),
                 BaseLayoutBox(Vec2d(0, 0), Vec2d(Window_width, Window_height), base.getSize(), true, true), &base_widget);


    bool close_window_flag = false;
    Button *close_button = new Button(  getPlugTexture(Cross_button_released), getPlugTexture(Cross_button_pressed),
                                        getPlugTexture(Cross_button_released), getPlugTexture(Cross_button_pressed), 
                                        BaseLayoutBox(Vec2d(Window_width - 25.0, 0), Cross_button_size, base.getSize(), false, true),
                                        new Click(close_window_flag));
 

    AppWidget *application = new AppWidget();    

    frame.addWidget(close_button);
    frame.addWidget(application);

    TransformStack stack;
    plug::EHC context = {(plug::TransformStack&)stack, false, false};

    context.stack.enter(Transform(Vec2d(0.0, 0.0), Vec2d(1.0, 1.0)));
    frame.onParentUpdate(base);

   sf::Clock timer;

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
        frame.onEvent(plug::TickEvent(timer.getElapsedTime().asSeconds()), context);

        window.display();

        timer.restart();
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