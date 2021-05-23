#ifndef ASTEROIDCLASS_H
#define ASTEROIDCLASS_H
#pragma once

class AsteroidClass
{
public:
	AsteroidClass();
	~AsteroidClass();
	sf::CircleShape shape;
	void AsteroidDraw(sf::RenderWindow& window);
};
#endif