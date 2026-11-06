// SPDX-License-Identifier: AGPL-3.0-or-later
// Copies len bytes of dst through a scratch buffer, rearranging each cols << 10 byte chunk from interleaved to strided rows, for kind 0x10 with more than one column.
struct Obj_eu_18EE08 {
    u8 pad0[4];
    s32 kind;
    u8 pad8[4];
    s32 cols;
    s32 stride;
};

void func_0018D608(void);
u8* func_0018D658(s32 n);
void func_0018D800(u8* dst, u8* src, u32 bytes);
void func_0018D6F0(void);

void func_eu_0018EE08(Obj_eu_18EE08* self, s32 len, u8* dst)
{
    if (self->kind != 0x10) {
        return;
    }
    if (self->cols == 1) {
        return;
    }
    PushBackMemoryMark();
    s32 chunk = self->cols << 10;
    u8* p = dst;
    u8* buf = AllocateBackMemory(chunk);
    s32 rem = len;
    while (rem != 0) {
        s32 col = 0;
        s32 row = 0;
        s32 off = 0;
        for (; off < chunk; off += self->stride) {
            CopyMemory(buf + ((col << 10) + row * self->stride), p + off, (u32)self->stride);
            col++;
            if (col >= self->cols) {
                row++;
                col = 0;
            }
        }
        CopyMemory(p, buf, (u32)chunk);
        p += chunk;
        rem -= chunk;
    }
    PopBackMemoryMark();
}
