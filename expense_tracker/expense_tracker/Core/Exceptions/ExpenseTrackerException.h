#pragma once
class ExpenseTrackerException : public exception
{
public:
	ExpenseTrackerException() : exception() {}
	ExpenseTrackerException(char const* const message) : exception(message) {}
	ExpenseTrackerException(exception& innerException) : exception(innerException) {}
};

