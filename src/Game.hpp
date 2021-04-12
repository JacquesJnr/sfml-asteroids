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
	void Update();
	void Render();

private:
	sf::RenderWindow gameWindow;
	sf::CircleShape playerShape;
};
#endif