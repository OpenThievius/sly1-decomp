// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "fpu.h"
#include "vu0.h"
#include "path_curve_object.h"
#include "world.h"
#include "packet_writer.h"
#include "list_iter.h"
#include "shapes.h"
#include "globals.h"
#include "range_record.h"
#include "collider.h"
#include "game_clock.h"
#include "cursor_animator.h"
#include "asm_func.h"
struct Mat02;
struct Vec02;


void InvalidateRangeRecordPacket(RangeRecord* o);
extern "C" void* FillMemory(void* p, s32 value, s32 size);
extern s32 g_meshQueueCount;
extern u8 D_0027DC20[];
void LinkRangeRecord(RangeRecord* self, s32 code);
s32 HasRangeRecordRanges(RangeRecord* self);
void StoreRangeRecordNear(RangeRecord* self, f32 v);
void StoreRangeRecordFar(RangeRecord* self, f32 v);
AnimRecord* FindAnimRecord(s32 key);
void UpdateRangeRecordBounds(RangeRecord* o);
struct BufferedStream;
s32 ReadBufferedU8(BufferedStream* self);
PathCurve* CreatePathCurve(s32 kind);
void ReadPropertyRecords(void* self, void* obj);
void BuildRangeRecordPacket(void* o);
s32 RangeRecordReachesSphere(RangeRecord* node, void* a1, f32 f);
extern "C" f32 Tangent(f32 x);
extern u8 D_00248400[];
void BuildMatrixFromRotationAndTranslation(const Vec02* pos, const Mat02* rot, Mat4A* out);
void ReparentObject(BaseObject* self, BaseObject* parent);

// The file's .data, in retail's order.
f32 D_002744F0 = 50.0f;

ASM_FUNC(func_001B1AC8);

void PrepareRangeRecord(RangeRecord* self)
{
    if (self->link == 0) {
        LinkRangeRecord(self, 0x2C);
    }
    if (HasRangeRecordRanges(self) == 0) {
        StoreRangeRecordNear(self, 100.0f);
        StoreRangeRecordFar(self, 400.0f);
    }
    if ((self->link->maskC & 0x10000000) == 0) {
        s32 idx = g_meshQueueCount;
        if (idx < 0x4000) {
            u8* p = D_0027DC20 + idx * 16;
            self->f2D0 = p;
            g_meshQueueCount = idx + 1;
            FillMemory(p, 0, 16);
        }
    }
}

void InvalidateRangeRecordPacket(RangeRecord* self)
{
    self->packetValid = 0;
}

s32 AreFloatsNearlyEqual(f32 a, f32 b, f32 eps);

void UpdateRangeRecordBounds(RangeRecord* self)
{
    Vec02 scaled;
    f32 half;
    f32 t;
    if (AreFloatsNearlyEqual(self->nearRange, self->farRange, 1e-4f)) {
        half = (__builtin_fabsf(self->outerDistance - self->innerDistance)) * 0.5f;
        t = self->innerDistance + half;
        self->halfLength = half;
    } else {
        f32 a = self->innerDistance;
        f32 q = self->farRange;
        f32 b = self->outerDistance;
        f32 p = self->nearRange;
        f32 m = (a * q - b * p) / (p - q);
        f32 d = b - a;
        f32 a2 = a + m;
        f32 b2 = b + m;
        f32 s = Fpu::Sqrt(d * d + q * q);
        f32 u = a2 * s / d;
        f32 w = u + s * 0.5f;
        f32 r = u * w / a2;
        half = Fpu::Sqrt((b2 - r) * (b2 - r) + q * q);
        t = r - m;
        self->halfLength = half;
    }
    Vu0::Q(scaled) = Vu0::MulX(Vu0::Q(self->v20), Vu0::Scalar(t));
    Vu0::Q(self->v50) = Vu0::Add(Vu0::Q(self->v10), Vu0::Q(scaled));
}

void LinkRangeRecord(RangeRecord* self, s32 key)
{
    AnimRecord* found = FindAnimRecord(key != -1 ? key : 0x2C);
    self->link = found;
    if (found)
        InvalidateRangeRecordPacket(self);
}

s32 HasRangeRecordRanges(RangeRecord* p)
{
    s32 r = 0;
    if (0.0f <= p->nearRange && 0.0f <= p->farRange)
        r = 1;
    return r;
}

void StoreRangeRecordNear(RangeRecord* p, f32 v)
{
    p->nearRange = v;
    if (p->farRange < 0.0f)
        p->farRange = v;
    InvalidateRangeRecordPacket(p);
}

void StoreRangeRecordFar(RangeRecord* o, f32 v)
{
    o->farRange = v;
    if (o->nearRange < 0.0f) {
        o->nearRange = v;
    }
    InvalidateRangeRecordPacket(o);
}

