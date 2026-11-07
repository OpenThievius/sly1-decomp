// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "switched_collider.h"
#include "asm_func.h"
#include "fpu.h"
#include "list_iter.h"
#include "packet_writer.h"
#include "screen_element.h"
#include "message_body.h"
#include "shapes.h"
#include "camera.h"
#include "state_walker.h"
#include "object_pool.h"
extern u8* D_00262E10;
extern u8* D_00275710;

void func_001921A8(void* self);
void* func_0018D500(s32 size);

void func_001E5378(PlayerLinkedCollider* self)
{
    InitSwitchedCollider(self);
    self->f644 = 1;
    self->f63C = AllocateFrontMemory(0x40);
    self->f640 = AllocateFrontMemory(0x40);
    self->f658 = -1.5f;
    self->f65C = 1.5f;
    self->f650 = -0.7f;
    self->f654 = 0.7f;
}

void func_001E53F8(PlayerLinkedCollider* self, void* value)
{
    s32 n = self->f638;
    if (n < 0x11) {
        ((void**)self->f640)[n] = value;
        self->f638 = n + 1;
    }
}

typedef void (*ListenFn)(void* self, void* other);

struct ListenerObject {
    ListenFn* vtbl;
};

struct OwnedAgent {
    u8 pad0[0xC2C];
    PlayerLinkedCollider* owner;
};

extern s32 D_00275B28[10];

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 n, void* table);
void* func_001B6290(void* a, void* self, s32 b, s32 c);
void* func_0015A448(void* a, s32 b, void* c);
s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);
void func_00189230(void* a, void* b, void* c);

void func_001E5428(PlayerLinkedCollider* self)
{
    void* r2;
    s32 i;
    s32 n;
    void* r;

    StartPlacedObject(self);
    ResolveObjectLinks(self, 3, D_00275B28);
    self->f614 = (StateWalker*)CreateStateWalker(self->f610, self, -1, 1);
    r = FindFirstObjectByIdMode4(g_currentWorld, 7, self);
    if (r != 0) {
        self->f620 = r;
        self->f624 = r;
        ((OwnedAgent*)r)->owner = self;
        self->f598 = r;
        self->f584 = (void*)FindFirstObjectById(self->world, 1, 0x160, r);
        i = 0;
        do {
            self->f588[i] = (void*)FindFirstObjectById(self->world, 1, i + 0x161, r);
            i++;
        } while (i < 3);
        self->f594 = 300.0f;
        ((ListenerObject*)r)->vtbl[27](r, self);
    } else {
        self->f620 = (void*)g_player;
    }

    n = 0;
    while (n < self->f638) {
        r2 = FindFirstObjectByIdMode4(self->world, ((s32*)self->f640)[n], self);
        if (r2 != 0) {
            ((void**)self->f63C)[n] = r2;
            n++;
        }
    }
    self->f638 = n;
    VectorToAngles((u8*)self + 0x110, (u8*)self + 0x648, (u8*)self + 0x64C);
}

void func_00192B58(void* self);
s32 func_0015A4F0(void* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);
void func_001C8F20(void* node, s32 kind, s32 flag);

void func_001E55D0(PlayerLinkedCollider* self)
{
    void* arr[8];
    s32 n;
    s32 count;
    s32 i;

    UpdateSwitchedCollider(self);
    if (((SwitchedCollider*)self->f620) != 0) {
        if (((SwitchedCollider*)self->f620)->desc05()->m4D(((SwitchedCollider*)self->f620))) {
            n = GatherObjectsById(self->world, 5, 8, 0, 8, arr);
            if (n > 0) {
                count = n;
                i = 0;
                do {
                    void* item = arr[i];
                    if (item != self->f620) {
                        if (((Agent*)item)->f724 != 0xB) {
                            ChangeAgentState(item, 0xA, 0);
                        }
                    }
                    count--;
                    i++;
                } while (count != 0);
            }
            self->f580 = 0;
        } else {
            self->f580 = 1;
        }
    }
}

extern u8* D_00262E10;

