#ifndef PLAYER_H
#define PLAYER_H

#include "Bullet.h"

class Player : public sf::Sprite
{
private:
	sf::Texture leftSheetTexture;
	sf::Texture rightSheetTexture;

	sf::Texture leftIdleTexture;
	sf::Texture rightIdleTexture;

	sf::Texture rightJumpTexture;
	sf::Texture leftJumpTexture;

	float animationTime;

	sf::Clock animationClock;

	int numFrames;//The total number of frames in the sheet

	/*texture rectangle stuff*/
	sf::Vector2i framePosition;
	sf::Vector2i frameSize;
	sf::IntRect frame;

	enum Directions
	{
		RIGHT,
		LEFT
	};
	int currentDirection;

	bool moving;

	bool jumping;
	sf::Vector2f preJumpPos;
	bool grounded;

	int health;

	enum Weapons
	{
		PISTOL,
		ROCKETS
	};
	int currentWeapon;

	std::vector<Bullet*> bullets;

	float speed;

public:
	Player();

	~Player();

	void Update();

	void Move();

	void Jump();

	void Fire();

	void SwapWeapon();

	void LurchIneffectively();

	void CheckCollisionWithGround(sf::FloatRect groundBounds);

	void Draw(sf::RenderTarget& window);

	int getCurrentDirection();

	void setCurrentDirection(int d);

	bool getMove();

	void setMove(bool m);

	int getCurrentWeapon();
};

#endif
