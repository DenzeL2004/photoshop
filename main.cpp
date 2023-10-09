#include <stdio.h>

#include "src/widget/window/window.h"
#include "src/widget/button/button.h"

int main()
{
     #ifdef USE_LOG
        if (OpenLogsFile()) 
            return OPEN_FILE_LOG_ERR;
    #endif

    sf::RenderWindow window(sf::VideoMode(1600, 1200), "");
    Button photoshop_window("src/img/CloseResCrossReleased.png", "src/img/CloseResCrossCovered.png",
                            "src/img/CloseResCrossCovered.png", "src/img/CloseResCrossCovered.png", nullptr,
                            Dot(0.0, 0.0), 0.5, 0.5);

    Container<Transform> stack;
    stack.PushBack(Transform({0.0, 0.0}, {1600.0, 1200.0}));

    sf::Clock timer;
    while (window.isOpen())
    {   
        window.clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        photoshop_window.PassTime(timer.getElapsedTime().asMicroseconds());
        sf::Mouse mouse;
        photoshop_window.OnMouseMoved(mouse.getPosition().x, mouse.getPosition().y - 70, stack);
        photoshop_window.Draw(window, stack);


        window.display();
        timer.restart();
    }
    
    #ifdef USE_LOG
        if (CloseLogsFile ())
            return OPEN_FILE_LOG_ERR;
    #endif

    return EXIT_SUCCESS;
}