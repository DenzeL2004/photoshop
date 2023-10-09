#include <stdio.h>

#include "src/widget/window/window.h"
#include "src/widget/button/button.h"
#include "src/widget/decorator/decorator.h"

const double WEIDTH = 1600.0; 
const double HIEGHT = 1200.0;

int main()
{
     #ifdef USE_LOG
        if (OpenLogsFile()) 
            return OPEN_FILE_LOG_ERR;
    #endif

    sf::RenderWindow window(sf::VideoMode(WEIDTH, HIEGHT), "window manager");

    

    Button close_button("src/img/CloseResCrossReleased.png", "src/img/CloseResCrossCovered.png",
                        "src/img/CloseResCrossCovered.png", "src/img/CloseResCrossCovered.png", new Click(),
                        30.0, 30.0, Dot(1.0, 1.0), Vector(0.5, 0.5));

    Window canvas("src/img/border.png", 40.0, 40.0, Dot(0.5, 0.5), Vector(0.8, 0.8));

    Border border("src/img/border.png", &close_button, Title("border wwwwwwwwwwww", sf::Color::Cyan), &canvas, Dot(0.0, 0.0), Vector(0.5, 0.2));

    Container<Transform> stack;
    stack.PushBack(Transform({0.0, 0.0}, {WEIDTH, HIEGHT}));

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

        // close_button.PassTime(timer.getElapsedTime().asMicroseconds());
        // close_button.OnMouseMoved(event.mouseMove.x, event.mouseMove.y, stack);
        // close_button.Draw(window, stack);        

        border.Draw(window, stack);

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            if (close_button.OnMousePressed(Left, stack))
                printf("true\n");
        }

        window.display();
        timer.restart();
    }
    
    #ifdef USE_LOG
        if (CloseLogsFile ())
            return OPEN_FILE_LOG_ERR;
    #endif

    return EXIT_SUCCESS;
}