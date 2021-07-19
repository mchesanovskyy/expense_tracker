#pragma once
#include "EntityBase.h"

class Transaction : public EntityBase
{
public:
	int UserId  = 0;
	string Title {};
	time_t Timestamp {};
	double Amount = 0;
};

