// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 368/376, checked 2026-11-10
// NEAR (2026-11-08, night-gamec): registers: retail keeps the point count in s6 and -1 in s7 (swapped here) and copies each link index to v1 before its multiply
// In the context of its file, src/main/file_1E08F8.cpp: its declarations before the function, bodies cut.
#include "common.h"
#include "asm_func.h"
#include "on_off_object.h"
#include "collider.h"
#include "world.h"
#include "camera_controller.h"
#include "globals.h"
#include "buffered_stream.h"
#include "key_id.h"
#include "load_progress.h"
#include "output_buffer.h"
#include "game_progress.h"
#include "flag_table.h"
#include "semaphore_params.h"
#include "thread_params.h"
#include "memory_card.h"
#include "screen_element.h"
#include "vu0.h"
#include "fpu.h"

void* InitStringOutputBuffer(u8* buf, char* dst, s32 cap);
s32 FormatToOutputBuffer(u8* buf, s32 a, s32 b);
void DestroyOutputBuffer(u8* buf, s32 n);

void* FillMemory(void* p, s32 v, s32 n);
s32 NewSemaphore(void* self);

s32 PrintFormattedVa(void* self, void* ap);

// The stack room of an output buffer as the format functions declare one: its header and the
// 0x400 bytes AppendToOutputBuffer fills before it flushes.
struct OutputBufferStorage { u8 bytes[0x420]; };

void* InitStringOutputBuffer(void* stream, char* dst, s32 cap);
s32 FormatToOutputBuffer(void* stream, const char* fmt, void* ap);
void DestroyOutputBuffer(void* stream, s32 mode);

s32 FormatToStringVa(char* dst, const char* fmt, void* ap);

s32 FormatToStringBoundedVa(char* dst, s32 cap, const char* fmt, void* ap);

void* InitOutputBuffer(void* stream, s32 cap);
s32 FormatToOutputBuffer(void* stream, const char* fmt, void* ap);
void DestroyOutputBuffer(void* stream, s32 mode);

s32 GetStringLength(void* p);
void CopyMemory(void* dst, void* src, s32 count);

s32 GetStringLength(void* p);
void CopyMemory(void* dst, void* src, s32 count);

s32 CreateLockSemaphore(s32 a, s32 b);

// A lock one thread may take again (InitRecursiveLock, EnterRecursiveLock, LeaveRecursiveLock):
// how many times its holder took it, the holder's thread id (-1 for none) and the semaphore.
struct RecursiveLock { s32 count; s32 last; void* sema; };

void RemoveCameraControllers(u32 a0, int a1, int a2, void* a3, int a4, void* a5);
void PushCameraController(u32 a0, int a1, void* a2, int a3, void* a4);
void TriggerScriptEvent(void* self, s32 a, s32 b, s32 c);
extern f32 g_gameTime;

void UpdateOnOffObjectState(void* self, s32 a, s32 b);

extern void PostSemaphore(void* a);

void UpdatePlacedObject(void* self);
void UpdateOnOffObjectState(void* self, s32 a, s32 b);
void* AppendQueuedCall(void* owner, void* fn, void* arg, s32 a3, s32 a4);

void DrawPlacedObject(void);

extern f32 D_00275980[16];

void UnregisterPlacedObject(void* self);
void SetOnOffObjectState(void* self, s32 state);
void RemoveQueuedCalls(void* a, s32 b, s32 c, void* d, s32 e, s32 f);

void StartPlacedObject(void* self);

void SetPlacedObjectFrozen(void* self, void* p);
void SetOnOffObjectState(void* selfv, s32 state);

void ReadBufferedRotation3(void* a, void* b);
void ReadBufferedVector3(void* a, void* b);
s32 ReadBufferedS8(void* a);
void* CreatePathCurve(s32 idx);
void ReadPropertyRecords(void* a, void* b);

// What an on-off camera controller points to: while f438 is set, its f43C is the camera's f1C8.
struct CameraFovSource { u8 pad[0x438]; f32 f438; f32 f43C; };

void* FillMemory(void* p, s32 zero, s32 size);

