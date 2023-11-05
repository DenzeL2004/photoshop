#include <stdio.h>

#include "src/widgets/widget/widget.h"
#include "src/widgets/window/window.h"
#include "src/widgets/button/button.h"


const double WIDTH = 1600.0; 
const double HIEGHT = 900.0;

int main()
{
     #ifdef USE_LOG
        if (OpenLogsFile())
            return OPEN_FILE_LOG_ERR;
    #endif

    sf::RenderWindow window(sf::VideoMode((uint32_t)WIDTH, (uint32_t)HIEGHT), "window manager");

    bool ans = 0;
    Button *button = new Button("src/img/closePressed.png", "src/img/closeReleased.png", 
                                "src/img/closeReleased.png", "src/img/closeReleased.png", 
                                new Click(&ans), {20, 20}, {100, 100}, {10, 10}); 

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
            eventAdapter(*button, mouse.getPosition(window).x, mouse.getPosition(window).y, event, stack);

            if (ans)
                window.close();
        }

        button->draw(window, stack);
        ans = false;
    
        window.display();
    }
    
    #ifdef USE_LOG
        if (CloseLogsFile ())
            return OPEN_FILE_LOG_ERR;
    #endif

    return EXIT_SUCCESS;
}