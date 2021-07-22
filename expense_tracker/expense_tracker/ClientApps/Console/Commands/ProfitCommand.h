#pragma once
#include <iostream>

#include "../ICommand.h"
#include "../ServicesContainer.h"

class ProfitCommand : public virtual IAuthorizedCommand
{
	ITransactionService& _transactionService;
	
public:
	ProfitCommand(ITransactionService& transactionService)
		: _transactionService(transactionService) {
		
	}

	string GetCommandName() override { return "profit";}

	void ProcessAuthorized(UserSession& session) override
	{
		if(!session.IsAuthorized())
		{
			throw ExpenseTrackerException("Unauthorized");
		}

		TransactionModelIn model;
		model.Timestamp = now(); // todo: use console
		model.IsProfit = true;

		cout << "Title:";
		cin >> model.Title;

		cout << "Amount:";
		cin >> model.Amount;

		cin.ignore();
		
		auto trans = _transactionService.Add(session.GetUserId(), model);

		cout << "ID:" << trans->Id << endl;
		cout << "Title:" << trans->Title << endl;
		cout << "Amount:" << trans->Amount << endl;
	}
};