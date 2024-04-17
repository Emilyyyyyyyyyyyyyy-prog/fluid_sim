#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <cmath>
#include <windows.h>
#include <vector>
#include "Vector2.h"

template <typename T> int sign(T val) {
    return (T(0) < val) - (val < T(0));
}

int NumParticles;
double gravity;
double CollisionDamping;
double ParticleSize;
double ParticleSpacing;
double x, y;
double widht = 600, hight = 600;


Vector2<double> velocity(0, 0);
Vector2<double> position(300, 300);
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
    sf::RenderWindow window(sf::VideoMode(widht, hight), "Fluid Model!", sf::Style::Fullscreen);

    //создаём реакционный сосуд
    sf::RectangleShape vessel(sf::Vector2f(x, y));
    vessel.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    vessel.setFillColor(sf::Color::Black);
    vessel.setOutlineThickness(1);
    vessel.setOutlineColor(sf::Color::Green);

    position.x = window.getSize().x / 2;
    position.y = window.getSize().y / 2;

    //создаём частицу
    sf::CircleShape shape(30);
    shape.setPosition(position.x, position.y);
    shape.setFillColor(sf::Color(51, 102, 204));

    //создаём окно настроек
    sf::RenderWindow settings(sf::VideoMode(400, 230), "Settings!");
    settings.setPosition(sf::Vector2i(window.getPosition().x + window.getSize().x, window.getPosition().y));

    //кнопка
    sf::CircleShape buttonRun(10, 3);
    buttonRun.setFillColor(sf::Color::Green);
    buttonRun.setPosition(30, 10);
    buttonRun.setRotation(90);

    sf::RectangleShape buttonStop(sf::Vector2f(18, 18));
    buttonStop.setFillColor(sf::Color::Red);
    buttonStop.setPosition(45, 10);

    sf::CircleShape buttonRound(9);
    buttonRound.setFillColor(sf::Color(51, 51, 51));
    buttonRound.setPosition(80, 10);
    buttonRound.setOutlineThickness(2);
    buttonRound.setOutlineColor(sf::Color::Yellow);

    int tmp_y = 45;

    std::vector<sf::RectangleShape> rect;
    struct StructInputText {
        sf::Text inputTextTmp;
        bool textEnteredTmp = false;
    };
    std::vector<StructInputText> inputText;
    std::vector<sf::Text> label;
    std::string name[7] = { "Num Particles", "Gravity", "Collision Damping", "Particle Size", "Particle Spacing", "X", "Y"};
    std::string data[7] = { "3", "10", "0.7", "0.7", "0.5", "20", "20" };
    for (int i = 0; i < 5; i++, tmp_y += 30) {
        //поле ввода
        sf::RectangleShape rectTmp(sf::Vector2f(230, 20));
        rectTmp.setPosition(150, tmp_y);
        rectTmp.setFillColor(sf::Color(31, 31, 31));
        rect.push_back(rectTmp);
        //ввод текста
        sf::Text inputTextTmp;
        inputTextTmp.setFont(font);
        inputTextTmp.setString(data[i]);
        inputTextTmp.setCharacterSize(20);
        inputTextTmp.setFillColor(sf::Color::White);
        inputTextTmp.setPosition(155, tmp_y - 3);
        bool textEnteredTmp = false;
        StructInputText structTmp;
        structTmp.inputTextTmp = inputTextTmp;
        structTmp.textEnteredTmp = textEnteredTmp;
        inputText.push_back(structTmp);
        //имя ячейки
        sf::Text labelTmp;
        labelTmp.setFont(font);
        labelTmp.setString(name[i]);
        labelTmp.setCharacterSize(20);
        labelTmp.setFillColor(sf::Color::White);
        labelTmp.setPosition(15, tmp_y - 3);
        label.push_back(labelTmp);
    }

    int tmp_x = 20;
    std::vector<sf::RectangleShape> vesselRect;
    std::vector<StructInputText> vesselText;
    std::vector<sf::Text> vesselLabel;
    for (int i = 0; i < 2; i++, tmp_x += 80) {
        //поле ввода
        sf::RectangleShape rectTmp(sf::Vector2f(50, 20));
        rectTmp.setPosition(150 + tmp_x, tmp_y);
        rectTmp.setFillColor(sf::Color(31, 31, 31));
        vesselRect.push_back(rectTmp);
        //ввод текста
        sf::Text inputTextTmp;
        inputTextTmp.setFont(font);
        inputTextTmp.setString(data[i+5]);
        inputTextTmp.setCharacterSize(20);
        inputTextTmp.setFillColor(sf::Color::White);
        inputTextTmp.setPosition(155 + tmp_x, tmp_y - 3);
        bool textEnteredTmp = false;
        StructInputText structTmp;
        structTmp.inputTextTmp = inputTextTmp;
        structTmp.textEnteredTmp = textEnteredTmp;
        vesselText.push_back(structTmp);
        //имя ячейки
        sf::Text labelTmp;
        labelTmp.setFont(font);
        labelTmp.setString(name[i + 5]);
        labelTmp.setCharacterSize(20);
        labelTmp.setFillColor(sf::Color::White);
        labelTmp.setPosition(135 + tmp_x, tmp_y - 3);
        vesselLabel.push_back(labelTmp);
    }
    sf::Text labelBoundsSize;
    labelBoundsSize.setFont(font);
    labelBoundsSize.setString("Bounds Size");
    labelBoundsSize.setCharacterSize(20);
    labelBoundsSize.setFillColor(sf::Color::White);
    labelBoundsSize.setPosition(15, tmp_y - 3);

    sf::RectangleShape line(sf::Vector2f(settings.getSize().x - 20, 5));
    line.setPosition(10, 35);
    //подключаем время
    sf::Clock clock;

    bool flag = false;
    std::vector<bool> activ(7, false);
    std::vector<double> startData({ 3, 9.8, 0.7, 0.7, 0.5, 20, 20 });

    while (window.isOpen())
    {
        sf::Event event;
        while (settings.pollEvent(event)) {
            if (event.type == sf::Event::MouseButtonPressed) {
                for (int i = 0; i < 5; i++) {
                    if (event.mouseButton.button == sf::Mouse::Left &&
                        rect[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        for (int j = 0; j < 5; j++) {
                            i != j ? activ[j] = false : activ[j] = true;
                        }
                    }
                }
            }
            for (int i = 0; i < 5; i++) {
                if (activ[i]) {
                    rect[i].setOutlineThickness(1);
                    rect[i].setOutlineColor(sf::Color(51, 102, 153));
                    for (int j = 0; j < 5; j++) {
                        if (j != i) rect[j].setOutlineThickness(0);
                    }
                    activ[5] = false;
                    vesselRect[0].setOutlineThickness(0);
                    activ[6] = false;
                    vesselRect[1].setOutlineThickness(0);
                }
            }
            for (int i = 0; i < 5; i++) {
                if (event.type == sf::Event::TextEntered && activ[i]) {
                    if (event.text.unicode < 128) {
                        if (event.text.unicode == 8 && !inputText[i].inputTextTmp.getString().isEmpty()) {
                            std::string inputString = inputText[i].inputTextTmp.getString();
                            inputString.erase(inputString.size() - 1, 1);
                            inputText[i].inputTextTmp.setString(inputString);
                        }
                        else if (event.text.unicode == 13) {
                            std::string inputString = inputText[i].inputTextTmp.getString();
                            startData[i] = std::stod(inputString);
                            activ[i] = false;
                            rect[i].setOutlineThickness(0);
                        }
                        else if (event.text.unicode != 8 && event.text.unicode != 13) {
                            std::string inputString = inputText[i].inputTextTmp.getString();
                            inputString += static_cast<char>(event.text.unicode);
                            inputText[i].inputTextTmp.setString(inputString);
                        }
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                for (int i = 0; i < 2; i++) {
                    if (event.mouseButton.button == sf::Mouse::Left &&
                        vesselRect[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        for (int j = 0; j < 2; j++) {
                            i != j ? activ[j+5] = false : activ[j+5] = true;
                        }
                    }
                }
            }
            for (int i = 0; i < 2; i++) {
                if (activ[i+5]) {
                    vesselRect[i].setOutlineThickness(1);
                    vesselRect[i].setOutlineColor(sf::Color(51, 102, 153));
                    for (int j = 0; j < 2; j++) {
                        if (j != i) vesselRect[j].setOutlineThickness(0);
                    }
                    for (int j = 0; j < 5; j++) {
                        activ[j] = false;
                        rect[j].setOutlineThickness(0);
                    }
                }
            }
            for (int i = 0; i < 2; i++) {
                if (event.type == sf::Event::TextEntered && activ[i+5]) {
                    if (event.text.unicode < 128) {
                        if (event.text.unicode == 8 && !vesselText[i].inputTextTmp.getString().isEmpty()) {
                            std::string inputString = vesselText[i].inputTextTmp.getString();
                            inputString.erase(inputString.size() - 1, 1);
                            vesselText[i].inputTextTmp.setString(inputString);
                        }
                        else if (event.text.unicode == 13) {
                            std::string inputString = vesselText[i].inputTextTmp.getString();
                            startData[i+5] = std::stod(inputString);
                            activ[i+5] = false;
                            vesselRect[i].setOutlineThickness(0);
                        }
                        else if (event.text.unicode != 8 && event.text.unicode != 13) {
                            std::string inputString = vesselText[i].inputTextTmp.getString();
                            inputString += static_cast<char>(event.text.unicode);
                            vesselText[i].inputTextTmp.setString(inputString);
                        }
                    }
                }

            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left &&
                    buttonRun.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    flag = true;
                    clock.restart();
                    for (int i = 0; i < startData.size(); i++) {
                        std::cout << startData[i] << ' ';
                    }
                    std::cout << std::endl;
                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    buttonStop.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    flag = false;
                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    buttonRound.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    position.x = window.getSize().x / 2;
                    position.y = window.getSize().y / 2;
                    velocity.x = 0;
                    velocity.y = 0;
                }
            }
        }

        settings.clear(sf::Color(51, 51, 51));
        settings.draw(buttonRun);
        settings.draw(buttonStop);
        settings.draw(buttonRound);
        settings.draw(line);
        for (int i = 0; i < 5; i++) {
            settings.draw(rect[i]);
            settings.draw(inputText[i].inputTextTmp);
            settings.draw(label[i]);
        }
        for (int i = 0; i < 2; i++) {
            settings.draw(vesselRect[i]);
            settings.draw(vesselText[i].inputTextTmp);
            settings.draw(vesselLabel[i]);
        }
        settings.draw(labelBoundsSize);

        NumParticles = static_cast<int>(startData[0]);
        gravity = startData[1];
        CollisionDamping = static_cast<double>(startData[2]);
        ParticleSize = startData[3];
        ParticleSpacing = startData[4];
        x = startData[5], y = startData[6];

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (flag) {
            double time = clock.getElapsedTime().asSeconds() / 100;
            velocity += Vdown * gravity * time;
            position += velocity * time;

            if (position.x < window.getSize().x / 2 - vessel.getSize().x / 2 + shape.getRadius()) {
                position.x = window.getSize().x / 2 - vessel.getSize().x / 2 + shape.getRadius();
                velocity *= -1;
            }
            if (position.y < window.getSize().y / 2 - vessel.getSize().y / 2 + shape.getRadius()) {
                position.y = window.getSize().y / 2 - vessel.getSize().y / 2 + shape.getRadius();
                velocity *= -1;
            }

            if (position.x > window.getSize().x / 2 + vessel.getSize().x / 2 - shape.getRadius()) {
                position.x = window.getSize().x / 2 + vessel.getSize().x / 2 - shape.getRadius();
                velocity *= -1;
            }
            if (position.y > window.getSize().y / 2 + vessel.getSize().y / 2 - shape.getRadius()) {
                position.y = window.getSize().y / 2 + vessel.getSize().y / 2 - shape.getRadius();
                velocity *= -1;
            }
        }

        shape.setRadius(ParticleSize);
        shape.setOrigin(shape.getRadius(), shape.getRadius());
        shape.setPosition(position.x, position.y);
        vessel.setSize(sf::Vector2f(x, y));
        vessel.setOrigin(x / 2, y / 2);
        vessel.setPosition(window.getSize().x / 2, window.getSize().y / 2);
        window.clear();
        window.draw(vessel);
        window.draw(shape);
        window.display();
        settings.display();
        settings.setPosition(sf::Vector2i(window.getPosition().x + window.getSize().x - settings.getSize().x, window.getPosition().y + 40));
        Sleep(2);
    }

    return 0;
}
