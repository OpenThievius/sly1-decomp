// SPDX-License-Identifier: AGPL-3.0-or-later
// The file from 0x18B580 to 0x18D410: the background job (include/background_job.h) and the
// memory card (include/memory_card.h): its states, its save files and the calls to the card.
// Its name is ours, after the card.
#include "common.h"
#include "asm_func.h"
#include "memory_card.h"
#include "background_job.h"
#include "game_clock.h"
#include "game_progress.h"
#include "screen_element.h"
#include "buffered_stream.h"
#include "key_id.h"
#include "key_record.h"

// The memory card: the background job its calls run on (a thread of its own), the card object
// and its states, the save files (the directory, its icon and header, the three slots) and the
// wrappers of the card library's calls, each finished through FinishMemoryCardCall.

MemoryCard D_00264A40 = {};
BackgroundJob D_00269990 = {0};

extern f32 D_00261868[];
extern u8 D_00275960[];
extern const u32 D_00248470[8];
extern u8 D_002BE540[];
extern u8 D_002BE9C0[];

void func_002093F0(void);
void* func_001F5C0C(void* p, s32 v, s32 n);
s32 func_001E2268(s32 a, s32 b);
s32 func_001F6B60(void* a);
void func_001F6B40(void* a);
s32 func_001F6A30();
void func_001F6A50(s32 thread, s32 b);
s32 func_00209B80(void* a0, s32* a1, s32* a2);
void func_00194D30(T217D_6D0* self, s32 a, s32 b);
s32 func_001E2100(void* p);
void* func_001E2138(void* dst, void* src);
s32 func_001E1FD0(char* dst, const char* fmt, ...);
s32 func_001407A0(void* p);
void func_001A7E90(GameProgress* ctx);
void func_001605E8(void* self);
s32 func_00160650(void* img);
void func_001B5C40(void* p, void* q);
void* func_0020A078(void*, void*, const char*);
s32 func_00209E48(void* a, void* b, const void* c, s32 d, s32 e, void* f);
s32 func_00209CB8(void* a, void* b, s32* c, s32* d, s32* e);
void* func_00209FA8(s32, s32);
void* func_002096E8(s32, s32, void*);
void* func_002095B0(s32, s32, void*, void*);
void* func_00209720(void*);
s32 func_00209870(void* a, void* b, void* c);
void* func_00209990(void*, void*, void*);
void func_0018D410(void* p);
void func_0018D608(void);
u8* func_0018D658(s32 size);
void func_0018D6F0(void);
s32 func_00137290(BufferedStream* o, s32 a, u8* b, s32 c);
s32 func_001373B0(BufferedStream* o, KeyId* p);
void func_00137A60(BufferedStream* o, s32 n, u8* d);
void func_001373D0(BufferedStream* o);
void func_001372E0(BufferedStream* o, s32 f);

void func_0018B5C0(BackgroundJob* self);
void func_0018B670(BackgroundJob* job, void* fn, void* arg);
void func_0018B720(BackgroundJob* job);
s32 func_0018B770(void* p);
s32 func_0018B910(s32 value);
s32 func_0018B930(s32 value);
s32 func_0018B988(s32 a, s32 b);
s32 func_0018BC90(void* a0, void* a1, s32* a2);
s32 func_0018BD00(s32 value, void* first, s32 second);
void func_0018BD58(MemoryCard* self, s32 a, s32 b);
s32 func_0018BFA8(void* lhs, void* rhs);
void func_0018C028(MemoryCard* self, s32 value);
void func_0018C178(MemoryCard* self, s32 value);
s32 func_0018C420(void* self);
s32 func_0018C638(MemoryCard* self);
s32 func_0018C888(void* a, u8* b, s32 c, u8* d, s32* e);
s32 func_0018C9C0(void* a0, void* a1, void* a2);
s32 func_0018CA10(void* owner, void* a1, void* a2);
s32 func_0018CBF8(void* self, void* b);
s32 func_0018CC20(void* self, s32 a1, void* key, s32 a3);
s32 func_0018CDD8(void* a0, void* a1, GameProgress* out, void* info);
s32 func_0018CFC0(void* owner, void* name, void* state);
s32 func_0018D028(void* a0, void* a1, void* a2, void* a3);
s32 func_0018D0A0(MemoryCard* o);
s32 func_0018D168(void* a0, s32* a1);
s32 func_0018D1F8(void* p);
s32 func_0018D228(void* p, void* value);
s32 func_0018D268(void* p, void* a1, void* a2, void* a3);
s32 func_0018D2B0(void* unused, void* value);
s32 func_0018D2E8(void* a0, void* a1, void* a2, void* a3, void* a4);
s32 func_0018D328(void* unused, void* a1, void* a2, void* a3, void* a4);
s32 func_0018D368(void* self, void* code, void* data, s32 version);

