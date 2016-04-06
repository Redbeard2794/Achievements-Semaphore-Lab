#ifndef JUMPCOMMAND_H
#define JUMPCOMMAND_H

#include "Command.h"

class JumpCommand : public Command
{
private:
	
public:
	JumpCommand(Player* p) : Command(p)
	{
		std::cout << "JumpCommand constructor called." << std::endl;
	}

	void Execute() 
	{ 
		std::cout << "Jump command exectued." << std::endl;
		player->Jump();
	}
};

#endif
