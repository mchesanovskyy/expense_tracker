#pragma once
#include "Core/Entities/user.h"

class UserSession
{
	User* _user = nullptr;
public:

	int GetUserId() const
	{
		if(_user == nullptr)
		{
			return 0;
		}
		
		return _user->Id;
	}

	void SetUser(User& user)
	{
		_user = &user;
	}

	bool IsAuthorized() const
	{
		return _user != nullptr && _user->Id > 0;
	}

	void ClearUser() const
	{
		delete _user;
	}
};

