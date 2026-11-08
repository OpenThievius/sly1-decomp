// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 0/0, checked 2026-11-08
// NEAR: the C is 1308 bytes against retail's 1268, one callee-saved register more (frame 0x100,
// retail 0xE0). Retail's strip search is not rotated (`b` into its test, everything reloaded each
// time: loop.c leaves it alone); ours is rotated with a pre-test and keeps mesh->strips. Retail
// also computes &D_0027DC20[first] inside the j loop where ours hoists `first << 4` to a stack
// slot. Tried: the search as a while(1) with breaks, and as an inline function returning the strip.
#include "common.h"
#include "strip_mesh.h"

struct AttachmentCopy { s32 n0; void* p4; u8 pad8[4]; s32 count; void* recs; void* p14; u8 pad18[0x28]; s32 n40; void* p44; u8 pad48[4]; void* head; s32 f50; };
struct PartPacketContext;
struct PartPacketSource;
struct PartPackets;
void BuildPartVifPackets(PartPacketContext* a, PartPacketSource* b, PartPackets* c);
void* CopyToFrontMemory(s32 size, void* src);
void QueueNodeLink(s32 a, s32 b, AnimCursor* node);
void QueueMeshStrip(StripMesh* mesh, FrameSource* strip, s32 a, s32 b, s32 n, AnimCursor* node);
extern s32 g_meshQueueCount;
// What CopyAttachmentPart copies: a part's 0x50-byte entries (the mesh, a record of pointers
// into its three buffers, the buffers' sizes and the buffers) and the 0x28-byte record built
// for the part.
struct PartPointers {
    void* f00;              // 0x00
    void* a[4];             // 0x04
    void* b[4];             // 0x14
    void* c[4];             // 0x24
};
struct PartEntry {
    u8 pad00[0x18];
    StripMesh* mesh;        // 0x18
    u8 pad1C[0x20 - 0x1C];
    PartPointers* pointers; // 0x20
    u8 pad24[0x38 - 0x24];
    s32 sizes[3];           // 0x38: quadwords
    void* buffers[3];       // 0x44
    u8 pad50[0x50 - 0x50];
};
struct CopiedPart {
    u8 pad00[0x38];
    CursorAnimator* animator;   // 0x38
    u8 pad3C[0x54 - 0x3C];
    void* f54;              // 0x54
    s32 count;              // 0x58
    PartEntry* entries;     // 0x5C
};
struct PartRecord {
    u8 pad00[0x04];
    u8* packets;            // 0x04: 0x30 bytes an entry
};
extern FrameTarget D_0027DC20[];
extern s32 g_meshQueueCount;
s32 GetAnimatorSize(s32 type);
void RemapMeshQueueValues(s32 idx, u32 lo, u32 take, u32 give);

// Moves a pointer that points into the block at `from` (`size` bytes) to the same place in the
// block at `to`.
static inline void MovePointerInto(void** p, u8* from, s32 size, u8* to)
{
    if (p != 0 && !((u8*)*p < from) && (u8*)*p < from + size) {
        *p = (u8*)*p + (to - from);
    }
}

void CopyAttachmentPart(AttachmentCopy* owner, void* partp, void* recp)
{
    CopiedPart* part = (CopiedPart*)partp;
    PartRecord* rec = (PartRecord*)recp;
    rec->packets = (u8*)CopyToFrontMemory(part->count * 0x30, rec->packets);
    s32 animated;
    if (part->animator != 0) {
        owner->f50++;
        animated = part->animator != 0 && (part->animator->cursor.flags & 4) != 0;
    } else {
        animated = 0;
    }
    s32 linked = part->f54 != 0;
    s32 first;
    if (animated || linked) {
        first = g_meshQueueCount;
        part->entries = (PartEntry*)CopyToFrontMemory(part->count * 0x50, part->entries);
        if (part->animator != 0) {
            part->animator = (CursorAnimator*)CopyToFrontMemory(GetAnimatorSize(part->animator->type), part->animator);
            AnimCursor* cursor = &part->animator->cursor;
            FrameLink* link = cursor->links;
            cursor->links = 0;
            while (link != 0) {
                FrameTarget* t = link->dst;
                if (link->src != 0) {
                    QueueMeshStrip((StripMesh*)cursor->record, link->src, t->dstAddr, t->count, t->flag, cursor);
                } else {
                    QueueNodeLink(t->dstAddr, t->count, cursor);
                }
                link = link->next;
            }
        }
    }
    for (s32 i = 0; i < part->count; i++) {
        PartEntry* e = &part->entries[i];
        u8* packets = rec->packets + i * 0x30;
        if (animated || linked) {
            for (s32 j = 0; j < 3; j++) {
                u8* old = (u8*)e->buffers[j];
                if (old != 0) {
                    s32 size = e->sizes[j] << 4;
                    u8* end = old + size;
                    e->buffers[j] = CopyToFrontMemory(size, old);
                    for (s32 k = 0; k < first; k++) {
                        FrameTarget* t = &D_0027DC20[k];
                        if (!((u8*)t->dstAddr < old) && (u8*)t->dstAddr < end) {
                            s32 again = 0;
                            for (s32 m = first; m < g_meshQueueCount; m++) {
                                if (D_0027DC20[m].dstAddr == t->dstAddr) {
                                    again = 1;
                                    break;
                                }
                            }
                            if (again == 0) {
                                StripMesh* mesh = e->mesh;
                                FrameSource* strip = 0;
                                for (s32 n = 0; n < mesh->nstrips; n++) {
                                    FrameSource* s = &mesh->strips[n];
                                    if (!((u32)t->value < (u32)s->base) &&
                                        (u32)t->value < (u32)s->base + ((*(s32*)((u8*)mesh + 0x20) * s->stride) << 4)) {
                                        strip = s;
                                        break;
                                    }
                                }
                                QueueMeshStrip(mesh, strip, t->dstAddr, t->count, t->flag, 0);
                            }
                        }
                    }
                    RemapMeshQueueValues(first, size, (u32)old, (u32)e->buffers[j]);
                    if (linked) {
                        e->pointers = (PartPointers*)CopyToFrontMemory(0x34, e->pointers);
                        MovePointerInto(&e->pointers->f00, old, e->sizes[j] << 4, (u8*)e->buffers[j]);
                        for (s32 k = 0; k < 4; k++) {
                            MovePointerInto(&e->pointers->a[k], old, e->sizes[j] << 4, (u8*)e->buffers[j]);
                            MovePointerInto(&e->pointers->b[k], old, e->sizes[j] << 4, (u8*)e->buffers[j]);
                            MovePointerInto(&e->pointers->c[k], old, e->sizes[j] << 4, (u8*)e->buffers[j]);
                        }
                    }
                }
            }
        }
        BuildPartVifPackets((PartPacketContext*)part, (PartPacketSource*)e, (PartPackets*)packets);
    }
}
