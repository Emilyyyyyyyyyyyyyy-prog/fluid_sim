#include "Fluid.h"
#include "MainMenu.h"
#include <SFML/Graphics.hpp>

int main() {
	//make a main window
	sf::RenderWindow menu(sf::VideoMode(960, 720), "Main", sf::Style::Default);
	MainMenu mainMenu(menu.getSize().x, menu.getSize().y);

	//fluid parameters
	int xSize = 300;
	int ySize = 300;
	int elementSize = 4;
	float diff = 0.07;
	float visc = 0.9975;

	//simulation parameters
	int framerate = 120;
	float dt = 1.0 / framerate;
	int numIterations = 5;

	//mouse parameters
	int mouseX = 0;
	int mouseY = 0;
	int lastMouseX = 0;
	int lastMouseY = 0;

	//setting up render window
	//sf::RenderWindow window(sf::VideoMode((xSize + 2) * elementSize, (ySize + 2) * elementSize), "Fluid Simulation!");
	//window.setFramerateLimit(framerate);

	//creating rendering tools
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	image.create((xSize + 2) * elementSize, (ySize + 2) * elementSize, sf::Color::Black);

	//now let's create the fluid we want (x, y, diffusion, viscosity, timestep, accuracy/quality)
	Fluid fluid(xSize, ySize, diff, visc, dt, numIterations);

	while (menu.isOpen()) {
		//window details
		sf::Event event;
		while (menu.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				menu.close();

			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Up) {
					mainMenu.move_up();
					break;
				}
				if (event.key.code == sf::Keyboard::Down) {
					mainMenu.move_down();
					break;
				}
				if (event.key.code == sf::Keyboard::Return) {
					sf::RenderWindow window(sf::VideoMode(960, 720), "simulation");
					window.setFramerateLimit(framerate);
					sf::RenderWindow Options(sf::VideoMode(960, 720), "OPTIONS");
					sf::RenderWindow About(sf::VideoMode(960, 720), "ABOUT");

					int x = mainMenu.pressed();
					if (x == 0) {
						sf::Event s_event;
						while (window.pollEvent(s_event)) {
							if (event.type == sf::Event::Closed)
								window.close();

							if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
								window.close();
						}
						Options.close();
						About.close();
						lastMouseX = mouseX;
						lastMouseY = mouseY;
						sf::Vector2i localPosition = sf::Mouse::getPosition(window);
						mouseX = localPosition.x;
						mouseY = localPosition.y;

						if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
							if ((mouseX / elementSize > 0 && mouseX / elementSize < xSize - 1 && mouseY / elementSize  > 0 && mouseY / elementSize < ySize - 1) && (lastMouseX / elementSize > 0 && lastMouseX / elementSize < xSize - 1 && lastMouseY / elementSize  > 0 && lastMouseY / elementSize < ySize - 1)) {
								fluid.addSource(lastMouseX / elementSize, lastMouseY / elementSize, mouseX / elementSize, mouseY / elementSize);
							}
						}

						if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
							fluid.reset();
						}

						fluid.update();
						fluid.render(elementSize, image);
						texture.loadFromImage(image);
						sprite.setTexture(texture, true);
						window.draw(sprite);
						window.display();
					}
					if (x == 1) {
						while (Options.isOpen()) {
							sf::Event o_event;
							while (Options.pollEvent(o_event)) {
								if (o_event.type == sf::Event::Closed)
									Options.close();

								if (o_event.type == sf::Event::KeyPressed) {
									if (o_event.key.code == sf::Keyboard::Escape)
										Options.close();
								}
							}
							window.close();
							Options.clear();
							About.close();

							Options.display();
						}
					}
					if (x == 2) {
						while (About.isOpen()) {
							sf::Event a_event;
							while (About.pollEvent(a_event)) {
								if (a_event.type == sf::Event::Closed)
									About.close();

								if (a_event.type == sf::Event::KeyPressed) {
									if (a_event.key.code == sf::Keyboard::Escape)
										About.close();
								}
							}
							window.close();
							Options.clear();
							About.clear();

							About.display();
						}
					}
					if (x == 3)
						menu.close();
					break;
				}
			}
		}
		menu.clear();
		mainMenu.draw(menu);
		menu.display();
	}
	return 0;
}
