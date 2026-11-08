// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 1728/1708, checked 2026-11-08
// NEAR: the view walk, the VIF packet and the merged tails are retail's shape; left: retail spills frames/count/sent (count re-read each pass of the frame loop, which counts up, where loop.c here reverses it), the count == 0 return is cross-jumped into the end in retail (ours loads the pop's address high half into v1, retail a0), and the first walk's vector loads are scheduled a little apart.
#include "common.h"
#include "asm_func.h"
#include "list_iter.h"
#include "buffered_stream.h"
#include "key_id.h"
#include "world_listed_object.h"
#include "effect_spawner.h"
#include "world.h"
#include "child_group_object.h"
#include "c8b.h"
#include "packet_writer.h"
#include "owned_record.h"
#include "object_message.h"
#include "globals.h"
#include "anim_curve.h"
#include "attachment.h"
#include "cursor_animator.h"
#include "texture_table.h"
#include "vu0.h"
#include "placed_object.h"
#include "collider.h"

struct DeferredRadiusRequest { void (*fn)(void* self); s32 zero; s32 count; u8 pad0[0x50 - 0x0C]; f32 radius; u8 pad1[0x60 - 0x54]; void* owner; u8 pad2[0x80 - 0x64]; };
extern f32 g_gameClock[];
extern s32 g_alphaStatePacket1;
extern s32 g_alphaStatePacket2;
s32 IsListEmpty(void* sub);
void PopBackMemoryMark(void);

// An object of a spawner's list as func_0013AD80 draws it: the record whose 0x7C gives the frame.
struct Mat4x4Copy { u128 r[4]; };
struct ViewedPartRecord { u8 pad0[0x7C]; PlacedObject* frame; };
struct ViewedPart : PlacedObject { ViewedPartRecord* rec; };
// A mesh of a listed object's own list: two banks of vertex data, the bank in use and the count.
struct ListedMesh { u8 bank[2][0x840]; s32 current; s32 count; };
// A matrix the object is drawn at and its fade (0x50 bytes, AllocateBackMemory).
struct ViewedFrame { f32 m[4][4]; f32 fade; u8 pad44[0x50 - 0x44]; };

void PushBackMemoryMark();
void* AllocateBackMemory(s32 size);
s32 CountListItems(void* list);
s32 IsObjectAttached(void* obj);
s32 ComputeCameraDistanceFade(Camera* self, u128 d, f32* fade, f32 radius, f32 x);
void BuildMatrixFromRotationAndTranslation(Vec02* pos, Mat02* rot, ViewedFrame* out);
void BeginDmaTag(PacketWriter* w);
void CloseDmaTag(PacketWriter* w);
void FlipVifBaseOffset();
void ReserveVifUnpack(PacketWriter* w, s32 tag, s32 size, s32 a3, void* a4, void* out);
void CopyWordsToWriter(PacketWriter* w, s32 tag, s32 size, void* src, s32 addr);
void WriteVifUnpack(PacketWriter* w, s32 tag, s32 size, void* src, s32 addr, s32 flag);
void WriteVifStcycl(PacketWriter* w, s32 cl, s32 wl);
void WriteVifMscal(PacketWriter* w, void* addr);
void WriteVifFlush(PacketWriter* w);
extern const f32 D_00248400[28];
extern u8 D_00000000[];
extern u8 D_00000398[];
extern u8 D_00000880[];

// A walk of a list on g_activeListFrames, popped when it ends.
struct ViewListWalk {
    void* list;
    u8* link;
    s32 offset;
    ViewListWalk* prev;
    ViewListWalk(void* l)
    {
        list = l;
        link = (u8*)l;
        offset = ((List01*)l)->offset;
        prev = (ViewListWalk*)g_activeListFrames;
        g_activeListFrames = (ListFrame*)this;
    }
    ~ViewListWalk() { g_activeListFrames = (ListFrame*)prev; }
    void* Next()
    {
        void* n = *(void**)link;
        link = (u8*)n + offset;
        return n;
    }
};

