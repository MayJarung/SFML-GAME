#pragma once

#include<iostream>
#include<ctime>
#include<vector>
#include<sstream>
#include<string>

#include"Player.h"
#include"Ball.h"


class Game
{
private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	bool endGame;
	sf::Event sfmlEvent;

	Player player;

	int points; 


	sf::RectangleShape background;
	sf::Texture texturebackground;
	sf::Texture enemyTexture[3];

	
	sf::Font font;
	sf::Text  guiText;
	sf::Text endGameText;
	sf::Text NameText;

	std::vector<Ball> ball;
	float spawnTimerMax;
	float spawnTimer;
	float timer;
	float fallSpeed;
	int maxBall;

	//Private Functions
	void initVariables();
	void initWindow();
	void initFont();
	void initText();
	void initBackground();
public:
	Game(sf::RenderWindow* window);

	//Accessors
	const bool& getEndGame() const;
	inline const int getPoints() { return points; }
	//Modifiers
	void timeUpdate(float deltatime);

	//Funtions          
	const bool running() const;
	void pollEvents();
	void spawnBall();
	const int randBallType() const;
	void updatePlayer();
	void updateCollison();
	void updateGui();
	void update();
	

	void renderGui(sf::RenderTarget* target);
	void render();

};
