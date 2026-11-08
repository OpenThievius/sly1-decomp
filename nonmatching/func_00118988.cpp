// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 876/872, checked 2026-11-08
// NEAR (2026-11-08, night-gamec): anim is in s3 in retail (s2 here) and the spill reloads take other registers; the frame and stack slots are retail's
// In the context of its file, src/main/script_machine.cpp: its declarations before the function, bodies cut.
#include "common.h"
#include "vu0.h"
#include "asm_func.h"
#include "vu0.h"
#include "world.h"
#include "globals.h"
#include "shapes.h"
#include "collider.h"
#include "script_value.h"
#include "script_builtin.h"
#include "queued_call.h"
#include "vu0.h"

// The script machine's built-in functions (the table D_00259958, which func_00119BB0 calls through,
// lists them from func_00112698 on), their helpers and the collector's mark stacks: one source
// file, 0x112698 to 0x11AE78 (.rodata from 0x248FE0, .data from 0x259938 to 0x25C250, no .bss).
// A built-in has ScriptBuiltinFn's signature (script_builtin.h); the evaluator (func_0011A080) and the
// handlers it dispatches to take the result's place, an expression (a chain of R11B008Node) and
// the scope.

// The mark stacks of the collector (func_0011A850 walks them; value.cpp's functions run it through
// func_0011AB58). Its constructor (func_0011A678) and destructor (func_0011A680) are defined below at
// their places; the compiler's initialiser, constructor and destructor for this file are
// func_0011ADF8, func_0011AE38 and func_0011AE58 (config/us/generated.tsv).
// A pooled entry the collector marks: a scope (a count and that many values from 0x04, its
// chain of keyed values at 0x14) or a value node (a tag, a payload, the next node at 0x08).
struct MarkEntry {
    s32 f0;                 // 0x00
    MarkEntry* f4;          // 0x04
    MarkEntry* f8;          // 0x08
    MarkEntry* fC;          // 0x0C
    MarkEntry* f10;         // 0x10
    MarkEntry* f14;         // 0x14
};

// A tag 0x1F payload as the collector reads it: a scope, a chain of nodes and a third entry.
struct MarkRecord {
    MarkEntry* f0;          // 0x00
    MarkEntry* f4;          // 0x04
    s32 f8;                 // 0x08
    s32 fC;                 // 0x0C
    MarkEntry* f10;         // 0x10
};

// D_00259F38: the collector's roots and its three mark stacks. Each is a count followed by its
// items; ResetMarkRoots clears the two root counts, CollectScriptPools the three stack counts.
struct MarkStacks {
    s32 rootCount;              // 0x0000: AddUniqueMarkRoot
    MarkEntry* roots[0x140];    // 0x0004
    s32 listCount;              // 0x0504: AddMarkRootList
    R11B008List* lists[0x80];   // 0x0508
    s32 objectCount;            // 0x0708: PushMarkObject, PopMarkObject
    MarkEntry* objects[0x200];  // 0x070C
    s32 chainCount;             // 0x0F0C: PushMarkChain, PopMarkChain
    MarkEntry* chains[0x100];   // 0x0F10
    s32 recordCount;            // 0x1310: PushMarkRecord, PopMarkRecord
    MarkRecord* records[0x400]; // 0x1314
    u8 pad2314[4];              // 0x2314: to the label's end
    MarkStacks();
    ~MarkStacks();
};

// The table of one-float math functions func_00115CA0 calls by index (src/libm, and
// func_001EA408).
typedef f32 (*MathFn_259938)(f32 x);

// The pooled payloads (value_pools.cpp): the 16-byte vectors of tags 0x16 and 0x18, the 0x40-byte
// block of tag 0x17, the two and three floats of tags 0x19 and 0x1A.
f32* AcquireVectorAPayload(void);
f32* AcquireMatrixPayload(void);
f32* AcquireVectorBPayload(void);
f32* AcquirePairPayload(void);
f32* AcquireTriplePayload(void);
R11B008Key* NewKeyedValue(void);
void CopyKeyedValueChain(R11B008Key* src, R11B008Key* dst, s32 first);

