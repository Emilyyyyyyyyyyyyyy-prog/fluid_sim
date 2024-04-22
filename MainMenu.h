#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

const int max_main_menu = 4;
class MainMenu {
private:
	int selected;
	sf::Font font;
	sf::Text main_menu[max_main_menu];
public:
	MainMenu(float width, float height);

	void draw(sf::RenderWindow& window);
	void move_up();
	void move_down();

	int pressed() {
		return this->selected;
	}

	~MainMenu();
};