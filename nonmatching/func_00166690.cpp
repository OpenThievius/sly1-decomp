// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 5796/5772, checked 2026-11-07
// NEAR: func_00166690 at 96.7% (regdiff: code, 1395/1443); the C is 5796 bytes, retail's 5772.
// The structure, switches, calls and packet writes all match. What differs: in the strip loop
// (part->strips) retail keeps &D_002623E0 in s8 and the constant 1 in t9 while ours gives those
// registers to the hoisted UNPACK constants 0x6C0BC000/0x6C01C01A (24 extra bytes of rematerialised
// address/constant loads); c (cache item) is in s2 where retail has s1; a few v0/v1 ties.
#include "common.h"
#include "world.h"
#include "packet_writer.h"

extern World* g_currentWorld;
// Built at startup: the compiler's initialiser and constructor for this file are func_00167D20
// and func_00167D48 (config/us/generated.tsv).
struct ColorWord
{
    union {
        struct { u8 r, g, b, a; };
        u32 rgba;
    };
    ColorWord(u32 v) { rgba = v; }
};
ColorWord D_002623E0(0x80101010);
s32 D_00262474 = 0x28;
extern PacketWriter g_vifPacketWriter;
struct WordCopy {
    static void Words(s32* dst, s32* src, s32 n)
    {
        s32 rem = n & 3;
        s32 bulk = n - rem;
        s32 i;
        for (i = 0; i < rem; i++) {
            *dst++ = *src++;
        }
        for (i = 0; i < bulk; i += 4) {
            s32 a = src[0];
            s32 b = src[1];
            s32 c = src[2];
            s32 d = src[3];
            dst[0] = a;
            dst[1] = b;
            dst[2] = c;
            dst[3] = d;
            src += 4;
            dst += 4;
        }
    }
};
extern u8 D_00001210[];
extern u8 D_00000010[];
void InvertRigidTransform(void* a, void* b, void* out);
// The part drawer func_001533A8 runs for each 0x70-byte part of a placed object: it writes the
// part's header block, its bone matrices and weights and the DMA references of its meshes.
struct Bone_166690 { u8 pad0[0x50]; Mat4 m; };
struct Skin_166690 {
    u8 pad0[4];
    Bone_166690* bones;     // 0x04
    u8 pad8[0x38 - 0x8];
    u32 flags;              // 0x38
    u8 r, g, b, a;          // 0x3C
    s32 count;              // 0x40
    s32* words;             // 0x44
};
struct Slots_166690 { u16 f0; u16 f2; u16 f4; u16 f6; u16 f8; u16 fA; u16 fC; u16 fE; };
struct Mesh_166690 {
    Quad16 pos;             // 0x00
    f32 f10;                // 0x10
    u8 pad14[4];
    u8* kind;               // 0x18
    Slots_166690* slots;    // 0x1C
    u8 pad20[4];
    s32 nbones;             // 0x24
    s32 bones[4];           // 0x28
    s32 f38;                // 0x38
    s32 f3C;                // 0x3C
    s32 f40;                // 0x40
    s32 f44;                // 0x44
    s32 f48;                // 0x48
    s32 f4C;                // 0x4C
};
struct Strip_166690 {
    Slots_166690* slots;    // 0x00
    s32 nbones;             // 0x04
    s32 bones[4];           // 0x08
    s32 f18;                // 0x18
    s32 f1C;                // 0x1C
};
struct Light_166690 { u8 pad0[0x27C]; void* f27C; };
struct Part_166690 {
    u8 pad0[0x10];
    f32 f10;                // 0x10
    u8 pad14[4];
    s32 f18;                // 0x18
    u8 pad1C[0x28 - 0x1C];
    s32 f28;                // 0x28
    u32 flags;              // 0x2C
    u8 pad30[0x40 - 0x30];
    QuadP f40;              // 0x40
    f32 f50;                // 0x50
    s32 f54;                // 0x54
    s32 nmeshes;            // 0x58
    Mesh_166690* meshes;    // 0x5C
    s32 nstrips;            // 0x60
    Strip_166690* strips;   // 0x64
    u8 pad68[4];
    Light_166690* light;    // 0x6C
};
struct Cache_166690 {
    s32 f00;                // 0x00
    s32 f04;                // 0x04
    u8 pad08[4];
    s32 f0C;                // 0x0C
    s32 f10;                // 0x10
    u8 pad14[4];
    f32 f18;                // 0x18
    s32 count;              // 0x1C
    void* nodes[4];         // 0x20
};
struct CacheSet_166690 {
    u8 pad0[4];
    Cache_166690* items;    // 0x04
    s32 f8;                 // 0x08
    s32 fC;                 // 0x0C
    u8 pad10[0x18 - 0x10];
    s32 f18;                // 0x18
    u8 pad1C[0x20 - 0x1C];
    s32 refs[2];            // 0x20
};
struct Class_166690 { u8 pad0[8]; u32 flags; };
struct Owner_166690 { Class_166690* cls; u8 pad4[0x410 - 4]; s32 f410; };
struct Frame_166690 {
    u8 pad0[0x10];
    Mat4A m;                // 0x10
    f32 f50;                // 0x50
    f32 f54;                // 0x54
    u8 pad58[8];
    Quad16 f60;             // 0x60
    Owner_166690* owner;    // 0x70
    Skin_166690* skin;      // 0x74
    Part_166690* part;      // 0x78
    CacheSet_166690* cache; // 0x7C
};
struct Batch_166690 {
    Mat4A m;                // 0x00
    Mat4A m40;              // 0x40
    QuadP f80;              // 0x80
    f32 f90;                // 0x90
    s32 mode;               // 0x94
    s32 f98;                // 0x98
    s32 f9C;                // 0x9C
    union {
        Quad16 fA0;         // 0xA0
        struct { f32 pad[3]; f32 fAC; } w;
    };
};
struct Qw_166690 { u64 lo; u64 hi; };
struct World_166690 { u8 pad0[0x234C]; f32 f234C; };
extern s32 g_lightingChangeFrame;
extern s32 g_lightCount;
extern s32 g_frameCount;
extern Quad4* g_buildFrameData;
extern f32 g_gameClock[];
extern f32 g_gameTime;
s32 CollectLightsForSphere(World* world, void* pos, s32 mode, s32 max, s32* n0, s32* n1, void** out, f32 r);
void CollectRangeRecordsInReach(World* world, void* pos, s32 max, s32* count, void** out, f32 r);
void TransformByMatrixWithW(void* m, void* v, void* out, f32 w);
s32 RangeRecordMatchesKinds(void* node, u32 bits);
s32 RangeRecordReachesSphere(void* node, void* v, f32 f);
void QueueRangeRecordPacket(void* node);
struct Vif_166690 {
    static u32* Open(PacketWriter* w)
    {
        u32* tag = (u32*)w->cur;
        *(u64*)w->cur = 0x10000000;
        w->cur += 16;
        return tag;
    }
    static void Cnt1(PacketWriter* w)
    {
        *(u64*)w->cur = 0x10000001;
        w->cur += 16;
    }
    static void Word(PacketWriter* w, u32 v)
    {
        *(u32*)w->cur = v;
        w->cur += 4;
    }
    static void Copy(PacketWriter* w, void* src, s32 size)
    {
        WordCopy::Words((s32*)w->cur, (s32*)src, size >> 2);
        w->cur += size;
    }
    static void Pad(PacketWriter* w)
    {
        while (w->curU & 0xF) {
            *(u32*)w->cur = 0;
            w->cur += 4;
        }
    }
    static void Close(PacketWriter* w, u32* tag)
    {
        *tag |= ((w->cur - (u8*)tag) >> 4) - 1;
    }
    static void Refs(PacketWriter* w, s32 qwc, s32 addr)
    {
        *(u64*)w->cur = (s64)(qwc | 0x40000000) | ((s64)addr << 32);
        w->cur += 16;
    }
    static void Call(PacketWriter* w, s32 addr)
    {
        *(u64*)w->cur = ((s64)addr << 32) | 0x50000000;
        w->cur += 16;
    }
    static void Mscal(PacketWriter* w, u8* addr)
    {
        Word(w, ((u32)addr >> 3) | 0x14000000);
    }
    static void Mscalf(PacketWriter* w, u8* addr)
    {
        Word(w, ((u32)addr >> 3) | 0x15000000);
    }
    static void Unpack(PacketWriter* w, u32 cmd, void* src, s32 size)
    {
        Word(w, cmd);
        Copy(w, src, size);
    }
    static void UnpackAt(PacketWriter* w, u32 cmd, u32 addr, void* src, s32 size)
    {
        Word(w, cmd | addr);
        Copy(w, src, size);
    }
};
static inline u8 Alpha_166690(u8 a)
{
    if (a <= 0x40) {
        return a;
    }
    if ((s8)a >= 0) {
        return 0x40;
    }
    return 0x80;
}
static inline u64 Rgbaq_166690(u8 a, u8 r, u8 g, u8 b)
{
    return (u64)r | ((u64)g << 8) | ((u64)b << 16) | ((u64)a << 24) | (1ULL << 32);
}
void DrawModelPart(Frame_166690* self)
{
    Batch_166690 b;
    void* lights[128];
    void* nodes[16];
    Qw_166690 q;
    s32 n300;
    s32 n304;
    s32 n308;
    Part_166690* part = self->part;
    Owner_166690* owner = self->owner;
    CacheSet_166690* cache = self->cache;
    Skin_166690* skin = self->skin;
    s32 useCache;
    s32 count;
    s32 i;
    s32 t;
    u32* tag;
    Mesh_166690* e;
    Cache_166690* c;
    f32 r;

    b.m = self->m;
    InvertRigidTransform(&self->m.m[3], &self->m, &b.m40);
    b.f80 = part->f40;
    n300 = 0;
    n304 = 0;
    if (part->f18 != 0) {
        if (part->light != 0) {
            n304 = 1;
            n300 = 1;
            lights[0] = part->light->f27C;
            b.fA0 = self->f60;
            b.mode = 4;
            b.f9C = 2;
        } else if (part->f28 != 0) {
            b.f9C = CollectLightsForSphere(g_currentWorld, &self->f60, 1, 0x80, &n300, &n304, lights, part->f10);
            b.fA0 = self->f60;
            b.mode = 4;
        } else if (cache == 0) {
            b.f9C = CollectLightsForSphere(g_currentWorld, &self->f60, 3, 0x80, &n300, &n304, lights, part->f10);
            b.mode = 2;
        } else if (cache->f8 >= g_lightingChangeFrame) {
            if (g_lightCount != 0) {
                b.f9C = CollectLightsForSphere(g_currentWorld, &self->f60, 2, 0x80, 0, &n304, lights, part->f10);
            }
            if (n304 != 0) {
                b.mode = 1;
                if (b.f9C < cache->fC) {
                    b.f9C = cache->fC;
                }
            } else {
                b.mode = 0;
                b.f9C = cache->fC;
            }
        } else {
            b.f9C = CollectLightsForSphere(g_currentWorld, &self->f60, 7, 0x80, &n300, &n304, lights, part->f10);
            if (n300 == 0 && n304 > 0) {
                b.mode = 2;
            } else {
                b.mode = 3;
                cache->f8 = g_frameCount;
            }
            cache->fC = b.f9C;
        }
    } else {
        b.mode = -1;
        b.f9C = 2;
    }

    useCache = cache != 0 && (owner->cls->flags & 2) && owner->f410 != 0;
    n308 = 0;
    if (!useCache && (part->flags & 3)) {
        CollectRangeRecordsInReach(g_currentWorld, &self->f60, 0x10, &n308, nodes, part->f10);
    }
    b.f90 = self->f50;
    b.f98 = 1;
    if (part->flags & 4) {
        b.w.fAC = 1.0f;
    } else {
        b.w.fAC = ((World_166690*)g_currentWorld)->f234C;
    }
    count = 0;

    if (cache != 0 && cache->f18 != 0 && (b.mode == -1 || b.mode == 0)
        && (useCache || n308 == 0) && !(skin->flags & 3)) {
        if (useCache) {
            for (i = 0; i < part->nmeshes; i++) {
                Cache_166690* t = &cache->items[i];
                if (t->count != 0 && t->f18 == g_gameClock[1]) {
                    goto slow;
                }
            }
        }
        {
            s32 half = D_00262474 != 0x28;
            D_00262474 = 0x23C - D_00262474;
            tag = Vif_166690::Open(&g_vifPacketWriter);
            Vif_166690::Word(&g_vifPacketWriter, D_00262474 | 0x03000000);
            Vif_166690::Word(&g_vifPacketWriter, 0x02000000);
            Vif_166690::Unpack(&g_vifPacketWriter, 0x6C0BC000, &b, 0xB0);
            Vif_166690::Pad(&g_vifPacketWriter);
            Vif_166690::Close(&g_vifPacketWriter, tag);
            Vif_166690::Call(&g_vifPacketWriter, cache->refs[half]);
            if ((part->nmeshes + part->nstrips) & 1) {
                return;
            }
            D_00262474 = 0x23C - D_00262474;
            return;
        }
    }
slow:
    for (i = 0; i < part->nmeshes; i++) {
        s32 k;
        s32 j;
        s32 n;
        e = &part->meshes[i];
        if (cache != 0) {
            c = &cache->items[i];
        } else {
            c = 0;
        }
        D_00262474 = 0x23C - D_00262474;
        tag = Vif_166690::Open(&g_vifPacketWriter);
        count++;
        Vif_166690::Word(&g_vifPacketWriter, D_00262474 | 0x03000000);
        Vif_166690::Word(&g_vifPacketWriter, 0x02000000);
        if (count == 1) {
            Vif_166690::Unpack(&g_vifPacketWriter, 0x6C0BC000, &b, 0xB0);
        }
        if (e->nbones > 0) {
            u32 addr = e->slots->f4;
            for (k = 0; k < e->nbones; k++) {
                Vif_166690::UnpackAt(&g_vifPacketWriter, 0x6C04C000, addr, &skin->bones[e->bones[k]].m, 0x40);
                addr += 4;
            }
        }
        n = skin->count;
        if (n > 0) {
            Vif_166690::UnpackAt(&g_vifPacketWriter, (n << 16) | 0x6000C000, e->slots->f6, skin->words, n * 4);
        }
        Vif_166690::Pad(&g_vifPacketWriter);
        Vif_166690::Close(&g_vifPacketWriter, tag);

        switch (*e->kind) {
        case 0:
            Vif_166690::Refs(&g_vifPacketWriter, e->f38, e->f44);
            switch (b.mode) {
            case 0:
                if (part->f54) {
                    Vif_166690::Call(&g_vifPacketWriter, e->f4C);
                } else {
                    Vif_166690::Refs(&g_vifPacketWriter, e->f40, e->f4C);
                }
                Vif_166690::Refs(&g_vifPacketWriter, c->f00, c->f04);
                Vif_166690::Refs(&g_vifPacketWriter, c->f0C, c->f10);
                break;
            case 1:
                Vif_166690::Refs(&g_vifPacketWriter, c->f0C, c->f10);
                Vif_166690::Refs(&g_vifPacketWriter, e->f3C, e->f48);
                for (k = 0; k < n304; k++) {
                    u8* l = (u8*)lights[k];
                    Vif_166690::Refs(&g_vifPacketWriter, *(s32*)(l + 0x418), (s32)(l + 0x420));
                }
                Vif_166690::Cnt1(&g_vifPacketWriter);
                Vif_166690::Mscal(&g_vifPacketWriter, D_00001210);
                Vif_166690::Word(&g_vifPacketWriter, 0x10000000);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                if (part->f54) {
                    Vif_166690::Call(&g_vifPacketWriter, e->f4C);
                } else {
                    Vif_166690::Refs(&g_vifPacketWriter, e->f40, e->f4C);
                }
                Vif_166690::Cnt1(&g_vifPacketWriter);
                Vif_166690::Mscal(&g_vifPacketWriter, D_00000010);
                Vif_166690::Word(&g_vifPacketWriter, 0x10000000);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                break;
            case 2:
            case 4:
                Vif_166690::Refs(&g_vifPacketWriter, e->f3C, e->f48);
                for (k = 0; k < n304; k++) {
                    u8* l = (u8*)lights[k];
                    Vif_166690::Refs(&g_vifPacketWriter, *(s32*)(l + 0x418), (s32)(l + 0x420));
                }
                Vif_166690::Cnt1(&g_vifPacketWriter);
                Vif_166690::Mscal(&g_vifPacketWriter, D_00001210);
                Vif_166690::Word(&g_vifPacketWriter, 0x10000000);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                if (part->f54) {
                    Vif_166690::Call(&g_vifPacketWriter, e->f4C);
                } else {
                    Vif_166690::Refs(&g_vifPacketWriter, e->f40, e->f4C);
                }
                Vif_166690::Cnt1(&g_vifPacketWriter);
                Vif_166690::Mscalf(&g_vifPacketWriter, D_00000010);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                break;
            case 3: {
                Vif_166690::Refs(&g_vifPacketWriter, e->f3C, e->f48);
                for (k = 0; k < n300; k++) {
                    u8* l = (u8*)lights[k];
                    Vif_166690::Refs(&g_vifPacketWriter, *(s32*)(l + 0x418), (s32)(l + 0x420));
                }
                Vif_166690::Cnt1(&g_vifPacketWriter);
                Vif_166690::Mscal(&g_vifPacketWriter, D_00001210);
                Vif_166690::Word(&g_vifPacketWriter, 0x90000000);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                {
                    s32 base = D_00262474;
                    u32* p = (u32*)g_buildFrameData++;
                    p[0] = ((base + e->slots->f0) << 4) + 0x1100C000;
                    p[1] = ((base + e->slots->f2) << 4) + 0x1100C000;
                    p[2] = ((base + e->slots->fE) << 4) + 0x1100C000;
                    p[3] = (u32)c;
                }
                if (k < n304) {
                    Vif_166690::Refs(&g_vifPacketWriter, e->f3C, e->f48);
                    for (k = 0; k < n304; k++) {
                        u8* l = (u8*)lights[k];
                        Vif_166690::Refs(&g_vifPacketWriter, *(s32*)(l + 0x418), (s32)(l + 0x420));
                    }
                    Vif_166690::Cnt1(&g_vifPacketWriter);
                    Vif_166690::Mscal(&g_vifPacketWriter, D_00001210);
                    Vif_166690::Word(&g_vifPacketWriter, 0);
                    Vif_166690::Word(&g_vifPacketWriter, 0);
                    Vif_166690::Word(&g_vifPacketWriter, 0);
                }
                if (part->f54) {
                    Vif_166690::Call(&g_vifPacketWriter, e->f4C);
                } else {
                    Vif_166690::Refs(&g_vifPacketWriter, e->f40, e->f4C);
                }
                Vif_166690::Cnt1(&g_vifPacketWriter);
                Vif_166690::Mscalf(&g_vifPacketWriter, D_00000010);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                break;
            }
            }
            break;
        case 1:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            if (part->f54) {
                Vif_166690::Call(&g_vifPacketWriter, e->f44);
            } else {
                Vif_166690::Refs(&g_vifPacketWriter, e->f38, e->f44);
            }
            break;
        case 4:
            if (part->f54) {
                Vif_166690::Call(&g_vifPacketWriter, e->f44);
            } else {
                Vif_166690::Refs(&g_vifPacketWriter, e->f38, e->f44);
            }
            continue;
        case 5:
            if (part->f54) {
                Vif_166690::Call(&g_vifPacketWriter, e->f44);
            } else {
                Vif_166690::Refs(&g_vifPacketWriter, e->f38, e->f44);
            }
            continue;
        default:
            continue;
        }

        if (useCache) {
            if (c->f18 == g_gameTime) {
                n308 = c->count;
            } else {
                n308 = 0;
            }
        }
        if (n308 != 0) {
            TransformByMatrixWithW(&b, e, &q, 1.0f);
            r = e->f10 * part->f50;
        }
        for (j = 0; j < n308; j++) {
            void* node;
            if (useCache) {
                node = c->nodes[j];
            } else {
                node = nodes[j];
                if (RangeRecordMatchesKinds(node, part->flags) == 0) {
                    continue;
                }
            }
            if (RangeRecordReachesSphere(node, &q, r) != 0) {
                QueueRangeRecordPacket(node);
            }
        }
    }

    if (skin != 0 && (skin->flags & 1)) {
        return;
    }
    if (self->f54 <= 0.0f) {
        return;
    }
    for (t = 0; t < part->nstrips; t++) {
        Strip_166690* s = &part->strips[t];
        s32 n;
        if (skin != 0 && (skin->flags & 2)) {
            u8 a = Alpha_166690((s32)(skin->a * self->f54));
            q.hi = 1;
            q.lo = Rgbaq_166690(a, skin->r, skin->g, skin->b);
        } else {
            q.lo = Rgbaq_166690(Alpha_166690((s32)(D_002623E0.a * self->f54)), D_002623E0.r, D_002623E0.g, D_002623E0.b);
            q.hi = 1;
        }
        D_00262474 = 0x23C - D_00262474;
        tag = Vif_166690::Open(&g_vifPacketWriter);
        count++;
        Vif_166690::Word(&g_vifPacketWriter, D_00262474 | 0x03000000);
        Vif_166690::Word(&g_vifPacketWriter, 0x02000000);
        if (count == 1) {
            Vif_166690::Unpack(&g_vifPacketWriter, 0x6C0BC000, &b, 0xB0);
        }
        if (s->nbones > 0) {
            u32 addr = s->slots->f8;
            s32 k;
            for (k = 0; k < s->nbones; k++) {
                Vif_166690::UnpackAt(&g_vifPacketWriter, 0x6C04C000, addr, &skin->bones[s->bones[k]].m, 0x40);
                addr += 4;
            }
        }
        n = skin->count;
        if (n > 0) {
            Vif_166690::UnpackAt(&g_vifPacketWriter, (n << 16) | 0x6000C000, s->slots->fA, skin->words, n * 4);
        }
        Vif_166690::Unpack(&g_vifPacketWriter, 0x6C01C01A, &q, 0x10);
        Vif_166690::Pad(&g_vifPacketWriter);
        Vif_166690::Close(&g_vifPacketWriter, tag);
        Vif_166690::Refs(&g_vifPacketWriter, s->f18, s->f1C);
    }
}
