#pragma once
#include "../ITgBotCommand.h"
#include "./Core/CoreContainer.h"

class TgLoginCommand : public ITgBotCommand
{
	IUserService& _userService;

public:
	TgLoginCommand(IUserService& userService) : _userService(userService) {

	}

	string GetName() override { return "/login"; }


	void Process(TgBot::Bot* bot, TgBot::Message::Ptr message, TgUserSession& session) override
	{
		if (session.IsAuthorized())
		{
			bot->getApi().sendMessage(session.GetChatId(), "You are authorized");
			session.ClearCommand();
			return;
		}

		switch (session.GetState())
		{
		case 0:
			bot->getApi().sendMessage(session.GetChatId(), "Login:");
			session.MoveStateNext();
			return;

		case 1:
			session.AddMetadata(message->text);
			bot->getApi().sendMessage(session.GetChatId(), "Password:");
			session.MoveStateNext();
			return;

		case 2:
			session.AddMetadata(message->text);

			LoginUser(bot, session);

			session.ClearCommand();
			return;

		default:
			session.ClearCommand();
			return;
		}
	}


private:
	void LoginUser(TgBot::Bot* bot, TgUserSession& session)
	{
		vector<string> metadata = session.GetMetadata();
		User* user = _userService.Login(metadata[0], metadata[1]);
		session.SetUser(*user);

		bot->getApi().sendMessage(session.GetChatId(), user->Login + " authorized");
	}
};
