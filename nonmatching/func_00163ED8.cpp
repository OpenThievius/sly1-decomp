// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 2336/2448 (95.4%), checked 2026-11-02
#include "common.h"
// NEAR (r60d): 47 aligned lines differ (51 marked by check.py; was 93). Two source changes
// on top of m59f: (1) one function-level `Rec_163ED8* r` assigned `r = &recs[i]` in every loop
// (loop 1 before `if (hasUv)`, the weights, morph and tint loops); retail keeps r in a3 in all
// four. Because r is now used after loop 1 ends, loop.c records it as a non-replaceable giv: its
// insn becomes the copy `r = reduced giv` and the uv loads go through r, which is retail's
// `move a3,a1`. (2) the morph inner loop is a plain `for (i = 0; i < n; i++) { r = &recs[i]; ...}`
// (the m59f `c = r++` do-while is no longer needed: the copy `a3 = a6` and `a6 = a3 + 4` of
// retail come out by themselves). Loop 1 and the morph loop now match exactly.
// Still differs, register choice only: in the weights loop i+1 lands in t2 (retail t1) and recs
// in t3 (retail t2); in the morph section `off` is reloaded from 64(sp) where retail keeps it in
// t3; in the tint loop the inner j's get a1/t0 where retail gives both a2 (i's register: i is
// dead there since i+1 is precomputed into t1) and the color pointer a2/t3 (retail a1/t2), which
// shifts 127/510 by one register. Tried: function-level j shared by all inner loops (83), by the
// tint loops only (78), by the weights loop only (47, same), loop 1 on the shared i (98).
struct Pkt_163ED8;
struct Vec3_163ED8 {
    f32 x;
    f32 y;
    f32 z;
};
struct Uv_163ED8 {
    f32 u;
    f32 v;
};
struct Rec_163ED8 {
    u8 pos;
    u8 pad1;
    u8 uv;
    u8 flags;
};
struct Ent_163ED8 {
    u16* idx;
    s32 pad;
};
struct Self_163ED8 {
    u8 pad00[0x40];
    s32 f40;
};
struct Info_163ED8 {
    u8 pad00[0x10];
    s32 f10;
    s32 f14;
    s32 f18;
};
struct Node_163ED8;
struct Hook_163ED8;
typedef Node_163ED8* (*HookFn_163ED8)(Hook_163ED8* self, struct Mesh_163ED8* mesh);
struct Hook_163ED8 {
    HookFn_163ED8* vt;
};
struct Node_163ED8 {
    s32 flags;
};
struct Obj_163ED8 {
    u8 pad00[0x38];
    Hook_163ED8* f38;
    u8 pad3C[0x40 - 0x3C];
    f32 f40;
    u8 pad44[0x54 - 0x44];
    Info_163ED8* f54;
};
struct Strip_163ED8 {
    s32 count;
    s32 pad;
};
struct Mesh_163ED8 {
    u8 kind;
    u8 mode;
    u8 pad2[2];
    u8 color[4];
    u8 pad8[0x18 - 0x8];
    s32 nstrips;
    Strip_163ED8* strips;
    u8 pad20[0x24 - 0x20];
    Hook_163ED8* f24;
};
struct Extra_163ED8 {
    s32 f0;
    s32 a4[4];
    s32 a14[4];
    s32 a24[4];
};
struct Hdr_163ED8 {
    u8 pad00[0x1C];
    u16* p;
    Extra_163ED8* extra;
    s32 count;
};

extern s32 D_00262418[];
extern s32 D_00262430[];
extern u8 D_000002F8[];
extern u8 D_00001A50[];
extern u8 D_000036D0[];
extern u8 D_00001A80[];
extern u8 D_000027C0[];
extern u8 D_00002008[];
extern u8 D_000023B8[];
extern u8 D_00003A80[];
extern u8 D_00003A90[];

