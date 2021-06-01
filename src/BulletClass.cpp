#include "BulletClass.hpp"

BulletClass::BulletClass(sf::Sprite playerSprite, float& rotation)
{
	// Initialize Bullet

	// Set the bullets position to the postition of the player
	shape.setPosition(playerSprite.getPosition().x, playerSprite.getPosition().y);
	shape.setRadius(radius);
	shape.setOrigin(shape.getRadius() / 2, shape.getRadius() / 2);
	shape.setFillColor(sf::Color::Magenta);
	//shape.setRotation(playerSprite.getRotation() - 180);

	// Set the vector of the bullet

	if (rotation > 0)
	{
		bulletVelocity = sf::Vector2f(sin(rotation) * speed, 0);
	}
	else
	{
		bulletVelocity = sf::Vector2f(sin(rotation) * speed, 0);
	}
}
void BulletClass::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}
void BulletClass::Update(float& dt)
{
	shape.move(bulletVelocity * dt);
}