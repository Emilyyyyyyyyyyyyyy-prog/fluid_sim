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
//Vector2<double> velosity(0, 0);
//Vector2<double> position(geo::width / 2, geo::height / 2);
Vector2<double> Vdown(0, 1);

int n = 5;
std::vector<Vector2<double>> positions(n);
std::vector<Vector2<double>> velocities(n);

int main()
{
    sf::RenderWindow window(sf::VideoMode(geo::width, geo::height), "Fluid Model!");
    std::vector<sf::CircleShape> shapes(n);
    for (unsigned int i = 0; i < positions.size(); i++) {
        positions[i] = Vector2<double>(geo::width / 2 + i * 30, geo::height / 2);
        velocities[i] = Vector2<double>(0, 0);
        shapes[i] = sf::CircleShape(30);
        shapes[i].setPosition(positions[i].x, positions[i].y);
        shapes[i].setFillColor(sf::Color(51, 102, 204));
    }
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
        window.clear();
        for (unsigned int i = 0; i < positions.size(); i++) {
            velocities[i] += Vdown * gravity * time;
            positions[i] += velocities[i] * time;
       
            if (positions[i].x < 0) {
                positions[i].x = 0;
                velocities[i] *= -1;
            }
            if (positions[i].y < 0) {
                positions[i].y = 0;
                velocities[i] *= -1;
            }
            if (positions[i].x > geo::width - 2 * shapes[i].getRadius()) {
                positions[i].x = geo::width - 2 * shapes[i].getRadius();
                velocities[i] *= -1;
            }
            if (positions[i].y > geo::height - 2 * shapes[i].getRadius()) {
                positions[i].y = geo::height - 2 * shapes[i].getRadius();
                velocities[i] *= -1;
            }

            shapes[i].setPosition(positions[i].x, positions[i].y);
            window.draw(shapes[i]);
        }
        window.display();
        Sleep(2);
    }

    return 0;
}
