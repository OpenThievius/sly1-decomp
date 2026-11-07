// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the memory-card directory names carry SCES-50917, the title is "Sly Raccoon", and the save count is 11.
s32 func_0018C250(MemoryCard* self)
{
    char name[0x50];
    s32 info[4];
    s32 r = FinishMemoryCardCall((s32)func_0020A078(self->port, self->slot, "/"), (void*)0x12, (s32)info);
    if (r != 0) return r;
    s32 need = info[0] == 0 ? 2 : 1;
    s32 sz = GetKeyedDataSize((KeyRecord*)g_memoryCardIconKey);
    need += 5;
    need += (sz + 1023) / 1024;
    need += 0x15;
    if (self->freeBlocks < need) return 1;
    const char* dir = "/BESCES-50917YAOTWTD!";
    r = CreateMemoryCardDirectory(self, (void*)dir);
    if (r == 0) {
        const char* title = "Sly Raccoon";
        r = CreateMemoryCardFile(self, (void*)"/BESCES-50917YAOTWTD!/BESCES-50917YAOTWTD!", (void*)title, 11);
        if (r == 0) {
            r = WriteMemoryCardSaveHeader(self, (void*)dir, (void*)title);
            if (r == 0) {
                r = WriteMemoryCardIcon(self, (void*)dir);
                if (r == 0) {
                    for (s32 i = 0; i < 3; i++) {
                        FormatToString(name, "/%s/%s%d", "BESCES-50917YAOTWTD!", "save", i + 1);
                        r = WriteMemoryCardSlot(self, name, (u8*)self + 0x30 + i * 0x1A5C, (u8*)self + 0x1A30 + i * 0x1A5C);
                        if (r != 0) return r;
                    }
                    if (self->targetState < 5) self->targetState = 5;
                }
            }
        }
    }
    return r;
}