void func_0018B580(void)
{
	InitMemoryCardClient();
	InitBackgroundJob(&g_backgroundJob);
	InitMemoryCard(&g_memoryCard, 0, 0);
}

void func_0018B5C0(BackgroundJob* self)
{
    s32 r = CreateLockSemaphore(1, 1);
    self->semaphoreId = r; self->thread = -1; self->result = 0x22;
}

void func_0018B600()
{
    AwaitSemaphore(g_backgroundJob.semaphore);
    BackgroundJob* o = &g_backgroundJob;
    s32 r = o->job(o->arg);
    o->result = r;
    *(s32*)D_00275960 = -1;
    o->thread = -1;
    o->arg = 0;
    o->job = 0;
    PostSemaphore(g_backgroundJob.semaphore);
    EndOwnThread();
}

// The parameters of the thread a job runs on (func_001F6A10 creates it from them).
struct ThreadParams { s32 f00; void (*entry)(); void* stack; s32 stackSize; void* gp; s32 priority; u8 pad18[0x18]; };

extern u8 D_002BEA10[];
extern u8 D_002832F0[];
s32 func_001F6A10(ThreadParams* param);
void func_001F6A20(s32 thread, void* arg);

void func_0018B670(BackgroundJob* job, void* fn, void* arg)
{
    ThreadParams param;
    WaitForBackgroundJob(job);
    job->job = (s32 (*)(void*))fn;
    job->arg = arg;
    job->result = 0x20;
    FillMemory(&param, 0, 0x30);
    param.entry = RunBackgroundJob;
    param.stack = D_002BEA10;
    param.stackSize = 0x4000;
    param.gp = D_002832F0;
    param.priority = 3;
    job->thread = MakeThread(&param);
    *(s32*)D_00275960 = job->thread;
    RunThread(job->thread, job);
}

void func_0018B720(BackgroundJob* job)
{
    if (IsBackgroundJobRunning(&g_backgroundJob)) {
        SetThreadPriority(job->thread, 1);
    }
    AwaitSemaphore(job->semaphore);
    PostSemaphore(job->semaphore);
}

s32 func_0018B770(void* p)
{
	return *(s32*)((char*)p + 4) != -1;
}

// A directory entry as the card returns it (0x40 bytes): two times, the size, the attributes
// and the name at 0x20 (func_0018C888 reads 0x480 bytes of them).
struct CardDirEntry {
    u8 pad0[1];
    u8 b1;
    u8 b2;
    u8 b3;
    u8 b4;
    u8 b5;
    u16 h6;
    u8 pad3[1];
    u8 b9;
    u8 bA;
    u8 bB;
    u8 bC;
    u8 bD;
    u16 hE;
    s32 f10;
    u16 f14;
    u8 pad2[0x20 - 0x16];
    u8 sub20[0x10];
};

// What ConvertMemoryCardDirEntry makes of one (0x5C bytes): the name, the size at 0x44, the
// flags at 0x48 and the two times.
struct CardFileInfo {
    u8 pad0[0x44];
    s32 f44;                // 0x44: the size
    union {
        s32 flags;          // 0x48: the attributes, rearranged
        struct {
            u8 pad48[2];
            u8 f4A;         // 0x4A
            u8 f4B;         // 0x4B
        };
    };
    u16 f4C;
    u8 f4E;
    u8 f4F;
    u8 f50;
    u8 pad3[1];
    u8 f52;
    u8 f53;
    u16 f54;
    u8 f56;
    u8 f57;
    u8 f58;
};

void func_0018B780(CardDirEntry* s, CardFileInfo* d)
{
    FillMemory(d, 0, 0x5C);
    CopyString(d, s->sub20);
    d->f44 = s->f10;
    if (s->f14 & 0x1) {
        d->flags |= 0x1;
    }
    if (s->f14 & 0x2) {
        d->flags |= 0x2;
    }
    if (s->f14 & 0x4) {
        d->flags |= 0x4;
    }
    if (s->f14 & 0x8) {
        d->flags |= 0x8;
    }
    if (s->f14 & 0x20) {
        d->flags |= 0x10;
    }
    if (s->f14 & 0x80) {
        d->flags |= 0x20;
    }
    if (s->f14 & 0x800) {
        d->flags |= 0x40;
    }
    if (s->f14 & 0x1000) {
        d->flags |= 0x80;
    }
    d->f4A = s->b5;
    d->f4B = s->b4;
    d->f4C = s->h6;
    d->f4E = s->b3;
    d->f4F = s->b2;
    d->f50 = s->b1;
    d->f52 = s->bD;
    d->f53 = s->bC;
    d->f54 = s->hE;
    d->f56 = s->bB;
    d->f57 = s->bA;
    d->f58 = s->b9;
}

