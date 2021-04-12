#ifndef GAME_H
#define GAME_H
#pragma once

class Game
{
public:
	Game();
	void Run();

private:
	void ProcessInput();
	void Update(sf::Time deltaTime);
	void Render();

	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

private:
	const sf::Time timePerFrame;

	sf::RenderWindow gameWindow;
	sf::Texture texture;
	sf::Sprite playerSprite;

	bool isMovingUp;
	bool isMovingDown;
	bool isMovingLeft;
	bool isMovingRight;
};
#endif