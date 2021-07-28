#pragma once
#include <iostream>

#include "../../../Core/Entities/user.h"

class UserDisplayHelper
{
public:
	static void OutputUser(User& user)
	{
		cout << "ID:" << user.Id << endl;
		cout << "Login:" << user.Login << endl;
		cout << "FirstName:" << user.FirstName << endl;
	}
};

