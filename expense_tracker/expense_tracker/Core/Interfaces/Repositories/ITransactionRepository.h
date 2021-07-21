#pragma once
#include "../../Entities/transaction.h"

class ITransactionRepository
{
public:
	virtual int Add(Transaction& entity) = 0;
	virtual Transaction* GetById(int id) = 0;
	virtual vector<Transaction*> GetUserTransactions(int userId) = 0;
};