#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int ScreenX = 800;
int ScreenY = 800;

float dt = 0;
float thrustSpeed = 10.0f;

std::string ASSETS = "content/";
std::string SPRITES = "sprites/";
std::string FONTS = "fonts/";

sf::Vector2f playerPos;
float xPos = 400;
float yPos = 400;

sf::Vector2f spaceship(400, 400);

std::stringstream playerCoordsX;
std::stringstream playerCoordsY;

bool up;
bool left;
bool right;
bool down;

int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(ScreenX, ScreenY), "Asteroids");
	// Load Player Texture
	sf::Texture texture;
	if (!texture.loadFromFile(ASSETS + SPRITES + "Player.png"))
		return EXIT_FAILURE;
	sf::Sprite playerSprite(texture);

	// Place the player in the center of the screen
	playerSprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	playerSprite.setPosition(ScreenX / 2, ScreenY / 2);
	playerSprite.setScale(0.3f, 0.3f);
	playerPos = sf::Vector2f(playerSprite.getPosition().x, playerSprite.getPosition().y);

	// Get the player coordinates for debugging
	playerCoordsX << std::fixed << std::setprecision(2) << playerPos.x;
	playerCoordsY << std::fixed << std::setprecision(2) << playerPos.y;

	// Create BG Texture
	sf::Texture backGroundTexture;
	// Load BG Texture
	if (!backGroundTexture.loadFromFile(ASSETS + SPRITES + "Background.png"))
		return EXIT_FAILURE;
	// Load BG Sprite
	sf::Sprite bgSprite(backGroundTexture);

	// Set BG position
	bgSprite.setOrigin(backGroundTexture.getSize().x / 2, backGroundTexture.getSize().y / 2);
	bgSprite.setPosition(ScreenX / 2, ScreenY / 2);

	// Create a graphical text to display
	sf::Font font;
	if (!font.loadFromFile(ASSETS + FONTS + "Teko-Regular.ttf"))
		return EXIT_FAILURE;
	sf::Text text("X: " + playerCoordsX.str() + " Y: " + playerCoordsY.str(), font, 20);

	// Open game window
	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		sf::Clock deltaClock;
		sf::Time timer;
		while (window.pollEvent(event))
		{

			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();

			// Move the player upwards, pressing up
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				std::cout << "Up" << '\n';
				playerSprite.setPosition(playerSprite.getPosition().x, playerSprite.getPosition().y - thrustSpeed);
			}

			// Move the player downwards, pressing down
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				std::cout << "Up" << '\n';
				playerSprite.setPosition(playerSprite.getPosition().x, playerSprite.getPosition().y + thrustSpeed);
			}

			// If left is pressed.
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				std::cout << "Left" << '\n';
				playerSprite.setPosition(playerSprite.getPosition().x - thrustSpeed, playerSprite.getPosition().y);
			}

			// If right is pressed
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				std::cout << "Right" << '\n';
				playerSprite.setPosition(playerSprite.getPosition().x + thrustSpeed, playerSprite.getPosition().y);
			}

			text.setString("X: " + std::to_string(playerPos.x) + " Y: " + std::to_string(playerPos.y));

			timer = deltaClock.restart();
			dt = timer.asSeconds();

			// Screen Wrapping
			// Wrap left & right
			if (xPos >= ScreenX + playerSprite.getScale().x)
			{
				playerSprite.setPosition(0, playerPos.y);
			}
			else if (xPos <= 0 + playerSprite.getScale().y)
			{
				playerSprite.setPosition(ScreenX, playerPos.y);
			}

			// Wrap up and down
			if (yPos <= 0 - playerSprite.getScale().y)
			{
				playerSprite.setPosition(playerPos.x, ScreenY);
			}
			else if (yPos >= ScreenY + playerSprite.getScale().y)
			{
				playerSprite.setPosition(playerPos.x, 0);
			}

			// Restart the clock and get the delta time

			xPos = playerSprite.getPosition().x;
			yPos = playerSprite.getPosition().y;
			playerPos = sf::Vector2f(xPos, yPos);
		}

		// Clear screen
		window.clear();
		//Draw BG
		window.draw(bgSprite);
		// Draw the player
		window.draw(playerSprite);
		// Draw the string
		window.draw(text);
		// Update the window
		window.display();
	}
	return EXIT_SUCCESS;
}