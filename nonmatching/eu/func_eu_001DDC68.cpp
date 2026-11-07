// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 948/944, checked 2026-11-07
// NEAR (only in PAL): python3 tools/check.py nonmatching/eu/func_eu_001DDC68.cpp func_eu_001DDC68 --unit src/main/file_1D62E0.cpp
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

void ResetScatterController(void* p);
void InitScriptValuePools(void);
s32 ReadBufferedU8(void* ctx);
s32 ReadBufferedS16(void* ctx);
void SkipBufferedBlocks(void* ctx);
void func_eu_001DDA10(void* ctx);
Node_eu_1DDC68* CreateTypedRecord(s32 kind, void* world, s32 a, s32 b, s32 c);
void LoadScriptEntryTable(void* world, void* ctx);
void ReadPropertyRecords(void* world, void* ctx);
void ReadOptionalBufferedBlock(void* ctx, void* p);
void ReadBufferedString(void* ctx, void* p);
void LoadScreenResources(void* ctx);
void ReadSlotObjects(void* world, s32 a, void* ctx);
void ReadBufferedBlockBody(void* ctx);
void EnsureSoundBankLoaded(s32 a);
void SilenceVolumeChannel2(void);
void RequestStagedBank(s32 a);
void SendResidentImages(void);
s32 IsListEmpty(void* p);
void CreateConeVolumes(void* world);
void FillScreenColor(void* d, void* p, s32 a, s32 w);
void SpawnListedObjectCopies(void* world);
void RunQueuedCalls(void* world);
void UpdateScatterLevelLimits(void* p);
void ResumeElementStackState(void* p);
void* AllocateZeroedFrontMemory(u32 n);
void UpdateCameraLocation(void* p);
void UpdateWorldContacts(void* world, s32 a);
void PlayStagedBank(s32 a);
void StartWorldSoundEntries(void* world);

void func_eu_001DDC68(World_eu_1DDC68* self, void* ctx)
{
    Word_eu_1DDC68 w;
    Iter_eu_1DDC68 iter;
    Iter_eu_1DDC68* itp;
    s32 i;
    s32 j;
    s32 k;
    ResetScatterController(D_eu_002631F0);
    InitScriptValuePools();
    D_eu_0027EE84 = ReadBufferedU8(ctx);
    self->f1D70 = ReadBufferedS16(ctx);
    SkipBufferedBlocks(ctx);
    func_eu_001DDA10(ctx);
    D_eu_00262C90 = CreateTypedRecord(0x6D, self, 0, 4, -1);
    itp = &iter;
    for (i = 9; i >= 0; i--) {
        Node_eu_1DDC68* n = CreateTypedRecord(0x1E, self, 0, 0xA, -1);
        n->vt->f1C(n);
    }
    for (j = 0x27; j >= 0; j--) {
        Node_eu_1DDC68* n = CreateTypedRecord(0x4D, self, 0, 0xB, -1);
        n->vt->f1C(n);
    }
    LoadScriptEntryTable(self, ctx);
    ReadPropertyRecords(self, ctx);
    ReadOptionalBufferedBlock(ctx, &self->f2310);
    ReadBufferedString(ctx, &self->f2314);
    ReadOptionalBufferedBlock(ctx, &self->f1D74);
    for (k = 0xD; k >= 0; k--) {
        ReadOptionalBufferedBlock(ctx, &D_eu_0027EEA0[13 - k]);
    }
    LoadScreenResources(ctx);
    ReadSlotObjects(self, 0, ctx);
    ReadBufferedBlockBody(ctx);
    if (self->f1D70 >= 0) {
        EnsureSoundBankLoaded(self->f1D70);
    }
    if (self->f1D78 == 0) {
        SilenceVolumeChannel2();
    }
    RequestStagedBank(self->f1D74);
    SendResidentImages();
    if (IsListEmpty(self->f1BE8) != 0) {
        CreateConeVolumes(self);
    }
    ((u8*)self)[0x1D67] = 0x80;
    w = self->f1D64;
    FillScreenColor(D_eu_002C73A0, &w, 0, w.v);
    self->f1D68 = self->f1D68 * 0.003921569f;
    self->f1D6C = self->f1D6C * 0.003921569f;
    SpawnListedObjectCopies(self);
    RunQueuedCalls(self);
    for (Node_eu_1DDC68* n = (Node_eu_1DDC68*)self->list.head; n != 0; n = n->next) {
        if (n->vt->f4C != 0) {
            n->vt->f4C(n);
        }
    }
    RunQueuedCalls(self);
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
    RunQueuedCalls(self);
    UpdateScatterLevelLimits(D_eu_002631F0);
    ResumeElementStackState(D_eu_0027F330);
    if (D_eu_00274868.f570 == 0) {
        if (D_eu_002636F0->mode != 0) {
            AllocateZeroedFrontMemory(0x80000);
        }
    }
    UpdateCameraLocation(D_eu_00262C90);
    UpdateWorldContacts(self, 0);
    PlayStagedBank(self->f1D74);
    StartWorldSoundEntries(self);
}