typedef void (*VFn_56A0)(void* self, f32 t, void* buf);

void func_001E5938(void);
void func_0016EC20(void* obj, s32 n);
void func_001E5C78(void* self);
s32 func_00182FC8(void);
void func_001F5C0C(void* p, s32 v, s32 n);

void func_001E56A0(PlayerLinkedCollider* self, void* obj, f32 t)
{
    u8 buf[0xC4];
    u8* o;

    ChoosePlayerLinkedColliderTarget();
    if (*(u16*)((u8*)obj + 0xAA) & 0xC0) {
        ClearPadPressedBits(obj, 0xC0);
        AdvancePlayerLinkedColliderWalker(self);
    }
    o = g_player;
    if (o != 0) {
        if (*(s32*)(o + 0x2740) != 0) {
            if (IsObjectAttached()) {
                VFn_56A0 fn;
                FillMemory(buf, 0, 0xC4);
                o = g_player;
                fn = *(VFn_56A0*)(*(u8**)o + 0x134);
                if (fn != 0) {
                    fn(o, t, buf);
                }
            }
        }
    }
}

extern Camera* D_00261990;
extern u8 D_00275BC0[];

void func_001922E8(void* a, void* b);
void func_001E9498(void* self, void* node);
void func_001E9570(void* self);
void func_001356C0(T217D_440* self, s32 mode);
void func_00145088(void* a, s32 b, void* c, void* d, s32 e);
void func_001495E8(void* a, s32 b);
void func_001451F0(void* a, s32 b, s32 c, void* d, void* e, s32 f);
s32 func_00149610(void* a);
void func_001B64D8(void* a, s32 b);

void func_001E5750(PlayerLinkedCollider* self, u8* p)
{
    HandleSwitchedColliderActivation(self, p);
    if (p != 0) {
        g_camera->ctl460.f20 = 100.0f;
        PushStackElement(g_elementStack, &g_typedTextCaptionBox);
        SetTextPanelState(&g_typedTextCaptionBox, 5);
        g_camera->ctl460.f5C = (void*)self->f61C;
        if (self->f630 != 0) {
            *(Quad16*)g_camera->f80 = *(Quad16*)&self->m110.r[0];
            *(Quad16*)g_camera->f90 = *(Quad16*)&self->m110.r[1];
            *(Quad16*)g_camera->fA0 = *(Quad16*)&self->m110.r[2];
        }
        PushCameraController(g_camera, 6, &g_camera->ctl460, self, 0);
        PushStackValue(&g_camera->ctl460, self->f644);
        SetStateWalkerTarget(self->f614, 0x359);
    } else {
        g_camera->ctl460.f20 = 10.0f;
        PopStackElement(g_elementStack);
        RemoveCameraControllers(g_camera, 0xF, 6, &g_camera->ctl460, self, 0);
        PopStackValue(&g_camera->ctl460);
        SetStateWalkerTarget(self->f614, 0x358);
    }
}

s32 func_001A8820(void* p, void* v);

s32 func_001E5888(PlayerLinkedCollider* self, Collider* node)
{
    Collider* a;
    Collider* b;

    if (node->flags538 & (1ULL << 43)) {
        return 0;
    }
    if ((void*)node->root == (void*)self) {
        return 0;
    }
    if (func_001A8820(self->f618, node) != 0) {
        return 0;
    }
    a = node->root03();
    b = (Collider*)self->f618->f48;
    if (a->desc03()->m38(a, b) != 0 || b->desc03()->m38(b, a) != 0) {
        return 0;
    }
    return 1;
}

ASM_FUNC(func_001E5938);

void func_001B6598(void* dev, s32* out);
void func_001B6568(void* dev, s32* out);
s32 func_001A8C50(void* a);
void func_001B64D8(void* dev, s32 value);

void func_001E5C78(PlayerLinkedCollider* self)
{
    s32 a;
    s32 b;
    GetStateWalkerCurrentKey(self->f614, &a);
    GetStateWalkerTargetKey(self->f614, &b);
    if (a == 0x359 && b == a) {
        if (HasObjectPoolChoice(self->f618) != 0) {
            SetStateWalkerTarget(self->f614, 0x35A);
        }
    }
}


