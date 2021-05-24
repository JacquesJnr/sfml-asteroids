#include "AsteroidClass.hpp"

AsteroidClass::AsteroidClass()
{
	// Initialize normal asteroid
	shape.setRadius(startRadius);
	shape.setPosition(100, 100);
	shape.setFillColor(sf::Color::Red);
}

void AsteroidClass::AsteroidDraw(sf::RenderWindow& window)
{
	window.draw(shape);
}