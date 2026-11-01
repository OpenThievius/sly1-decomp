// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: D_002701F8.value is at 0x5B0 (US 0x324).
struct Global_2701F8_eu { u8 pad[0x5B0]; void* value; };

void func_00151860(void* value, Object_151860* object)
{
    if (object != 0) {
        object->vtable->callback(object, value);
    } else {
        ((Global_2701F8_eu*)&D_002701F8)->value = value;
        func_001E9498(D_00275BC0, &D_002701F8);
    }
}