s32 func_0018B910(s32 value)
{
	if (value == 0) return 29;
	if (value > 0) return 30;
	return 31;
}

// Two words a card call gives back (SyncCardRequest's command and result, a handle and a count).
struct CardCallResult { s32 a; s32 b; };

s32 func_0018B930(s32 value)
{
    switch (value) {
    case 0: return 32;
    case 1: return 33;
    case -1: return 34;
    default: return 31;
    }
}

struct ErrorCodeTail
{
    static s32 Get(s32 b, s32 v, s32 lim)
    {
        s32 r = v;
        if (b >= lim) r = 31;
        return r;
    }
};

s32 func_0018B988(s32 a, s32 b)
{
    s32 r;
    switch (a) {
    case 1:
        switch (b) {
        case 0: return 0;
        case -1: return 9;
        case -2: return 10;
        case -5: return 11;
        }
        return ErrorCodeTail::Get(b, 11, -9);
    case 2:
        switch (b) {
        case -2: return 12;
        case -3: return 1;
        case -4: return 13;
        case -5: return 6;
        case -7: return 25;
        }
        if (b >= 0) return 0;
        return ErrorCodeTail::Get(b, 11, -9);
    case 3:
        switch (b) {
        case 0: return 0;
        case -2: return 12;
        case -4: return 16;
        }
        return ErrorCodeTail::Get(b, 11, -9);
    case 4:
        switch (b) {
        case -2: return 12;
        case -4: return 16;
        }
        if (b >= 0) return 0;
        return ErrorCodeTail::Get(b, 11, -9);
    case 5:
        switch (b) {
        case -2: return 12;
        case -4: return 16;
        case -5: return 17;
        }
        if (b >= 0) return 0;
        return ErrorCodeTail::Get(b, 11, -9);
    case 6:
        switch (b) {
        case -2: return 12;
        case -3: return 1;
        case -4: return 16;
        case -5: return 18;
        case -8: return 26;
        }
        if (b >= 0) return 0;
        return ErrorCodeTail::Get(b, 11, -9);
    case 10:
        switch (b) {
        case 0: return 0;
        case -2: return 12;
        case -4: return 16;
        }
        return ErrorCodeTail::Get(b, 11, -9);
    case 11:
        switch (b) {
        case 0: return 0;
        case -2: return 12;
        case -3: return 1;
        case -4: return 24;
        }
        return ErrorCodeTail::Get(b, 11, -9);
    case 12:
        switch (b) {
        case 0: return 0;
        case -2: return 12;
        case -4: return 21;
        }
        return ErrorCodeTail::Get(b, 11, -9);
    case 13:
        switch (b) {
        case -2: return 12;
        case -4: return 21;
        }
        if (b >= 0) return 0;
        return ErrorCodeTail::Get(b, 11, -9);
    case 14:
        switch (b) {
        case 0: return 0;
        case -2: return 12;
        case -4: return 22;
        }
        return ErrorCodeTail::Get(b, 11, -9);
    case 15:
        switch (b) {
        case 0: return 0;
        case -2: return 12;
        case -4: return 14;
        case -5: return 19;
        case -6: return 23;
        }
        return ErrorCodeTail::Get(b, 11, -9);
    case 16:
        r = 0;
        if (b != 0) return ErrorCodeTail::Get(b, 4, 0);
        break;
    case 17:
        r = 0;
        if (b != 0) return ErrorCodeTail::Get(b, 5, 0);
        break;
    case 18:
        switch (b) {
        case -2: return 12;
        }
        if (b >= 0) return 0;
        return ErrorCodeTail::Get(b, 11, -9);
    case 19:
        switch (b) {
        case 0: return 0;
        case -2: return 12;
        case -4: return 22;
        }
        return ErrorCodeTail::Get(b, 11, -9);
    case 20:
        switch (b) {
        case 0: return 0;
        case -403: return 35;
        }
        return 31;
    case 21:
        if (b >= 0) return 0;
        if ((u32)(b + 100) < 100) return 31;
        return ErrorCodeTail::Get(b, 30, -99);
    default:
        r = 31;
        break;
    }
    return r;
}

s32 func_0018BC90(void* a0, void* a1, s32* a2)
{
    CardCallResult t;
    s32 r = ClassifyMemoryCardSyncResult(SyncCardRequest(a0, &t.a, &t.b));
    if (a2) {
        *a2 = t.b;
    }
    if (r == 0x21) {
        r = MapMemoryCardErrorCode((s32)a1, t.b);
    }
    return r;
}

