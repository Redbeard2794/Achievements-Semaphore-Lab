#include "stdafx.h"
#include "Ground.h"

Ground::Ground()
{
	if(texture.loadFromFile("Assets/ground.png")){}
	else texture.loadFromFile("Assets/Debug.png");
	setTexture(texture);
	setPosition(0, 500);
}

Ground::~Ground()
{

}
