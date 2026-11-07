// SPDX-License-Identifier: AGPL-3.0-or-later
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
