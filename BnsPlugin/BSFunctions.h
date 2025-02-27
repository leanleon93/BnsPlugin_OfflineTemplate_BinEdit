#pragma once
#include <cstdint>
#include <cstddef>
#include <string>


enum class EngineKeyStateType {
	EKS_PRESSED = 0,
	EKS_RELEASED = 1,
	EKS_REPEAT = 2,
	EKS_DOUBLECLICK = 3,
	EKS_AXIS = 4
};

std::string EngineKeyStateString(EngineKeyStateType type);

struct EngineEvent;

struct EngineEventVtbl
{
	void* (__fastcall* __vecDelDtor)(EngineEvent* This, unsigned int);
	int(__fastcall* Id)(EngineEvent* This);
};

struct EngineEvent {
	EngineEventVtbl* vfptr;
	EngineEvent* _next;
	__int64 _etime;
};

struct EInputKeyEvent : EngineEvent {
	char _vKey;
	char padd_2[0x2];
	EngineKeyStateType KeyState;
	bool bCtrlPressed;
	bool bShiftPressed;
	bool bAltPressed;
};

#ifndef BInstance_H
#define BInstance_H

class BInstance {
public:
	char pad[0xA0];
	uintptr_t* GameWorld;
	char padd[0x10];
	uintptr_t* PresentationWorld;
};
#endif // !BInstance_H

typedef void(__cdecl* _AddInstantNotification)(
	uintptr_t* thisptr,
	const wchar_t* text,
	const wchar_t* particleRef,
	const wchar_t* sound,
	char track,
	bool stopPreviousSound,
	bool headline2,
	bool boss_headline,
	bool chat,
	char category,
	const wchar_t* sound2);

typedef void* (__cdecl* _BNSClient_GetWorld)();

#ifndef BSMessaging_H
#define BSMessaging_H

class BSMessaging {
private:
	static void SendGameMessage_s(
		uintptr_t* BNSClientInstance,
		_AddInstantNotification* oAddInstantNotification,
		const wchar_t* text,
		const wchar_t* particleRef,
		const wchar_t* sound,
		char track,
		bool stopPreviousSound,
		bool headline2,
		bool boss_headline,
		bool chat,
		char category,
		const wchar_t* sound2);
public:
	static void DisplaySystemChatMessage(uintptr_t*, _AddInstantNotification*, const wchar_t*, bool playSound);
	static void DisplayScrollingTextHeadline(uintptr_t*, _AddInstantNotification*, const wchar_t*, bool playSound);
};
#endif // !BSMessaging_H

uintptr_t GetAddress(uintptr_t AddressOfCall, int index, int length);
