#pragma once

template<class T>
class IRepository
{
public:
	virtual ~IRepository() = default;
	virtual int Add(T& user) = 0;
	virtual T* GetById(int id) = 0;
	virtual bool Delete(int id) = 0;
};

