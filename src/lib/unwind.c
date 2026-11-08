/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The toolchain runtime's unwinder, the whole object, 0x1FF048-0x1FFFD0: the readers of the frame
 * tables' encoded numbers, the sort of each registered table's records, the lookup of a code
 * address's record, the reading of its common record and instructions, and the registration of a
 * table, which throw (src/lib/throw.c) relies on to unwind each frame. C, built by the Linux cc1
 * of 2.9-ee-991111 (config/cflags.tsv, docs/TOOLCHAIN.md). Written for this project from retail's
 * code. */
#include "common.h"
#include "asm_func.h"

/* A frame description record: its length, the distance back to its common record, its range. */
typedef struct FrameDesc {
    u32 length;
    s32 commonDelta;
    void* start;
    u32 range;
} FrameDesc;

/* What the common record says: its augmentation string, the handler data, the return column
 * (read as a halfword by the caller, written as a word where the record is parsed). */
typedef struct CommonInfo {
    char* augmentation;
    void* handlerData;
    s32 codeAlign;
    s32 dataAlign;
    u16 returnColumn;
    u16 pad12;
    s32 pad14[3];
} CommonInfo;

/* A frame's unwind state as the caller gets it, 0x2F0 bytes: how the frame's address is
 * computed, and for each register how it was saved and where. */
typedef struct UnwindState {
    s32 cfa;
    void* handlerData;
    s64 cfaOffset;
    s64 cfaReg;
    s64 value[0x50];
    s16 cfaColumn;
    s16 returnColumn;
    u8 how[0x54];
} UnwindState;

/* The interpreter's state: the caller's, and the saved one. */
typedef struct UnwindWork {
    UnwindState s;
    struct UnwindWork* saved;
    s32 pad2F4;
} UnwindWork;

/* A registered block of frame descriptions: the code it covers, its records, its sorted table
 * of them, and the next block. */
typedef struct FrameTable {
    u32 start;
    u32 end;
    FrameDesc* records;
    FrameDesc** sorted;
    u32 count;
    struct FrameTable* next;
} FrameTable;

/* The records of a table being listed: the list, the room for a second one, and the range. */
typedef struct FrameList {
    FrameDesc** items;
    s32 count;
    FrameDesc** other;
    s32 unused;
    u32 lo;
    s32 hi;
} FrameList;

/* An unaligned word and halfword in the instruction stream. */
typedef struct __attribute__((packed)) Unaligned32 {
    u32 v;
} Unaligned32;

typedef struct __attribute__((packed)) Unaligned16 {
    u16 v;
} Unaligned16;

/* A table's elements, as func_001FF0E0 and func_001FFE58 merge them by key. */
typedef struct KeyedElem {
    s32 a;
    s32 b;
    s32 key;
} KeyedElem;

typedef struct KeyedArray {
    KeyedElem** data;
    u32 count;
} KeyedArray;

/* The head of the blocks of frame descriptions. */
static FrameTable* D_0062A7B8;
/* The lock of the list, in a runtime built for one thread: its functions do nothing. It sits in the
 * word after the list (nothing reads it), and its inline functions keep func_001FF658's check of
 * the walk's result where retail has it. */
static s32 D_0062A7BC;

static inline s32 LockFrameTables(s32* lock) { return 0; }
static inline s32 UnlockFrameTables(s32* lock) { return 0; }

s32 CompareStrings(const char* a, const char* b);
s32 GetStringLength(const char* s);
void* EnterRuntimeLock(u32 size);
void LeaveRuntimeLock(void* p);
void AbortProgram(void) __attribute__((noreturn));
void* FillMemory(void* dst, s32 c, u32 n);
FrameDesc* func_001FF658(void* pc);
u8* func_001FF740(FrameDesc* f, CommonInfo* info);
u8* func_001FF848(u8* insn, UnwindWork* work, CommonInfo* info, u32* pc);
u8* ReadUnsignedLeb128(u8* input, u32* output);
FrameDesc** func_001FF1E0(FrameList* list, s32 count);
s32 func_001FF448(FrameDesc* p);
void func_001FF490(FrameDesc* cur, FrameList* list, s32* lo, s32* hi);
void func_001FFE58(KeyedArray* self, KeyedArray* out);

u8* ReadUnsignedLeb128(u8* input, u32* output)
{
    u8 byte = *input;
    u32 shift = 0;
    u32 value;

    input++;
    value = byte & 0x7F;
    if (byte & 0x80) {
        do {
            byte = *input;
            shift += 7;
            input++;
            value |= (byte & 0x7F) << shift;
        } while (byte & 0x80);
    }
    *output = value;
    return input;
}

