#include <Game.hpp>

Game::Game() :
	gameWindow(sf::VideoMode(800, 800), "Asteroids!"),
	texture(),
	playerSprite()
{
	if (!texture.loadFromFile("sprites/Player.png"))
	{
		// Handle loading error
	}
	playerSprite.setTexture(texture);
	playerSprite.setPosition(100.f, 100.f);
}

// Calls all methods required to load, process and display the game and its window.
void Game::Run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (gameWindow.isOpen())
	{
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			ProcessInput();
			Update(timePerFrame);
		}
		Render();
	}
}

// Polls all inputs by the player through sf::Event obejct
void Game::ProcessInput()
{
	sf::Event event;
	while (gameWindow.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::KeyPressed:
				handlePlayerInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				handlePlayerInput(event.key.code, false);
				break;
			case sf::Event::Closed:
				gameWindow.close();
				break;
			default:
				break;
		}
	}
}

//
void Game::Update(sf::Time deltaTime)
{
	sf::Vector2f movement(0.f, 0.f);
	if (isMovingUp)
		movement.y -= 1.f;
	if (isMovingDown)
		movement.y += 1.f;
	if (isMovingLeft)
		movement.x -= 1.f;
	if (isMovingRight)
		movement.x += 1.f;

	playerSprite.move(movement * deltaTime.asSeconds());
}

// Refreshes & draws the game window
void Game::Render()
{
	gameWindow.clear();
	gameWindow.draw(playerSprite);
	gameWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	// Checks if the player is moving forward
	if (key == sf::Keyboard::W || key == sf::Keyboard::Up)
	{
		isMovingUp = isPressed;
	}

	if (key == sf::Keyboard::S || key == sf::Keyboard::Down)
	{
		isMovingDown = isPressed;
	}

	else if (key == sf::Keyboard::A || key == sf::Keyboard::Left)
	{
		isMovingLeft = isPressed;
	}

	else if (key == sf::Keyboard::D || key == sf::Keyboard::Right)
	{
		isMovingRight = isPressed;
	}
}
