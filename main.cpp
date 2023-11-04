#include <stdio.h>

#include "src/widgets/widget/widget.h"

const double WIDTH = 1600.0; 
const double HIEGHT = 900.0;

int main()
{
     #ifdef USE_LOG
        if (OpenLogsFile()) 
            return OPEN_FILE_LOG_ERR;
    #endif

    sf::RenderWindow window(sf::VideoMode((uint32_t)WIDTH, (uint32_t)HIEGHT), "window manager");

    Widget *widget = new Widget({100, 75}, {200, 200}, {10, 10}); 

    Container<Transform> stack;
    stack.pushBack(Transform({0.0, 0.0}, {1.0, 1.0}));

    while (window.isOpen())
    {   
        window.clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            sf::Mouse mouse;
            eventAdapter(*widget, mouse.getPosition(window).x, mouse.getPosition(window).y, event, stack);
        }

        widget->draw(window, stack);
    
        window.display();
    }
    
    #ifdef USE_LOG
        if (CloseLogsFile ())
            return OPEN_FILE_LOG_ERR;
    #endif

    return EXIT_SUCCESS;
}