void func_00152B38(Pkt_163ED8* pkt);
void func_00152D70(Pkt_163ED8* pkt);
void func_00152CA0(Pkt_163ED8* pkt);
void func_001EE5C8(Pkt_163ED8* s, s32 tag, s32 size, s32 a3, void* a4, void* a5);
void* func_001F5C0C(void* p, s32 value, s32 size);
void func_001EE498(Pkt_163ED8* s, s32 a, s32 b);
void func_001EE4C0(Pkt_163ED8* s, u32* src);
void func_001EE528(Pkt_163ED8* s, s32 value);
void func_001EE3F0(Pkt_163ED8* s, void* data);
void func_001EE420(Pkt_163ED8* s, void* data);
void func_001EE480(Pkt_163ED8* s);
void func_001EE668(Pkt_163ED8* s, s32 a, s32 b, void* data, s32 flags);
void func_001EE718(Pkt_163ED8* s, s32 a, s32 b, s32 c, s32 d, s32* out);
void* func_0018D5C0(s32 bytes);
void func_00163938(s32 mode, Pkt_163ED8* pkt);
void func_00169608(s32 a, s32 b, Node_163ED8* node);
void func_001694F8(Mesh_163ED8* mesh, Strip_163ED8* strip, s32 a, s32 b, s32 n, Node_163ED8* node);