s32 AreFloatsNearlyEqual(f32 a, f32 b, f32 tolerance);
void UpdateRangeRecordBounds(RangeRecord* self);

// Two floats within 1e-4 of each other, as an inline function of its own: retail sets the
// tolerance again before each of a vector's three tests, where the constant written at each call
// is shared by CSE in one saved register (func_001B1DE0, func_001B1EC8).
static inline s32 IsNearlyEqual(f32 a, f32 b)
{
    return AreFloatsNearlyEqual(a, b, 0.0001f);
}

void SetRangeRecordPosition(RangeRecord* self, Vec02* v)
{
    u128 a = Vu0::Q(self->v10);
    u128 b = Vu0::Q(*v);
    s32 same = IsNearlyEqual(Vu0::ToFloatMoved(a), Vu0::ToFloatMoved(b))
        && IsNearlyEqual(Vu0::ToFloatY(a), Vu0::ToFloatY(b))
        && IsNearlyEqual(Vu0::ToFloatZ(a), Vu0::ToFloatZ(b));
    if (!same) {
        self->v10 = *v;
        UpdateRangeRecordBounds(self);
        InvalidateRangeRecordPacket(self);
    }
}

void SetRangeRecordDirection(RangeRecord* self, Vec02* v)
{
    u128 a = Vu0::Q(self->v20);
    u128 b = Vu0::Q(*v);
    s32 same = IsNearlyEqual(Vu0::ToFloatMoved(a), Vu0::ToFloatMoved(b))
        && IsNearlyEqual(Vu0::ToFloatY(a), Vu0::ToFloatY(b))
        && IsNearlyEqual(Vu0::ToFloatZ(a), Vu0::ToFloatZ(b));
    if (!same) {
        self->v20 = *v;
        UpdateRangeRecordBounds(self);
        InvalidateRangeRecordPacket(self);
    }
}

void StoreRangeRecordInner(RangeRecord* o, f32 v)
{
    o->innerDistance = v;
    UpdateRangeRecordBounds(o);
    InvalidateRangeRecordPacket(o);
}

void StoreRangeRecordOuter(RangeRecord* o, f32 v)
{
    o->outerDistance = v;
    UpdateRangeRecordBounds(o);
    InvalidateRangeRecordPacket(o);
}

void ScaleRangeRecordByAngle(RangeRecord* o, f32 s) {
    f32 t = Tangent(s * 0.00872664712f);
    o->nearRange = t * o->innerDistance;
    o->farRange = t * o->outerDistance;
    InvalidateRangeRecordPacket(o);
}

void StoreRangeRecordVector(RangeRecord* self, Quad16* src)
{
    *(Quad16*)((u8*)self + 0x30) = *src;
    InvalidateRangeRecordPacket(self);
}

s32 RangeRecordMatchesKinds(RangeRecord* self, u32 bits)
{
    s32 r = 0;
    if (self->link != 0) {
        u32 flags = self->link->maskC;
        Camera* g = g_camera;
        u32 mask = g->f21C;
        s32 ok = 0;
        if ((flags & 0x10000000) != 0 || (mask & flags) == mask) {
            ok = 1;
        }
        if (ok != 0) {
            if (((bits & 1) != 0 && self->link->kind == 2) || ((bits & 2) != 0 && self->link->kind == 3)) {
                r = 1;
            }
        }
    }
    return r;
}

s32 IsRangeRecordBodyCandidate(void* unused, Collider* o)
{
    s32 r = 0;
    if ((o->flags538 & (1UL << 43)) == 0) {
        r = o->faceStarts != 0;
    }
    return r;
}

struct MeshHit {
    Vec02 r0;
    Vec02 r1;
    Vec02 r2;
    Vec02 r3;
    f32 f40;
    f32 f44;
    u8 pad48[0x50 - 0x48];
    void* part;             // 0x50: the part of the body the segment hit
    u8 pad54[0x70 - 0x54];
};
struct RangeDrawPart { u8 pad00[0x2C]; u32 bits; u8 pad30[0x70 - 0x30]; };
struct RangeSlot {
    u8 pad00[0x18];
    f32 stamp;
    s32 count;
    RangeRecord* owners[4];
};
struct RangePartState { s32 w0; RangeSlot* slots; u8 pad08[0x28 - 8]; };
struct RangeFacePair { s32 part; s32 slot; };
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
typedef s32 (*RangeBodyFilter)(void*, Collider*);
void GatherCollidersInSphere(World* world, Collider* skip, f32 radius, Vec02* center, s32 (*filter)(void*, Collider*), void* arg, s32* count, Collider*** out);
s32 CollectTreeNodeSpans(TreeNode03* root, Vec02* a, Vec02* b, s32* groups, s32 max, ColliderSpan* spans);