s32 func_0018BD00(s32 value, void* first, s32 second)
{
	s32 result = ClassifyMemoryCardCallResult(value);
	if (result == 29)
		result = SyncMemoryCardResult(0, first, (s32*)second);
	return result;
}

void func_0018BD58(MemoryCard* self, s32 a, s32 b)
{
    FillMemory(self, 0, 0x4F50);
    self->state = -1;
    self->targetState = 0;
    SetMemoryCardDisplayMode(self, 0);
    self->port = (void*)a;
    self->slot = (void*)b;
    self->i4F48 = 0;
    self->i4F44 = 0;
}

void func_0018BDC8(MemoryCard* self)
{
    if (IsBackgroundJobRunning(&g_backgroundJob) != 0) return;
    if (self->state == self->targetState) {
        if (self->nextPollTime <= g_elapsedTime[0])
            StartBackgroundJob(&g_backgroundJob, (void*)PollMemoryCard, self);
    } else {
        SetMemoryCardState(self, self->targetState);
    }
    if (IsBackgroundJobRunning(&g_backgroundJob) != 0) return;
    if (self->displayMode == 1 && g_elapsedTime[0] - self->stateTime >= 0.3f) {
        if (self->i4F44 != 0) {
            if (self->state != 5) SetPauseMenuLayerPage(&g_pauseMenuElement, 1, 0x15);
        } else if (g_pauseMenuElement.open != 0 && g_pauseMenuElement.want[0] == 0x11) {
            if (self->state != 5) SetPauseMenuLayerPage(&g_pauseMenuElement, 1, 0x20);
        } else {
            switch (self->state) {
            case 1: SetPauseMenuLayerPage(&g_pauseMenuElement, 1, 3); break;
            case 2: SetPauseMenuLayerPage(&g_pauseMenuElement, 1, 4); break;
            case 3: SetPauseMenuLayerPage(&g_pauseMenuElement, 1, 7); break;
            case 4: SetPauseMenuLayerPage(&g_pauseMenuElement, 1, 10); break;
            }
        }
    }
}

s32 func_0018BFA8(void* lhs, void* rhs)
{
	s32 difference = *(u16*)((char*)lhs + 0x54) - *(u16*)((char*)rhs + 0x54);
	if (difference) return difference;
	difference = *(u8*)((char*)lhs + 0x52) - *(u8*)((char*)rhs + 0x52);
	if (difference) return difference;
	difference = *(u8*)((char*)lhs + 0x53) - *(u8*)((char*)rhs + 0x53);
	if (difference) return difference;
	difference = *(u8*)((char*)lhs + 0x56) - *(u8*)((char*)rhs + 0x56);
	if (difference) return difference;
	difference = *(u8*)((char*)lhs + 0x57) - *(u8*)((char*)rhs + 0x57);
	if (difference) return difference;
	return *(u8*)((char*)lhs + 0x58) - *(u8*)((char*)rhs + 0x58);
}

void func_0018C028(MemoryCard* self, s32 value)
{
    s32 old = self->state;
    s32 n;
    if (value == old) return;
    if (old == 5) self->f4F48 = 0;
    if (value == 3) goto c420;
    if (value < 4) goto small;
    if (value == 5) goto loop;
    goto store;
small:
    if (value >= 2) goto store;
    if (value < 0) goto store;
    StartBackgroundJob(&g_backgroundJob, (void*)PollMemoryCard, self);
    goto store;
c420:
    StartBackgroundJob(&g_backgroundJob, (void*)LoadMemoryCardSaveSlots, self);
    goto store;
loop: {
    CardSlot* e;
    CardSlot* p = (CardSlot*)((u8*)self + 0x1A30);
    e = (CardSlot*)(self->f4F48 = (u8*)self + 0x30);
    n = 2;
    do {
        if (e->f0C != 0.0f) {
            s32 r = CompareMemoryCardEntryTimes((u8*)self->f4F48 + 0x1A00, p);
            if (r < 0) self->f4F48 = e;
        } else {
            ResetGameProgress(e);
        }
        p = (CardSlot*)((u8*)p + 0x1A5C);
        e = (CardSlot*)((u8*)e + 0x1A5C);
    } while (--n >= 0);
}

store:
    self->state = value;
    self->stateTime = g_gameClock.elapsed;
}

void func_0018C178(MemoryCard* self, s32 value)
{
    if (value != self->displayMode) {
        if (value == 2) self->i4F44 = 0;
        self->displayMode = value;
        self->displayModeTime = g_elapsedTime[0];
    }
}

s32 func_0018C1A8(MemoryCard* self)
{
    s32 r = FormatMemoryCard(self);
    if (r != 0) {
        self->targetState = 2;
    } else {
        self->targetState = 3;
    }
    return r;
}

