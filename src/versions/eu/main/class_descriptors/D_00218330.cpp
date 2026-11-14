// SPDX-License-Identifier: AGPL-3.0-or-later
// The framed element's table, with PAL's slot 8: US's SetCaptionTextAndSize is absent from PAL,
// whose element tables hold SetScreenElementWideText (func_eu_001AB2B0) there.
void SetScreenElementWideText();
extern const T217D_Vt D_00218330 = {
    (ElementIntFn)InitScreenElement, (ElementFn)InitFramedElement, (ElementFn)UpdateScreenElementSlide, 0,
    0, (ElementFn)ResetScreenElement, 0, 0,
    (ElementTextFn)SetScreenElementWideText, (ElementFn)DrawElementWithFadedFrame, 0, (ElementTimeFn)GetScreenElementSlideInTime,
    (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement,
    (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0,
};
