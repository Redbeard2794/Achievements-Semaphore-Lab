#ifndef COMMAND_H
#define COMMAND_H

class Command
{
public:
	Command(Player* p) : player(p)
	{ 
		std::cout << "Command constructor called." << std::endl;
	}

	virtual ~Command() {}

	virtual void Execute() = 0;

protected:
	Player* player;

};

#endif
