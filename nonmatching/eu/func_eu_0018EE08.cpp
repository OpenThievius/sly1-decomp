// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR (only in PAL): python3 tools/check.py nonmatching/eu/func_eu_0018EE08.cpp func_eu_0018EE08 --unit src/main/0018C000.cpp
// Still differs: Strided chunk copy for kind 0x10; only saved-register numbering differs (self s3 vs s4, chunk s1 vs s2, etc.), ~34 lines.
// Copies a block of len bytes through a chunk buffer of cols << 10 bytes, in strided rows, when the object's kind is 0x10 and it has more than one column.
struct Obj_eu_18EE08 {
    u8 pad0[4];
    s32 kind;
    u8 pad8[4];
    s32 cols;
    s32 stride;
};

void func_0018D608(void* self, s32 len, u8* dst);
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
    func_0018D608(self, len, dst);
    u8* p = dst;
    s32 chunk = self->cols << 10;
    u8* buf = func_0018D658(chunk);
    s32 rem = len;
    while (rem != 0) {
        s32 off = 0;
        s32 row = 0;
        s32 col = 0;
        u8* end = p + chunk;
        if (chunk > 0) {
            do {
                func_0018D800(buf + (col << 10) + row * self->stride, p + off, (u32)self->stride);
                col++;
                if (col >= self->cols) {
                    row++;
                    col = 0;
                }
                off += self->stride;
            } while (off < chunk);
        }
        func_0018D800(p, buf, (u32)chunk);
        p = end;
        rem -= chunk;
    }
    func_0018D6F0();
}
