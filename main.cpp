#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include <cmath>
#include <windows.h>

template <typename T> int sign(T val) {
    return (T(0) < val) - (val < T(0));
}
namespace geo {
    const int width = 500;
    const int height = 500;
}
double gravity = 9.81;
Vector2<double> velosity(0, 0);
Vector2<double> position(geo::width / 2, geo::height / 2);
Vector2<double> Vdown(0, 1);

int main()
{
    sf::RenderWindow window(sf::VideoMode(geo::width, geo::height), "Fluid Model!");
    sf::CircleShape shape(30);
    shape.setPosition(position.x, position.y);
    shape.setFillColor(sf::Color(51, 102, 204));
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        double time = clock.getElapsedTime().asSeconds() / 100;
        velosity += Vdown * gravity * time;
        position += velosity * time;

        if (position.x < 0) {
            position.x = 0;
            velosity *= -1;
        }
        if (position.y < 0) {
            position.y = 0;
            velosity *= -1;
        }
        if (position.x > geo::width-2*shape.getRadius()) {
            position.x = geo::width- 2 * shape.getRadius();
            velosity *= -1;
        }
        if (position.y > geo::height- 2 * shape.getRadius()) {
            position.y = geo::height - 2 * shape.getRadius();
            velosity *= -1;
        }

        shape.setPosition(position.x, position.y);
        window.clear();
        window.draw(shape);
        window.display();
        Sleep(2);
    }

    return 0;
}
