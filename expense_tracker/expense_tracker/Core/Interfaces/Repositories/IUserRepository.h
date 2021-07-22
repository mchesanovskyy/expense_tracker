#pragma once
#include "IRepository.h"
#include "../../Entities/user.h"

class IUserRepository : public virtual IRepository<User>
{
public:
	virtual ~IUserRepository() = default;

	virtual User* GetByLogin(string login) = 0;
};

