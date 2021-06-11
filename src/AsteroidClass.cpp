#include "AsteroidClass.hpp"

AsteroidClass::AsteroidClass()
{
	// Generate random coordinates
	std::srand(time(NULL));
	int randX = rand() % 801;
	int randY = rand() % 801;

	// Initialize asteroid	velocity = sf::Vector2f(speed * dt, speed * dt);
	this->shape.setRadius(startRadius);
	this->shape.setPosition(randX, randY);
	shape.setRotation(rand() % 360);

	float norm = sqrt(randX * randX + randY * randY);
	float signX = randX < 400 ? -1 : 1;
	float signY = randY < 400 ? -1 : 1;

	velocity = sf::Vector2f((float)randX * signX / norm, (float)randY * signY / norm);
}

void AsteroidClass::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

void AsteroidClass::Update(float& dt)
{
	//shape.setPosition(shape.getPosition().x + speed * dt, shape.getPosition().y + speed * dt);

	shape.move(velocity);
	//shape.rotate(20 * dt);
	(void)dt;
	// Wrap X
	if (shape.getPosition().x > 800 + shape.getRadius())
		shape.setPosition(sf::Vector2f(0 - shape.getRadius() / 2, shape.getPosition().y));
	if (shape.getPosition().x < 0 - shape.getRadius())
		shape.setPosition(sf::Vector2f(800 + shape.getRadius() / 2, shape.getPosition().y));

	// Wrap Y
	if (shape.getPosition().y > 800 + shape.getRadius())
		shape.setPosition(sf::Vector2f(shape.getPosition().x, 0 - shape.getRadius() / 2));
	if (shape.getPosition().y < 0 - shape.getRadius())
		shape.setPosition(sf::Vector2f(shape.getPosition().x, 800 + shape.getRadius() / 2));
}

void AsteroidClass::CollisionUpdate(AsteroidClass& other)
{
	static int counter = 10000;

	float dx = other.shape.getPosition().x - shape.getPosition().x;
	float dy = other.shape.getPosition().y - shape.getPosition().y;
	float norm = sqrt(dx * dx + dy * dy);

	if (norm < startRadius * 2 && counter == 0)
	{
		velocity = -velocity;
		counter = 10000;
	}
	if (counter != 0)
	{
		counter--;
	}
}

void AsteroidClass::OnHit()
{
}