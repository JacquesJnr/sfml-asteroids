#include "BulletClass.hpp"

BulletClass::BulletClass(sf::Sprite playerSprite)
{
	// Initialize Bullet

	// Set the bullets position to the postition of the player
	shape.setPosition(playerSprite.getPosition().x, playerSprite.getPosition().y);
	shape.setRadius(radius);
	shape.setOrigin(radius / 2, radius / 2);
	shape.setFillColor(sf::Color::Magenta);
	shape.setRotation(playerSprite.getRotation());
}
void BulletClass::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}
void BulletClass::Update(float& dt)
{
	sf::Vector2f velocity = sf::Vector2f(speed * dt, speed * dt);
	shape.move(velocity);
}