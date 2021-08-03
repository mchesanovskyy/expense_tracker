#pragma once
#include "TgBotCommand.h"

class TgPingCommand : public TgBotCommand
{
public:
	string GetName() override { return "/ping"; }
	void Process(TgBot::Bot* bot, TgBot::Message::Ptr message, TgUserSession& session) override
	{
		bot->getApi().sendMessage(session.GetChatId(), "pong");
		session.ClearCommand();
	}
};

class TgLoginCommand : public TgBotCommand
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

class TgUserTransactionsCommand : public TgBotCommand
{
	ITransactionService& _transactionService;
public:
	TgUserTransactionsCommand(ITransactionService& transactionService) : _transactionService(transactionService)
	{

	}

	string GetName() override { return "/transactions"; }

	void Process(TgBot::Bot* bot, TgBot::Message::Ptr message, TgUserSession& session) override
	{
		if (!session.IsAuthorized())
		{
			bot->getApi().sendMessage(session.GetChatId(), "Please use /login command first");
			session.ClearCommand();
			return;
		}

		vector<Transaction*> trans = _transactionService.GetUserTransactions(session.GetUserId());

		stringstream ss;
		for (auto* transaction : trans)
		{
			ss << "Type:" << (transaction->IsProfit() ? "PROFIT" : "EXPENSE") << endl;
			ss << "Id:" << transaction->Id << endl;
			ss << "Title:" << transaction->Title << endl;
			ss << "Amount:" << transaction->Amount << endl;
			ss << "Timestamp:" << to_date_time_str(transaction->Timestamp) << endl << endl;
		}
		bot->getApi().sendMessage(session.GetChatId(), ss.str());
		session.ClearCommand();
	}

};

class TgProfitTransactionsCommand : public TgBotCommand
{
	ITransactionService& _transactionService;
public:
	TgProfitTransactionsCommand(ITransactionService& transactionService)
		: _transactionService(transactionService)
	{

	}

	string GetName() override { return "/profit"; }

	void CreateProfit(TgBot::Bot* bot, TgUserSession& session)
	{
		TransactionModelIn model;
		model.Timestamp = now(); // todo: use console
		model.IsProfit = true;
		auto metadata = session.GetMetadata();
		model.Title = metadata[0];
		model.Amount = stod(metadata[1]);

		auto* transaction = _transactionService.Add(session.GetUserId(), model);
		stringstream ss;
		ss << "Type:" << (transaction->IsProfit() ? "PROFIT" : "EXPENSE") << endl;
		ss << "Id:" << transaction->Id << endl;
		ss << "Title:" << transaction->Title << endl;
		ss << "Amount:" << transaction->Amount << endl;
		ss << "Timestamp:" << to_date_time_str(transaction->Timestamp) << endl << endl;

		bot->getApi().sendMessage(session.GetChatId(), ss.str());
	}

	void Process(TgBot::Bot* bot, TgBot::Message::Ptr message, TgUserSession& session) override
	{
		if (!session.IsAuthorized())
		{
			bot->getApi().sendMessage(session.GetChatId(), "Please use /login command first");
			session.ClearCommand();
			return;
		}


		switch (session.GetState())
		{
		case 0:
			bot->getApi().sendMessage(session.GetChatId(), "Title:");
			session.MoveStateNext();
			return;
		case 1:
			session.AddMetadata(message->text);
			bot->getApi().sendMessage(session.GetChatId(), "Amount:");
			session.MoveStateNext();
			return;
		case 2:
			if (stod(message->text) < 0)
			{
				bot->getApi().sendMessage(session.GetChatId(), "Please enter amount more than 0");
				return;
			}
			session.AddMetadata(message->text);

			CreateProfit(bot, session);

			session.ClearCommand();
			return;
			
		default:
			session.ClearCommand();
		}
	}
};
