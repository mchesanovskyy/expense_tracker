#pragma once
#include <iostream>
#include "ICommand.h"
#include "Commands/ExitCommand.h"
#include "Commands/SignUpCommand.h"

#include "../../Core/Services/TransactionService.h"
#include "../../Core/Services/UserService.h"
#include "../../Infrastructure/Repositories/File/FileTransactionRepository.h"
#include "../../Infrastructure/Repositories/File/FileUserRepository.h"
#include "Commands/ExpenseCommand.h"
#include "Commands/LoginCommand.h"
#include "Commands/ProfitCommand.h"

class ConsoleManager
{
	vector<ICommand*> _commands;

	ITransactionRepository* _transactionRepository = nullptr;
	IUserRepository* _userRepository = nullptr;
	IUserService* _userService = nullptr;
	ITransactionService* _transactionService = nullptr;
public:
	ConsoleManager()
	{
		InitDependencies();

		// todo: move out of the class
		_commands.push_back(new ExitCommand);
		_commands.push_back(new SignUpCommand(*_userService));
		_commands.push_back(new LoginCommand(*_userService));
		_commands.push_back(new ProfitCommand(*_transactionService));
		_commands.push_back(new ExpenseCommand(*_transactionService));
	}

	void InitDependencies()
	{
		_transactionRepository = new FileTransactionRepository;
		_userRepository = new FileUserRepository;
		_userService = new UserService(*_userRepository);
		_transactionService = new TransactionService(*_transactionRepository);
	}

	~ConsoleManager()
	{
		delete _transactionService;
		delete _userService;
		delete _userRepository;
		delete _transactionRepository;
	}

	void Start()
	{
		UserSession session;
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

				ProcessCmd(cmd, session);

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
			cmd = "";
		}
	}

protected:

	void ProcessCmd(const string& cmd, UserSession& session)
	{
		for (auto* command : _commands)
		{
			if (is_equals_ignore_case(command->GetCommandName(), cmd))
			{
				command->Process(session);
				return;
			}
		}

		cout << "Command '" << cmd << "' not implemented" << endl;
	}
};