void func_0013AD80(void* self)
{
    DeferredRadiusRequest* req = (DeferredRadiusRequest*)self;
    ViewedFrame one;
    ViewedFrame* frames;
    s32 count;
    s32 sent;
    PushBackMemoryMark();
    WorldListedObject* obj = (WorldListedObject*)req->owner;
    if (obj->source != 0 && IsListEmpty(((EffectSpawner*)obj->source)->list314) == 0) {
        count = 0;
        ViewListWalk walk(((EffectSpawner*)obj->source)->list314);
        frames = (ViewedFrame*)AllocateBackMemory(CountListItems(((EffectSpawner*)obj->source)->list314) * sizeof(ViewedFrame));
        ViewedFrame* cur = frames;
        ViewedPart* e;
        while ((e = (ViewedPart*)walk.Next()) != 0) {
            if ((e->f88 & g_camera->f21C) == g_camera->f21C && IsObjectAttached(e)) {
                Vec02 pos;
                Mat02 rot;
                if (e->rec->frame != 0) {
                    pos = e->rec->frame->v140;
                    rot = e->rec->frame->m110;
                } else {
                    pos = e->v140;
                    if (e->parent != 0)
                        rot = ((PlacedObject*)e->parent)->m110;
                    else
                        rot = g_identityMatrix;
                }
                f32 radius = obj->f2A8;
                Camera* cam = g_camera;
                u128 d = Vu0::Sub(Vu0::Add(Vu0::Rotate(rot, Vu0::Vec::Of(obj->pos)), Vu0::Vec::Of(pos)), Vu0::Vec::Of(cam->f40)).q;
                u128 ones = Vu0::Ones();
                if ((Vu0::PlaneSigns(Vu0::Q(cam->planes[0]), Vu0::Q(cam->planes[1]), Vu0::Q(cam->planes[2]), d, ones, Vu0::Scalar(radius)) ^ 0xF0) == 0) {
                    if (ComputeCameraDistanceFade(cam, d, &cur->fade, radius, e->f80) != 0) {
                        BuildMatrixFromRotationAndTranslation(&pos, &rot, cur);
                        cur++;
                        count++;
                    }
                }
            }
        }
        if (count == 0) {
            PopBackMemoryMark();
            return;
        }
    } else {
        frames = &one;
        count = 1;
        *(Mat4x4Copy*)one.m = *(const Mat4x4Copy*)D_00248400;
        one.fade = req->radius;
    }
    sent = 0;
    BeginDmaTag(&g_vifPacketWriter);
    ViewListWalk walk(&obj->members);
    ListedMesh* mesh;
    while ((mesh = (ListedMesh*)walk.Next()) != 0) {
        FlipVifBaseOffset();
        if (sent++ < 2) {
            f32* p;
            s32* q;
            ReserveVifUnpack(&g_vifPacketWriter, 0xC, 1, 5, 0, &p);
            Camera* cam = g_camera;
            p[0] = cam->fC0;
            p[1] = cam->fD4;
            p[2] = obj->f61C;
            p[3] = g_gameClock[1];
            ReserveVifUnpack(&g_vifPacketWriter, 0xC, 1, 6, 0, &q);
            q[0] = 0;
            if (obj->f614 != 0)
                q[0] |= 1;
            q[1] = obj->colorCount;
            q[2] = obj->regCount;
            *(f32*)&q[3] = g_gameClock[5];
            CopyWordsToWriter(&g_vifPacketWriter, 0xE, obj->colorCount, obj->color, 0x30 - obj->colorCount);
            CopyWordsToWriter(&g_vifPacketWriter, 8, 1, obj->curve2F0, 1);
            CopyWordsToWriter(&g_vifPacketWriter, 8, 1, obj->curve2E0, 2);
            CopyWordsToWriter(&g_vifPacketWriter, 8, 1, &obj->q300, 3);
            CopyWordsToWriter(&g_vifPacketWriter, 8, 1, obj->curve310, 4);
            CopyWordsToWriter(&g_vifPacketWriter, 0xC, 4, (void*)((obj->flagRecord->flags & 1) != 0 ? g_alphaStatePacket2 : g_alphaStatePacket1), 0x30);
            WriteVifUnpack(&g_vifPacketWriter, 0xC, obj->regCount, obj->regs, 0xF, 0);
        }
        u8* bank = mesh->bank[mesh->current];
        u16 hdr[3];
        hdr[0] = 0x34;
        hdr[1] = mesh->count * 10 + 0x34;
        hdr[2] = mesh->count;
        CopyWordsToWriter(&g_vifPacketWriter, 9, 1, hdr, 0);
        ViewedFrame* f = frames;
        for (s32 i = 0; i < count; i++) {
            Vec02 fade;
            CopyWordsToWriter(&g_vifPacketWriter, 0xC, 4, f, 7);
            fade.x = f->fade;
            CopyWordsToWriter(&g_vifPacketWriter, 0xC, 1, &fade, 0xB);
            WriteVifStcycl(&g_vifPacketWriter, 1, 10);
            if (obj->f618 == 1)
                WriteVifUnpack(&g_vifPacketWriter, 0xC, mesh->count, bank + 0x2C0, hdr[0] + 1, 0);
            WriteVifUnpack(&g_vifPacketWriter, 0xC, mesh->count, bank + 0x580, hdr[0] + 2, 0);
            WriteVifUnpack(&g_vifPacketWriter, 0xC, mesh->count, bank, hdr[0] + 3, 0);
            WriteVifStcycl(&g_vifPacketWriter, 1, 1);
            switch (obj->f618) {
            case 0:
                WriteVifMscal(&g_vifPacketWriter, D_00000000);
                WriteVifFlush(&g_vifPacketWriter);
                break;
            case 1:
                WriteVifMscal(&g_vifPacketWriter, D_00000398);
                WriteVifFlush(&g_vifPacketWriter);
                break;
            case 2:
                WriteVifMscal(&g_vifPacketWriter, D_00000880);
                WriteVifFlush(&g_vifPacketWriter);
                break;
            default:
                WriteVifFlush(&g_vifPacketWriter);
                break;
            }
            f++;
        }
    }
    CloseDmaTag(&g_vifPacketWriter);
    PopBackMemoryMark();
}
