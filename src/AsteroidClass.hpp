#ifndef ASTEROIDCLASS_H
#define ASTEROIDCLASS_H
#pragma once

class AsteroidClass
{
public:
	AsteroidClass();
	~AsteroidClass();
	void AsteroidDraw(sf::RenderWindow& window);
	void AsteroidUpdate(float dt);

	sf::CircleShape shape;
	float initialRadius = 200.0f;
	float radius;
	sf::Vector2f velocity;

	// Place texture in main
};
#endif