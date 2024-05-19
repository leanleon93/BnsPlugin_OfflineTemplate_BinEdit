#pragma once
#include "BSFunctions.h"
#include "Data.h"

extern bool(__fastcall* oBInputKey)(BInputKey* thisptr, EInputKeyEvent* InputKeyEvent);
bool __fastcall hkBInputKey(BInputKey* thisptr, EInputKeyEvent* InputKeyEvent);

extern DrEl* (__fastcall* oFind_b8)(DrMultiKeyTable* thisptr, unsigned __int64 key);
DrEl* __fastcall hkFind_b8(DrMultiKeyTable* thisptr, unsigned __int64 key);