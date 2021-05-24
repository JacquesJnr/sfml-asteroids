#ifndef ASTEROIDCLASS_H
#define ASTEROIDCLASS_H
#pragma once

class AsteroidClass
{
public:
	AsteroidClass();
	void AsteroidDraw(sf::RenderWindow& window);

	sf::CircleShape shape;
	sf::Vector2f velocity;
	sf::Vector2f spawnPos;
	float startRadius = 50.0f;
	float speed;
};
#endif