void func_00192230(void* self, s32 kind, MessageBody* rec);
s32 func_001A8C90(void* a, s32 b);

void func_001E5CE8(PlayerLinkedCollider* self, s32 kind, MessageBody* rec)
{
    HandleSwitchedColliderNotification(self, kind, rec);
    if (kind == 0x13) {
        StateWalker* dev = self->f614;
        s32 id = rec->sourceId;
        if (id == (s32)dev->player) {
            if (rec->code == 0x35B) {
                func_001A8C90(self->f618, 1);
            }
        } else if (((Agent*)self->f624) != 0 && id == (s32)((Agent*)self->f624)->f7E0) {
            s32 k = rec->code;
            if (k != 0x15E) {
                if (k == 0x15F) {
                    self->f628 = 0;
                }
            } else {
                self->f628 = 1;
            }
        }
    }
}

s32 func_001B8A08(void* a, void* b);
s32 func_001A8820(void* p, void* v);

s32 func_001E5DA8(PlayerLinkedCollider* self, void* arg)
{
    if (TestCollidersMayContact(self, arg)) {
        return 1;
    }
    if (self->f618 != 0) {
        s32 r = func_001A8820(self->f618, arg);
        if (r != 0) {
            return 1;
        }
    }
    return 0;
}

typedef void (*VFn_5E08)(void* self);

void func_001924C8(void* self);

void func_001E5E08(PlayerLinkedCollider* self)
{
    if (self->f624 != 0) {
        VFn_5E08 fn = *(VFn_5E08*)(*(u8**)self->f624 + 0x148);
        fn(self->f624);
    } else {
        StartSwitchedColliderEffect(self);
    }
}

struct ZeroPair { s32 lo; s32 hi; };

void func_001E5E50(PlayerLinkedCollider* a0, void* a1, ZeroPair* out)
{
    out->lo = 0;
    out->hi = 0;
}

void* func_001E5E60(PlayerLinkedCollider* self) { return self->f620 ? self->f620 : self; }

// A view of the vertices that starts one vertex before the first (0x254): through it, the fields
// of the vertex i are at 0x2C more (x at 0x2C, y at 0x34, the colours at 0x3C and 0x40, the
// brightness at 0x44 and 0x48, the rates from 0x4C), and the previous vertex's next place is at
// 0x04 and 0x0C.
struct ArcPointStep {
    u8 pad0[4];
    f32 f4;
    u8 pad1[4];
    f32 fC;
    u8 pad2[0x2C - 0x10];
    f32 f2C;
    u8 pad3[4];
    f32 f34;
    u8 pad4[4];
    u32 f3C;
    u32 f40;
    f32 f44;
    f32 f48;
    f32 f4C;
    f32 f50;
    f32 f54;
};

void func_001AA1F0(ScreenElement* self, s32 kind);
f32 func_001EAAE0(f32 a, f32 b);

