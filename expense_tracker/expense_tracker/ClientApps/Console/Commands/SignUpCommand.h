#pragma once
#include <iostream>

#include "../ICommand.h"
#include "../Containers/CoreContainer.h"
#include "../Helpers/UserDisplayHelper.h"

class SignUpCommand : public virtual ICommand
{
	IUserService& _userService;

public:
	SignUpCommand(IUserService& userService) : _userService(userService) {

	}

	string GetCommandName() override
	{
		return "signup";
	}

	void Process(UserSession& session) override
	{
		auto model = new SignUpUserModel;
		cout << "Login: ";
		cin >> model->Login;
		
		cout << "Password: ";
		cin >> model->Password;

		cout << "First Name: ";
		cin >> model->FirstName;

		cout << "Last Name: ";
		cin >> model->LastName;

		cin.ignore();

	 	auto* user = _userService.SignUp(*model);
		UserDisplayHelper::OutputUser(*user);
	}
};

