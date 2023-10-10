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

    

    bool close_window = false;
    Button close_button("src/img/CloseResCrossReleased.png", "src/img/CloseResCrossCovered.png",
                        "src/img/CloseResCrossReleased.png", "src/img/CloseResCrossCovered.png", new Click(&close_window),
                        Dot(0.98, 0.0), Vector(0.02, 0.025));

    Window canvas("src/img/canvas.png", {0.005, 0.03}, Vector(0.99, 0.91)); 

    Border border("src/img/border.png", &close_button, Title("window manager", sf::Color::Black), &canvas, Dot(0.0, 0.0), Vector(1.15, 1));

    Container<Transform> stack;
    stack.PushBack(Transform({0.0, 0.0}, {WEIDTH, HIEGHT}));

    while (window.isOpen())
    {   
        window.clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            sf::Mouse mouse;
            EventAdapter(border, mouse.getPosition(window).x, mouse.getPosition(window).y, event, stack);

            if (close_window)
                window.close();
        }

        border.Draw(window, stack);
    
        window.display();
    }
    
    #ifdef USE_LOG
        if (CloseLogsFile ())
            return OPEN_FILE_LOG_ERR;
    #endif

    return EXIT_SUCCESS;
}