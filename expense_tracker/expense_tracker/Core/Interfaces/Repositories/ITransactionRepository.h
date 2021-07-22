#pragma once
#include "IRepository.h"
#include "../../Entities/transaction.h"

class ITransactionRepository : public virtual IRepository<Transaction>
{
public:
	virtual ~ITransactionRepository() = default;
	virtual vector<Transaction*> GetUserTransactions(int userId) = 0;
};