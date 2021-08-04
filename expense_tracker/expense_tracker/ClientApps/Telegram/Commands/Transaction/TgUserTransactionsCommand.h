#pragma once
#include "../TgBotAuthorizedCommandBase.h"
#include "./Core/CoreContainer.h"

class TgUserTransactionsCommand : public TgBotAuthorizedCommandBase
{
	ITransactionService& _transactionService;
public:
	TgUserTransactionsCommand(ITransactionService& transactionService) : _transactionService(transactionService)
	{

	}

	string GetName() override { return "/transactions"; }

	void ProcessAuthorized(TgBot::Bot* bot, TgBot::Message::Ptr message, TgUserSession& session) override
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