// The 16 bytes func_0018C1E8 hands func_001407A0: a KeyId and two words it leaves alone.
struct KeyIdSlot { s32 w0; s32 w4; s32 w8; s32 wC; };

s32 func_0018C1E8(KeyRecord* self)
{
    KeyIdSlot key;
    s32 flag;
    ClearKeyId(&key);
    if (self == 0) {
        flag = 0;
    } else {
        s32 x = self->wordB ^ self->maskB;
        key.w0 = self->wordA ^ self->maskA;
        key.w4 = x;
        flag = x != 0;
    }
    if (flag != 0) {
        return func_001407A0(&key);
    }
    return 0;
}

// The save files' names, in the order retail's .rodata holds them.
extern const char D_0024B340[8] = "/";
extern const char D_0024B348[24] = "/BASCUS-97198YAOTWTD!";
extern const char D_0024B360[48] = "/BASCUS-97198YAOTWTD!/BASCUS-97198YAOTWTD!";
extern const char D_0024B390[16] = "Sly Cooper";
extern const char D_0024B3A0[16] = "/%s/%s%d";
extern const char D_0024B3B0[24] = "BASCUS-97198YAOTWTD!";
extern const char D_0024B3C8[8] = "save";

s32 func_0018C250(MemoryCard* self)
{
    char name[0x50];
    s32 info[4];
    s32 r = FinishMemoryCardCall((s32)func_0020A078(self->port, self->slot, D_0024B340), (void*)0x12, (s32)info);
    if (r != 0) return r;
    s32 need = info[0] == 0 ? 2 : 1;
    s32 sz = GetKeyedDataSize((KeyRecord*)g_memoryCardIconKey);
    need += 5;
    need += (sz + 1023) / 1024;
    need += 0x15;
    if (self->freeBlocks < need) return 1;
    const char* dir = D_0024B348;
    r = CreateMemoryCardDirectory(self, (void*)dir);
    if (r == 0) {
        const char* title = D_0024B390;
        r = CreateMemoryCardFile(self, (void*)D_0024B360, (void*)title, 10);
        if (r == 0) {
            r = WriteMemoryCardSaveHeader(self, (void*)dir, (void*)title);
            if (r == 0) {
                r = WriteMemoryCardIcon(self, (void*)dir);
                if (r == 0) {
                    for (s32 i = 0; i < 3; i++) {
                        FormatToString(name, D_0024B3A0, D_0024B3B0, D_0024B3C8, i + 1);
                        r = WriteMemoryCardSlot(self, name, (u8*)self + 0x30 + i * 0x1A5C, (u8*)self + 0x1A30 + i * 0x1A5C);
                        if (r != 0) return r;
                    }
                    if (self->targetState < 5) self->targetState = 5;
                }
            }
        }
    }
    return r;
}

// A save file's name ("/%s/%s%d" and the like), built on the stack.
struct CardFileName {
    char s[0x50];
};

s32 func_0018C420(void* p) {
    MemoryCard* self = (MemoryCard*)p;
    CardFileName buf;
    s32 r;
    s32 n;
        s32 local50;
    s32 local54;

    r = FinishMemoryCardCall(ReadCardDirectory(self->port, self->slot, D_0024B348, 0, -1, 0), (void*)0xD, (s32)&local50);
    if (local50 <= 0) {
        GetMemoryCardFreeBytes(self, &local54);
        if (local54 <= 0xC3FF) {
            self->targetState = 4;
        }
        return 0xE;
    }
    n = 0;
    if (r == 0) {
        for (; r == 0 && n < 3; n++) {
            FormatToString((char*)&buf, D_0024B3A0, D_0024B3B0, D_0024B3C8, n + 1);
            (void)ReadMemoryCardSlotFile(self, &buf, &self->slots[n].data, self->slots[n].info);
        }
        if (r == 0 && self->targetState < 5) {
            self->targetState = 5;
        }
    }
    return r;
}

s32 func_0018C568(MemoryCard* self)
{
    if (self->image == 0) {
        return 0x2C;
    }
    *g_saveData = *self->image;
    ApplyPadPatternSetting(g_saveData);
    return 0;
}


s32 func_0018C638(MemoryCard* self)
{
    CardFileName buf;
    s32 n;

    if (self->p4F44 == 0) {
        return 0x2C;
    }
    ApplyPadPatternSetting(g_saveData);
    *(GameProgress*)self->p4F44 = *(GameProgress*)(*(u8**)&g_saveData);
    n = (s32)self->p4F44 - 0x30;
    n = n - (s32)self;
    n = n * 0x26FFD927;
    n = (n >> 2) + 1;
    FormatToString((char*)&buf, D_0024B3A0, D_0024B3B0, D_0024B3C8, n);
    return WriteMemoryCardSlotFile(self, &buf, self->p4F44);
}