// The pools (value.cpp) and the collector's calls on them (value_pools.cpp).
void BuildBasisFromXAndZHint(void* self, void* table, void* value);
extern u8 g_valueNodePool[];
extern u8 g_scopePool[];
extern u8 g_keyedValuePool[];
extern u8 g_payloadPool[];
extern u8 g_propertyRefPool[];
void* TakePoolEntry(void* pool);
void MarkPoolLiveEnd(void* pool);
void ClearPoolLiveStates(u8* pool);
void ReleaseDeadPoolEntries(u8* pool);

void* FillMemory(void* p, s32 value, s32 size);
void CopyMemory(void* dst, void* src, s32 bytes);

// Other files' functions the built-ins call.
f32 ArctangentOfRatio(f32 x, f32 y);
f32 RandomFloatInRange(f32 a, f32 b);
s32 AreFloatsNearlyEqual(f32 a, f32 b, f32 c);
f32 ComputeAngleBetweenVectors(s32 a, s32 b, f32* c);
s32 ComputeBallisticLaunchVelocity(void* a0, void* a1, f32* a2, void* a3, f32 f);
void FitQuadraticCurve(f32* a0, f32 x, f32 y, f32 z, f32 w);
f32 ClampToRange(void* span, f32 x);
s32 IsInsideRange(void* target, f32 scale);
void CopyTransposedMatrix(s32 a, f32* b);
void* InvertMatrix4x4(s32 a, f32* b);
void TransformMatrixByObject(s32 a, s32 b, f32* c);
void MatrixToEulerAngles(void* a, f32* b);
void MatrixToAxisAngle(void* a, f32* b, f32* c);
void RotateMatrixUpright(void* sub, s32 zero, void* out);
void BuildMatrixFromRotationAndTranslation(void* a, void* b, f32* c);
void ResetMatrixHomogeneous(void* p);
void SetCachedVoiceParam(s32 index, s32 value);
void SeedRandom(s32 v);
void* FindFirstObjectById(void* host, s32 a1, s32 a2, s32 ctx);
s32 GatherObjectsByMode(void* host, s32 a1, s32 a2, void* ctx, s32 a4, u8* a5);
s32 GatherObjectsById(void* host, s32 a1, s32 a2, void* ctx, s32 a4, u8* a5);
void* GetActiveSwitchedCollider(void);
ScriptValue* UpdateObjectProperty(ScriptValue* out, s32 a1, s32 a2, ScriptValue* a3);
ScriptValue* SetExtraObjectProperty(ScriptValue* out, s32 a1, s32 a2, ScriptValue* a3);
ScriptValue* AddObjectProperty(ScriptValue* out, s32 a1, s32 a2, ScriptValue* a3);
ScriptValue* GetObjectProperty(ScriptValue* out, s32 a1, s32 a2);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void GatherCollidersInSphere(void* self, f32 scale, s32 p1, s32 p2, s32 p3, s32 p4, s32* o1, u8** o2);
s32 TransformPointBetweenFrames(void* a, s32 b, void* c, f32* d);
s32 TransformDirectionBetweenFrames(void* a, s32 b, void* c, f32* d);
void TransformRotationBetweenFrames(s32 a, s32 b, s32 c, f32* d);
void StartSoundEffect(s32 a0, void* a1, s32 a2, s32 a3, s32 a4, s32 a5, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);
void ClearSoundRecordHandle(void* slot);
void StopSoundRecord(void* self, s32 n);
void StartPadRecordPattern(void* p, s32 n, f32 f);
void SendPointEventToWorldListener(void* obj, f32 f);
s32 PrintFormatted(const char* x);
ScriptValue* EvalScriptEntry(ScriptValue* out, s32 id, u8* ctx);
ScriptScope* GetScriptEntryScope(s32 id, u8* ctx);
void RunScriptEventHandler(void* a);

