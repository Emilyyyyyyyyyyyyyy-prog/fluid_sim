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

void start() {
    std::vector<Vector2<double>> positions_start(num_particles);
    std::vector<Vector2<double>> velocities_start(num_particles);

    int particle_size = 5, particle_spacing = 10;

    int particles_per_row = (int)sqrt(num_particles);
    int particles_per_col = (num_particles - 1) / particles_per_row + 1;
    float spacing = particle_size * 2 + particle_spacing;

    for (int i = 0; i < num_particles; i++) {
        float x = (i % particles_per_row - particles_per_row / 2 + 0.5) * spacing;
        float y = (i / particles_per_row - particles_per_col / 2 + 0.5) * spacing;
        positions_start[i] = Vector2<double>(x, y);
    }
}

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
