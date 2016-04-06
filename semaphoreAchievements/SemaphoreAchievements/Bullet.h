#ifndef BULLET_H
#define BULLET_H

class Bullet : public sf::Sprite
{
private:
	sf::Texture bulletTexture;

	sf::Texture rocketRightTexture;

	sf::Texture rocketLeftTexture;

	enum Directions
	{
		RIGHT,
		LEFT
	};
	int currentDirection;

	enum BulletType
	{
		BULLET,
		ROCKET
	};
	int type;

public:
	Bullet(int t, int dir, sf::Vector2f pos);

	~Bullet();

	void Update();
};

#endif