s32 func_0018C770(MemoryCard* self)
{
    CardFileName buf;
    s32 f = self->i4F4C;
    s32 n;
    s32 g;

    if (f == 0) {
        return 0x2C;
    }
    n = f - 0x30;
    n = n - (s32)self;
    n = n * 0x26FFD927;
    n = (n >> 2) + 1;
    FormatToString((char*)&buf, D_0024B3A0, D_0024B3B0, D_0024B3C8, n);
    g = self->i4F4C;
    return WriteMemoryCardSlot(self, &buf, (void*)g, (void*)(g + 0x1A00));
}


void func_0018C7F8(MemoryCard* self)
{
    if (self->i4F44 != 0) {
        if ((g_saveData->f19EC & 0x100) == 0) {
            g_pauseMenuElement.stage = -1;
            SetPauseMenuLayerPage(&g_pauseMenuElement, 1, 0x14);
        } else {
            StartBackgroundJob(&g_backgroundJob, (void*)SaveGameToMemoryCardSlot, self);
            T217D_600* obj = &D_00273EB0;
            ((T217D_Word*)&obj->flag)->v = 0;
            obj->vt->m14(obj);
        }
    }
}


s32 func_0018C888(void* ctx, u8* b, s32 c, u8* d, s32* e)
{
    MemoryCard* a = (MemoryCard*)ctx;
    s32 flag;
    s32 r;
    u8* t;
    s32 i;
    u8* buf;
    if (c >= 0x13) {
        return 0x25;
    }
    if (b != 0) {
        if ((u32)GetStringLength(b) >= 0x41) {
            return 0xD;
        }
        CopyString(D_002BE9C0, b);
        flag = 0;
    } else {
        flag = 1;
        b = D_002BE9C0;
    }
    buf = D_002BE540;
    FillMemory(buf, 0, 0x480);
    r = FinishMemoryCardCall(ReadCardDirectory(a->port, a->slot, b, flag, c, buf), (void*)0xD, (s32)e);
    if (r != 0) {
        return r;
    }
    i = 0;
    if (*e > 0) {
        t = d;
        do {
            ConvertMemoryCardDirEntry((CardDirEntry*)buf, (CardFileInfo*)t);
            i++;
            t += 0x5C;
            buf += 0x40;
        } while (i < *e);
    }
    return 0;
}

s32 func_0018C9C0(void* a0, void* a1, void* a2)
{
	s32 temp;
	s32 result = ListMemoryCardDirectory(a0, (u8*)a1, 1, (u8*)a2, &temp);
	if (result != 0)
		return result;
	return temp == 1 ? 0 : 14;
}

LINKER_REMNANT(func_0018C9F8);

struct IconSysMagic {
    s32 w0;
    u8 b4;
};
struct IconFileName {
    u8 b[8];
};
struct IconSysHeader {
    s32 f000;
    u8 f004;
    s16 f006;
    u8 pad08[4];
    s32 f00C;
    s32 f010;
    s32 f014;
    s32 f018;
    u8 pad1C[4];
    s32 f020;
    s32 f024;
    s32 f028;
    u8 pad2C[4];
    s32 f030;
    s32 f034;
    s32 f038;
    u8 pad3C[4];
    s32 f040;
    s32 f044;
    s32 f048;
    u8 pad4C[4];
    s32 f050;
    f32 f054;
    f32 f058;
    u8 pad5C[4];
    f32 f060;
    f32 f064;
    f32 f068;
    u8 pad6C[4];
    f32 f070;
    f32 f074;
    f32 f078;
    u8 pad7C[4];
    f32 f080;
    f32 f084;
    f32 f088;
    u8 pad8C[4];
    f32 f090;
    s32 f094;
    f32 f098;
    u8 pad9C[4];
    f32 f0A0;
    f32 f0A4;
    f32 f0A8;
    u8 padAC[4];
    f32 f0B0;
    f32 f0B4;
    f32 f0B8;
    u8 padBC[4];
    u8 pad0C0[0x104 - 0xC0];
    IconFileName f104;
    u8 pad10C[0x144 - 0x10C];
    IconFileName f144;
    u8 pad14C[0x184 - 0x14C];
    IconFileName f184;
    u8 pad18C[0x3C4 - 0x18C];
};


// The header and icon files' names.
extern const IconSysMagic D_0024B3D0 = { 0x44325350, 0 };
extern const char D_0024B3D8[8] = "sly.ico";
extern const char D_0024B3E0[8] = "%s/%s";
extern const char D_0024B3E8[24] = "icon.sys";