void func_001E5E70(T217D_3F0* self, s32 kind)
{
    self->w = 160.0f;
    self->h = 125.4f;
    self->lineLen = self->lineLen2 = 3.3000002f;
    InitScreenElement(self, kind);
    f32 sign;
    if (kind == 0x1A) {
        self->edgeTo = 0.0f;
        self->edgeFrom = self->w - 62.7f;
        sign = 1.0f;
    } else {
        self->edgeTo = self->w;
        self->edgeFrom = 62.7f;
        sign = -1.0f;
    }
    f32 step = 1.0f / 57.0f;
    s32 i = 0;
    u32 dim = 0x30000000;
    s32 special = 0x1A;
    ArcPointStep* p;
    for (p = (ArcPointStep*)(self->pts - 1); i < 0x39; i++) {
        f32 t = (f32)i * step;
        f32 y = t + t - 1.0f;
        p->f34 = y;
        p->f2C = sign * Fpu::Sqrt(1.0f - y * y);
        p->f3C = p->f40 = (i & 1) ? dim : 0x30808080;
        p->f44 = p->f48 = 0.0f;
        if (self->index == special) {
            p->f4C = RandomFloatInRange(0.6f, 0.8f);
            p->f50 = RandomFloatInRange(0.4f, 0.6f);
            p->f54 = RandomFloatInRange(0.05f, 0.2f);
        } else {
            p->f4C = RandomFloatInRange(0.3f, 0.4f);
            p->f50 = RandomFloatInRange(0.2f, 0.3f);
            p->f54 = RandomFloatInRange(0.1f, 0.4f);
        }
        if (i != 0) {
            p->fC = p->f34;
            p->f4 = p->f2C;
        }
        p = (ArcPointStep*)((u8*)p + 0x2C);
    }
    self->pts[56].nextY = 1.0f;
    self->pts[56].nextX = 0.0f;
    if (self->index == 0x1A) {
        self->pulseA = RandomFloatInRange(1.0f, 1.4f);
        self->pulseB = RandomFloatInRange(0.6f, 0.8f);
        self->pulseC = RandomFloatInRange(0.1f, 0.2f);
    } else {
        self->pulseA = RandomFloatInRange(0.5f, 0.7f);
        self->pulseB = RandomFloatInRange(0.2f, 0.3f);
        self->pulseC = RandomFloatInRange(0.3f, 0.5f);
    }
}

extern u8* D_00275710;
extern u8 D_00275640[];
extern f32 D_00275B58[2];
extern f32 D_00275650;
extern f32 D_00275654;
extern f32 D_00275658;
extern f32 D_0027565C;
extern f32 D_00275660;

typedef void (*ConeSpriteFn)(void* self);
struct ConeSprite { ConeSpriteFn* vtbl; };

void func_001AA268(ScreenElement* self);
void* func_0011E580(s32 a0, void* a1, void* a2, s32 a3, s32 a4);
void func_00184768(void* p, s32 v);
void func_001847F0(void* p, void* q);
void func_00184858(void* p, f32 v);
void func_00184818(void* p, f32 v);
void func_00184878(void* p, f32 v);
void func_00184838(void* p, f32 v);
void func_00184898(void* p, f32 v);
void func_00184990(void* p, void* q);
void func_00184968(void* p, s32 v);

void func_001E6188(T217D_3F0* self)
{
    SetupScreenElementText(self);
    self->sprite = CreateTypedRecord(0x51, g_currentWorld, 0, 0x201, -1);
    SetConeVolumeMode(self->sprite, 1);
    SetConeVolumeColor(self->sprite, D_00275640);
    SetConeVolumeFirstAngle(self->sprite, D_00275650);
    SetConeVolumeSecondLevel(self->sprite, D_00275654);
    SetConeVolumeSecondAngle(self->sprite, D_00275658);
    SetConeVolumeThirdLevel(self->sprite, D_0027565C);
    SetConeVolumeThirdAngle(self->sprite, D_00275660);
    SetConeVolumeRange(self->sprite, D_00275B58);
    SetConeVolumeValue(self->sprite, 1);
    ((ConeSprite*)self->sprite)->vtbl[7](self->sprite);
}

void func_001E6268(T217D_3F0* self, s32* first, s32* second) { s32 n = (s32)(self->size * 57.0f); s32 half = (57 - n) / 2; *first = half; *second = half + n; }

extern s32 D_00270458;
void func_00161670(PacketWriter* c, s32 a, s32 b, s32 d, s32 e);
void func_001615F0(PacketWriter* c, s32 a, s32 b, s32 d, s32 e);

