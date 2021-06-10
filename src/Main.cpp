#include <AsteroidClass.hpp>
#include <BulletClass.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Mouse.hpp>

#include <bits/stdc++.h>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

enum GameState
{
	Menu,
	Game,
	End
};

int ScreenX = 800;
int ScreenY = 800;
const uint MAX_ASTEROIDS = 2;
const uint MAX_BULLETS = 3;

std::string ASSETS = "content/";
std::string SPRITES = "sprites/";
std::string FONTS = "fonts/";
std::string AUDIO = "audio/";

std::stringstream playerCoordsX;
std::stringstream playerCoordsY;

//
bool up;
bool left;
bool right;
bool down;

//Pi
const float PI = 3.14159265;

// Player rotation
float playerRot;

// Delta time
float dt = 0;
float thrustSpeedX = 0;
float thrustSpeedY = 0;
float fraction;

// Spawn timer
const float timerTime = 1.5f;
float timer = 0;

GameState state;

// Create Main Menu Texture
sf::Texture mainMenuTexture;

// Create BG Texture
sf::Texture backGroundTexture;

// Craete Player texture.
sf::Texture playerTexture;

// Create asteroid texture.
sf::Texture astrTexture;

// Asteroid Vector
std::vector<AsteroidClass> asteroids = {};

// Bullet Vector
std::vector<BulletClass> bullets = {};

// Bullet
bool hasShot = false;

void ManageAsteroids();
void PewPew(sf::Sprite sprite, float x, float y);