s32 func_0018CA10(void* owner, void* a1, void* a2)
{
    IconSysHeader c;
    CardFileName buf;
    (void)FillMemory(&c, 0, 0x3C4);
    c.f000 = ((IconSysMagic*)&D_0024B3D0)->w0;
    c.f004 = ((IconSysMagic*)&D_0024B3D0)->b4;
    c.f006 = 0x20;
    c.f00C = 0x60;
    c.f010 = 0;
    c.f014 = 0x87;
    c.f018 = 0xFF;
    c.f020 = 0;
    c.f024 = 0x29;
    c.f028 = 0x6F;
    c.f030 = 0;
    c.f034 = 0x29;
    c.f038 = 0x6F;
    c.f040 = 0;
    c.f044 = 0x87;
    c.f048 = 0xFF;
    c.f050 = 0;
    c.f054 = 0.5f;
    c.f058 = -0.5f;
    c.f060 = 0.5f;
    c.f064 = -0.4f;
    c.f068 = 0.1f;
    c.f070 = -0.5f;
    c.f074 = 0.5f;
    c.f078 = 0.5f;
    c.f080 = 0.14f;
    c.f084 = 0.03f;
    c.f088 = 0.48f;
    c.f090 = 0.33f;
    c.f094 = 0;
    c.f098 = 0.33f;
    c.f0A0 = 0.14f;
    c.f0A4 = 0.14f;
    c.f0A8 = 0.38f;
    c.f0B0 = 0.5f;
    c.f0B4 = 0.5f;
    c.f0B8 = 0.5f;
    ConvertStringToCharCodes(a2, (u8*)&c + 0xC0);
    c.f104 = (*(IconFileName*)&D_0024B3D8);
    c.f144 = (*(IconFileName*)&D_0024B3D8);
    c.f184 = (*(IconFileName*)&D_0024B3D8);
    FormatToString(buf.s, D_0024B3E0, a1, D_0024B3E8);
    return CreateMemoryCardFile(owner, &buf, &c, 0x3C4);
}

s32 func_0018CBF8(void* self, void* b)
{
    return WriteMemoryCardKeyedFile(self, (s32)b, (void*)g_memoryCardIconKey, (s32)D_0024B3D8);
}

struct KeyIdFromRecord : KeyId {
    s32 Set(KeyRecord* key)
    {
        s32 has;
        ClearKeyId(this);
        if (!key) {
            has = 0;
        } else {
            s32 t = key->wordB ^ key->maskB;
            second = t;
            first = key->wordA ^ key->maskA;
            has = t != 0;
        }
        return has;
    }
};

s32 func_0018CC20(void* self, s32 a1, void* k, s32 a3)
{
    KeyRecord* key = (KeyRecord*)k;
    char text[0x50];
    BufferedStream obj;
    KeyIdFromRecord pair;
    u8 data[0x1000];
    s32 code;
    s32 got;
    s32 status;

    PushBackMemoryMark();
    code = -1;
    (void)InitBufferedStream(&obj, 0x8040, AllocateBackMemory(0x8040), 0);
    FormatToString(text, D_0024B3E0, a1, a3);
    status = OpenMemoryCardFile(self, text, (void*)0x202, &code);
    if (status == 0) {
        if (!pair.Set(key) || !OpenBufferedSectorStreamRange(&obj, &pair)) {
            status = 0x27;
        } else {
            s32 left = obj.f10;
            while (left > 0) {
                s32 n = 0x1000;
                if (left <= 0xFFF) n = left;
                ReadBufferedStreamBytes(&obj, n, data);
                status = WriteMemoryCardFile(self, (void*)code, data, (void*)n, &got);
                if (status) goto done;
                left -= got;
                if (got != n) { status = 7; goto done; }
            }
            status = 0;
        }
    done:
        CloseBufferedStream(&obj);
        s32 r = CloseMemoryCardFile(self, (void*)code);
        if (status == 0) status = r;
        PopBackMemoryMark();
    }
    DestroyBufferedStream(&obj, 2);
    return status;
}