void func_00163ED8(Self_163ED8* self, Obj_163ED8* obj, s32 mode, Hdr_163ED8* hdr, Mesh_163ED8* mesh,
                   Vec3_163ED8* vecs, s32 unused6, u8* tints, Uv_163ED8* uvs, s32 n, Rec_163ED8* recs,
                   Ent_163ED8* ents, Vec3_163ED8* verts, s32 unused13, f32* weights, Pkt_163ED8* pkt,
                   s32** outs)
{
    u32 buf[4];
    f32* uvOut;
    f32* posOut;
    s32 a;
    s32 b;
    f32* wOut;
    s32 k;
    Vec3_163ED8* dOut;
    u8* cOut;
    s32 c;
    s32 d;
    s32 off;
    s32 hasUv;
    s32 tinted;
    void* tail;
    void* head;
    Node_163ED8* node;
    s32 i;
    Rec_163ED8* r;

    if (obj->f54 != 0) {
        func_00152B38(pkt);
    }
    func_001EE5C8(pkt, 0xD, 3, 0xB, 0, &hdr->p);
    off = 0x24;
    func_001F5C0C(hdr->p, 0, 0x18);
    hdr->p[8] = 3;
    hdr->p[0] = off;
    off = n * 3 + 0x24;
    hdr->p[1] = off;
    switch (mesh->kind) {
    case 1:
    case 5:
    case 6:
    case 7:
    case 8:
    case 10:
        head = D_000002F8;
        tail = D_00001A50;
        tinted = 1;
        hasUv = 1;
        break;
    case 4:
        head = D_000036D0;
        tail = D_00001A80;
        hasUv = mesh->mode & 2;
        tinted = hasUv;
        break;
    case 9:
        head = D_000002F8;
        tail = D_00001A50;
        hasUv = 0;
        tinted = 1;
        break;
    }
    cOut = 0;
    uvOut = 0;
    func_001EE498(pkt, 1, 3);
    if (hasUv) {
        func_001EE5C8(pkt, 8, n, hdr->p[0], 0, &uvOut);
    }
    func_001EE5C8(pkt, 0xC, n, hdr->p[0] + 2, 0, &posOut);
    func_001EE498(pkt, 1, 1);
    if (outs[0] != 0) {
        *outs[0] = n;
    }
    if (outs[1] != 0) {
        *outs[1] = (s32)posOut;
    }
    if (outs[2] != 0) {
        *outs[2] = (s32)uvOut;
    }
    if (obj->f54 != 0) {
        Extra_163ED8* e = (Extra_163ED8*)func_0018D5C0(0x34);
        hdr->extra = e;
        e->f0 = (s32)posOut;
    }
    for (s32 i = 0; i < n; i++) {
        r = &recs[i];
        if (hasUv) {
            if (r->uv == 0xFF) {
                uvOut[0] = uvOut[1] = 0.0f;
            } else {
                uvOut[0] = uvs[r->uv].u;
                uvOut[1] = uvs[r->uv].v;
            }
            uvOut[2] = 1.0f;
            uvOut += 3;
        }
        *(Vec3_163ED8*)posOut = vecs[recs[i].pos];
        if (recs[i].flags >> 7) {
            posOut[3] = obj->f40 + 32768.0f;
        } else {
            posOut[3] = obj->f40 + 28672.0f;
        }
        posOut += 4;
    }
    node = 0;
    if (obj->f38 != 0) {
        node = obj->f38->vt[5](obj->f38, mesh);
    }
    if (node == 0 && mesh->f24 != 0) {
        node = mesh->f24->vt[5](mesh->f24, mesh);
    }
    func_00163938(mode, pkt);
    if (node != 0 && (node->flags & 2)) {
        func_001EE5C8(pkt, 4, 1, 0x16, &a, &b);
        func_00169608(b, a, node);
        func_001EE3F0(pkt, D_000027C0);
    }
    if (hdr->count > 0) {
        hdr->p[2] = off;
        off += hdr->count * 4;
        hdr->p[3] = off;
        off += n;
        func_001F5C0C(buf, 0, 0x10);
        func_001EE4C0(pkt, buf);
        func_001EE528(pkt, D_00262418[hdr->count]);
        func_001EE5C8(pkt, D_00262430[hdr->count], n, hdr->p[3], 0, &wOut);
        func_001EE528(pkt, 0);
        for (i = 0; i < n; i++) {
            r = &recs[i];
            for (s32 j = 0; j < hdr->count; j++) {
                *wOut++ = weights[r->pos * hdr->count + j];
            }
        }
        func_001EE3F0(pkt, D_00002008);
    }
    if (self->f40 != 0) {
        hdr->p[3] = off;
        off += self->f40;
        hdr->p[7] = off;
        for (k = 0; k < self->f40; k++) {
            if (k > 0) {
                func_001EE480(pkt);
            }
            func_001EE668(pkt, 0, 1, &k, 0x16);
            func_001EE5C8(pkt, 8, n, hdr->p[7], 0, &dOut);
            u16* idx = ents[k].idx;
            for (i = 0; i < n; i++) {
                r = &recs[i];
                Vec3_163ED8* v = &verts[idx[i]];
                dOut[i].x = v->x - vecs[r->pos].x;
                dOut[i].y = v->y - vecs[r->pos].y;
                dOut[i].z = v->z - vecs[r->pos].z;
            }
            func_001EE3F0(pkt, D_000023B8);
        }
    }
    if (hdr->extra != 0) {
        Extra_163ED8* e = hdr->extra;
        s32 end = off + n;
        for (s32 i = 0; i < obj->f54->f10; i++) {
            func_001EE5C8(pkt, 0xC, n, off, 0, &e->a24[i]);
            if (obj->f54->f18 != 0) {
                func_001EE718(pkt, 0xC, 4, 0, 0x16, &e->a14[i]);
                func_001EE3F0(pkt, D_00003A80);
                func_001EE480(pkt);
            }
            if (obj->f54->f14 != 0) {
                func_001EE718(pkt, 0xC, 4, 0, 0x16, &e->a4[i]);
                func_001EE3F0(pkt, D_00003A90);
                func_001EE480(pkt);
            }
        }
        hdr->p[3] = off;
        off = end;
    }
    func_001EE3F0(pkt, tail);
    if (tinted) {
        func_001EE498(pkt, 1, 3);
        func_001EE5C8(pkt, 0xE, n, hdr->p[0] + 1, 0, &cOut);
        func_001EE498(pkt, 1, 1);
        for (i = 0; i < n; i++) {
            r = &recs[i];
            if ((r->flags & 0x7F) == 0x7F) {
                for (s32 j = 0; j < 4; j++) {
                    cOut[j] = (mesh->color[j] + 1) >> 1;
                }
            } else {
                for (s32 j = 0; j < 4; j++) {
                    cOut[j] = (mesh->color[j] * tints[(r->flags & 0x7F) * 4 + j] + 0x100) / 0x1FE;
                }
            }
            cOut += 4;
        }
    }
    for (s32 i = 0; i < mesh->nstrips; i++) {
        Strip_163ED8* s = &mesh->strips[i];
        func_001EE5C8(pkt, 0xC, s->count, off, &c, &d);
        func_001694F8(mesh, s, d, c, n, node);
        hdr->p[4 + i] = off;
        off += s->count;
    }
    func_001EE420(pkt, head);
    if (obj->f54 != 0) {
        func_00152D70(pkt);
        func_00152CA0(pkt);
    }
}
