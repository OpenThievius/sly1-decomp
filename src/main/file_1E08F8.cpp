// SPDX-License-Identifier: AGPL-3.0-or-later
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



void FillMemory(void* p, s32 v, s32 n);
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
s32 ReadMeshTables(void* a, void* b, void* c, void* d, void* e);
s32 ReadBufferedS8(void* a);
void* CreatePathCurve(s32 idx);
void ReadPropertyRecords(void* a, void* b);




// What an on-off camera controller points to: while f438 is set, its f43C is the camera's f1C8.
struct CameraFovSource { u8 pad[0x438]; f32 f438; f32 f43C; };



void FillMemory(void* p, s32 zero, s32 size);

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




void FillMemory(FormatSpec* dst, s32 value, s32 size);
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



void FillMemory(void* p, s32 v, s32 n);

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
INCLUDE_DATA(D_00275970);
INCLUDE_DATA(D_00275974);
INCLUDE_DATA(D_00275978);
f32 D_00275980[16] = { -450.0f, 0, 0, 0, 0, 1.0f, 0, 0, 0, 1.0f, 0, 0, 125.0f, 1.0f, 0, 0 };
INCLUDE_DATA(D_002759C0);
f32 D_00275A10[4] = { 0, 0.5f, 0, 0 };
f32 D_00275A20[2] = { 0, 3.4028235e38f };
INCLUDE_DATA(D_00275A28);
INCLUDE_DATA(D_00275A2C);
INCLUDE_DATA(D_00275A30);
INCLUDE_DATA(D_00275A40);
INCLUDE_DATA(D_00275A50);
INCLUDE_DATA(D_00275A58);
INCLUDE_DATA(D_00275A70);
INCLUDE_DATA(D_00275A80);
INCLUDE_DATA(D_00275A90);
INCLUDE_DATA(D_00275AA0);

s32 ParseSignedDecimal(s8* s, s32* out)
{
    s8* p = s;
    s32 sign = 1;
    s32 value = 0;
    s32 count = 0;
    u8 c;

    if (*p == 0x2D) {
        sign = -1;
    }
    if (sign == -1) {
        p++;
        count = 1;
    }
    c = *p;
    if ((u32)(c - 0x30) < 10) {
        do {
            value = value * 10 + ((s8)c - 0x30);
            p++;
            c = *p;
            count++;
        } while ((u32)(c - 0x30) < 10);
    }
    *out = value * sign;
    return count;
}

s32 ParseFormatSpec(s8* at, FormatSpec* spec, s32** va)
{
    s32 state = 0;
    s8* p = at;
    s32 next;

    FillMemory(spec, 0, 0x34);
    if (*at != 0) {
        for (;;) {
            s32 adv = 0;
            next = state;
            switch (state) {
            case 0: {
                s8 c = *p;
                if (c != 0x25) {
                    next = 6;
                } else {
                    s8 d = p[1];
                    next = 1;
                    if (d == c) {
                        spec->conv = d;
                        next = 6;
                        adv = 2;
                    } else {
                        adv = 1;
                    }
                }
                break;
            }
            case 1:
                switch ((s8)((u8)*p - 0x20)) {
                case 13:
                    spec->left = 1;
                    adv = 1;
                    break;
                case 11:
                    spec->plus = 1;
                    adv = 1;
                    break;
                case 0:
                    spec->space = 1;
                    adv = 1;
                    break;
                case 3:
                    spec->alt = 1;
                    adv = 1;
                    break;
                case 16:
                    spec->zero = 1;
                    adv = 1;
                    break;
                default:
                    next = 2;
                    break;
                }
                break;
            case 2:
                if (*p == 0x2A) {
                    s32* ap = *va;
                    s32 w;
                    *va = ap + 2;
                    w = *ap;
                    spec->width = w;
                    if (w < 0) {
                        w = (w < 0) ? -w : w;
                        spec->left = 1;
                        spec->width = w;
                    }
                    adv = 1;
                } else {
                    adv = ParseSignedDecimal(p, &spec->width);
                }
                if (p[adv] == 0x2E) {
                    next = 3;
                    adv++;
                } else {
                    next = 4;
                }
                break;
            case 3:
                if (*p == 0x2A) {
                    s32* ap = *va;
                    s32 w;
                    *va = ap + 2;
                    w = *ap;
                    adv = 1;
                    w = (w < 0) ? -w : w;
                    spec->prec = w;
                } else {
                    adv = ParseSignedDecimal(p, &spec->prec);
                }
                spec->noprec = spec->prec == 0;
                next = 4;
                break;
            case 4: {
                switch ((s8)((u8)*p - 0x4C)) {
                case 28:
                    spec->length = 1;
                    adv = 1;
                    break;
                case 32:
                    adv = 1;
                    if (p[1] != 0x6C) {
                        spec->length = 2;
                        break;
                    }
                    // fall through
                case 0:
                case 37:
                    spec->length = 2;
                    adv++;
                    break;
                case 1:
                case 10:
                case 33:
                case 42: {
                    s32 a = 3;
                    s32 r = 1;
                    s32 d;
                    s32 l;
                    if (g_charClassFlags[(s8)(u8)*p] & 1) {
                        a = 4;
                    }
                    spec->f24 = a;
                    d = *p;
                    l = (g_charClassFlags[d] & 1) ? d + 0x20 : d;
                    if (l ^ 0x76) {
                        r = a;
                    }
                    spec->f28 = r;
                    adv = 1;
                    break;
                }
                default:
                    break;
                }
                next = 5;
                break;
            }
            case 5:
                if (*p != 0x25) {
                    s32 e = *p;
                    s32 f;
                    s32 l;
                    spec->upper = g_charClassFlags[e] & 1;
                    f = *p;
                    l = (g_charClassFlags[f] & 1) ? f + 0x20 : f;
                    spec->conv = l;
                }
                adv = 1;
                next = 6;
                break;
            default:
                return p - at;
            }
            p += adv;
            state = next;
            if (*p == 0 || next == 6) {
                break;
            }
        }
    }
    return p - at;
}


