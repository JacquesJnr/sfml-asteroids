#include "AsteroidClass.hpp"

AsteroidClass::AsteroidClass()
{
	// Initialize normal asteroid
	shape.setPosition(100, 100);
	shape.setPosition(sf::Vector2f(100, 100));
	shape.setFillColor(sf::Color::Red);
}

AsteroidClass::~AsteroidClass()
{
}

void AsteroidDraw(sf::RenderWindow& window)
{
}