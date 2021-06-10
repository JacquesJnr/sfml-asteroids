#include "BulletClass.hpp"

BulletClass::BulletClass(sf::Sprite playerSprite, float& dx, float& dy)
{
	// Initialize Bullet

	// Set the bullets initial properties
	shape.setPosition(playerSprite.getPosition().x, playerSprite.getPosition().y);
	shape.setRadius(radius);
	shape.setOrigin(shape.getRadius() / 2, shape.getRadius() / 2);
	shape.setFillColor(sf::Color::Magenta);

	// Normalise movement vector
	int norm = sqrt(dx * dx + dy * dy);

	// Move the bullet towards the mouse
	// Speed is negative because of the order I put the variables here - Main.cpp, line 157-158
	bulletVelocity.x = -speed * dx / norm;
	bulletVelocity.y = -speed * dy / norm;
}

void BulletClass::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}
void BulletClass::Update(float& dt)
{
	shape.move(bulletVelocity * dt);

	// Wrap X
	if (shape.getPosition().x > 800 + shape.getRadius())
	{
		shape.setPosition(sf::Vector2f(0 - shape.getRadius() / 2, shape.getPosition().y));
	}
	if (shape.getPosition().x < 0 - shape.getRadius())
	{
		shape.setPosition(sf::Vector2f(800 + shape.getRadius() / 2, shape.getPosition().y));
	}

	// Wrap Y
	if (shape.getPosition().y > 800 + shape.getRadius())
	{
		shape.setPosition(sf::Vector2f(shape.getPosition().x, 0 - shape.getRadius() / 2));
	}
	if (shape.getPosition().y < 0 - shape.getRadius())
	{
		shape.setPosition(sf::Vector2f(shape.getPosition().x, 800 + shape.getRadius() / 2));
	}
}