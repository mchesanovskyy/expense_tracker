#pragma once

class Transaction
{
public:
	int Id = 0;
	int UserId  = 0;
	string Title {};
	time_t Timestamp {};
	double Amount = 0;
};