extern u8 D_00275940[0x18];

u64 func_001FBE00(u64 value, u64 radix);
s64 func_001FC3D0(u64 value, u64 radix);
void CopyMemory(void* dst, void* src, s32 count);

extern f32 D_00275980[];
extern f32 D_00275A10[4];
extern f32 D_00275A20[2];

void InitPlacedObject(void* self);

extern s32 GetCurrentThreadId(void);
extern s32 AwaitSemaphore(void* a);

// A conversion of the formatter (func_001E1DB8): func_001E0978 parses it from a '%' on, and
// func_001E1A08 hands it to the writer of its kind (func_001E0CD0 strings, func_001E1028
// integers, func_001E17A8 floats).
struct FormatSpec {
    s32 left;       // 0x00: '-'
    s32 plus;       // 0x04: '+'
    s32 space;      // 0x08: ' '
    s32 alt;        // 0x0C: '#'
    s32 zero;       // 0x10: '0'
    s32 noprec;     // 0x14: the precision given as zero
    s32 width;      // 0x18
    s32 prec;       // 0x1C
    s32 length;     // 0x20: 1 'h', 2 'l' or 'L'
    s32 f24;        // 0x24: a vector's count (3, or 4 for an upper-case letter)
    s32 f28;        // 0x28: a matrix's rows ('v' for one)
    u8 conv;        // 0x2C: the conversion letter, in lower case
    s8 pad2D[3];
    s32 upper;      // 0x30: the letter was upper case
};

// A point as func_00128018 writes it and func_001E4DC0 tests it.
struct FacePoint {
    s32 v[4];
};

void* GetActiveSwitchedCollider(void);
void TransformPointBetweenFrames(void* a0, OnOffObject* a1, void* a2, FacePoint* a3);
s32 IsPointInsideFaceTree(TreeNode03* self, FacePoint* value);
void SetOnOffObjectState(OnOffObject* self, s32 state);

// func_001E1DB8's frame: the conversion it parses, then the argument pointer.
struct FormatFrame {
    FormatSpec spec;    // the conversion spec, at sp + 0
    u8 pad34[0x40 - 0x34];
    void* va;           // the argument pointer, at sp + 0x40
    u8 pad44[0xC];
};

void FlushOutputBuffer(OutputBuffer* ctx);
s32 AppendToOutputBuffer(OutputBuffer* ctx, const char* p, s32 n);
char* FindCharInString(const char* s, s32 c);
s32 GetStringLength(const char* s);
s32 ParseFormatSpec(const char* at, FormatSpec* spec, void* va);
void FormatConversionArg(FormatSpec* spec, OutputBuffer* ctx, void* va, const char* at, s32 len);

extern u8 g_charClassFlags[];

struct IntegerArg {
    u64 v;
};

s32 ExtractIntegerSign(FormatSpec* self, IntegerArg* v);
s32 GetStringLength(char* p);
s32 GetConversionRadix(s8 c);
s32 WriteIntegerDigits(char* buf, s32 len, u64 value, u32 radix);
s32 AppendToOutputBuffer(OutputBuffer* sink, const char* p, s32 n);
void UppercaseString(char* p);

void* FillMemory(FormatSpec* dst, s32 value, s32 size);
s32 ParseSignedDecimal(s8* s, s32* out);
extern u8 g_charClassFlags[];

s32 GetStringLength(const char* s);
s32 AppendToOutputBuffer(OutputBuffer* c, const char* s, s32 n);
void FormatStringArg(FormatSpec* sp, OutputBuffer* c, const char* s);
void FormatIntegerArg(FormatSpec* sp, OutputBuffer* c, u64 v);
void FormatFloatArg(FormatSpec* sp, OutputBuffer* c, s64 s);
void FormatFloatArg(FormatSpec* sp, OutputBuffer* c, double value);
s32 FormatFloatDigits(char* buf, s32 n, FormatSpec* sp, double value);
void UppercaseString(char* p);
double func_001FD868(f32 f);