s32 func_0018CDD8(void* a0, void* a1, GameProgress* out, void* i)
{
    CardFileInfo* info = (CardFileInfo*)i;
    CardFileInfo local;
    GameProgress buf;
    s32 handle = -1;
    s32 got;
    s32 r;
    s32 size;
    if (info == 0) info = &local;
    FillMemory(info, 0, 0x5C);
    ResetGameProgress(out);
    r = CheckMemoryCardFileExists(a0, a1, info);
    if (r != 0) return r;
    if ((info->flags & 0xD4) != 4) return 20;
    size = info->f44;
    if (size != 0x1A00) return 28;
    r = OpenMemoryCardFile(a0, a1, (void*)1, &handle);
    if (r != 0) return r;
    r = ReadMemoryCardFile(a0, (void*)handle, &buf, (void*)0x1A00, &got);
    if (r == 0) {
        r = 8;
        if (got == size) {
            if (buf.type != 18 || buf.size != got) r = 28;
            else if (buf.sum != ChecksumGameProgress(&buf)) r = 27;
            else {
                *out = buf;
                r = 0;
            }
        }
    }
    CloseMemoryCardFile(a0, (void*)handle);
    return r;
}


// The first words of a save image (a GameProgress) as func_0018CFC0 stamps it.
struct ProgressHeader { s32 type; s32 size; s32 handle; };

s32 func_0018CFC0(void* owner, void* name, void* s)
{
    ProgressHeader* state = (ProgressHeader*)s;
    state->type = 18;
    state->size = 0x1A00;
    return CreateMemoryCardFile(owner, name,
        (state->handle = ChecksumGameProgress(state), state), 0x1A00);
}

s32 func_0018D028(void* a0, void* a1, void* a2, void* a3)
{
    u8 local[0x60];
    ResetGameProgress(a2);
    if (a3 == 0) a3 = local;
    s32 result = WriteMemoryCardSlotFile(a0, a1, (ProgressHeader*)a2);
    if (result != 0) return result;
    return CheckMemoryCardFileExists(a0, a1, a3);
}

s32 func_0018D0A0(MemoryCard* o)
{
    s32 r = FinishMemoryCardCall(GetCardInfo(o->port, o->slot, &o->f24, &o->freeBlocks, &o->f2C), (void*)1, 0);
    switch (r) {
    case 9:
    case 11:
        o->targetState = 1;
        r = 11;
        break;
    case 10:
    case 12:
        o->targetState = 2;
        r = 12;
        break;
    case 0:
        if (o->f2C != 0) {
            if (o->targetState < 3)
                o->targetState = 3;
            else
                break;
        } else
            o->targetState = 2;
        break;
    }
    o->nextPollTime = g_elapsedTime[0] + 0.3f;
    return r;
}

s32 func_0018D168(void* p, s32* a1)
{
    MemoryCard* a0 = (MemoryCard*)p;
    s32 v = FinishMemoryCardCall(GetCardInfo(a0->port, a0->slot, &a0->f24, &a0->freeBlocks, &a0->f2C), (void*)1, 0);
    switch (v) {
    case 9: v = 0; break;
    case 10: v = 12; break;
    }
    if (v == 0) { *a1 = a0->freeBlocks << 10; } else { *a1 = 0; }
    return v;
}

s32 func_0018D1F8(void* p)
{
	void* result = func_00209FA8(*(s32*)((char*)p + 4), *(s32*)((char*)p + 8));
	return FinishMemoryCardCall((s32)result, (void*)0x10, 0);
}

s32 func_0018D228(void* p, void* value)
{
	s32 result = FinishMemoryCardCall((s32)MakeCardDirectory(*(s32*)((char*)p + 4), *(s32*)((char*)p + 8), value), (void*)0xB, 0);
	return result == 0x18 ? 0 : result;
}

s32 func_0018D268(void* p, void* a1, void* a2, void* a3)
{
	return FinishMemoryCardCall((s32)OpenCardFile(*(s32*)((char*)p + 4), *(s32*)((char*)p + 8), a1, a2), (void*)2, (s32)a3);
}

s32 func_0018D2B0(void* unused, void* value)
{
	return FinishMemoryCardCall((s32)CloseCardFile(value), (void*)3, 0);
}

LINKER_REMNANT(func_0018D2E0);

s32 func_0018D2E8(void* a0, void* a1, void* a2, void* a3, void* a4)
{
    return FinishMemoryCardCall(ReadCardFile(a1, a2, a3), (void*)5, (s32)a4);
}

s32 func_0018D328(void* unused, void* a1, void* a2, void* a3, void* a4)
{
	return FinishMemoryCardCall((s32)WriteCardFile(a1, a2, a3), (void*)6, (s32)a4);
}


s32 func_0018D368(void* self, void* code, void* data, s32 version)
{
    CardCallResult result;
    result.a = -1;
    s32 status = OpenMemoryCardFile(self, code, (void*)514, &result.a);
    if (status != 0) return status;
    status = WriteMemoryCardFile(self, (void*)result.a, data, (void*)version, &result.b);
    if (status == 0) status = result.b == version ? 0 : 7;
    CloseMemoryCardFile(self, (void*)result.a);
    return status;
}

LINKER_REMNANT(func_0018D408);
