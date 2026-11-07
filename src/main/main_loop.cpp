// SPDX-License-Identifier: AGPL-3.0-or-later
// The file from 0x184D78 to 0x185C18: an object sort, the aim helpers, the main loop with the
// IOP modules it loads and the startup initializers it runs. Its name is ours, after the loop.
#include "common.h"
#include "asm_func.h"

#include "fpu.h"
#include "attachment.h"
#include "globals.h"
#include "game_clock.h"
#include "pad_record.h"
#include "memory_card.h"


struct Obj_184D78 {
    u8 pad0[0x2C8];
    u64 bits;
    s32 f2D0;
    u8 pad1[0x304 - 0x2D4];
    s32 f304;
    s32 f308;
};



struct __attribute__((aligned(16))) Vec4_264770 { f32 x, y, z, w; };
struct Vec2_2647A0 { f32 a, b; };

void func_00121338(Attachment* self);



extern s32 D_00261F14;
extern u8 D_00211E10[];
void func_001F6C20(s32 unused);
void func_00202A80(void* dma, void* addr);
s32 func_00202C38(void* dma, s32 b, s32 c);



extern u8 D_00261F18[];
extern u8 D_00212110[];

void func_001F6C20(s32 a);
void func_00202A80(void* a, void* b);
s32 func_00202C38(void* a, s32 b, s32 c);

struct Flags_185AC8 {
    s32 flags;
};



struct Cfg_275F80 { s32 a; s32 mode; };
struct Flag_269A00 { s32 a; s32 on; };

extern Flag_269A00 D_00269A00;
extern Cfg_275F80 D_00275F80;
extern s32 D_00275AF0;
extern u8 D_00275BC0[];
extern s32 D_002622CC;

void func_001FAE18(void);
void func_00185B38(void);
void func_0015F210(s32 flag);
void func_0018F148(void* p);
void func_001E4EA8(void* p);
void func_0016E238(void* p);
void func_0016F2E0(void);
void func_0018BDC8(void* p);
void func_001E9108(void* p);
void func_001607D0(f32 dt);
void func_00144270(void* p);
void func_0015E9F0(void);
void func_00142F10(void* p);
void func_0019D6C0(World* o, void* a);
void func_001E9668(void* p);
void func_0019DC98(World* o, void* a);
void func_001E9648(void* p);
void func_0015EC68(void);



struct Frame_185B38 { s32 w[28]; };
typedef void (*Fn_185B38)(void);

// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();

s32 func_00193210(void* a, void* b, void* c, void* d, void* e);
void func_00191E70(s32 value);
void func_00193270(void* p);
void func_00193288(void* self, s32 value);
void func_00193300(void* p);
void func_00191EB0(s32 value);



s32 func_001925F0(void);






void func_00140B60(void* buf, const u8* name, s32 n);
void func_001F7BE8(s32 a);
s32 func_00203548(s32 a);
s32 func_00140968();
void func_001409A8();
s32 func_001F8BF8();
s32 func_001F9C50(void* buf);
s32 func_001F9C18();
s32 func_001F9820();
s32 func_00203828(s32 a);
s32 func_00140D68(s32 a);
s32 func_001F9A90(void* buf, s32 a, s32 b);

s32 func_00184D78(Obj_184D78** a, Obj_184D78** b);
void func_00185358(T2195_790* self);
void func_001853F0(T2195_790* self, void* obj, Vec02* src);
s32 func_00185468(T2195_790* a0);
void func_00185758(s32 a, s32 b);
void func_001858F8();
void func_00185A58(void);
void func_00185AC8();
void func_00185B38(void);

void func_0012B868();
void func_00139C38();
void func_00140790();
void func_001409D8();
void func_0011E560();
void func_001430C8();
void func_00143140();
void func_00152810();
void func_0015C178();
void func_0015E810();
void func_00160070();
void func_001688B8();
void func_00169C58();
void func_0016E0B8();
void func_0016F588();
void func_0017FD48();
void func_0018B580();
void func_0018D430();
void func_0018E5E8();
void func_00191EC0();
void func_0019DF48();
void func_001A9C68();
void func_001BF130();
void func_001DFD48();
void func_001E2398();
void func_001E9088();

