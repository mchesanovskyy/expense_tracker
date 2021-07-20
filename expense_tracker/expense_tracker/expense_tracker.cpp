#include "stdafx.h"
#include <iostream>
#include "Core/Entities/transaction.h"

int main()
{
	Transaction t;
	cout << ++t.Amount;
}