struct PaddedOutput : OutputBuffer {
    void Pad(u8 ch, s32 count)
    {
        u8 buf = ch;
        while (count-- > 0) {
            if (AppendToOutputBuffer(this, (const char*)&buf, 1) != 1) {
                break;
            }
        }
    }
};

struct RegDouble { u8 pad; };

f32 Power(f32 a, f32 b);
RegDouble* func_001FCDE0(RegDouble* self, u64 v);
RegDouble* func_001FCDE0(RegDouble* self, double v); // soft-float double in a1
RegDouble* TruncateDouble(RegDouble* self);
RegDouble* func_001FCD78(RegDouble* self, RegDouble* v);
s32 ConvertDoubleToS32(RegDouble* self);

extern u8 D_00275940[];

void* CopyString(char* dst, char* src);
s32 GetStringLength(char* p);
s32 GetDecimalExponent(double v);
u8 GetDecimalDigit(double v, s32 e, s32 i);
f32 Power(f32 a, f32 b);
double func_001FD868(f32 f);
double func_001FCDE0(double a, double b);
double func_001FCD20(double a, double b);

union DoubleBits {
    double d;
    u64 u;
};

extern u8 g_renderThreadStack[];
extern u8 D_002832F0[];
// The ids of the main thread and of the render thread func_001E2398 starts.
struct ThreadIds { s32 main; s32 render; };
extern ThreadIds g_mainAndRenderThreads;

void RunRenderThread(void);
s32 GetCurrentThreadId(void);
void SetThreadPriority(s32 a, s32 b);
s32 FillMemory(ThreadParams* p, s32 zero, s32 size);
s32 MakeThread(ThreadParams* p);

s32 func_001FD308(double a, double b);
f32 func_001FD578(double a);
f32 LogarithmBase10(f32 x);
double func_001FD868(f32 x);
s32 ConvertDoubleToS32(double a);
double func_001FD358(s32 a);

extern f32 g_gameClock[];

struct SpanCandidate { u8 pad[0x20]; f32 value; };

void* FillMemory(void* p, s32 v, s32 n);

// The eight scrambled words that locate a level's data on the disc: the key of the sector
// range is w[0] ^ w[5] and w[1] ^ w[7]; two blocks are the same level when w[2] ^ w[6] agree.
struct WorldKeyBlock { u32 w[8]; };

// The world load QueueWorldLoad (func_001E4E80) asks for and RunPendingWorldLoad
// (func_001E4EA8) carries out. Built at startup: its constructor is func_001E4E38; the
// compiler's initialiser and constructor for this file are func_001E5328 and func_001E5358
// (config/us/generated.tsv).
struct WorldLoadRequest {
    s32 state;              // 0x00: 1 while a load is queued
    WorldKeyBlock* key;     // 0x04: the level to load, or 0 to stay
    s32 f8;                 // 0x08: the ids FindOrActivateSwitchedCollider starts from
    s32 fC;                 // 0x0C
    s32 flags;              // 0x10: handed to SetCurrentLevelEntry; 0x10 shows D_0026C6C8
    WorldKeyBlock current;  // 0x14: the level loaded last
    WorldLoadRequest();
};

extern FlagTable g_flagTable;

void SetIopVolumeChannel8(f32 x);
void StartScreenFadeFromFlagTable(FlagTable* r);
void QueueWorldLoad(WorldLoadRequest* self, WorldKeyBlock* key, s32 a, s32 b, s32 flags);

struct SameWorldKey {
    static s32 Of(WorldKeyBlock* a, WorldKeyBlock* b)
    {
        if (a == b) return 1;
        if (b == 0) return 0;
        return ((a->w[2] ^ a->w[6]) ^ (b->w[2] ^ b->w[6])) == 0;
    }
};
struct OwnedStream : BufferedStream {
    void SetOwner(void* o) { owner = o; }
};

extern u8 D_002C3B00[];
extern u8 g_scatterController[];
extern u8 D_002623D8[];

extern f32 g_frameStep;

