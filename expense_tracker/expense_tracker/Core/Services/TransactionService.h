#pragma once
#include "../Interfaces/ITransactionService.h"
#include "../Interfaces/Repositories/ITransactionRepository.h"

class TransactionService : public ITransactionService
{
	ITransactionRepository* _repository;
	
public:
	TransactionService(ITransactionRepository& repository)
		: _repository(&repository)
	{
		
	}

	Transaction* Add(int userId, TransactionModelIn& model) override
	{
		const auto transaction = new Transaction;
		transaction->Amount = model.IsProfit
			? model.Amount
			: model.Amount * -1;
		transaction->Timestamp = model.Timestamp;
		transaction->Title = model.Title;
		transaction->UserId = userId;

		const int createdTransId = _repository->Add(*transaction);
		return _repository->GetById(createdTransId);
	}

	vector<Transaction*> GetUserTransactions(int userId) override
	{
		return _repository->GetUserTransactions(userId);
	}

	bool Delete(int transactionId) override
	{
	 	return _repository->Delete(transactionId);
	}
};

