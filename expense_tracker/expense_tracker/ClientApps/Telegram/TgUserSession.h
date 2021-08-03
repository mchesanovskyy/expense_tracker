#pragma once
#include "../../Core/Entities/user.h"

class TgUserSession
{
	User* _user = nullptr;
	std::int64_t _chatId;

	string _command = {};
	int _state = 0;
	vector<string> _metadata;

public:

	TgUserSession(std::int64_t chatId)
		: _chatId(chatId) {
	}

	vector<string> GetMetadata()
	{
		return _metadata;
	}

	void AddMetadata(string value)
	{
		_metadata.push_back(value);
	}

	int GetState()
	{
		return _state;
	}
	
	void MoveStateNext()
	{
		_state++;
	}

	void ClearCommand()
	{
		_command = {};
		_state = 0;
		_metadata.clear();
	}
	
	std::int64_t GetChatId()
	{
		return _chatId;
	}

	void SetCommand(string command)
	{
		_command = command;
	}

	string GetCommand() const
	{
		return _command;
	}
	
	int GetUserId() const
	{
		if (_user == nullptr)
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