void func_001E62A8(T217D_3F0* self, PacketWriter* c, s32 k)
{
    if (D_00270458 == 4) {
        f32 y = self->shownY;
        f32 x = self->shownX;
        s32 x0 = (s32)((x + 1728.0f) * 16.0f);
        s32 y0 = (s32)((y * 0.45454547f + 1936.0f) * 16.0f);
        AddGifXyzfNoDrawEntry(c, x0, y0, k, 0);
        AddGifXyzfNoDrawEntry(c, x0, (s32)(((y + self->h) * 0.45454547f + 1936.0f) * 16.0f), k, 0);
        AddGifXyzfEntry(c, (s32)(((x + self->w) + 1728.0f) * 16.0f), y0, k, 0);
        y = y + self->h;
        x = x + self->w;
        AddGifXyzfEntry(c, (s32)((x + 1728.0f) * 16.0f), (s32)((y * 0.45454547f + 1936.0f) * 16.0f), k, 0);
    } else {
        s32 r[2];
        GetArcVisibleRange(self, &r[0], &r[1]);
        if (r[0] != r[1]) {
            f32 a = self->y + 62.7f;
            f32 b = self->x + self->edgeTo;
            f32 bx = self->x + self->edgeFrom;
            s32 x0, y0, i;
            f32 t;
            y0 = (s32)(((a + self->pts[r[0]].y * 62.7f) * 0.45454547f + 1936.0f) * 16.0f);
            x0 = (s32)((b + 1728.0f) * 16.0f);
            t = bx + self->pts[r[0]].x * 62.7f;
            AddGifXyzfNoDrawEntry(c, x0, y0, k, 0);
            AddGifXyzfNoDrawEntry(c, (s32)((t + 1728.0f) * 16.0f), y0, k, 0);
            for (i = r[0]; i < r[1]; i++) {
                T217D_3F0_Pt* p = &self->pts[i];
                t = bx + p->nextX * 62.7f;
                s32 x = (s32)((b + 1728.0f) * 16.0f);
                y0 = (s32)(((a + p->nextY * 62.7f) * 0.45454547f + 1936.0f) * 16.0f);
                AddGifXyzfEntry(c, x, y0, k, 0);
                AddGifXyzfEntry(c, (s32)((t + 1728.0f) * 16.0f), y0, k, 0);
            }
        }
    }
}

ASM_FUNC(func_001E6600);


extern f32 D_00261868;
extern Rgba4 D_002610D8;
extern Rgba4 D_002610E0;

void func_001613C0(PacketWriter* b, s32 a1, s32 a2, s32 a3);
void func_00161458(PacketWriter* b, u32 c);
void func_001615F0(PacketWriter* b, s32 x, s32 y, s32 a3, s32 a4);

struct ColorLerp {
    static u8 Of(s32 a, s32 b, f32 t)
    {
    if (a == b) return b;
    if (a < b) return a + (s32)(t * ((f32)b + 0.999f - (f32)a));
    return b + (s32)((1.0f - t) * ((f32)a + 0.999f - (f32)b));
    }
};

#define SX_1E6C20(x) ((s32)(((x) + 1728.0f) * 16.0f))
#define SY_1E6C20(y) ((s32)(((y) * 0.45454547f + 1936.0f) * 16.0f))

struct FadeClamp {
    static f32 Of(f32 x, f32 lo, f32 hi)
    {
        if (x < lo) return lo;
        if (hi < x) return hi;
        return x;
    }
};

