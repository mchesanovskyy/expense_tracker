#pragma once
#include "sqlite_orm/sqlite_orm.h"

#include "../../../Core/Entities/transaction.h"
#include "../../../Core/Entities/user.h"
#include "../../../Core/Interfaces/Repositories/IUserRepository.h"
#include "../../../Core/Interfaces/Repositories/ITransactionRepository.h"

using namespace sqlite_orm;
using namespace internal;

class ExpenseTrackerSqliteContext
{
public:
	auto GetStorage()
	{
		auto storage = make_storage("db.sqlite",
			make_table("users",
				make_column("FirstLame", &User::FirstName),
				make_column("Id", &User::Id, autoincrement(), primary_key()),
				make_column("LastName", &User::LastName),
				make_column("Login", &User::Login),
				make_column("PasswordHash", &User::PasswordHash)),

			make_table("transactions",
				make_column("UserId", &Transaction::UserId),
				make_column("Id", &Transaction::Id, autoincrement(), primary_key()),
				make_column("Title", &Transaction::Title),
				make_column("Timestamp", &Transaction::Timestamp),
				make_column("Amount", &Transaction::Amount)));

		storage.sync_schema();

		return storage;
	}
};

class SqliteUserRepository : public IUserRepository
{
	ExpenseTrackerSqliteContext& _context;

public:
	SqliteUserRepository(ExpenseTrackerSqliteContext& context) : _context(context)
	{

	}

	virtual User* GetByLogin(string login) override
	{
		auto storage = _context.GetStorage();

		auto results = storage.get_all_pointer<User>(where(c(&User::Login) == login));
		
		if (results.empty())
		{
			return nullptr;
		}

		User* u = new User;
		u->Id = results.at(0)->Id;
		u->Login = results.at(0)->Login;
		u->PasswordHash = results.at(0)->PasswordHash;
		u->LastName = results.at(0)->LastName;
		u->FirstName = results.at(0)->FirstName;
		return u;
	}

	int Add(User& user) override
	{
		auto storage = _context.GetStorage();
		return storage.insert(user);
	}

	User* GetById(int id) override
	{
		auto storage = _context.GetStorage();
		return storage.get_pointer<User>(id).get();
	}

	bool Delete(int id) override
	{
		auto storage = _context.GetStorage();
		storage.remove<User>(id);
		return true;
	}

	~SqliteUserRepository() override
	{

	}
};

class SqliteTransactionRepository : public ITransactionRepository
{
	ExpenseTrackerSqliteContext& _context;

public:
	SqliteTransactionRepository(ExpenseTrackerSqliteContext& context) : _context(context)
	{

	}

	vector<Transaction*> GetUserTransactions(int userId) override
	{
		auto storage = _context.GetStorage();
		auto results = storage.get_all_pointer<Transaction>(
			where(c(&Transaction::UserId) == userId));

		vector<Transaction*> transactions;
		for (int i = 0; i < results.size(); i++)
		{
			transactions.push_back(results.at(i).get());
		}

		return transactions;
	}

	int Add(Transaction& user) override
	{
		auto storage = _context.GetStorage();
		return storage.insert(user);
	}

	Transaction* GetById(int id) override
	{
		auto storage = _context.GetStorage();
		return storage.get_pointer<Transaction>(id).get();
	}
	bool Delete(int id) override
	{
		auto storage = _context.GetStorage();
		storage.remove<Transaction>(id);
		return true;
	}

	~SqliteTransactionRepository() override
	{

	}

};