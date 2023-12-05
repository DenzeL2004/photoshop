#include "App.h"



static void runEvent(sf::Event &event, plug::EHC &context, Vec2d mouse_pos, plug::Widget &widget);

static void defineModifierKey(sf::Event &event, bool &shift, bool &ctrl, bool &alt);

AppWidget::AppWidget():
                    ContainerWidget(BaseLayoutBox(Background_window_pos, Background_window_size, plug::Vec2d(Window_width, Window_height), false, false)), 
                    m_filter_palette(),
                    m_color_palette(),
                    m_canvas_manager_id(0)
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

    m_widgets.pushBack( new Window( getPlugTexture(Config_bar_texture), 
                                    Title(),
                                    BaseLayoutBox(Config_bar_pos, 
                                                  Config_bar_size, 
                                                  box.getSize(), 
                                                  true, true)));

    ButtonList *file_button = new ButtonList(getPlugTexture(Menu_file_released), getPlugTexture(Menu_file_pressed), 
                                             getPlugTexture(Menu_file_pressed),  getPlugTexture(Menu_file_pressed), 
                                             BaseLayoutBox(File_button_pos, File_button_size, box.getSize(), false, false));

    file_button->addButton(new TextButton(  getPlugTexture(Menu_file_open_released), getPlugTexture(Menu_file_open_pressed), 
                                            getPlugTexture(Menu_file_open_released), getPlugTexture(Empty_texture), 
                                            Title(Menu_title_pos, "Open", Menu_button_scale, Menu_button_color), 
                                            Title(Menu_title_pos, "Open", Menu_button_scale, Menu_button_color),
                                            BaseLayoutBox(File_button_open_pos, File_button_open_size, file_button->getLayoutBox().getSize(), false, false), 
                                            new LoadImage(*this)));
   
    file_button->addButton(new TextButton(  getPlugTexture(Menu_file_open_released), getPlugTexture(Menu_file_open_pressed), 
                                            getPlugTexture(Menu_file_open_released), getPlugTexture(Empty_texture),
                                            Title(Menu_title_pos, "New", Menu_button_scale, Menu_button_color), 
                                            Title(Menu_title_pos, "New", Menu_button_scale, Menu_button_color),
                                            BaseLayoutBox(File_button_new_pos, File_button_open_size, file_button->getLayoutBox().getSize(), false, false), 
                                            new AddNewCanvas(*this)));

    m_widgets.pushBack(file_button);

    CanvasManager* manager = new CanvasManager(BaseLayoutBox(Canvase_manager_pos, Canvase_manager_size, box.getSize(), false, false));

    m_widgets.pushBack(manager);
    m_canvas_manager_id = m_widgets.getSize() - 1;
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

    context.stopped = false;

    int size = static_cast<int>(m_widgets.getSize());
    for (int it = size - 1; it >= 0; it--)
    {
        m_widgets[it]->onEvent(event, context);   
    }

    if (!context.stopped)
    {
        Widget::onEvent(event, context);
    }

    context.stack.leave();
}

void AppWidget::createNewCanvas(const char *file_path)
{
    CanvasManager *manager = static_cast<CanvasManager*>(m_widgets[m_canvas_manager_id]);
    manager->createCanvas(m_filter_palette, m_color_palette, file_path);
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
