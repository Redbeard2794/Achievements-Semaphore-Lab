#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	if (rightSheetTexture.loadFromFile("Assets/Player/rightSheet.png")) {}
	else rightSheetTexture.loadFromFile("Assets/Debug.png");

	if (rightIdleTexture.loadFromFile("Assets/Player/rightIdle.png")) {}
	else rightIdleTexture.loadFromFile("Assets/Debug.png");

	if (leftSheetTexture.loadFromFile("Assets/Player/leftSheet.png")) {}
	else leftSheetTexture.loadFromFile("Assets/Debug.png");

	if (leftIdleTexture.loadFromFile("Assets/Player/leftIdle.png")) {}
	else leftIdleTexture.loadFromFile("Assets/Debug.png");

	if (rightJumpTexture.loadFromFile("Assets/Player/jumpRightSheet.png")) {}
	else rightJumpTexture.loadFromFile("Assets/Debug.png");

	if (leftJumpTexture.loadFromFile("Assets/Player/jumpLeftSheet.png")) {}
	else leftJumpTexture.loadFromFile("Assets/Debug.png");

	setTexture(rightIdleTexture);
	setOrigin(rightIdleTexture.getSize().x / 2, rightIdleTexture.getSize().y / 2);
	setPosition(100, 500 - getTexture()->getSize().y/2);

	currentDirection = RIGHT;

	animationTime = 0.13f;

	animationClock.restart();

	moving = false;

	numFrames = 4;

	//set up the texture rectangle
	framePosition = sf::Vector2i(0, 0);

	frameSize = sf::Vector2i(44, 54);

	frame = sf::IntRect(framePosition, frameSize);

	setTextureRect(frame);

	speed = 0;

	grounded = false;
	jumping = false;

	currentWeapon = 0;
}

Player::~Player()
{

}

void Player::Update()
{
	if (moving)
	{
		if (animationClock.getElapsedTime().asSeconds() > animationTime)
		{
			if (framePosition.x < getTexture()->getSize().x - frameSize.x)
				framePosition.x += frameSize.x;//move the frame forward
			else framePosition.x = 0;
			animationClock.restart();
		}

		//reset the texture rectangle
		frameSize = sf::Vector2i(getTexture()->getSize().x / numFrames, getTexture()->getSize().y);
		frame = sf::IntRect(framePosition, frameSize);
		setTextureRect(frame);
		setOrigin(frameSize.x / 2, frameSize.y / 2);
	}

	else
	{
		if (currentDirection == RIGHT && moving == false)
		{
			setTexture(rightIdleTexture);
		}
		if (currentDirection == LEFT && moving == false)
		{
			setTexture(leftIdleTexture);
		}


		frameSize = sf::Vector2i(getTexture()->getSize().x, getTexture()->getSize().y);
		frame = sf::IntRect(framePosition, frameSize);
		setTextureRect(frame);
		setOrigin(frameSize.x / 2, frameSize.y / 2);
		framePosition.x = 0;
	}

	if (!grounded && !jumping)
	{
		setPosition(getPosition().x, getPosition().y + 0.7);
	}

	if (jumping)
	{
		float temp = getTexture()->getSize().y * 1.5;
		if (getPosition().y > (preJumpPos.y - temp))
		{
			setPosition(getPosition().x, getPosition().y - 1);
		}
		else jumping = false;
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		bullets.at(i)->Update();
	}

	Move();
}

void Player::Move()
{
	if (currentDirection == RIGHT && moving == true)
	{
		setPosition(getPosition().x + 1, getPosition().y);
		if(!jumping)
			setTexture(rightSheetTexture);
		else setTexture(rightJumpTexture);
	}

	if (currentDirection == LEFT && moving == true)
	{
		setPosition(getPosition().x - 1, getPosition().y);
		if(!jumping)
			setTexture(leftSheetTexture);
		else setTexture(leftJumpTexture);
	}

}

void Player::Jump()
{
	std::cout << "Player::Jump() called." << std::endl;
	if (grounded)
	{
		preJumpPos = getPosition();
		jumping = true;
	}
}

void Player::Fire()
{
	std::cout << "Player::Fire() called." << std::endl;
	Bullet* b = new Bullet(currentWeapon, currentDirection, getPosition());
	bullets.push_back(b);
}

void Player::SwapWeapon()
{
	std::cout << "Player::SwapWeapon() called." << std::endl;
	if (currentWeapon == 0)
		currentWeapon = 1;
	else currentWeapon = 0;
}

void Player::LurchIneffectively()
{
	std::cout << "Player::LurchIneffectively() called." << std::endl;
}

void Player::CheckCollisionWithGround(sf::FloatRect groundBounds)
{
	if (getGlobalBounds().intersects(groundBounds))
	{
		grounded = true;
		jumping = false;
	}
	else grounded = false;
}

void Player::Draw(sf::RenderTarget& window)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		window.draw(*bullets.at(i));
	}
}

int Player::getCurrentDirection()
{
	return currentDirection;
}

void Player::setCurrentDirection(int d)
{
	currentDirection = d;
}

bool Player::getMove()
{
	return moving;
}

void Player::setMove(bool m)
{
	moving = m;
}

int Player::getCurrentWeapon()
{
	return currentWeapon;
}

