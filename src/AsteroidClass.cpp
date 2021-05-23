#include "AsteroidClass.hpp"

AsteroidClass::AsteroidClass()
{
	// Initialize normal asteroid
	shape.setPosition(100, 100);
	shape.setRadius(this->initialRadius);
	shape.setPosition(sf::Vector2f(100, 100));
	shape.setFillColor(sf::Color::Red);
}

AsteroidClass::~AsteroidClass()
{
}

void AsteroidClass::AsteroidDraw(sf::RenderWindow& window)
{
	// Draw an asteroid on the current instace of the game window
	window.draw(shape);
}

void AsteroidClass::AsteroidUpdate(float dt)
{
	// Store the current position as a vector2 and multiply it by delta time
	sf::Vector2f currentPos = sf::Vector2f(shape.getPosition().x * dt, shape.getPosition().y * dt);

	// Set the position of the asteroid each frame
	shape.setPosition(currentPos.x + 20.0f, currentPos.y + 20.0f);
}