extern f32 g_gameTime;
extern u8 g_padRecord[];

// The table's records (script_builtin.h): D_00259DE8 is the count word of the last record of the first
// label (func_00117668's, 0x259DE4), the one word func_00117668 reads.
extern ScriptBuiltin g_scriptBuiltins[];
extern s32 D_00259DE8;

// The collector's calls on the pooled entries (value_pools.cpp).
s32 IsPoolEntryUnmarked(MarkEntry* e);
void MarkPoolEntryUsed(MarkEntry* e);

s32 FindNearestSpanObject(Quad16* z, s32 a, s32 b, s32 c, void** d, ColliderSpan* e);

// This file's functions. The built-ins (ScriptBuiltinFn) and their helpers:
ScriptValue* IgnoreScriptArgument(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* IgnoreScriptArguments(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* DiscardScriptArgument(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* TestScriptWordsEqual(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* CompareScriptNumbers(ScriptValue* ret, ScriptValue* args, s32 mode);
ScriptValue* TestScriptLess(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* TestScriptLessOrEqual(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* TestScriptGreater(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* TestScriptGreaterOrEqual(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* TestScriptValuesIdentical(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* CompareScriptValues(ScriptValue* ret, ScriptValue* a, ScriptValue* b);
ScriptValue* TestScriptEqual(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* IsScriptBool(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* IsScriptNumber(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* IsScriptFloat(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* IsScriptInt(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* IsScriptPointer(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* IsScriptVector(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* IsScriptMatrix(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* IsScriptVector4(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* IsScriptFloatPair(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* IsScriptFloatTriple(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* IsScriptList(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* IsScriptEmptyList(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* IsScriptRef(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* IsScriptNullRef(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* IsScriptHostFunction(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* IsScriptFunction(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* TestScriptNearlyEqual(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* IsScriptFalse(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* PrependScriptListItem(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* GetScriptListHead(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* GetScriptListTail(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* SetScriptListCell(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope, s32 mode);
ScriptValue* SetScriptListHead(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* SetScriptListTail(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* GetScriptListLength(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* GetScriptListItem(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* TestScriptListContains(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* ReturnScriptArgument(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* MapScriptList(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* FilterScriptList(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* ForEachScriptListItem(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* EvalScriptArgument(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* MakeScriptVector(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* MakeScriptMatrix(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* SetScriptVoiceParam(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* MakeScriptVector4FromThree(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* MakeScriptFloatPair(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* MakeScriptFloatTriple(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* GetScriptVectorElement(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* SetScriptRandomSeed(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* GetScriptRandomFloat(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* CallScriptMathFunction(ScriptValue* ret, ScriptValue* arg, s32 index);
ScriptValue* GetScriptSquareRoot(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* GetScriptSine(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* GetScriptCosine(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* GetScriptTangent(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* GetScriptArcSine(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* GetScriptArcCosine(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* GetScriptArcTangent(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* WrapScriptAngle(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* GetScriptAtan2(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* GetScriptBallisticVelocity(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* GetScriptAngleAndAxis(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* TransposeScriptMatrix(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* InvertScriptMatrix(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* TransformScriptMatrixByObject(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* GetScriptMatrixTranslation(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* GetScriptMatrixRotation(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* GetScriptMatrixEuler(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* GetScriptMatrixAxisAngle(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* MakeScriptUprightObjectMatrix(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* EvalScriptQuadratic(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* EvalScriptClampedQuadratic(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* MakeScriptVector4FromFour(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* ClampScriptToRange(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* TestScriptInsideRange(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* ConvertScriptFloatToInt(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* RoundScriptFloatUp(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* RoundScriptFloat(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* TruncateScriptFloat(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* GetScriptAbsolute(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* GetScriptMaximum(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* GetScriptMinimum(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* GetScriptRemainder(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* GetScriptClock(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* ScheduleScriptCall(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* SetScriptObjectEventTimer(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* DispatchScriptObjectProperty(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope, s32 kind);
ScriptValue* AddScriptObjectProperty(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* SetScriptExtraObjectProperty(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* UpdateScriptObjectProperty(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* GetScriptObjectProperty(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* MakeScriptRefList(ScriptValue* ret, s32 count, void** values);
// How its callers declare it (KEPT: see build/swarm/v2/NOTES.md): they call it as GCC calls a
// function that gives a class back, a `call` with no value (expand_call has no value register when
// the result goes through the hidden address), which schedules the argument moves differently
// from a call of a function returning a pointer. The plain value cannot say that.
void MakeScriptRefList(ScriptValue* ret, s32 count, u8* values);
ScriptValue* FindScriptObject(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* FindScriptObjectList(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* FindScriptObjectById(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* FindScriptObjectListById(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* GetScriptControlledObject(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* GetScriptWorld(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* GetScriptCamera(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* GatherScriptObjectsById(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* FindScriptObjectsInSphere(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
// How its callers declare it; it is defined giving back a RetValue (KEPT, see there).
ScriptValue* SearchScriptObjectHits(ScriptValue* ret, s32 id, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* CollectScriptObjectHits(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* FindScriptObjectHit(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* TransformScriptPointBetweenFrames(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* TransformScriptDirectionBetweenFrames(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* TransformScriptRotationBetweenFrames(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* StartScriptEffect(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* StopScriptEffect(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* StartScriptPadRecordPattern(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* SendScriptPointEventToWorldListener(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

// A 128-bit value, copied as one quadword.
typedef u64 Quad_118D10 __attribute__((mode(TI)));

// A 128-bit value, stored as one quadword.
typedef u64 Quad_118D20 __attribute__((mode(TI)));

Quad_118D10* CopyQuadword(Quad_118D10* out, void* src);
Quad_118D20* StoreQuadword(Quad_118D20* out, Quad_118D20 v);

// The evaluator (func_0011A080) and the handlers it dispatches to by the expression's kind.
ScriptValue* EvalScriptVariable(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope);
ScriptValue* EvalScriptAssign(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope);
ScriptValue* EvalScriptDefine(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope);
ScriptValue* EvalScriptAssert(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope);
ScriptValue* EvalScriptIf(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope);
ScriptValue* EvalScriptOr(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope);
// How func_0011A080 declares it; it is defined giving back a RetValue (KEPT, see there).
ScriptValue* EvalScriptAnd(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope);
ScriptValue* EvalScriptCond(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope);
ScriptValue* EvalScriptCase(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope);
ScriptValue* EvalScriptLet(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope);
ScriptValue* EvalScriptWhile(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope);
ScriptValue* EvalScriptLambda(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope);
ScriptValue* EvalScriptBody(ScriptValue* ret, R11B008Node* list, ScriptScope* scope);
ScriptValue* EvalScriptSequence(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope);
ScriptValue* EvalScriptCall(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope);
ScriptValue* EvalScriptImportScope(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope);
ScriptValue* EvalScriptExpression(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope);

// The scopes.
void SetScriptScopeParent(ScriptScope* scope, ScriptScope* parent);
void AddScriptScopeParent(ScriptScope* scope, ScriptScope* parent);
ScriptValue* DefineScriptVariable(ScriptValue* ret, ScriptScope* scope, s32 key, ScriptValue* value);
ScriptValue* AssignScriptVariable(ScriptValue* ret, ScriptScope* scope, s32 key, ScriptValue* value);
s32 LookupScriptVariable(ScriptScope* scope, s32 key, s32 flag, ScriptValue* out);
ScriptValue* FindScriptVariable(ScriptScope* scope, s32 key, s32 flag);
void CopyScriptScope(ScriptScope* src, ScriptScope* dst);
ScriptScope* NewScriptScope(void);
void ReleaseScriptScope(void);

// The collector.
void ResetMarkRoots(MarkStacks* self);
void ShutDownMarkRoots();
void AddUniqueMarkRoot(MarkStacks* self, MarkEntry* value);
void AddMarkRootList(MarkStacks* self, R11B008List* list);
void PushMarkObject(MarkStacks* self, MarkEntry* value);
MarkEntry* PopMarkObject(MarkStacks* self);
void PushMarkChain(MarkStacks* self, MarkEntry* value);
MarkEntry* PopMarkChain(MarkStacks* self);
void PushMarkRecord(MarkStacks* self, MarkRecord* value);
MarkRecord* PopMarkRecord(MarkStacks* self);
void MarkPoolLiveEnds(void);
void DrainMarkStacks(MarkStacks* self);
void CollectScriptPools(MarkStacks* self);

// Tables of functions this file's code reads: the math functions of func_00115CA0.
f32 WrapAngle(f32 x);
f32 Arctangent(f32 x);
f32 Cosine(f32 x);
f32 Sine(f32 x);
f32 Tangent(f32 x);
f32 Arccosine(f32 x);
f32 Arcsine(f32 x);
f32 SquareRoot(f32 x);
MathFn_259938 g_scriptMathFunctions[8] = { SquareRoot, Sine, Cosine, Tangent, Arcsine, Arccosine, Arctangent, WrapAngle };
MarkStacks g_markStacks;

ScriptValue* IgnoreScriptArgument(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* IgnoreScriptArguments(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* DiscardScriptArgument(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* TestScriptWordsEqual(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* CompareScriptNumbers(ScriptValue* ret, ScriptValue* e, s32 mode);

ScriptValue* TestScriptLess(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* TestScriptLessOrEqual(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* TestScriptGreater(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* TestScriptGreaterOrEqual(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* TestScriptValuesIdentical(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* CompareScriptValues(ScriptValue* ret, ScriptValue* a, ScriptValue* b);

ScriptValue* TestScriptEqual(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* IsScriptBool(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* IsScriptNumber(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* IsScriptFloat(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* IsScriptInt(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* IsScriptPointer(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* IsScriptVector(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* IsScriptMatrix(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* IsScriptVector4(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* IsScriptFloatPair(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* IsScriptFloatTriple(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* IsScriptList(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* IsScriptEmptyList(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* IsScriptRef(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* IsScriptNullRef(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* IsScriptHostFunction(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* IsScriptFunction(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* TestScriptNearlyEqual(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* IsScriptFalse(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* PrependScriptListItem(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* GetScriptListHead(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* GetScriptListTail(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* SetScriptListCell(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope, s32 mode);

ScriptValue* SetScriptListHead(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* SetScriptListTail(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* GetScriptListLength(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* GetScriptListItem(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* TestScriptListContains(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* ReturnScriptArgument(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* MapScriptList(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* FilterScriptList(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* ForEachScriptListItem(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* EvalScriptArgument(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* MakeScriptVector(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

// A row of the 0x40-byte block of tag 0x17 (func_0011C618), 16-aligned: copied with lq/sq.
struct __attribute__((aligned(16))) Row_115510 {
    f32 f[4];               // 0x00
};

ScriptValue* MakeScriptMatrix(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* SetScriptVoiceParam(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* MakeScriptVector4FromThree(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* MakeScriptFloatPair(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* MakeScriptFloatTriple(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

// The payloads func_001159B8 reads: a 16-byte vector (tags 0x16, 0x18) and the four rows of the
// 0x40-byte block (tag 0x17), 16-aligned (a row is copied with lq/sq).
struct __attribute__((aligned(16))) ScriptVectorRow {
    f32 v[4];               // 0x00
};
struct ScriptMatrixPayload {
    ScriptVectorRow row[4];      // 0x00
};

ScriptValue* GetScriptVectorElement(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* SetScriptRandomSeed(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* GetScriptRandomFloat(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* CallScriptMathFunction(ScriptValue* ret, ScriptValue* arg, s32 index);

ScriptValue* GetScriptSquareRoot(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* GetScriptSine(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* GetScriptCosine(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* GetScriptTangent(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* GetScriptArcSine(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* GetScriptArcCosine(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* GetScriptArcTangent(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* WrapScriptAngle(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* GetScriptAtan2(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* GetScriptDotProduct(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* func_00115FF8(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* GetScriptVectorLength(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* GetScriptDistance(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* GetScriptDistanceSquared(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* ProjectScriptVector(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* RemoveScriptVectorComponent(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* GetScriptBallisticVelocity(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* GetScriptAngleAndAxis(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* TransposeScriptMatrix(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* InvertScriptMatrix(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* TransformScriptMatrixByObject(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

typedef f32 (*MathFn_259938)(f32 x);
f32* AcquireMatrixPayload(void);
void MatrixToAxisAngle(void* a, f32* b, f32* c);
void ResetMatrixHomogeneous(void* p);

void MultiplyMatrices3x3(void* a, void* b, void* out);
void BuildAxisAngleMatrix(void* axis, void* out, f32 angle);

ScriptValue* InterpolateScriptRotation(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* GetScriptMatrixTranslation(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* GetScriptMatrixRotation(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* GetScriptMatrixEuler(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* GetScriptMatrixAxisAngle(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* MakeScriptDirectionMatrix(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

// What func_00189378 fills in for func_00188B08: 0x30 bytes.
struct UprightBasis {
    u8 bytes[0x30];         // 0x00
};

ScriptValue* MakeScriptUprightObjectMatrix(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* EvalScriptQuadratic(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* EvalScriptClampedQuadratic(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* MakeScriptVector4FromFour(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* ClampScriptToRange(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* TestScriptInsideRange(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* ConvertScriptFloatToInt(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* RoundScriptFloatUp(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* RoundScriptFloat(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* TruncateScriptFloat(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* GetScriptAbsolute(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* GetScriptMaximum(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* GetScriptMinimum(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* GetScriptRemainder(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* GetScriptClock(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* ScheduleScriptCall(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* SetScriptObjectEventTimer(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* DispatchScriptObjectProperty(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope, s32 kind);

ScriptValue* AddScriptObjectProperty(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* SetScriptExtraObjectProperty(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* UpdateScriptObjectProperty(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* GetScriptObjectProperty(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* MakeScriptRefList(ScriptValue* ret, s32 count, void** values);

ScriptValue* FindScriptObject(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* FindScriptObjectList(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* FindScriptObjectById(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* FindScriptObjectListById(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* GetScriptControlledObject(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* GetScriptWorld(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* GetScriptCamera(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* GatherScriptObjectsById(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* FindScriptObjectsInSphere(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

// KEPT (build/swarm/v2/NOTES.md): func_00118198 and func_00119218 give their value back as a
// class (the result's place is GCC's hidden first argument), and their early return inside a
// loop keeps its own copy and destruction only so: written with the plain value and explicit
// calls, GCC cross-jumps that return into the last one. Their callers call them through the
// plain declarations above (ScriptValue* first).
struct RetValue : ScriptValue {
    RetValue() { InitScriptValue(this); }
    RetValue(const RetValue& o) { CopyConstructScriptValue(this, &o); }
    ~RetValue() { DestroyScriptValue(this, 2); }
};

RetValue SearchScriptObjectHits(s32 id, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* CollectScriptObjectHits(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* FindScriptObjectHit(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* TransformScriptPointBetweenFrames(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* TransformScriptDirectionBetweenFrames(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* TransformScriptRotationBetweenFrames(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* GetScriptPointAheadOfCamera(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* StartScriptEffect(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* StopScriptEffect(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* StartScriptPadRecordPattern(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

ScriptValue* SendScriptPointEventToWorldListener(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);

// A sample's 16-aligned quadword and 0x30-byte rotation, as func_0012CD78 fills them.
struct __attribute__((aligned(16))) ScriptSampleQuad {
    f32 f[4];
};
struct __attribute__((aligned(16))) ScriptSampleRotation {
    f32 f[12];
};

void* AllocateBackMemory(s32 size);
void func_0012CD78(f32 a, f32 b, void* anim, void* from, void* to, s32 n, ScriptSampleQuad* positions,
                   ScriptSampleRotation* rotations, ScriptSampleQuad* q4, ScriptSampleQuad* q8);
void CopyRotationMatrix(f32* dst, ScriptSampleRotation* src);

ScriptValue* SampleScriptAnimation(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    ScriptValue t;
    s32 n;
    s32 mask;
    void* from;
    void* to;
    InitScriptValue(&q);
    ScriptSampleQuad* positions = 0;
    ScriptSampleRotation* rotations = 0;
    ScriptSampleQuad* q4 = 0;
    ScriptSampleQuad* q8 = 0;
    void* anim = args[0].p;
    ConvertScriptValueToFloat(&t, args + 1);
    f32 a = t.f;
    DestroyScriptValue(&t, 2);
    ConvertScriptValueToFloat(&t, args + 2);
    f32 b = t.f;
    DestroyScriptValue(&t, 2);
    mask = args[6].i;
    from = args[3].p;
    to = args[4].p;
    n = args[5].i;
    PushBackMemoryMark();
    if (mask & 1) {
        positions = (ScriptSampleQuad*)AllocateBackMemory(n * sizeof(ScriptSampleQuad));
    }
    if (mask & 2) {
        rotations = (ScriptSampleRotation*)AllocateBackMemory(n * sizeof(ScriptSampleRotation));
    }
    if (mask & 4) {
        q4 = (ScriptSampleQuad*)AllocateBackMemory(n * sizeof(ScriptSampleQuad));
    }
    if (mask & 8) {
        q8 = (ScriptSampleQuad*)AllocateBackMemory(n * sizeof(ScriptSampleQuad));
    }
    func_0012CD78(a, b, anim, from, to, n, positions, rotations, q4, q8);
    R11B008Node* head = 0;
    R11B008Node* tail = 0;
    for (s32 bit = 1; bit < 9; bit <<= 1) {
        if (!(mask & bit)) {
            continue;
        }
        R11B008Node* list = NewScriptValueNode();
        if (tail != 0) {
            tail->next = list;
        } else {
            head = list;
        }
        tail = list;
        SetScriptValueTag(list, 0);
        R11B008Node* last = 0;
        for (s32 i = 0; i < n; i++) {
            R11B008Node* v = NewScriptValueNode();
            switch (bit) {
            case 1: {
                ScriptSampleQuad* p = (ScriptSampleQuad*)AcquireVectorAPayload();
                *p = positions[i];
                SetScriptValueVectorA(v, (f32*)p);
                break;
            }
            case 2: {
                f32* m = AcquireMatrixPayload();
                CopyRotationMatrix(m, &rotations[i]);
                SetScriptValueMatrix(v, m);
                break;
            }
            case 4: {
                ScriptSampleQuad* p = (ScriptSampleQuad*)AcquireVectorAPayload();
                *p = q4[i];
                SetScriptValueVectorA(v, (f32*)p);
                break;
            }
            case 8: {
                ScriptSampleQuad* p = (ScriptSampleQuad*)AcquireVectorAPayload();
                *p = q8[i];
                SetScriptValueVectorA(v, (f32*)p);
                break;
            }
            }
            if (last != 0) {
                last->next = v;
            } else {
                SetScriptValueChain(list, v);
            }
            last = v;
        }
    }
    PopBackMemoryMark();
    if (head != 0) {
        SetScriptValueChain(&q, head);
    } else {
        SetScriptValueTag(&q, 0);
    }
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}