void func_001E6C20(T217D_3F0* self, PacketWriter* buf)
{
    Rgba4 c;
    f32 t;
    switch (self->fade) {
    case 0:
        t = FadeClamp::Of((g_elapsedTime - self->fadeSince) * 5.0f, 0.0f, 1.0f);
        break;
    case 1:
        t = FadeClamp::Of(1.0f - (g_elapsedTime - self->fadeSince) * 5.0f, 0.0f, 1.0f);
        break;
    }
    BeginGifTag(buf, 0, 1, 1);
    {
        Rgba4 a = D_002610D8;
        Rgba4 b = D_002610E0;
        Rgba4 r;
        r.r = ColorLerp::Of(a.r, b.r, t);
        r.g = ColorLerp::Of(a.g, b.g, t);
        r.b = ColorLerp::Of(a.b, b.b, t);
        r.a = ColorLerp::Of(a.a, b.a, t);
        c = r;
    }
    AddGifRgbaEntry(buf, *(u32*)&c);
    BeginGifTag(buf, 0x44, 1, 4);
    f32 x0 = self->x + self->edgeFrom;
    f32 y0 = self->y + 62.7f;
    f32 xe = self->x + self->edgeTo;
    s32 first, last;
    GetArcVisibleRange(self, &first, &last);
    T217D_3F0_Pt* e = &self->pts[first];
    f32 len = self->lineLen;
    f32 xa = x0 + e->x * 62.7f;
    f32 xb = x0 + (len + 62.7f) * e->x;
    f32 ya = y0 + e->y * 62.7f;
    f32 yb = ya - len;
    AddGifXyzfEntry(buf, SX_1E6C20(xe), SY_1E6C20(ya), 0, 0);
    AddGifXyzfEntry(buf, SX_1E6C20(xe), SY_1E6C20(yb), 0, 0);
    AddGifXyzfEntry(buf, SX_1E6C20(xa), SY_1E6C20(ya), 0, 0);
    AddGifXyzfEntry(buf, SX_1E6C20(xb), SY_1E6C20(yb), 0, 0);
    for (s32 i = first; i < last; i++) {
        e = &self->pts[i];
        xa = x0 + e->x * 62.7f;
        ya = y0 + e->y * 62.7f;
        xb = x0 + (self->lineLen + 62.7f) * e->x;
        yb = y0 + (self->lineLen + 62.7f) * e->y;
        AddGifXyzfEntry(buf, SX_1E6C20(xa), SY_1E6C20(ya), 0, 0);
        AddGifXyzfEntry(buf, SX_1E6C20(xb), SY_1E6C20(yb), 0, 0);
    }
    xa = x0 + e->nextX * 62.7f;
    ya = y0 + e->nextY * 62.7f;
    yb = ya + self->lineLen;
    xb = x0 + (self->lineLen + 62.7f) * e->nextX;
    AddGifXyzfEntry(buf, SX_1E6C20(xa), SY_1E6C20(ya), 0, 0);
    AddGifXyzfEntry(buf, SX_1E6C20(xb), SY_1E6C20(yb), 0, 0);
    AddGifXyzfEntry(buf, SX_1E6C20(xe), SY_1E6C20(ya), 0, 0);
    AddGifXyzfEntry(buf, SX_1E6C20(xe), SY_1E6C20(yb), 0, 0);
}

extern u8 D_00262280[];

s32 func_001E9A68(void);
void func_001613C0(void* p, s32 a, s32 b, s32 c);
void func_00161708(void* p, s32 a, u64 b);
void func_001E6600(void* self, void* p);
void func_001E6C20(void* self, void* p);

void func_001E73B8(T217D_3F0* self)
{
    u8* s = g_gsPacketWriter;
    if (IsArcDrawAllowed()) {
        BeginGifTag(s, 0, 1, 0xE);
        AddGifRegisterWrite(s, 0x47, 0x31001);
        AddGifRegisterWrite(s, 0x42, 0x44);
        WriteArcPointVertices(self, s);
        WriteArcTickVertices(self, s);
    }
}

extern f32 D_00261868;

void func_001E7440(T217D_3F0* a0, s32 a1)
{
    if (a1 != a0->fade) {
        a0->fade = a1;
        a0->fadeSince = g_elapsedTime;
    }
}

void func_00126BC0(PlacedObject* node, T217D_3F0* self);
extern s32 D_00270458;

void func_001E7460(T217D_3F0* self)
{
    PlacedObject* cur = (PlacedObject*)self->current;
    if ((PlacedObject*)self->target == cur) {
        return;
    }
    if (cur != 0) {
        if (!(D_00270458 == 4 && cur == (PlacedObject*)self->special)) {
            cur->desc->m03(cur);
        }
    }
    self->current = self->target;
    if (self->current != 0) {
        ((PlacedObject*)self->current)->desc->m02((PlacedObject*)self->current);
        if (D_00270458 != 4) {
            SetObjectTreeRecordsValue((PlacedObject*)self->current, self);
        }
        ((PlacedObject*)self->current)->flags |= 0x100000000UL;
    }
}

