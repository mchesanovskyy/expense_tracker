#pragma once
#include "TgUserSession.h"
#include "Commands/TgCommands.h"

#include "../../Core/Services/TransactionService.h"
#include "../../Core/Services/UserService.h"
#include "../../Infrastructure/Managers/ConfigManager.h"
#include "../../Infrastructure/Repositories/File/FileTransactionRepository.h"
#include "../../Infrastructure/Repositories/File/FileUserRepository.h"

#include "tgbot/tgbot.h"

class TgBotManager
{
	TgBot::Bot* _bot;
	map<int64_t, TgUserSession*> _sessions;
	vector<ITgBotCommand*> _cmds;

	ITransactionRepository* _transactionRepository = nullptr;
	IUserRepository* _userRepository = nullptr;
	IUserService* _userService = nullptr;
	ITransactionService* _transactionService = nullptr;

public:
	TgBotManager()
	{
		InitDependencies();
		InitializeCommands();
	}

	void Start()
	{
		try
		{
			auto& config = ConfigManager::get_instance();
			const string apiKey = config.GetSetting(configs::BOT_APPID_KEY);
			_bot = new TgBot::Bot(apiKey);

			InitializeBot();

			printf("Bot username: %s\n",
				_bot->getApi().getMe()->username.c_str());

			TgBot::TgLongPoll longPoll(*_bot);

			while (true)
			{
				printf("Long poll started\n");
				longPoll.start();
			}
		}
		catch (TgBot::TgException& e)
		{
			printf("error: %s\n", e.what());
		}
	}

	~TgBotManager()
	{
		delete _transactionService;
		delete _userService;
		delete _userRepository;
		delete _transactionRepository;
	}

private:
	void InitDependencies()
	{
		_transactionRepository = new FileTransactionRepository;
		_userRepository = new FileUserRepository;
		_userService = new UserService(*_userRepository);
		_transactionService = new TransactionService(*_transactionRepository);
	}

	void InitializeCommands()
	{
		_cmds.push_back(new TgPingCommand());
		_cmds.push_back(new TgLoginCommand(*_userService));
		_cmds.push_back(new TgUserTransactionsCommand(*_transactionService));
		_cmds.push_back(new TgProfitTransactionCommand(*_transactionService));
	}
	
	void InitializeBot()
	{
		TgBot::Bot& bot = *_bot;
		
		bot.getEvents().onCommand("start",
			[&bot, this](TgBot::Message::Ptr message)
			{
				bot.getApi().sendMessage(message->chat->id, "Use /login to authorize");
			});

		bot.getEvents()
			.onAnyMessage([&bot, this](TgBot::Message::Ptr message)
				{
					std::int64_t chatId = message->chat->id;

					auto* session = GetOrCreateUserSession(chatId);

					string cmdName = session->GetCommand();
					if (cmdName.empty())
					{
						cmdName = message->text;
					}

					for (auto* cmd : _cmds)
					{
						if (is_equals_ignore_case(cmd->GetName(), cmdName))
						{
							if(session->GetCommand().empty())
							{
								session->SetCommand(cmd->GetName());
							}
							
							cmd->Process(&bot, message, *session);
						}
					}
				});
	};

	TgUserSession* GetOrCreateUserSession(int64_t chatId)
	{
		if (_sessions.find(chatId) == _sessions.end())
		{
			_sessions.insert_or_assign(chatId, new TgUserSession(chatId));
		}

		return _sessions.at(chatId);
	}
};
