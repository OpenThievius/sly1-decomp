// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 126/184 (68.5%), checked 2026-11-07
// NEAR: order: the zero stores come out in another order than retail's; a random order search
//       reached 21 differing lines and was not kept.
#include "common.h"
#include "cursor_animator.h"
#include "globals.h"

extern AnimCursor* g_lastPendingCursor;
extern AnimCursor* g_pendingCursors;
extern CursorAnimator** g_cursorAnimators;
void FillMemory(void* p, int zero, s32 count);
extern s32 g_animRecordCount;
extern AnimRecord* g_animRecords;
extern s32 g_imageRecordCountA;
extern s32 g_defaultFont;
extern s32 g_fontCount;
extern s32 g_fontRecords;
extern s32 g_imageRecordCountB;
extern s32 g_fonts[5];
extern s32 g_activeImageMask;
extern s32 g_cursorAnimatorCount;
extern s32 g_maskImageUploads[6];
extern s32 g_maskedImagesPacket;
void InitMeshQueue(void);
void ResetScreenResources(void)
{
    g_imageRecordCountA = 0;
    g_imageRecordsB = 0;
    g_defaultFont = 0;
    g_fontCount = 0;
    g_fontRecords = 0;
    g_animRecords = 0;
    g_imageRecordsA = 0;
    g_imageRecordCountB = 0;
    g_animRecordCount = 0;
    FillMemory(g_fonts, 0, 0x14);
    g_cursorAnimators = 0;
    g_activeImageMask = 0;
    g_pendingCursors = 0;
    g_lastPendingCursor = 0;
    g_cursorAnimatorCount = 0;
    FillMemory(g_maskImageUploads, 0, 0x18);
    g_maskedImagesPacket = 0;
    InitMeshQueue();
}
