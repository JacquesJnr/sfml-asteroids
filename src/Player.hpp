#include <SFML/Graphics.hpp>

#ifndef PLAYER_H
	#define PLAYER_H
	#pragma once

class Player
{
private:
	float xPos;
	float yPos;
	sf::Vector2f currentPosition;
	sf::Texture* texture;

public:
	Player(float x, float y, sf::Texture texture);
	~Player();
};
#endif