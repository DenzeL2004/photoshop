#include "App.h"

static void runEvent(sf::Event &event, plug::EHC &context, Vec2d mouse_pos, plug::Widget &widget);

static void defineModifierKey(sf::Event &event, bool &shift, bool &ctrl, bool &alt);

AppWidget::AppWidget():
                    ContainerWidget(BaseLayoutBox(Background_window_pos, Background_window_size, plug::Vec2d(Window_width, Window_height), false, false)), 
                    m_plugin_list(),
                    m_filter_palette(),
                    m_color_palette(),
                    m_tool_palette(),
                    m_canvas_manager_id(0)
{
    plug::LayoutBox &box = getLayoutBox();
    m_color_palette.setBGColor(plug::White);
    m_color_palette.setFGColor(plug::Black);

    loadePlugins(m_plugin_list);

    m_filter_palette.loadPlugins(m_plugin_list);
    m_tool_palette.loadPlugins(m_plugin_list);

    m_widgets.pushBack( new Window( getPlugTexture(Background_window_texture), 
                                    Title(),
                                    BaseLayoutBox(Background_window_pos, Background_window_size, box.getSize(), true, true)));

    m_widgets.pushBack( new Window( getPlugTexture(Config_bar_texture), 
                                    Title(),
                                    BaseLayoutBox(Config_bar_pos, Config_bar_size, box.getSize(), true, true)));

    m_widgets.pushBack( new Window( getPlugTexture(Tool_bar_texture), 
                                    Title(),
                                    BaseLayoutBox(Tool_bar_pos, Tool_bar_size, box.getSize(), true, true)));

    AddToolsButtons();
    AddFileButtons();
    AddFiltersButtons();
    
    m_widgets.pushBack(new Clock(Menu_button_color, 2.6, BaseLayoutBox(plug::Vec2d(Config_bar_size.x - 150, Config_bar_size.y - 10), Menu_button_size, box.getSize(), false, true)));
    m_widgets.pushBack(new ColorField(Color_field_pos, Vec2d(0.5, 0.5), m_color_palette));

    m_widgets.pushBack(new ColorView(m_color_palette, BaseLayoutBox(Color_field_pos + plug::Vec2d(0, 300), plug::Vec2d(75, 75), box.getSize(), false, false)));


    CanvasManager* manager = new CanvasManager(BaseLayoutBox(Canvase_manager_pos, Canvase_manager_size, box.getSize(), false, false));

    m_widgets.pushBack(manager);
    m_canvas_manager_id = m_widgets.getSize() - 1;
}

void AppWidget::AddFiltersButtons(void)
{
    ButtonList *filters_button = new ButtonList(getPlugTexture(Menu_filter_released), getPlugTexture(Menu_filter_pressed), 
                                                getPlugTexture(Menu_filter_pressed),  getPlugTexture(Menu_filter_pressed), 
                                                BaseLayoutBox(Filter_button_pos, Filter_button_size, this->getLayoutBox().getSize(), false, false));    
    
    size_t cnt_filters = m_filter_palette.getSize();
    for (size_t it = 0; it < cnt_filters; it++)
    {
        plug::Filter *filter = m_filter_palette.getFilter(it);

        const char* filter_name = filter->getPluginData()->getName();
        plug::Vec2d button_pos = plug::Vec2d(0, Filter_button_size.y + Menu_list_size.y * it);

        filters_button->addButton(new TextButton(getPlugTexture(Menu_file_open_released), getPlugTexture(Menu_file_open_pressed), 
                                                 getPlugTexture(Menu_file_open_released), getPlugTexture(Empty_texture),
                                                 Title(Menu_title_pos, filter_name, Menu_button_scale, Menu_button_color), 
                                                 Title(Menu_title_pos, filter_name, Menu_button_scale, Menu_button_color),
                                                 BaseLayoutBox(button_pos, Menu_list_size, filters_button->getLayoutBox().getSize(), false, false), 
                                                 new ApplyFilter(*this, it)));       

        filter->release();
    }

    m_widgets.pushBack(filters_button);
}

void AppWidget::AddToolsButtons(void)
{
    ContainerWidget *tool_buttons = new ContainerWidget(BaseLayoutBox(Tool_bar_pos, Tool_bar_pos, getLayoutBox().getSize(), false, false));

    const size_t cnt_on_line = 3;

    size_t cnt_tools = m_tool_palette.getSize();
    for (size_t it = 0; it < cnt_tools; it++)
    {
        plug::Tool *tool = m_tool_palette.getTool(it);

        const char* tool_name = tool->getPluginData()->getName();
        const char* tool_texture = tool->getPluginData()->getTexturePath();

        plug::Vec2d button_pos = Vec2d(5, 50) + plug::Vec2d(Tool_button_size.x * (it % cnt_on_line), Tool_button_size.y * (it / cnt_on_line));

        tool_buttons->insertWidget(new ColorButton( getPlugTexture(tool_texture), plug::White,
                                                    Released_tool_color, Pressed_tool_color,
                                                    BaseLayoutBox(button_pos, Tool_button_size, tool_buttons->getLayoutBox().getSize(), false, false), 
                                                    new ChooseToolAction(*this, it)));       

        tool->release();
    }

    m_widgets.pushBack(tool_buttons);    
}

void AppWidget::AddFileButtons(void)
{
    ButtonList *file_button = new ButtonList(getPlugTexture(Menu_file_released), getPlugTexture(Menu_file_pressed), 
                                             getPlugTexture(Menu_file_pressed),  getPlugTexture(Menu_file_pressed), 
                                             BaseLayoutBox(File_button_pos, File_button_size, this->getLayoutBox().getSize(), false, false));

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
    manager->createCanvas(m_tool_palette, m_filter_palette, m_color_palette, file_path);
}


void AppWidget::onKeyboardPressed(const plug::KeyboardPressedEvent &event, plug::EHC &context)
{
    if (event.ctrl)
    {
        if (event.key_id == plug::KeyCode::F)
        {
            onEvent(plug::FilterApplyEvent(FilterPalette::FilterType::LAST), context);
        }
    
        if (event.key_id >= plug::KeyCode::Num0 && event.key_id <= plug::KeyCode::Num9)
        {
            size_t tool_id = static_cast<size_t>(event.key_id) - static_cast<size_t>(plug::KeyCode::Num0);
            onEvent(plug::ToolChooseEvent(tool_id), context);
        }
    }
}

//=========================================================================================

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
