#pragma once
#include <iostream>

#include "../ICommand.h"
#include "../Containers/CoreContainer.h"

class LoginCommand : public virtual ICommand
{
	IUserService& _userService;
public:
	LoginCommand(IUserService& userService) : _userService(userService) {}

	string GetCommandName() override { return  "login"; }

	void Process(UserSession& session) override
	{
		cout << "Login: ";
		string login;
		cin >> login;

		cout << "Password: ";
		string password;
		cin >> password;

		cin.ignore();
		
		User* user = _userService.Login(login, password);
		session.SetUser(*user);
		cout << user->Login << " authorized" << endl;
	}
};