void FormatStringArg(FormatSpec* self, PaddedOutput* ctx, const char* str) {
    s32 n;
    s32 right;
    s32 left;
    u8 pad;

    if (str == 0) {
        str = "(null)";
    }
    right = 0;
    n = GetStringLength(str);
    left = 0;
    if (self->prec != 0 && self->prec < n) {
        n = self->prec;
    } else if (self->noprec != 0) {
        n = 0;
    }
    if (n < self->width) {
        pad = (self->zero != 0) ? 0x30 : 0x20;
        s32 d = self->width - n;
        if (self->left != 0) {
            right = d;
        } else {
            left = d;
        }
    }
    ctx->Pad(pad, left);
    AppendToOutputBuffer(ctx, str, n);
    ctx->Pad(0x20, right);
}


s32 ExtractIntegerSign(FormatSpec* self, void* dst)
{
    s32 ret = 0;
    if (self->length != 1) {
        if (self->length < 2) {
            if (self->length == 0) {
                *(u32*)((u8*)dst + 4) = 0;
            }
        }
    } else {
        *(u64*)dst = *(u16*)dst;
    }
    if (self->conv == 'd' || self->conv == 'i') {
        switch (self->length) {
        case 0:
            if (*(s32*)dst < 0) {
                *(s32*)dst = -*(s32*)dst;
                ret = 1;
            }
            break;
        case 1:
            if (*(s16*)dst < 0) {
                *(s16*)dst = -*(u16*)dst;
                ret = 1;
            }
            break;
        case 2:
            if (*(s64*)dst < 0) {
                *(s64*)dst = -*(s64*)dst;
                ret = 1;
            }
            break;
        }
    }
    return ret;
}

s32 GetConversionRadix(s8 c)
{
    switch (c) {
    case 0x64:
    case 0x69:
    case 0x75:
        return 10;
    case 0x42:
    case 0x62:
        return 2;
    case 0x6F:
        return 8;
    case 0x78:
        return 16;
    }
    return 10;
}

s32 WriteIntegerDigits(u8* buf, s32 len, u64 value, u32 radixArg)
{
    u64 radix = radixArg;
    u8* end = buf + len;
    u8* stop = end;
    u64 v = value;
    do {
        s64 digit = func_001FC3D0(v, radix);
        end--;
        *end = D_00275940[(s32)digit];
        v = func_001FBE00(v, radix);
    } while (v != 0 && end >= buf);
    s32 count = stop - end;
    if (count != 0 && buf < end) {
        CopyMemory(buf, end, count);
    }
    return count;
}


