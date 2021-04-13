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

std::string ASSETS = "content/";
std::string SPRITES = "sprites/";
std::string FONTS = "fonts/";

sf::Vector2f playerPos;
std::stringstream playerCoordsX;
std::stringstream playerCoordsY;

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
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();
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