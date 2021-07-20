#pragma once
#include "../Interfaces/IUserService.h"
#include "../Interfaces/Repositories/IUserRepository.h"

class UserService : public IUserService
{
	IUserRepository* _userRepository;

public:
	UserService(IUserRepository& userRepository)
	{
		_userRepository = &userRepository;
	}

	virtual User* SignUp(SignUpUserModel signUpModel) override
	{
		if (signUpModel.Login.empty())
		{
			throw ExpenseTrackerException("Login can't be empty");
		}

		if (signUpModel.Password.empty())
		{
			throw ExpenseTrackerException("Password can't be empty");
		}

		User* userByLogin = _userRepository->GetByLogin(signUpModel.Login);
		if (userByLogin != nullptr)
		{
			throw ExpenseTrackerException("Login already used");
		}

		User* user = Transform(signUpModel);
		int createdUserId = _userRepository->Add(*user);

		return _userRepository->GetById(createdUserId);
	}

	virtual User* Login(string login, string password) override
	{
		if (login.empty())
		{
			throw ExpenseTrackerException("Login can't be empty");
		}

		if (password.empty())
		{
			throw ExpenseTrackerException("Password can't be empty");
		}

		User* userByLogin = _userRepository->GetByLogin(login);
		if(userByLogin == nullptr)
		{
			throw ExpenseTrackerException("Login/Password is invalid");
		}

		string pwdHash = hash_helper::create_sha256_hash_str(password);
		if(pwdHash != userByLogin->PasswordHash)
		{
			throw ExpenseTrackerException("Login/Password is invalid");	
		}

		return userByLogin;
	}

private:
	User* Transform(SignUpUserModel model)
	{
		User* user = new User;
		user->Login = model.Login;
		user->FirstName = model.FirstName;
		user->LastName = model.LastName;
		user->PasswordHash = hash_helper::create_sha256_hash_str(
			model.Password);
		return user;
	}

};

