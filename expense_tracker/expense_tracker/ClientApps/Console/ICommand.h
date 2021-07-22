#pragma once
#include "UserSession.h"

class ICommand
{
public:
	virtual ~ICommand() = default;

	virtual string GetCommandName() = 0;

	virtual void Process(UserSession& session) = 0;
};


class IAuthorizedCommand : public virtual ICommand
{

public:
	virtual void Process(UserSession& session) override
	{
		Validate(session);
		ProcessAuthorized(session);
	}

protected:
	virtual void Validate(UserSession& session)
	{
		if (!session.IsAuthorized())
		{
			throw ExpenseTrackerException("Unauthorized");
		}
	}

	virtual void ProcessAuthorized(UserSession& session) = 0;
};