struct Ent_264670 { void* f0; s32 f4; s32 f8; s16 fC; s16 fE; };

s32 D_00264260 = 0;
s32 D_00264264 = 0;
void* D_00264268[256] = {0};
s32 D_00264668 = 0;
Ent_264670 D_00264670[16] = {};
Vec4_264770 D_00264770 = { 0.0f, 1.0f, 0.0f, 0.0f };
Vec4_264770 D_00264780 = { -3.4028234663852886e38f, 3.4028234663852886e38f, 0.0f, 0.0f };
Vec4_264770 D_00264790 = { 0.0f, 1.0f, 0.0f, 0.0f };
Vec2_2647A0 D_002647A0 = { -1.0f, 1.0f };
const u8* D_002647A8[6] = {
    (const u8*)"sio2man.irx", (const u8*)"padman.irx", (const u8*)"mcman.irx",
    (const u8*)"mcserv.irx", (const u8*)"libsd.irx", (const u8*)"989snd.irx",
};
Fn_Table D_002647C0[29] = { (Fn_Table)func_0012B868, (Fn_Table)func_0018D430, (Fn_Table)func_00152810, (Fn_Table)func_001E2398, (Fn_Table)func_001688B8, (Fn_Table)func_001858F8, (Fn_Table)func_001409D8, (Fn_Table)func_00140790, (Fn_Table)func_0016E0B8, (Fn_Table)func_0016F588, (Fn_Table)func_0015E810, (Fn_Table)func_0015C178, (Fn_Table)func_0011E560, (Fn_Table)func_00143140, (Fn_Table)func_001BF130, (Fn_Table)func_001A9C68, (Fn_Table)func_001E9088, (Fn_Table)func_001DFD48, (Fn_Table)func_0017FD48, (Fn_Table)func_00191EC0, (Fn_Table)func_00169C58, (Fn_Table)func_00185A58, (Fn_Table)func_00185AC8, (Fn_Table)func_00139C38, (Fn_Table)func_0019DF48, (Fn_Table)func_001430C8, (Fn_Table)func_0018B580, (Fn_Table)func_00160070, (Fn_Table)func_0018E5E8 };
s32 D_00264834;
s32 D_00264838;

s32 func_00184D78(Obj_184D78** a, Obj_184D78** b)
{
    Obj_184D78* x = *a;
    Obj_184D78* y = *b;
    s32 d;

    d = x->f304 - y->f304;
    if (d != 0) {
        return d;
    }
    d = x->f308 - y->f308;
    if (d != 0) {
        return d;
    }
    d = ((s32)(x->bits >> 38) & 1) - ((s32)(y->bits >> 38) & 1);
    if (d != 0) {
        return d;
    }
    return x->f2D0 - y->f2D0;
}

INCLUDE_ASM(func_00184DE8);

ASM_FUNC(func_00185150);

void func_00185358(T2195_790* self)
{
    InitPoseSource(self);
    self->f20 = -1;
    self->f40 = 800.0f;
    self->v50 = *(Vec02*)&D_00264770;
    self->p60 = *(Pk8_2195*)&D_00264780;
    self->v70 = *(Vec02*)&D_00264790;
    self->p80 = *(Pk8_2195*)&D_002647A0;
    self->f44 = 1;
    self->f48 = -1;
}

void func_001853F0(T2195_790* self, void* obj, Vec02* src)
{
    if (obj == 0 || obj == (void*)GetActiveSwitchedCollider()) {
        self->hasTarget = 0;
        self->target = 0;
        self->point = D_00248D30;
    } else {
        self->target = obj;
        self->hasTarget = 1;
        self->point = *src;
    }
}

s32 func_00185468(T2195_790* a0) {
    if (a0->hasTarget == 0) {
        return GetActiveSwitchedCollider();
    }
    return (s32)a0->target;
}

ASM_FUNC(func_00185498);

ASM_FUNC(func_00185538);

