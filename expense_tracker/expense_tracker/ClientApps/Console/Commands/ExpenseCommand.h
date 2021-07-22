#pragma once
#include "../ICommand.h"
#include "../ServicesContainer.h"

class ExpenseCommand : public virtual IAuthorizedCommand
{
	ITransactionService& _transactionService;
	
public:
	ExpenseCommand(ITransactionService& transactionService)
		: _transactionService(transactionService) {
		
	}

	string GetCommandName() override { return "expense";}

	void ProcessAuthorized(UserSession& session) override
	{
		TransactionModelIn model;
		model.Timestamp = now(); // todo: use console
		model.IsProfit = false;

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
