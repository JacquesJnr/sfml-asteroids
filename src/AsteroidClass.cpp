#include "AsteroidClass.hpp"

AsteroidClass::AsteroidClass()
{
	// Generate random coordinates
	std::srand(time(NULL));
	int randX = rand() % 801;
	int randY = rand() % 801;

	// Initialize asteroid
	this->shape.setRadius(startRadius);
	this->shape.setPosition(randX, randY);
	shape.setRotation(rand() % 360);
	x = this->shape.getPosition().x;
	y = this->shape.getPosition().y;
}

void AsteroidClass::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

void AsteroidClass::Update(float& dt)
{
	//shape.setPosition(shape.getPosition().x + speed * dt, shape.getPosition().y + speed * dt);
	velocity = sf::Vector2f(speed * dt, speed * dt);
	shape.move(velocity);
	shape.rotate(20 * dt);

	// Wrap X
	if (shape.getPosition().x > 800 + shape.getRadius())
		shape.setPosition(sf::Vector2f(0 - shape.getRadius() / 2, y));
	if (shape.getPosition().x < 0 - shape.getRadius())
		shape.setPosition(sf::Vector2f(800 + shape.getRadius() / 2, y));

	// Wrap Y
	if (shape.getPosition().y > 800 + shape.getRadius())
		shape.setPosition(sf::Vector2f(x, 0 - shape.getRadius() / 2));
	if (shape.getPosition().y < 0 - shape.getRadius())
		shape.setPosition(sf::Vector2f(x, 800 + shape.getRadius() / 2));
}

void AsteroidClass::OnHit()
{
}