u8* ReadSignedLeb128(u8* input, s32* output)
{
    u32 shift = 0;
    u32 value = 0;
    u8 byte;

    do {
        byte = *input++;
        value |= (u32)(byte & 0x7F) << shift;
        shift += 7;
    } while (byte & 0x80);

    if (shift < 32) {
        s32 signMask = -1;
        if (byte & 0x40) {
            value |= signMask << shift;
        }
    }
    *output = (s32)value;
    return input;
}

void func_001FF0E0(KeyedArray* self, KeyedArray* other)
{
    s32 j = other->count;
    if (j != 0) {
        s32 n1 = self->count;
        s32 i = n1;
        do {
            KeyedElem* x = other->data[--j];
            if (i != 0 && self->data[i - 1]->key - x->key > 0) {
                do {
                    self->data[i + j] = self->data[i - 1];
                    i--;
                } while (i != 0 && self->data[i - 1]->key - x->key > 0);
            }
            self->data[i + j] = x;
        } while (j != 0);
        self->count = n1 + other->count;
    }
}

/* The order of two records: by key. */
static inline s32 CompareFrames(KeyedElem* x, KeyedElem* y)
{
    return x->key - y->key;
}

/* The runtime's swap is a statement macro: retail's sift loops need its do-while form (a plain
 * block of the same three statements changes them). */
#define SWAP_FRAMES(x, y) do { KeyedElem* tmp = x; x = y; y = tmp; } while (0)

/* A heap sort of the records that came out of order. */
static inline void SortFrames(KeyedArray* erratic)
{
    KeyedElem** a = erratic->data;
    u32 n = erratic->count;
    u32 m = n;
    u32 i;

    while (m > 0) {
        --m;
        for (i = m; 2 * i + 1 < n;) {
            if (2 * i + 2 < n && CompareFrames(a[2 * i + 2], a[2 * i + 1]) > 0
                && CompareFrames(a[2 * i + 2], a[i]) > 0) {
                SWAP_FRAMES(a[i], a[2 * i + 2]);
                i = 2 * i + 2;
            } else if (CompareFrames(a[2 * i + 1], a[i]) > 0) {
                SWAP_FRAMES(a[i], a[2 * i + 1]);
                i = 2 * i + 1;
            } else
                break;
        }
    }
    while (n > 1) {
        --n;
        SWAP_FRAMES(a[0], a[n]);
        for (i = 0; 2 * i + 1 < n;) {
            if (2 * i + 2 < n && CompareFrames(a[2 * i + 2], a[2 * i + 1]) > 0
                && CompareFrames(a[2 * i + 2], a[i]) > 0) {
                SWAP_FRAMES(a[i], a[2 * i + 2]);
                i = 2 * i + 2;
            } else if (CompareFrames(a[2 * i + 1], a[i]) > 0) {
                SWAP_FRAMES(a[i], a[2 * i + 1]);
                i = 2 * i + 1;
            } else
                break;
        }
    }
}

/* The end of a table's sort: the records in order split from those out of it, these sorted and
 * merged back; the second list is freed. */
FrameDesc** func_001FF1E0(FrameList* list, s32 count)
{
    if (list->count != count)
        AbortProgram();
    func_001FFE58((KeyedArray*)list, (KeyedArray*)&list->other);
    if (list->count + list->unused != count)
        AbortProgram();
    SortFrames((KeyedArray*)&list->other);
    func_001FF0E0((KeyedArray*)list, (KeyedArray*)&list->other);
    LeaveRuntimeLock(list->other);
    return list->items;
}

s32 func_001FF448(FrameDesc* p)
{
    s32 n = 0;
    s32 off = p->length;
    s32 nx;
    if (off != 0) {
        goto body;
        for (;;) {
            off = nx;
        body:
            if (p->commonDelta != 0 && p->start != 0) n++;
            p = (FrameDesc*)((u8*)p + off + 4);
            nx = p->length;
            if (nx == 0) break;
        }
    }
    return n;
}

void func_001FF490(FrameDesc* cur, FrameList* list, s32* lo, s32* hi)
{
    s32 mn = *lo;
    s32 mx = *hi;
    if (cur->length != 0) {
        do {
            if (cur->commonDelta == 0) goto next;
            if (cur->start == 0) goto next;
            {
                list->items[list->count++] = cur;
                {
                    s32 x = (s32)cur->start;
                    s32 e = x + cur->range;
                    if ((u32)x < (u32)mn) mn = x;
                    if ((u32)mx < (u32)e) mx = e;
                }
            }
        next:
            cur = (FrameDesc*)((u8*)cur + cur->length + 4);
        } while (cur->length != 0);
    }
    *lo = mn;
    *hi = mx;
}

