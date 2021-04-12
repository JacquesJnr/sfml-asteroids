#include <Game.hpp>

Game::Game() :
	gameWindow(sf::VideoMode(800, 800), "Asteroids!"),
	playerShape()
{
	playerShape.setRadius(40.f);
	playerShape.setPosition(100.f, 100.f);
	playerShape.setFillColor(sf::Color::Magenta);
}

void Game::Run()
{
	while (gameWindow.isOpen())
	{
		ProcessInput();
		Update();
		Render();
	}
}

void Game::ProcessInput()
{
	sf::Event event;
	while (gameWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			gameWindow.close();
	}
}

void Game::Update()
{
}

void Game::Render()
{
	gameWindow.clear();
	gameWindow.draw(playerShape);
	gameWindow.display();
}
