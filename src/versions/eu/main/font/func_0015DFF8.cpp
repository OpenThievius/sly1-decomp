// SPDX-License-Identifier: AGPL-3.0-or-later
// Sums a float over a list: each step calls the node's info function at its offset.
struct Info_eu_15E438 {
    u8 pad[0x18];
    s16 off;
    u8 pad1A[2];
    f32 (*fn)(void* self, s32 arg);
};
struct Node_eu_15E438 {
    u8 pad[0x4C];
    Info_eu_15E438* info;
};
struct Holder_eu_15E438 {
    u8 pad[0xC];
    Node_eu_15E438* node;
};

void RewindTextReader(TextReader* self);
s32 ReadTextCharAnyWidth(void* self);

f32 SumTextWidth(Holder_eu_15E438* self)
{
    f32 total = 0.0f;
    RewindTextReader((TextReader*)self);
    s32 r;
    while ((r = ReadTextCharAnyWidth(self)) != 0) {
        Node_eu_15E438* n = self->node;
        total += n->info->fn((u8*)n + n->info->off, r);
    }
    return total;
}
