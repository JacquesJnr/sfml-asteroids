#ifndef ASTEROIDCLASS_H
#define ASTEROIDCLASS_H
#pragma once

class AsteroidClass
{
public:
	AsteroidClass();
	void Draw(sf::RenderWindow& window);
	void Update(float& dt);

	sf::CircleShape shape;
	sf::Vector2f velocity;
	float x;
	float y;
	sf::Vector2f spawnPos;
	float startRadius = 50.0f;
	float speed = 50.0f;
};
#endif