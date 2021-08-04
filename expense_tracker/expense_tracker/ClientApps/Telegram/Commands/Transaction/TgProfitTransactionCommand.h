#pragma once
#include "../TgBotAuthorizedCommandBase.h"
#include "./Core/CoreContainer.h"

class TgProfitTransactionCommand : public TgBotAuthorizedCommandBase
{
	ITransactionService& _transactionService;
public:
	TgProfitTransactionCommand(ITransactionService& transactionService)
		: _transactionService(transactionService)
	{

	}

	string GetName() override { return "/profit"; }
	
	void ProcessAuthorized(TgBot::Bot* bot, TgBot::Message::Ptr message, TgUserSession& session) override
	{
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

protected:
	void CreateProfit(TgBot::Bot* bot, TgUserSession& session) const
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

};
