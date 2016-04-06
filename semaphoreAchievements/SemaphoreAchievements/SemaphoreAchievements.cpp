//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <iostream> 
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <mutex>
#include <fstream>
#include <string>

////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 

using std::atomic_int;

atomic_int numActiveReaders = 0;//the number of active readers
atomic_int numActiveWriters = 0;//the number of active writers

atomic_int readWriteLock = 1;//lock for access to the imaginary data
atomic_int readerLock = 1;//lock for reader access to numActiveReaders

std::mutex coutMutex;//stop output being weird

atomic_int unlockedAchievements = 0;
atomic_int lockedAchievements = 1;

bool shot = false;

void processReader(int id)//the readers process
{
	while (true)
	{
		//await numActiveReaders = 0
		while (numActiveWriters != 0)
		{
			coutMutex.lock();
			std::cout << "+*+ READER " << id << " WAITING to access data. +*+" << std::endl;
			coutMutex.unlock();
		}

		numActiveReaders = numActiveReaders + 1;

		readerLock -= 1;//P(mutexR)

		if (numActiveReaders == 1)
			readWriteLock -= 1;//P(rw)

							   //if first, get lock
		readerLock += 1;//V(mutexR)

						//read data
		coutMutex.lock();


		//string line;
		//ifstream myfile("letters.txt");
		//if (myfile.is_open())
		//{
		//	while (getline(myfile, line))
		//	{
		//		std::cout << "READER" << id << " is reading file, value: " << line << std::endl;
		//	}
		//	myfile.close();
		//}
		//else cout << "Unable to open 'letters.txt'";

		xml_document<> doc;
		std::ifstream file("Assets/AchievementList.xml");
		std::stringstream buffer;
		buffer << file.rdbuf();
		file.close();
		std::string content(buffer.str());
		doc.parse<0>(&content[0]);

		xml_node<> *pRoot = doc.first_node();

		xml_node<>* achievementList = doc.first_node("AchievementList");
		xml_node<>* achievement = achievementList->first_node("Achievement");

		//load in each npc's information and then create them
		while (achievement != NULL)
		{
			std::string name = "";
			int id = 0;
			bool locked = true;
			std::string texturePath;

			/*Get the name*/
			name = achievement->first_attribute("name")->value();

			locked = std::atoi(achievement->first_node("locked")->value());

			if (!locked)
				unlockedAchievements += 1;

			/*Move onto the next achievement tag*/
			achievement = achievement->next_sibling("Achievement");
		}
		std::cout << "Player has " << unlockedAchievements << " out of " << lockedAchievements << " acheievements unlocked." << std::endl;
		unlockedAchievements = 0;

		coutMutex.unlock();

		readerLock -= 1;//P(mutexR)

		numActiveReaders = numActiveReaders - 1;

		if (numActiveReaders == 0)
			readWriteLock += 1;//V(rw)

							   //if last, release lock
		readerLock += 1;//V(mutexR)
		std::this_thread::sleep_for(1s);
	}
}