int main()
{
	//----------WINDOW----------

	// Create the main window
	sf::RenderWindow window(sf::VideoMode(ScreenX, ScreenY), "Asteroids");

	//----------TEXTURES & SPRITES----------

	// Offset for player sprite - I use this this compensate for the sprite being miss alligned with the horizontal.
	int spriteOffset = 90;

	// Load Main Menu Texture
	sf::Sprite mainMenu;
	if (!mainMenuTexture.loadFromFile(ASSETS + SPRITES + "Main Menu.png"))
		return EXIT_FAILURE;
	mainMenu.setTexture(mainMenuTexture);

	// Load Player Texture
	sf::Sprite playerSprite;
	if (!playerTexture.loadFromFile(ASSETS + SPRITES + "Player.png"))
		return EXIT_FAILURE;
	playerSprite.setTexture(playerTexture);

	// Load the asteroid texture
	if (!astrTexture.loadFromFile(ASSETS + SPRITES + "Asteroid Red.png"))
		return EXIT_FAILURE;

	// Load BG Texture
	sf::Sprite bgSprite;
	if (!backGroundTexture.loadFromFile(ASSETS + SPRITES + "Background.png"))
		return EXIT_FAILURE;
	bgSprite.setTexture(backGroundTexture);

	// Set BG position
	bgSprite.setOrigin(backGroundTexture.getSize().x / 2, backGroundTexture.getSize().y / 2);
	bgSprite.setPosition(ScreenX / 2, ScreenY / 2);

	//----------FONT----------

	// Load Font - true type font
	sf::Font font;
	if (!font.loadFromFile(ASSETS + FONTS + "Teko-Regular.ttf"))
		return EXIT_FAILURE;

	// Delta time clock and time signature.
	sf::Clock clock;
	sf::Time time;

	// Set Player position
	playerSprite.setOrigin(playerTexture.getSize().x / 2, playerTexture.getSize().y / 2);
	playerSprite.setPosition(ScreenX / 2, ScreenY / 2);
	playerSprite.setScale(0.3f, 0.3f);

	//----------PLAYER----------

	// Player Position.
	sf::Vector2f ship(400, 400);

	// Player Rotation
	sf::Text playerRotation("Player Rot: ", font, 20);
	playerRotation.setPosition(0, 40);
	playerRotation.setFillColor(sf::Color(255, 255, 0, 255));

	// Debug Player Position.
	sf::Text text("Player X: " + std::to_string(ship.x) + " Player Y: " + std::to_string(ship.y), font, 20);

	//----------MOUSE----------

	// Mouse Position Debug.
	sf::Mouse mouse;
	sf::Vector2i mousePosition;
	sf::Text mouseDebug("Mouse X: 0  Mouse Y: 0", font, 20);
	mouseDebug.setPosition(0, 20);

	//----------SCORE----------

	// UI rectangle properties
	sf::RectangleShape uiBox;
	uiBox.setSize(sf::Vector2f(210, 75));
	uiBox.setFillColor(sf::Color::Blue);
	uiBox.setOutlineColor(sf::Color::White);
	uiBox.setOutlineThickness(1.5f);

	// "Score:" text
	sf::Text scoreText("Score: ", font, 32);

	// Score Number Text
	sf::Text scoreDisplay("0", font, 32);

	scoreText.setPosition(590, 20);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setOutlineThickness(2.0f);

	scoreDisplay.setPosition(690, 20);
	scoreDisplay.setFillColor(sf::Color::White);

	uiBox.setPosition(580, 20);

	//----------LIVES----------

	sf::Text livesText("Lives: ", font, 32);
	livesText.setPosition(590, 50);
	livesText.setFillColor(sf::Color::White);
	livesText.setOutlineThickness(2.0f);

	// Open game window
	while (window.isOpen())
	{
		// Set mousePosition vector to mouse coords
		mousePosition = mouse.getPosition(window);
		mouseDebug.setString("Mouse X: " + std::to_string(mousePosition.x) + " Mouse Y: " + std::to_string(mousePosition.y));

		// Get rotation of mouse relative to player
		float dx = playerSprite.getPosition().x - mousePosition.x;
		float dy = playerSprite.getPosition().y - mousePosition.y;

		playerRot = (atan2(dy, dx)) * 180 / PI;

		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();

			// MENU
			if (state == GameState::Menu)
			{
				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Escape)
						window.close();

					if (event.key.code == sf::Keyboard::Space)
						state = GameState::Game;
				}
			}
			// GAME
			else if (state == GameState::Game)
			{
				// Mouse Down
				if (event.type == sf::Event::MouseButtonPressed)
				{
					// Left Mouse Pressed
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						// Instantiate a bullet
						PewPew(playerSprite, dx, dy);
					}
				}
			}
		}

		// Set Debug coordinate string
		text.setString("Player X: " + std::to_string(ship.x) + " Player Y: " + std::to_string(ship.y));

		// Set rotation string to current player rotation
		playerRotation.setString("Player Rotation: " + std::to_string(playerRot));

		const float kForce = 0.1;

		// Check for upwards input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			thrustSpeedY -= kForce;

		// Check for downwards input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			thrustSpeedY += kForce;

		//Check for left input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			thrustSpeedX -= kForce;

		//Check for right input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			thrustSpeedX += kForce;

		thrustSpeedX *= 0.9998f;
		thrustSpeedY *= 0.9998f;
		ship.x += thrustSpeedX * dt;
		ship.y += thrustSpeedY * dt;

		// ENUM STATES
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			state = GameState::Menu;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			state = GameState::Game;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			state = GameState::End;
		}

		// Set player rotation to that of the mouses rotation
		playerSprite.setRotation(playerRot - spriteOffset);

		// Restart the clock and get the delta time
		time = clock.restart();
		dt = time.asSeconds();

		// Run spawn timer
		timer += dt;
		if (timer >= timerTime)
		{
			ManageAsteroids();
		}

		// Move player
		playerSprite.setPosition(ship.x, ship.y);

		// Update Bullet
		for (uint i = 0; i < bullets.size(); i++)
		{
			bullets[i].Update(dt);

			// Limit bullet count to 5
			if (bullets.size() > 4)
			{
				// Destroy the 'oldest' bullet
				bullets.erase(bullets.begin() + 0);
			}
		}
		// Update objects in the asteroid vector
		for (uint i = 0; i < asteroids.size(); i++)
		{
			asteroids[i].Update(dt);
		}

		// Screen Wrapping!
		// Wrap left & right
		if (ship.x >= ScreenX + playerSprite.getScale().x)
			ship.x = 5;

		else if (ship.x <= 2 + playerSprite.getScale().y)
			ship.x = ScreenX;

		// Wrap up and down
		if (ship.y <= 2 - playerSprite.getScale().y)
			ship.y = ScreenY;

		else if (ship.y >= ScreenY + playerSprite.getScale().y)
			ship.y = 5; // Set coordinate string

		switch (state)
		{
			case GameState::Menu:
				window.clear();
				window.draw(mainMenu);
				break;
			case GameState::Game:
				// Clear screen
				window.clear();

				//Draw BG
				window.draw(bgSprite);

				// Draw the player
				window.draw(playerSprite);

				// Score
				window.draw(uiBox);
				window.draw(scoreText);
				window.draw(scoreDisplay);

				//Lives
				window.draw(livesText);

				// Draw bullets
				for (uint i = 0; i < bullets.size(); i++)
				{
					bullets[i].Draw(window);
				}
				// Draw asteroids
				for (uint i = 0; i < asteroids.size(); i++)
				{
					asteroids[i].Draw(window);
				}
				break;
			default:
				break;
		}

		// TEXT DEBUG

		// window.draw(text);
		// // Draw the mouse position debug
		// window.draw(mouseDebug);
		// // Draw rotation debug
		// window.draw(playerRotation);

		// Update the window
		window.display();
	}
	return EXIT_SUCCESS;
}

// Spawn & Destroys Asteroids
void ManageAsteroids()
{
	timer = 0.f;
	if (asteroids.size() < MAX_ASTEROIDS)
	{
		// Create a new Asteroid every 1.5 secs
		AsteroidClass newAsteroid;

		// Set the texture of the asteroid
		newAsteroid.shape.setTexture(&astrTexture);

		// Add asteroid to the asteroids vector
		asteroids.push_back(newAsteroid);

		// Debug
		std::cout << "Spawned " << asteroids.size() << std::endl;
	}
}

// Instantiates a bullet object at the players position
void PewPew(sf::Sprite sprite, float x, float y)
{
	BulletClass newBullet(sprite, x, y);

	// Add the new bullet to the bullets vector for drawing
	bullets.push_back(newBullet);

	// Debug
	std::cout << "Bullets: " << bullets.size() << '\n';
}