#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <iostream>

class Player
{
private:
	//sf::Sprite sprite;
	//sf::Texture texture;
	sf::RectangleShape shape;
	sf::Texture shapePlayer;

	int hp;
	int hpMax;
	float movementSpeed;

	//Private Funtions
	//void initTexture();
	//void initSprite();
	void initVariables();
	void initShape();

public:
	Player();
	virtual ~Player();
	
	//Accessors
	const sf::RectangleShape& getShape() const;
	const int& getHp() const;
	const int& getHpMax() const;


	//Functions
	void takeDamage(const int damage);
	void gainHealth(const int health);

	void updateInput();
	void updateWindowBoundsCollision(const sf::RenderTarget* target);
	void update(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);

	inline sf::FloatRect getGlobalBounds() const { return this->shape.getGlobalBounds(); }
};

