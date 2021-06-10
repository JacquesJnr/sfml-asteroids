#ifndef BULLETCLASS_H
#define BULLETCLASS_H
#pragma once

class BulletClass
{
public:
	BulletClass(sf::Sprite playerSprite, float& dx, float& dy);
	void Draw(sf::RenderWindow& window);
	void Update(float& dt);

	sf::CircleShape shape;
	sf::Vector2f position = sf::Vector2f(shape.getPosition().x, shape.getPosition().y);

	//  Keep this a float incase we want to resize bullets
	sf::Vector2f bulletVelocity;
	float radius = 10;

	// The player speed is negative because
	float speed = 250.0f;
	sf::Clock timer;
	const float lifetime = 5;
};
#endif