extern f32 D_00261858[];
f32 func_001EAAE0(f32 a, f32 b);
void func_001BFCD8(s32 id, s32 a, s32 b, s32 c, f32 f0, f32 f1, f32 f2, f32 f3, f32 f4, s32 d, s32 e);

void func_001E7518(T217D_3F0* self, s32 mode)
{
    if (mode == self->phase) {
        return;
    }
    switch (mode) {
    case 0: {
        StartSoundEffect(0x8C, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        for (s32 i = 0; i < 57; i++) {
            T217D_3F0_Pt* e = &self->pts[i];
            e->level = 1.0f;
            e->target = RandomFloatInRange(0.0f, 0.05f);
            e->rateA = 1.0f;
            e->rateB = 0.6f;
            e->rateC = 0.2f;
        }
        break;
    }
    case 2:
        StartSoundEffect(0x8D, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        break;
    case 1:
        self->size = 1.0f;
        break;
    case 3:
        self->size = 0.0f;
        ApplyArcTarget(self);
        break;
    }
    self->phase = mode;
    self->phaseSince = g_gameClock[4];
}

extern s32 D_00270458;
void func_001AAB20(ScreenElement* self, f32 x, f32 y);

void func_001E76E0(T217D_3F0* self, s32 value)
{
    s32 old = self->mode;
    SetScreenElementMode(self, value);
    if (old == value) return;
    if (old != 0) goto done;
    if (D_00270458 == 4) {
        self->place->dy = 0.0f;
        SetScreenElementSize(self, 640.0f, 360.0f);
    } else {
        self->place->dy = -20.0f;
        SetScreenElementSize(self, 160.0f, 125.4f);
    }
done:
    if (value != 2) return;
    if (D_00270458 == 4) return;
    self->phase = -1;
    SetArcPhase(self, 3);
}

extern f32 D_00261858[];
extern s32 D_00270448;
extern s32 D_00270458;

void func_001AA298(ScreenElement* self);
f32 func_001EA4B8(f32* p, s32 zero, f32 a, f32 b, f32 c);
s32 func_001EAC68(f32 a, f32 b, f32 c);
f32 func_001EAAE0(f32 a, f32 b);

void func_001E77C0(T217D_3F0* self)
{
    UpdateScreenElementSlide(self);
    s32 state = self->mode;
    s32 sub = self->phase;
    switch (state)
    {
    case 0:
        if (self->current != 0)
        {
            state = 2;
        }
        else if (self->target != 0)
        {
            state = D_00270448 != 0;
        }
        break;
    case 3:
        sub = 3;
        break;
    case 2:
        switch (sub)
        {
        case 0:
        {
            f32 f = self->size + g_gameClock[5] * 5.0f;
            self->size = f;
            if (1.0f <= f)
            {
                self->size = 1.0f;
                sub = 1;
            }
            break;
        }
        case 2:
        {
            f32 f = self->size - g_gameClock[5] * 5.0f;
            self->size = f;
            if (f <= 0.0f)
            {
                self->size = 0.0f;
                sub = 3;
            }
            break;
        }
        case 3:
            if (self->target != 0)
            {
                sub = 0;
            }
            else
            {
                state = 3;
            }
            break;
        }
        if (D_00270458 != 4)
        {
            self->pulse = ApproachValueWithRamp(&self->pulseA, 0, self->pulse, self->pulseTarget, g_gameClock[5]);
            if (func_001EAC68(self->pulse, self->pulseTarget, 1e-4f) != 0)
            {
                self->pulse = 1.0f;
                if (self->index == 0x1A)
                {
                    self->pulseA = RandomFloatInRange(1.0f, 1.4f);
                    self->pulseB = RandomFloatInRange(0.6f, 0.8f);
                    self->pulseC = RandomFloatInRange(0.1f, 0.2f);
                }
                else
                {
                    self->pulseA = RandomFloatInRange(0.5f, 0.7f);
                    self->pulseB = RandomFloatInRange(0.2f, 0.3f);
                    self->pulseC = RandomFloatInRange(0.3f, 0.5f);
                }
            }
            s32 idx = (s32)(self->pulse * 56.999f);
            f32 d = RandomFloatInRange(0.1f, 0.2f);
            if (self->index == 0x1A)
            {
                d = d + d;
            }
            f32 lo = 0.0f;
            f32 hi = 1.0f;
            f32 v = self->pts[idx].level + d;
            if (v < lo)
            {
                v = lo;
            }
            else if (hi < v)
            {
                v = hi;
            }
            self->pts[idx].level = v;
            s32 big = 0x1A;
            f32* q;
            T217D_3F0_Pt* e;
            s32 i;
            for (q = &self->pts[0].rateA, e = self->pts, i = 0; i < 57; q += 11, i++, e++)
            {
                if (func_001EAC68(e->level, e->target, 1e-4f) != 0)
                {
                    if (self->index == big)
                    {
                        e->rateA = RandomFloatInRange(0.6f, 0.8f);
                        e->rateB = RandomFloatInRange(0.4f, 0.6f);
                        e->rateC = RandomFloatInRange(0.05f, 0.2f);
                    }
                    else
                    {
                        e->rateA = RandomFloatInRange(0.3f, 0.4f);
                        e->rateB = RandomFloatInRange(0.2f, 0.3f);
                        e->rateC = RandomFloatInRange(0.1f, 0.4f);
                    }
                    e->target = RandomFloatInRange(0.0f, 0.05f);
                }
                else
                {
                    e->level = ApproachValueWithRamp(q, 0, e->level, e->target, g_gameClock[5]);
                }
            }
        }
        break;
    }
    self->vt->m16(self, state);
    SetArcPhase(self, sub);
}

ASM_FUNC(func_001E7C60);

ASM_FUNC(func_001E80D8);

ASM_FUNC(func_001E83E0);

void func_001E87F0(T217D_3F0* self, void* a1);

void func_001E86E0(T217D_3F0* self, void* value)
{
    if (value == self->target) return;
    if (self->target == 0) {
        g_typedTextCaptionBox.vt->m08(&g_typedTextCaptionBox, 0);
    }
    self->target = value;
    if (g_typedTextCaptionBox.state == 4) {
        ApplyArcTarget(self);
        if (self->target != 0) {
            self->vt->m16(self, 2);
            SetArcPhase(self, 1);
            SetArcFade(self, 0);
        } else {
            self->vt->m16(self, 0);
            SetArcPhase(self, 3);
            SetArcFade(self, 0);
            SetArcSpecialObject(self, 0);
        }
    } else {
        s32 st = self->phase;
        if (st >= 2) return;
        if (st < 0) return;
        SetArcPhase(self, 2);
    }
}

void func_001E87F0(T217D_3F0* self, void* a1)
{
    PlacedObject* old = (PlacedObject*)self->special;
    if (old != 0) {
        old->flags &= ~(1ULL << 32);
    }
    self->special = a1;
    if (a1 != 0) {
        ((PlacedObject*)a1)->flags |= (1ULL << 32);
    }
}

void func_001E8840(T217D_3F0* self)
{
    ResetScreenElement(self);
    self->size = 0;
    self->current = 0;
    self->target = 0;
    self->phase = 3;
}

extern u8 D_00275B50[8];
void func_001E8878(s32 enabled, u32 value) { if (value == 0xFFFF && enabled) { D_00275B50[0] = 0x80; D_00275B50[1] = 0x80; D_00275B50[2] = 0x80; D_00275B50[3] = 0x80; } }

void func_001E8878(s32 a0, s32 a1);

void func_001E88B0(void)
{
    func_001E8878(1, 0xFFFF);
}

s32 D_00275B28[10] = { 0x00000000, 0x00000356, 0x00000618, 0x00000000, 0x00000357, 0x00000610, 0x00000002, 0x0000035C, 0x0000061C, 0x00000000 };
u8 D_00275B50[8] = { 0 };
f32 D_00275B58[2] = { 500.0f, 2500.0f };
