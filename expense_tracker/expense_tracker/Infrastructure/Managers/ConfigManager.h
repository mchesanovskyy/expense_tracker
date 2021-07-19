#pragma once
#include <fstream>

class ConfigManager
{

private:
	const string config_file_name = "app.config";
	map<string, string> settings;

	ConfigManager();

	static ConfigManager* current_;

public:
	static ConfigManager& get_instance();

	ConfigManager(ConfigManager& other) = delete;

	void operator=(const ConfigManager&) = delete;

	string GetSetting(string setting_name);

	int GetSettingAsInt(const string setting_name);

	void AddOrUpdateSetting(string name, string value);

	void AddOrUpdateSetting(string name, int value);

	int GetAutoincrementValue(string name);

private:

	void LoadSettings();

	void SaveSettings();
};

ConfigManager* ConfigManager::current_ = nullptr;

ConfigManager::ConfigManager()
{
	LoadSettings();
}

ConfigManager& ConfigManager::get_instance()
{
	if (current_ == nullptr)
	{
		current_ = new ConfigManager;
	}

	return *current_;
}

string ConfigManager::GetSetting(string setting_name)
{
	for (auto& setting : settings)
	{
		if (is_equals_ignore_case(setting.first, setting_name))
		{
			return setting.second;
		}
	}

	return "";
}

int ConfigManager::GetSettingAsInt(const string setting_name)
{
	const auto setting = GetSetting(setting_name);
	if (empty(setting))
	{
		return 0;
	}

	return stoi(setting);
}

void ConfigManager::AddOrUpdateSetting(string name, string value)
{
	LoadSettings();
	settings.insert_or_assign(name, value);
	SaveSettings();
}

void ConfigManager::AddOrUpdateSetting(string name, int value)
{
	AddOrUpdateSetting(name, to_string(value));
}

int ConfigManager::GetAutoincrementValue(string name)
{
	int value = GetSettingAsInt(name);
	AddOrUpdateSetting(name, ++value);
	return value;
}

void ConfigManager::LoadSettings()
{
	string line;
	ifstream myfile(config_file_name);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			vector<string> parts = split(line, '=');

			if (parts.size() < 2)
			{
				throw "The app.config file is corrupted";
			}

			settings.emplace(parts[0], parts[1]);
		}
		myfile.close();
	}
}

void ConfigManager::SaveSettings()
{
	ofstream writer;
	writer.open(config_file_name);
	for (auto& setting : settings)
	{
		writer << setting.first << "=" << setting.second;
		writer << endl;
	}
	writer.close();
}
