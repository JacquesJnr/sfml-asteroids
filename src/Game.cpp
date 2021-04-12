#include "Game.h"

Game::Game() :
	mWindow(sf::VideoMode(640, 480), "SFML Application"),
	mPlayer()
{
	mPlayer.setRadius(40.f);
	mPlayer.setPosition(100.f, 100.f);
	mPlayer.setFillColor(sf::Color::Cyan);
}
void Game::run()
{
	while (mWindow.isOpen())
	{
		processEvents();
		update();
		render();
	}
}