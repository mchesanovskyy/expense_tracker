#pragma once
#include "../Entities/user.h"
#include "../Models/SignUpUserModel.h"

class IUserService
{
public:
	virtual User* SignUp(SignUpUserModel signUpModel) = 0;
	virtual User* Login(string login, string password) = 0;
};

