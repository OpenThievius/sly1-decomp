// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "list_iter.h"
#include "trigger_zone.h"
#include "zone_collider.h"
#include "flagged_object.h"
#include "object_gatherer.h"
#include "world.h"
#include "game_clock.h"
#include "object_event.h"

extern const u32 D_00247AA0;
s32 D_002613F4;
extern s32 D_002613F8[6];
s32 func_0011E138(void*, void*, void*, void*);
s32 func_0011E1F8(s32);
s32 func_0011E2E8(void);
void func_00140C28(void* a, void* b, void* c)
{
	s32 result;
	do {
		result = StartDiscRead(a, b, c, (void*)&D_00247AA0);
		g_lastDiscReadResult = result;
		if (result != 1) { SyncDiscRead(0); g_discReadErrors[0] = GetDiscReadError(); }
	} while (result != 1);
}

s32 func_00203B18(void*, void*, void*, void*);
s32 func_002032C8(s32);
s32 func_00203D90(void);
void func_00140CC8(void* a, void* b, void* c)
{
	s32 result;
	do {
		result = func_00203B18(a, b, c, (void*)&D_00247AA0);
		g_lastDiscReadResult = result;
		if (result != 1) { func_002032C8(0); g_discReadErrors[0] = func_00203D90(); }
	} while (result != 1);
}

s32 func_001C1A28(void* a, void* b);

struct Self_140550 {
    u8 pad0[0x598];
    s32 f598;
    void* f59C[32];
};

s32 func_00140550(Self_140550* self, void* arg)
{
    for (s32 i = 0; i < self->f598; i++) {
        if (AppendPropertyToScriptList(arg, &self->f59C[i]) == 0) {
            return 0;
        }
    }
    return 1;
}

void func_0013EB30(void* p);
void func_00140640(void* a, void* b, void* c);

void func_00140688(void* self, void* b)
{
    func_00140640((u8*)self + 0x5C0, self, b);
}

void func_0013EB30(void* p);

void func_00140750(void* self)
{
    SetZoneEntry((u8*)self + 0x554);
}

void func_001409D8(void) {}



extern s32 D_002613EC;

void func_00140790(void)
{
    g_discSectorCheckState = 3;
}

struct Holder_1407A0 { u8 pad[0x4]; s32 value; };

s32 func_001407A0(Holder_1407A0* holder)
{
    return holder->value;
}

extern s32 D_002613F0;
u32 func_00203A20(s32 arg);

void func_001409A8(void)
{
    if (D_002613F0 == 0x14) {
        func_00203A20(2);
    }
}

void func_001405D0(void* a, void* b, int c);

void func_00140618(void* self, int value)
{
    func_001405D0((u8*)self + 0x5C0, self, value);
}

bool func_0013E8F8(void* a, int b);

void func_00140640(void* self, void* unused, int value)
{
    AppendToObjectQueue((u8*)self + 0x90, value);
}

void func_00140640(void* self, void* unused, int value);

void func_00140660(TriggerZone* self, int value)
{
    func_00140640(&self->zone, self, value);
}

void func_001406B0(TriggerZone* list, s32 value)
{
    list->idsIn[list->countIdsIn++] = value;
}




void func_001406D0(TriggerZone* self, s32 value)
{
    s32 n = self->countIdsOut;
    self->idsOut[n] = value;
    self->countIdsOut = n + 1;
}

void func_001406F0(TriggerZone* self, s32 value)
{
    s32 n = self->countKindsIn;
    self->kindsIn[n] = value;
    self->countKindsIn = n + 1;
}


void func_00124A48(void* self);
void func_0013EA38(void* p);
void func_00140238(ZoneCollider* self, s32 flag);
void* func_0015A448(void* obj, s32 id, void* ctx);


void func_00140140(ZoneCollider* self)
{
    StartPlacedObject(self);
    StartZoneRecord(&self->zone);
    func_00140238(self, 0);
    for (s32 i = 0; i < self->countIds; i++) {
        void* p = func_0015A448(self->world, self->ids[i], self);
        if (p != 0) {
            s32 n = self->countObjs;
            self->objs[n] = (s32)p;
            self->countObjs = n + 1;
        }
    }
    if (self->countIds == 0) {
        self->f5BC = 1;
    }
}

void func_001BA130(void* self);


void func_00140200(ZoneCollider* self)
{
    s32 saved = self->zone.id120;
    CopyCollider(self);
    self->zone.id120 = saved;
    self->zone.owner = self;
}


typedef signed int s32;
typedef unsigned char u8;

extern void func_0013EB68(void* state);

