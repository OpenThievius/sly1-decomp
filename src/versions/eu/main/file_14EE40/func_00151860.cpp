// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: D_002701F8.value is at 0x5B0 (US 0x324).
struct Global_2701F8_eu { u8 pad[0x5B0]; void* value; };

void func_00151860(void* value, Ent65* object)
{
    if (object != 0) {
        object->vt->f158(object, value);
    } else {
        ((Global_2701F8_eu*)&g_typedTextCaptionBox)->value = value;
        PushStackElement(g_elementStack, &g_typedTextCaptionBox);
    }
}

