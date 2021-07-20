#include "../../Managers/ConfigManager.h"
#include "../../Providers/FileProvider.h"

template<class T>
class FileRepositoryBase : protected FileProvider<T>
{
	string _idConfigName;
protected:
	ConfigManager& _configManager;

	FileRepositoryBase(string fileName, string idConfigName)
		: FileProvider<T>(fileName),
		_configManager(ConfigManager::get_instance())
	{
		_idConfigName = idConfigName;
	}

public:
	virtual int Create(T& entity)
	{
		entity.Id = _configManager.GetAutoincrementValue(_idConfigName);

		FileProvider<T>::AddRecord(entity);

		return entity.Id;
	}

	virtual T* GetById(int id)
	{
		auto i = 0;
		for (auto* record : FileProvider<T>::GetRecords())
		{
			if (record->Id == id)
			{
				return record;
			}
		}
		return nullptr;
	}

	virtual bool Delete(int id)
	{
		auto records = FileProvider<T>::GetRecords();
		vector<T*> outRecords;
		for (auto* record : records)
		{
			if (record->Id != id)
			{
				outRecords.push_back(record);
			}
		}
		FileProvider<T>::SaveChanges(outRecords);
		return true;
	}

};

