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
Vector2<double> Vdown(0, 1);
Vector2<double> Vup(0, -1);
Vector2<double> Vright(1, 0);
Vector2<double> Vleft(-1, 0);
Vector2<double> Vzero(0, 0);


int n = 30, num_particles = 2, start_radius = 8;
float smoothing_radius = 25;
float PI = 10;

const float mass = 0.15;

std::vector<Vector2<double>> positions(n);
std::vector<Vector2<double>> velocities(n);
std::vector<float> particle_properties(num_particles);
std::vector<float> densities(num_particles);

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

static float smoothing_kernel(float radius, float dst) {
    float volume = PI * pow(radius, 8) / 4;
    float value = (0 < radius * radius - dst * dst) ? radius * radius - dst * dst : 0;
    return value * value * value / volume;
}

static float smoothing_kernel_derivative(float dst, float radius) {
    if (dst >= radius) return 0;
    float f = radius * radius - dst * dst;
    float scale = -24 / (PI * pow(radius, 8));
    return scale * dst * f * f;
}

float calculate_density(Vector2<double> sample_point) {
    float density = 0;

    for (auto pos : positions) {
        Vector2<double> d = pos - sample_point;
        float dst = sqrt(d.x * d.x + d.y * d.y);
        float influence = smoothing_kernel(smoothing_radius, dst);
        density += mass * influence;
    }

    return density;
}

float example_function(Vector2<double> pos) {
    return cos(pos.y - 3 * sin(pos.x));
}

void create_particles(int seed) {
    int rng = rand() % (seed + 1);
    std::vector<Vector2<double>> create_positions(num_particles);

    for (unsigned int i = 0; i < create_positions.size(); i++) {
        float x = (float)(rand() / RAND_MAX - 0.5) * geo::width;
        float y = (float)(rand() / RAND_MAX - 0.5) * geo::height;
        create_positions[i] = Vector2<double>(x, y);
        particle_properties[i] = example_function(create_positions[i]);
    }
}

float calculate_property(Vector2<double> sample_point) {
    float property = 0;
    for (int i = 0; i < num_particles; i++) {
        Vector2<double> d = positions[i] - sample_point;
        float dst = sqrt(d.x * d.x + d.y + d.y);
        float influence = smoothing_kernel(dst, smoothing_radius);
        float density = calculate_density(positions[i]);
        property += particle_properties[i] * influence * mass / density;
    }
    return property;
}

Vector2<double> calculate_property_gradient(Vector2<double> sample_point) {
    Vector2<double> property_gradient = Vzero;

    for (int i = 0; i < num_particles; i++) {
        Vector2<double> d = positions[i] - sample_point;
        float dst = sqrt(d.x * d.x + d.y * d.y);
        Vector2<double> dir = (positions[i] - sample_point) / dst;
        float influence = smoothing_kernel_derivative(dst, smoothing_radius);
        float density = densities[i];
        property_gradient += dir * (-1) * particle_properties[i] * influence * mass / density;
    }
    return property_gradient;
}

void update_densities() {
    for (int i = 0; i < num_particles; i++) {
        densities[i] = calculate_density(positions[i]);
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(geo::width, geo::height), "Fluid Model!");
    std::vector<sf::CircleShape> shapes(n);
    for (unsigned int i = 0; i < positions.size(); i++) {
        positions[i] = Vector2<double>(geo::width / 2, geo::height / 2 - i * start_radius / 2);
        velocities[i] = Vector2<double>(0, 0);
        shapes[i] = sf::CircleShape(start_radius);
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
