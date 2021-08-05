#include "stdafx.h"

#include "ClientApps/Console/ConsoleManager.h"
#include "ClientApps/Telegram/TgBotManager.h"
#include "Core/Services/TransactionService.h"
#include "Infrastructure/Repositories/File/FileTransactionRepository.h"
#include "Tests/UserServiceTests.h"

int main()
{
	/*ConsoleManager manager;
	manager.Start();
	*/
	/*UserServiceTests serviceTests;
	serviceTests.Run();*/

	TgBotManager manager;
	manager.Start();





}