void FormatIntegerArg(FormatSpec* self, OutputBuffer* sink, u64 value)
{
    char buf[0x50];
    char pfx[0x10];
    char padc[0x10];
    IntegerArg val;
    s32 total;
    s32 lead;
    s32 trail;
    s32 zeros;
    s32 plen;
    s32 ndig;
    s32 n;

    val.v = value;
    if (self->noprec != 0 || self->prec != 0) {
        self->zero = 0;
    }
    if (self->noprec != 0 && val.v == 0) {
        plen = 0;
        zeros = 0;
        ndig = 0;
    } else {
        s32 neg = ExtractIntegerSign(self, &val);
        zeros = self->prec;
        pfx[0] = 0;
        switch ((u8)self->conv) {
        case 'd':
        case 'i':
            if (neg) {
                __builtin_strcpy(pfx, "-");
            } else if (self->plus) {
                __builtin_strcpy(pfx, "+");
            } else if (self->space) {
                __builtin_strcpy(pfx, " ");
            }
            zeros -= GetStringLength(pfx);
            break;
        case 'b':
            if (self->alt) {
                __builtin_strcpy(pfx, "0b");
            }
            break;
        case 'o':
            if (self->alt) {
                __builtin_strcpy(pfx, "0");
            }
            break;
        case 'x':
            if (self->alt) {
                __builtin_strcpy(pfx, "0x");
            }
            break;
        }
        plen = GetStringLength(pfx);
        ndig = WriteIntegerDigits(buf, 0x40, val.v, GetConversionRadix(self->conv));
        zeros -= ndig;
        zeros = zeros >= 0 ? zeros : 0;
    }
    buf[ndig] = 0;
    if (self->upper) {
        UppercaseString(pfx);
        UppercaseString(buf);
    }
    total = plen + zeros + ndig;
    lead = 0;
    trail = 0;
    if (total < self->width) {
        s32 rem = self->width - total;
        if (self->left) {
            trail = rem;
        } else if (self->zero == 0) {
            lead = rem;
        } else if (ndig != 0) {
            zeros += rem;
        } else {
            lead = rem;
        }
    }
    padc[0] = ' ';
    n = lead;
    while (n-- > 0) {
        if (AppendToOutputBuffer(sink, padc, 1) != 1) {
            break;
        }
    }
    AppendToOutputBuffer(sink, pfx, plen);
    padc[0] = '0';
    n = zeros;
    while (n-- > 0) {
        if (AppendToOutputBuffer(sink, padc, 1) != 1) {
            break;
        }
    }
    AppendToOutputBuffer(sink, buf, ndig);
    padc[0] = ' ';
    n = trail;
    while (n-- > 0) {
        if (AppendToOutputBuffer(sink, padc, 1) != 1) {
            break;
        }
    }
}


s32 GetDecimalExponent(double v)
{
    s32 i;
    if (func_001FD308(v, 0.0) > 0) {
        double l = func_001FD868(LogarithmBase10(func_001FD578(v)));
        i = ConvertDoubleToS32(l);
        if (func_001FD308(l, 0.0) < 0 && func_001FD308(l, func_001FD358(i)) != 0)
            i--;
    } else {
        i = 0;
    }
    return i;
}

s8 GetDecimalDigit(RegDouble* self0, s32 a, s32 b)
{
    RegDouble* self = self0;
    s32 idx;
    if (a < b || a - 15 >= b) {
        idx = 0;
    } else {
        f32 t = Power(10.0f, (f32)(-b));
        RegDouble* p = func_001FCDE0(self, func_001FD868(t));
        self = TruncateDouble(p);
        p = TruncateDouble(func_001FCDE0(self, 0.1));
        p = func_001FCDE0(p, (u64)0x4024000000000000ULL);
        idx = ConvertDoubleToS32(func_001FCD78(self, p));
    }
    return ((s8*)&D_00275940)[idx];
}


s32 FormatFloatDigits(char* buf, s32 unused, FormatSpec* sp, double v)
{
    DoubleBits bits;
    bits.d = v;
    if ((bits.u & 0x7FF0000000000000UL) == 0x7FF0000000000000UL) {
        const char* s = (bits.u & 0x000FFFFFFFFFFFFFUL) ? "(nan)" : "(inf)";
        CopyString(buf, (char*)s);
        return GetStringLength(buf);
    }
    char* out = buf;
    s32 e = GetDecimalExponent(v);
    s32 isE = sp->conv == 'e';
    if (sp->conv == 'g') {
        if (e < -4 || e >= sp->prec) {
            isE = 1;
            sp->prec = sp->prec - 1;
        }
    }
    s32 base = 0;
    if (isE) base = e;
    s32 prec = sp->prec;
    f32 p = Power(10.0f, (f32)(base - prec));
    double r = func_001FCD20(v, func_001FCDE0(func_001FD868(p), 0.5));
    s32 e2 = GetDecimalExponent(r);
    if (e < GetDecimalExponent(r)) e = e2;
    s32 n, i;
    if (isE) {
        n = 1;
        i = e;
    } else if (e >= 0) {
        i = e;
        n = e + 1;
    } else {
        n = 1;
        i = 0;
    }
    while (n-- > 0) {
        *out++ = GetDecimalDigit(r, e, i--);
    }
    if (sp->noprec == 0) {
        *out++ = '.';
        n = sp->prec;
        while (n-- > 0) {
            *out++ = GetDecimalDigit(r, e, i--);
        }
        if (sp->conv == 'g' && buf < out) {
            while (buf < out && out[-1] == '0') out--;
            if (buf < out && out[-1] == '.') out--;
        }
    }
    if (isE) {
        *out++ = 'e';
        if (e < 0) {
            *out++ = '-';
            e = -e;
        } else {
            *out++ = '+';
        }
        s32 d = (s32)Power(10.0f, 2.0f);
        for (s32 k = 2; k >= 0; k--) {
            *out++ = D_00275940[e / d];
            e = (e % d) * 10;
        }
    }
    return out - buf;
}


