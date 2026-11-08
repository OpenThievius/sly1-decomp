// SPDX-License-Identifier: AGPL-3.0-or-later
// Only in PAL: copies a block into the IOP's ring (waiting for the transfer), then for kind 0x10 tells the IOP the block's slot.
struct Obj_eu_18F118 {
    u8 pad0[4];
    s32 kind;
    u8 pad8[4];
    s32 cols;
    u8 pad10[4];
    s32 f14;
    u8 pad18[4];
    s32 f1C;
    u8 pad20[0xC];
    s32 f2C;
};

struct IopDmaTransfer_eu {
    s32 src;
    s32 dest;
    void* size;
    s32 attr;
};

void SyncDataCache(s32 a);
void* StartIopDma(IopDmaTransfer_eu* span, s32 n);
s32 GetIopDmaStatus(void* obj);
void func_eu_0011E5F8(s32 a, s32 b);

s32 func_eu_0018F118(Obj_eu_18F118* self, s32 size, u8* buf)
{
    IopDmaTransfer_eu span;
    void* obj;
    s32 pos = 0;

    if (self->kind != 0x10) {
        pos = self->f1C;
    }
    span.src = (s32)buf;
    span.dest = self->f14 + pos;
    span.size = (void*)size;
    span.attr = 0;
    SyncDataCache(0);
    obj = StartIopDma(&span, 1);
    while (GetIopDmaStatus(obj) >= 0) {
    }
    if (self->kind == 0x10) {
        s32 t = self->f2C / 1024;
        s32 q = t / self->cols;
        s32 r = t % self->cols;
        s32 slot = q % 4;
        func_eu_0011E5F8(size, (slot << 10) + (r << 12));
    }
    return size;
}