void UpdateRangeRecord(RangeRecord* self, f32 dt)
{
    Vec02 a;
    Vec02 b;
    s32 count;
    Collider** list;
    PushBackMemoryMark();
    GatherCollidersInSphere(g_currentWorld, 0, self->halfLength, &self->v50, (s32 (*)(void*, Collider*))IsRangeRecordBodyCandidate, 0, &count, &list);
    if (count != 0) {
        *(Vu0::Vec*)&a = Vu0::MulAddX(Vu0::Vec::Of(self->v10), Vu0::Vec::Of(self->v20), Vu0::Vec::ScalarAt(self->innerDistance));
        *(Vu0::Vec*)&b = Vu0::MulAddX(Vu0::Vec::Of(self->v10), Vu0::Vec::Of(self->v20), Vu0::Vec::ScalarAt(self->outerDistance));
    }
    MeshHit hit;
    for (s32 i = 0; i < count; i++) {
        Collider* obj = list[i];
        if (CollectTreeNodeSpans(obj->tree.nodes, &a, &b, 0, 1, (ColliderSpan*)&hit) != 0) {
            if (hit.part != 0) {
                s32 face = ((u8*)hit.part - (u8*)obj->meshCopy.faces) >> 5;
                s32 end = obj->faceStarts[face + 1];
                for (s32 j = obj->faceStarts[face]; j < end; j++) {
                    RangeFacePair* pair = (RangeFacePair*)obj->refs + j;
                    RangeDrawPart* part = (RangeDrawPart*)obj->drawParts + pair->part;
                    if (RangeRecordMatchesKinds(self, part->bits) != 0) {
                        RangePartState* state = (RangePartState*)obj->partStates + pair->part;
                        RangeSlot* slot = state->slots + pair->slot;
                        if (slot->stamp != g_gameClock.time) {
                            slot->stamp = g_gameClock.time;
                            slot->count = 0;
                        }
                        if ((u32)slot->count >= 4) {
                            goto done;
                        }
                        slot->owners[slot->count] = self;
                        slot->count++;
                    }
                }
            }
        }
    }
done:
    PopBackMemoryMark();
}

// What the range record's first unpack holds: a matrix, the sizes of the record's colour bytes
// halved, and the near and far planes of the range with the clip below the near one.
struct RangeUniforms {
    u8 pad00[0x40];
    s32 sizes[4];
    f32 nearZ;
    f32 farZ;
    u8 pad58[4];
    f32 clipZ;
};
void* InitPacketWriter(PacketWriter* p);
void UsePacketBufferMemory(PacketWriter* b, s32 n, void* q);
void ReserveVifUnpack(PacketWriter* s, s32 a, s32 size, s32 d, s32* outSize, u8** outCursor);
void WriteVifMscal(PacketWriter* s, void* data);
void WriteVifFlushE(PacketWriter* s);
void DetachPacketBuffer(PacketWriter* self, u32* outCount, u8** outBegin);
void SubmitMeshQueueEntry(FrameTarget* self);
void BuildBasisFromXAndZHint(const Vec02* x, const Vec02* hint, Mat02* out);
s32 AreFloatsNearlyEqual(f32 a, f32 b, f32 eps);
void InitIdentityMatrix(Mat4* self);
void BuildProjectionMatrix(Mat4* self, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f);
void BuildViewProjectionMatrix(f32* b, f32* a, void* c, Quad16* out);
void CopyMemory(void* dst, void* src, u32 size);
extern u8 D_000003B0[];
extern f32 D_002744F0;

