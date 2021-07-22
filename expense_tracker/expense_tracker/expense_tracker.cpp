#include "stdafx.h"

#include "ClientApps/Console/ConsoleManager.h"
#include "Core/Services/TransactionService.h"
#include "Infrastructure/Repositories/File/FileTransactionRepository.h"
#include "Tests/UserServiceTests.h"

int main()
{
	ConsoleManager manager;
	manager.Start();
	
	/*UserServiceTests serviceTests;
	serviceTests.Run();*/

	//ITransactionRepository* repo = new FileTransactionRepository;
	//ITransactionService* service = new TransactionService(*repo);
}