void FormatFloatArg(FormatSpec* spec, OutputBuffer* ctx, double value)
{
    char buf[0x1C0];
    char sign[16];
    char padc[16];
    s32 zeros = 0;
    s32 left;
    s32 lead;
    s32 n;
    s32 len;
    s32 slen;
    s32 width;
    s32 total;
    s32 neg;
    if (spec->prec == 0 && spec->noprec == 0) {
        spec->prec = 6;
    } else if (spec->noprec != 0 && spec->conv == 0x67) {
        spec->prec = 1;
    }
    neg = value < 0.0;
    if (neg) value = 0.0 - value;
    sign[0] = 0;
    if (neg) __builtin_strcpy(sign, "-");
    else if (spec->plus) __builtin_strcpy(sign, "+");
    else if (spec->space) __builtin_strcpy(sign, " ");
    slen = GetStringLength(sign);
    len = FormatFloatDigits(buf, 0x1B5, spec, value);
    buf[len] = 0;
    if (spec->upper) UppercaseString(buf);
    width = spec->width;
    total = slen + len;
    lead = 0;
    left = 0;
    if (total < width) {
        s32 pad = width - total;
        if (spec->left) left = pad;
        else if (spec->zero && len != 0) zeros = pad;
        else lead = pad;
    }
    padc[0] = ' ';
    n = lead;
    while (n-- > 0) {
        if (AppendToOutputBuffer(ctx, padc, 1) != 1) break;
    }
    n = zeros;
    AppendToOutputBuffer(ctx, sign, slen);
    padc[0] = '0';
    while (n-- > 0) {
        if (AppendToOutputBuffer(ctx, padc, 1) != 1) break;
    }
    AppendToOutputBuffer(ctx, buf, len);
    n = left;
    padc[0] = ' ';
    while (n-- > 0) {
        if (AppendToOutputBuffer(ctx, padc, 1) != 1) break;
    }
}


void FormatConversionArg(FormatSpec* sp, OutputBuffer* c, u8** va, const char* fmt, s32 len) {
    u64 v;
    switch (sp->conv) {
    case '%':
        AppendToOutputBuffer(c, (const char*)&sp->conv, 1);
        return;
    case 'c': {
        signed char buf[16];
        u8* p = *va;
        *va = p + 8;
        s32 ch = *(s8*)p;
        buf[0] = ch;
        AppendToOutputBuffer(c, (const char*)buf, 1);
        return;
    }
    case 's': {
        u8* p = *va;
        *va = p + 8;
        FormatStringArg(sp, c, *(const char**)p);
        return;
    }
    case 'p':
        sp->prec = 8;
        sp->conv = 'x';
        sp->length = 0;
    case 'b': case 'd': case 'i': case 'o': case 'u': case 'x':
        switch (sp->length) {
        case 0: case 1: { u8* p = *va; *va = p + 8; v = *(u32*)p; break; }
        case 2: { u8* p = *va; *va = p + 8; v = *(u64*)p; break; }
        }
        FormatIntegerArg(sp, c, v);
        return;
    case 'e': case 'f': case 'g':
        if (sp->f24 != 0) {
            const char* s4 = "
";
            u8* a = *va;
            const char* s8 = ",
";
            const char* s7 = "{ ";
            *va = a + 8;
            const char* s5 = ", ";
            const char* s6 = " }";
            f32* fp = *(f32**)a;
            if (sp->f28 >= 2) {
                AppendToOutputBuffer(c, s4, GetStringLength(s4));
            }
            for (s32 i = 0; i < sp->f28; ) {
                s32 next;
                if (i != 0) {
                    AppendToOutputBuffer(c, s8, GetStringLength(s8));
                }
                next = i + 1;
                AppendToOutputBuffer(c, s7, GetStringLength(s7));
                for (s32 j = 0; j < sp->f24; j++) {
                    if (j != 0) {
                        AppendToOutputBuffer(c, s5, GetStringLength(s5));
                    }
                    FormatFloatArg(sp, c, func_001FD868(*fp++));
                }
                AppendToOutputBuffer(c, s6, GetStringLength(s6));
                i = next;
            }
            if (sp->f28 >= 2) {
                AppendToOutputBuffer(c, s4, GetStringLength(s4));
            }
        } else {
            u8* p = *va;
            *va = p + 8;
            FormatFloatArg(sp, c, *(s64*)p);
        }
        return;
    case 'n':
        switch (sp->length) {
        case 0: { u8* p = *va; *va = p + 8; **(s32**)p = c->count; break; }
        case 1: { u8* p = *va; *va = p + 8; s16* q = *(s16**)p; s32 n = c->count; *q = n; break; }
        case 2: { u8* p = *va; *va = p + 8; **(s64**)p = c->count; break; }
        }
        return;
    default:
        AppendToOutputBuffer(c, fmt, len);
        return;
    }
}


