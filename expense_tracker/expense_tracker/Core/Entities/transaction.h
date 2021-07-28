#pragma once
#include "EntityBase.h"

class Transaction : public EntityBase
{
public:
	int UserId = 0;
	string Title{};
	time_t Timestamp{};
	double Amount = 0;

	Transaction() = default;

	Transaction(const int id, const int userId, const string& title, const time_t timestamp, const double amount) : Transaction()
	{
		Id = id;
		UserId = userId;
		Title = title;
		Timestamp = timestamp;
		Amount = amount;
	}

	bool IsProfit()
	{
		return Amount >= 0;
	}
};

