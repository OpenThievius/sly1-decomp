// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "base_object.h"
#include "switched_collider.h"
#include "list_iter.h"
#include "globals.h"

void func_001C06A0(s32 a, s32 b, f32 x);

void func_001C0000(s32 flag, f32 x)
{
    SetVolumeChannelFactor(6, 0, x);
    SetVolumeChannelFactor(6, 2, x);
    SetVolumeChannelFactor(6, 3, x);
    if (flag) {
        SetVolumeChannelFactor(6, 1, x);
    }
}

struct Elem_1C30E8 { f32 f0; f32 f4; u8 pad8[8]; f32 v10[4]; f32 v20[4]; };
struct Poly_1C30E8 {
    f32 c[3];
    f32 Eval(f32 t) { return c[0] + t * (c[1] + t * c[2]); }
};
struct Range_1C30E8 {
    f32 lo;
    f32 hi;
    f32 Clamp(f32 v)
    {
        f32 l = lo;
        f32 h = hi;
        if (v < l)
            v = l;
        else if (h < v)
            v = h;
        return v;
    }
};
struct Rec_1C30E8 {
    struct Obj_1C30E8* f0;
    s32 f4;
    s32 f8;
    s32 fC;
    f32 f10;
    u8 pad14[0x3C];
    Poly_1C30E8 poly;
    u8 pad5C[4];
    Elem_1C30E8 elems[1];
};

extern u8 D_00274998[8];
extern u8 D_002749A0[16];
extern f32 D_00261858[];

struct Ent_1C0070;
struct Frame_1C0070 : ListFrame {
    Ent_1C0070* Next() { Ent_1C0070* n = *(Ent_1C0070**)link; link = (u8*)n + offset; return n; }
};
struct Ent_1C0070 {
    s32 f0; s32 f4; s32 f8; u8 pad0c[0x08]; f32 f14;
    s32 f18; u8 pad1c[0x04];
    u8 f20[0x10];
    BaseObject* f30; f32 f34; f32 f38; s32 f3C; s32 f40; s32 f44; s32 f48; u8 f4C;
    u8 pad4d[3];
    s32 f50; s32 f54; f32 f58; u8 pad5c[0x18];
    f32 f74; f32 f78;
};
struct Pair_1C0070 { s32 a; s32 b; };

extern ListFrame* D_0027472C;
extern s32 D_00274744;
extern s32 D_00274730;
extern s32 D_00274738;
extern s32 D_00274734;
s32 D_00274754 = 3;
extern s32 D_002748EC;
f32 D_00274750 = -2.0f;
extern f32 D_00261858[];
extern Pair_1C0070 D_00245024[];

s32 func_001BF1F0(void);
void* func_001BF3D0(void);
typedef f32 (*Fn_1C0070)(void* a, void* b);
Fn_1C0070 func_001BF578(void);
s32 func_0011D708(ListFrame* h);
void func_0011D928(s32 a);
void func_001C06A0(s32 a, s32 b, f32 x);
s32 func_00182FC8(BaseObject* o);
void func_0011D600(s32 h);
void func_0011D730(s32 h, void (*fn)(void), s64 arg);
void func_001BFFC8(void);
void func_001BFBF8(Ent_1C0070* e);
void func_001BF200(f32 r, void* pos, s32* o1, s32* o2, f32 a, f32 b, f32 c);
s32 func_0011D598(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);
void func_001BF428(Ent_1C0070* e);
void func_001BF7F8(Ent_1C0070* e, f32 x);
void func_001BE860(Ent_1C0070* e);
void func_001BF788(Ent_1C0070* e, s32 n);
s32 func_0011CE30(void);

