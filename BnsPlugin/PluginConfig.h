#pragma once
#include <cstdint>

class PluginConfig {
public:
	int32_t ConfigValue;

	const wchar_t* ConfigPath;
	PluginConfig();
	void ReloadFromConfig();
private:
	void Initialize();
};

extern PluginConfig g_PluginConfig;