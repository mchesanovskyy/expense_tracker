#pragma once

#include "FileRepositoryBase.h"
#include "../../../Core/Entities/user.h"
#include "../../../Core/Interfaces/Repositories/IUserRepository.h"

class FileUserRepository : public FileRepositoryBase<User>, public IUserRepository
{
public:
	FileUserRepository() : FileRepositoryBase<User>(fileNames::USER_FILE_NAME, configs::USER_ID_KEY)
	{

	}

	virtual int Add(User& user) override
	{
		return FileRepositoryBase<User>::Add(user);
	}

	virtual User* GetByLogin(string login) override 
	{
	 	auto records = FileRepositoryBase<User>::GetRecords();
		for (auto* record : records)
		{
			if(is_equals_ignore_case(record->Login, login))
			{
				return record;
			}
		}
		return nullptr;
	}

	virtual User* GetById(int id) override {
		return FileRepositoryBase<User>::GetById(id);
	}

protected:

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
			to_string(entity.Id),
			entity.Login,
			entity.PasswordHash,
			entity.FirstName,
			entity.LastName
			}, delimiter);
	}

};
