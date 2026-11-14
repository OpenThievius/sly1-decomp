// SPDX-License-Identifier: AGPL-3.0-or-later
// The prompt element's table, with PAL's slot 16: PAL's holds the generic SetScreenElementMode
// (func_001AB790), where US's has SetElementModeRebuildingText (US func_001AE130).
// Slot 8 stays SetScreenElementText, which PAL's translation table pairs with its
// SetScreenElementWideText (func_eu_001AB2B0), as in the other element tables.
extern const T217D_Vt D_002184C0 = { (ElementIntFn)InitScreenElement, (ElementFn)InitPromptElement, (ElementFn)UpdatePromptElement, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawPromptElement, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
