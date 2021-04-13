#include "Player.hpp"

Player::Player(float x, float y, sf::Texture texture)
{
	sf::Sprite playerSprite(texture);
	playerSprite.setPosition(x, y);
	playerSprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	playerSprite.setScale(0.1, 0.1);
	playerSprite.setTexture(texture);
}

Player::~Player()
{
}