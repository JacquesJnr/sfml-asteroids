#ifndef ASTEROIDCLASS_H
#define ASTEROIDCLASS_H
#pragma once

class AsteroidClass
{
public:
	AsteroidClass();
	void Draw(sf::RenderWindow& window);
	void Update(float& dt);
	void CollisionUpdate(AsteroidClass& other);
	//void OnHit(BulletClass& bullet);

	sf::CircleShape shape;
	sf::Vector2f velocity;
	sf::Vector2f spawnPos;
	float startRadius = 50.0f;
	int counter;
	float speed = 50.0f;
	bool destroyed;
};
#endif