#pragma once
#include "../../Entities/user.h"

class IUserRepository
{
public:
	virtual ~IUserRepository() = default;
	virtual int Add(User& user) = 0;
	virtual User* GetByLogin(string login) = 0;
	virtual User* GetById(int id) = 0;
};

