#ifndef LURCHINEFFECTIVELYCOMMAND_H
#define LURCHINEFFECTIVELYCOMMAND_H

#include "Command.h"

class LurchIneffectivelyCommand : public Command
{
private:

public:
	LurchIneffectivelyCommand(Player* p) : Command(p)
	{
		std::cout << "LurchIneffectivelyCommand constructor called." << std::endl;
	}

	void Execute()
	{
		std::cout << "Lurch ineffectively command exectued." << std::endl;
		player->LurchIneffectively();
	}
};

#endif
