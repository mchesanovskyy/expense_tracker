#include "stdafx.h"
#include <iostream>
#include "Core/Entities/transaction.h"
#include "Infrastructure/Managers/ConfigManager.h"
#include "Infrastructure/Repositories/File/FileRepositoryBase.h"
#include "Core/Entities/user.h"

class UserRepo : public FileRepositoryBase<User>
{
public:
	UserRepo() : FileRepositoryBase<User>("users.txt", "USER_ID") {}

	virtual User* ToObject(vector<string> parts) override
	{
		User* user = new ::User;
		user->Id = stoi(parts[0]);
		user->Login = parts[1];
		user->PasswordHash = parts[2];
		user->FirstName = parts[3];
		user->LastName = parts[4];
		return user;
	}

	virtual string ToString(User& entity) override
	{
		return join({ 
			std::to_string(entity.Id), 
			entity.Login, 
			entity.PasswordHash,
			entity.FirstName,
			entity.LastName
			}, delimiter);
	}
};

int main()
{
	auto* u = new User;
	u->FirstName = "M";
	u->LastName = "M";
	u->Login = "M";
	u->PasswordHash = "M";

	UserRepo repo;
	cout << repo.Create(*u);
}