void func_00140238(ZoneCollider* self, s32 flag)
{
    SetZoneMode(&self->zone);
}

typedef signed int s32;
typedef unsigned char u8;

bool func_0013E8F8(void* a, s32 b);

void func_001405D0(void* a, void* b, s32 c)
{
    AppendToObjectQueue((u8*)a + 0x8, c);
}



// Newly matched US functions from the small-function wave.
extern void func_0013EB30(void*);
extern s32 func_0011E1F8(s32);
extern void func_001439A8(void*);
extern void func_001439C8(void*);
extern void func_001439E8(void*);
extern void func_00143A08(void*);
extern void* D_00261990;
extern void func_001448C8(void*, s32, void*);

void func_00140710(TriggerZone* self, void* value)
{
    s32 i = self->countKindsOut;
    u32 address = (u32)self + (u32)(i << 2);
    *(u32*)(address + 0x790) = (u32)value;
    self->countKindsOut = i + 1;
}

void func_00140730(void* self, void* value)
{
    s32 i = *(s32*)((u8*)self + 0x550);
    u32 address = (u32)self + (u32)(i << 2);
    *(u32*)(address + 0x554) = (u32)value;
    *(s32*)((u8*)self + 0x550) = i + 1;
}

void func_00140770(void* self) { SetZoneEntry((u8*)self + 0x5C0); }

s32 func_00140D68(s32 value) { s32 result = SyncDiscRead((u32)value < 1u); return result == 0; }

void func_001405F0(u8* self, s32 value)
{
    func_001405D0(self + 0x554, self, value);
}



void func_001BAC30(void* self);
void func_0013E950(void* p, void* self);

void func_00140100(ZoneCollider* self)
{
    LoadCollider(self);
    CollectZoneChildren(&self->zone, self);
    if (self->f790 != 0) {
        self->zone.f13C = 1;
    }
}

s32 func_001BC320(void* self, void* ev);
void func_0013F6F8(TriggerZone* state, s32 mode);

s32 func_00140028(TriggerZone* a0, void* a1)
{
    s32 r = HandleObjectEvent(a0, a1);
    if (r != 0 && (*(s32*)((u8*)a1 + 0xC) & 4) == 0 && a0->state == 3 && a0->zone.mode == 0) {
        SetTriggerZoneMode(a0, 1);
    }
    return r;
}










void func_0013E918(Zone28* p);
void func_001B7968(Collider* self);
void func_001B9AE0(void* self, s32 a, s32 b, s32 c, s32 d);

void func_001400A8(ZoneCollider* self)
{
    u64 m = 0x8000;
    InitCollider(self);
    InitZoneRecord(&self->zone);
    m <<= 28;
    self->flags538 = self->flags538 | m;
    SetColliderAnchors(self, 3, 0, 3, 0);
}

extern u8 D_002701B8[];
extern const u32 D_00247AA4;
extern const u32 D_00247AA8[2];
extern const u32 D_00247AA0;
extern u8 D_0026FF68[];
extern u8 D_0027B800[];
extern u32 D_002476A0[];

s32 func_00203EE0(s32 a0, s32* out);
s32 func_00140968(void);
s32 func_00140D68(s32 value);
void func_00194D30(void* self, s32 a, s32 b);
s32 func_0011E138(s32 a0, s32 a1, void* a2, void* a3);

void func_001409E0(void)
{
    s32 tmp[1];
    s32 s1;
    switch (g_discSectorCheckState) {
    case 3:
        if (func_00203EE0(2, tmp) != 0) {
            if (tmp[0] != 0) {
                if (func_00140968() == 0) {
                    SetPauseMenuLayerPage(g_pauseMenuElement, 2, 0x16);
                    g_discSectorCheckState = 1;
                }
            }
        }
        break;
    case 1:
        s1 = *(s32*)D_002701B8;
        if (s1 == 2) {
            if (func_00140968() != 0) {
                if (StartDiscRead((s32)D_00247AA4, 1, D_0027B800, (void*)&D_00247AA0) == 1) {
                    g_discSectorCheckState = s1;
                }
            }
        }
        break;
    case 2:
        if (TestDiscReadDone(0) != 0) {
            u8* p = D_0027B800;
            u32* tbl = g_crc32Table;
            u32 crc = 0xFFFFFFFF;
            s32 n = 0x7FF;
            do {
                crc = *(u32*)((u8*)tbl + (((crc ^ *p) & 0xFF) << 2)) ^ (crc >> 8);
                p++;
                n--;
            } while (n != -1);
            if ((s32)crc != (s32)D_00247AA8[0]) {
                g_discSectorCheckState = 1;
            } else {
                SetPauseMenuLayerPage(g_pauseMenuElement, 2, -1);
                g_discSectorCheckState = 3;
            }
        }
        break;
    }
}

