#pragma once
#include "../ITgBotCommand.h"

class TgPingCommand : public ITgBotCommand
{
public:
	string GetName() override { return "/ping"; }

	void Process(TgBot::Bot* bot, TgBot::Message::Ptr message, TgUserSession& session) override
	{
		bot->getApi().sendMessage(session.GetChatId(), "pong");
		session.ClearCommand();
	}
};

