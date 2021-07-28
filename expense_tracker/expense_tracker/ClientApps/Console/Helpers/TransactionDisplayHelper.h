#pragma once
#include "../../../Core/Entities/transaction.h"
#include "CoutHelper.h"

using namespace CoutHelper;

class TransactionDisplayHelper
{
public:
	inline static string TransactionHeader = "TRANSACTION";
	inline static string TransactionsHeader = "TRANSACTIONS";

	static void OutputTransactions(vector<Transaction*>& transactions, bool includeHeader = true)
	{
		if (includeHeader)
		{
			WriteHeader(TransactionsHeader);
		}

		if (transactions.empty())
		{
			cout << "No records" << endl;
			return;
		}

		for (auto* trans : transactions)
		{
			OutputTransaction(*trans, false);
		}
	}

	static void OutputTransaction(Transaction& transaction, bool includeHeader = true)
	{
		if (includeHeader)
		{
			WriteHeader(TransactionHeader);
		}
		 d = put_money(transaction.Amount, false);
		
		const int nameLen = 10;
		cout << endl;
		WriteParameter("Type", transaction.IsProfit() ? "PROFIT" : "EXPENSE", nameLen);
		WriteParameter("Id", transaction.Id, nameLen);
		WriteParameter("Title", transaction.Title, nameLen);
		WriteParameter("Timestamp", to_date_time_str(transaction.Timestamp), nameLen);
		WriteParameter("Amount", put_money(transaction.Amount, false), nameLen);
	}
};

