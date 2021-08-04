#pragma once
#include <tgbot/Bot.h>
#include <tgbot/types/Message.h>

#include "../TgUserSession.h"

class ITgBotCommand
{
public:
	virtual string GetName() = 0;
	virtual void Process(TgBot::Bot* bot, TgBot::Message::Ptr message, TgUserSession& session) = 0;
};