s32 FormatToOutputBuffer(OutputBuffer* ctx, const char* fmt, void* a2)
{
    FormatFrame loc;
    const char* s1 = fmt;

    loc.va = a2;
    if (*s1 != 0) {
        do {
            char* s2 = FindCharInString(s1, '%');
            s32 n = (s32)s2 - (s32)s1;
            if (s2 == 0) {
                n = GetStringLength(s1);
                s2 = (char*)((s32)s1 + n);
            }
            if (n != 0) {
                if (AppendToOutputBuffer(ctx, s1, n) < n) {
                    break;
                }
                s1 = s2;
            }
            if (*s1 == '%') {
                s32 n2 = ParseFormatSpec(s1, &loc.spec, (void*)&loc.va);
                FormatConversionArg(&loc.spec, ctx, (void*)&loc.va, s1, n2);
                s1 = s1 + n2;
            }
        } while (*s1 != 0);
    }
    FlushOutputBuffer(ctx);
    return ctx->count;
}

s32 PrintFormattedVa(const char* fmt, void* ap)
{
    OutputBufferStorage buf;
    InitOutputBuffer(&buf, -1);
    s32 n = FormatToOutputBuffer(&buf, fmt, ap);
    DestroyOutputBuffer(&buf, 2);
    return n;
}

s32 PrintFormatted(void* self, ...)
{
    void* ap = (char*)__builtin_next_arg(self) - 56;
    return PrintFormattedVa(self, ap);
}

s32 FormatToStringVa(char* dst, const char* fmt, void* ap)
{
    OutputBufferStorage buf;
    InitStringOutputBuffer(&buf, dst, 0);
    s32 n = FormatToOutputBuffer(&buf, fmt, ap);
    dst += n;
    *dst = 0;
    DestroyOutputBuffer(&buf, 2);
    return n;
}

s32 FormatToString(char* dst, const char* fmt, ...)
{
    void* ap = (char*)__builtin_next_arg(fmt) - 48;
    return FormatToStringVa(dst, fmt, ap);
}

s32 FormatToStringBoundedVa(char* dst, s32 cap, s32 a, s32 b)
{
    u8 buf[0x420];
    s32 n;

    InitStringOutputBuffer(buf, dst, cap);
    n = FormatToOutputBuffer(buf, a, b);
    if (n >= cap) {
        n = -1;
        dst[cap - 1] = 0;
    } else {
        dst[n] = 0;
    }
    DestroyOutputBuffer(buf, 2);
    return n;
}

LINKER_REMNANT(func_001E20B0);

s32 FormatToStringBounded(char* dst, s32 cap, const char* fmt, ...)
{
    void* ap = (char*)__builtin_next_arg(fmt) - 40;
    return FormatToStringBoundedVa(dst, cap, fmt, ap);
}

LINKER_REMNANT(func_001E20F8);

s32 GetStringLength(const char* s) { s32 length = 0; while (*s) { s++; length++; } return length; }

void* CopyString(void* dst, void* src)
{
    s32 n = GetStringLength(src);
    CopyMemory(dst, src, n + 1);
    return dst;
}

void* AppendString(void* dst, void* src)
{
    s32 len = GetStringLength(dst);
    s32 n = GetStringLength(src);
    CopyMemory((u8*)dst + len, src, n + 1);
    return dst;
}

char* FindCharInString(char* s, s32 c)
{
    while (*s != 0) {
        if ((s8)*s == c) {
            return s;
        }
        s++;
    }
    return 0;
}

