#pragma once
#include <iostream>
#include "ICommand.h"
#include "Commands/ExitCommand.h"

class ConsoleManager
{
	vector<ICommand*> _commands;
public:
	ConsoleManager()
	{
		// todo: register commands
		// todo: move out of the class
		_commands.push_back(new ExitCommand);
	}
	
	void Start()
	{
		string cmd;
		auto runNextIteration = true;
		while (runNextIteration)
		{
			try
			{
				if (empty(cmd))
				{
					cout << "CMD:> ";
					getline(cin, cmd);
				}

				ProcessCmd(cmd);
				cmd = "";

				cout << endl;
			}
			catch (ExitException& e)
			{
				runNextIteration = false;
			}
			catch (ExpenseTrackerException& e)
			{
				cout << e.what() << endl;
			}
			catch (exception& e)
			{
				cout << e.what() << endl;
			}
			catch (...)
			{
				cout << "Something went wrong" << endl;
			}
		}
	}

protected:

	void ProcessCmd(const string& cmd)
	{
		for (auto* command : _commands)
		{
			if (is_equals_ignore_case(command->GetCommandName(), cmd))
			{
				command->Process();
				return;
			}
		}

		cout << "Command '" << cmd << "' not implemented" << endl;
	}
};

