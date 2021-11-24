#include "Menu.h"

Menu::Menu(sf::RenderWindow* window)
{
	if (!font.loadFromFile("Fonts/WarWound.otf"))
	{
		//handle error
	}
	//MAIN MENU
	backgroundTexture.loadFromFile("Picture/MENU.jpg");
	background.setSize({ 1200, 900 });
	background.setTexture(&backgroundTexture);

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Black);
	menu[0].setCharacterSize(100);
	menu[0].setString("PLAY");
	menu[0].setOrigin(menu[0].getLocalBounds().width / 2, menu[0].getLocalBounds().height / 2);
	menu[0].setPosition(sf::Vector2f(window->getSize().x / 2, window->getSize().y / (4) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setCharacterSize(100);
	menu[1].setString("SCORE");
	menu[1].setOrigin(menu[1].getLocalBounds().width / 2, menu[1].getLocalBounds().height / 2);
	menu[1].setPosition(sf::Vector2f(window->getSize().x / 2, window->getSize().y / (4) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setCharacterSize(100);
	menu[2].setString("EXIT");
	menu[2].setOrigin(menu[2].getLocalBounds().width / 2, menu[2].getLocalBounds().height / 2);
	menu[2].setPosition(sf::Vector2f(window->getSize().x / 2, window->getSize().y / (4) * 3));

	//SCORE
	scoreboardBackground.loadFromFile("Picture/1.jpg");
	for (int i = 0; i < 5; i++)
	{
		playerName[i].setFont(font);
		playerName[i].setFillColor(sf::Color::White);
		playerName[i].setCharacterSize(70);
		playerName[i].setPosition(window->getSize().x / 2 - 300, window->getSize().y / 2 - 300 + (i * 100));

		playerScore[i].setFont(font);
		playerScore[i].setFillColor(sf::Color::White);
		playerScore[i].setCharacterSize(60);
		playerScore[i].setPosition(window->getSize().x / 2 + 300, window->getSize().y / 2 - 300 + (i * 100));
	}

	//NAME ENTER
	typingName.setFont(font);
	typingName.setFillColor(sf::Color::White);
	typingName.setCharacterSize(60);
	typingName.setPosition(window->getSize().x / 2, window->getSize().y / 2);

	enterTitle.setFont(font);
	enterTitle.setFillColor(sf::Color::White);
	enterTitle.setCharacterSize(100);
	enterTitle.setPosition(window->getSize().x / 2, window->getSize().y / 2 - 200);
	enterTitle.setString("Enter your name");
	enterTitle.setOrigin(enterTitle.getLocalBounds().width / 2, enterTitle.getLocalBounds().height / 2);


	this->window = window;
}

void Menu::timeUpdate(float deltatime)
{
	debounce += deltatime;
}

void Menu::draw()
{
	window->clear();
	if (state == MENU)
	{
		background.setTexture(&backgroundTexture);
		window->draw(background);
		for (int i = 0; i < 3; i++)
		{
			window->draw(menu[i]);
		}
	}
	if (state == NAME_ENTER)
	{
		window->draw(enterTitle);
		window->draw(typingName);
	}
	if (state == SCORE)
	{	
		background.setTexture(&scoreboardBackground);
		window->draw(background);
		for (int i = 0; i < 5; i++)
		{
			window->draw(playerName[i]);
			window->draw(playerScore[i]);
		}
	}
	window->display();
}

void Menu::Move()
{
	if (selectedItem > 0 &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
		debounce >= 0.2)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		selectedItem--;
		menu[selectedItem].setFillColor(sf::Color::Black);
		debounce = 0;
	}
	else if (selectedItem < 2 &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
		debounce >= 0.2)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		selectedItem++;
		menu[selectedItem].setFillColor(sf::Color::Black);
		debounce = 0;
	}
}

void Menu::writeFile()
{
	if (!isWritten)
	{
		score.writeFile(enteredName, gameScore);
		score.clearScore();
		isWritten = true;
	}
}

void Menu::update(std::vector<sf::Event> events)
{
	if (state == MENU)
	{
		Move();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			if (selectedItem == 0)
				state = NAME_ENTER;
			else if (selectedItem == 1)
				state = SCORE;
			else
				window->close();
			debounce = 0;
		}
	}

	if (state == NAME_ENTER)
	{
		for (int i = 0; i < events.size(); i++)
		{
			if (events[i].type == sf::Event::TextEntered &&
				!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				if (events[i].text.unicode == 32 && enteredName.length() < 10)
				{
					enteredName += static_cast<char>(95);
				}
				if (events[i].text.unicode == 8 && enteredName.length() > 0)
				{
					enteredName.erase(enteredName.length() - 1);
				}
				else if (events[i].text.unicode < 128 && enteredName.length() < 10 &&
					events[i].text.unicode != 8 && (events[i].text.unicode < 48 ||
						events[i].text.unicode > 57))
				{
					typingName.setFillColor(sf::Color(140.f, 100.f, 54.f, 255.f));
					enteredName += static_cast<char>(events[i].text.unicode);
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && debounce >= 0.2f)
			{
				debounce = 0;
				state = GAME;
			}
		}

		typingName.setString(enteredName);
		typingName.setOrigin(typingName.getLocalBounds().width / 2, typingName.getLocalBounds().height / 2);
		
	}

	if (state == SCORE)
	{
		score.readFile();
		for (int i = 0; i < 5; i++)
		{
			playerName[i].setString(score.getName()[i].second);
			playerScore[i].setString(std::to_string(score.getName()[i].first));
		}
		score.clearScore();
	}
}