struct Buf_140B60 { char b[256]; };
struct Obj_140B60 { u8 pad; };

extern const u16 D_00249E20[4];
extern const char D_00249E28[8];
extern const char D_00249E30[8];
extern const char D_00249E38[4];

void* func_001E2180(Buf_140B60* dst, void* src);
s32 func_001407A8(Buf_140B60* p);
s32 func_001E2100(Buf_140B60* p);
s32 func_001E1FD0(Obj_140B60* dst, const char* fmt, ...);

void func_00140B60(void* self, void* a1, s32 flag)
{
    char buf[256];
    *(u16*)buf = D_00249E20[0];
    AppendString((Buf_140B60*)buf, a1);
    s32 n = NormalizeDiscPath((Buf_140B60*)buf);
    char* p = buf;
    for (s32 i = 1; i < n; i++) {
        p[GetStringLength((Buf_140B60*)p)] = 0x5C;
    }
    FormatToString((Obj_140B60*)self, D_00249E28,
                  flag ? (void*)D_00249E30 : (void*)D_00249E38, buf);
}


void func_001E2218(s8* p);
s32 func_001E2100(const s8* s);
void* func_001E2180(s8* dst, const char* src);

s32 func_001407A8(s8* path)
{
    UppercaseString(path);
    s32 len = GetStringLength(path);
    if (len != 0) {
        s8 last = path[len - 1];
        if (last != '\\' && last != '/') {
            AppendString(path, ";1");
            len = GetStringLength(path);
        }
    }
    s8* end = path + len;
    s8* out = path;
    s8* in = path;
    s32 count = 0;
    s32 n = 0;
    s32 max = 8;
    while (in < end) {
        switch (*in) {
        case '/':
        case '\\':
            if (n != 0) {
                *out++ = 0;
                n = 0;
                max = 8;
                count++;
            }
            break;
        case '.':
            if (n != 0 && max == 8) {
                *out++ = *in;
                n = 0;
                max = 3;
            }
            break;
        case ';':
            if (n != 0 && in == end - 2 && in[1] == '1') {
                *out++ = *in++;
                *out++ = *in;
                n += 2;
                break;
            }
        default:
            if (n < max) {
                if ((u8)(*in - 'A') < 26 || (u8)(*in - '0') < 10) {
                    *out++ = *in;
                } else {
                    *out++ = '_';
                }
                n++;
            }
            break;
        }
        in++;
    }
    if (n != 0) {
        *out = 0;
        count++;
    }
    return count;
}


// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
void func_001493C0();
void func_001496C0();
void func_00149760();
void func_0014A7B8();
void func_0014A8D0();
void func_0014A8F8();
void func_0014AA90();
void func_0014AA98();
void func_0014AAA0();
void func_001E2E68();
void func_001E30A0();
void func_001E30D8();
void func_001E30E0();
void func_001E31F0();
typedef void (*Fn_Table)();
extern const Fn_Table D_00217398[6] = { 0, 0, 0, 0, (Fn_Table)func_001493C0, 0 };
extern const Fn_Table D_002173B0[6] = { (Fn_Table)func_001496C0, (Fn_Table)func_0014A7B8, 0, 0, (Fn_Table)func_00149760, 0 };
extern const Fn_Table D_002173C8[6] = { (Fn_Table)func_0014A8D0, 0, 0, 0, (Fn_Table)func_0014A8F8, 0 };
extern const Fn_Table D_002173E0[6] = { (Fn_Table)func_0014AA90, (Fn_Table)func_0014AA98, 0, 0, (Fn_Table)func_0014AAA0, 0 };
extern const Fn_Table D_002173F8[6] = { (Fn_Table)func_001E2E68, (Fn_Table)func_001E30A0, (Fn_Table)func_001E30D8, (Fn_Table)func_001E30E0, (Fn_Table)func_001E31F0, 0 };



s32 D_002613F8[6] = { 0, 0, 0, 0, 0, 0 };
extern const u32 D_00247AA0 = 0x17F;
extern const u32 D_00247AA4 = 0x14E0EF;
extern const u32 D_00247AA8[2] = { 0x2E774159, 0 };
extern const u16 D_00249E20[4] = { 0x5C, 0, 0, 0 };
extern const char D_00249E28[8] = "%s\\%s";
extern const char D_00249E30[8] = "cdrom0:";
extern const char D_00249E38[4] = "";
