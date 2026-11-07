// SPDX-License-Identifier: AGPL-3.0-or-later
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
INCLUDE_DATA(D_00259958);
INCLUDE_DATA(D_00259DE8);
MarkStacks g_markStacks;

INCLUDE_ASM(func_00112698);

INCLUDE_ASM(func_00112968);

INCLUDE_RODATA(jtbl_00248FE0);
INCLUDE_RODATA(jtbl_00249000);
INCLUDE_RODATA(jtbl_00249020);
INCLUDE_RODATA(jtbl_00249040);
INCLUDE_ASM(func_00112C38);

INCLUDE_RODATA(jtbl_00249060);
INCLUDE_RODATA(jtbl_00249080);
INCLUDE_RODATA(jtbl_002490A0);
INCLUDE_ASM(func_00113240);

ScriptValue* IgnoreScriptArgument(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* IgnoreScriptArguments(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* DiscardScriptArgument(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* TestScriptWordsEqual(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    SetScriptValueBool(&q, args[0].i == args[1].i);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* CompareScriptNumbers(ScriptValue* ret, ScriptValue* e, s32 mode)
{
    f32 xy[2];
    ScriptValue obj;
    InitScriptValue(&obj);
    f32* out = xy;
    for (s32 i = 1; i >= 0; i--, e++) {
        if (e->tag == 0x15) {
            *out = e->f;
        } else {
            *out = (f32)e->i;
        }
        out++;
    }
    switch (mode) {
    case 0:
        SetScriptValueBool(&obj, xy[0] < xy[1]);
        break;
    case 1:
        SetScriptValueBool(&obj, xy[0] <= xy[1]);
        break;
    case 2:
        SetScriptValueBool(&obj, xy[0] > xy[1]);
        break;
    case 3:
        SetScriptValueBool(&obj, xy[0] >= xy[1]);
        break;
    }
    CopyConstructScriptValue(ret, &obj);
    DestroyScriptValue(&obj, 2);
    return ret;
}

ScriptValue* TestScriptLess(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    CompareScriptNumbers(ret, args, 0);
    return ret;
}

ScriptValue* TestScriptLessOrEqual(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    CompareScriptNumbers(ret, args, 1);
    return ret;
}

ScriptValue* TestScriptGreater(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    CompareScriptNumbers(ret, args, 2);
    return ret;
}

ScriptValue* TestScriptGreaterOrEqual(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    CompareScriptNumbers(ret, args, 3);
    return ret;
}

ScriptValue* TestScriptValuesIdentical(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    s32 r;
    InitScriptValue(&q);
    ScriptValue* k = args;
    ScriptValue* p = k + 1;
    if (k->tag != p->tag) {
        r = 0;
    } else {
        switch (k->tag) {
        case 20:
        case 27: case 28: case 29: case 30: case 31: case 32: case 33:
            r = (k->i == p->i);
            break;
        case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
        case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19:
        case 34:
            r = 1;
            break;
        }
    }
    SetScriptValueBool(&q, r);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* CompareScriptValues(ScriptValue* ret, ScriptValue* a, ScriptValue* b)
{
    ScriptValue R;
    ScriptValue A;
    ScriptValue B;
    ScriptValue C;
    ScriptValue D;
    ScriptValue E;
    ScriptValue F;
    s32 r;

    InitScriptValue(&R);
    if (a->tag != b->tag) {
        r = 0;
    } else {
        switch (a->tag) {
        case 30: {
            R11B008Node* p = a->node;
            R11B008Node* q = b->node;
            if (p == q) {
                r = 1;
            } else if ((p->next == 0) != (q->next == 0)) {
                r = 0;
            } else {
                InitScriptValue(&A);
                CompareScriptValues(&B, p, q);
                AssignScriptValue(&A, &B);
                DestroyScriptValue(&B, 2);
                if (A.i == 0) {
                    r = 0;
                } else if (p->next == 0) {
                    r = 1;
                } else {
                    InitScriptValue(&B);
                    InitScriptValue(&C);
                    SetScriptValueChain(&B, p->next);
                    SetScriptValueChain(&C, q->next);
                    CompareScriptValues(&D, &B, &C);
                    AssignScriptValue(&A, &D);
                    DestroyScriptValue(&D, 2);
                    r = A.i;
                    DestroyScriptValue(&C, 2);
                    DestroyScriptValue(&B, 2);
                }
                DestroyScriptValue(&A, 2);
            }
            break;
        }
        case 31: {
            R11AFC8* p = a->rec;
            R11AFC8* q = b->rec;
            if (p == q) {
                r = 1;
            } else if (p->w8 != q->w8 || p->wC != q->wC || p->w0 != q->w0) {
                r = 0;
            } else {
                InitScriptValue(&A);
                InitScriptValue(&B);
                InitScriptValue(&E);
                SetScriptValueChain(&A, (R11B008Node*)p->w10);
                SetScriptValueChain(&B, (R11B008Node*)q->w10);
                CompareScriptValues(&F, &A, &B);
                AssignScriptValue(&E, &F);
                DestroyScriptValue(&F, 2);
                r = E.i;
                DestroyScriptValue(&E, 2);
                DestroyScriptValue(&B, 2);
                DestroyScriptValue(&A, 2);
            }
            break;
        }
        case 20: case 27: case 28: case 29: case 32:
            r = a->i == b->i;
            break;
        case 33: {
            ScriptHostCall* p = (ScriptHostCall*)a->p;
            ScriptHostCall* q = (ScriptHostCall*)b->p;
            if (p == q) {
                r = 1;
            } else {
                r = p->self == q->self && p->fn == q->fn;
            }
            break;
        }
        case 21: case 22: case 23: case 24: case 25: case 26:
            break;
        case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
        case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19:
        case 34:
            r = 1;
            break;
        }
    }
    SetScriptValueBool(&R, r);
    CopyConstructScriptValue(ret, &R);
    DestroyScriptValue(&R, 2);
    return ret;
}

ScriptValue* TestScriptEqual(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    CompareScriptValues(ret, args, args + 1);
    return ret;
}

ScriptValue* IsScriptBool(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue local;
    InitScriptValue(&local);
    SetScriptValueBool(&local, args[0].tag == 0x1B);
    CopyConstructScriptValue(ret, &local);
    DestroyScriptValue(&local, 2);
    return ret;
}

ScriptValue* IsScriptNumber(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue local;
    InitScriptValue(&local);
    SetScriptValueBool(&local, args[0].tag >= 0x14 && args[0].tag < 0x16);
    CopyConstructScriptValue(ret, &local);
    DestroyScriptValue(&local, 2);
    return ret;
}

ScriptValue* IsScriptFloat(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue local;
    InitScriptValue(&local);
    SetScriptValueBool(&local, args[0].tag == 0x15);
    CopyConstructScriptValue(ret, &local);
    DestroyScriptValue(&local, 2);
    return ret;
}

ScriptValue* IsScriptInt(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue local;
    InitScriptValue(&local);
    SetScriptValueBool(&local, args[0].tag == 0x14);
    CopyConstructScriptValue(ret, &local);
    DestroyScriptValue(&local, 2);
    return ret;
}

ScriptValue* IsScriptPointer(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    SetScriptValueBool(&q, args->tag == 0x1C);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* IsScriptVector(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    SetScriptValueBool(&q, args->tag == 0x16);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* IsScriptMatrix(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    SetScriptValueBool(&q, args->tag == 0x17);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* IsScriptVector4(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    SetScriptValueBool(&q, args->tag == 0x18);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* IsScriptFloatPair(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue a;
    InitScriptValue(&a);
    SetScriptValueBool(&a, args->tag == 0x19);
    CopyConstructScriptValue(ret, &a);
    DestroyScriptValue(&a, 2);
    return ret;
}

ScriptValue* IsScriptFloatTriple(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue a;
    InitScriptValue(&a);
    SetScriptValueBool(&a, args->tag == 0x1A);
    CopyConstructScriptValue(ret, &a);
    DestroyScriptValue(&a, 2);
    return ret;
}

ScriptValue* IsScriptList(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    s32 v = args->tag;
    SetScriptValueBool(&q, v == 0x1E || v == 0);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* IsScriptEmptyList(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    SetScriptValueBool(&q, args->tag == 0);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* IsScriptRef(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    SetScriptValueBool(&q, (args->tag ^ 0x20) == 0);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* IsScriptNullRef(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    int flag = 0;
    if (args[0].tag == 0x20) {
        flag = args[0].i == 0;
    }
    SetScriptValueBool(&q, flag);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* IsScriptHostFunction(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    SetScriptValueBool(&q, args[0].tag == 0x21);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* IsScriptFunction(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    s32 v = args->tag;
    int flag = (v == 0x1F || v == 0x1D);
    SetScriptValueBool(&q, flag);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* TestScriptNearlyEqual(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    f32 out[3];
    InitScriptValue(&q);
    for (s32 k = 0; k < 3; k++) {
        if (args[k].tag == 0x14) {
            out[k] = (f32)args[k].i;
        } else {
            out[k] = args[k].f;
        }
    }
    s32 flag = AreFloatsNearlyEqual(out[0], out[1], out[2]);
    SetScriptValueBool(&q, flag);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* IsScriptFalse(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    int flag = 0;
    if (args[0].tag == 0x1B) {
        flag = (u32)args[0].i < 1;
    }
    SetScriptValueBool(&q, flag);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* PrependScriptListItem(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    R11B008Node* node = NewScriptValueNode();
    AssignScriptValue(node, args);
    s32 kind = args[1].tag;
    args = args + 1;
    if (kind == 0) {
        node->next = 0;
    } else if (kind == 0x1E) {
        node->next = args->node;
    }
    SetScriptValueChain(&q, node);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* GetScriptListHead(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    AssignScriptValue(&q, args->node);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* GetScriptListTail(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    R11B008Node* in = args->node;
    R11B008Node* v = in->next;
    if (v != 0) {
        SetScriptValueChain(&q, v);
    } else {
        SetScriptValueTag(&q, 0);
    }
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptListCell(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope, s32 mode)
{
    ScriptValue q;
    R11B008Node* p;
    InitScriptValue(&q);
    p = args[0].node;
    if (mode == 0x23) {
        AssignScriptValue(p, &args[1]);
    } else {
        if (args[1].tag == 0x1E) {
            p->next = args[1].node;
        } else {
            p->next = 0;
        }
    }
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptListHead(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    SetScriptListCell(ret, count, args, scope, 0x23);
    return ret;
}

ScriptValue* SetScriptListTail(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    SetScriptListCell(ret, count, args, scope, 0x24);
    return ret;
}

ScriptValue* GetScriptListLength(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    s32 n = 0;
    if (args->tag == 0x1E && args->node) {
        R11B008Node* node = args->node;
        do {
            node = node->next;
            n++;
        } while (node);
    }
    SetScriptValueInt(&q, n);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* GetScriptListItem(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    SetScriptValueTag(&q, 0);
    if (args->tag == 0x1E) {
        R11B008Node* node = args->node;
        ScriptValue* sub = &args[1];
        s32 i = 0;
        while (node != 0) {
            if (i == sub->i) {
                AssignScriptValue(&q, node);
                break;
            }
            node = node->next;
            i++;
        }
    }
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* TestScriptListContains(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue A;
    ScriptValue B;
    ScriptValue C[2];
    ScriptValue D;
    s32 n;
    R11B008Node* cur;

    InitScriptValue(&A);
    InitScriptValue(&B);
    ScriptValue* q = C;
    n = 1;
    do {
        InitScriptValue(q);
        n--;
        q++;
    } while (n != -1);
    SetScriptValueBool(&A, 0);
    if (args[1].tag == 0x1E) {
        AssignScriptValue(C, args);
        cur = args[1].node;
        while (cur != 0) {
            AssignScriptValue(&C[1], cur);
            TestScriptEqual(&D, 2, C, scope);
            AssignScriptValue(&B, &D);
            DestroyScriptValue(&D, 2);
            if (B.tag == 0x1B) {
                if (B.i != 0) {
                    SetScriptValueBool(&A, 1);
                    break;
                }
            }
            cur = cur->next;
        }
    }
    CopyConstructScriptValue(ret, &A);
    q = &D;
    if (C != q) {
        do {
            q--;
            DestroyScriptValue(q, 0);
        } while (C != q);
    }
    DestroyScriptValue(&B, 2);
    DestroyScriptValue(&A, 2);
    return ret;
}

ScriptValue* ReturnScriptArgument(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    CopyConstructScriptValue(ret, args);
    return ret;
}

INCLUDE_ASM(func_00114BB0);

ScriptValue* MapScriptList(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    R11B008Node arr[5];
    R11B008Node* it;
    InitScriptValue(&q);
    it = arr;
    for (s32 k = 4; k != -1; k--) {
        InitScriptValue(it);
        it->tag = -1;
        it++;
    }
    if (args[1].tag == 0) {
        AssignScriptValue(&q, &args[1]);
    } else {
        R11B008Node* list = NewScriptValueNode();
        R11B008Node* p[2];
        R11B008Node* last;
        list->tag = 0x1E;
        for (u32 i = 0; i < 2; i++) {
            p[i] = NewScriptValueNode();
        }
        SetScriptValueChain(&arr[0], &arr[1]);
        arr[0].next = 0;
        SetScriptValueChain(&arr[1], &arr[3]);
        arr[1].next = &arr[2];
        SetScriptValueChain(&arr[2], &arr[4]);
        arr[2].next = 0;
        arr[3].tag = 0x11;
        arr[3].next = p[0];
        AssignScriptValue(p[0], args);
        arr[4].tag = 0x11;
        arr[4].next = p[1];
        ScriptValue* m = &args[1];
        for (R11B008Node* l = m->node; l != 0; l = l->next) {
            R11B008Node* e = NewScriptValueNode();
            ScriptValue t;
            AssignScriptValue(p[1], l);
            EvalScriptExpression(&t, &arr[0], scope);
            AssignScriptValue(e, &t);
            DestroyScriptValue(&t, 2);
            if (list->node == 0) {
                SetScriptValueChain(list, e);
            } else {
                last->next = e;
            }
            last = e;
        }
        SetScriptValueChain(&q, list->node);
    }
    CopyConstructScriptValue(ret, &q);
    R11B008Node* end = arr + 5;
    while (arr != end) {
        end--;
        DestroyScriptValue(end, 2);
    }
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* FilterScriptList(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    R11B008Node arr[5];
    R11B008Node* it;
    R11B008Node* p[2];
    ScriptValue r;
    InitScriptValue(&q);
    it = arr;
    for (s32 k = 4; k != -1; k--) {
        InitScriptValue(it);
        it->tag = -1;
        it++;
    }
    InitScriptValue(&r);
    if (args[1].tag == 0) {
        AssignScriptValue(&q, &args[1]);
    } else {
        R11B008Node* list = 0;
        R11B008Node* last;
        for (u32 i = 0; i < 2; i++) {
            p[i] = NewScriptValueNode();
        }
        SetScriptValueChain(&arr[0], &arr[1]);
        arr[0].next = 0;
        SetScriptValueChain(&arr[1], &arr[3]);
        arr[1].next = &arr[2];
        SetScriptValueChain(&arr[2], &arr[4]);
        arr[2].next = 0;
        arr[3].tag = 0x11;
        arr[3].next = p[0];
        AssignScriptValue(p[0], args);
        arr[4].tag = 0x11;
        arr[4].next = p[1];
        ScriptValue* m = &args[1];
        for (R11B008Node* l = m->node; l != 0; l = l->next) {
            ScriptValue t;
            AssignScriptValue(p[1], l);
            EvalScriptExpression(&t, &arr[0], scope);
            AssignScriptValue(&r, &t);
            DestroyScriptValue(&t, 2);
            if (r.tag == 0x1B && r.i != 0) {
                R11B008Node* e = NewScriptValueNode();
                AssignScriptValue(e, l);
                if (list == 0) {
                    list = NewScriptValueNode();
                    SetScriptValueChain(list, e);
                } else {
                    last->next = e;
                }
                last = e;
            }
        }
        if (list != 0) {
            SetScriptValueChain(&q, list->node);
        } else {
            q.tag = 0;
        }
    }
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&r, 2);
    R11B008Node* end = arr + 5;
    while (arr != end) {
        end--;
        DestroyScriptValue(end, 2);
    }
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* ForEachScriptListItem(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    R11B008Node arr[5];
    R11B008Node* it;
    InitScriptValue(&q);
    it = arr;
    for (s32 k = 4; k != -1; k--) {
        InitScriptValue(it);
        it->tag = -1;
        it++;
    }
    if (args[1].tag == 0x1E) {
        R11B008Node* p[2];
        for (u32 i = 0; i < 2; i++) {
            p[i] = NewScriptValueNode();
        }
        SetScriptValueChain(&arr[0], &arr[1]);
        arr[0].next = 0;
        SetScriptValueChain(&arr[1], &arr[3]);
        arr[1].next = &arr[2];
        SetScriptValueChain(&arr[2], &arr[4]);
        arr[2].next = 0;
        arr[3].tag = 0x11;
        arr[3].next = p[0];
        AssignScriptValue(p[0], args);
        arr[4].tag = 0x11;
        arr[4].next = p[1];
        ScriptValue* m = &args[1];
        for (R11B008Node* l = m->node; l != 0; l = l->next) {
            ScriptValue t;
            AssignScriptValue(p[1], l);
            EvalScriptExpression(&t, &arr[0], scope);
            AssignScriptValue(&q, &t);
            DestroyScriptValue(&t, 2);
        }
    }
    q.tag = 0x22;
    CopyConstructScriptValue(ret, &q);
    R11B008Node* end = arr + 5;
    while (arr != end) {
        end--;
        DestroyScriptValue(end, 2);
    }
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* EvalScriptArgument(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    ScriptValue u;
    InitScriptValue(&t);
    R11B008Node* n = NewScriptValueNode();
    AssignScriptValue(n, args);
    EvalScriptExpression(&u, n, scope);
    AssignScriptValue(&t, &u);
    DestroyScriptValue(&u, 2);
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

ScriptValue* MakeScriptVector(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue a;
    ScriptValue b;
    s32 n = 2;
    InitScriptValue(&a);
    ScriptValue* in = args;
    f32* base = AcquireVectorAPayload();
    f32* out = base;
    do {
        ConvertScriptValueToFloat(&b, in);
        in++;
        AssignScriptValue(&a, &b);
        n--;
        DestroyScriptValue(&b, 2);
        *out = a.f;
        out++;
    } while (n >= 0);
    SetScriptValueVectorA(&a, base);
    CopyConstructScriptValue(ret, &a);
    DestroyScriptValue(&a, 2);
    return ret;
}

// A row of the 0x40-byte block of tag 0x17 (func_0011C618), 16-aligned: copied with lq/sq.
struct __attribute__((aligned(16))) Row_115510 {
    f32 f[4];               // 0x00
};

ScriptValue* MakeScriptMatrix(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t, u;
    InitScriptValue(&t);
    Row_115510* a = (Row_115510*)AcquireMatrixPayload();
    R11B008Node* n = args->node;
    switch (count) {
    case 3:
    case 4: {
        ResetMatrixHomogeneous(a);
        for (s32 i = 0; i < count; i++) {
            a[i] = *(Row_115510*)n->v;
            n = n->next;
        }
        break;
    }
    case 9:
        ResetMatrixHomogeneous(a);
    case 16: {
        s32 m = count == 9 ? 3 : 4;
        for (s32 i = 0; i < m; i++) {
            for (s32 j = 0; j < m; j++) {
                ConvertScriptValueToFloat(&u, n);
                AssignScriptValue(&t, &u);
                DestroyScriptValue(&u, 2);
                a[i].f[j] = t.f;
                n = n->next;
            }
        }
        break;
    }
    }
    SetScriptValueMatrix(&t, (f32*)a);
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

ScriptValue* SetScriptVoiceParam(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    SetCachedVoiceParam(args[0].i, args[1].i);
    InitScriptValue(&q);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* MakeScriptVector4FromThree(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue a;
    ScriptValue b;
    f32* base;
    f32* out;
    s32 n = 2;
    InitScriptValue(&a);
    ScriptValue* p = args;
    base = AcquireVectorBPayload();
    out = base;
    do {
        ConvertScriptValueToFloat(&b, p);
        p++;
        AssignScriptValue(&a, &b);
        n--;
        DestroyScriptValue(&b, 2);
        *out++ = a.f;
    } while (n >= 0);
    SetScriptValueVectorB(&a, base);
    CopyConstructScriptValue(ret, &a);
    DestroyScriptValue(&a, 2);
    return ret;
}

ScriptValue* MakeScriptFloatPair(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue a;
    ScriptValue b;
    f32* out;
    InitScriptValue(&a);
    out = AcquirePairPayload();
    ConvertScriptValueToFloat(&b, args);
    AssignScriptValue(&a, &b);
    DestroyScriptValue(&b, 2);
    out[0] = a.f;
    ConvertScriptValueToFloat(&b, args + 1);
    AssignScriptValue(&a, &b);
    DestroyScriptValue(&b, 2);
    out[1] = a.f;
    SetScriptValuePair(&a, out);
    CopyConstructScriptValue(ret, &a);
    DestroyScriptValue(&a, 2);
    return ret;
}

ScriptValue* MakeScriptFloatTriple(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    ScriptValue u;
    InitScriptValue(&t);
    f32* out = AcquireTriplePayload();
    ConvertScriptValueToFloat(&u, args);
    AssignScriptValue(&t, &u);
    DestroyScriptValue(&u, 2);
    out[0] = t.f;
    ConvertScriptValueToFloat(&u, args + 1);
    AssignScriptValue(&t, &u);
    DestroyScriptValue(&u, 2);
    out[1] = t.f;
    ConvertScriptValueToFloat(&u, args + 2);
    AssignScriptValue(&t, &u);
    DestroyScriptValue(&u, 2);
    out[2] = t.f;
    SetScriptValueTriple(&t, out);
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

// The payloads func_001159B8 reads: a 16-byte vector (tags 0x16, 0x18) and the four rows of the
// 0x40-byte block (tag 0x17), 16-aligned (a row is copied with lq/sq).
struct __attribute__((aligned(16))) ScriptVectorRow {
    f32 v[4];               // 0x00
};
struct ScriptMatrixPayload {
    ScriptVectorRow row[4];      // 0x00
};

ScriptValue* GetScriptVectorElement(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    R11B008Node* indexNode = args[1].node;
    switch (args[0].tag) {
    case 0x16:
        SetScriptValueFloat(&q, ((ScriptVectorRow*)args[0].v)->v[indexNode->i]);
        break;
    case 0x17: {
        s32 i = indexNode->i;
        ScriptVectorRow* v;
        if (count == 2) {
            v = (ScriptVectorRow*)AcquireVectorAPayload();
            *v = ((ScriptVectorRow*)args[0].v)[i];
            SetScriptValueVectorA(&q, (f32*)v);
        } else {
            indexNode = indexNode->next;
            v = &((ScriptMatrixPayload*)args[0].v)->row[i];
            SetScriptValueFloat(&q, v->v[indexNode->i]);
        }
        break;
    }
    case 0x18:
        SetScriptValueFloat(&q, ((ScriptVectorRow*)args[0].v)->v[indexNode->i]);
        break;
    case 0x19:
        SetScriptValueFloat(&q, indexNode->i == 0 ? args[0].v[0] : args[0].v[1]);
        break;
    case 0x1A:
        switch (indexNode->i) {
        case 0:
            SetScriptValueFloat(&q, args[0].v[0]);
            break;
        case 1:
            SetScriptValueFloat(&q, args[0].v[1]);
            break;
        case 2:
            SetScriptValueFloat(&q, args[0].v[2]);
            break;
        }
        break;
    }
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptRandomSeed(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    if (args->tag == 0x14) {
        SeedRandom(args->i);
    } else {
        SeedRandom((s32)args->f);
    }
    q.tag = 0x22;
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* GetScriptRandomFloat(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue f;
    InitScriptValue(&f);
    f32 x;
    f32 y;
    if (args[0].tag == 0x14) {
        x = (f32)args[0].i;
    } else {
        x = args[0].f;
    }
    if (args[1].tag == 0x14) {
        y = (f32)args[1].i;
    } else {
        y = args[1].f;
    }
    f32 r = RandomFloatInRange(x, y);
    SetScriptValueFloat(&f, r);
    CopyConstructScriptValue(ret, &f);
    DestroyScriptValue(&f, 2);
    return ret;
}

ScriptValue* CallScriptMathFunction(ScriptValue* ret, ScriptValue* arg, s32 index)
{
    ScriptValue f;
    InitScriptValue(&f);
    f32 v;
    if (arg->tag == 0x15) {
        v = arg->f;
    } else {
        v = (f32)arg->i;
    }
    f32 r = g_scriptMathFunctions[index](v);
    SetScriptValueFloat(&f, r);
    CopyConstructScriptValue(ret, &f);
    DestroyScriptValue(&f, 2);
    return ret;
}

ScriptValue* GetScriptSquareRoot(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    CallScriptMathFunction(ret, args, 0);
    return ret;
}

ScriptValue* GetScriptSine(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    CallScriptMathFunction(ret, args, 1);
    return ret;
}

ScriptValue* GetScriptCosine(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    CallScriptMathFunction(ret, args, 2);
    return ret;
}

ScriptValue* GetScriptTangent(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    CallScriptMathFunction(ret, args, 3);
    return ret;
}

ScriptValue* GetScriptArcSine(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    CallScriptMathFunction(ret, args, 4);
    return ret;
}

ScriptValue* GetScriptArcCosine(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    CallScriptMathFunction(ret, args, 5);
    return ret;
}

ScriptValue* GetScriptArcTangent(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    CallScriptMathFunction(ret, args, 6);
    return ret;
}

ScriptValue* WrapScriptAngle(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    CallScriptMathFunction(ret, args, 7);
    return ret;
}

ScriptValue* GetScriptAtan2(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue obj;
    f32 xy[2];
    InitScriptValue(&obj);
    f32* out = xy;
    for (s32 i = 1; i >= 0; i--, args++) {
        if (args->tag == 0x15) {
            *out = args->f;
        } else {
            *out = (f32)args->i;
        }
        out++;
    }
    f32 d = ArctangentOfRatio(xy[0], xy[1]);
    SetScriptValueFloat(&obj, d);
    CopyConstructScriptValue(ret, &obj);
    DestroyScriptValue(&obj, 2);
    return ret;
}

ScriptValue* GetScriptDotProduct(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue obj;
    InitScriptValue(&obj);
    SetScriptValueFloat(&obj, Vu0::ToFloat(Vu0::Dot(Vu0::Q(*(Vec02*)args[0].v), Vu0::Q(*(Vec02*)args[1].v))));
    CopyConstructScriptValue(ret, &obj);
    DestroyScriptValue(&obj, 2);
    return ret;
}

ScriptValue* func_00115FF8(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    InitScriptValue(&t);
    f32* p = AcquireVectorAPayload();
    Vu0::Q(*p) = Vu0::Cross(Vu0::Q(*args[0].v), Vu0::Q(*args[1].v));
    SetScriptValueVectorA(&t, p);
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

ScriptValue* GetScriptVectorLength(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue obj;
    InitScriptValue(&obj);
    SetScriptValueFloat(&obj, Vu0::ToFloat(Vu0::Length(Vu0::Q(*args->v))));
    CopyConstructScriptValue(ret, &obj);
    DestroyScriptValue(&obj, 2);
    return ret;
}

INCLUDE_ASM(func_00116108);

ScriptValue* GetScriptDistanceSquared(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue obj;
    InitScriptValue(&obj);
    if (args[1].tag == 0) {
        u128 d = Vu0::Sub(Vu0::Q(*(Vec02*)args[0].v), Vu0::Q(D_00248D30));
        SetScriptValueFloat(&obj, Vu0::ToFloat(Vu0::Dot(d, d)));
    } else {
        u128 d = Vu0::Sub(Vu0::Q(*(Vec02*)args[0].v), Vu0::Q(*(Vec02*)args[1].node->v));
        SetScriptValueFloat(&obj, Vu0::ToFloat(Vu0::Dot(d, d)));
    }
    CopyConstructScriptValue(ret, &obj);
    DestroyScriptValue(&obj, 2);
    return ret;
}

INCLUDE_ASM(func_001162D0);

ScriptValue* ProjectScriptVector(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue obj;
    InitScriptValue(&obj);
    f32* p = AcquireVectorAPayload();
    u128 a = Vu0::Q(*(Vec02*)args[0].v);
    u128 b = Vu0::Q(*(Vec02*)args[1].v);
    Vu0::Q(*(Vec02*)p) = Vu0::MulX(b, Vu0::Dot(a, b));
    SetScriptValueVectorA(&obj, p);
    CopyConstructScriptValue(ret, &obj);
    DestroyScriptValue(&obj, 2);
    return ret;
}

ScriptValue* RemoveScriptVectorComponent(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue obj;
    InitScriptValue(&obj);
    f32* p = AcquireVectorAPayload();
    u128 a = Vu0::Q(*(Vec02*)args[0].v);
    u128 b = Vu0::Q(*(Vec02*)args[1].v);
    Vu0::Q(*(Vec02*)p) = Vu0::Sub(a, Vu0::MulX(b, Vu0::Dot(a, b)));
    SetScriptValueVectorA(&obj, p);
    CopyConstructScriptValue(ret, &obj);
    DestroyScriptValue(&obj, 2);
    return ret;
}

ScriptValue* GetScriptBallisticVelocity(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    ScriptValue v;
    InitScriptValue(&q);
    f32* p = AcquireVectorAPayload();
    void* s3;
    if (args[3].tag == 0) {
        s3 = 0;
    } else {
        s3 = args[3].node->p;
    }
    void* s1 = args[0].p;
    void* fc = args[1].p;
    ConvertScriptValueToFloat(&v, &args[2]);
    ComputeBallisticLaunchVelocity(s1, fc, p, s3, v.f);
    DestroyScriptValue(&v, 2);
    SetScriptValueVectorA(&q, p);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* GetScriptAngleAndAxis(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    InitScriptValue(&t);
    R11B008Node* a = NewScriptValueNode();
    R11B008Node* b = NewScriptValueNode();
    a->next = b;
    f32* c = AcquireVectorAPayload();
    SetScriptValueVectorA(b, c);
    f32 d = ComputeAngleBetweenVectors(args[0].i, args[1].i, c);
    SetScriptValueFloat(a, d);
    SetScriptValueChain(&t, a);
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

ScriptValue* TransposeScriptMatrix(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    InitScriptValue(&t);
    f32* a = AcquireMatrixPayload();
    CopyTransposedMatrix(args[0].i, a);
    SetScriptValueMatrix(&t, a);
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

ScriptValue* InvertScriptMatrix(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    InitScriptValue(&t);
    f32* a = AcquireMatrixPayload();
    InvertMatrix4x4(args[0].i, a);
    SetScriptValueMatrix(&t, a);
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

ScriptValue* TransformScriptMatrixByObject(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    InitScriptValue(&t);
    f32* a = AcquireMatrixPayload();
    TransformMatrixByObject(args[0].i, args[1].i, a);
    SetScriptValueMatrix(&t, a);
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

typedef f32 (*MathFn_259938)(f32 x);
f32* AcquireMatrixPayload(void);
void MatrixToAxisAngle(void* a, f32* b, f32* c);
void ResetMatrixHomogeneous(void* p);

void MultiplyMatrices3x3(void* a, void* b, void* out);
void BuildAxisAngleMatrix(void* axis, void* out, f32 angle);

ScriptValue* InterpolateScriptRotation(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue obj;
    Mat02 delta;
    Vec02 axis;
    Mat02 a;
    Mat02 b;
    f32 angle;
    InitScriptValue(&obj);
    f32* m = AcquireMatrixPayload();
    MultiplyMatrices3x3(args[0].p, args[1].p, &delta);
    MatrixToAxisAngle(&delta, &angle, (f32*)&axis);
    BuildAxisAngleMatrix(&axis, &delta, angle * args[2].f);
    const Mat02* src = (const Mat02*)args[0].p;
    u128 v0 = Vu0::Q(src->r[0]);
    Vu0::Q(b.r[0]) = Vu0::Q(a.r[0]) = Vu0::RotateUntied(delta, v0);
    Vu0::Q(b.r[1]) = Vu0::Q(a.r[1]) = Vu0::RotateUntied(delta, Vu0::Q(src->r[1]));
    Vu0::Q(b.r[2]) = Vu0::Q(a.r[2]) = Vu0::RotateUntied(delta, Vu0::Q(src->r[2]));
    *(Mat02*)m = a;
    ResetMatrixHomogeneous(m);
    SetScriptValueMatrix(&obj, m);
    CopyConstructScriptValue(ret, &obj);
    DestroyScriptValue(&obj, 2);
    return ret;
}

ScriptValue* GetScriptMatrixTranslation(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    InitScriptValue(&t);
    f32* c = AcquireVectorAPayload();
    *(Quad16*)c = *(Quad16*)((u8*)args[0].p + 0x30);
    SetScriptValueVectorA(&t, c);
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

ScriptValue* GetScriptMatrixRotation(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    f32* obj;
    InitScriptValue(&q);
    obj = AcquireMatrixPayload();
    *(Mat4A*)obj = *(Mat4A*)args[0].v;
    ResetMatrixHomogeneous(obj);
    SetScriptValueMatrix(&q, obj);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* GetScriptMatrixEuler(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    InitScriptValue(&t);
    f32* c = AcquireVectorAPayload();
    MatrixToEulerAngles(args[0].p, c);
    SetScriptValueVectorA(&t, c);
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

ScriptValue* GetScriptMatrixAxisAngle(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    Vec4U vec;
    InitScriptValue(&t);
    R11B008Node* a = NewScriptValueNode();
    R11B008Node* b = NewScriptValueNode();
    f32* c = AcquireVectorAPayload();
    SetScriptValueVectorA(b, c);
    a->next = b;
    MatrixToAxisAngle(args[0].p, &vec.x, c);
    SetScriptValueFloat(a, vec.x);
    SetScriptValueChain(&t, a);
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

ScriptValue* MakeScriptDirectionMatrix(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue obj;
    u128 dir;
    const Vec02* up;
    InitScriptValue(&obj);
    if (args[2].tag == 0) {
        up = &g_unitZVector;
    } else {
        up = (const Vec02*)args[2].node->v;
    }
    dir = Vu0::Sub(Vu0::Q(*(Vec02*)args[1].v), Vu0::Q(*(Vec02*)args[0].v));
    f32* m = AcquireMatrixPayload();
    BuildBasisFromXAndZHint(&dir, (void*)up, m);
    ResetMatrixHomogeneous(m);
    SetScriptValueMatrix(&obj, m);
    CopyConstructScriptValue(ret, &obj);
    DestroyScriptValue(&obj, 2);
    return ret;
}

// What func_00189378 fills in for func_00188B08: 0x30 bytes.
struct UprightBasis {
    u8 bytes[0x30];         // 0x00
};

ScriptValue* MakeScriptUprightObjectMatrix(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    UprightBasis v;
    InitScriptValue(&t);
    f32* a = AcquireMatrixPayload();
    RotateMatrixUpright(args[0].p, 0, &v);
    BuildMatrixFromRotationAndTranslation((u8*)args[0].p + 0x30, &v, a);
    SetScriptValueMatrix(&t, a);
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

ScriptValue* EvalScriptQuadratic(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    ScriptValue v;
    InitScriptValue(&t);
    Vec3* k = (Vec3*)args[0].v;
    ConvertScriptValueToFloat(&v, args + 1);
    f32 x = v.f;
    f32 r = k->x + x * (k->y + x * k->z);
    SetScriptValueFloat(&t, r);
    DestroyScriptValue(&v, 2);
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

ScriptValue* EvalScriptClampedQuadratic(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    ScriptValue u;
    InitScriptValue(&t);
    f32* poly = args[0].v;
    f32* range = args[1].v;
    ConvertScriptValueToFloat(&u, args + 2);
    f32 k = u.f;
    f32 v = poly[0] + k * (poly[1] + k * poly[2]);
    f32 lo = range[0];
    f32 hi = range[1];
    if (v < lo) {
        v = lo;
    } else if (hi < v) {
        v = hi;
    }
    SetScriptValueFloat(&t, v);
    DestroyScriptValue(&u, 2);
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

ScriptValue* MakeScriptVector4FromFour(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q0;
    ScriptValue q1;
    ScriptValue q2;
    ScriptValue q3;
    ScriptValue q4;
    InitScriptValue(&q0);
    f32* p = AcquireVectorBPayload();
    ConvertScriptValueToFloat(&q1, args);
    f32 x = q1.f;
    ConvertScriptValueToFloat(&q2, args + 1);
    f32 y = q2.f;
    ConvertScriptValueToFloat(&q3, args + 2);
    f32 z = q3.f;
    ConvertScriptValueToFloat(&q4, args + 3);
    f32 w = q4.f;
    FitQuadraticCurve(p, x, y, z, w);
    DestroyScriptValue(&q4, 2);
    DestroyScriptValue(&q3, 2);
    DestroyScriptValue(&q2, 2);
    DestroyScriptValue(&q1, 2);
    SetScriptValueVectorB(&q0, p);
    CopyConstructScriptValue(ret, &q0);
    DestroyScriptValue(&q0, 2);
    return ret;
}

ScriptValue* ClampScriptToRange(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q0;
    ScriptValue q1;
    InitScriptValue(&q0);
    void* span = args[0].p;
    ConvertScriptValueToFloat(&q1, args + 1);
    f32 r = ClampToRange(span, q1.f);
    SetScriptValueFloat(&q0, r);
    DestroyScriptValue(&q1, 2);
    CopyConstructScriptValue(ret, &q0);
    DestroyScriptValue(&q0, 2);
    return ret;
}

ScriptValue* TestScriptInsideRange(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    ScriptValue v;
    InitScriptValue(&q);
    void* s1 = args[0].p;
    ConvertScriptValueToFloat(&v, &args[1]);
    s32 flag = IsInsideRange(s1, v.f);
    SetScriptValueBool(&q, flag);
    DestroyScriptValue(&v, 2);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* ConvertScriptFloatToInt(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    SetScriptValueInt(&q, (s32)args->f);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* RoundScriptFloatUp(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    InitScriptValue(&t);
    s32 n = (s32)(args->f + 1.0f);
    SetScriptValueInt(&t, n);
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

ScriptValue* RoundScriptFloat(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    InitScriptValue(&t);
    s32 n = (s32)(args->f + 0.5f);
    SetScriptValueInt(&t, n);
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

ScriptValue* TruncateScriptFloat(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    InitScriptValue(&t);
    s32 n = (s32)args->f;
    SetScriptValueInt(&t, n);
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

ScriptValue* GetScriptAbsolute(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    if (args->tag == 20) {
        s32 v = args->i; v = v < 0 ? -v : v;
        SetScriptValueInt(&q, v);
    } else {
        f32 v = args->f;
        if (v < 0.0f) {
            v = -v;
        }
        SetScriptValueFloat(&q, v);
    }
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* GetScriptMaximum(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    AssignScriptValue(&q, args);
    if (args[1].tag == 0) {
        args = 0;
    } else {
        args = args[1].node;
    }
    R11B008Node* x = (R11B008Node*)args;
    if (x != 0) {
        do {
            if (q.tag == 0x14) {
                if (x->tag == 0x14) {
                    if (q.i < x->i) {
                        AssignScriptValue(&q, x);
                    }
                } else {
                    if ((f32)q.i < x->f) {
                        AssignScriptValue(&q, x);
                    }
                }
            } else {
                if (x->tag == 0x14) {
                    if (q.f < (f32)x->i) {
                        AssignScriptValue(&q, x);
                    }
                } else {
                    f32 pf = x->f;
                    if (q.f < pf) {
                        AssignScriptValue(&q, x);
                    }
                }
            }
            x = x->next;
        } while (x != 0);
    }
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* GetScriptMinimum(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    AssignScriptValue(&q, args);
    if (args[1].tag == 0) {
        args = 0;
    } else {
        args = args[1].node;
    }
    R11B008Node* x = (R11B008Node*)args;
    if (x != 0) {
        do {
            if (q.tag == 0x14) {
                if (x->tag == 0x14) {
                    if (x->i < q.i) {
                        AssignScriptValue(&q, x);
                    }
                } else {
                    if (x->f < (f32)q.i) {
                        AssignScriptValue(&q, x);
                    }
                }
            } else {
                if (x->tag == 0x14) {
                    if ((f32)x->i < q.f) {
                        AssignScriptValue(&q, x);
                    }
                } else {
                    f32 pf = x->f;
                    if (pf < q.f) {
                        AssignScriptValue(&q, x);
                    }
                }
            }
            x = x->next;
        } while (x != 0);
    }
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* GetScriptRemainder(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    InitScriptValue(&t);
    s32 v = args[0].i % args[1].i;
    SetScriptValueInt(&t, v);
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

ScriptValue* GetScriptClock(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    SetScriptValueFloat(&q, g_gameTime);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* ScheduleScriptCall(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    ScriptValue r;
    InitScriptValue(&q);
    InitScriptValue(&r);
    R11B008Node* a = NewScriptValueNode();
    R11B008Node* b = NewScriptValueNode();
    R11B008Node* c = NewScriptValueNode();
    R11B008Node* d = NewScriptValueNode();
    R11B008Node* e;
    R11B008Node* f;
    e = NewScriptValueNode();
    f = NewScriptValueNode();
    SetScriptValueChain(a, b);
    ScriptValue t;
    ConvertScriptValueToFloat(&t, args);
    SetScriptValueFloat(b, t.f);
    DestroyScriptValue(&t, 2);
    b->next = c;
    SetScriptValueChain(c, d);
    SetScriptValueChain(d, e);
    SetScriptValueTag(e, 0x11);
    e->next = f;
    SetScriptValueRecord(f, args[1].rec);
    s32 idx = D_00259DE8;
    if (idx < count) {
        R11B008Node* n = args[idx].node;
        if (n) {
            R11B008Node* prev = d;
            do {
                d = NewScriptValueNode();
                e = NewScriptValueNode();
                SetScriptValueChain(d, e);
                SetScriptValueTag(e, 0x11);
                e->next = n;
                prev->next = d;
                R11B008Node* nx = n->next;
                n->next = 0;
                n = nx;
                prev = d;
            } while (n);
        }
    }
    LookupScriptVariable((ScriptScope*)g_currentWorld->f2C, g_currentWorld->f1EF8, 0, &r);
    if (r.tag == 0x1E) {
        a->next = r.node;
    }
    SetScriptValueChain(&r, a);
    AssignScriptVariable(&t, (ScriptScope*)g_currentWorld->f2C, g_currentWorld->f1EF8, &r);
    DestroyScriptValue(&t, 2);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&r, 2);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptObjectEventTimer(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    ScriptValue u;
    InitScriptValue(&t);
    PlacedObject* obj = (PlacedObject*)args[0].p;
    ConvertScriptValueToFloat(&u, args + 1);
    f32 f = u.f;
    DestroyScriptValue(&u, 2);
    obj->eventTimer = f;
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

ScriptValue* DispatchScriptObjectProperty(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope, s32 kind)
{
    ScriptValue q1;
    ScriptValue q2;

    InitScriptValue(&q1);
    s32 x1 = args[0].i;
    s32 x2 = args[1].i;
    switch (kind) {
    case 0x63:
        AddObjectProperty(&q2, x1, x2, &args[2]);
        AssignScriptValue(&q1, &q2);
        DestroyScriptValue(&q2, 2);
        break;
    case 0x64:
        SetExtraObjectProperty(&q2, x1, x2, &args[2]);
        AssignScriptValue(&q1, &q2);
        DestroyScriptValue(&q2, 2);
        break;
    case 0x65:
        UpdateObjectProperty(&q2, x1, x2, &args[2]);
        AssignScriptValue(&q1, &q2);
        DestroyScriptValue(&q2, 2);
        break;
    case 0x66:
        GetObjectProperty(&q2, x1, x2);
        AssignScriptValue(&q1, &q2);
        DestroyScriptValue(&q2, 2);
        break;
    }
    CopyConstructScriptValue(ret, &q1);
    DestroyScriptValue(&q1, 2);
    return ret;
}

ScriptValue* AddScriptObjectProperty(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    DispatchScriptObjectProperty(ret, count, args, scope, 0x63);
    return ret;
}

ScriptValue* SetScriptExtraObjectProperty(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    DispatchScriptObjectProperty(ret, count, args, scope, 0x64);
    return ret;
}

ScriptValue* UpdateScriptObjectProperty(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    DispatchScriptObjectProperty(ret, count, args, scope, 0x65);
    return ret;
}

ScriptValue* GetScriptObjectProperty(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    DispatchScriptObjectProperty(ret, count, args, scope, 0x66);
    return ret;
}

ScriptValue* MakeScriptRefList(ScriptValue* ret, s32 count, void** values)
{
    ScriptValue q;
    InitScriptValue(&q);
    if (count != 0) {
        R11B008Node* prev = 0;
        if (count > 0) {
            void** v = values;
            s32 n = count;
            do {
                R11B008Node* node = NewScriptValueNode();
                if (prev) {
                    prev->next = node;
                } else {
                    SetScriptValueChain(&q, node);
                }
                SetScriptValuePointerB(node, *v);
                prev = node;
                v++;
            } while (--n != 0);
        }
    } else {
        SetScriptValueTag(&q, 0);
    }
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* FindScriptObject(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    void* r;
    InitScriptValue(&q);
    s32 flag = 0x105;
    s32 k = 0x101;
    if (args[1].i != 0) flag = k;
    r = FindFirstObjectById(g_currentWorld, flag, args[0].i, args[1].i);
    SetScriptValuePointerB(&q, r);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* FindScriptObjectList(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    u8 buf[0x100];
    ScriptValue t;
    InitScriptValue(&q);
    s32 r = GatherObjectsByMode(g_currentWorld, args[1].i ? 0x101 : 0x105, args[0].i, args[1].p, 0x40, buf);
    MakeScriptRefList(&t, r, buf);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* FindScriptObjectById(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    void* r;
    InitScriptValue(&q);
    r = FindFirstObjectById(g_currentWorld, 0x104, args[0].i, args[1].i);
    SetScriptValuePointerB(&q, r);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* FindScriptObjectListById(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    u8 buf[0x100];
    ScriptValue t;
    InitScriptValue(&q);
    s32 r = GatherObjectsByMode(g_currentWorld, 0x104, args[0].i, args[1].p, 0x40, buf);
    MakeScriptRefList(&t, r, buf);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* GetScriptControlledObject(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    SetScriptValuePointerB(&q, GetActiveSwitchedCollider());
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* GetScriptWorld(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    SetScriptValuePointerB(&q, g_currentWorld);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* GetScriptCamera(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    SetScriptValuePointerB(&q, g_camera);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* GatherScriptObjectsById(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    u8 buf[0x400];
    ScriptValue t;
    InitScriptValue(&q);
    s32 r = GatherObjectsById(g_currentWorld, args[1].i ? 0x101 : 0x105, args[0].i, args[1].p, 0x100, buf);
    MakeScriptRefList(&t, r, buf);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

INCLUDE_ASM(func_00117FE0);

ScriptValue* FindScriptObjectsInSphere(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    ScriptValue t;
    s32 n;
    u8* list;
    f32 scale;
    InitScriptValue(&q);
    if (args[1].tag == 0x14) scale = (f32)args[1].i; else scale = args[1].f;
    PushBackMemoryMark();
    GatherCollidersInSphere(g_currentWorld, scale, 0, args[0].i, 0, 0, &n, &list);
    MakeScriptRefList(&t, n, list);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    PopBackMemoryMark();
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

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

RetValue SearchScriptObjectHits(s32 id, s32 count, ScriptValue* args, ScriptScope* scope)
{
    RetValue l0;
    ColliderSpan hit;
    void* slot;
    if (args[0].tag == 0) {
        AssignScriptValue(&l0, args);
    } else {
        s32 kind = 0x71;
        R11B008Node* head = 0;
        R11B008Node* tail;
        R11B008Node* it;
        for (it = args[0].node; it != 0; it = it->next) {
            ScriptValue* pa = &args[1];
            ScriptValue* pb = &args[2];
            R11B008Node* n1;
            R11B008Node* n2;
            R11B008Node* n3;
            Quad16* v;
            void* e = it->p;
            if (e == 0)
                continue;
            slot = e;
            if (FindNearestSpanObject(0, pa->i, pb->i, 1, &slot, &hit) == 0)
                continue;
            if (id == kind) {
                n1 = NewScriptValueNode();
                n2 = NewScriptValueNode();
                n3 = NewScriptValueNode();
                SetScriptValuePointerB(n1, e);
                n1->next = n2;
                v = (Quad16*)AcquireVectorAPayload();
                *v = hit.q[0];
                SetScriptValueVectorA(n2, (f32*)v);
                n2->next = n3;
                v = (Quad16*)AcquireVectorAPayload();
                *v = hit.q[1];
                SetScriptValueVectorA(n3, (f32*)v);
                n3 = NewScriptValueNode();
                SetScriptValueChain(n3, n1);
                if (head != 0)
                    tail->next = n3;
                else
                    head = n3;
                tail = n3;
            } else {
                n1 = NewScriptValueNode();
                n2 = NewScriptValueNode();
                SetScriptValuePointerB(n1, e);
                n1->next = n2;
                v = (Quad16*)AcquireVectorAPayload();
                *v = hit.q[1];
                SetScriptValueVectorA(n2, (f32*)v);
                SetScriptValueChain(&l0, n1);
                return l0;
            }
        }
        if (head != 0)
            SetScriptValueChain(&l0, head);
        else
            l0.tag = 0;
    }
    return l0;
}

ScriptValue* CollectScriptObjectHits(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    SearchScriptObjectHits(&t, 0x71, count, args, scope);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* FindScriptObjectHit(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    SearchScriptObjectHits(&t, 0x72, count, args, scope);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* TransformScriptPointBetweenFrames(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    InitScriptValue(&t);
    f32* p = AcquireVectorAPayload();
    TransformPointBetweenFrames(args[0].p, args[1].i, args[2].p, p);
    SetScriptValueVectorA(&t, p);
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

ScriptValue* TransformScriptDirectionBetweenFrames(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    InitScriptValue(&t);
    f32* p = AcquireVectorAPayload();
    TransformDirectionBetweenFrames(args[0].p, args[1].i, args[2].p, p);
    SetScriptValueVectorA(&t, p);
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

ScriptValue* TransformScriptRotationBetweenFrames(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    f32* obj;
    InitScriptValue(&q);
    obj = AcquireMatrixPayload();
    TransformRotationBetweenFrames(args[0].i, args[1].i, args[2].i, obj);
    ResetMatrixHomogeneous(obj);
    SetScriptValueMatrix(&q, obj);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* GetScriptPointAheadOfCamera(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue obj;
    Vec02 t;
    Vec02 k;
    InitScriptValue(&obj);
    f32* p = AcquireVectorAPayload();
    Camera* c = g_camera;
    Vu0::Q(k) = Vu0::FromFloatAt(c->f1E4);
    Vu0::Q(t) = Vu0::MulX(Vu0::Q(c->f80), Vu0::Q(k));
    Vu0::Q(*(Vec02*)p) = Vu0::Add(Vu0::Q(c->f40), Vu0::Q(t));
    SetScriptValueVectorA(&obj, p);
    CopyConstructScriptValue(ret, &obj);
    DestroyScriptValue(&obj, 2);
    return ret;
}

ScriptValue* StartScriptEffect(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    s32 n;
    InitScriptValue(&q);
    n = 0;
    StartSoundEffect(args[0].i, args[1].i ? &n : 0, args[1].i, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f);
    SetScriptValueInt(&q, n);
    if (n != 0) ClearSoundRecordHandle(&n);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* StopScriptEffect(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    InitScriptValue(&t);
    StopSoundRecord(args[0].p, 0);
    t.tag = 0x22;
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

ScriptValue* StartScriptPadRecordPattern(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    ScriptValue u;
    InitScriptValue(&t);
    void* p = g_padRecord;
    s32 n = args[0].i;
    ConvertScriptValueToFloat(&u, args + 1);
    StartPadRecordPattern(p, n, u.f);
    DestroyScriptValue(&u, 2);
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

ScriptValue* SendScriptPointEventToWorldListener(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    ScriptValue u;
    InitScriptValue(&t);
    void* s1 = args[0].p;
    ConvertScriptValueToFloat(&u, args + 1);
    SendPointEventToWorldListener(s1, u.f);
    DestroyScriptValue(&u, 2);
    SetScriptValueTag(&t, 0x22);
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

INCLUDE_ASM(func_00118988);

INCLUDE_ASM(func_00118CF0);

Quad_118D10* CopyQuadword(Quad_118D10* out, void* src)
{
    Quad_118D10 v = *(Quad_118D10*)src;
    *out = v;
    return out;
}

Quad_118D20* StoreQuadword(Quad_118D20* out, Quad_118D20 v)
{
    *out = v;
    return out;
}

ASM_FUNC(func_00118D30);

ScriptValue* EvalScriptVariable(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope)
{
    ScriptValue t;
    InitScriptValue(&t);
    LookupScriptVariable(scope, expr->i, 1, &t);
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

ScriptValue* EvalScriptAssign(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    R11B008Node* p = expr->node;
    R11B008Node* m = p->next;
    EvalScriptExpression(&t, m->next, scope);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AssignScriptVariable(&t, scope, m->i, &q);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* EvalScriptDefine(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    R11B008Node* p = expr->node;
    R11B008Node* m = p->next;
    EvalScriptExpression(&t, m->next, scope);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    DefineScriptVariable(&t, scope, m->i, &q);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

// The message func_00118F48 prints, kept as retail's bytes: retail places it on 16 bytes, 8 past
// where GCC puts the literal (the 8 zero bytes before it are not explained yet).
extern const char D_00249200[];
INCLUDE_RODATA(D_00249200);

ScriptValue* EvalScriptAssert(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    R11B008Node* a = expr->node;
    R11B008Node* b = a->next;
    R11B008Node* c = b->next;
    EvalScriptExpression(&t, b, scope);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    if (q.i == 0) {
        R11B008Node* v = c->node;
        R11B008Node* w = v->next;
        PrintFormatted(D_00249200);
        IgnoreScriptArgument(&t, 1, w, scope);
        DestroyScriptValue(&t, 2);
    }
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* EvalScriptIf(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope)
{
    ScriptValue q;
    ScriptValue t;
    R11B008Node* m;
    R11B008Node* n2;
    R11B008Node* n3;
    InitScriptValue(&q);
    m = expr->node->next;
    n2 = m->next;
    n3 = n2->next;
    EvalScriptExpression(&t, m, scope);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    if (q.i == 1) {
        EvalScriptExpression(&t, n2, scope);
        AssignScriptValue(&q, &t);
        DestroyScriptValue(&t, 2);
    } else if (n3 != 0) {
        EvalScriptExpression(&t, n3, scope);
        AssignScriptValue(&q, &t);
        DestroyScriptValue(&t, 2);
    } else {
        SetScriptValueTag(&q, 0x22);
    }
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* EvalScriptOr(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope)
{
    ScriptValue L;
    ScriptValue M;
    R11B008Node* n;

    InitScriptValue(&L);
    n = expr->node->next;
    if (n != 0) {
        do {
            EvalScriptExpression(&M, n, scope);
            AssignScriptValue(&L, &M);
            DestroyScriptValue(&M, 2);
            if (L.tag != 27 || L.i != 0) {
                CopyConstructScriptValue(ret, &L);
                DestroyScriptValue(&L, 2);
                goto done;
            }
            n = n->next;
        } while (n != 0);
    }
    SetScriptValueBool(&L, 0);
    CopyConstructScriptValue(ret, &L);
    DestroyScriptValue(&L, 2);
done:
    return ret;
}

RetValue EvalScriptAnd(R11B008Node* expr, ScriptScope* scope)
{
    RetValue L;
    SetScriptValueBool(&L, 1);
    for (R11B008Node* n = expr->node->next; n != 0; n = n->next) {
        ScriptValue t;
        EvalScriptExpression(&t, n, scope);
        AssignScriptValue(&L, &t);
        DestroyScriptValue(&t, 2);
        if (L.tag == 27 && L.i == 0)
            return L;
    }
    return L;
}

ScriptValue* EvalScriptCond(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope)
{
    ScriptValue q, r, t;
    InitScriptValue(&q);
    InitScriptValue(&r);
    SetScriptValueTag(&q, 0x22);
    R11B008Node* n = expr->node->next;
    while (n) {
        R11B008Node* e = n->node;
        s32 flag;
        if (e->tag == 10) {
            flag = 1;
        } else {
            EvalScriptExpression(&t, e, scope);
            flag = 0;
            AssignScriptValue(&r, &t);
            DestroyScriptValue(&t, 2);
            if (r.tag != 0x1B || r.i != 0)
                flag = 1;
            if (flag && e->next == 0)
                AssignScriptValue(&q, &r);
        }
        if (flag) {
            e = e->next;
            while (e) {
                EvalScriptExpression(&t, e, scope);
                AssignScriptValue(&q, &t);
                DestroyScriptValue(&t, 2);
                e = e->next;
            }
            n = 0;
        } else {
            n = n->next;
        }
    }
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&r, 2);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* EvalScriptCase(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope)
{
    ScriptValue a;
    ScriptValue b[2];
    ScriptValue c;
    ScriptValue d;
    InitScriptValue(&a);
    ScriptValue* p = b;
    for (s32 k = 1; k != -1; k--) {
        InitScriptValue(p);
        p++;
    }
    InitScriptValue(&c);
    SetScriptValueTag(&a, 0x22);
    R11B008Node* s0 = expr->node->next;
    EvalScriptExpression(&d, s0, scope);
    AssignScriptValue(&b[0], &d);
    DestroyScriptValue(&d, 2);
    expr = s0->next;
    if (expr) do {
        R11B008Node* e = expr->node;
        s32 found;
        if (e->tag == 10) {
            found = 1;
        } else {
            found = 0;
            R11B008Node* x = e->node;
            if (x) {
                do {
                    AssignScriptValue(&b[1], x);
                    TestScriptValuesIdentical(&d, 2, b, scope);
                    AssignScriptValue(&c, &d);
                    DestroyScriptValue(&d, 2);
                    if (c.tag == 0x1B && c.i != 0) {
                        found = 1;
                        x = 0;
                    } else {
                        x = x->next;
                    }
                } while (x);
            }
        }
        if (found) {
            e = e->next;
            if (e) {
                do {
                    EvalScriptExpression(&d, e, scope);
                    AssignScriptValue(&a, &d);
                    DestroyScriptValue(&d, 2);
                    e = e->next;
                } while (e);
            }
            expr = 0;
        } else {
            expr = expr->next;
        }
    } while (expr);
    CopyConstructScriptValue(ret, &a);
    DestroyScriptValue(&c, 2);
    ScriptValue* p2 = &c;
    if (b != p2) {
        do {
            p2--;
            DestroyScriptValue(p2, 0);
        } while (b != p2);
    }
    DestroyScriptValue(&a, 2);
    return ret;
}

ScriptValue* EvalScriptLet(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope)
{
    ScriptValue q, r, u, t;
    InitScriptValue(&q);
    InitScriptValue(&r);
    InitScriptValue(&u);
    R11B008Node* p = expr->node->next;
    ScriptScope* d;
    R11B008Node* n;
    if (p->tag == 0x1E) {
        d = NewScriptScope();
        R11B008Node* l = p->node;
        if (l) {
            do {
                R11B008Node* e = l->node;
                ScriptValue* pr = &r;
                EvalScriptExpression(&t, e->next, scope);
                AssignScriptValue(pr, &t);
                DestroyScriptValue(&t, 2);
                DefineScriptVariable(&t, d, e->i, pr);
                AssignScriptValue(&u, &t);
                DestroyScriptValue(&t, 2);
                l = l->next;
            } while (l);
        }
        SetScriptScopeParent(d, scope);
    } else {
        d = scope;
    }
    n = p->next;
    while (n) {
        EvalScriptExpression(&t, n, d);
        AssignScriptValue(&q, &t);
        DestroyScriptValue(&t, 2);
        n = n->next;
    }
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&u, 2);
    DestroyScriptValue(&r, 2);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* EvalScriptWhile(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope)
{
    ScriptValue q, t;
    s32 a, b;
    InitScriptValue(&q);
    R11B008Node* first = expr->node->next;
    R11B008Node* second = first->next;
    for (;;) {
        EvalScriptExpression(&t, first, scope);
        AssignScriptValue(&q, &t);
        DestroyScriptValue(&t, 2);
        a = q.tag;
        if (a != 0x1B)
            goto other;
        b = q.i;
        if (b != 0)
            goto other;
        break;
    other:
        EvalScriptExpression(&t, second, scope);
        AssignScriptValue(&q, &t);
        DestroyScriptValue(&t, 2);
    }
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* EvalScriptLambda(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    R11B008Node* first = expr->node->next;
    R11B008Node* after = first->next;
    R11AFC8* p = NewScriptValueRecord();
    p->w0 = (s32)scope;
    if (first->tag == 0)
        p->w4 = 0;
    else
        p->w4 = (s32)first->node;
    p->w10 = (s32)after;
    s32 found = 0;
    s32 count = 0;
    R11B008Node* n = (R11B008Node*)p->w4;
    while (n != 0) {
        if (n->tag == 0x13) {
            found = 1;
            n = 0;
        } else {
            n = n->next;
            count++;
        }
    }
    p->w8 = count;
    p->wC = found;
    SetScriptValueRecord(&q, p);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* EvalScriptBody(ScriptValue* ret, R11B008Node* list, ScriptScope* scope)
{
    ScriptValue q, t;
    InitScriptValue(&q);
    R11B008Node* n = list;
    do {
        EvalScriptExpression(&t, n, scope);
        AssignScriptValue(&q, &t);
        DestroyScriptValue(&t, 2);
        n = n->next;
    } while (n);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* EvalScriptSequence(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope)
{
    ScriptValue q, t;
    InitScriptValue(&q);
    SetScriptValueTag(&q, 0x22);
    R11B008Node* n = expr->node->next;
    while (n != 0) {
        EvalScriptExpression(&t, n, scope);
        AssignScriptValue(&q, &t);
        DestroyScriptValue(&t, 2);
        n = n->next;
    }
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* EvalScriptCall(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope)
{
    R11B008Node* node;
    ScriptValue a;
    ScriptValue b;
    ScriptValue arr[32];
    ScriptValue t;
    ScriptValue u;
    s32 total;
    ScriptBuiltin* ent;
    ScriptHostCall* host;
    R11AFC8* d;
    s32 n;
    s32 last;
    s32 count;
    s32 i;
    ScriptValue* p;

    InitScriptValue(&a);
    InitScriptValue(&b);
    p = arr;
    for (s32 k = 31; k != -1; k--) {
        InitScriptValue(p);
        p++;
    }
    R11B008Node* first = expr->node;
    EvalScriptExpression(&t, first, scope);
    AssignScriptValue(&a, &t);
    DestroyScriptValue(&t, 2);
    if (a.tag == 0x1D) {
        ent = &g_scriptBuiltins[a.i];
        n = ent->count;
        last = ent->rest;
    } else if (a.tag == 0x21) {
        host = (ScriptHostCall*)a.p;
        last = 0;
        n = host->count;
    } else {
        d = a.rec;
        n = d->w8;
        last = d->wC;
    }
    node = first->next;
    total = n + (last != 0);
    count = n;
    for (i = 0; i < n; i++) {
        ScriptValue* bp = &b;
        EvalScriptExpression(&t, node, scope);
        AssignScriptValue(bp, &t);
        DestroyScriptValue(&t, 2);
        AssignScriptValue(&arr[i], bp);
        node = node->next;
    }
    if (last) {
        R11B008Node* tail = 0;
        R11B008Node* head = 0;
        R11B008Node* m;
        for (m = node; m; m = m->next) {
            R11B008Node* e = NewScriptValueNode();
            EvalScriptExpression(&t, m, scope);
            AssignScriptValue(e, &t);
            DestroyScriptValue(&t, 2);
            if (tail) {
                tail->next = e;
                tail = e;
            } else {
                tail = e;
                head = e;
            }
            count++;
        }
        if (head) {
            SetScriptValueChain(&arr[i], head);
        } else {
            SetScriptValueTag(&arr[i], 0);
        }
    }
    switch (a.tag) {
    case 0x1D:
        ent->fn(&t, count, arr, scope);
        AssignScriptValue(&b, &t);
        DestroyScriptValue(&t, 2);
        break;
    case 0x1F: {
        d = a.rec;
        ScriptScope* s = NewScriptScope();
        SetScriptScopeParent(s, (ScriptScope*)d->w0);
        R11B008Node* q = (R11B008Node*)d->w4;
        for (i = 0; i < total; i++) {
            InitScriptValue(&t);
            if (0x13 == q->tag) {
                q = q->next;
            }
            DefineScriptVariable(&u, s, q->i, &arr[i]);
            AssignScriptValue(&t, &u);
            DestroyScriptValue(&u, 2);
            q = q->next;
            DestroyScriptValue(&t, 2);
        }
        EvalScriptBody(&t, (R11B008Node*)d->w10, s);
        AssignScriptValue(&b, &t);
        DestroyScriptValue(&t, 2);
        break;
    }
    case 0x21:
        host->fn(&t, host->self, count, arr);
        AssignScriptValue(&b, &t);
        DestroyScriptValue(&t, 2);
        break;
    }
    CopyConstructScriptValue(ret, &b);
    p = &t;
    while (arr != p) {
        p--;
        DestroyScriptValue(p, 0);
    }
    DestroyScriptValue(&b, 2);
    DestroyScriptValue(&a, 2);
    return ret;
}

ScriptValue* EvalScriptImportScope(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope)
{
    ScriptValue a;
    ScriptValue b;
    ScriptScope* found;
    s32 id;

    InitScriptValue(&a);
    id = expr->node->next->i;
    found = GetScriptEntryScope(id, (u8*)g_currentWorld);
    if (found == 0) {
        EvalScriptEntry(&b, id, (u8*)g_currentWorld);
        AssignScriptValue(&a, &b);
        DestroyScriptValue(&b, 2);
        found = GetScriptEntryScope(id, (u8*)g_currentWorld);
    }
    AddScriptScopeParent(scope, found);
    SetScriptValueTag(&a, 0x22);
    CopyConstructScriptValue(ret, &a);
    DestroyScriptValue(&a, 2);
    return ret;
}

ScriptValue* EvalScriptExpression(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope)
{
    ScriptValue t;
    ScriptValue u;
    ScriptValue* src;
    R11B008Node* p;
    InitScriptValue(&t);
    switch (expr->tag) {
    case 0:
    case 20: case 21: case 22: case 23: case 24: case 25: case 26: case 27:
    case 29:
    case 32: case 33:
        src = expr;
        goto copy;
    case 28:
        EvalScriptVariable(&u, expr, scope);
        goto tail;
    case 30:
        p = expr->node;
        switch (p->tag) {
        case 1: EvalScriptAssign(&u, expr, scope); goto tail;
        case 2: EvalScriptDefine(&u, expr, scope); goto tail;
        case 5: EvalScriptAssert(&u, expr, scope); goto tail;
        case 6: EvalScriptIf(&u, expr, scope); goto tail;
        case 7: EvalScriptOr(&u, expr, scope); goto tail;
        case 8: EvalScriptAnd(&u, expr, scope); goto tail;
        case 9: EvalScriptCond(&u, expr, scope); goto tail;
        case 11: EvalScriptCase(&u, expr, scope); goto tail;
        case 12: EvalScriptLet(&u, expr, scope); goto tail;
        case 13: EvalScriptWhile(&u, expr, scope); goto tail;
        case 15: EvalScriptSequence(&u, expr, scope); goto tail;
        case 14: EvalScriptLambda(&u, expr, scope); goto tail;
        case 17:
            src = p->next;
        copy:
            AssignScriptValue(&t, src);
            goto end;
        case 16:
            EvalScriptImportScope(&u, expr, scope);
        tail:
            AssignScriptValue(&t, &u);
            DestroyScriptValue(&u, 2);
            goto end;
        default:
            EvalScriptCall(&u, expr, scope);
            AssignScriptValue(&t, &u);
            DestroyScriptValue(&u, 2);
            break;
        }
        break;
    default:
        break;
    }
end:
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

void SetScriptScopeParent(ScriptScope* scope, ScriptScope* parent)
{
    scope->parents[0] = parent;
    scope->count = 1;
}

void AddScriptScopeParent(ScriptScope* scope, ScriptScope* parent)
{
    scope->parents[scope->count++] = parent;
}

ScriptValue* DefineScriptVariable(ScriptValue* ret, ScriptScope* scope, s32 key, ScriptValue* value)
{
    ScriptValue a;
    R11B008Key* node;

    InitScriptValue(&a);
    node = NewKeyedValue();
    node->key = key;
    AssignScriptValue(&node->value, value);
    node->next = scope->head;
    scope->head = node;
    SetScriptValueTag(&a, 0x22);
    CopyConstructScriptValue(ret, &a);
    DestroyScriptValue(&a, 2);
    return ret;
}

ScriptValue* AssignScriptVariable(ScriptValue* ret, ScriptScope* scope, s32 key, ScriptValue* value)
{
    ScriptValue a;
    ScriptValue* found;

    InitScriptValue(&a);
    found = FindScriptVariable(scope, key, 1);
    if (found != 0) {
        AssignScriptValue(found, value);
    }
    SetScriptValueTag(&a, 0x22);
    CopyConstructScriptValue(ret, &a);
    DestroyScriptValue(&a, 2);
    return ret;
}

s32 LookupScriptVariable(ScriptScope* scope, s32 key, s32 flag, ScriptValue* out)
{
    ScriptValue* r = FindScriptVariable(scope, key, flag);
    if (r != 0) {
        if (out)
            AssignScriptValue(out, r);
        return 1;
    }
    return 0;
}

ScriptValue* FindScriptVariable(ScriptScope* scope, s32 key, s32 flag)
{
    ScriptValue* found = 0;
    R11B008Key* n;
    s32 i;

    scope->busy = 1;
    for (n = scope->head; n != 0; n = n->next) {
        if (n->key == key) {
            found = &n->value;
            goto done;
        }
    }
    if (flag != 0) {
        for (i = 0; i < scope->count; i++) {
            ScriptScope* c = scope->parents[i];
            if (c->busy == 0) {
                found = FindScriptVariable(c, key, flag);
                if (found != 0)
                    goto done;
            }
        }
    }
done:
    scope->busy = 0;
    return found;
}

void CopyScriptScope(ScriptScope* src, ScriptScope* dst)
{
    dst->count = src->count;
    CopyMemory(dst->parents, src->parents, src->count * 4);
    if (src->head != 0) {
        R11B008Key* n = NewKeyedValue();
        CopyKeyedValueChain(src->head, n, (s32)dst);
        dst->head = n;
    }
}

ScriptScope* NewScriptScope(void)
{
    ScriptScope* p = (ScriptScope*)TakePoolEntry(g_scopePool);
    FillMemory(p, 0, 0x1C);
    return p;
}
void ReleaseScriptScope(void)
{
}

MarkStacks::MarkStacks()
{
}

MarkStacks::~MarkStacks()
{
}

void ResetMarkRoots(MarkStacks* self)
{
    self->rootCount = 0;
    self->listCount = 0;
}

void ShutDownMarkRoots() {}

void AddUniqueMarkRoot(MarkStacks* self, MarkEntry* value)
{
    for (int i = 0; i < self->rootCount; i++)
        if (self->roots[i] == value)
            return;
    self->roots[self->rootCount++] = value;
}

void AddMarkRootList(MarkStacks* self, R11B008List* list) { self->lists[self->listCount++] = list; }

void PushMarkObject(MarkStacks* self, MarkEntry* value) { self->objects[self->objectCount++] = value; }

MarkEntry* PopMarkObject(MarkStacks* self)
{
    if (self->objectCount > 0)
        return self->objects[--self->objectCount];
    return 0;
}

void PushMarkChain(MarkStacks* self, MarkEntry* value) { self->chains[self->chainCount++] = value; }

MarkEntry* PopMarkChain(MarkStacks* self)
{
    if (self->chainCount > 0) {
        s32 n = self->chainCount - 1;
        self->chainCount = n;
        return self->chains[n];
    }
    return 0;
}

void PushMarkRecord(MarkStacks* self, MarkRecord* value)
{
    s32 n = self->recordCount;
    self->records[n] = value;
    self->recordCount = n + 1;
}

MarkRecord* PopMarkRecord(MarkStacks* self)
{
    s32 n = self->recordCount;
    if (n > 0) {
        n = n - 1;
        self->recordCount = n;
        return self->records[n];
    }
    return 0;
}

void MarkPoolLiveEnds(void)
{
    MarkPoolLiveEnd(g_valueNodePool);
    MarkPoolLiveEnd(g_scopePool);
    MarkPoolLiveEnd(g_keyedValuePool);
    MarkPoolLiveEnd(g_payloadPool);
    MarkPoolLiveEnd(g_propertyRefPool);
}

void DrainMarkStacks(MarkStacks* self)
{
    MarkEntry* obj;
    MarkEntry* other;
    MarkEntry* group;
    for (;;) {
        group = PopMarkObject(self);
        if (group) {
            MarkEntry* link = group->f14;
            if (link) {
                do {
                    MarkPoolEntryUsed(link);
                    MarkEntry* ev = (MarkEntry*)&link->f4;
                    switch (ev->f0) {
                    case 0x1E:
                        obj = ev->f4;
                        if (IsPoolEntryUnmarked(obj)) {
                            MarkPoolEntryUsed(obj);
                            PushMarkChain(self, obj);
                        }
                        break;
                    case 0x1F:
                        other = ev->f4;
                        if (IsPoolEntryUnmarked(other)) {
                            MarkPoolEntryUsed(other);
                            PushMarkRecord(self, (MarkRecord*)other);
                        }
                        break;
                    case 0x21:
                        MarkPoolEntryUsed(ev->f4);
                        break;
                    }
                    link = link->fC;
                } while (link);
            }
            if (group->f0 > 0) {
                s32 i = 0;
                MarkEntry** p = &group->f4;
                do {
                    obj = *p;
                    if (IsPoolEntryUnmarked(obj)) {
                        MarkPoolEntryUsed(obj);
                        PushMarkObject(self, obj);
                    }
                    i++;
                    p++;
                } while (i < group->f0);
            }
            continue;
        }
        MarkRecord* b = PopMarkRecord(self);
        if (b) {
            obj = b->f4;
            if (obj) {
                do {
                    MarkPoolEntryUsed(obj);
                    obj = obj->f8;
                } while (obj);
            }
            obj = b->f10;
            if (IsPoolEntryUnmarked(obj)) {
                MarkPoolEntryUsed(obj);
                PushMarkChain(self, obj);
            }
            group = b->f0;
            if (IsPoolEntryUnmarked(group)) {
                MarkPoolEntryUsed(group);
                PushMarkObject(self, group);
            }
            continue;
        }
        obj = PopMarkChain(self);
        if (!obj)
            return;
        switch (obj->f0) {
        case 0x1E:
            other = obj->f4;
            if (IsPoolEntryUnmarked(other)) {
                MarkPoolEntryUsed(other);
                PushMarkChain(self, other);
            }
            break;
        case 0x1F:
            other = obj->f4;
            if (IsPoolEntryUnmarked(other)) {
                MarkPoolEntryUsed(other);
                PushMarkRecord(self, (MarkRecord*)other);
            }
            break;
        case 0x21:
            MarkPoolEntryUsed(obj->f4);
            break;
        }
        obj = obj->f8;
        if (obj) {
            if (IsPoolEntryUnmarked(obj)) {
                MarkPoolEntryUsed(obj);
                PushMarkChain(self, obj);
            }
        }
    }
}

void CollectScriptPools(MarkStacks* w) {
    ClearPoolLiveStates(g_valueNodePool);
    ClearPoolLiveStates(g_scopePool);
    ClearPoolLiveStates(g_keyedValuePool);
    ClearPoolLiveStates(g_payloadPool);
    ClearPoolLiveStates(g_propertyRefPool);
    s32 i = w->rootCount;
    w->objectCount = 0;
    w->chainCount = 0;
    w->recordCount = 0;
    for (i--; i >= 0; i--) {
        MarkEntry* e = w->roots[i];
        if (IsPoolEntryUnmarked(e)) {
            MarkPoolEntryUsed(e);
            PushMarkObject(w, e);
        }
    }
    s32 j = w->listCount;
    for (j--; j >= 0; j--) {
        R11B008Key* n = w->lists[j]->head;
        while (n) {
            MarkPoolEntryUsed((MarkEntry*)n);
            ScriptValue* sp = &n->value;
            switch (sp->tag) {
            case 0x1E: {
                MarkEntry* e = (MarkEntry*)sp->p;
                if (IsPoolEntryUnmarked(e)) {
                    MarkPoolEntryUsed(e);
                    PushMarkChain(w, e);
                }
                break;
            }
            case 0x1F: {
                MarkEntry* e = (MarkEntry*)sp->p;
                if (IsPoolEntryUnmarked(e)) {
                    MarkPoolEntryUsed(e);
                    PushMarkRecord(w, (MarkRecord*)e);
                }
                break;
            }
            case 0x21:
                MarkPoolEntryUsed((MarkEntry*)sp->p);
                break;
            }
            n = n->next;
        }
    }
    for (QueuedCall* it = (QueuedCall*)g_currentWorld->f1EC8; it; it = it->next) {
        if ((void*)it->fn == (void*)RunScriptEventHandler) {
            MarkEntry* e = (MarkEntry*)it->p0C;
            if (e && IsPoolEntryUnmarked(e)) {
                MarkPoolEntryUsed(e);
                PushMarkChain(w, e);
            }
        }
    }
    DrainMarkStacks(w);
    ReleaseDeadPoolEntries(g_valueNodePool);
    ReleaseDeadPoolEntries(g_scopePool);
    ReleaseDeadPoolEntries(g_keyedValuePool);
    ReleaseDeadPoolEntries(g_payloadPool);
    ReleaseDeadPoolEntries(g_propertyRefPool);
}
