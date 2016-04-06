#include "stdafx.h"
#include "Achievement.h"

/*constructor. params: name, id, locked or not, path for texture to load*/
Achievement::Achievement(std::string n, int i, bool l, std::string filePath) : name(n), id(i), locked(l)
{
	if (texture.loadFromFile(filePath)) {}
	else texture.loadFromFile("Assets/Debug.png");
	setTexture(texture);
	setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	displayed = false;
	setPosition(SCREENWIDTH/2, 150);
	scale(2, 2);
}

/*destructor*/
Achievement::~Achievement()
{
	texture.~Texture();
}

/*Lock the achievement*/
void Achievement::Lock()
{
	locked = true;
}

/*Unlock the achievement*/
void Achievement::Unlock()
{
	locked = false;
}

/*Check whether the achievement is locked or unlocked*/
bool Achievement::GetLockedStatus()
{
	return locked;
}

/*retrieve the achievement id*/
int Achievement::GetId()
{
	return id;
}

/*retireve the achievement name*/
std::string Achievement::GetName()
{
	return name;
}

bool Achievement::HasBeenDisplayed()
{
	return displayed;
}

void Achievement::SetDisplayStatus(bool d)
{
	displayed = d;
}
