#include "Player.h"

void Player::initVariables()
{
	this->movementSpeed = 2.f;
	this->hpMax = 10;
	this->hp = hpMax;
}

void Player::initShape()
{
	shapePlayer.loadFromFile("Picture/rabbitship.png");
	this->shape.setTexture(&shapePlayer);
	this->shape.setSize(sf::Vector2f(100.f, 100.f));
}

Player::Player()
{
	this->shape.setPosition(600,850);
	//this->initTexture();
	//this->initSprite();
	this->initVariables();
	this->initShape();
}

Player::~Player()
{

}

//Accessors
const sf::RectangleShape& Player::getShape() const
{
	return this->shape;
}

const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::getHpMax() const
{
	return this->hpMax;
}

//Functions
void Player::takeDamage(const int damage)
{
	if (this->hp > 0)
		this->hp -= damage;

	if (this->hp < 0)
		this->hp = 0;
}

void Player::gainHealth(const int health)
{
	if (this->hp < this->hpMax)
		this->hp += health;

	if (this->hp > this->hpMax)
		this->hp = this->hpMax;
}

void Player::updateInput()
{
	//Keyboard input
	//Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->shape.move(-this->movementSpeed, 0.f);
	}
	//Right
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->shape.move(this->movementSpeed, 0.f);
	}
	//Up
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->shape.move(0.f, -this->movementSpeed);
	}
	//Down
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->shape.move(0.f, this->movementSpeed);
	}
}

void Player::updateWindowBoundsCollision(const sf::RenderTarget * target)
{
	//Left
	if (this->shape.getGlobalBounds().left <= 0.f)
		this->shape.setPosition(0.f, this->shape.getGlobalBounds().top);
	//Right
	if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x)
		this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);
	//Top
	if (this->shape.getGlobalBounds().top <= 0.f)
		this->shape.setPosition(this->shape.getGlobalBounds().left, 0.f);
	//Down
	if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y)
		this->shape.setPosition(this->shape.getGlobalBounds().left, target->getSize().y - this->shape.getGlobalBounds().height);
}

void Player::update(const sf::RenderTarget* target)
{
	this->updateInput();

	//window bound collision
	this->updateWindowBoundsCollision(target);
	
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
