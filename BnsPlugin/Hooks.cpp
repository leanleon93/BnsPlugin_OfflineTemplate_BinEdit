#include "Hooks.h"
#include "PluginConfig.h"
#include <unordered_map>

extern BSMessaging* Messaging;

template <typename Callable>
void handleKeyEvent(EInputKeyEvent const* InputKeyEvent, int vKeyTarget, const Callable& onPress) {
	static std::unordered_map<int, bool> toggleKeys;
	if (vKeyTarget == 0)  return;
	if (InputKeyEvent->_vKey == vKeyTarget) {
		bool& toggleKey = toggleKeys[vKeyTarget];
		if (!toggleKey && InputKeyEvent->KeyState == EngineKeyStateType::EKS_PRESSED) {
			toggleKey = true;
			onPress();
		}
		else if (toggleKey && InputKeyEvent->KeyState == EngineKeyStateType::EKS_RELEASED) {
			toggleKey = false;
		}
	}
}

template <typename Callable>
void handleKeyEventWithModifiers(
	EInputKeyEvent const* InputKeyEvent,
	int vKeyTarget,
	bool alt,
	bool shift,
	bool ctrl,
	const Callable& onPress
) {
	static std::unordered_map<int, bool> toggleKeys;
	if (vKeyTarget == 0)  return;
	if (InputKeyEvent->_vKey == vKeyTarget) {
		bool& toggleKey = toggleKeys[vKeyTarget];
		if (!toggleKey && InputKeyEvent->KeyState == EngineKeyStateType::EKS_PRESSED) {
			// Check for Alt, Shift, and Ctrl modifiers
			if ((alt == InputKeyEvent->bAltPressed) &&
				(shift == InputKeyEvent->bShiftPressed) &&
				(ctrl == InputKeyEvent->bCtrlPressed)) {
				toggleKey = true;
				onPress();
			}
		}
		else if (toggleKey && InputKeyEvent->KeyState == EngineKeyStateType::EKS_RELEASED) {
			toggleKey = false;
		}
	}
}

bool(__fastcall* oBInputKey)(BInputKey* thisptr, EInputKeyEvent* InputKeyEvent);
bool __fastcall hkBInputKey(BInputKey* thisptr, EInputKeyEvent* InputKeyEvent) {
	//alt+p to reload config
	handleKeyEventWithModifiers(InputKeyEvent, 0x50, true, false, false, []() {
		g_PluginConfig.ReloadFromConfig();
		auto message = LR"(<image imagesetpath="00027918.Tooltip_Alert" enablescale="true" scalerate="1.6" />PluginTemplate Config reloaded!)";
		Messaging->DisplaySystemChatMessage(message, false);
		});
	return oBInputKey(thisptr, InputKeyEvent);
}

DrEl* (__fastcall* oFind_b8)(DrMultiKeyTable* thisptr, unsigned __int64 key);
DrEl* __fastcall hkFind_b8(DrMultiKeyTable* thisptr, unsigned __int64 key) {
	return oFind_b8(thisptr, key);
}