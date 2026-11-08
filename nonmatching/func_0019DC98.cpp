// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 205/264 (77.7%), checked 2026-11-08
// NEAR: order: the frame is exact with DeferredRequest* list[0x412]; retail hoists lui
//       hi(D_0026AC10) and a copy into s4 above the first call, this form hoists D_002622A8's high
//       half instead. Night-low1 (2026-11-08): a pointer to g_nextDeferredRequest taken before
//       the first call keeps the full address in s4 (addiu s4, v0, lo) instead of the high half,
//       further.
// Tried (order-class pass): a pointer to the struct or to its field taken before UploadLightVolumes (also used for the final store), the end pointer as a local: 18 to 20 words.
#include "common.h"
#include "packet_writer.h"
#include "globals.h"
#include "deferred_request.h"

struct Obj_26AC10 { DeferredRequest* p0; u8 pad04[12]; };
extern Obj_26AC10 g_nextDeferredRequest;
extern s32 D_00604780;
extern s32 D_00604784;
extern u32 g_cameraUploadedThisFrame;
extern u32 D_0060478C;
extern s32 D_00262474;
extern u8 D_002BDC20[];
struct Obj_19DC98;
typedef void (*Fn_19DC98)(void* self);
struct Obj_19DC98 { Fn_19DC98* vtbl; };

void UploadLightVolumes(void);
s32 BucketDeferredRequests(s32 n, DeferredRequest* items, void** out);
void CloseDmaTag(void* self);
void BeginDmaTag(void* self);
void WriteVifDirect(void* self, s32 n, void* buf, s32 flag);

void SubmitDeferredRequests(void)
{
    DeferredRequest* list[0x412];
    UploadLightVolumes();
    s32 n = g_nextDeferredRequest.p0 - g_deferredRequests;
    D_00604784 = 0;
    D_00262474 = 0x214;
    D_00604780 = 0;
    g_cameraUploadedThisFrame = 0;
    D_0060478C = 0;
    s32 count = BucketDeferredRequests(n, g_deferredRequests, (void**)list);
    g_vifPacketWriter.f20 = 1;
    CloseDmaTag(&g_vifPacketWriter);
    for (s32 i = 0; i < count; i++) {
        ((Fn_19DC98)list[i]->callback)(list[i]);
    }
    BeginDmaTag(&g_vifPacketWriter);
    if (count == 0) {
        WriteVifDirect(&g_vifPacketWriter, 0x2C, D_002BDC20, 0);
    }
    g_nextDeferredRequest.p0 = 0;
}
