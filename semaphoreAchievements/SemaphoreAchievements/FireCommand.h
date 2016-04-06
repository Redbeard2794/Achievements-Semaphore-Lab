#ifndef FIRECOMMAND_H
#define FIRECOMMAND_H

#include "Command.h"

class FireCommand : public Command
{
private:

public:
	FireCommand(Player* p) : Command(p)
	{
		std::cout << "FireCommand constructor called." << std::endl;
	}

	void Execute()
	{
		std::cout << "Fire command exectued." << std::endl;
		player->Fire();
	}
};

#endif
