#include <stdio.h>

#include "src/widgets/widget/widget.h"
#include "src/widgets/window/window.h"
#include "src/widgets/button/button.h"
#include "src/widgets/decorator/decorator.h"


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

    // Window* win = new Window("src/img/frame.png", 
    //                          {1600, 900.0}, {WIDTH, HEIGHT}, {0.0, 0.0}, nullptr);

    Frame* frame = new Frame("src/img/frame.png", Title({10, 5}, "window", sf::Color::Black), 
                            {720, 540.0}, {WIDTH, HEIGHT}, {10.0, 10.0}, nullptr);

    Window* win = new Window("src/img/YellowReleased.png", 
                            {680, 500.0}, {720, 540}, {10.0, 30.0}, nullptr);

    Button *button = new Button("src/img/closePressed.png", "src/img/closeReleased.png", 
                                "src/img/closeReleased.png", "src/img/closeReleased.png", 
                                new Click(&ans), {25, 25}, {720, 540.0}, {695, 0.0}, frame); 

    frame->addWidget(button);
    frame->addWidget(win);


    Container<Transform> stack;
    stack.pushBack(Transform({0.0, 0.0}, {1, 1}));

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