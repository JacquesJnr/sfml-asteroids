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
const uint MAX_ASTEROIDS = 10;
const uint MAX_BULLETS = 3;

std::string ASSETS = "content/";
std::string SPRITES = "sprites/";
std::string FONTS = "fonts/";
std::string AUDIO = "audio/";

std::stringstream playerCoordsX;
std::stringstream playerCoordsY;

//Pi
const float PI = 3.14159265;

// Player rotation
float playerRot;

//SCORE
int score = 0;
int hitCount = 0;

// Delta time
float dt = 0;
float thrustSpeedX = 0;
float thrustSpeedY = 0;
float fraction;

// Spawn timer
const float timerTime = 1.5f;
float timer = 0;

// Game Timer
sf::Clock gameClock;
const float gameTime = 30;
sf::Text timerText;
sf::Text timerDisplay;

GameState state;

// Create Main Menu Texture
sf::Texture mainMenuTexture;

// Create game bacckground Texture
sf::Texture backGroundTexture;

// Create Game Over texture
sf::Texture gameOverTexture;

// Craete Player texture.
sf::Texture playerTexture;

// Create asteroid textures
sf::Texture bigAsteroid;
sf::Texture medAsteroid;
sf::Texture smallAsteroid;

// Asteroid Vector
std::vector<AsteroidClass> asteroids = {};

// Bullet Vector
std::vector<BulletClass> bullets = {};

// Bullet
bool hasShot = false;

void Start(sf::Sprite player);
void ManageAsteroids();
void PewPew(sf::Sprite sprite, float x, float y);