LINKER_REMNANT(func_001E2210);

void UppercaseString(s8* p)
{
    while (*p != 0) {
        s32 c = *p;
        s32 r = c;
        if (g_charClassFlags[c] & 2) {
            r = c - 0x20;
        }
        *p = r;
        p++;
    }
}

void CreateLockSemaphore(void* a, void* b)
{
    SemaphoreParams tmp;

    FillMemory(&tmp, 0, 0x18);
    tmp.initCount = (s32)a;
    tmp.maxCount = (s32)b;
    NewSemaphore(&tmp);
}

LINKER_REMNANT(func_001E22B8);

void InitRecursiveLock(RecursiveLock* self)
{
    self->last = -1;
    self->sema = (void*)CreateLockSemaphore(1, 1);
}

void EnterRecursiveLock(RecursiveLock* self)
{
    s32 key = GetCurrentThreadId();
    if (key != self->last) {
        (void)AwaitSemaphore(self->sema);
        self->last = key;
        self->count = 1;
    } else {
        self->count++;
    }
}

void LeaveRecursiveLock(RecursiveLock* self)
{
    if (--self->count == 0) {
        self->last = -1;
        PostSemaphore(self->sema);
    }
}

LINKER_REMNANT(func_001E2390);

void CreateRenderThread(void)
{
    ThreadParams l;

    g_mainAndRenderThreads.main = GetCurrentThreadId();
    SetThreadPriority(g_mainAndRenderThreads.main, 4);
    (void)FillMemory(&l, 0, sizeof(l));
    l.stackSize = 0x20000;
    l.stack = g_renderThreadStack;
    l.priority = 2;
    l.gp = D_002832F0;
    l.entry = RunRenderThread;
    g_mainAndRenderThreads.render = MakeThread(&l);
}

void* GetOnOffObjectBlock(void* self) { return self ? (u8*)self + 0x2F0 : (void*)D_00275980; }

INCLUDE_ASM(func_001E2438);

void InitOnOffObject(OnOffObject* self)
{
    InitPlacedObject(self);
    self->block2F0 = *(Block63*)D_00275980;
    self->f428 = 2.0f;
    self->f42C = 1.0f;
    self->flags = (self->flags & 0xFFFFFCFFFFFFFFFFULL) | 0x10000000000ULL;
    self->f420 = 2.0f;
    self->f424 = 1.0f;
    self->f430 = -1;
    self->quad450 = *(Quad63*)D_00275A10;
    {
        u8* src = (u8*)D_00275A20;
        self->pack460 = *(Pack63*)src;
    }
    self->f398 = -1;
}

void UnregisterOnOffObject(OnOffObject* self)
{
    UnregisterPlacedObject(self);
    SetOnOffObjectState(self, 0);
    RemoveQueuedCalls(self->world, 2, 0, self, -1, 0);
}

void LoadOnOffObject(OnOffObject* self, void* a1)
{
    ReadBufferedRotation3(a1, &self->rot);
    ReadBufferedVector3(a1, &self->pos);
    const Desc01* vt = self->desc;
    if (vt->m12 != 0) {
        vt->m12(self);
    }
    ReadMeshTables(a1, (u8*)self + 0x2D4, (u8*)self + 0x2D8, (u8*)self + 0x2DC, (u8*)self + 0x2E0);
    s32 idx = ReadBufferedS8(a1);
    if (idx != -1) {
        Arr63* o = (Arr63*)CreatePathCurve(idx);
        self->obj = o;
        void** curveTable = *(void***)o;
        if (curveTable[0] != 0) {
            ((void (*)(void*, void*))curveTable[0])(o, a1);
        }
        Arr63* p = self->obj;
        self->f3F0 = p->data[p->count - 1];
    } else {
        ReadBufferedRotation3(a1, (u8*)self + 0x3B0);
        ReadBufferedVector3(a1, (u8*)self + 0x3E0);
        *(s32*)&self->f3F0 = 0;
    }
    self->i414 = (self->obj != 0) ? 7 : 5;
    ReadPropertyRecords(self, a1);
}

void StartOnOffObject(OnOffObject* self)
{
    StartPlacedObject(self);
}

