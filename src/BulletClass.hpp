#ifndef BULLETCLASS_H
#define BULLETCLASS_H
#pragma once

class BulletClass
{
public:
	BulletClass(sf::Sprite playerSprite);
	void Draw(sf::RenderWindow& window);
	void Update(float& dt);

	sf::CircleShape shape;
	sf::Vector2f position = sf::Vector2f(shape.getPosition().x, shape.getPosition().y);

	//  Keep this a float incase we want to resize bullets
	float radius = 10;
	float speed = 80.0f;
};
#endif