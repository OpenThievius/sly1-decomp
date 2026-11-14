// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL reads the state at offset 0x570 of the global block (US 0x260).
struct Gl_eu_1F4808 { u8 pad[0x570]; s32 f570; };
void StartObjectSubGroupFinish(ObjectSubGroup* self)
{
    BaseObject* key;
    s32 i;
    s32 found = 0;
    s32 next;
    Animation* it;

    key = (BaseObject*)GetActiveSwitchedCollider();
    if (((Gl_eu_1F4808*)&g_timerCaption)->f570 == 2
        && (self->f2E0 != 0 || self->f2D4 != 0
            || (g_saveData->entryIndex == 0 && (u8)GetEntryIdByKey(self->levelEntry) == 1))) {
        FinishBestTimeRun(&g_timerCaption);
        SetObjectSubGroupState(self, 2);
        goto tail;
    }
    if (((Gl_eu_1F4808*)&g_timerCaption)->f570 >= 2) {
        SetBestTimeState(&g_timerCaption, 4);
    }
    if (self->exitsLevel != 0) {
        BeginLevelExit(1, self->exitTarget);
        SetObjectSubGroupState(self, 0);
        return;
    }
    if (key == 0 || IsObjectOfKind(key, 0x16) == 0) {
        RemoveCameraControllers(g_camera, 2, 0, (CameraController*)((u8*)g_camera + 0x460), 0, 0);
    }
    SetObjectSubGroupState(self, 5);
    for (i = 0; i < self->count; i++) {
        it = (Animation*)self->items[i];
        CreateAnimationPlayerWithoutPresetTargets(it, 0, 0, 0, 0.0f, 1.0f);
        next = 0;
        if (found != 0 || HasAnimationEventKind19(it) != 0) {
            next = 1;
        }
        found = next;
    }
    if (found == 0) {
        if (self->fadeDelay > 0.0f) {
            self->fadeTime = ((f32*)&g_gameTime)[0] + self->fadeDelay;
        } else if (self->count > 0) {
            self->fadeTime = ((f32*)&g_gameTime)[0] + ((Animation*)self->items[0])->length;
        } else {
            self->fadeTime = ((f32*)&g_gameTime)[0];
        }
    }
tail:
    TriggerScriptEvent(self, 2, 0, 0);
}
