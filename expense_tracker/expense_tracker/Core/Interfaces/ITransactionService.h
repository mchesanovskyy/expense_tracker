#pragma once
#include "../Entities/transaction.h"
#include "../Models/TransactionModelIn.h"

class ITransactionService
{
public:
	virtual ~ITransactionService() = default;
	virtual Transaction* Add(int userId, TransactionModelIn& model) = 0;
	virtual vector<Transaction*> GetUserTransactions(int userId) = 0;
	virtual bool Delete(int transactionId) = 0;
};