#pragma once
#include <iostream>
#include <filesystem>

#include "Core/Interfaces/IUserService.h"
#include "Core/Services/UserService.h"
#include "Infrastructure/Repositories/File/FileUserRepository.h"

class UserServiceTests
{
	const string _fileName = "users.test";
	const string _idParameters = "USER_TEST_ID";

public:
	void Run()
	{
		ClearTestData();
		IUserService* service = nullptr;
		try
		{
			service = InitDependencies();
			
			SignUpShouldPass(*service);
			LoginShouldPass(*service);
		}
		catch (exception& ex)
		{
			cout << ex.what() << endl;
		}
		catch (...)
		{
			cout << "Unknown error. Check in Debug Mode" << endl;
		}

		delete service;
		ClearTestData();
	}

private:
	void ClearTestData()
	{
		try {
			if (filesystem::remove(_fileName))
				cout << "file " << _fileName << " deleted." << endl;
			else
				cout << "file " << _fileName << " not found." << endl;
		}
		catch (const std::filesystem::filesystem_error& err) {
			std::cout << "filesystem error: " << err.what() << endl;
		}
	}

	IUserService* InitDependencies()
	{
		auto* repo = new FileUserRepository(_fileName, _idParameters);
		return new UserService(*repo);
	}

	void SignUpShouldPass(IUserService& service)
	{
		cout << endl << __FUNCTION__ << endl;
		
		auto user = new SignUpUserModel;
		user->Login = "login";
		user->Password = "pass";
		user->FirstName = "M";
		user->LastName = "C";

		auto createdUser = service.SignUp(*user);
		cout << createdUser->Id << endl;
		cout << createdUser->Login << endl;
	}

	void LoginShouldPass(IUserService& service)
	{
		cout << endl << "Login_ShouldPass" << endl;

		auto* user = service.Login("login", "pass");
		cout << user->Id << endl;
		cout << user->Login << endl;
	}
};

