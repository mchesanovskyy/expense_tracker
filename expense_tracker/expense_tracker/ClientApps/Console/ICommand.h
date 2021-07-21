#pragma once

class ICommand
{
public:
	virtual ~ICommand() = default;

	virtual string GetCommandName() = 0;

	virtual void Process() = 0;
};