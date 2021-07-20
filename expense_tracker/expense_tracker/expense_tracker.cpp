#include "stdafx.h"
#include <iostream>
#include "Core/Services/UserService.h"
#include "Infrastructure/Repositories/File/FileUserRepository.h"

int main()
{
	IUserRepository* repo = new FileUserRepository;
	IUserService* service = new UserService(*repo);

	auto* model = new SignUpUserModel;
	model->Login = "mc1";
	model->Password = "qwerty";
	model->FirstName = "M";
	model->LastName = "C";

	try
	{
		/*auto* user = service->SignUp(*model);
		cout << user->Id << endl;
		cout << user->Login << endl;*/

		auto* authUser = service->Login("mc", "qwerty");
	}
	catch (const std::exception& ex)
	{
		cout << ex.what();
	}
}