#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <string>
#include "Fluid.h"

int main() {
	sf::Font font;
	if (!font.loadFromFile("Fonts/PIXY.ttf")) {
		std::cerr << "Failed to load font!" << std::endl;
		return -1;
	}

	double diff = 0.07;
	double visc = 0.997;

	//fluid parameters
	int xSize = 400;
	int ySize = 200;
	int elementSize = 4;

	//simulation parameters
	int framerate = 120;
	float dt = 1.0 / framerate;
	int numIterations = 5;

	//mouse parameters
	int mouseX = 0;
	int mouseY = 0;
	int lastMouseX = 0;
	int lastMouseY = 0;

	//creating rendering tools
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	image.create((xSize + 2) * elementSize, (ySize + 2) * elementSize, sf::Color::Black);


	//setting up render window
	sf::RenderWindow window(sf::VideoMode((xSize + 2) * elementSize, (ySize + 2) * elementSize), "Diffusion Simulation", sf::Style::Default);
	window.setPosition(sf::Vector2i(1, 1));
	window.setFramerateLimit(framerate);

	//now let's create the fluid we want (x, y, diffusion, viscosity, timestep, accuracy/quality)
	Fluid fluid(xSize, ySize, diff, visc, dt, numIterations);

	unsigned int flag = 0, mig = 0;
	bool flagMig = true, flagMenu = false, flagClose = false, flagJet = false, flagGo = false;

	//flag == 0
	//main screensaver
	sf::Text labelMain;
	labelMain.setFont(font);
	labelMain.setString("Diffusion Simulation");
	labelMain.setCharacterSize(80);
	labelMain.setFillColor(sf::Color::White);
	labelMain.setPosition(400, 50);

	//main buttons: start, settings, exit
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

	sf::RectangleShape rectHome(sf::Vector2f(300, 40));
	rectHome.setOrigin(150, 20);
	rectHome.setFillColor(sf::Color::Black);
	rectHome.setPosition(160, window.getSize().y - 50);
	rectHome.setOutlineThickness(2);
	rectHome.setOutlineColor(sf::Color(102, 102, 102));
	sf::Text labelHome;
	labelHome.setFont(font);
	labelHome.setString("Home");
	labelHome.setCharacterSize(40);
	labelHome.setFillColor(sf::Color::White);
	labelHome.setPosition(120, window.getSize().y - 80);

	sf::Text labelVers;
	labelVers.setFont(font);
	labelVers.setString("Version 1.0.1");
	labelVers.setCharacterSize(25);
	labelVers.setFillColor(sf::Color::Yellow);
	labelVers.setPosition(window.getSize().x - 160, window.getSize().y - 40);

	//flag == 1
	//on the page start
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
	//closing window and two buttons yes or no
	sf::RectangleShape rectClose(sf::Vector2f(600, 150));
	rectClose.setFillColor(sf::Color::Black);
	rectClose.setOrigin(300, 125);
	rectClose.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	rectClose.setOutlineThickness(2);
	rectClose.setOutlineColor(sf::Color::Red);

	sf::Text labelClose;
	labelClose.setFont(font);
	labelClose.setString("Really close the window?");
	labelClose.setCharacterSize(40);
	labelClose.setFillColor(sf::Color::White);
	labelClose.setPosition(rectClose.getPosition().x - 270, rectClose.getPosition().y - 120);

	sf::RectangleShape rectYes(sf::Vector2f(100, 50));
	rectYes.setFillColor(sf::Color::Black);
	rectYes.setOrigin(50, 25);
	rectYes.setPosition(window.getSize().x / 2 - 100, window.getSize().y / 2 - 25);
	rectYes.setOutlineThickness(2);
	rectYes.setOutlineColor(sf::Color(102, 102, 102));

	sf::Text labelYes;
	labelYes.setFont(font);
	labelYes.setString("Yes");
	labelYes.setCharacterSize(40);
	labelYes.setFillColor(sf::Color::White);
	labelYes.setPosition(rectYes.getPosition().x - 35, rectYes.getPosition().y - 30);

	sf::RectangleShape rectNo(sf::Vector2f(100, 50));
	rectNo.setFillColor(sf::Color::Black);
	rectNo.setOrigin(50, 25);
	rectNo.setPosition(window.getSize().x / 2 + 100, window.getSize().y / 2 - 25);
	rectNo.setOutlineThickness(2);
	rectNo.setOutlineColor(sf::Color(102, 102, 102));

	sf::Text labelNo;
	labelNo.setFont(font);
	labelNo.setString("No");
	labelNo.setCharacterSize(40);
	labelNo.setFillColor(sf::Color::White);
	labelNo.setPosition(rectNo.getPosition().x - 20, rectNo.getPosition().y - 30);

	//flag == 2
	//diffusion input
	sf::RectangleShape rectInput1(sf::Vector2f(300, 40));
	rectInput1.setOrigin(rectInput1.getSize().x / 2, rectInput1.getSize().y / 2);
	rectInput1.setPosition(window.getSize().x / 2 + 160, window.getSize().y / 2 - 50);
	rectInput1.setFillColor(sf::Color::Black);
	rectInput1.setOutlineThickness(2);
	rectInput1.setOutlineColor(sf::Color(102, 102, 102));
	
	sf::Text inputText1;
	inputText1.setFont(font);
	inputText1.setString("0.07");
	inputText1.setCharacterSize(40);
	inputText1.setFillColor(sf::Color::White);
	inputText1.setPosition(rectInput1.getPosition().x - 140, rectInput1.getPosition().y - 30);
	bool textEntered1 = false;
	int count1 = 4;
	
	sf::Text labelInput1;
	labelInput1.setFont(font);
	labelInput1.setString("Diffusion coefficient");
	labelInput1.setCharacterSize(40);
	labelInput1.setFillColor(sf::Color::White);
	labelInput1.setPosition(rectInput1.getPosition().x - 600, rectInput1.getPosition().y - 30);
	bool activ1 = false;

	//viscosity input
	sf::RectangleShape rectInput2(sf::Vector2f(300, 40));
	rectInput2.setOrigin(rectInput1.getSize().x / 2, rectInput1.getSize().y / 2);
	rectInput2.setPosition(window.getSize().x / 2 + 160, window.getSize().y / 2);
	rectInput2.setFillColor(sf::Color::Black);
	rectInput2.setOutlineThickness(2);
	rectInput2.setOutlineColor(sf::Color(102, 102, 102));
	
	sf::Text inputText2;
	inputText2.setFont(font);
	inputText2.setString("0.997");
	inputText2.setCharacterSize(40);
	inputText2.setFillColor(sf::Color::White);
	inputText2.setPosition(rectInput2.getPosition().x - 140, rectInput2.getPosition().y - 30);
	bool textEntered2 = false;
	int count2 = 5;
	
	sf::Text labelInput2;
	labelInput2.setFont(font);
	labelInput2.setString("Viscosity coefficient");
	labelInput2.setCharacterSize(40);
	labelInput2.setFillColor(sf::Color::White);
	labelInput2.setPosition(rectInput2.getPosition().x - 600, rectInput2.getPosition().y - 30);
	bool activ2 = false;

	//button save
	sf::RectangleShape rectSave(sf::Vector2f(300, 40));
	rectSave.setOrigin(rectSave.getSize().x / 2, rectInput1.getSize().y / 2);
	rectSave.setPosition(window.getSize().x / 2 + 160, window.getSize().y / 2 + 50);
	rectSave.setFillColor(sf::Color::Black);
	rectSave.setOutlineThickness(2);
	rectSave.setOutlineColor(sf::Color(102, 102, 102));
	sf::Text labelSave;
	labelSave.setFont(font);
	labelSave.setString("Save");
	labelSave.setCharacterSize(40);
	labelSave.setFillColor(sf::Color::White);
	labelSave.setPosition(rectSave.getPosition().x - 50, rectSave.getPosition().y - 30);
	bool activ3 = false;

	//button settings on the left of the screen
	sf::Text labelSettings;
	labelSettings.setFont(font);
	labelSettings.setString("Settings");
	labelSettings.setCharacterSize(80);
	labelSettings.setFillColor(sf::Color::White);
	labelSettings.setPosition(100, -15);

	while (window.isOpen()) {
		//window details
		sf::Event event;
		while (window.pollEvent(event)) {
			//close window with exit button and escape
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				window.close();
			if (event.mouseButton.button == sf::Mouse::Left &&
				rectInput1.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
				activ1 = true;
				rectInput1.setOutlineColor(sf::Color::Yellow);
				rectInput2.setOutlineColor(sf::Color(102, 102, 102));
				rectSave.setOutlineColor(sf::Color(102, 102, 102));
				activ2 = false, activ3 = false;
			}
			//getting diffusion input
			if (event.type == sf::Event::TextEntered && activ1) {
				if (event.text.unicode < 128) {
					if (event.text.unicode == 8 && !inputText1.getString().isEmpty()) {
						std::string inputString = inputText1.getString();
						inputString.erase(inputString.size() - 1, 1);
						inputText1.setString(inputString);
						count1--;
					}
					else if (event.text.unicode == 13) {
						std::string inputString = inputText1.getString();
						activ1 = false;
						rectInput1.setOutlineColor(sf::Color(102, 102, 102));
					}
					else if (event.text.unicode >= 48 && event.text.unicode <= 57 || static_cast<char>(event.text.unicode) == '.') {
						std::string inputString = inputText1.getString();
						if (count1 <= 7) {
							inputString += static_cast<char>(event.text.unicode);
							count1++;
							inputText1.setString(inputString);
						}
					}
				}
			}
			if (event.mouseButton.button == sf::Mouse::Left &&
				rectInput2.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
				activ2 = true;
				rectInput2.setOutlineColor(sf::Color::Yellow);
				rectInput1.setOutlineColor(sf::Color(102, 102, 102));
				rectSave.setOutlineColor(sf::Color(102, 102, 102));
				activ1 = false, activ3 = false;
			}
			//getting viscosity input
			if (event.type == sf::Event::TextEntered && activ2) {
				if (event.text.unicode < 128) {
					if (event.text.unicode == 8 && !inputText2.getString().isEmpty()) {
						std::string inputString = inputText2.getString();
						inputString.erase(inputString.size() - 1, 1);
						inputText2.setString(inputString);
						count2--;
					}
					else if (event.text.unicode == 13) {
						std::string inputString = inputText2.getString();
						activ2 = false;
						rectInput2.setOutlineColor(sf::Color(102, 102, 102));
					}
					else if (event.text.unicode >= 48 && event.text.unicode <= 57 || static_cast<char>(event.text.unicode) == '.') {
						std::string inputString = inputText2.getString();
						if (count2 <= 7) {
							inputString += static_cast<char>(event.text.unicode);
							count2++;
							inputText2.setString(inputString);
						}
					}
				}
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left && !flagClose &&
					rectRun.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
					flag = 1;
					flagGo = true;
					if (flagMenu) {
						rectLine.setPosition(rectLine.getPosition().x - 250, rectLine.getPosition().y);
						flagMenu = false;
					}
				}
				if (event.mouseButton.button == sf::Mouse::Left && !flagClose &&
					rectSet.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
					flag = 2;
					flagGo = true;
					if (flagMenu) {
						rectLine.setPosition(rectLine.getPosition().x - 250, rectLine.getPosition().y);
						flagMenu = false;
					}
				}
				if (event.mouseButton.button == sf::Mouse::Left && !flagClose &&
					rectOut.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
					flagClose = true;
				}
				if (event.mouseButton.button == sf::Mouse::Left && !flagClose &&
					rectHome.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
					flag = 0;
					flagGo = false;
					flagMenu = false;
					x = window.getSize().x / 2;
					y = window.getSize().y / 2 - 100;
					rectRun.setPosition(x, y);
					labelRun.setPosition(x - 55, y - 30);

					y += 75;

					rectSet.setPosition(x, y);
					labelSet.setPosition(x - 85, y - 30);

					y += 75;

					rectOut.setPosition(x, y);
					labelOut.setPosition(x - 35, y - 30);
					rectLine.setPosition(rectLine.getPosition().x - 250, rectLine.getPosition().y);
				}
				if (event.mouseButton.button == sf::Mouse::Left && !flagMenu &&
					rectMenu.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
					rectLine.setPosition(rectLine.getPosition().x + 250, rectLine.getPosition().y);
					flagMenu = true;
				}
				else if (event.mouseButton.button == sf::Mouse::Left && flagMenu &&
					rectMenu.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
					rectLine.setPosition(rectLine.getPosition().x - 250, rectLine.getPosition().y);
					flagMenu = false;
				}
				if (event.mouseButton.button == sf::Mouse::Left &&
					rectNo.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
					flagClose = false;
				}
				if (event.mouseButton.button == sf::Mouse::Left &&
					rectYes.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
					window.close();
				}
				if (flagGo) {
					rectRun.setPosition(160, 110);
					labelRun.setPosition(100, 80);
					rectSet.setPosition(160, 170);
					labelSet.setPosition(75, 140);
					rectOut.setPosition(160, 230);
					labelOut.setPosition(125, 200);
				}
			}
			if (event.mouseButton.button == sf::Mouse::Left &&
				rectSave.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
				rectInput1.setOutlineColor(sf::Color(102, 102, 102));
				rectInput2.setOutlineColor(sf::Color(102, 102, 102));
				std::string tmp1 = inputText1.getString();
				std::string tmp2 = inputText2.getString();
				if (std::stod(tmp1) > 0 && std::stod(tmp1) <= 1 && std::stod(tmp2) > 0 && std::stod(tmp2) <= 1) {
					diff = std::stod(tmp1), visc = std::stod(tmp2);
					rectSave.setOutlineColor(sf::Color::Green);
				}
				else {
					rectSave.setOutlineColor(sf::Color::Red);
				}

			}
		}
		window.clear();
		if (flag == 1) {  // we in the page start
			lastMouseX = mouseX;
			lastMouseY = mouseY;
			sf::Vector2i localPosition = sf::Mouse::getPosition(window);
			mouseX = localPosition.x;
			mouseY = localPosition.y;

			//add new source
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if ((mouseX / elementSize > 0 && mouseX / elementSize < xSize - 1 && mouseY / elementSize  > 0 && mouseY / elementSize < ySize - 1) && (lastMouseX / elementSize > 0 && lastMouseX / elementSize < xSize - 1 && lastMouseY / elementSize  > 0 && lastMouseY / elementSize < ySize - 1)) {
					fluid.addSource(lastMouseX / elementSize, lastMouseY / elementSize, mouseX / elementSize, mouseY / elementSize);
				}
			}

			//restart simulation
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				fluid.reset();
			}

			fluid.update();
			fluid.render(elementSize, image);
			texture.loadFromImage(image);
			sprite.setTexture(texture, true);
			window.draw(sprite);
		}

		if (flag == 0) {  // we on the main page
			window.draw(labelMain);
			window.draw(rectRun);
			window.draw(labelRun);
			window.draw(rectSet);
			window.draw(labelSet);
			window.draw(rectOut);
			window.draw(labelOut);
			window.draw(labelVers);
		}
		else if (flag == 1 || flag == 2) {
			window.draw(rectLine);
			window.draw(rectMenu);
			window.draw(rectM2);
			if (!flagMenu) {
				window.draw(rectM1);
				window.draw(rectM3);
			}
			else {
				if (flagGo) {
					window.draw(rectSet);
					window.draw(labelSet);
					window.draw(rectRun);
					window.draw(labelRun);
					window.draw(rectHome);
					window.draw(labelHome);
				}
				window.draw(rectOut);
				window.draw(labelOut);
			}
		}
		if (flag == 2) {  // we on the page settings
			if (flagMenu && labelSettings.getPosition().x == 100) labelSettings.setPosition(labelSettings.getPosition().x + 250, labelSettings.getPosition().y);
			if (!flagMenu && labelSettings.getPosition().x == 350) labelSettings.setPosition(labelSettings.getPosition().x - 250, labelSettings.getPosition().y);
			window.draw(labelSettings);
			window.draw(rectInput1);
			window.draw(labelInput1);
			window.draw(inputText1);
			window.draw(rectInput2);
			window.draw(labelInput2);
			window.draw(inputText2);
			window.draw(rectSave);
			window.draw(labelSave);
		}
		if (flagClose) {  // we on the page exit
			window.draw(rectClose);
			window.draw(rectYes);
			window.draw(rectNo);
			window.draw(labelYes);
			window.draw(labelNo);
			window.draw(labelClose);
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
