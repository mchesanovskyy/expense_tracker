#pragma once
#include "FileRepositoryBase.h"
#include "../../../Core/Entities/transaction.h"
#include "../../../Core/Interfaces/Repositories/ITransactionRepository.h"

class FileTransactionRepository : public FileRepositoryBase<Transaction>, public ITransactionRepository 
{
public:
	FileTransactionRepository()
		: FileTransactionRepository(fileNames::TRANSACTION_FILE_NAME, configs::TRANSACTION_ID_KEY)
	{

	}
	
	FileTransactionRepository(const string& fileName, const string& idConfigName)
		: FileRepositoryBase<Transaction>(fileName, idConfigName)
	{
		
	}

	int Add(Transaction& entity) override
	{
		return FileRepositoryBase<Transaction>::Add(entity);
	}

	Transaction* GetById(int id) override
	{
		return FileRepositoryBase<Transaction>::GetById(id);	
	}
	
	vector<Transaction*> GetUserTransactions(int userId) override
	{
		vector<Transaction*> transactions;
		for(auto* record : GetRecords())
		{
			if(record->UserId == userId)
			{
				transactions.push_back(record);
			}
		}
		
		return transactions;
	}

protected:
	virtual Transaction* ToObject(vector<string> parts) override
	{
		return new Transaction(
			stoi(parts[0]),
			stoi(parts[1]),
			parts[2],
			stol(parts[3]),
			stod(parts[4])
		);
	}

	virtual string ToString(Transaction& entity) override
	{
		return join({
			to_string(entity.Id),
			to_string(entity.UserId),
			entity.Title,
			to_string(entity.Timestamp),
			to_string(entity.Amount)
			}, delimiter);
	}

};

