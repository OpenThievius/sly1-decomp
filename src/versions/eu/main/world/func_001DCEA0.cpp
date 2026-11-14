// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL's copy of LoadWorld (US func_001DCEA0, src/main/path_follower.cpp): it also reads the text table
// (func_eu_001DDA10) after SkipBufferedBlocks and the 14 entries of D_eu_0027EEA0 after f1D74,
// and finds the map screen's current page at 0x570 (US 0x260).
extern const char* D_eu_0027EEA0[];
void LoadTextTable(void* a0);
struct MapScreen_eu { u8 pad0[0x570]; WarpPage* current; };

void LoadWorld(World* self, BufferedStream* s)
{
    Rgba4 color;
    ListFrame walk;
    ListFrame frame;
    s32 i;
    ResetScatterController((ScatterController*)g_scatterController);
    InitScriptValuePools();
    D_00275714 = ReadBufferedU8(s);
    self->f1D70 = ReadBufferedS16(s);
    SkipBufferedBlocks(s);
    LoadTextTable(s);
    g_camera = (Camera*)CreateTypedRecord(0x6D, self, 0, 4, -1);
    for (i = 0; i < 10; i++) {
        BaseObject* o = (BaseObject*)CreateTypedRecord(0x1E, self, 0, 0xA, -1);
        o->desc->m03(o);
    }
    for (i = 0; i < 0x28; i++) {
        BaseObject* o = (BaseObject*)CreateTypedRecord(0x4D, self, 0, 0xB, -1);
        o->desc->m03(o);
    }
    LoadScriptEntryTable(self, s);
    ReadPropertyRecords(self, s);
    ReadOptionalBufferedBlock(s, (u32*)&self->f2310);
    ReadBufferedString(s, (u8**)&self->f2314);
    ReadOptionalBufferedBlock(s, (u32*)&self->f1D74);
    for (s32 k = 0; k < 14; k++) {
        ReadOptionalBufferedBlock(s, (u32*)&D_eu_0027EEA0[k]);
    }
    LoadScreenResources(s);
    ReadSlotObjects(self, 0, s);
    ReadBufferedBlockBody(s);
    if (self->f1D70 >= 0) {
        EnsureSoundBankLoaded(self->f1D70);
    }
    if (self->f1D78 == 0) {
        SilenceVolumeChannel2();
    }
    RequestStagedBank(self->f1D74);
    SendResidentImages();
    if (IsListEmpty(&self->list1BE8) != 0) {
        CreateConeVolumes(self);
    }
    self->f1D67 = 0x80;
    color = self->color1D64;
    FillScreenColor(D_002BDC20, &color, 0);
    self->f1D68 *= 0.003921569f;
    self->f1D6C *= 0.003921569f;
    SpawnListedObjectCopies(self);
    RunQueuedCalls(self);
    for (BaseObject* o = (BaseObject*)self->list48.head; o != 0; o = o->next) {
        if (o->desc->m0F != 0) {
            o->desc->m0F(o);
        }
    }
    RunQueuedCalls(self);
    List01* list = &self->list48;
    frame.list = list;
    frame.offset = list->offset;
    frame.prev = g_activeListFrames;
    g_activeListFrames = &frame;
    BaseObject* head = *(BaseObject**)frame.list;
    frame.link = (u8*)head + frame.offset;
    BaseObject* h = head;
    while (h != 0) {
        h->desc->m10(h);
        BaseObject* nx = *(BaseObject**)frame.link;
        frame.link = (u8*)nx + frame.offset;
        h = nx;
    }
    g_activeListFrames = frame.prev;
    RunQueuedCalls(self);
    UpdateScatterLevelLimits((ScatterController*)g_scatterController);
    ResumeElementStackState(g_elementStack);
    if (((MapScreen_eu*)&g_mapScreenList)->current == 0 && g_saveData->f19D8 != 0) {
        AllocateZeroedFrontMemory(0x80000);
    }
    UpdateCameraLocation(g_camera);
    UpdateWorldContacts(self, 0);
    PlayStagedBank(self->f1D74);
    StartWorldSoundEntries(self);
}