void SetOnOffObjectState(void* selfv, s32 state)
{
    OnOffObject* self = (OnOffObject*)selfv;
    if (self->f394 == state) return;
    if (state != 0) {
        if (state != 1) {
            self->f394 = state;
            goto tail;
        }
        u32 base = (u32)g_camera;
        PushCameraController(base, self->f388 + 2, (void*)(base + 0x520), (s32)self->f2D0, self);
        TriggerScriptEvent(self, 2, 0, 0);
    } else {
        u32 base = (u32)g_camera;
        RemoveCameraControllers(base, 8, -1, 0, 0, self);
        TriggerScriptEvent(self, 3, 0, 0);
    }
    self->f394 = state;
tail:
    self->f39C = g_gameTime;
}

void SetOnOffObjectForcedState(void* selfv, s32 value)
{
    OnOffObject* self = (OnOffObject*)selfv;
    if (value == self->f398) return;
    self->f398 = value;
    UpdateOnOffObjectState(self, 0, 0);
}

void UpdateOnOffObjectState(OnOffObject* self) {
    FacePoint loc;
    void* p = GetActiveSwitchedCollider();
    if (p == 0) {
        return;
    }
    if (p != self->f2D0) {
        SetOnOffObjectState(self, 0);
        self->f2D0 = p;
    }
    s32 st;
    if (self->f398 == -1) {
        TransformPointBetweenFrames(0, self, (u8*)p + 0x140, &loc);
        s32 r = IsPointInsideFaceTree((TreeNode03*)self->f2E0, &loc);
        st = (0u < (u32)r);
    } else {
        st = self->f398;
    }
    if (self->f384 == 0 && p == (u8*)g_player && ((Player*)p)->f2220 == 2 &&
        g_camera->f224 == 0) {
        if (self->f398 == -1) {
            return;
        }
    }
    SetOnOffObjectState(self, st);
}

void UpdateOnOffObject(OnOffObject* self)
{
    UpdatePlacedObject(self);
    if (self->f398 != 0) {
        AppendQueuedCall(self->world, (void*)(void (*)(OnOffObject*))UpdateOnOffObjectState, self, 0, 0);
    }
}

void DrawOnOffObject(void)
{
    DrawPlacedObject();
}

void SetOnOffObjectFrozen(OnOffObject* self, void* p)
{
    SetPlacedObjectFrozen(self, p);
    if (p != 0) {
        SetOnOffObjectState(self, 0);
    }
}

void SetOnOffObjectBlockValue(OnOffObject* self, f32 value) { *(f32*)(self->block2F0.d + 0x74) = value; *(f32*)(self->block2F0.d + 0x78) = 1.0f; *(f32*)(self->block2F0.d + 0x70) = value; }

INCLUDE_ASM(func_001E2A00);

INCLUDE_ASM(func_001E2BF0);

// The five quadwords func_00143418 gives for a camera and its target: the placement.
struct CameraPlacement { Vec02 q[5]; };
void BlendOnOffCameraPoint(void* block, CameraPlacement* eye, Vec02* out, OnOffObject* object);

INCLUDE_ASM(func_001E2E68);

void DeactivateOnOffCameraController(OnOffCameraController* self)
{
    CameraFovSource* s = (CameraFovSource*)self->ptr;
    if (s != 0) {
        if (s->f438 != 0.0f) {
            Camera* g = g_camera;
            g->f1C8 = s->f43C;
        }
    }
    self->ptr = 0;
}

void NoteOnOffCameraControllerPushed(OnOffCameraController* self, s32 arg)
{
}

void NoteOnOffCameraControllerRemoved(OnOffCameraController* self, s32 arg) {}

f32 ArctangentOfRatio(f32 y, f32 x);

void func_001E30E8(OnOffCameraController* self, CameraPlacement* eye)
{
    Vec02 blended;
    Vec02 here;
    Vec02 delta;
    OnOffObject* object = (OnOffObject*)self->ptr;
    if (!object)
        return;
    if (!object->obj && !object->f38C)
        return;
    BlendOnOffCameraPoint(GetOnOffObjectBlock(object), eye, &blended, 0);
    TransformPointBetweenFrames(0, object, &blended, (FacePoint*)&here);
    if (object->obj) {
        typedef void (*Fn)(f32, Arr63*, Vec02*, s32, s32, s32, s32, f32*);
        Fn fn = *(Fn*)(*(u8**)object->obj + 0x30);
        if (!fn)
            return;
        fn(object->angle3A0, object->obj, &here, 0, 0, 0, 0, &object->angle3A0);
    } else {
        Vu0::Q(delta) = Vu0::Sub(Vu0::Q(here), Vu0::Q(object->v400));
        f32 angle = ArctangentOfRatio(delta.y, delta.x);
        if (angle < 0.0f)
            angle += 6.2831855f;
        object->angle3A0 = angle * object->f410;
    }
}

INCLUDE_ASM(func_001E31F0);

