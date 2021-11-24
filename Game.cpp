#include "Game.h"


void Game::initVariables()
{
	this->endGame = false;
	this->spawnTimerMax = 0.9f;
	this->maxBall = 10;
	this->points = 0;
	this->timer = 0;
	this->fallSpeed = 3;
}

//Private functions

void Game::initFont()
{
	if (!this->font.loadFromFile("Fonts/WarWound.otf"))
	{
		std::cout << " ! ERROR::GAME::INFINITIONS::CLOUD NOT LOAD WarWound.otf" << "\n";
	}
}

//con/Des
Game::Game(sf::RenderWindow* window)
{
	this->initVariables();
	this->initFont();
	this->initText();
	this->initBackground();
	this->window = window;
	for (int i=0; i<3; i++)
	{
		this->enemyTexture[i].loadFromFile("Picture/egg"+std::to_string(i+1)+".png");
	}
}

void Game::timeUpdate(float deltatime)
{
	spawnTimer += deltatime;
	timer += deltatime;
}


void Game::initText()
{
	//gui text init
	this->guiText.setFont(this->font);
	this->guiText.setFillColor(sf::Color::White);
	this->guiText.setCharacterSize(30);
	this->guiText.setPosition(sf::Vector2f(10, 10));

	//EndGame Text
	this->endGameText.setFont(this->font);
	this->endGameText.setFillColor(sf::Color::Red);
	this->endGameText.setCharacterSize(150);
	this->endGameText.setPosition(sf::Vector2f(200, 300));
	this->endGameText.setString(" GAME OVER ");
	/*
	//Name Text
	this->NameText.setFont(this->font);
	this->NameText.setFillColor(sf::Color::White);
	this->NameText.setCharacterSize(24);
	this->NameText.setPosition(sf::Vector2f(500, 10));
	this->NameText.setString(" TANCHANOCK CHARUNGPATTANANON 64010359 ");*/
}

//Function

const bool Game::running() const
{
	return this->window->isOpen() /*&& this->endGame == false*/;
}

const bool& Game::getEndGame() const
{
	return this->endGame;
}

//Functions
void Game::spawnBall()
{
	//Timer
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->spawnTimer = 0;
		int type = this->randBallType();
		this->ball.push_back(Ball(*this->window, type, &this->enemyTexture[type]));
	}
	if (timer >= 5)
	{
		if (this->spawnTimerMax > 0.1)          
		{
			this->spawnTimerMax -= 0.05;
		}
		this->fallSpeed += 0.1;
		this->timer = 0;
	}
	std::cout << spawnTimer << " / " << timer << std::endl;
}

void Game::updateCollison()
{
	//Check the Collision
	for (size_t i = 0; i < this->ball.size(); i++)
	{
		ball[i].fall(fallSpeed);
		if (this->player.getGlobalBounds().intersects(this->ball[i].getGlobalBounds()))
		{
			switch (this->ball[i].getType())
			{
			case BallTypes::DEFAULT:
				this->points++;    //Add points
				break;
			case BallTypes::DAMAGING:
				this->player.takeDamage(5);
				break;
			case BallTypes::HEALING:
				this->player.gainHealth(1);
				break;
			}

			//Remove the ball
			this->ball.erase(this->ball.begin() + i);
			break;
		}
		else if (this->ball[i].getPosition().y >= 920)
		{
			this->ball.erase(this->ball.begin() + i);
			break;
		}
	}
	
}

const int Game::randBallType() const
{
	int type = BallTypes::DEFAULT;
	
	int randValue = rand() % 100 + 1;
	if (randValue > 60 && randValue <= 80)
		type = BallTypes::DAMAGING;
	else if (randValue > 80 && randValue <= 100)
		type = BallTypes::HEALING;

	return type;
}

void Game::updatePlayer()
{
	this->player.update(this->window);

	if (this->player.getHp() <= 0)
		this->endGame = true;
}

void Game::initBackground()
{
	texturebackground.loadFromFile("Picture/grass.png");
	background.setSize({ 1200,900 });
	background.setPosition(0, 0);
	background.setTexture(&texturebackground);
}

void Game::update()
{
	if (this->endGame == false)
	{
		this->spawnBall();
		this->updatePlayer();
		this->updateCollison();
		this->updateGui();
	}
}

void Game::renderGui(sf::RenderTarget* target)
{
	target->draw(this->guiText);
}

void Game::render()
{
	this->window->clear();

	//Render stuffs
	this->window->draw(background);
	this->player.render(this->window);

	for (auto i : this->ball)
	{
		i.render(*this->window );
	}

	//Render gui
	this->renderGui(this->window);

	//Render end text
	if (this->endGame == true)
		this->window->draw(this->endGameText);


	this->window->display();
}

void Game::updateGui()
{
	std::stringstream ss;

	ss << " POINTS  :  " << this->points << "\n"
		<< " HEALTH  :  " << this->player.getHp() << " / " << this->player.getHpMax() << "\n";

	this->guiText.setString(ss.str());
}


