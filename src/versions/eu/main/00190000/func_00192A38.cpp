// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the packed field sits at 0x5B0 (not 0x324).
struct __attribute__((packed)) BlockAt5B0_eu { u8 pad[0x5B0]; u32 field; };

void func_00192A38(SwitchedCollider* self, u32 value)
{
    BlockAt5B0_eu* block = (BlockAt5B0_eu*)&g_typedTextCaptionBox;
    block->field = value;
    PushStackElement(g_elementStack, &g_typedTextCaptionBox);
}