void func_001FF518(FrameTable* self)
{
    s32 count;
    FrameDesc** p;
    FrameList acc;

    if (self->sorted != 0) {
        p = self->sorted;
        count = 0;
        if (*p != 0) {
            do {
                count += func_001FF448(*p);
                p++;
            } while (*p != 0);
        }
    } else {
        count = func_001FF448(self->records);
    }
    self->count = count;
    acc.items = (FrameDesc**)EnterRuntimeLock(count << 2);
    acc.other = (FrameDesc**)EnterRuntimeLock(count << 2);
    acc.lo = 0xFFFFFFFF;
    acc.count = 0;
    acc.unused = 0;
    acc.hi = 0;
    if (self->sorted != 0) {
        p = self->sorted;
        if (*p != 0) {
            do {
                func_001FF490(*p, &acc, (s32*)&acc.lo, &acc.hi);
                p++;
            } while (*p != 0);
        }
    } else {
        func_001FF490(self->records, &acc, (s32*)&acc.lo, &acc.hi);
    }
    self->sorted = func_001FF1E0(&acc, count);
    self->start = acc.lo;
    self->end = acc.hi;
}

FrameDesc* func_001FF658(void* pc)
{
    FrameTable* t;
    u32 lo, hi, mid;
    FrameDesc* f;

    LockFrameTables(&D_0062A7BC);
    for (t = D_0062A7B8; t != 0; t = t->next) {
        if (t->start == 0)
            func_001FF518(t);
        if ((u32)pc >= t->start && (u32)pc < t->end)
            break;
    }
    UnlockFrameTables(&D_0062A7BC);
    if (t == 0)
        return 0;

    lo = 0;
    hi = t->count;
    while (lo < hi) {
        mid = (lo + hi) / 2;
        f = t->sorted[mid];
        if (pc < f->start)
            hi = mid;
        else if ((u32)pc >= (u32)f->start + f->range)
            lo = mid + 1;
        else
            return f;
    }
    return 0;
}

u8* func_001FF740(FrameDesc* f, CommonInfo* info)
{
    CommonInfo* common = (CommonInfo*)((char*)&f->commonDelta - f->commonDelta);
    u8* p;
    u32 len;

    info->augmentation = (char*)common + 9;
    if (CompareStrings(info->augmentation, "") != 0 &&
        CompareStrings(info->augmentation, "eh") != 0 &&
        info->augmentation[0] != 'z') {
        return 0;
    }
    p = (u8*)info->augmentation + GetStringLength(info->augmentation) + 1;
    if (CompareStrings(info->augmentation, "eh") == 0) {
        info->handlerData = (void*)((Unaligned32*)p)->v;
        p += 4;
    } else {
        info->handlerData = 0;
    }
    p = ReadUnsignedLeb128(p, (u32*)&info->codeAlign);
    p = ReadSignedLeb128(p, &info->dataAlign);
    *(s32*)&info->returnColumn = *p++;
    if (info->augmentation[0] == 'z') {
        p = ReadUnsignedLeb128(p, &len);
        p += len;
    }
    return p;
}

