#pragma once
#include <fstream>

template <class TEntity>
class FileProvider
{
	string file_name_;

protected:
	const char delimiter = '|';

public:
	FileProvider(string file_name)
		: file_name_(std::move(file_name))
	{

	}

	virtual ~FileProvider() = default;

	virtual vector<TEntity*> GetRecords()
	{
		ifstream reader(file_name_);
		vector<TEntity*> records;
		if (reader.is_open())
		{
			string line;
			while (getline(reader, line))
			{
				vector<string> parts = split(line, delimiter);
				TEntity* entity = ToObject(parts);
				records.push_back(entity);
			}
			reader.close();
		}

		return records;
	}

	virtual void AddRecord(TEntity& entity)
	{
		std::ofstream file_stream(file_name_, std::ios_base::app | std::ios_base::out);
		file_stream << ToString(entity) << endl;
	}

	virtual void SaveChanges(vector<TEntity*> records)
	{
		ofstream writer;
		writer.open(file_name_);
		for (size_t i = 0; i < records.size(); i++)
		{
			writer << ToString(*records[i]) << endl;
		}
		writer.close();
	}

protected:

	virtual TEntity* ToObject(vector<string> parts) = 0;
	virtual string ToString(TEntity& entity) = 0;
};