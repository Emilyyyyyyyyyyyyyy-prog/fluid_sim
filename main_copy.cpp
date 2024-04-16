#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <cmath>
#include <windows.h>
#include "Vector2.h"

template <typename T> int sign(T val) {
    return (T(0) < val) - (val < T(0));
}
namespace vessel {
    const int width = 500;
    const int height = 500;
}
double gravity = 9.81;
Vector2<double> velosity(0, 0);
Vector2<double> position(vessel::width / 2, vessel::height / 2);
Vector2<double> Vdown(0, 1);


int main()
{
    //текст
    sf::Font font;
    if (!font.loadFromFile("Fonts/GOST type A Standard.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return -1;
    }

    //создаём окно
    sf::RenderWindow window(sf::VideoMode(vessel::width, vessel::height), "Fluid Model!");
    window.setPosition(sf::Vector2i(10, 50));

    //отрисовка частицы
    sf::CircleShape shape(30);
    shape.setPosition(position.x, position.y);
    shape.setFillColor(sf::Color(51, 102, 204));

    //создаём окно настроек
    sf::RenderWindow settings(sf::VideoMode(800, 200), "Settings!");
    settings.setPosition(sf::Vector2i(window.getPosition().x + window.getSize().x, window.getPosition().y));

    //кнопка
    sf::CircleShape buttonRun(10, 3);
    buttonRun.setFillColor(sf::Color::Green);
    buttonRun.setPosition(30, 10);
    buttonRun.setRotation(90);

    sf::RectangleShape buttonStop(sf::Vector2f(18, 18));
    buttonStop.setFillColor(sf::Color::Red);
    buttonStop.setPosition(45, 10);

    //поля ввода
    sf::RectangleShape rect1(sf::Vector2f(500, 20));
    rect1.setPosition(100, 45);
    rect1.setFillColor(sf::Color(31, 31, 31));
    //ввод текста
    sf::Text inputText1;
    inputText1.setFont(font);
    inputText1.setString("10");
    inputText1.setCharacterSize(20);
    inputText1.setFillColor(sf::Color::White);
    inputText1.setPosition(105, 42);
    bool textEntered1 = false;

    sf::Text label1;
    label1.setFont(font);
    label1.setString("Gravity");
    label1.setCharacterSize(20);
    label1.setFillColor(sf::Color::White);
    label1.setPosition(15, 42);

    sf::RectangleShape line(sf::Vector2f(settings.getSize().x-5, 5));
    line.setPosition(5, 35);
    //подключаем время
    sf::Clock clock;

    bool flag = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (settings.pollEvent(event)) {
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    if (event.text.unicode == '\b' && !inputText1.getString().isEmpty()) {
                        std::string inputString = inputText1.getString();
                        inputString.erase(inputString.size() - 1, 1);
                        inputText1.setString(inputString);
                    }
                    else if (event.text.unicode != '\b') {
                        std::string inputString = inputText1.getString();
                        inputString += static_cast<char>(event.text.unicode);
                        inputText1.setString(inputString);
                    }
                }

            }
            /*else if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Enter) {
                    std::string inputString = inputText.getString();
                    inputString += '\n';
                    inputText.setString(inputString);
                    std::cout << "Enter" << std::endl;
                }*/

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left &&
                    buttonRun.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    flag = true;
                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    buttonStop.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    flag = false;
                }
            }
        }

        settings.clear(sf::Color(51, 51, 51));
        settings.draw(buttonRun);
        settings.draw(buttonStop);
        settings.draw(line);
        settings.draw(rect1);
        settings.draw(inputText1);
        settings.draw(label1);
        settings.display();

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (flag) {
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
            if (position.x > vessel::width - 2 * shape.getRadius()) {
                position.x = vessel::width - 2 * shape.getRadius();
                velosity *= -1;
            }
            if (position.y > vessel::height - 2 * shape.getRadius()) {
                position.y = vessel::height - 2 * shape.getRadius();
                velosity *= -1;
            }
        }

        shape.setPosition(position.x, position.y);
        window.clear();
        window.draw(shape);
        window.display();
        settings.setPosition(sf::Vector2i(window.getPosition().x + window.getSize().x, window.getPosition().y));
        Sleep(2);
    }

    return 0;
}
