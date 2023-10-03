#include <stdio.h>

#include "src/widget/window/window.h"

int main()
{
     #ifdef USE_LOG
        if (OpenLogsFile()) 
            return OPEN_FILE_LOG_ERR;
    #endif

    sf::RenderWindow window(sf::VideoMode(Default_window_width, Default_window_height), "");
    Window photoshop_window("src/img/square.png", Dot(20.0, 20.0), 1.0, 1.0);

    StackTransform stack;
    stack.AddTransform(Transform(Dot(30.0, 30.0), 10.0, 10.0));

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