int main()
{
	//----------WINDOW----------

	// Create the main window
	sf::RenderWindow window(sf::VideoMode(ScreenX, ScreenY), "Asteroids");
	window.setFramerateLimit(144);

	//----------TEXTURES & SPRITES----------

	// Offset for player sprite - I use this this compensate for the sprite being miss alligned with the horizontal.
	int spriteOffset = 90;

	// Load Main Menu Texture
	sf::Sprite mainMenu;
	if (!mainMenuTexture.loadFromFile(ASSETS + SPRITES + "Main Menu.png"))
		return EXIT_FAILURE;
	mainMenu.setTexture(mainMenuTexture);

	// Load Game Background Texture
	sf::Sprite bgSprite;
	if (!backGroundTexture.loadFromFile(ASSETS + SPRITES + "Background.png"))
		return EXIT_FAILURE;
	bgSprite.setTexture(backGroundTexture);

	// Load Game Over Background Texture
	sf::Sprite gameOverBg;
	if (!gameOverTexture.loadFromFile(ASSETS + SPRITES + "Game Over.png"))
		return EXIT_FAILURE;
	gameOverBg.setTexture(gameOverTexture);

	// Load Player Texture
	sf::Sprite playerSprite;
	if (!playerTexture.loadFromFile(ASSETS + SPRITES + "Player.png"))
		return EXIT_FAILURE;

	// Apply a texture to the player sprite
	playerSprite.setTexture(playerTexture);

	// Load the asteroid textures
	if (!bigAsteroid.loadFromFile(ASSETS + SPRITES + "Asteroid Red.png"))
		return EXIT_FAILURE;
	if (!medAsteroid.loadFromFile(ASSETS + SPRITES + "Asteroid Blue.png"))
		return EXIT_FAILURE;
	if (!smallAsteroid.loadFromFile(ASSETS + SPRITES + "Asteroid Yellow.png"))
		return EXIT_FAILURE;

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

	//---------MUSIC---------

	sf::Music music;

	if (!music.openFromFile(ASSETS + AUDIO + "8bitPresentation-David_Fesliyan.wav"))
		return EXIT_FAILURE;

	music.play();
	music.setVolume(0.5f);

	//----------SFX------------

	sf::SoundBuffer shootBuffer;
	if (!shootBuffer.loadFromFile(ASSETS + AUDIO + "shoot.wav"))
		return EXIT_FAILURE;
	sf::Sound shootSound;
	shootSound.setBuffer(shootBuffer);

	sf::SoundBuffer thrustBuffer;
	if (!thrustBuffer.loadFromFile(ASSETS + AUDIO + "thruster.wav"))
		return EXIT_FAILURE;
	sf::Sound thrusterSound;
	thrusterSound.setBuffer(thrustBuffer);

	sf::SoundBuffer startGameBuffer;
	if (!startGameBuffer.loadFromFile(ASSETS + AUDIO + "startgame.wav"))
		return EXIT_FAILURE;
	sf::Sound playSound;
	playSound.setBuffer(startGameBuffer);

	sf::SoundBuffer explodeBuffer;
	if (!explodeBuffer.loadFromFile(ASSETS + AUDIO + "asteroidexplosion1.wav"))
		return EXIT_FAILURE;
	sf::Sound explodeSound;
	explodeSound.setBuffer(explodeBuffer);

	//----------PLAYER----------

	// Set Player position
	playerSprite.setOrigin(playerTexture.getSize().x / 2, playerTexture.getSize().y / 2);
	playerSprite.setPosition(ScreenX / 2, ScreenY / 2);
	playerSprite.setScale(0.3f, 0.3f);

	// Player Position for debug.
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

	// Lives positions
	sf::Vector2f livePos1(660, 50);
	sf::Vector2f livePos2(700, 50);
	sf::Vector2f livePos3(740, 50);

	sf::Sprite live1, live2, live3;
	live1.setTexture(playerTexture);
	live1.setScale(0.15f, 0.15f);
	live1.setPosition(livePos1);
	live2.setTexture(playerTexture);
	live2.setScale(0.15f, 0.15f);
	live2.setPosition(livePos2);
	live3.setTexture(playerTexture);
	live3.setScale(0.15f, 0.15f);
	live3.setPosition(livePos3);

	//----------TIMER---------
	gameClock.restart();

	timerText.setString("Time: ");
	timerText.setFont(font);
	timerText.setPosition(350, 20);
	timerText.setFillColor(sf::Color::Black);

	timerDisplay.setFont(font);
	timerDisplay.setPosition(420, 20);
	timerDisplay.setFillColor(sf::Color::Black);

	sf::RectangleShape timerBox;
	timerBox.setSize(sf::Vector2f(200, 75));
	timerBox.setPosition(340, 20);
	timerBox.setFillColor(sf::Color::Yellow);
	timerBox.setOutlineColor(sf::Color::White);
	timerBox.setOutlineThickness(1.5f);

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
				Start(playerSprite);
				ship.x = 400;
				ship.y = 400;
				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Escape)
						window.close();

					if (event.key.code == sf::Keyboard::Space)
					{
						state = GameState::Game;
						playSound.play();
					}
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
						shootSound.play();
					}

					if (event.type == sf::Event::KeyPressed)
					{
						if (event.key.code == sf::Keyboard::Escape)
						{
							state = GameState::Menu;
						}
					}
				}
			}
			// GAME OVER
			else
			{
				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Escape)
						window.close();

					if (event.key.code == sf::Keyboard::Space)
					{
						state = GameState::Menu;
					}
					if (music.getStatus() == music.Stopped)
						music.play();
				}
			}
		}

		// Set Debug coordinate string
		text.setString("Player X: " + std::to_string(ship.x) + " Player Y: " + std::to_string(ship.y));

		// Set rotation string to current player rotation
		playerRotation.setString("Player Rotation: " + std::to_string(playerRot));

		const float kForce = 3.5;

		// Check for upwards input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			thrustSpeedY -= kForce;
			if (thrusterSound.getStatus() == thrusterSound.Stopped)
			{
				thrusterSound.play();
			}
		}
		// Check for downwards input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			thrustSpeedY += kForce;
			if (thrusterSound.getStatus() == thrusterSound.Stopped)
			{
				thrusterSound.play();
			}
		}

		//Check for left input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			thrustSpeedX -= kForce;
			if (thrusterSound.getStatus() == thrusterSound.Stopped)
			{
				thrusterSound.play();
			}
		}

		//Check for right input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			thrustSpeedX += kForce;
			if (thrusterSound.getStatus() == thrusterSound.Stopped)
			{
				thrusterSound.play();
			}
		}

		thrustSpeedX *= 0.998f;
		thrustSpeedY *= 0.998f;
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

			for (uint i = 0; i < bullets.size(); i++)
			{
				for (uint j = 0; j < asteroids.size(); j++)
				{
					float dx = bullets[i].shape.getPosition().x - asteroids[j].shape.getPosition().x;
					float dy = bullets[i].shape.getPosition().y - asteroids[j].shape.getPosition().y;
					float norm = sqrt(dx * dx + dy * dy);

					if (norm < 10 + 50 && !asteroids[j].isHit)
					{
						asteroids[j].isHit = true;
						explodeSound.play();
						score += 50;
					}
				}
			}
		}

		for (uint i = 0; i < asteroids.size(); i++)
		{
			for (uint j = 0; j < asteroids.size(); j++)
			{
				if (j != i)
				{
					asteroids[i].CollisionUpdate(asteroids[j]);
				}
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

		scoreDisplay.setString(std::to_string(score));
		timerDisplay.setString(std::to_string(gameTime - gameClock.getElapsedTime().asSeconds()));

		// Check for the timer being < 0
		if (gameTime - gameClock.getElapsedTime().asSeconds() <= 0)
		{
			state = GameState::End;
		}

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
				window.draw(live1);
				window.draw(live2);
				window.draw(live3);

				// Timer
				window.draw(timerBox);
				window.draw(timerText);
				window.draw(timerDisplay);

				// Draw bullets
				for (uint i = 0; i < bullets.size(); i++)
				{
					bullets[i].Draw(window);
				}
				// Draw asteroids
				hitCount = 0;
				for (uint i = 0; i < asteroids.size(); i++)
				{
					if (!asteroids[i].isHit)
					{
						asteroids[i].Draw(window);
					}

					if (asteroids[i].isHit)
					{
						hitCount++;
					}
				}
				// if (hitCount == MAX_ASTEROIDS)
				// {
				// 	Start(playerSprite);
				// }
				break;
			case GameState::End:
				window.clear();
				window.draw(gameOverBg);
				window.draw(uiBox);
				window.draw(scoreText);
				window.draw(scoreDisplay);
				music.stop();
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

// Initialise the game
void Start(sf::Sprite player)
{
	player.setPosition(ScreenX / 2, ScreenY / 2);
	score = 0;
	hitCount = 0;
	gameClock.restart();
	bullets.clear();
	asteroids.clear();
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
		newAsteroid.shape.setTexture(&bigAsteroid);

		// Set the origin of the asteroid
		newAsteroid.shape.setOrigin(newAsteroid.shape.getTexture()->getSize().x / 2, newAsteroid.shape.getTexture()->getSize().y / 2);

		// Add asteroid to the asteroids vector
		asteroids.push_back(newAsteroid);

		// Debug

		std::cout << "Spawned " << asteroids.size() << " asteroids" << std::endl;
	}
}

// Instantiates a bullet object at the players position
void PewPew(sf::Sprite sprite, float x, float y)
{
	BulletClass newBullet(sprite, x, y);

	// Add the new bullet to the bullets vector for drawing
	bullets.push_back(newBullet);

	// Debug
	//std::cout << "Bullets: " << bullets.size() << '\n';
}