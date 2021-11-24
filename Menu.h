#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Score.h"
#include "String.h"

enum STATES { MENU, NAME_ENTER, SCORE, GAME };

class Menu
{
public:
	Menu(sf::RenderWindow* window);
	Score score;
	void draw();
	void Move();
	void update(std::vector<sf::Event> events);
	void timeUpdate(float deltatime);
	void writeFile();
	inline int getState() { return state; }
	inline int GetPressedItem() { return selectedItem; }
	inline void getScore(int score) { gameScore = score; }

private:
	int selectedItem=0;
	int state = 0;
	int gameScore = 0;
	float debounce;
	bool isWritten = 0;

	sf::Event event;
	sf::RenderWindow* window;
	sf::Font font;

	//MAIN MENU_0
	sf::RectangleShape background;
	sf::Texture backgroundTexture;
	sf::Text menu[3];
	
	//NAME ENTER_1
	std::string enteredName;
	sf::Text typingName;

	//SCOREBOARD_2
	sf::Texture scoreboardBackground;
	sf::Text enterTitle;
	sf::Text playerScore[5];
	sf::Text playerName[5];
};