u8* func_001FF848(u8* p, UnwindWork* rs, CommonInfo* cie, u32* pc)
{
    s32 offset;
    u32 reg;
    u32 reg2;
    u8 op = *p++;

    if (op & 0x40) {
        *pc += (op & 0x3F) * cie->codeAlign;
    } else if (op & 0x80) {
        reg = op & 0x3F;
        p = ReadUnsignedLeb128(p, (u32*)&offset);
        offset *= cie->dataAlign;
        rs->s.how[reg] = 1;
        rs->s.value[reg] = offset;
    } else if (op & 0xC0) {
        reg = op & 0x3F;
        rs->s.how[reg] = 0;
    } else {
        switch (op) {
        case 0:
            break;
        case 1:
            *pc = ((Unaligned32*)p)->v;
            p += 4;
            break;
        case 2:
            *pc += *p;
            p += 1;
            break;
        case 3:
            *pc += ((Unaligned16*)p)->v;
            p += 2;
            break;
        case 4:
            *pc += ((Unaligned32*)p)->v;
            p += 4;
            break;
        case 5:
            p = ReadUnsignedLeb128(p, &reg);
            p = ReadUnsignedLeb128(p, (u32*)&offset);
            offset *= cie->dataAlign;
            rs->s.how[reg] = 1;
            rs->s.value[reg] = offset;
            break;
        case 6:
            p = ReadUnsignedLeb128(p, &reg);
            rs->s.how[reg] = 0;
            break;
        case 7:
        case 8:
            break;
        case 9:
            p = ReadUnsignedLeb128(p, &reg);
            p = ReadUnsignedLeb128(p, &reg2);
            rs->s.how[reg] = 2;
            rs->s.value[reg] = reg2;
            break;
        case 12:
            p = ReadUnsignedLeb128(p, &reg);
            p = ReadUnsignedLeb128(p, (u32*)&offset);
            rs->s.cfaColumn = reg;
            rs->s.cfaOffset = offset;
            break;
        case 13:
            p = ReadUnsignedLeb128(p, &reg);
            rs->s.cfaColumn = reg;
            break;
        case 14:
            p = ReadUnsignedLeb128(p, (u32*)&offset);
            rs->s.cfaOffset = offset;
            break;
        case 10: {
            UnwindWork* copy = (UnwindWork*)EnterRuntimeLock(sizeof(UnwindWork));
            *copy = *rs;
            rs->saved = copy;
            break;
        }
        case 11: {
            UnwindWork* copy = rs->saved;
            *rs = *copy;
            LeaveRuntimeLock(copy);
            break;
        }
        case 45:
            for (reg = 16; reg < 32; reg++) {
                rs->s.how[reg] = 1;
                rs->s.value[reg] = (reg - 16) * 4;
            }
            break;
        case 46:
            p = ReadUnsignedLeb128(p, (u32*)&offset);
            rs->s.cfaReg = offset;
            break;
        default:
            AbortProgram();
            break;
        }
    }
    return p;
}

void RegisterFrameInfo(void* begin, FrameTable* ob)
{
    ob->records = begin;
    ob->start = ob->end = 0;
    ob->count = 0;
    ob->next = D_0062A7B8;
    D_0062A7B8 = ob;
    ob->sorted = (FrameDesc**)begin;
}


FrameTable* DeregisterFrameInfo(void* value)
{
    FrameTable** slot = &D_0062A7B8;
    FrameTable* t;

    if (D_0062A7B8 != 0) {
        do {
            t = *slot;
            if (t->records == value) {
                *slot = t->next;
                if (t->start != 0)
                    LeaveRuntimeLock(t->sorted);
                return t;
            }
            slot = &t->next;
        } while (t->next != 0);
    }
    AbortProgram();
}

UnwindState* FindFrameUnwindState(void* target, UnwindState* out)
{
    FrameDesc* f;
    u8* insn;
    u8* end;
    void* pc;
    CommonInfo info;
    UnwindWork work;

    f = func_001FF658(target);
    if (f == 0)
        return 0;
    insn = func_001FF740(f, &info);
    if (insn == 0)
        return 0;

    FillMemory(&work, 0, sizeof(work));
    work.s.returnColumn = info.returnColumn;
    work.s.handlerData = info.handlerData;

    {
        FrameDesc* common = (FrameDesc*)((char*)&f->commonDelta - f->commonDelta);
        end = (u8*)common + common->length + 4;
    }
    while (insn < end)
        insn = func_001FF848(insn, &work, &info, 0);

    insn = (u8*)(f + 1);
    if (info.augmentation[0] == 'z') {
        u32 skip;
        insn = ReadUnsignedLeb128(insn, &skip);
        insn += skip;
    }

    end = (u8*)f + f->length + 4;
    pc = f->start;
    while (insn < end && pc <= target)
        insn = func_001FF848(insn, &work, &info, (u32*)&pc);

    *out = work.s;
    return out;
}

void func_001FFE58(KeyedArray* self, KeyedArray* out)
{
    u32 n = self->count;
    u32 next[n];
    u32 head = 0xFFFFFFFFu;
    u32 i;
    u32 cur;
    for (i = 0; i < n; i++) {
        for (cur = head; cur != 0xFFFFFFFFu; cur = next[cur]) {
            KeyedElem* a = self->data[i];
            KeyedElem* b = self->data[cur];
            if (a->key - b->key >= 0) break;
            out->data[out->count++] = self->data[cur];
            self->data[cur] = 0;
        }
        head = i;
        next[i] = cur;
    }
    cur = 0;
    for (i = 0; i < n; i++) {
        KeyedElem* x = self->data[i];
        if (x != 0) {
            self->data[cur++] = x;
        }
    }
    self->count = cur;
}