void BuildRangeRecordPacket(RangeRecord* self)
{
    if (self->link != 0) {
        Camera* g = g_camera;
        s32 bits = self->link->maskC;
        s32 need = g->f21C;
        s32 ok = 0;
        if ((bits & 0x10000000) != 0 || (need & bits) == need) {
            ok = 1;
        }
        if (ok != 0) {
            PacketWriter pw;
            u8 spare[16];
            Vec02 pos;
            Mat02 basis;
            Mat4A proj;
            Vec02 axis;
            RangeUniforms* p;
            InitPacketWriter(&pw);
            u8* dst = self->f2D0;
            if (dst == 0) {
                dst = spare;
            }
            UsePacketBufferMemory(&pw, 0x20, (u8*)self + 0xD0);
            ReserveVifUnpack(&pw, 0xC, 6, 0x16, 0, (u8**)&p);
            AnimRecordEntry* ents = self->link->ents;
            ReserveVifUnpack(&pw, 0xC, ents->type, 0x1C, (s32*)dst, (u8**)(dst + 8));
            *(s32*)(dst + 4) = ents->addr;
            *(s32*)(dst + 0xC) = 0;
            SubmitMeshQueueEntry((FrameTarget*)dst);
            WriteVifMscal(&pw, D_000003B0);
            WriteVifFlushE(&pw);
            DetachPacketBuffer(&pw, (u32*)&self->packetValid, 0);
            axis = self->v20;
            BuildBasisFromXAndZHint(&axis, &self->v30, &basis);
            if (AreFloatsNearlyEqual(self->nearRange, self->farRange, 0.0001f) != 0) {
                pos = self->v10;
                InitIdentityMatrix((Mat4*)&proj);
                f32 half = 0.5f;
                f32 q = half / self->nearRange;
                proj.m[0][0] = q;
                proj.m[1][1] = q;
                proj.m[3][0] = half;
                proj.m[3][1] = half;
                p->nearZ = -3.40282347e+38f;
                p->farZ = 3.40282347e+38f;
                p->clipZ = self->innerDistance - D_002744F0;
            } else {
                f32 k = (self->farRange * self->innerDistance - self->nearRange * self->outerDistance) / (self->farRange - self->nearRange);
                f32 lo = self->innerDistance - k;
                Vu0::Set(pos, Vu0::MulAddX(Vu0::Q(self->v10), Vu0::Q(axis), Vu0::Scalar(k)));
                f32 hi = self->outerDistance - k;
                BuildProjectionMatrix((Mat4*)&proj, 0.5f / (self->nearRange / lo), 0.5f / (self->nearRange / lo), 0.5f, 0.5f, lo, hi);
                if (lo < hi) {
                    p->nearZ = lo;
                    p->farZ = hi;
                } else {
                    p->nearZ = hi;
                    p->farZ = lo;
                }
                p->clipZ = p->nearZ - D_002744F0;
            }
            BuildViewProjectionMatrix((f32*)&pos, (f32*)&basis, &proj, (Quad16*)((u8*)self + 0x70));
            CopyMemory(p, (u8*)self + 0x70, 0x40);
            for (s32 i = 0; i < 4; i++) {
                p->sizes[i] = ((((u8*)self->link) + i)[4] + 1) >> 1;
            }
        }
    }
}

void QueueRangeRecordPacket(RangeRecord* o)
{
    if (o->link != 0) {
        Camera* c = g_camera;
        s32 bits = o->link->maskC;
        s32 need = c->f21C;
        s32 a2 = 0;
        if ((bits & 0x10000000) != 0) {
            goto set;
        }
        if ((need & bits) != need) {
            goto skip;
        }
    set:
        a2 = 1;
    skip:
        if (a2 != 0) {
            if (o->packetValid == 0) {
                BuildRangeRecordPacket(o);
                if (o->packetValid == 0) {
                    goto done;
                }
            }
            PacketWriter* g = &g_vifPacketWriter;
            u64 hi = (u64)(u32)((u8*)o + 0xD0) << 32;
            u64 v = (u64)(s64)(o->packetValid | 0x40000000) | hi;
            *(u64*)g->cur = v;
            g->cur = g->cur + 0x10;
        }
    }
done:
    ;
}

ASM_FUNC(func_001B26F8);

void CollectRangeRecordsInReach(World* self, void* a1, s32 max, s32* outCount, RangeRecord** out, f32 f)
{
    ListFrame frame;
    s32 count = 0;
    RangeRecord* node;
    for (node = (RangeRecord*)self->list1C00.head; node != 0; node = node->next) {
        if (RangeRecordReachesSphere(node, a1, f) == 0) {
            continue;
        }
        if (count < max) {
            *out = node;
            out++;
            count++;
        } else {
            break;
        }
    }
    *outCount = count;
}

void LoadPathCurveObject(PathCurveObject* self, void* obj)
{
    PathCurve* p = CreatePathCurve(ReadBufferedU8((BufferedStream*)obj));
    self->curve = p;
    void (*fn)(PathCurve* self, void* stream) = p->vt->m00;
    if (fn != 0) {
        fn(p, obj);
    }
    ReadPropertyRecords(self, obj);
}

void ReparentPathCurveObject(PathCurveObject* self, BaseObject* other)
{
    Mat4A a;
    Mat4A b;
    PathCurve* h;
    if (self->parent) {
        BuildMatrixFromRotationAndTranslation((const Vec02*)((u8*)self->parent + 0x140), (const Mat02*)((u8*)self->parent + 0x110), &a);
    } else {
        a = *(Mat4A*)D_00248400;
    }
    if (other) {
        BuildMatrixFromRotationAndTranslation((const Vec02*)((u8*)other + 0x140), (const Mat02*)((u8*)other + 0x110), &b);
    } else {
        b = *(Mat4A*)D_00248400;
    }
    h = self->curve;
    if (h->vt->m04) {
        h->vt->m04(h, &a, &b);
    }
    ReparentObject(self, other);
}
