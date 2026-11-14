// SPDX-License-Identifier: AGPL-3.0-or-later
// The constructor list D_0027B130 that RunConstructorsOnce walks: its count (0x12), the static
// initialisers of the files that have one (their _GLOBAL_$I$ functions), then a zero; after it,
// in the same run of words, the destructor list (its count, 3, the three exit functions, a zero)
// and the count of the frame information list (6), whose six objects D_0027B198 lists, ending in
// a zero, to the end of .data. D_0027B184, the destructor list's first function, is a label inside
// D_0027B130 (tlb.cpp takes its address): only an object starting there would be aligned to 8,
// which 0x27B184 is not. Its name is ours, after that role (it was the window file 001F8000.cpp).
#include "common.h"

extern "C" void ConstructScriptMachineStaticsAtStartup();
void ConstructValuePoolsAtStartup();
extern "C" void ConstructTextPanelStaticsAtStartup();
extern "C" void ConstructCameraStaticColorAtStartup();
void ResetPacketWriters();
void ConstructDefaultRgbaColorAtStartup();
extern "C" void ConstructBoxStylesAtStartup();
extern "C" void ConstructMenuBoxStyleAtStartup();
void ConstructScreenTextStylesAtStartup();
void ConstructBestTimeTextStyleAtStartup();
extern "C" void ConstructWarpTextStyleGlobalsAtStartup();
extern "C" void ConstructTriangleGroupColorsAtStartup();
extern "C" void ConstructMovieRingSinkAtStartup();
s32 ConstructSwitchedColliderDefaultsAtStartup();
extern "C" void ConstructScratchpadTransfersAtStartup();
extern "C" void ConstructWorldLoadRequestGlobalAtStartup();
void ConstructGreyColorAtStartup();
void RegisterProgramFrameInfo();
extern "C" void DestroyScriptMachineStaticsAtExit();
void DestroyValuePoolsAtExit();
void ReleaseProgramFrameInfo();
void* D_0027B130[26] = {
    (void*)0x12, ConstructScriptMachineStaticsAtStartup, ConstructValuePoolsAtStartup, ConstructTextPanelStaticsAtStartup,
    ConstructCameraStaticColorAtStartup, ResetPacketWriters, ConstructDefaultRgbaColorAtStartup, ConstructBoxStylesAtStartup,
    ConstructTriangleGroupColorsAtStartup, ConstructMovieRingSinkAtStartup, ConstructSwitchedColliderDefaultsAtStartup, ConstructMenuBoxStyleAtStartup,
    ConstructScreenTextStylesAtStartup, ConstructScratchpadTransfersAtStartup, ConstructBestTimeTextStyleAtStartup, ConstructWorldLoadRequestGlobalAtStartup,
    ConstructGreyColorAtStartup, ConstructWarpTextStyleGlobalsAtStartup, RegisterProgramFrameInfo, 0,
    (void*)3, DestroyScriptMachineStaticsAtExit, DestroyValuePoolsAtExit, ReleaseProgramFrameInfo, 0,
    (void*)6
};

// The frame information of the six objects that have it (the libraries' C++ files: allocate.cpp,
// exception.cpp, new_handler.cpp, type_info.cpp and the two before them), which
// RegisterProgramFrameInfo hands to the runtime, ending in a zero.
extern u8 D_00278000[], D_00278050[], D_00278644[], D_002789DC[], D_00278A7C[], D_00278E88[];
u8* D_0027B198[7] = { D_00278000, D_00278050, D_00278644, D_002789DC, D_00278A7C, D_00278E88, 0 };
