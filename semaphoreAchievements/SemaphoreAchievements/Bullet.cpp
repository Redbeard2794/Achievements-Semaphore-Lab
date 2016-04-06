#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(int t, int dir, sf::Vector2f pos)
{
	currentDirection = dir;

	type = t;

	if (type == BULLET)
	{
		if (bulletTexture.loadFromFile("Assets/bullet.png")) {}
		else bulletTexture.loadFromFile("Assets/Debug.png");
		setTexture(bulletTexture);
		setOrigin(bulletTexture.getSize().x / 2, bulletTexture.getSize().y / 2);
	}
	else if (type == ROCKET)
	{
		if (currentDirection == RIGHT)
		{
			if (rocketRightTexture.loadFromFile("Assets/rocketR.png")) {}
			else rocketRightTexture.loadFromFile("Assets/Debug.png");
			setTexture(rocketRightTexture);
			setOrigin(rocketRightTexture.getSize().x / 2, rocketRightTexture.getSize().y / 2);
		}
		else if (currentDirection == LEFT)
		{
			if (rocketLeftTexture.loadFromFile("Assets/rocketL.png")) {}
			else rocketLeftTexture.loadFromFile("Assets/Debug.png");
			setTexture(rocketLeftTexture);
			setOrigin(rocketLeftTexture.getSize().x / 2, rocketLeftTexture.getSize().y / 2);
		}
	}

	setPosition(pos.x, pos.y-10);
}

Bullet::~Bullet()
{

}

void Bullet::Update()
{
	if (currentDirection == RIGHT)
	{

		setPosition(getPosition().x + 3, getPosition().y);
	}

	else if (currentDirection == LEFT)
	{

		setPosition(getPosition().x - 3, getPosition().y);
	}
}
