// SPDX-License-Identifier: AGPL-3.0-or-later
// The constructor list D_0027B130 that RunConstructorsOnce walks: its count (0x12), the static
// initialisers of the files that have one (their _GLOBAL_$I$ functions), then a zero and the
// word 3. Its name is ours, after that role (it was the window file 001F8000.cpp).
#include "common.h"

void ConstructScriptMachineStaticsAtStartup();
void ConstructValuePoolsAtStartup();
void ConstructTextPanelStaticsAtStartup();
void ConstructCameraStaticColorAtStartup();
void ResetPacketWriters();
void ConstructDefaultRgbaColorAtStartup();
void ConstructBoxStylesAtStartup();
void ConstructMenuBoxStyleAtStartup();
void ConstructScreenTextStylesAtStartup();
void ConstructBestTimeTextStyleAtStartup();
void ConstructWarpTextStyleGlobalsAtStartup();
void ConstructTriangleGroupColorsAtStartup();
void ConstructMovieRingSinkAtStartup();
s32 ConstructSwitchedColliderDefaultsAtStartup();
void ConstructScratchpadTransfersAtStartup();
void ConstructWorldLoadRequestGlobalAtStartup();
void ConstructGreyColorAtStartup();
void RegisterProgramFrameInfo();
void* D_0027B130[21] = {
    (void*)0x12, ConstructScriptMachineStaticsAtStartup, ConstructValuePoolsAtStartup, ConstructTextPanelStaticsAtStartup,
    ConstructCameraStaticColorAtStartup, ResetPacketWriters, ConstructDefaultRgbaColorAtStartup, ConstructBoxStylesAtStartup,
    ConstructTriangleGroupColorsAtStartup, ConstructMovieRingSinkAtStartup, ConstructSwitchedColliderDefaultsAtStartup, ConstructMenuBoxStyleAtStartup,
    ConstructScreenTextStylesAtStartup, ConstructScratchpadTransfersAtStartup, ConstructBestTimeTextStyleAtStartup, ConstructWorldLoadRequestGlobalAtStartup,
    ConstructGreyColorAtStartup, ConstructWarpTextStyleGlobalsAtStartup, RegisterProgramFrameInfo, 0,
    (void*)3
};
