#include <iostream>
#include <complex>
#include <cmath>
#include <sstream>
#include <string>
#include "ComplexPlane.h"
using namespace std;
using namespace sf;

int main()
{
    unsigned int desktop_w = VideoMode::getDesktopMode().width; 
    unsigned int desktop_h = VideoMode::getDesktopMode().height;
    VideoMode vm(desktop_w, desktop_h);
    
    RenderWindow window(vm, "Mandelbrot Set", Style::Default);
    ComplexPlane complexPlane(desktop_w, desktop_h);
    
    Text text;
    Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        cout << "Error loading font file." << endl;
    }
    text.setFont(font);
    text.setCharacterSize(30);
    text.setPosition(desktop_w/17.0f, desktop_h/11.5f);
    text.setFillColor(Color::White);

    while (window.isOpen())
	{
        Event event;
        while (window.pollEvent(event))
		{
            if (event.type == Event::Closed)
            {
                window.close();
            }
            else if (event.type == Event::MouseButtonPressed) // handle mouse clicks
            {
				if (event.mouseButton.button == sf::Mouse::Left) // if left click
				{
					complexPlane.zoomIn();
					complexPlane.setCenter({event.mouseButton.x, event.mouseButton.y});
				}
				else if (event.mouseButton.button == sf::Mouse::Right) //if right click
				{
					complexPlane.zoomOut();
					complexPlane.setCenter({event.mouseButton.x, event.mouseButton.y});
				}
            }
            else if (event.type == Event::MouseMoved) 
            {
				complexPlane.setMouseLocation({event.mouseMove.x, event.mouseMove.y}); 
            }
            else if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
            }
        }
        
        complexPlane.updateRender();
        complexPlane.loadText(text);
        
        window.clear();
        window.draw(complexPlane);
        window.draw(text);
        window.display();
    }

    return 0;
}
