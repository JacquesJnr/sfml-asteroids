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

std::stringstream playerCoordsX;
std::stringstream playerCoordsY;

bool up;
bool left;
bool right;
bool down;

// Delta time
float dt = 0;
float thrustSpeed = 200.0f;

int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(ScreenX, ScreenY), "Asteroids");

	// Load player Texture
	sf::Texture texture;
	if (!texture.loadFromFile(ASSETS + SPRITES + "Player.png"))
		return EXIT_FAILURE;

	// Define the player sprite and assign the player texture
	sf::Sprite playerSprite(texture);

	// Place the player in the center of the screen
	playerSprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	playerSprite.setPosition(ScreenX / 2, ScreenY / 2);
	playerSprite.setScale(0.3f, 0.3f);

	// Create one asteroid
	sf::CircleShape asteroid;

	// Place the asteroid in the scene
	asteroid.setPosition(300, 0);
	asteroid.setRadius(200);
	asteroid.setPointCount(200);

	// Declare asteroid texture.
	sf::Texture astrTexture;

	// Load the asteroid texture
	if (!astrTexture.loadFromFile(ASSETS + SPRITES + "Asteroid Red.png"))
		return EXIT_FAILURE;

	// Set the asteroid's texture to the image we just loaded
	asteroid.setTexture(&astrTexture);

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

	// Delta time clock and time signature.
	sf::Clock clock;
	sf::Time time;

	// Player Position.
	sf::Vector2f ship(400, 400);

	// Mouse Position.
	sf::Vector2f mousePosition(0, 0);

	// Debug Player Position.
	sf::Text text("X: " + std::to_string(ship.x) + " Y: " + std::to_string(ship.y), font, 20);

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

		// Set coordinate string
		text.setString("X: " + std::to_string(ship.x) + " Y: " + std::to_string(ship.y));

		// Check for upwards input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			ship.y -= thrustSpeed * dt;

		// Check for downwards input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			ship.y += thrustSpeed * dt;

		//Check for left input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			ship.x -= thrustSpeed * dt;

		//Check for right input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			ship.x += thrustSpeed * dt;

		// Restart the clock and get the delta time
		time = clock.restart();
		dt = time.asSeconds();

		// Move player
		playerSprite.setPosition(ship.x, ship.y);

		// Screen Wrapping!
		// Wrap left & right
		if (ship.x >= ScreenX + playerSprite.getScale().x)
			ship.x = 0;

		else if (ship.x <= 0 + playerSprite.getScale().y)
			ship.x = ScreenX;

		// Wrap up and down
		if (ship.y <= 0 - playerSprite.getScale().y)
			ship.y = ScreenY;

		else if (ship.y >= ScreenY + playerSprite.getScale().y)
			ship.y = 0; // Set coordinate string

		// Clear screen
		window.clear();
		//Draw BG
		window.draw(bgSprite);
		// Draw the player
		window.draw(playerSprite);
		//Draw the asteroid
		window.draw(asteroid);
		// Draw the string
		window.draw(text);
		// Update the window
		window.display();
	}
	return EXIT_SUCCESS;
}