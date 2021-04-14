#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Mouse.hpp>

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
	asteroid.setRadius(50);
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

	// Player Rotation
	sf::Text playerRotation("Player Rot: ", font, 20);
	playerRotation.setPosition(0, 40);
	playerRotation.setFillColor(sf::Color(255, 255, 0, 255));

	// Mouse Position Debug.
	sf::Mouse mouse;
	sf::Vector2i mousePosition;
	sf::Text mouseDebug("Mouse X: 0  Mouse Y: 0", font, 20);
	mouseDebug.setPosition(0, 20);

	//Pi
	const float PI = 3.14159265;

	// Debug Player Position.
	sf::Text text("Player X: " + std::to_string(ship.x) + " Player Y: " + std::to_string(ship.y), font, 20);

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

		// Set Debug coordinate string
		text.setString("Player X: " + std::to_string(ship.x) + " Player Y: " + std::to_string(ship.y));

		// Set mousePosition vector to mouse coords
		mousePosition = mouse.getPosition(window);
		mouseDebug.setString("Mouse X: " + std::to_string(mousePosition.x) + " Mouse Y: " + std::to_string(mousePosition.y));

		// Get rotation of mouse relative to player
		float dx = playerSprite.getPosition().x - mousePosition.x;
		float dy = playerSprite.getPosition().y - mousePosition.y;
		float rotation = (atan2(dy, dx)) * 180 / PI;

		// Set rotation string to current player rotation
		playerRotation.setString("Player Rotation: " + std::to_string(rotation));

		// Check for upwards input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			ship.y -= thrustSpeed * dt;

		// Check for downwards input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			ship.y += thrustSpeed * dt;

		//Check for left input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			ship.x -= thrustSpeed * dt;

		//Check for right input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			ship.x += thrustSpeed * dt;

		// Restart the clock and get the delta time
		time = clock.restart();
		dt = time.asSeconds();

		// Move player
		playerSprite.setPosition(ship.x, ship.y);
		// Set player rotation to that of the mouses rotation
		playerSprite.setRotation(rotation - 90);

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
		// Draw player position debug
		window.draw(text);
		// Draw the mouse position debug
		window.draw(mouseDebug);
		// Draw rotation debug
		window.draw(playerRotation);
		// Update the window
		window.display();
	}
	return EXIT_SUCCESS;
}