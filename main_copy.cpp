#include "Fluid.h"
//#include "Window.cpp"
//#include "roundedRect.cpp"
#include <SFML/Graphics.hpp>
#include "SFC/Svg.hpp"
#include <windows.h>

int main() {
	sf::Font font;
	if (!font.loadFromFile("Fonts/PIXY.ttf")) {
		std::cerr << "Failed to load font!" << std::endl;
		return -1;
	}

	//fluid parameters
	int size_x = 400;
	int size_y = 200;
	int splitting = 4;

	//simulation parameters
	int framerate = 60;

	//mouse parameters

	//setting up render window
	sf::RenderWindow window(sf::VideoMode((size_x + 2) * splitting, (size_y + 2) * splitting), "Diffusion Simulation", sf::Style::Default);
	window.setPosition(sf::Vector2i(1, 1));
	window.setFramerateLimit(framerate);

	unsigned int flag = 0, mig = 0;
	bool flagMig = true, flagMenu = true, flagClose = false;;

	//flag == 0
	sf::Text labelMain;
	labelMain.setFont(font);
	labelMain.setString("Diffusion Simulation");
	labelMain.setCharacterSize(80);
	labelMain.setFillColor(sf::Color::White);
	labelMain.setPosition(400, 50);

	//кнопки главного меню
	sf::RectangleShape rectRun(sf::Vector2f(300, 40));
	rectRun.setOrigin(150, 20);
	rectRun.setFillColor(sf::Color::Black);
	double x = window.getSize().x / 2;
	double y = window.getSize().y / 2 - 100;
	rectRun.setPosition(x, y);
	rectRun.setOutlineThickness(2);
	rectRun.setOutlineColor(sf::Color(102, 102, 102));
	sf::Text labelRun;
	labelRun.setFont(font);
	labelRun.setString("Start");
	labelRun.setCharacterSize(40);
	labelRun.setFillColor(sf::Color::White);
	labelRun.setPosition(x - 55, y - 30);

	y += 75;

	sf::RectangleShape rectSet(sf::Vector2f(300, 40));
	rectSet.setOrigin(150, 20);
	rectSet.setFillColor(sf::Color::Black);
	rectSet.setPosition(x, y);
	rectSet.setOutlineThickness(2);
	rectSet.setOutlineColor(sf::Color(102, 102, 102));
	sf::Text labelSet;
	labelSet.setFont(font);
	labelSet.setString("Settings");
	labelSet.setCharacterSize(40);
	labelSet.setFillColor(sf::Color::White);
	labelSet.setPosition(x - 85, y - 30);

	y += 75;

	sf::RectangleShape rectOut(sf::Vector2f(300, 40));
	rectOut.setOrigin(150, 20);
	rectOut.setFillColor(sf::Color::Black);
	rectOut.setPosition(x, y);
	rectOut.setOutlineThickness(2);
	rectOut.setOutlineColor(sf::Color(102, 102, 102));
	sf::Text labelOut;
	labelOut.setFont(font);
	labelOut.setString("Exit");
	labelOut.setCharacterSize(40);
	labelOut.setFillColor(sf::Color::White);
	labelOut.setPosition(x - 35, y - 30);

	sf::Text labelVers;
	labelVers.setFont(font);
	labelVers.setString("Version 1.0.1");
	labelVers.setCharacterSize(25);
	labelVers.setFillColor(sf::Color::Yellow);
	labelVers.setPosition(window.getSize().x - 160, window.getSize().y - 40);

	//flag == 1
	sf::RectangleShape rectLine(sf::Vector2f(2, window.getSize().y - 20));
	rectLine.setFillColor(sf::Color(102, 102, 102));
	rectLine.setPosition(70, 10);

	sf::RectangleShape rectMenu(sf::Vector2f(50, 50));
	rectMenu.setFillColor(sf::Color::Black);
	rectMenu.setPosition(10, 20);
	rectMenu.setOutlineThickness(2);
	rectMenu.setOutlineColor(sf::Color(102, 102, 102));

	sf::RectangleShape rectM1(sf::Vector2f(42, 4));
	rectM1.setFillColor(sf::Color(102, 102, 102));
	rectM1.setPosition(14, 28);
	sf::RectangleShape rectM2(sf::Vector2f(42, 4));
	rectM2.setFillColor(sf::Color(102, 102, 102));
	rectM2.setPosition(14, 43);
	sf::RectangleShape rectM3(sf::Vector2f(42, 4));
	rectM3.setFillColor(sf::Color(102, 102, 102));
	rectM3.setPosition(14, 58);

	//flagClose == true
	sf::RectangleShape rectClose(sf::Vector2f(400, 150));
	rectClose.setFillColor(sf::Color::Black);
	rectClose.setOrigin(200, 125);
	rectClose.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	rectClose.setOutlineThickness(2);
	rectClose.setOutlineColor(sf::Color(102, 102, 102));

	sf::Text labelSet;
	labelSet.setFont(font);
	labelSet.setString("Really close the window?");
	labelSet.setCharacterSize(40);
	labelSet.setFillColor(sf::Color::White);
	labelSet.setPosition(window.getSize().x / 2 - , y - 30);

	while (window.isOpen())
	{
		//window details
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				window.close();
		}

		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left &&
				rectRun.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
				flag = 1;
				std::cout << 1 << std::endl;
			}
			if (event.mouseButton.button == sf::Mouse::Left &&
				rectSet.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
				flag = 2;
				std::cout << 2 << std::endl;
			}
			if (event.mouseButton.button == sf::Mouse::Left &&
				rectOut.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
				flagClose = true;
			}
			if (flagMenu)
			{
				if (sf::Mouse::getPosition().x < rectLine.getPosition().x) {
					rectLine.setPosition(rectLine.getPosition().x + 250, rectLine.getPosition().y);
					flagMenu = false;
					rectSet.setPosition(160, 110);
					labelSet.setPosition(75, 80);
					rectOut.setPosition(160, 170);
					labelOut.setPosition(125, 140);
				}
			}
			else
			{
				if (event.mouseButton.button == sf::Mouse::Left && !flagMenu &&
					rectMenu.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
					rectLine.setPosition(rectLine.getPosition().x - 250, rectLine.getPosition().y);
					flagMenu = true;
				}
			}
		}

		window.clear();
		if (flag == 0) {
			window.draw(labelMain);
			window.draw(rectRun);
			window.draw(labelRun);
			window.draw(rectSet);
			window.draw(labelSet);
			window.draw(rectOut);
			window.draw(labelOut);
			window.draw(labelVers);
		}
		else if (flag == 1) {
			window.draw(rectLine);
			window.draw(rectMenu);
			window.draw(rectM2);
			if (flagMenu) {
				window.draw(rectM1);
				window.draw(rectM3);
			}
			else {
				window.draw(rectSet);
				window.draw(labelSet);
				window.draw(rectOut);
				window.draw(labelOut);
			}
		}

		if (flagClose) {
			window.draw(rectClose);
		}
		Sleep(100);
		if (mig < 5 and flagMig) {
			mig++;
			labelMain.setCharacterSize(labelMain.getCharacterSize() + 1);
			labelMain.setPosition(labelMain.getPosition().x - 2, labelMain.getPosition().y);
			if (mig == 5) flagMig = false;
		}
		else {
			mig--;
			labelMain.setCharacterSize(labelMain.getCharacterSize() - 1);
			labelMain.setPosition(labelMain.getPosition().x + 2, labelMain.getPosition().y);
			if (mig == 0) flagMig = true;
		}
		window.display();
	}
	return 0;
}