  #include "Ball.h"

void Ball::initShape(const sf::RenderWindow& window)
{
	this->shape.setRadius(static_cast<float>(rand() % 10 + 10));
	switch (this->type)
	{
	case DAMAGING:
		this->shape.setOutlineColor(sf::Color::White);
		this->shape.setOutlineThickness(2.f);
		break;
	case HEALING:
		this->shape.setOutlineColor(sf::Color::White);
		this->shape.setOutlineThickness(2.f);
		break;
	}
	this->shape.setPosition((rand() % 901), -10);
}

Ball::Ball(const sf::RenderWindow& window, int type, sf::Texture* texture)
	: type(type)
{
	this->initShape(window);
	this->shape.setTexture(texture);
}
const sf::CircleShape Ball::getShape() const
{
	return this->shape;
}

const int& Ball::getType() const
{
	return this->type;
}

void Ball::fall(float speed)
{
	shape.move(0, speed);
}

void Ball::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
