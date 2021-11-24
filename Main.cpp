#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Menu.h"

int main()
{
	sf::Clock clock;
	sf::RenderWindow window(sf::VideoMode(1200, 900), "RABBIT MASTER");
	window.setFramerateLimit(144.f);
	sf::Event event;
	sf::Texture texture;
	std::vector<sf::Event> keyInput;

	Menu menu(&window);
	Game game(&window);
	srand(static_cast<unsigned>(time(0)));
	float deltatime;

	if (!texture.loadFromFile("Picture/11.jpg"))
	{

	}
	sf::Sprite background;
	background.setTexture(texture);

	while (window.isOpen())
	{
		keyInput.clear();
		deltatime = clock.restart().asSeconds();
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					window.close();
				break;
			case sf::Event::TextEntered:
				keyInput.push_back(event);
				break;
			case sf::Event::Closed:
				window.close();
				break;
			}
		}

		int state = menu.getState();
		if (state == 0)
		{
			window.draw(background);
			menu.timeUpdate(deltatime);
			menu.update(keyInput);
			menu.draw();
		}
		else if (state == 1)
		{
			menu.timeUpdate(deltatime);
			menu.update(keyInput);
			menu.draw();
		}
		else if (state == 2)
		{
			menu.update(keyInput);
			menu.draw();
		}
		else if (state == 3)
		{
			game.timeUpdate(deltatime);
			game.update();
			game.render();
			if (game.getEndGame())
			{
				menu.getScore(game.getPoints());
				menu.writeFile();
			}
		}
	}

	//Initialise random seed


	//Initialise game object


	//End of application
	return 0;
}
