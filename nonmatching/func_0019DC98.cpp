// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 205/264 (77.7%), checked 2026-11-06
// NEAR: order: the frame is exact with DeferredRequest* list[0x412]; retail hoists lui
//       hi(D_0026AC10) and a copy into s4 above the first call, this form hoists D_002622A8's high
//       half instead.
#include "common.h"
#include "v24a0.h"
#include "globals.h"
#include "deferred_request.h"

struct Obj_26AC10 { DeferredRequest* p0; u8 pad04[12]; };
extern Obj_26AC10 D_0026AC10;
extern s32 D_00604780;
extern s32 D_00604784;
extern u32 D_00604788;
extern u32 D_0060478C;
extern s32 D_00262474;
extern u8 D_002BDC20[];
struct Obj_19DC98;
typedef void (*Fn_19DC98)(void* self);
struct Obj_19DC98 { Fn_19DC98* vtbl; };

void func_00184DE8(void);
s32 func_0019D4B0(s32 n, DeferredRequest* items, void** out);
void func_00152D70(void* self);
void func_00152B38(void* self);
void func_001EE7D0(void* self, s32 n, void* buf, s32 flag);

void func_0019DC98(void)
{
    DeferredRequest* list[0x412];
    func_00184DE8();
    s32 n = D_0026AC10.p0 - D_005E4700;
    D_00604784 = 0;
    D_00262474 = 0x214;
    D_00604780 = 0;
    D_00604788 = 0;
    D_0060478C = 0;
    s32 count = func_0019D4B0(n, D_005E4700, (void**)list);
    D_002622A8.f20 = 1;
    func_00152D70(&D_002622A8);
    for (s32 i = 0; i < count; i++) {
        ((Fn_19DC98)list[i]->callback)(list[i]);
    }
    func_00152B38(&D_002622A8);
    if (count == 0) {
        func_001EE7D0(&D_002622A8, 0x2C, D_002BDC20, 0);
    }
    D_0026AC10.p0 = 0;
}
