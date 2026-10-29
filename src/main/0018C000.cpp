// SPDX-License-Identifier: AGPL-3.0-or-later

#include "common.h"

extern s32 func_0018C888(void*, void*, s32, void*, void*);
extern s32 func_0018BD00(s32, void*, s32);
extern void* func_00209FA8(s32, s32);
extern void* func_002096E8(s32, s32, void*);
extern void* func_002095B0(s32, s32, void*, void*);
extern void* func_00209720(void*);
extern void* func_00209870(void*, void*, void*);
extern void* func_00209990(void*, void*, void*);

s32 func_0018C9C0(void* a0, void* a1, void* a2)
{
	s32 temp;
	s32 result = func_0018C888(a0, a1, 1, a2, &temp);
	if (result != 0)
		return result;
	return temp == 1 ? 0 : 14;
}

void func_0018D1F8(void* p)
{
	void* result = func_00209FA8(*(s32*)((char*)p + 4), *(s32*)((char*)p + 8));
	func_0018BD00((s32)result, (void*)0x10, 0);
}

s32 func_0018D228(void* p, void* value)
{
	s32 result = func_0018BD00((s32)func_002096E8(*(s32*)((char*)p + 4), *(s32*)((char*)p + 8), value), (void*)0xB, 0);
	return result == 0x18 ? 0 : result;
}

s32 func_0018D268(void* p, void* a1, void* a2, void* a3)
{
	return func_0018BD00((s32)func_002095B0(*(s32*)((char*)p + 4), *(s32*)((char*)p + 8), a1, a2), (void*)2, (s32)a3);
}

void func_0018D2B0(void* unused, void* value)
{
	func_0018BD00((s32)func_00209720(value), (void*)3, 0);
}

void func_0018D2E8(void* unused, void* a1, void* a2, void* a3, void* a4)
{
	func_0018BD00((s32)func_00209870(a1, a2, a3), (void*)5, (s32)a4);
}

void func_0018D328(void* unused, void* a1, void* a2, void* a3, void* a4)
{
	func_0018BD00((s32)func_00209990(a1, a2, a3), (void*)6, (s32)a4);
}
