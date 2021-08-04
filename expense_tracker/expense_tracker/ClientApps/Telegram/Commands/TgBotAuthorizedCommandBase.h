#pragma once
#include "ITgBotCommand.h"

class TgBotAuthorizedCommandBase : public virtual ITgBotCommand
{
public:
	virtual void Process(TgBot::Bot* bot, TgBot::Message::Ptr message, TgUserSession& session) override
	{
		if (IsValid(bot, message, session))
		{
			ProcessAuthorized(bot, message, session);
		}
	}

protected:
	virtual bool IsValid(TgBot::Bot* bot, TgBot::Message::Ptr message, TgUserSession& session)
	{
		if (session.IsAuthorized())
		{
			return true;
		}

		bot->getApi().sendMessage(session.GetChatId(), "Please use /login command first");
		session.ClearCommand();
		return false;
	}

	virtual void ProcessAuthorized(TgBot::Bot* bot, TgBot::Message::Ptr message, TgUserSession& session) = 0;
};
