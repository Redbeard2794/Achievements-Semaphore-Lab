#ifndef SWAPWEAPONCOMMAND_H
#define SWAPWEAPONCOMMAND_H

#include "Command.h"

class SwapWeaponCommand : public Command
{
private:

public:
	SwapWeaponCommand(Player* p) : Command(p)
	{
		std::cout << "SwapWeaponCommand constructor called." << std::endl;
	}

	void Execute()
	{
		std::cout << "Swap weapon command exectued." << std::endl;
		player->SwapWeapon();
	}
};

#endif
