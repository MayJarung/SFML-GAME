#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

enum BallTypes { DEFAULT = 0, DAMAGING, HEALING, NROFTYPES };

class Ball
{
private:
	sf::CircleShape shape;
	sf::Texture shapeegg;

	int type;

	void initShape(const sf::RenderWindow& window);

public:
	Ball(const sf::RenderWindow& window, int type, sf::Texture* texture);

	//Accessor
	const sf::CircleShape getShape() const;
	const int& getType() const;
	inline const sf::Vector2f getPosition() { return shape.getPosition(); }

	//Functions
	void fall(float speed);
	void render(sf::RenderTarget& target);
	inline sf::FloatRect getGlobalBounds() const { return this->shape.getGlobalBounds(); }
};

