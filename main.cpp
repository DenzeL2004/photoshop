#include <stdio.h>

#include "src/widgets/widget/widget.h"
#include "src/widgets/window/window.h"
#include "src/widgets/button/button.h"
#include "src/widgets/decorator/decorator.h"
#include "src/widgets/window/canvas.h"


const double WIDTH = 1600.0; 
const double HEIGHT = 900.0;

int main()
{
     #ifdef USE_LOG
        if (OpenLogsFile())
            return OPEN_FILE_LOG_ERR;
    #endif

    sf::RenderWindow window(sf::VideoMode((uint32_t)WIDTH, (uint32_t)HEIGHT), "window manager");

    bool ans = 0;

    BaseLayoutBox base({0.0, 00.0}, {WIDTH, HEIGHT}, {WIDTH, HEIGHT} , false, false);

    Frame* frame = new Frame("src/img/frame.png", Title({10, 5}, "window", sf::Color::Black), 
                            {730, 540.0}, {10.0, 10.0}, nullptr, {WIDTH, HEIGHT});

    Tool tools(Tool::Brash, sf::Color::Cyan, 15);

    Button *button = new Button("src/img/closePressed.png", "src/img/closeReleased.png", 
                                "src/img/closeReleased.png", "src/img/closeReleased.png", 
                                new Click(&ans), {25, 25}, {705, 0.0}, frame); 


    Canvas *canvas = new Canvas(&tools, {2000, 2000.0}, {680, 470.0}, {10.0, 60.0}, frame);

    Scrollbar *scroll_ver = new Scrollbar(canvas, Scrollbar::Type::VERTICAL, 
                                         {20, 470.0}, {695.0, 60.0}, frame);
   
    Button *up_btn = new Button("src/img/arrowUpReleased.png", "src/img/arrowUpPressed.png", 
                                "src/img/arrowUpReleased.png", "src/img/arrowUpPressed.png", 
                                new ScrollCanvas(Dot(0.0, -5.0), canvas), 
                                {20, 20.0}, {0.0, 0.0}, scroll_ver);

    Button *down_btn = new Button("src/img/arrowUpReleased.png", "src/img/arrowUpPressed.png", 
                                  "src/img/arrowUpReleased.png", "src/img/arrowUpPressed.png", 
                                  new ScrollCanvas(Dot(0.0, 5.0), canvas), 
                                  {20, 20.0}, {0.0, 450.0}, scroll_ver);

    Button *ver_btn = new Button("src/img/arrowUpReleased.png", "src/img/arrowUpPressed.png", 
                                  "src/img/arrowUpReleased.png", "src/img/arrowUpPressed.png", 
                                  new ScrollCanvas(Dot(0.0, 1.0), canvas), 
                                  {20, 20.0}, {0.0, 210.0}, scroll_ver);

    Scrollbar *scroll_hor = new Scrollbar(canvas, Scrollbar::Type::HORIZONTAL, 
                                         {680, 20.0}, {10, 30.0}, frame);
   
    Button *left_btn = new Button("src/img/arrowUpReleased.png", "src/img/arrowUpPressed.png", 
                                "src/img/arrowUpReleased.png", "src/img/arrowUpPressed.png", 
                                new ScrollCanvas(Dot(-5.0, 0.0), canvas), 
                                {20, 20.0}, {0.0, 0.0}, scroll_hor);

    Button *right_btn = new Button("src/img/arrowUpReleased.png", "src/img/arrowUpPressed.png", 
                                  "src/img/arrowUpReleased.png", "src/img/arrowUpPressed.png", 
                                  new ScrollCanvas(Dot(5.0, 0.0), canvas), 
                                  {20, 20.0}, {660.0, 0.0}, scroll_hor);

    Button *hor_btn = new Button("src/img/arrowUpReleased.png", "src/img/arrowUpPressed.png", 
                                  "src/img/arrowUpReleased.png", "src/img/arrowUpPressed.png", 
                                  new ScrollCanvas(Dot(0.0, 1.0), canvas), 
                                  {20, 20.0}, {0.0, 0.0}, scroll_hor);

    scroll_hor->addButtons(left_btn, right_btn, hor_btn);
    scroll_ver->addButtons(up_btn, down_btn, ver_btn);

    frame->addWidget(button);
    frame->addWidget(scroll_hor);
    frame->addWidget(scroll_ver);
    frame->addWidget(canvas);

    Container<Transform> stack;
    stack.pushBack(Transform({0.0, 0.0}, {1, 1}));

    frame->onUpdate(base);

    while (window.isOpen())
    {   
        window.clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            sf::Mouse mouse;
            eventAdapter(*frame, mouse.getPosition(window).x, mouse.getPosition(window).y, event, stack);

            if (ans)
                window.close();
        }

        frame->draw(window, stack);
        ans = false;
    
        window.display();
    }
    
    #ifdef USE_LOG
        if (CloseLogsFile ())
            return OPEN_FILE_LOG_ERR;
    #endif

    return EXIT_SUCCESS;
}