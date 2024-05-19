#include "PluginConfig.h"
#include "SimpleIni.h"
#include "xorstr.hpp";
#include <string>
#include <filesystem>
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

PluginConfig g_PluginConfig;

PluginConfig::PluginConfig()
{
	Initialize();
}

void PluginConfig::Initialize() {
	WCHAR fullpath[MAX_PATH];
	GetModuleFileNameW(nullptr, fullpath, MAX_PATH);
	std::filesystem::path base(fullpath);
	std::wstring inipath(base.parent_path());
	inipath += xorstr_(L"/plugins/templateconfig.ini");
	ConfigPath = inipath.c_str();
#ifdef _DEBUG
	std::wcout << ConfigPath << std::endl;
#endif // _DEBUG
}

void PluginConfig::ReloadFromConfig()
{
	CSimpleIniA configIni;
	configIni.SetUnicode();
	configIni.LoadFile(ConfigPath);
	if (configIni.GetValue("SECTION", "Key"))
	{
		ConfigValue = std::stoi(configIni.GetValue("SECTION", "Key"));
	}
}