void SetScreenOwner(s32 a);
void ClearKeyId(KeyId* q);
LoadProgress* InitLoadProgress(LoadProgress* q, U32P* a, U32P* b, U32P* c, U32P* d);
void* InitBufferedStream(BufferedStream* q, s32 a, u8* b, s32 c);
void BeginLoadProgress(void* q);
s32 OpenBufferedSectorStreamRange(BufferedStream* q, KeyId* k);
void DestroyBufferedStream(BufferedStream* q, s32 n);
void ResetWorldSubsystems(World* q);
void ReadBufferedBlockHeader(s32 a, BufferedStream* q);
void SetGameClockTime(u8* q, f32 v);
s32 SetPadSelectFlags(s32 n);
void SetCurrentLevelEntry(WorldKeyBlock* q, s32 n);
World* CreateTypedRecord(s32 a, s32 b, s32 c, s32 d, s32 e);
void SetVolumeChannelFactor(s32 a, s32 b, f32 x);
void CloseBufferedStream(BufferedStream* q);
void EndLoadProgress(void* q);
void StartMemoryCardSave(MemoryCard* q);
void ResetCamera(s32 q, s32 f);
void UpdateSoundEmitters(void);
s32 FindOrActivateSwitchedCollider(World* q, s32 a, s32 b);
void NotifyScatterControllerLoaded(u8* q);
void ResetCounter(u8* q);
void RestoreSelectionCaptionCamera(T217D_12E0* q);
void UpdateWorldContacts(World* q, s32 n);
void UpdateCamera(s32 q, s32 n, f32 v);
void SetGameClockScale(f32 x);
void ResetVolumeChannelFactors(void);
void ClearScreenOwner(s32 a);

// The file's .data, in retail's order; the labels only its assembly reads are included.
u8 D_00275940[0x18] = "0123456789abcdef";
ThreadIds g_mainAndRenderThreads = { 0, 0 };
u8 D_00275960[4] = { 0 };
s32 g_movieDecodeThread = 0;
f32 D_00275980[16] = { -450.0f, 0, 0, 0, 0, 1.0f, 0, 0, 0, 1.0f, 0, 0, 125.0f, 1.0f, 0, 0 };
f32 D_00275A10[4] = { 0, 0.5f, 0, 0 };
f32 D_00275A20[2] = { 0, 3.4028235e38f };

s32 ParseSignedDecimal(s8* s, s32* out);

s32 ParseFormatSpec(s8* at, FormatSpec* spec, s32** va);

void FormatStringArg(FormatSpec* self, PaddedOutput* ctx, const char* str);

s32 ExtractIntegerSign(FormatSpec* self, void* dst);

s32 GetConversionRadix(s8 c);

s32 WriteIntegerDigits(u8* buf, s32 len, u64 value, u32 radixArg);

void FormatIntegerArg(FormatSpec* self, OutputBuffer* sink, u64 value);

s32 GetDecimalExponent(double v);

s8 GetDecimalDigit(RegDouble* self0, s32 a, s32 b);

s32 FormatFloatDigits(char* buf, s32 unused, FormatSpec* sp, double v);

void FormatFloatArg(FormatSpec* spec, OutputBuffer* ctx, double value);

void FormatConversionArg(FormatSpec* sp, OutputBuffer* c, u8** va, const char* fmt, s32 len);

s32 FormatToOutputBuffer(OutputBuffer* ctx, const char* fmt, void* a2);

s32 PrintFormattedVa(const char* fmt, void* ap);

s32 PrintFormatted(void* self, ...);

s32 FormatToStringVa(char* dst, const char* fmt, void* ap);

s32 FormatToString(char* dst, const char* fmt, ...);

s32 FormatToStringBoundedVa(char* dst, s32 cap, s32 a, s32 b);

s32 FormatToStringBounded(char* dst, s32 cap, const char* fmt, ...);

s32 GetStringLength(const char* s);

void* CopyString(void* dst, void* src);

void* AppendString(void* dst, void* src);

char* FindCharInString(char* s, s32 c);

void UppercaseString(s8* p);

void CreateLockSemaphore(void* a, void* b);

void InitRecursiveLock(RecursiveLock* self);

void EnterRecursiveLock(RecursiveLock* self);

void LeaveRecursiveLock(RecursiveLock* self);

