#include "AsteroidClass.hpp"

AsteroidClass::AsteroidClass()
{
	// Initialize asteroid
	this->shape.setRadius(startRadius);
	this->shape.setPosition(100, 100); // Randomize when instantiated
	this->shape.setFillColor(sf::Color::Red);
	x = this->shape.getPosition().x;
	y = this->shape.getPosition().y;
}

void AsteroidClass::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

void AsteroidClass::Update(float& dt)
{
	shape.setPosition(shape.getPosition().x + speed * dt, shape.getPosition().y + speed * dt);
}

void AsteroidClass::OnHit()
{
}