#pragma once
class TransactionModelIn
{
public:
	string Title{};
	double Amount = 0;
	time_t Timestamp = 0;
	bool IsProfit = true;
};

