// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 948/944, checked 2026-11-01
// NEAR (only in PAL): python3 tools/check.py nonmatching/eu/func_eu_001DDC68.cpp func_eu_001DDC68 --unit src/main/001DC000.cpp
// Still differs: Level setup; now 948 vs 944 bytes with the list iterator rewritten (cur = next + stride, stride via list pointer); still differs in saved-register roles (self/ctx s1,s2 vs s2,s3) and stack layout (iterator at sp+16 vs retail sp+32).
// Level object setup: spawns the fixed object pools, initialises the managers, runs the update/draw passes over the object list once and ends the frame.
struct Vt_eu_1DDC68 { u8 pad0[0x1C]; void (*f1C)(void* self); u8 pad1[0x4C - 0x20]; void (*f4C)(void* self); void (*f50)(void* self); };
struct Node_eu_1DDC68 { Vt_eu_1DDC68* vt; u8 pad0[0x18]; Node_eu_1DDC68* next; };
struct __attribute__((packed)) Word_eu_1DDC68 { s32 v; };
struct Iter_eu_1DDC68 { u8* list; u8* cur; s32 stride; Iter_eu_1DDC68* prev; };
struct List_eu_1DDC68 { u8* head; s32 f4; s32 stride; };
struct World_eu_1DDC68 {
    u8 pad0[0x48]; List_eu_1DDC68 list;
    u8 pad1[0x1BE8 - 0x54]; u8 f1BE8[0x1D64 - 0x1BE8];
    Word_eu_1DDC68 f1D64; f32 f1D68; f32 f1D6C; s32 f1D70; s32 f1D74; s32 f1D78;
    u8 pad2[0x2310 - 0x1D7C]; s32 f2310; s32 f2314;
};
struct Owner_eu_1DDC68 { u8 pad0[0x570]; s32 f570; };
struct Mode_eu_1DDC68 { u8 pad0[0x19D8]; s32 mode; };
extern u8 D_eu_002631F0[];
extern void* D_eu_00262C90;
extern s32 D_eu_0027EE84;
extern const char* D_eu_0027EEA0[];
extern Iter_eu_1DDC68* D_eu_00284A94;
extern u8 D_eu_002C73A0[];
extern u8 D_eu_0027F330[];
extern Owner_eu_1DDC68 D_eu_00274868;
extern Mode_eu_1DDC68* D_eu_002636F0;

void func_00151A88(void* p);
void func_0011BF70(void);
s32 func_00137B90(void* ctx);
s32 func_00137D10(void* ctx);
void func_001DCCC0(void* ctx);
void func_eu_001DDA10(void* ctx);
Node_eu_1DDC68* func_0011E580(s32 kind, void* world, s32 a, s32 b, s32 c);
void func_001C1190(void* world, void* ctx);
void func_0011EC40(void* world, void* ctx);
void func_00138550(void* ctx, void* p);
void func_001384A0(void* ctx, void* p);
void func_001B3040(void* ctx);
void func_0011ECB8(void* world, s32 a, void* ctx);
void func_001DBA38(void* ctx);
void func_001BE268(s32 a);
void func_001BECF8(void);
void func_001BEB10(s32 a);
void func_001B3450(void);
s32 func_00152720(void* p);
void func_001DC9A0(void* world);
void func_00168770(void* d, void* p, s32 a, s32 w);
void func_001DCD28(void* world);
void func_001DBE48(void* world);
void func_00151D28(void* p);
void func_001E90E8(void* p);
void* func_0018D5C0(u32 n);
void func_00144270(void* p);
void func_00138C00(void* world, s32 a);
void func_001BEC58(s32 a);
void func_001C0B38(void* world);

void func_eu_001DDC68(World_eu_1DDC68* self, void* ctx)
{
    Word_eu_1DDC68 w;
    Iter_eu_1DDC68 iter;
    Iter_eu_1DDC68* itp;
    s32 i;
    s32 j;
    s32 k;
    func_00151A88(D_eu_002631F0);
    func_0011BF70();
    D_eu_0027EE84 = func_00137B90(ctx);
    self->f1D70 = func_00137D10(ctx);
    func_001DCCC0(ctx);
    func_eu_001DDA10(ctx);
    D_eu_00262C90 = func_0011E580(0x6D, self, 0, 4, -1);
    itp = &iter;
    for (i = 9; i >= 0; i--) {
        Node_eu_1DDC68* n = func_0011E580(0x1E, self, 0, 0xA, -1);
        n->vt->f1C(n);
    }
    for (j = 0x27; j >= 0; j--) {
        Node_eu_1DDC68* n = func_0011E580(0x4D, self, 0, 0xB, -1);
        n->vt->f1C(n);
    }
    func_001C1190(self, ctx);
    func_0011EC40(self, ctx);
    func_00138550(ctx, &self->f2310);
    func_001384A0(ctx, &self->f2314);
    func_00138550(ctx, &self->f1D74);
    for (k = 0xD; k >= 0; k--) {
        func_00138550(ctx, &D_eu_0027EEA0[13 - k]);
    }
    func_001B3040(ctx);
    func_0011ECB8(self, 0, ctx);
    func_001DBA38(ctx);
    if (self->f1D70 >= 0) {
        func_001BE268(self->f1D70);
    }
    if (self->f1D78 == 0) {
        func_001BECF8();
    }
    func_001BEB10(self->f1D74);
    func_001B3450();
    if (func_00152720(self->f1BE8) != 0) {
        func_001DC9A0(self);
    }
    ((u8*)self)[0x1D67] = 0x80;
    w = self->f1D64;
    func_00168770(D_eu_002C73A0, &w, 0, w.v);
    self->f1D68 = self->f1D68 * 0.003921569f;
    self->f1D6C = self->f1D6C * 0.003921569f;
    func_001DCD28(self);
    func_001DBE48(self);
    for (Node_eu_1DDC68* n = (Node_eu_1DDC68*)self->list.head; n != 0; n = n->next) {
        if (n->vt->f4C != 0) {
            n->vt->f4C(n);
        }
    }
    func_001DBE48(self);
    iter.prev = D_eu_00284A94;
    D_eu_00284A94 = itp;
    List_eu_1DDC68* lp = &self->list;
    iter.list = (u8*)lp;
    iter.stride = lp->stride;
    iter.cur = self->list.head + iter.stride;
    for (Node_eu_1DDC68* n = (Node_eu_1DDC68*)self->list.head; n != 0; n = *(Node_eu_1DDC68**)iter.cur, iter.cur = (u8*)n + iter.stride) {
        n->vt->f50(n);
    }
    D_eu_00284A94 = iter.prev;
    func_001DBE48(self);
    func_00151D28(D_eu_002631F0);
    func_001E90E8(D_eu_0027F330);
    if (D_eu_00274868.f570 == 0) {
        if (D_eu_002636F0->mode != 0) {
            func_0018D5C0(0x80000);
        }
    }
    func_00144270(D_eu_00262C90);
    func_00138C00(self, 0);
    func_001BEC58(self->f1D74);
    func_001C0B38(self);
}