void func_001C0070(void)
{
    Frame_1C0070 f;
    if (func_001BF1F0() != 0) return;
    void* v4 = GetSoundListenerPosition();
    Fn_1C0070 v5 = ChooseSoundListenerFunction();
    u8* P = (u8*)g_currentWorld + 0x1BAC;
    ListFrame* saved = g_activeListFrames;
    f.list = P;
    f.link = P;
    f.offset = *(s32*)(P + 8);
    f.prev = saved;
    g_activeListFrames = &f;
    if (g_streamVoice != 0 && IsVoiceBusy(g_streamVoice) == 0) {
        if (g_streamVoiceLocked != 0) {
            SetVolumeChannelFactor(8, 1, 1.0f);
            SetVolumeChannelFactor(8, 0, 1.0f);
            SetVolumeChannelFactor(8, 3, 1.0f);
        }
        g_streamVoice = 0;
        g_streamVoiceLocked = 0;
        g_streamVoicePending = 0;
    }
    if (g_previousSoundLevel != -100) {
        s32 up = g_previousSoundLevel < g_currentSoundLevel;
        if (g_currentSoundLevel > 0 && up) {
            func_0011D928(g_currentSoundLevel + 0x14);
            g_previousSoundLevel = g_currentSoundLevel;
            SetVolumeChannelFactor(7, 1, 1.0f);
            D_002748EC = 0;
        } else {
            D_00274754 = D_00274754 - 1;
            if (D_00274754 < 0) {
                s32 a = g_previousSoundLevel;
                s32 v = (g_currentSoundLevel < a) ? a - 1 : a + 1;
                D_002748EC = (u32)v >> 31;
                g_previousSoundLevel = v;
                func_0011D928(v + 0x14);
                if (g_previousSoundLevel < 0) {
                    f32 cnv = (f32)g_previousSoundLevel;
                    f32 k = -0.05f;
                    f32 zero = 0.0f;
                    f32 one = 1.0f;
                    f32 x = cnv * k;
                    f32 y;
                    if (x < zero) y = zero;
                    else if (one < x) y = one;
                    else y = x;
                    f32 m = y * 0.6666667f;
                    SetVolumeChannelFactor(7, 1, (1.0f - y) + m);
                }
                D_00274754 = D_00274754 + 3;
            }
        }
        if (up ? !(g_previousSoundLevel < g_currentSoundLevel) : !(g_previousSoundLevel > g_currentSoundLevel)) {
            D_002748EC = (u32)g_previousSoundLevel >> 31;
            func_0011D928(g_currentSoundLevel + 0x14);
            g_previousSoundLevel = -100;
        }
    }
    Ent_1C0070* e;
    {
        while ((e = f.Next()) != 0) {
            u8* s1;
            f32 r;
            if (e->f30 != 0 && IsObjectAttached(e->f30) == 0) {
                StopSoundRecord(e, 0);
                goto next;
            }
            if (e->f40 == 0) {
                if (e->f48 != 0) {
                    if (0.0f <= e->f78) {
                        e->f18 = 0;
                    } else {
                        if (e->f30 != 0) e->f30->desc->m0E(e->f30, 9, e);
                        if (e->f3C == 0) goto kill;
                        StopSoundVoice(e->f18);
                        e->f18 = 0;
                    }
                    e->f48 = 0;
                    e->f40 = 1;
                    goto next;
                }
                e->f4C = (e->f4C + 1) % 4;
                if (e->f4C == 0) {
                    RequestVoiceCallback(e->f18, MarkSoundRecordIfIdMatches, ((s64)e->f4 << 32) | (s64)(s32)e);
                }
            }
            if (0.0f <= e->f78) {
                f32* s1 = g_gameClock;
                if (s1[1] < e->f74) {
                    if (e->f40 != 0) goto next;
                } else {
                    func_001BFBF8(e);
                    if (e->f40 != 0) {
                        if (s1[1] - D_00274750 < 1.0f) goto next;
                        D_00274750 = s1[1];
                    }
                }
            }
            if (e->f44 == 0) goto next;
            {
                s1 = (u8*)e + 0x20;
                if (e->f30 != 0) s1 = (u8*)e->f30 + 0x140;
                r = v5(v4, s1);
                if (e->f34 < r) {
                    if (0.0f <= e->f78) goto next;
                    if (e->f40 != 0) goto next;
                    if (e->f3C != 0 || 0.0f < e->f74) {
                        StopSoundVoice(e->f18);
                        e->f18 = 0;
                        e->f40 = 1;
                        goto next;
                    }
                kill:
                    StopSoundRecord(e, 0);
                    goto next;
                }
                func_001BF200(r, s1, &e->f50, &e->f54, e->f14, e->f34, e->f38);
            }
            if (e->f40 != 0 && e->f0 != -2) {
                e->f18 = StartSoundVoice(e->f8, D_00245024[e->f0].a, 0, 0, 0, 0);
                e->f40 = 0;
            }
            func_001BF428(e);
            SetSoundRecordPitch(e, e->f58);
            ApplySoundRecordVolumePan(e);
        next:;
        }
    }
    PollIopCommands();
    g_activeListFrames = f.prev;
}

// Data definitions (retail values)
s32 D_0026E228[8] = { 0 };

// Data of src/main/file_1C05D0.cpp, defined here until the file's own data is proved.
