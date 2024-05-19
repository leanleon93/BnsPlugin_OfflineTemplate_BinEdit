#include "BSFunctions.h"
#include <string>
#include <iostream>

static BInstance* BNSInstance;

BSMessaging::BSMessaging(uintptr_t* _BNSClientInstance, _AddInstantNotification addInstantNotification)
{
	this->BNSClientInstance = _BNSClientInstance;
	this->oAddInstantNotification = addInstantNotification;
}

void BSMessaging::SendGameMessage_s(const wchar_t* text, const wchar_t* particleRef, const wchar_t* sound, char track, bool stopPreviousSound, bool headline2, bool boss_headline, bool chat, char category, const wchar_t* sound2)
{
	try {
		if (*BNSClientInstance) {
			BNSInstance = *(BInstance**)BNSClientInstance;

			// Always check if oAddInstantNotification was defined otherwise you will cause a crash
			if (*BNSInstance->GameWorld && oAddInstantNotification) {
#ifdef _DEBUG
				std::wcout << "Sending message: " << text << std::endl;
#endif // _DEBUG
				oAddInstantNotification(BNSInstance->GameWorld, text, particleRef, sound, track, stopPreviousSound, headline2, boss_headline, chat, category, sound2);
			}
			else {
				throw std::runtime_error("oAddInstantNotification not defined");
			}
		}
		else {
			throw std::runtime_error("BNSClientInstance not defined");
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

void BSMessaging::DisplaySystemChatMessage(const wchar_t* text, bool playSound)
{
	SendGameMessage_s(text, L"", playSound ? L"00003805.Signal_UI.S_Sys_FindNewSpaceCue" : L"", 0, playSound, false, false, true, 22, L"");
}

void BSMessaging::DisplayScrollingTextHeadline(const wchar_t* text, bool playSound)
{
	SendGameMessage_s(text, L"", playSound ? L"00003805.Signal_UI.S_Sys_FindNewSpaceCue" : L"", 0, playSound, false, false, false, 0, L"");
}

uintptr_t GetAddress(uintptr_t AddressOfCall, int index, int length)
{
	if (!AddressOfCall)
		return 0;

	long delta = *(long*)(AddressOfCall + index);
	return (AddressOfCall + delta + length);
}

std::string EngineKeyStateString(EngineKeyStateType type) {
	switch (type)
	{
	case EngineKeyStateType::EKS_PRESSED:
		return "EKS_PRESSED";
		break;
	case EngineKeyStateType::EKS_RELEASED:
		return "EKS_RELEASED";
		break;
	case EngineKeyStateType::EKS_REPEAT:
		return "EKS_REPEAT";
		break;
	case EngineKeyStateType::EKS_DOUBLECLICK:
		return "EKS_DOUBLECLICK";
		break;
	case EngineKeyStateType::EKS_AXIS:
		return "EKS_AXIS";
		break;
	default:
		return "UNKNOWN";
		break;
	}
}

static_assert(offsetof(BInstance, PresentationWorld) == 0xB8);