void func_00185758(s32 a, s32 b)
{
    func_001FAE18();
    D_00264834 = a;
    D_00264838 = b;
    RunStartupInitializers();
    while (1) {
        if (g_moviePlayer.on != 0 && g_screenFade.mode != 1) {
            DrainRenderFrames(1);
            PlayQueuedMovies(&g_moviePlayer);
        }
        if (g_worldLoadRequest != 0) {
            DrainRenderFrames(1);
            RunPendingWorldLoad(&g_worldLoadRequest);
        }
        if (g_moviePlayer.on != 0 && g_screenFade.mode != 1) {
            DrainRenderFrames(1);
            PlayQueuedMovies(&g_moviePlayer);
        }
        UpdatePadConnection(&g_padRecord);
        RunCompletedButtonCode();
        UpdateMemoryCard(&g_memoryCard);
        UpdateElementStack(g_elementStack);
        AddElapsedTime(g_gameClock.dt);
        if (g_currentWorld != 0) {
            func_00144270(g_camera);
            BeginRenderFrame();
            AdvanceGameClock(&g_gameClock);
            if (g_currentWorld->desc->m11 != 0)
                g_currentWorld->desc->m11(g_currentWorld, g_gameClock.dt);
            RunWorldFrameLists(g_currentWorld, g_camera);
            func_001E9668(g_elementStack);
            func_0019DC98(g_currentWorld, g_camera);
            func_001E9648(g_elementStack);
            SubmitRenderFrame();
        }
        D_002622CC++;
    }
}

void func_001858F8()
{
    u8 buf[0x100];
    FormatDiscPath(buf, (const u8*)"ioprp243.img", 1);
    func_001F7BE8(0);
    func_00203548(0);
    if (func_00140968() == 0) {
        for (;;) {
        }
    }
    func_001409A8();
    func_001F8BF8();
    while (func_001F9C50(buf) == 0) {
    }
    while (func_001F9C18() == 0) {
    }
    func_001F7BE8(0);
    func_001F9820();
    func_00203548(0);
    if (func_00140968() == 0) {
        for (;;) {
        }
    }
    func_001409A8();
    func_001F8BF8();
    func_00203828(0);
    TestDiscReadDone(1);
    for (u32 i = 0; i < 6; i++) {
        FormatDiscPath(buf, g_iopModuleNames[i], 1);
        while (func_001F9A90(buf, 0, 0) < 0) {
        }
    }
}

void func_00185A58(void)
{
    s32* p = (s32*)g_vif0Channel;
    *p |= 0x40;
    func_001F6C20(0);
    func_00202A80((void*)g_vif0Channel, D_00211E10);
    func_00202C38((void*)g_vif0Channel, 0, 0);
    s32* q = (s32*)g_vif0Channel;
    *q &= ~0x40;
}

void func_00185AC8()
{
    Flags_185AC8* p = *(Flags_185AC8**)g_vif1Channel;
    p->flags |= 0x40;
    func_001F6C20(0);
    func_00202A80(*(void**)g_vif1Channel, D_00212110);
    func_00202C38(*(void**)g_vif1Channel, 0, 0);
    (*(Flags_185AC8**)g_vif1Channel)->flags &= ~0x40;
}

void func_00185B38(void)
{
    Frame_185B38 fr;
    u32 i;
    s32 idx;
    Fn_185B38* tbl;

    fr.w[12] = 0x7F0000;
    fr.w[16] = 0x3F3F3F;
    fr.w[20] = 0x3F3F;
    fr.w[24] = 0x3F;
    (void)InitLoadProgress(&fr, &fr.w[12], &fr.w[16], &fr.w[20], &fr.w[24]);
    idx = 0x1A;
    func_00191E70(1);
    func_00193270(&fr);
    tbl = (Fn_185B38*)((u8*)g_startupInitializers);
    i = 0;
    do {
        if ((s32)i >= 3) {
            UpdateLoadProgress(&fr, idx);
        }
        tbl[i]();
        i++;
        idx--;
    } while (i < 0x1D);
    UpdateLoadProgress(&fr, 0);
    func_00193300(&fr);
    func_00191EB0(1);
}
