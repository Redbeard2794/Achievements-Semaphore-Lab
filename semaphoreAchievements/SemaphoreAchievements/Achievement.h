#ifndef ACHIEVEMENT_H
#define ACHIEVEMENT_H

class Achievement : public sf::Sprite
{
private:
	std::string name;//achievement name
	int id;
	bool locked;//is it the achievement unlocked or not
	sf::Texture texture;
	bool displayed;

public:
	/*constructor. params: name, id, locked or not, path for texture to load*/
	Achievement(std::string n, int i, bool l, std::string filePath);

	/*destructor*/
	~Achievement();

	/*Lock the achievement*/
	void Lock();

	/*Unlock the achievement*/
	void Unlock();

	/*Check whether the achievement is locked or unlocked*/
	bool GetLockedStatus();

	/*retrieve the achievement id*/
	int GetId();

	/*retireve the achievement name*/
	std::string GetName();

	bool HasBeenDisplayed();
	void SetDisplayStatus(bool d);
};

#endif
