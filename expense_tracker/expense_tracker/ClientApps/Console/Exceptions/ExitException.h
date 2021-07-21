#pragma once
class ExitException : public  exception
{
public:
	ExitException() : exception() {}
	explicit ExitException(char const* const message) : exception(message) {}
	explicit ExitException(exception& innerException) : exception(innerException) {}
};

