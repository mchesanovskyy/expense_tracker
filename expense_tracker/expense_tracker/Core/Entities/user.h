#pragma once
#include "EntityBase.h"

class User : public EntityBase
{
public:
	string Login {};
	string PasswordHash {};
	string FirstName {};
	string LastName {};
};

