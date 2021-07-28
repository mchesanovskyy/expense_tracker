#pragma once
#include <iostream>

#include "../ICommand.h"
#include "../Containers/CoreContainer.h"
#include "../Helpers/TransactionDisplayHelper.h"

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
		
		auto* trans = _transactionService.Add(session.GetUserId(), model);
		TransactionDisplayHelper::OutputTransaction(*trans);
	}
};