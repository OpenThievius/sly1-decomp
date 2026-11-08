// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 609/696 (87.5%), checked 2026-11-07
// Tried night-close8: the link initialised before a plain walk loop (no change), after it (far worse).
// NEAR: registers: the contact list and axis pointers are s5, s6 and s7 in retail, s7, s5 and s6 here; the search of the contact row and the stores match.
#include "common.h"
#include "asm_func.h"
#include "vu0.h"
#include "globals.h"
#include "switched_collider.h"
float D_00274D40 = -0.25f;
float D_00274D44 = -2.5f;
float D_00274D48 = -1.0f;
float D_00274D4C = 0.25f;
float D_00274D50[4] = {5.0f, 0.0f, 0.0f, 0.0f};
float D_00274D60[4] = {0.5f, -0.00999999978f, 0.0f, 0.0f};
float D_00274D70[4] = {1000.0f, 0.0f, 0.25f, 5000.0f};
float D_00274D80 = 75.0f;
float D_00274D84 = 230.0f;
float D_00274D88[3] = {15.0f, 0.0f, 0.100000001f};
float D_00274D94 = 1.39999998f;
float D_00274D98 = 1.39999998f;
float D_00274D9C = 0.25f;
float D_00274DA0 = 0.100000001f;
float D_00274DA4 = 0.400000006f;
float D_00274DA8 = 80.0f;
float D_00274DAC = 120.0f;
float D_00274DB0[4] = {1.0f, 0.0f, 0.100000001f, 0.0f};
float D_00274DC0[3] = {4.0f, 0.0f, 0.100000001f};
float D_00274DCC = 1.70000005f;
float D_00274DD0 = 3.0f;
float D_00274DD4 = 3.5f;
float D_00274DD8[2] = {-1.70000005f, 0.0f};
float D_00274DE0[3] = {3000.0f, 1000.0f, 0.150000006f};
float D_00274DF0[3] = {30.0f, 10.0f, 0.150000006f};
void BuildCombinedBlendAnimation(void* self, s32 a1, s32 a2, void* a3, s32 a4, s32 a5, s32 a6, void** a7);
void SetBlendItemWeights(void* obj, s32 a1, s32 a2, void* a3);
struct ThreeBlendRecord { s32 f0; u8 pad0[0xC - 0x4]; s32 fC; u8 pad1[0x18 - 0x10]; f32 f18; };
static inline void MulRotation(Mat02* out, const Mat02& a, const Mat02& b)
{
    Mat02 r;
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Vu0::Q(x) = Vu0::RotateUntied(a, Vu0::Q(b.r[0]));
    r.r[0] = x;
    Vu0::Q(y) = Vu0::RotateUntied(a, Vu0::Q(b.r[1]));
    r.r[1] = y;
    Vu0::Q(z) = Vu0::RotateUntied(a, Vu0::Q(b.r[2]));
    r.r[2] = z;
    *out = r;
}
extern f32 g_frameDt[];
void AddColliderForce(void* target, void* slot);
s32 GetObjectWorldPosition(void* self, Vec02* out);
void BuildShortestArcRotation(const Vec02* from, Vec02* to, Mat02* out);
void BuildAxisAngleMatrix(const Vec02* axis, f32 angle, Mat02* out);
void TurnColliderTowardRotation(void* self, Mat02* rot, void* data, f32 scale);
struct LinkTargetHolder { s32 pad0; void* target; };
void AddColliderForce(void* target, void* slot);
void AddColliderTorque(void* target, void* slot);
void TransformPointBetweenFrames(void* a, void* b, void* c, Vec02* d);
struct LinkedFrame { u8 pad00[0x18]; void* frame; u8 pad1C[0x34 - 0x1C]; BaseObject* item; };
typedef void (*LinkItemFn)(BaseObject* self, Vec02* a, f32 t, s32 b, Vec02* c, s32 d, s32 e, void* f);
s32 IsObjectAttached(BaseObject* obj);
void SetContactPairFlags(World* world, Contacts03* a, Contacts03* b, s32 set, s32 clr);

s32 IsObjectAttached(BaseObject* obj);
void SetPlayerState(Player* self, s32 a, s32 b);
void BuildBasisFromXAndZHint(Vec02* x, const Vec02* z, Mat02* out);
s32 CreatePooledContact(f32 f, void* self, void* other, void* a2, void* a3, s32 a4, s32 a5, s32 a6, void* a7);

// Adds the contacts of the player with the object node for the axes of flags (bits 1 2 4: always,
// bits 8 0x10 0x20: when the offset along that axis is under 0.0001), in the frame of axis.
void AddPlayerObjectContacts(Player* self, s32 flags, BaseObject* node, Vec02* origin, Vec02* axis, Vec02* offset)
{
    Vec02 d;
    Mat02 m;
    if (IsObjectAttached(node) == 0) {
        SetPlayerState(self, 2, 2);
        return;
    }
    s32 each = flags & 2;
    s32 first = flags & 1;
    s32 third = flags & 4;
    BaseObject* n = node;
    Contact03** last;
    while ((last = &self->contacts4B4, n != 0) && (n->desc->flags & 2) == 0) {
        n = n->parent;
    }
    Contact03** head;
    if (n != 0) {
        ContactRow03* row = self->contacts->head;
        void* want = ((PlacedObject*)n)->root;
        while (row != 0 && (void*)row->other != want) {
            row = row->next;
        }
        head = (Contact03**)row;
        last = row->link;
    } else {
        head = last;
    }
    if (axis != 0) {
        BuildBasisFromXAndZHint(axis, &g_unitZVector, &m);
    } else {
        m = g_identityMatrix;
    }
    Vu0::Q(d) = Vu0::Sub(Vu0::Add(Vu0::Q(*offset), Vu0::Q(*(Vec02*)((u8*)self + 0x2400))), Vu0::Q(*origin));
    Vu0::Q(d) = Vu0::RotateTransposed(m, Vu0::Q(d));
    if (first != 0 || ((flags & 8) != 0 && d.x < 0.0001f)) {
        CreatePooledContact(d.x, self, n, offset, &m.r[0], first != 0 ? 11 : 10, 0, 0, head);
    }
    if (each != 0 || ((flags & 0x10) != 0 && d.y < 0.0001f)) {
        CreatePooledContact(d.y, self, n, offset, &m.r[1], each != 0 ? 11 : 10, 0, 0, head);
    }
    if (third != 0 || ((flags & 0x20) != 0 && d.z < 0.0001f)) {
        CreatePooledContact(d.z, self, n, offset, &m.r[2], third != 0 ? 11 : 10, third != 0 ? 0 : *(s32*)((u8*)self + 0x6D4), 0, head);
    }
    *last = *head;
}
