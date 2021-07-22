#pragma once
#include "../ICommand.h"
#include "../Exceptions/ExitException.h"

class ExitCommand : public virtual ICommand
{
public:
	string GetCommandName() override
	{
		return "exit";
	}

	void Process(UserSession& session) override
	{
		throw ExitException();
	}
};

