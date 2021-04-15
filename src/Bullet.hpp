#ifndef BULLET_H
#define BULLET_H
#pragma once

class Bullet
{
private:
	sf::CircleShape shape;
	float radius = 10.f;
	float bulletSpeed = 100.f;

public:
	Bullet();
	//void Shoot(sf::Vector2f origin, float angle);
	~Bullet();
};
#endif