void CreateRenderThread(void);

void* GetOnOffObjectBlock(void* self);

void InitOnOffObject(OnOffObject* self);

void UnregisterOnOffObject(OnOffObject* self);

void LoadOnOffObject(OnOffObject* self, void* a1);

void StartOnOffObject(OnOffObject* self);

void SetOnOffObjectState(void* selfv, s32 state);

void SetOnOffObjectForcedState(void* selfv, s32 value);

void UpdateOnOffObjectState(OnOffObject* self);

void UpdateOnOffObject(OnOffObject* self);

void DrawOnOffObject(void);

void SetOnOffObjectFrozen(OnOffObject* self, void* p);

void SetOnOffObjectBlockValue(OnOffObject* self, f32 value);

typedef void (*OnOffShapeFn)(f32 angle, Arr63* obj, Vec02* out, Vec02* dir);
void ComputePolarOffset(Vec02* out, f32 a, f32 b, f32 c);
void BuildBasisFromXAndZHint(Vec02* dir, const Vec02* hint, Mat02* out);

void PlaceOnOffCameraFrame(OnOffObject* self, Vec02* eye, Vec02* out, Vec02* dir);

f32 FloatRemainder(f32 x, f32 y);
void TransformPointBetweenFrames(OnOffObject* from, void* to, void* in, FacePoint* out);

void PlaceOnOffCameraOrbit(f32 angle, f32 offset, OnOffObject* self, f32* x, f32* poly, f32* range, s32 mode, Vec02* out);

// The five quadwords func_00143418 gives for a camera and its target: the placement.
struct CameraPlacement { Vec02 q[5]; };
void BlendOnOffCameraPoint(void* block, CameraPlacement* eye, Vec02* out, OnOffObject* object);

void DeactivateOnOffCameraController(OnOffCameraController* self);

void NoteOnOffCameraControllerPushed(OnOffCameraController* self, s32 arg);

void NoteOnOffCameraControllerRemoved(OnOffCameraController* self, s32 arg);

f32 ArctangentOfRatio(f32 y, f32 x);

void func_001E30E8(OnOffCameraController* self, CameraPlacement* eye);

f32 GetSpanCandidateValue(void* a0, void* a1, void* a2, SpanCandidate* a3);

// A point of a mesh's tables: a float and a vector (32 bytes).
struct MeshPoint {
    f32 f;
    u8 pad04[0xC];
    Vec02 v;
};

// A link of a mesh's tables: the point it starts at and two other links, or none.
struct MeshLink {
    MeshPoint* point;
    MeshLink* a;
    MeshLink* b;
};

s32 ReadBufferedU16(BufferedStream* s);
s32 ReadBufferedS16(BufferedStream* s);
f32 ReadBufferedFloat(BufferedStream* s);
void* AllocateFrontMemory(s32 size);

void ReadMeshTables(void* stream, void* nOut, void* pointsOut, void* mOut, void* linksOut)
{
    BufferedStream* s = (BufferedStream*)stream;
    s32 n = ReadBufferedU16(s);
    MeshPoint* points = (MeshPoint*)AllocateFrontMemory(n * sizeof(MeshPoint));
    for (s32 i = 0; i < n; i++) {
        points[i].f = ReadBufferedFloat(s);
        ReadBufferedVector3(s, &points[i].v);
    }
    s32 m = ReadBufferedU16(s);
    MeshLink* links = (MeshLink*)AllocateFrontMemory(m * sizeof(MeshLink));
    for (s32 i = 0; i < m; i++) {
        links[i].point = &points[ReadBufferedU16(s)];
        s32 k = ReadBufferedS16(s);
        if (k == -1) {
            links[i].a = 0;
        } else {
            links[i].a = &links[k];
        }
        k = ReadBufferedS16(s);
        if (k == -1) {
            links[i].b = 0;
        } else {
            links[i].b = &links[k];
        }
    }
    *(s32*)nOut = n;
    *(MeshPoint**)pointsOut = points;
    *(s32*)mOut = m;
    *(MeshLink**)linksOut = links;
}