INCLUDE_ASM(func_001E4578);

f32 GetSpanCandidateValue(void* a0, void* a1, void* a2, SpanCandidate* a3)
{
    return a3->value;
}

INCLUDE_RODATA(D_0024E5F0);
INCLUDE_ASM(func_001E4888);

INCLUDE_ASM(func_001E4C48);

ASM_FUNC(func_001E4DC0);

WorldLoadRequest::WorldLoadRequest()
{
    key = 0;
    flags = 0;
    fC = f8 = -1;
    FillMemory(&current, 0, 0x20);
}

WorldLoadRequest g_worldLoadRequest;

void QueueWorldLoad(WorldLoadRequest* self, WorldKeyBlock* key, s32 a2, s32 a3, s32 flags)
{
    if (self->state == 0) {
        self->state = 1;
        self->key = key;
        self->f8 = a2;
        self->fC = a3;
        self->flags = flags;
    }
}

void RunPendingWorldLoad(WorldLoadRequest* self)
{
    KeyId key;
    WorldKeyBlock blob;
    LoadProgress o30;
    U32P w60, w70, w80, w90;
    OwnedStream sub;
    SetScreenOwner(2);
    if (self->key != 0) {
        ClearKeyId(&key);
        blob = *self->key;
        self->key = 0;
        key.second = blob.w[1] ^ blob.w[7];
        key.first = blob.w[0] ^ blob.w[5];
        if (key.second == 0) goto end;
        {
            WorldKeyBlock* s2 = &self->current;
            s32 ne = !SameWorldKey::Of(&blob, s2);
            w60.v = 0x3F00;
            w70.v = 0x3F3F3F;
            w80.v = 0x3F3F;
            w90.v = 0x3F;
            InitLoadProgress(&o30, &w60, &w70, &w80, &w90);
            InitBufferedStream(&sub, 0x340C00, D_002C3B00, 6);
            sub.SetOwner(&o30);
            if (sub.owner != 0) BeginLoadProgress(sub.owner);
            if (OpenBufferedSectorStreamRange(&sub, &key) == 0) {
                DestroyBufferedStream(&sub, 2);
                goto end;
            }
            ResetWorldSubsystems(g_currentWorld);
            g_currentWorld = 0;
            ReadBufferedBlockHeader(ne, &sub);
            SetGameClockTime(((u8*)&g_gameClock), 0.0f);
            SetPadSelectFlags(0x80);
            self->current = blob;
            SetCurrentLevelEntry(s2, self->flags);
            g_currentWorld = CreateTypedRecord(0x6C, 0, 0, 3, -1);
            SetVolumeChannelFactor(0xA, 0, 0.0f);
            g_currentWorld->desc->m0A(g_currentWorld, &sub);
            CloseBufferedStream(&sub);
            if (sub.owner != 0) EndLoadProgress(sub.owner);
            if (g_saveData->f19EC & 0x100) {
                GameProgress* c = g_memoryCard.image;
                if (c != 0 && (c->f19D8 != g_saveData->f19D8 || c->f19DC != g_saveData->f19DC))
                    StartMemoryCardSave(&g_memoryCard);
            }
            DestroyBufferedStream(&sub, 2);
        }
    }
    ResetCamera((*(s32*)&g_camera), 1);
    UpdateSoundEmitters();
    SetVolumeChannelFactor(0xA, 0, 1.0f);
    FindOrActivateSwitchedCollider(g_currentWorld, self->f8, self->fC);
    NotifyScatterControllerLoaded(g_scatterController);
    ResetCounter(D_002623D8);
    RestoreSelectionCaptionCamera(&D_0026FA90);
    UpdateWorldContacts(g_currentWorld, 0);
    UpdateCamera((*(s32*)&g_camera), 0, g_frameStep);
    if (self->flags & 0x10) D_0026C6C8.vt->m14(&D_0026C6C8);
    SetGameClockScale(1.0f);
end:
    ResetVolumeChannelFactors();
    SetVolumeChannelFactor(1, 1, g_currentWorld->f1D7C);
    ClearScreenOwner(2);
    self->state = 0;
}

void RequestWorldLoadByMode(s32 mode)
{
    s32 n;
    SetIopVolumeChannel8(0.0f);
    switch (mode) {
    case 0:
        n = 0;
        break;
    case 1:
        StartScreenFadeFromFlagTable(&g_flagTable);
        return;
    case 2:
        n = 2;
        break;
    case 3:
        n = 4;
        break;
    }
    QueueWorldLoad(&g_worldLoadRequest, &g_worldLoadRequest.current, -1, -1, n);
}


