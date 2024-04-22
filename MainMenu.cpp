#include "MainMenu.h"

MainMenu::MainMenu(float wigth, float height) {
	if (!font.loadFromFile("Fonts/FuturaBookItalicBt.ttf")) {
		std::cout << "No font is here";
	}

	//play
	this->main_menu[0].setFont(this->font);
	//this->main_menu[0].setColor(sf::Color::White);
	this->main_menu[0].setString("Play");
	this->main_menu[0].setCharacterSize(70);
	this->main_menu[0].setPosition(400, 200);

	//options
	this->main_menu[1].setFont(this->font);
	//this->main_menu[1].setColor(sf::Color::White);
	this->main_menu[1].setString("Options");
	this->main_menu[1].setCharacterSize(70);
	this->main_menu[1].setPosition(400, 300);

	//about
	this->main_menu[2].setFont(this->font);
	//this->main_menu[2].setColor(sf::Color::White);
	this->main_menu[2].setString("About");
	this->main_menu[2].setCharacterSize(70);
	this->main_menu[2].setPosition(400, 400);

	//exit
	this->main_menu[3].setFont(this->font);
	//this->main_menu[3].setColor(sf::Color::White);
	this->main_menu[3].setString("Exit");
	this->main_menu[3].setCharacterSize(70);
	this->main_menu[3].setPosition(400, 500);

	this->selected = -1;
}

MainMenu::~MainMenu() {}

void MainMenu::draw(sf::RenderWindow& window) {
	for (int i = 0; i < max_main_menu; ++i) {
		window.draw(main_menu[i]);
	}
}

void MainMenu::move_up() {
	if (this->selected - 1 >= 0) {
		this->main_menu[this->selected].setFillColor(sf::Color::White);
		this->selected--;
		if (this->selected == -1) {
			this->selected = 2;
		}
		this->main_menu[this->selected].setFillColor(sf::Color::Blue);
	}
}

void MainMenu::move_down() {
	if (this->selected + 1 <= max_main_menu) {
		this->main_menu[this->selected].setFillColor(sf::Color::White);
		this->selected++;
		if (this->selected == 4) {
			this->selected = 0;
		}
		this->main_menu[this->selected].setFillColor(sf::Color::Blue);
	}
}