void processWriter(std::string aName)//the writers process
{
	while (true)
	{
		//await numActiveReaders = 0 AND numActiveWriters = 0
		while (numActiveReaders != 0 && numActiveWriters != 0)
		{
			coutMutex.lock();
			std::cout << "*+* WRITER WAITING to access data. *+*" << std::endl;
			coutMutex.unlock();
		}

		numActiveWriters += 1;

		readWriteLock = readWriteLock - 1;//P(rw)

		coutMutex.lock();



		//std::cout << "WRITER " << id << " is writing to the file." << std::endl;
		//ofstream myfile("letters.txt");
		//if (myfile.is_open())
		//{
		//	myfile << "WRITER " << id << " was here 2k16.\n";
		//	myfile.close();
		//}
		//else cout << "Unable to open 'letters.txt'";


		xml_document<> doc;
		std::ifstream file("Assets/AchievementList.xml");
		std::stringstream buffer;
		buffer << file.rdbuf();
		file.close();
		std::string content(buffer.str());
		//doc.parse<0>(&content[0]);
		doc.parse<rapidxml::parse_no_data_nodes>(&content[0]);

		xml_node<> *pRoot = doc.first_node();

		xml_node<>* achievementList = doc.first_node("AchievementList");
		xml_node<>* achievement = achievementList->first_node("Achievement");

		while (achievement != NULL)
		{
			bool locked = std::atoi(achievement->first_node("locked")->value());
			if (achievement->first_attribute("name")->value() == aName && locked == true && shot == true && unlockedAchievements == 0)
			{
				int id = std::atoi(achievement->first_node("id")->value());
				std::string text = std::to_string(0);
				const char * t = doc.allocate_string(text.c_str(), strlen(text.c_str()));
				achievement->first_node("locked")->value(t);
				unlockedAchievements += 1;
			}
			/*Move onto the next achievement tag*/
			achievement = achievement->next_sibling("Achievement");
		}

		coutMutex.unlock();

		numActiveWriters -= 1;

		readWriteLock = readWriteLock + 1;//V(rw)
		std::this_thread::sleep_for(1s);
		//std::terminate();
	}
}

/*
vector of achievements that match the achievements in the sql table(read the information for each one in from the table at the start?).
check for achievement condition and whether achievement already unlocked before awarding the achievement(write to table)
read in from table every so often or all time to check unlocked achievements? maybe just after an achievement is unlocked, should give the most up to date info
*/
int main()
{
	thread reader1(std::bind(processReader, 1));
	thread w(std::bind(processWriter, "Shoot!"));
	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Semaphore Implementation");

	window.setVerticalSyncEnabled(true);

	

	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("Assets/background.png");
	sf::Sprite background;
	background.setTexture(backgroundTexture);
	background.setPosition(0, 0);

	//load a font
	sf::Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\GARA.TTF");

	AchievementTracker* achievementTracker = new AchievementTracker(font);
	achievementTracker->LoadAchievements();

	sf::Text currentWeaponText;
	currentWeaponText.setFont(font);
	currentWeaponText.setString("Current Weapon: ");
	currentWeaponText.setPosition(25, 25);
	currentWeaponText.setColor(sf::Color::Red);

	Player* player = new Player();

	Ground* ground = new Ground();

	Command* jumpCommand = new JumpCommand(player);
	Command* fireCommand = new FireCommand(player);
	Command* swapWeaponCommand = new SwapWeaponCommand(player);
	Command* lurchIneffectivelyCommand = new LurchIneffectivelyCommand(player);

	// Start game loop 
	while (window.isOpen())
	{
		// Process events 
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			// Close window : exit 
			if (Event.type == sf::Event::Closed)
				window.close();

			// Escape key : exit 
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				window.close();

			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Space))
			{
				jumpCommand->Execute();
				
			}

			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::F))
			{
				fireCommand->Execute();
				shot = true;
			}

			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::I))
			{
				swapWeaponCommand->Execute();
			}

			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::L))
			{
				lurchIneffectivelyCommand->Execute();
			}
		}

		//prepare frame
		window.clear();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			player->setCurrentDirection(0);
			player->setMove(true);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			player->setCurrentDirection(1);
			player->setMove(true);
		}
		else player->setMove(false);

		player->Update();
		player->CheckCollisionWithGround(ground->getGlobalBounds());

		if (player->getCurrentWeapon() == 0)
			currentWeaponText.setString("Current Weapon: Pistol");
		else if (player->getCurrentWeapon() == 1)
			currentWeaponText.setString("Current Weapon: Rockets");

		window.draw(background);
		window.draw(currentWeaponText);
		window.draw(*ground);
		player->Draw(window);
		window.draw(*player);

		achievementTracker->DisplayAchievement(window);

		// Finally, display rendered frame on screen 
		window.display();
	} //loop back for next frame

	return EXIT_SUCCESS;
}