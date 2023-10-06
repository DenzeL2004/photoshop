#include <stdio.h>

#include "src/widget/window/window.h"

int main()
{
     #ifdef USE_LOG
        if (OpenLogsFile()) 
            return OPEN_FILE_LOG_ERR;
    #endif

    sf::RenderWindow window(sf::VideoMode(800, 600), "");
    Window photoshop_window("src/img/square.png", Dot(0.0, 0.0), 0.5, 0.5);

    Container<Transform> stack;
    stack.PushBack(Transform({0.0, 0.0}, {800.0, 600.0}));

    while (window.isOpen())
    {   
        window.clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        photoshop_window.Draw(window, stack);


        window.display();
    }
    
    #ifdef USE_LOG
        if (CloseLogsFile ())
            return OPEN_FILE_LOG_ERR;
    #endif

    return EXIT_SUCCESS;
}