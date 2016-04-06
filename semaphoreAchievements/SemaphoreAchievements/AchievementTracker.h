#ifndef ACHIEVEMENTTRACKER_H
#define ACHIEVEMENTTRACKER_H

#include "Achievement.h"

//rapidxml stuff
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
using namespace rapidxml;
#include <sstream> // std::stringstream
#include <fstream>
class AchievementTracker
{
private:
	std::vector<Achievement*> lockedAchievements;
	std::vector<Achievement*> unlockedAchievements;

	Player* player;

	sf::Clock displayClock;

	sf::Text unlockText;
	sf::Font font;
public:
	AchievementTracker(sf::Font f);
	~AchievementTracker();

	void LoadAchievements();

	void Update();

	void DisplayAchievement(sf::RenderTarget& window);

	bool CheckAchievementUnlocked(std::string name);
};

#endif
