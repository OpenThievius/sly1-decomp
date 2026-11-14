// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "vu0.h"
#include "entry_pool.h"
#include "asm_func.h"
#include "vu0.h"
#include "world.h"
#include "globals.h"
#include "shapes.h"
#include "collider.h"
#include "script_value.h"
#include "script_builtin.h"
#include "queued_call.h"
#include "aim_blend_grid.h"
#include "vu0.h"
#include "object_finder.h"
#include "functions/base_object.h"
#include "functions/effect_spawner.h"
#include "functions/pad_input.h"
#include "functions/placed_object.h"
#include "functions/random.h"
#include "functions/sound_system.h"
#include "functions/switched_collider.h"
#include "functions/text_format.h"
#include "functions/warp_menu.h"
#include "functions/world.h"
struct HomogeneousMatrix;

struct BaseObject;


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
    s32 tag;                // 0x00
    MarkEntry* payload;     // 0x04
    MarkEntry* next;        // 0x08
    MarkEntry* nextKeyed;   // 0x0C
    MarkEntry* f10;         // 0x10
    MarkEntry* keyedChain;  // 0x14
};

// A tag 0x1F payload as the collector reads it: a scope, a chain of nodes and a third entry.
struct MarkRecord {
    MarkEntry* scope;       // 0x00
    MarkEntry* nodes;       // 0x04
    s32 f8;                 // 0x08
    s32 fC;                 // 0x0C
    MarkEntry* thirdEntry;  // 0x10
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
void BuildBasisFromXAndZHint(const Vec02* x, const Vec02* hint, Mat02* out);
extern EntryPool g_valueNodePool;
extern EntryPool g_scopePool;
extern EntryPool g_keyedValuePool;
extern EntryPool g_payloadPool;
extern EntryPool g_propertyRefPool;
void* TakePoolEntry(EntryPool* self);
void MarkPoolLiveEnd(EntryPool* self);
void ClearPoolLiveStates(EntryPool* self);
void ReleaseDeadPoolEntries(EntryPool* self);

extern "C" void* FillMemory(void* p, s32 value, s32 size);
void CopyMemory(void* dst, void* src, u32 size);

// Other files' functions the built-ins call.
extern "C" f32 ArctangentOfRatio(f32 y, f32 x);
struct ValueRange;
void CopyTransposedMatrix(Quad16* src, Quad16* dst);
void* InvertMatrix4x4(void* a0, void* a1);
void TransformMatrixByObject(u8* self, void* arg, Quad16* out);
void MatrixToEulerAngles(Mat4* self, Vec3* out);
void MatrixToAxisAngle(Mat02* m, f32* angle, Vec02* axis);
void RotateMatrixUpright(Mat02* self, Mat02* scratch, Mat02* out);
void BuildMatrixFromRotationAndTranslation(const Vec02* pos, const Mat02* rot, Mat4A* out);
void ResetMatrixHomogeneous(HomogeneousMatrix* self);
ScriptValue* UpdateObjectProperty(ScriptValue* self, BaseObject* p, s32 key, ScriptValue* value);
ScriptValue* SetExtraObjectProperty(ScriptValue* self, BaseObject* p, s32 key, ScriptValue* value);
ScriptValue* AddObjectProperty(ScriptValue* self, BaseObject* p, s32 key, ScriptValue* value);
ScriptValue* GetObjectProperty(ScriptValue* self, BaseObject* p, s32 n);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
struct PlayingSound;
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);
ScriptValue* EvalScriptEntry(ScriptValue* self, s32 index, World* ctx);
ScriptScope* GetScriptEntryScope(s32 index, World* self);

extern f32 g_gameTime;
extern u8 g_padRecord[];

// The table's records (script_builtin.h): D_00259DE8 is the count word of the last record of the first
// label (func_00117668's, 0x259DE4), the one word func_00117668 reads.
extern ScriptBuiltin g_scriptBuiltins[];
extern s32 D_00259DE8;

// The collector's calls on the pooled entries (value_pools.cpp).
s32 IsPoolEntryUnmarked(void* payload);
void MarkPoolEntryUsed(void* payload);

s32 FindNearestSpanObject(s32 flags, Vec02* a1, Vec02* a2, s32 count, Collider** list, ColliderSpan* out);

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
void MakeScriptRefList(ScriptValue* ret, s32 count, u8* values); // stays void: retail returns a ScriptValue by value through the hidden pointer, a call with no value register, which a pointer return changes in func_00117C48, func_00117D78 and func_00117F28
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

u128* CopyQuadword(u128* out, void* src);
u128* StoreQuadword(u128* out, u128 v);

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
void ShutDownMarkRoots(MarkStacks* stacks);
void AddUniqueMarkRoot(MarkStacks* self, MarkEntry* value);
void AddMarkRootList(MarkStacks* self, R11B008List* list);
void PushMarkObject(MarkStacks* self, MarkEntry* value);
MarkEntry* PopMarkObject(MarkStacks* self);
void PushMarkChain(MarkStacks* self, MarkEntry* value);
MarkEntry* PopMarkChain(MarkStacks* self);
void PushMarkRecord(MarkStacks* self, MarkRecord* value);
MarkRecord* PopMarkRecord(MarkStacks* self);
void MarkPoolLiveEnds(MarkStacks* stacks);
void DrainMarkStacks(MarkStacks* self);
void CollectScriptPools(MarkStacks* self);

// Tables of functions this file's code reads: the math functions of func_00115CA0.
extern "C" f32 Arctangent(f32 x);
extern "C" f32 Cosine(f32 x);
extern "C" f32 Sine(f32 x);
extern "C" f32 Tangent(f32 x);
extern "C" f32 Arccosine(f32 x);
extern "C" f32 Arcsine(f32 x);
extern "C" f32 SquareRoot(f32 x);
MathFn_259938 g_scriptMathFunctions[8] = { SquareRoot, Sine, Cosine, Tangent, Arcsine, Arccosine, Arctangent, WrapAngle };
// The built-ins not matched yet (INCLUDE_ASM below) have the built-in signature.
ScriptValue* AddScriptValues(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* SubtractScriptValues(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* MultiplyScriptValues(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* DivideScriptValues(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* AppendScriptLists(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* GetScriptDotProduct(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* GetScriptCrossProduct(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* GetScriptVectorLength(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* GetScriptDistance(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* GetScriptDistanceSquared(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* NormalizeScriptVector(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* ProjectScriptVector(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* RemoveScriptVectorComponent(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* InterpolateScriptRotation(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* MakeScriptDirectionMatrix(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* FindScriptObjectsInBox(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* GetScriptPointAheadOfCamera(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptValue* SampleScriptAnimation(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope);
ScriptBuiltin g_scriptBuiltins[125] = {
    { (ScriptBuiltinFn)AddScriptValues, 1, 1 },
    { (ScriptBuiltinFn)SubtractScriptValues, 1, 1 },
    { (ScriptBuiltinFn)MultiplyScriptValues, 1, 1 },
    { (ScriptBuiltinFn)DivideScriptValues, 1, 1 },
    { (ScriptBuiltinFn)IgnoreScriptArgument, 1, 0 },
    { (ScriptBuiltinFn)IgnoreScriptArguments, 0, 1 },
    { (ScriptBuiltinFn)DiscardScriptArgument, 1, 0 },
    { (ScriptBuiltinFn)TestScriptWordsEqual, 2, 0 },
    { (ScriptBuiltinFn)TestScriptLess, 2, 0 },
    { (ScriptBuiltinFn)TestScriptLessOrEqual, 2, 0 },
    { (ScriptBuiltinFn)TestScriptGreater, 2, 0 },
    { (ScriptBuiltinFn)TestScriptGreaterOrEqual, 2, 0 },
    { (ScriptBuiltinFn)TestScriptValuesIdentical, 2, 0 },
    { (ScriptBuiltinFn)TestScriptEqual, 2, 0 },
    { (ScriptBuiltinFn)IsScriptBool, 1, 0 },
    { (ScriptBuiltinFn)IsScriptNumber, 1, 0 },
    { (ScriptBuiltinFn)IsScriptInt, 1, 0 },
    { (ScriptBuiltinFn)IsScriptFloat, 1, 0 },
    { (ScriptBuiltinFn)IsScriptPointer, 1, 0 },
    { (ScriptBuiltinFn)IsScriptVector, 1, 0 },
    { (ScriptBuiltinFn)IsScriptMatrix, 1, 0 },
    { (ScriptBuiltinFn)IsScriptVector4, 1, 0 },
    { (ScriptBuiltinFn)IsScriptFloatPair, 1, 0 },
    { (ScriptBuiltinFn)IsScriptFloatTriple, 1, 0 },
    { (ScriptBuiltinFn)IsScriptList, 1, 0 },
    { (ScriptBuiltinFn)IsScriptEmptyList, 1, 0 },
    { (ScriptBuiltinFn)IsScriptRef, 1, 0 },
    { (ScriptBuiltinFn)IsScriptNullRef, 1, 0 },
    { (ScriptBuiltinFn)IsScriptHostFunction, 1, 0 },
    { (ScriptBuiltinFn)IsScriptFunction, 1, 0 },
    { (ScriptBuiltinFn)TestScriptNearlyEqual, 3, 0 },
    { (ScriptBuiltinFn)IsScriptFalse, 1, 0 },
    { (ScriptBuiltinFn)PrependScriptListItem, 2, 0 },
    { (ScriptBuiltinFn)GetScriptListHead, 1, 0 },
    { (ScriptBuiltinFn)GetScriptListTail, 1, 0 },
    { (ScriptBuiltinFn)SetScriptListHead, 2, 0 },
    { (ScriptBuiltinFn)SetScriptListTail, 2, 0 },
    { (ScriptBuiltinFn)GetScriptListLength, 1, 0 },
    { (ScriptBuiltinFn)GetScriptListItem, 2, 0 },
    { (ScriptBuiltinFn)TestScriptListContains, 2, 0 },
    { (ScriptBuiltinFn)ReturnScriptArgument, 0, 1 },
    { (ScriptBuiltinFn)AppendScriptLists, 0, 1 },
    { (ScriptBuiltinFn)MapScriptList, 2, 0 },
    { (ScriptBuiltinFn)FilterScriptList, 2, 0 },
    { (ScriptBuiltinFn)ForEachScriptListItem, 2, 0 },
    { (ScriptBuiltinFn)EvalScriptArgument, 1, 0 },
    { (ScriptBuiltinFn)MakeScriptVector, 3, 0 },
    { (ScriptBuiltinFn)MakeScriptMatrix, 0, 1 },
    { (ScriptBuiltinFn)MakeScriptVector4FromThree, 3, 0 },
    { (ScriptBuiltinFn)MakeScriptFloatPair, 2, 0 },
    { (ScriptBuiltinFn)MakeScriptFloatTriple, 3, 0 },
    { (ScriptBuiltinFn)GetScriptVectorElement, 1, 1 },
    { (ScriptBuiltinFn)SetScriptRandomSeed, 1, 0 },
    { (ScriptBuiltinFn)GetScriptRandomFloat, 2, 0 },
    { (ScriptBuiltinFn)GetScriptSquareRoot, 1, 0 },
    { (ScriptBuiltinFn)GetScriptSine, 1, 0 },
    { (ScriptBuiltinFn)GetScriptCosine, 1, 0 },
    { (ScriptBuiltinFn)GetScriptTangent, 1, 0 },
    { (ScriptBuiltinFn)GetScriptArcSine, 1, 0 },
    { (ScriptBuiltinFn)GetScriptArcCosine, 1, 0 },
    { (ScriptBuiltinFn)GetScriptArcTangent, 1, 0 },
    { (ScriptBuiltinFn)WrapScriptAngle, 1, 0 },
    { (ScriptBuiltinFn)GetScriptAtan2, 2, 0 },
    { (ScriptBuiltinFn)GetScriptDotProduct, 2, 0 },
    { (ScriptBuiltinFn)GetScriptCrossProduct, 2, 0 },
    { (ScriptBuiltinFn)GetScriptVectorLength, 1, 0 },
    { (ScriptBuiltinFn)GetScriptDistance, 1, 1 },
    { (ScriptBuiltinFn)GetScriptDistanceSquared, 1, 1 },
    { (ScriptBuiltinFn)NormalizeScriptVector, 1, 1 },
    { (ScriptBuiltinFn)ProjectScriptVector, 2, 0 },
    { (ScriptBuiltinFn)RemoveScriptVectorComponent, 2, 0 },
    { (ScriptBuiltinFn)GetScriptBallisticVelocity, 3, 1 },
    { (ScriptBuiltinFn)GetScriptAngleAndAxis, 2, 0 },
    { (ScriptBuiltinFn)TransposeScriptMatrix, 1, 0 },
    { (ScriptBuiltinFn)InvertScriptMatrix, 1, 0 },
    { (ScriptBuiltinFn)TransformScriptMatrixByObject, 2, 0 },
    { (ScriptBuiltinFn)InterpolateScriptRotation, 3, 0 },
    { (ScriptBuiltinFn)GetScriptMatrixTranslation, 1, 0 },
    { (ScriptBuiltinFn)GetScriptMatrixRotation, 1, 0 },
    { (ScriptBuiltinFn)GetScriptMatrixEuler, 1, 0 },
    { (ScriptBuiltinFn)GetScriptMatrixAxisAngle, 1, 0 },
    { (ScriptBuiltinFn)MakeScriptDirectionMatrix, 2, 1 },
    { (ScriptBuiltinFn)MakeScriptUprightObjectMatrix, 1, 0 },
    { (ScriptBuiltinFn)EvalScriptQuadratic, 2, 0 },
    { (ScriptBuiltinFn)EvalScriptClampedQuadratic, 3, 0 },
    { (ScriptBuiltinFn)MakeScriptVector4FromFour, 4, 0 },
    { (ScriptBuiltinFn)ClampScriptToRange, 2, 0 },
    { (ScriptBuiltinFn)TestScriptInsideRange, 2, 0 },
    { (ScriptBuiltinFn)ConvertScriptFloatToInt, 1, 0 },
    { (ScriptBuiltinFn)RoundScriptFloatUp, 1, 0 },
    { (ScriptBuiltinFn)RoundScriptFloat, 1, 0 },
    { (ScriptBuiltinFn)TruncateScriptFloat, 1, 0 },
    { (ScriptBuiltinFn)GetScriptAbsolute, 1, 0 },
    { (ScriptBuiltinFn)GetScriptMaximum, 1, 1 },
    { (ScriptBuiltinFn)GetScriptMinimum, 1, 1 },
    { (ScriptBuiltinFn)GetScriptRemainder, 2, 0 },
    { (ScriptBuiltinFn)GetScriptClock, 0, 0 },
    { (ScriptBuiltinFn)ScheduleScriptCall, 2, 1 },
    { (ScriptBuiltinFn)SetScriptObjectEventTimer, 2, 0 },
    { (ScriptBuiltinFn)AddScriptObjectProperty, 3, 0 },
    { (ScriptBuiltinFn)SetScriptExtraObjectProperty, 3, 0 },
    { (ScriptBuiltinFn)UpdateScriptObjectProperty, 3, 0 },
    { (ScriptBuiltinFn)GetScriptObjectProperty, 2, 0 },
    { (ScriptBuiltinFn)FindScriptObject, 2, 0 },
    { (ScriptBuiltinFn)FindScriptObjectList, 2, 0 },
    { (ScriptBuiltinFn)FindScriptObjectById, 2, 0 },
    { (ScriptBuiltinFn)FindScriptObjectListById, 2, 0 },
    { (ScriptBuiltinFn)GetScriptControlledObject, 0, 0 },
    { (ScriptBuiltinFn)GetScriptWorld, 0, 0 },
    { (ScriptBuiltinFn)GetScriptCamera, 0, 0 },
    { (ScriptBuiltinFn)GatherScriptObjectsById, 2, 0 },
    { (ScriptBuiltinFn)FindScriptObjectsInBox, 2, 0 },
    { (ScriptBuiltinFn)FindScriptObjectsInSphere, 2, 0 },
    { (ScriptBuiltinFn)CollectScriptObjectHits, 3, 0 },
    { (ScriptBuiltinFn)FindScriptObjectHit, 3, 0 },
    { (ScriptBuiltinFn)TransformScriptPointBetweenFrames, 3, 0 },
    { (ScriptBuiltinFn)TransformScriptDirectionBetweenFrames, 3, 0 },
    { (ScriptBuiltinFn)TransformScriptRotationBetweenFrames, 3, 0 },
    { (ScriptBuiltinFn)GetScriptPointAheadOfCamera, 0, 0 },
    { (ScriptBuiltinFn)StartScriptEffect, 2, 0 },
    { (ScriptBuiltinFn)StopScriptEffect, 1, 0 },
    { (ScriptBuiltinFn)StartScriptPadRecordPattern, 2, 0 },
    { (ScriptBuiltinFn)SendScriptPointEventToWorldListener, 2, 0 },
    { (ScriptBuiltinFn)SampleScriptAnimation, 7, 0 },
    { (ScriptBuiltinFn)SetScriptVoiceParam, 2, 0 }
};
MarkStacks g_markStacks;

// The script's + built-in: the first argument plus every further argument (the rest list in
// args[1]). Numbers add as floats and the result stays an int only if every operand was one; a
// vector (tag 0x16) adds component by component on the VU0 and a matrix (tag 0x17) element by
// element. Any other first operand gives an empty result.
ScriptValue* AddScriptValues(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    InitScriptValue(&t);
    s32 tag = args[0].tag;
    R11B008Node* n;
    if (args[1].tag == 0) {
        n = 0;
    } else {
        ScriptValue* m = &args[1];
        n = m->node;
    }
    switch (tag) {
    case 0x14:
    case 0x15: {
        s32 isInt;
        f32 sum;
        if (tag == 0x14) {
            sum = (f32)args[0].i;
            isInt = 1;
        } else {
            sum = args[0].f;
            isInt = 0;
        }
        for (; n != 0; n = n->next) {
            if (n->tag == 0x14) {
                sum = sum + (f32)n->i;
            } else {
                isInt = 0;
                sum = sum + n->f;
            }
        }
        if (isInt != 0) {
            SetScriptValueInt(&t, (s32)sum);
        } else {
            SetScriptValueFloat(&t, sum);
        }
        break;
    }
    case 0x16: {
        Vec02* v = (Vec02*)AcquireVectorAPayload();
        *v = *(Vec02*)args[0].v;
        for (; n != 0; n = n->next) {
            Vu0::Q(*v) = Vu0::Add(Vu0::Q(*v), Vu0::Q(*(Vec02*)n->v));
        }
        SetScriptValueVectorA(&t, (f32*)v);
        break;
    }
    case 0x17: {
        Mat4A* m = (Mat4A*)AcquireMatrixPayload();
        *m = *(Mat4A*)args[0].v;
        for (; n != 0; n = n->next) {
            f32* src = n->v;
            ((f32*)m)[0] = ((f32*)m)[0] + src[0];
            ((f32*)m)[1] = ((f32*)m)[1] + src[1];
            ((f32*)m)[2] = ((f32*)m)[2] + src[2];
            ((f32*)m)[3] = ((f32*)m)[3] + src[3];
            ((f32*)m)[4] = ((f32*)m)[4] + src[4];
            ((f32*)m)[5] = ((f32*)m)[5] + src[5];
            ((f32*)m)[6] = ((f32*)m)[6] + src[6];
            ((f32*)m)[7] = ((f32*)m)[7] + src[7];
            ((f32*)m)[8] = ((f32*)m)[8] + src[8];
            ((f32*)m)[9] = ((f32*)m)[9] + src[9];
            ((f32*)m)[10] = ((f32*)m)[10] + src[10];
            ((f32*)m)[11] = ((f32*)m)[11] + src[11];
            ((f32*)m)[12] = ((f32*)m)[12] + src[12];
            ((f32*)m)[13] = ((f32*)m)[13] + src[13];
            ((f32*)m)[14] = ((f32*)m)[14] + src[14];
            ((f32*)m)[15] = ((f32*)m)[15] + src[15];
        }
        SetScriptValueMatrix(&t, (f32*)m);
        break;
    }
    }
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}
// The script's - built-in, AddScriptValues with subtraction: the first argument minus each further
// argument in turn, for numbers (int result only if all are ints), vectors and matrices.
ScriptValue* SubtractScriptValues(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    InitScriptValue(&t);
    s32 tag = args[0].tag;
    R11B008Node* n;
    if (args[1].tag == 0) {
        n = 0;
    } else {
        ScriptValue* m = &args[1];
        n = m->node;
    }
    switch (tag) {
    case 0x14:
    case 0x15: {
        s32 isInt;
        f32 sum;
        if (tag == 0x14) {
            sum = (f32)args[0].i;
            isInt = 1;
        } else {
            sum = args[0].f;
            isInt = 0;
        }
        for (; n != 0; n = n->next) {
            if (n->tag == 0x14) {
                sum = sum - (f32)n->i;
            } else {
                isInt = 0;
                sum = sum - n->f;
            }
        }
        if (isInt != 0) {
            SetScriptValueInt(&t, (s32)sum);
        } else {
            SetScriptValueFloat(&t, sum);
        }
        break;
    }
    case 0x16: {
        Vec02* v = (Vec02*)AcquireVectorAPayload();
        *v = *(Vec02*)args[0].v;
        for (; n != 0; n = n->next) {
            Vu0::Q(*v) = Vu0::Sub(Vu0::Q(*v), Vu0::Q(*(Vec02*)n->v));
        }
        SetScriptValueVectorA(&t, (f32*)v);
        break;
    }
    case 0x17: {
        Mat4A* m = (Mat4A*)AcquireMatrixPayload();
        *m = *(Mat4A*)args[0].v;
        for (; n != 0; n = n->next) {
            f32* src = n->v;
            ((f32*)m)[0] = ((f32*)m)[0] - src[0];
            ((f32*)m)[1] = ((f32*)m)[1] - src[1];
            ((f32*)m)[2] = ((f32*)m)[2] - src[2];
            ((f32*)m)[3] = ((f32*)m)[3] - src[3];
            ((f32*)m)[4] = ((f32*)m)[4] - src[4];
            ((f32*)m)[5] = ((f32*)m)[5] - src[5];
            ((f32*)m)[6] = ((f32*)m)[6] - src[6];
            ((f32*)m)[7] = ((f32*)m)[7] - src[7];
            ((f32*)m)[8] = ((f32*)m)[8] - src[8];
            ((f32*)m)[9] = ((f32*)m)[9] - src[9];
            ((f32*)m)[10] = ((f32*)m)[10] - src[10];
            ((f32*)m)[11] = ((f32*)m)[11] - src[11];
            ((f32*)m)[12] = ((f32*)m)[12] - src[12];
            ((f32*)m)[13] = ((f32*)m)[13] - src[13];
            ((f32*)m)[14] = ((f32*)m)[14] - src[14];
            ((f32*)m)[15] = ((f32*)m)[15] - src[15];
        }
        SetScriptValueMatrix(&t, (f32*)m);
        break;
    }
    }
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

// The payloads of the vector and matrix tags (func_001159B8 reads them too): a 16-byte vector
// (tags 0x16, 0x18) and the four rows of the 0x40-byte block (tag 0x17), 16-aligned (a row is
// copied with lq/sq). A matrix is copy-constructed with CopyBytes (the scaled matrix
// ScaledMatrix returns: CopyBytes(&c, &r, 0x40) in MultiplyScriptValues and
// DivideScriptValues); it is assigned member by member (lq/sq).
struct __attribute__((aligned(16))) ScriptVectorRow {
    f32 v[4];               // 0x00
};
// Declared void here: retail's calls leave v0 free for the copy that follows (a value the call
// set would end in v0, and the next lq would take v1).
extern "C" void CopyBytes(void* dst, void* src, s32 n); // stays void (see above): retail returns a value, but func_00113240 differs in registers if declared
struct ScriptMatrixPayload {
    ScriptVectorRow row[4];      // 0x00
    ScriptMatrixPayload() {}
    ScriptMatrixPayload(const ScriptMatrixPayload& o) { CopyBytes(this, (void*)&o, sizeof(*this)); }
};
// The two floats of tag 0x19, copied as one 8-byte value.
struct ScriptFloatPair {
    f32 v[2];
};
u128 ScaleQuadword(u128 s, u128 v);
s32 ScaleMatrix(ScriptMatrixPayload* out, const ScriptMatrixPayload* m, u128 s);
// A matrix scaled by a weight in a GPR (Vu0::ScalarInGpr), returned by value: ScaleMatrix into
// the inline's own matrix, which the return copies into the caller's with CopyBytes. Inlined, the
// call's arguments go straight into a0-a2, so retail forms the matrix's address afresh for
// ScaleMatrix and again for CopyBytes (addiu a0, sp, 0x60; addiu a1, sp, 0x60).
static inline ScriptMatrixPayload ScaledMatrix(const ScriptMatrixPayload* m, u128 s)
{
    ScriptMatrixPayload r;
    ScaleMatrix(&r, m, s);
    return r;
}
u128* StoreFloatAsQuadword(u128* out, f32 f);
void TransformByMatrixWithW(const Quad16* m, const Vec02* v, f32 w, Vec02* out);
ScriptMatrixPayload MultiplyMatrices(const ScriptMatrixPayload* a, const void* b);
void FreeMatrixPayload(void* p);

// The script's * built-in: multiplies the first argument by each further one. Number times number
// is a number (an int only if all are ints); a scalar scales a vector (0x16 or 0x18), a matrix or a
// float pair (0x19), in either order; a matrix times a vector transforms it (w = 1), and a matrix
// times a matrix multiplies them.
ScriptValue* MultiplyScriptValues(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    f32 n = 0.0f;
    s32 tag;
    s32 isInt = 0;
    ScriptVectorRow* va = 0;
    ScriptVectorRow* vb = 0;
    ScriptFloatPair* pair = 0;
    ScriptMatrixPayload* m = 0;
    switch (args[0].tag) {
    case 0x15:
        tag = 0x15;
        n = args[0].f;
        isInt = 0;
        break;
    case 0x14:
        tag = 0x15;
        n = (f32)args[0].i;
        isInt = 1;
        break;
    case 0x16:
        va = (ScriptVectorRow*)AcquireVectorAPayload();
        tag = 0x16;
        *va = *(ScriptVectorRow*)args[0].v;
        break;
    case 0x17:
        m = (ScriptMatrixPayload*)AcquireMatrixPayload();
        tag = 0x17;
        *m = *(ScriptMatrixPayload*)args[0].v;
        break;
    case 0x18:
        vb = (ScriptVectorRow*)AcquireVectorBPayload();
        tag = 0x18;
        *vb = *(ScriptVectorRow*)args[0].v;
        break;
    case 0x19:
        pair = (ScriptFloatPair*)AcquirePairPayload();
        tag = 0x19;
        *pair = *(ScriptFloatPair*)args[0].v;
        break;
    }
    R11B008Node* x = 0;
    if (args[1].tag != 0) {
        x = args[1].node;
    }
    for (; x != 0; x = x->next) {
        switch (tag) {
        case 0x15:
            switch (x->tag) {
            case 0x15:
                isInt = 0;
                n *= x->f;
                break;
            case 0x14:
                n *= (f32)x->i;
                break;
            case 0x16: {
                va = (ScriptVectorRow*)AcquireVectorAPayload();
                tag = 0x16;
                u128 k = Vu0::Scalar(n);
                Vu0::Q(*va) = Vu0::MulX(Vu0::Q(*(ScriptVectorRow*)x->v), k);
                break;
            }
            case 0x17: {
                m = (ScriptMatrixPayload*)AcquireMatrixPayload();
                tag = 0x17;
                ScriptMatrixPayload c = ScaledMatrix((ScriptMatrixPayload*)x->v, Vu0::ScalarInGpr(n));
                *m = c;
                break;
            }
            case 0x18: {
                vb = (ScriptVectorRow*)AcquireVectorBPayload();
                tag = 0x18;
                u128 t;
                f32* p = x->v;
                StoreFloatAsQuadword(&t, n);
                u128 tv = t;
                u128 u;
                CopyQuadword(&u, p);
                StoreQuadword((u128*)vb, ScaleQuadword(tv, *&u));
                break;
            }
            case 0x19: {
                pair = (ScriptFloatPair*)AcquirePairPayload();
                tag = 0x19;
                f32* p = x->v;
                pair->v[0] = p[0] * n;
                pair->v[1] = p[1] * n;
                break;
            }
            }
            break;
        case 0x16:
            switch (x->tag) {
            case 0x14:
                Vu0::Q(*va) = Vu0::MulX(Vu0::Q(*va), Vu0::Scalar((f32)x->i));
                break;
            case 0x15:
                Vu0::Q(*va) = Vu0::MulX(Vu0::Q(*va), Vu0::ScalarAt(x->f));
                break;
            }
            break;
        case 0x17:
            switch (x->tag) {
            case 0x14: {
                ScriptMatrixPayload c = ScaledMatrix(m, Vu0::ScalarInGpr((f32)x->i));
                *m = c;
                break;
            }
            case 0x15: {
                ScriptMatrixPayload c = ScaledMatrix(m, Vu0::ScalarInGprAt(x->f));
                *m = c;
                break;
            }
            case 0x16:
                va = (ScriptVectorRow*)AcquireVectorAPayload();
                tag = 0x16;
                TransformByMatrixWithW((const Quad16*)m, (const Vec02*)x->v, 1.0f, (Vec02*)va);
                break;
            case 0x17: {
                ScriptMatrixPayload c;
                c = MultiplyMatrices(m, x->v);
                *m = c;
                break;
            }
            }
            break;
        case 0x18:
            switch (x->tag) {
            case 0x14: {
                u128 t;
                StoreFloatAsQuadword(&t, (f32)x->i);
                u128 tv = t;
                u128 u;
                CopyQuadword(&u, vb);
                StoreQuadword((u128*)vb, ScaleQuadword(tv, *&u));
                break;
            }
            case 0x15: {
                u128 t;
                StoreFloatAsQuadword(&t, x->f);
                u128 tv = t;
                u128 u;
                CopyQuadword(&u, vb);
                StoreQuadword((u128*)vb, ScaleQuadword(tv, *&u));
                break;
            }
            }
            break;
        case 0x19:
            switch (x->tag) {
            case 0x14: {
                f32 k = (f32)x->i;
                pair->v[0] *= k;
                pair->v[1] *= k;
                break;
            }
            case 0x15: {
                f32 k = x->f;
                pair->v[0] *= k;
                pair->v[1] *= k;
                break;
            }
            }
            break;
        }
    }
    switch (tag) {
    case 0x15:
        if (isInt) {
            SetScriptValueInt(&q, (s32)n);
        } else {
            SetScriptValueFloat(&q, n);
        }
        break;
    case 0x16:
        SetScriptValueVectorA(&q, (f32*)va);
        if (m != 0) {
            FreeMatrixPayload(m);
        }
        break;
    case 0x17:
        SetScriptValueMatrix(&q, (f32*)m);
        break;
    case 0x18:
        SetScriptValueVectorB(&q, (f32*)vb);
        break;
    case 0x19:
        SetScriptValuePair(&q, (f32*)pair);
        break;
    }
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

// The script's / built-in: divides the first argument by each further number in turn. A number is
// divided as a float (int result only if all are ints); a vector (0x16 or 0x18), matrix or float
// pair is scaled by the reciprocal, so the divisor must be a number.
ScriptValue* DivideScriptValues(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    f32 n = 0.0f;
    s32 tag = args[0].tag;
    ScriptVectorRow* va = 0;
    ScriptVectorRow* vb = 0;
    s32 isInt = 0;
    ScriptFloatPair* pair = 0;
    ScriptMatrixPayload* m = 0;
    switch (tag) {
    case 0x15:
        n = args[0].f;
        isInt = 0;
        break;
    case 0x14:
        tag = 0x15;
        n = (f32)args[0].i;
        isInt = 1;
        break;
    case 0x16:
        va = (ScriptVectorRow*)AcquireVectorAPayload();
        *va = *(ScriptVectorRow*)args[0].v;
        break;
    case 0x17:
        m = (ScriptMatrixPayload*)AcquireMatrixPayload();
        *m = *(ScriptMatrixPayload*)args[0].v;
        break;
    case 0x18:
        vb = (ScriptVectorRow*)AcquireVectorBPayload();
        *vb = *(ScriptVectorRow*)args[0].v;
        break;
    case 0x19:
        pair = (ScriptFloatPair*)AcquirePairPayload();
        *pair = *(ScriptFloatPair*)args[0].v;
        break;
    }
    R11B008Node* x = 0;
    if (args[1].tag != 0) {
        x = args[1].node;
    }
    for (; x != 0; x = x->next) {
        switch (tag) {
        case 0x15:
            switch (x->tag) {
            case 0x15:
                isInt = 0;
                n /= x->f;
                break;
            case 0x14:
                n /= (f32)x->i;
                break;
            }
            break;
        case 0x16:
            switch (x->tag) {
            case 0x14: {
                Vu0::Q(*va) = Vu0::MulX(Vu0::Q(*va), Vu0::Scalar(1.0f / (f32)x->i));
                break;
            }
            case 0x15: {
                Vu0::Q(*va) = Vu0::MulX(Vu0::Q(*va), Vu0::Scalar(1.0f / x->f));
                break;
            }
            }
            break;
        case 0x17:
            switch (x->tag) {
            case 0x14: {
                ScriptMatrixPayload c = ScaledMatrix(m, Vu0::ScalarInGpr(1.0f / (f32)x->i));
                *m = c;
                break;
            }
            case 0x15: {
                ScriptMatrixPayload c = ScaledMatrix(m, Vu0::ScalarInGpr(1.0f / x->f));
                *m = c;
                break;
            }
            }
            break;
        case 0x18:
            switch (x->tag) {
            case 0x14: {
                u128 t;
                StoreFloatAsQuadword(&t, 1.0f / (f32)x->i);
                u128 tv = t;
                u128 u;
                CopyQuadword(&u, vb);
                StoreQuadword((u128*)vb, ScaleQuadword(tv, *&u));
                break;
            }
            case 0x15: {
                u128 t;
                StoreFloatAsQuadword(&t, 1.0f / x->f);
                u128 tv = t;
                u128 u;
                CopyQuadword(&u, vb);
                StoreQuadword((u128*)vb, ScaleQuadword(tv, *&u));
                break;
            }
            }
            break;
        case 0x19:
            switch (x->tag) {
            case 0x14: {
                f32 r = 1.0f / (f32)x->i;
                pair->v[0] *= r;
                pair->v[1] *= r;
                break;
            }
            case 0x15: {
                f32 r = 1.0f / x->f;
                pair->v[0] *= r;
                pair->v[1] *= r;
                break;
            }
            }
            break;
        }
    }
    switch (tag) {
    case 0x15:
        if (isInt) {
            SetScriptValueInt(&q, (s32)n);
        } else {
            SetScriptValueFloat(&q, n);
        }
        break;
    case 0x16:
        SetScriptValueVectorA(&q, (f32*)va);
        break;
    case 0x17:
        SetScriptValueMatrix(&q, (f32*)m);
        break;
    case 0x18:
        SetScriptValueVectorB(&q, (f32*)vb);
        break;
    case 0x19:
        SetScriptValuePair(&q, (f32*)pair);
        break;
    }
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

// Built-in that does nothing with its argument and gives back the empty value; the two
// functions after it are the same for other argument counts.
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

// Script built-in: whether the words of two values are equal.
ScriptValue* TestScriptWordsEqual(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    SetScriptValueBool(&q, args[0].i == args[1].i);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

// The shared body of the four ordering built-ins: converts the first two arguments to floats (an
// int is converted) and gives back the boolean of mode 0 (<), 1 (<=), 2 (>) or 3 (>=). The
// arguments are read from args[0] and args[1] in that order.
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

// Script built-in: the first number is less than the second. The next three do the same for
// less or equal, greater and greater or equal (modes 1 to 3 of CompareScriptNumbers).
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

// Script built-in: whether two values are identical: the tags must match, and then the word
// (for pointers and references) or just the kind (for operator and empty values) must match.
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

// Structural equality of two script values, the body of the = built-in: values of different tags
// are never equal; ints, pointers and refs compare by their word; lists (tag 0x1E) and function
// records (0x1F) compare element by element, recursively; a host function (0x21) by its object and
// function pointers. The result is a bool value in *ret.
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

// Script built-in: whether the value is a bool. The other IsScript... built-ins test one tag the
// same way and are left without comment.
ScriptValue* IsScriptBool(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue local;
    InitScriptValue(&local);
    SetScriptValueBool(&local, args[0].tag == 0x1B);
    CopyConstructScriptValue(ret, &local);
    DestroyScriptValue(&local, 2);
    return ret;
}

// Script built-in: whether the value is an int or a float (tag 0x14 or 0x15).
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

// Script built-in: whether the value is a list (a chain, or the empty list).
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

// Script built-in: whether the value is a reference (tag 0x20).
ScriptValue* IsScriptRef(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    SetScriptValueBool(&q, (args->tag ^ 0x20) == 0);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

// Script built-in: whether the value is a reference (tag 0x20) that is null.
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

// Script built-in: whether the value is a function (tag 0x1F or 0x1D).
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

// Script built-in: whether two numbers (ints or floats) are within the third one of each other.
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

// Script built-in: whether the value is a bool (tag 0x1B) that is false.
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

// Script built-in: a new list cell holding args[0] in front of the list args[1] (the empty list
// gives a one-item list).
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

// Script built-in: the first item of a list.
ScriptValue* GetScriptListHead(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    AssignScriptValue(&q, args->node);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

// Script built-in: the list without its first cell (the empty list when there is none).
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

// Script built-in: with mode 0x23 replaces the item of the cell args[0] with args[1], otherwise
// replaces the cell's tail with the list args[1] (or ends the list).
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

// Script built-in: replaces a list cell's item (SetScriptListCell mode 0x23).
ScriptValue* SetScriptListHead(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    SetScriptListCell(ret, count, args, scope, 0x23);
    return ret;
}

// Script built-in: replaces a list cell's tail (SetScriptListCell mode 0x24).
ScriptValue* SetScriptListTail(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    SetScriptListCell(ret, count, args, scope, 0x24);
    return ret;
}

// Script built-in: the number of cells in a list (0 for an empty list or anything else).
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

// Script built-in: the item at index args[1] of the list args[0], or the empty value when the
// list is shorter or the argument is not a list.
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

// The script's list-membership built-in: gives true if the list in args[1] has an element equal
// (TestScriptEqual, so the structural comparison) to args[0], false otherwise or when args[1] is
// not a list.
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

// KEPT (build/swarm/v2/NOTES.md): func_00114BB0, func_00118198 and func_00119218 give their
// value back as a class (the result's place is GCC's hidden first argument), and their early
// return keeps its own copy and destruction only so: written with the plain value and explicit
// calls, GCC cross-jumps that return into the last one. Their callers (for func_00114BB0, the
// table D_00259958) call them through the plain declarations above (ScriptValue* first).
struct RetValue : ScriptValue {
    RetValue() { InitScriptValue(this); }
    RetValue(const RetValue& o) { CopyConstructScriptValue(this, &o); }
    ~RetValue() { DestroyScriptValue(this, 2); }
};

// The script's append built-in: concatenates the lists in the rest argument into one list. Every
// list but the last is copied, the last is shared, not copied. Non-list arguments are skipped, and
// no list at all gives the empty list.
RetValue AppendScriptLists(s32 count, ScriptValue* args, ScriptScope* scope)
{
    RetValue q;
    if (args->tag == 0) {
        return *(RetValue*)args;
    }
    R11B008Node* n = args->node;
    R11B008Node* head = 0;
    R11B008Node* last;
    while (n != 0) {
        if (n->tag == 0x1E) {
            R11B008Node* c;
            if (n->next != 0) {
                c = NewScriptValueNode();
                CopyScriptValueChain(n->node, c, 0);
            } else {
                c = n->node;
            }
            if (head == 0) {
                head = NewScriptValueNode();
                SetScriptValueChain(head, c);
            } else {
                last->next = c;
            }
            last = c;
            while (last->next != 0) {
                last = last->next;
            }
        }
        n = n->next;
    }
    if (head != 0) {
        SetScriptValueChain(&q, head->node);
    } else {
        q.tag = 0;
    }
    return q;
}

// The script's map built-in: calls the function args[0] on each element of the list args[1] and
// gives back the list of the results. It builds a small call expression (the function applied to
// one argument slot) and evaluates it with EvalScriptExpression once per element; an empty list
// comes back empty.
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

// The script's filter built-in: calls the function args[0] on each element of the list args[1] and
// keeps the elements for which it gave true (a bool value that is non-zero). The result is the new
// list, or the empty list when none passed.
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

// The script's for-each built-in: calls the function args[0] on each element of the list args[1]
// for its side effects, then gives back the empty result (tag 0x22). Like MapScriptList it
// evaluates a small call expression once per element.
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

// Script built-in: evaluates its argument value as an expression in the calling scope and gives
// back the result.
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

// Script built-in: builds a vector value (tag 0x16) from the first three arguments, each
// converted to a float.
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

// The script's matrix constructor: with 3 or 4 arguments they are row vectors copied in (the rest
// is the identity); with 9 or 16 numbers they fill a 3x3 or 4x4 block row by row, a 3x3 over the
// identity. The result is a new tag 0x17 value.
ScriptValue* MakeScriptMatrix(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t, u;
    InitScriptValue(&t);
    Row_115510* a = (Row_115510*)AcquireMatrixPayload();
    R11B008Node* n = args->node;
    switch (count) {
    case 3:
    case 4: {
        ResetMatrixHomogeneous((HomogeneousMatrix*)a);
        for (s32 i = 0; i < count; i++) {
            a[i] = *(Row_115510*)n->v;
            n = n->next;
        }
        break;
    }
    case 9:
        ResetMatrixHomogeneous((HomogeneousMatrix*)a);
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

// Script built-in: sets the cached voice parameter args[0] to args[1] (SetCachedVoiceParam).
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

// Script built-in: builds a vector value of the second kind (tag 0x18) from three float
// arguments.
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

// Script built-in: builds a two-float value (tag 0x19) from its two arguments, each converted to a
// float.
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

// The script's constructor for a value of three floats (tag 0x1A): converts the three arguments to
// floats and stores them in a new pooled payload.
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

// The script's element accessor: takes a component of a vector, a four-float vector, a float pair
// or a float triple by index, or, for a matrix, gives the row as a vector (two arguments) or one
// element of the row (three arguments).
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

// Script built-in: seeds the random number generator with an int or a float argument.
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

// Script built-in: a random float between its two arguments (ints or floats).
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

// Calls entry index of the table of float functions (g_scriptMathFunctions) on a number (int or
// float) and gives back the float result; the sine, cosine and square root built-ins use it.
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

// Script built-in: square root. The seven built-ins after it call the same entry point with the
// next index of the math function table (sine, cosine, tangent, arcsine, arccosine, arctangent
// and the angle wrap).
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

// Script built-in: wraps an angle into range (entry 7 of the math function table).
ScriptValue* WrapScriptAngle(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    CallScriptMathFunction(ret, args, 7);
    return ret;
}

// Script built-in: the arctangent of the ratio of its two arguments (ints or floats), using both
// signs as atan2 does.
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

// Script built-in: the dot product of two vectors.
ScriptValue* GetScriptDotProduct(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue obj;
    InitScriptValue(&obj);
    SetScriptValueFloat(&obj, Vu0::ToFloat(Vu0::Dot(Vu0::Q(*(Vec02*)args[0].v), Vu0::Q(*(Vec02*)args[1].v))));
    CopyConstructScriptValue(ret, &obj);
    DestroyScriptValue(&obj, 2);
    return ret;
}

// Script built-in: the cross product of two vectors.
ScriptValue* GetScriptCrossProduct(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
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

// Script built-in: the length of a vector.
ScriptValue* GetScriptVectorLength(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue obj;
    InitScriptValue(&obj);
    SetScriptValueFloat(&obj, Vu0::ToFloat(Vu0::Length(Vu0::Q(*args->v))));
    CopyConstructScriptValue(ret, &obj);
    DestroyScriptValue(&obj, 2);
    return ret;
}

// The script's distance built-in: the length of args[0] minus the optional second vector in
// args[1], which defaults to the zero vector (D_00248D30), so with one argument it is the vector's
// distance from the origin.
ScriptValue* GetScriptDistance(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue obj;
    InitScriptValue(&obj);
    if (args[1].tag == 0) {
        SetScriptValueFloat(&obj, Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(*(Vec02*)args[0].v), Vu0::Q(g_zeroVector)))));
    } else {
        SetScriptValueFloat(&obj, Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(*(Vec02*)args[0].v), Vu0::Q(*(Vec02*)args[1].node->v)))));
    }
    CopyConstructScriptValue(ret, &obj);
    DestroyScriptValue(&obj, 2);
    return ret;
}

// Like GetScriptDistance but gives the squared distance (a dot product of the difference with
// itself), which avoids the square root; the second vector is optional and defaults to the zero
// vector.
ScriptValue* GetScriptDistanceSquared(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue obj;
    InitScriptValue(&obj);
    if (args[1].tag == 0) {
        u128 d = Vu0::Sub(Vu0::Q(*(Vec02*)args[0].v), Vu0::Q(g_zeroVector));
        SetScriptValueFloat(&obj, Vu0::ToFloat(Vu0::Dot(d, d)));
    } else {
        u128 d = Vu0::Sub(Vu0::Q(*(Vec02*)args[0].v), Vu0::Q(*(Vec02*)args[1].node->v));
        SetScriptValueFloat(&obj, Vu0::ToFloat(Vu0::Dot(d, d)));
    }
    CopyConstructScriptValue(ret, &obj);
    DestroyScriptValue(&obj, 2);
    return ret;
}

// The script's normalise built-in: args[0] divided by its length. When the length is under 0.0001
// it gives back the fallback instead: the optional second argument, or the zero vector (D_00248D30)
// when there is none.
ScriptValue* NormalizeScriptVector(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue obj;
    InitScriptValue(&obj);
    Vec02* out = (Vec02*)AcquireVectorAPayload();
    u128 a = Vu0::Q(*(Vec02*)args[0].v);
    Vu0::Q(*out) = a;
    if (args[1].tag == 0) {
        Vec02* fb = (Vec02*)&g_zeroVector;
        u128 len = Vu0::Length(a);
        if (Vu0::ToFloatMoved(len) < 0.0001f) {
            *out = *fb;
        } else {
            Vu0::Q(*out) = Vu0::DivX(a, len);
        }
    } else {
        Vec02* fb = (Vec02*)args[1].node->v;
        u128 len = Vu0::Length(a);
        if (Vu0::ToFloatMoved(len) < 0.0001f) {
            *out = *fb;
        } else {
            Vu0::Q(*out) = Vu0::DivX(a, len);
        }
    }
    SetScriptValueVectorA(&obj, (f32*)out);
    CopyConstructScriptValue(ret, &obj);
    DestroyScriptValue(&obj, 2);
    return ret;
}

// Script built-in: the projection of args[0] onto args[1] (the dot product times args[1]).
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

// Script built-in: args[0] minus its projection onto args[1], that is the part of the first
// vector perpendicular to the second.
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

// The script's launch-velocity built-in: gives the velocity vector that carries a projectile from
// the point args[0] to the point args[1] at the launch angle args[2], through
// ComputeBallisticLaunchVelocity. The optional fourth argument is a pointer passed through as that
// function's object (null when absent).
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
    ComputeBallisticLaunchVelocity((Vec02*)s1, (Vec02*)fc, (Vec02*)p, (u8*)s3, v.f);
    DestroyScriptValue(&v, 2);
    SetScriptValueVectorA(&q, p);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

// Script built-in: the angle between two vectors and the axis they turn about, as a two-node
// list (angle first, axis second).
ScriptValue* GetScriptAngleAndAxis(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    InitScriptValue(&t);
    R11B008Node* a = NewScriptValueNode();
    R11B008Node* b = NewScriptValueNode();
    a->next = b;
    f32* c = AcquireVectorAPayload();
    SetScriptValueVectorA(b, c);
    f32 d = ComputeAngleBetweenVectors((Vec02*)args[0].p, (Vec02*)args[1].p, (Vec02*)c);
    SetScriptValueFloat(a, d);
    SetScriptValueChain(&t, a);
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

// Script built-in: the transpose of a matrix.
ScriptValue* TransposeScriptMatrix(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    InitScriptValue(&t);
    f32* a = AcquireMatrixPayload();
    CopyTransposedMatrix((Quad16*)args[0].p, (Quad16*)a);
    SetScriptValueMatrix(&t, a);
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

// Script built-in: the inverse of a 4x4 matrix.
ScriptValue* InvertScriptMatrix(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    InitScriptValue(&t);
    f32* a = AcquireMatrixPayload();
    InvertMatrix4x4(args[0].p, a);
    SetScriptValueMatrix(&t, a);
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

// Script built-in: the matrix args[0] transformed by an object (args[1]), as a new matrix.
ScriptValue* TransformScriptMatrixByObject(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    InitScriptValue(&t);
    f32* a = AcquireMatrixPayload();
    TransformMatrixByObject((u8*)args[0].p, args[1].p, (Quad16*)a);
    SetScriptValueMatrix(&t, a);
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

typedef f32 (*MathFn_259938)(f32 x);
f32* AcquireMatrixPayload(void);
void MatrixToAxisAngle(Mat02* m, f32* angle, Vec02* axis);
void ResetMatrixHomogeneous(HomogeneousMatrix* self);

void MultiplyMatrices3x3(Mat02* a, Mat02* b, Mat02* out);
void BuildAxisAngleMatrix(const Vec02* v, Mat02* out, f32 angle);

// The script's rotation-blend built-in: takes the rotation between the matrices args[0] and args[1]
// as an axis and an angle, scales the angle by the weight args[2] and applies that partial rotation
// to args[0]'s three rows. The result is a matrix with the translation cleared.
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
    MultiplyMatrices3x3((Mat02*)args[0].p, (Mat02*)args[1].p, &delta);
    MatrixToAxisAngle(&delta, &angle, (Vec02*)&axis);
    BuildAxisAngleMatrix(&axis, &delta, angle * args[2].f);
    const Mat02* src = (const Mat02*)args[0].p;
    u128 v0 = Vu0::Q(src->r[0]);
    Vu0::Q(b.r[0]) = Vu0::Q(a.r[0]) = Vu0::RotateUntied(delta, v0);
    Vu0::Q(b.r[1]) = Vu0::Q(a.r[1]) = Vu0::RotateUntied(delta, Vu0::Q(src->r[1]));
    Vu0::Q(b.r[2]) = Vu0::Q(a.r[2]) = Vu0::RotateUntied(delta, Vu0::Q(src->r[2]));
    *(Mat02*)m = a;
    ResetMatrixHomogeneous((HomogeneousMatrix*)m);
    SetScriptValueMatrix(&obj, m);
    CopyConstructScriptValue(ret, &obj);
    DestroyScriptValue(&obj, 2);
    return ret;
}

// Script built-in: the translation (the row at +0x30) of a matrix, as a vector.
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

// Script built-in: a copy of the matrix in args[0] with its homogeneous column reset.
ScriptValue* GetScriptMatrixRotation(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    f32* obj;
    InitScriptValue(&q);
    obj = AcquireMatrixPayload();
    *(Mat4A*)obj = *(Mat4A*)args[0].v;
    ResetMatrixHomogeneous((HomogeneousMatrix*)obj);
    SetScriptValueMatrix(&q, obj);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

// Script built-in: the Euler angles of a matrix's rotation, as a vector.
ScriptValue* GetScriptMatrixEuler(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    InitScriptValue(&t);
    f32* c = AcquireVectorAPayload();
    MatrixToEulerAngles((Mat4*)args[0].p, (Vec3*)c);
    SetScriptValueVectorA(&t, c);
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

// Script built-in: the rotation of a matrix as a two-node list, the angle first and the axis
// second.
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
    MatrixToAxisAngle((Mat02*)args[0].p, &vec.x, (Vec02*)c);
    SetScriptValueFloat(a, vec.x);
    SetScriptValueChain(&t, a);
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

// Script built-in: a matrix whose X axis points from args[0] to args[1], with Z as close to the
// up vector args[2] as possible (the world Z axis when args[2] is empty).
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
    BuildBasisFromXAndZHint((const Vec02*)&dir, (const Vec02*)up, (Mat02*)m);
    ResetMatrixHomogeneous((HomogeneousMatrix*)m);
    SetScriptValueMatrix(&obj, m);
    CopyConstructScriptValue(ret, &obj);
    DestroyScriptValue(&obj, 2);
    return ret;
}

// What func_00189378 fills in for func_00188B08: 0x30 bytes.
struct UprightBasis {
    u8 bytes[0x30];         // 0x00
};

// Script built-in: a matrix with the object's rotation made upright and the object's position
// (the translation at +0x30) as its translation.
ScriptValue* MakeScriptUprightObjectMatrix(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    UprightBasis v;
    InitScriptValue(&t);
    f32* a = AcquireMatrixPayload();
    RotateMatrixUpright((Mat02*)args[0].p, 0, (Mat02*)&v);
    BuildMatrixFromRotationAndTranslation((const Vec02*)((u8*)args[0].p + 0x30), (const Mat02*)&v, (Mat4A*)a);
    SetScriptValueMatrix(&t, a);
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

// Script built-in: evaluates the polynomial c0 + x * (c1 + x * c2), with the coefficients taken
// from the three-float value in args[0] and x from args[1].
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

// The script's clamped polynomial built-in: evaluates c0 + x*(c1 + x*c2) for the coefficient triple
// args[0] at x = args[2], then clamps the value into the float pair args[1] (low, high).
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

// The script's built-in that fits a quadratic through three points of a curve: the four numbers are
// the values at t = 0 and t = 1, the t of the third point, and the value there; the three
// coefficients come back as a four-float vector (FitQuadraticCurve), the fourth float is not
// written here.
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

// Script built-in: args[1] clamped to the range in args[0].
ScriptValue* ClampScriptToRange(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q0;
    ScriptValue q1;
    InitScriptValue(&q0);
    void* span = args[0].p;
    ConvertScriptValueToFloat(&q1, args + 1);
    f32 r = ClampToRange((ValueRange*)span, q1.f);
    SetScriptValueFloat(&q0, r);
    DestroyScriptValue(&q1, 2);
    CopyConstructScriptValue(ret, &q0);
    DestroyScriptValue(&q0, 2);
    return ret;
}

// Script built-in: whether args[1] lies inside the range in args[0].
ScriptValue* TestScriptInsideRange(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    ScriptValue v;
    InitScriptValue(&q);
    void* s1 = args[0].p;
    ConvertScriptValueToFloat(&v, &args[1]);
    s32 flag = IsInsideRange((ValueRange*)s1, v.f);
    SetScriptValueBool(&q, flag);
    DestroyScriptValue(&v, 2);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

// Script built-in: the float argument truncated to an int.
ScriptValue* ConvertScriptFloatToInt(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    SetScriptValueInt(&q, (s32)args->f);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

// Script built-in: the float plus 1, truncated to an int (so exact integers go up too).
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

// Script built-in: the float plus 0.5, truncated to an int.
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

// Script built-in: the absolute value of an int or float.
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

// The script's max built-in: the largest of args[0] and every element of the rest list in args[1].
// Ints and floats compare across types, and the winning value is kept as it was (an int stays an
// int).
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

// The script's min built-in, GetScriptMaximum with the comparison reversed: the smallest of args[0]
// and every element of the rest list, keeping the winner's own type.
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

// Script built-in: the integer remainder of args[0] divided by args[1].
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

// Script built-in: the game time, as a float.
ScriptValue* GetScriptClock(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    SetScriptValueFloat(&q, g_gameTime);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

// The script's delayed-call built-in: makes an entry from the delay in args[0], the function in
// args[1] and the remaining arguments (each as a quoted constant) and pushes it on the list the
// current world keeps in its script scope under scopeVariableId (world.cpp reads that list back).
// Gives back the empty value.
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
    LookupScriptVariable((ScriptScope*)g_currentWorld->scriptScope, g_currentWorld->scopeVariableId, 0, &r);
    if (r.tag == 0x1E) {
        a->next = r.node;
    }
    SetScriptValueChain(&r, a);
    AssignScriptVariable(&t, (ScriptScope*)g_currentWorld->scriptScope, g_currentWorld->scopeVariableId, &r);
    DestroyScriptValue(&t, 2);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&r, 2);
    DestroyScriptValue(&q, 2);
    return ret;
}

// Script built-in: sets the event timer of the placed object args[0] to args[1].
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

// The shared body of the four object-property built-ins: reads the object (args[0]) and the
// property key (args[1]) and calls AddObjectProperty (kind 0x63), SetExtraObjectProperty (0x64),
// UpdateObjectProperty (0x65) or GetObjectProperty (0x66), with args[2] as the value for the first
// three. The call's result is the built-in's result.
ScriptValue* DispatchScriptObjectProperty(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope, s32 kind)
{
    ScriptValue q1;
    ScriptValue q2;

    InitScriptValue(&q1);
    BaseObject* x1 = (BaseObject*)args[0].p;
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

// Script built-in: the object property dispatcher in mode 0x63 (add). The three after it use
// modes 0x64 (set an extra property), 0x65 (update) and 0x66 (get).
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

// Turns count object pointers into a script list of tag 0x20 reference values, in order; a count of
// 0 gives the empty list. The built-ins that search for objects use it to hand their results to the
// script.
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

// Script built-in: the first object of the current world with a given id (args[0], args[1]), or
// null; a non-zero args[1] selects the other search mode.
ScriptValue* FindScriptObject(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    void* r;
    InitScriptValue(&q);
    s32 flag = 0x105;
    s32 k = 0x101;
    if (args[1].i != 0) flag = k;
    r = FindFirstObjectById(g_currentWorld, flag, args[0].i, args[1].p);
    SetScriptValuePointerB(&q, r);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

// Script built-in: up to 0x40 objects of the current world matching a class id (args[0]) and a
// name (args[1]), as a list of references; a non-zero args[1] selects the other search mode.
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

// Script built-in: the first object of the current world with a given id (args[0], args[1]), or
// null.
ScriptValue* FindScriptObjectById(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    void* r;
    InitScriptValue(&q);
    r = FindFirstObjectById(g_currentWorld, 0x104, args[0].i, args[1].p);
    SetScriptValuePointerB(&q, r);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

// Script built-in: up to 0x40 objects of the current world with a given id (args[0], args[1]),
// as a list of references.
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

// Script built-in: the switched collider that is active now (the one the player controls).
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

// Script built-in: like FindScriptObjectList but gathers up to 0x100 objects by id.
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

// The box between its two vector arguments, component by component. Both are read through
// ScriptValue::Vector(): the second's `this` is the inliner's fresh pseudo, so its pointer is
// read again after the store of lo, as retail does (docs/TOOLCHAIN.md, "An inline method's
// this").

ScriptValue* FindScriptObjectsInBox(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    Vec02 lo;
    Vec02 hi;
    ScriptValue t;
    s32 n;
    u8* list;
    InitScriptValue(&q);
    Vu0::Set(lo, Vu0::Min(Vu0::Q(*args[0].Vector()), Vu0::Q(*args[1].Vector())));
    Vu0::Set(hi, Vu0::Max(Vu0::Q(*args[0].Vector()), Vu0::Q(*args[1].Vector())));
    PushBackMemoryMark();
    GatherCollidersInBox(g_currentWorld, 0, &lo, &hi, 0, 0, &n, (Collider***)&list);
    MakeScriptRefList(&t, n, list);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    PopBackMemoryMark();
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

// Script built-in: the colliders of the current world within a radius (args[1], an int or a float)
// of a point (args[0]), as a list of references.
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
    GatherCollidersInSphere(g_currentWorld, 0, scale, (Vec02*)args[0].v, 0, 0, &n, (Collider***)&list);
    MakeScriptRefList(&t, n, list);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    PopBackMemoryMark();
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

// The shared search of the two ray-test built-ins: for each object in the list args[0], looks for
// the nearest span hit of the segment from args[1] to args[2] (FindNearestSpanObject). With id 0x71
// every hit is collected as a list of (object, vector, vector); with any other id it stops at the
// first hit and gives (object, vector). No hit gives the empty list.
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
            if (FindNearestSpanObject(0, (Vec02*)pa->p, (Vec02*)pb->p, 1, (Collider**)&slot, &hit) == 0)
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

// Script built-in: the object-hit search in mode 0x71, giving the list it builds.
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

// Script built-in: the object-hit search in mode 0x72, giving the single result it builds.
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

// Script built-in: the point args[2] moved from one object's frame to the other's.
ScriptValue* TransformScriptPointBetweenFrames(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    InitScriptValue(&t);
    f32* p = AcquireVectorAPayload();
    TransformPointBetweenFrames((PlacedObject*)args[0].p, (PlacedObject*)args[1].p, (Vec02*)args[2].p, (Vec02*)p);
    SetScriptValueVectorA(&t, p);
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

// Script built-in: the direction args[2] moved from one object's frame to the other's (rotation
// only).
ScriptValue* TransformScriptDirectionBetweenFrames(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    InitScriptValue(&t);
    f32* p = AcquireVectorAPayload();
    TransformDirectionBetweenFrames((PlacedObject*)args[0].p, (PlacedObject*)args[1].p, (Vec02*)args[2].p, (Vec02*)p);
    SetScriptValueVectorA(&t, p);
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

// Script built-in: the rotation args[2] expressed in one object's frame, converted to the other
// object's frame, as a matrix.
ScriptValue* TransformScriptRotationBetweenFrames(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    f32* obj;
    InitScriptValue(&q);
    obj = AcquireMatrixPayload();
    TransformRotationBetweenFrames((PlacedObject*)args[0].p, (PlacedObject*)args[1].p, (Mat02*)args[2].v, (Mat02*)obj);
    ResetMatrixHomogeneous((HomogeneousMatrix*)obj);
    SetScriptValueMatrix(&q, obj);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

// Script built-in: the point in front of the camera, at the camera's near distance along its
// forward axis.
ScriptValue* GetScriptPointAheadOfCamera(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue obj;
    Vec02 t;
    Vec02 k;
    InitScriptValue(&obj);
    f32* p = AcquireVectorAPayload();
    Camera* c = g_camera;
    Vu0::Q(k) = Vu0::FromFloatAt(c->nearDistance);
    Vu0::Q(t) = Vu0::MulX(Vu0::Q(c->rotation), Vu0::Q(k));
    Vu0::Q(*(Vec02*)p) = Vu0::Add(Vu0::Q(c->position), Vu0::Q(t));
    SetScriptValueVectorA(&obj, p);
    CopyConstructScriptValue(ret, &obj);
    DestroyScriptValue(&obj, 2);
    return ret;
}

// Script built-in: plays the sound effect numbered args[0] (attached to the object in args[1], if
// any) and gives back the handle it got, then lets go of the handle.
ScriptValue* StartScriptEffect(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    s32 n;
    InitScriptValue(&q);
    n = 0;
    StartSoundEffect(args[0].i, (PlayingSound**)(args[1].i ? &n : 0), (BaseObject*)args[1].i, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    SetScriptValueInt(&q, n);
    if (n != 0) ClearSoundRecordHandle((PlayingSound**)&n);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

// Script built-in: stops the sound record whose handle is args[0]; gives back the empty value.
ScriptValue* StopScriptEffect(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    InitScriptValue(&t);
    StopSoundRecord((PlayingSound*)args[0].p, 0);
    t.tag = 0x22;
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

// Script built-in: starts the pad record's pattern args[0] at the rate given by args[1].
ScriptValue* StartScriptPadRecordPattern(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    ScriptValue u;
    InitScriptValue(&t);
    void* p = g_padRecord;
    s32 n = args[0].i;
    ConvertScriptValueToFloat(&u, args + 1);
    StartPadRecordPattern((PadRecord*)p, n, u.f);
    DestroyScriptValue(&u, 2);
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

// Script built-in: sends a point event (a position, args[0], and a value, args[1]) to the world's
// listener; gives back the empty value.
ScriptValue* SendScriptPointEventToWorldListener(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    ScriptValue u;
    InitScriptValue(&t);
    void* s1 = args[0].p;
    ConvertScriptValueToFloat(&u, args + 1);
    SendPointEventToWorldListener((Quad16*)s1, u.f);
    DestroyScriptValue(&u, 2);
    SetScriptValueTag(&t, 0x22);
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

// A sample's 16-aligned quadword and 0x30-byte rotation, as func_0012CD78 fills them in the
// untyped back-memory buffers SampleScriptAnimation allocates.
struct __attribute__((aligned(16))) ScriptSampleQuad {
    f32 f[4];
};
struct __attribute__((aligned(16))) ScriptSampleRotation {
    f32 f[12];
};

void* AllocateBackMemory(s32 size);
void *CopyRotationMatrix(Quad16* destination, const Quad16* source);

// The script's animation-sampling built-in: samples the animation args[0] (two float arguments,
// then the objects args[3] and args[4], through SampleAnimationFrameChain) for n entries and gives
// back a list with one list of n values per bit set in the mask args[6]: 1 positions, 2 rotation
// matrices, 4 and 8 two more vectors. The buffers come from back memory, released on return.
ScriptValue* SampleScriptAnimation(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    ScriptValue t;
    s32 n;
    s32 mask;
    void* from;
    void* to;
    InitScriptValue(&q);
    u8* positions = 0;
    u8* rotations = 0;
    u8* q4 = 0;
    u8* q8 = 0;
    void* anim = args[0].p;
    ConvertScriptValueToFloat(&t, args + 1);
    f32 a = t.f;
    DestroyScriptValue(&t, 2);
    ConvertScriptValueToFloat(&t, args + 2);
    f32 b = t.f;
    DestroyScriptValue(&t, 2);
    from = args[3].p;
    to = args[4].p;
    n = args[5].i;
    mask = args[6].i;
    PushBackMemoryMark();
    if (mask & 1) {
        positions = (u8*)AllocateBackMemory(n * sizeof(ScriptSampleQuad));
    }
    if (mask & 2) {
        rotations = (u8*)AllocateBackMemory(n * sizeof(ScriptSampleRotation));
    }
    if (mask & 4) {
        q4 = (u8*)AllocateBackMemory(n * sizeof(ScriptSampleQuad));
    }
    if (mask & 8) {
        q8 = (u8*)AllocateBackMemory(n * sizeof(ScriptSampleQuad));
    }
    SampleAnimationFrameChain((BlendAnimationView*)anim, a, b, (PlacedObject*)from, (PlacedObject*)to, n, (Vec02*)positions, (Mat02*)rotations,
                  (Vec02*)q4, (Vec02*)q8);
    R11B008Node* head = 0;
    R11B008Node* tail = 0;
    for (s32 bit = 1; bit < 9; bit <<= 1) {
        if (!(mask & bit)) {
            continue;
        }
        R11B008Node* node = NewScriptValueNode();
        if (tail != 0) {
            tail->next = node;
        } else {
            head = node;
        }
        tail = node;
        SetScriptValueTag(node, 0);
        R11B008Node* last = 0;
        for (s32 i = 0; i < n; i++) {
            // The sample's byte offsets into the back-memory buffers, computed before the switch:
            // loop.c then finds every index of i in its first pass and counts the loop down.
            s32 quad = i * sizeof(ScriptSampleQuad);
            s32 rot = i * sizeof(ScriptSampleRotation);
            node = NewScriptValueNode();
            switch (bit) {
            case 1: {
                ScriptSampleQuad* p = (ScriptSampleQuad*)AcquireVectorAPayload();
                *p = *(ScriptSampleQuad*)(positions + quad);
                SetScriptValueVectorA(node, (f32*)p);
                break;
            }
            case 2: {
                f32* m = AcquireMatrixPayload();
                CopyRotationMatrix((Quad16*)m, (const Quad16*)(rotations + rot));
                SetScriptValueMatrix(node, m);
                break;
            }
            case 4: {
                ScriptSampleQuad* p = (ScriptSampleQuad*)AcquireVectorAPayload();
                *p = *(ScriptSampleQuad*)(q4 + quad);
                SetScriptValueVectorA(node, (f32*)p);
                break;
            }
            case 8: {
                ScriptSampleQuad* p = (ScriptSampleQuad*)AcquireVectorAPayload();
                *p = *(ScriptSampleQuad*)(q8 + quad);
                SetScriptValueVectorA(node, (f32*)p);
                break;
            }
            }
            if (last != 0) {
                last->next = node;
            } else {
                SetScriptValueChain(tail, node);
            }
            last = node;
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

// Writes a float into out as a 128-bit value (the float in the low word).
u128* StoreFloatAsQuadword(u128* out, f32 f)
{
    *out = (u128)Vu0::ScalarInGpr(f);
    return out;
}

u128* CopyQuadword(u128* out, void* src)
{
    u128 v = *(u128*)src;
    *out = v;
    return out;
}

u128* StoreQuadword(u128* out, u128 v)
{
    *out = v;
    return out;
}

ASM_FUNC(func_00118D30);

// Evaluator for a variable node: looks the key up through the scope chain and gives back its
// value.
ScriptValue* EvalScriptVariable(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope)
{
    ScriptValue t;
    InitScriptValue(&t);
    LookupScriptVariable(scope, expr->i, 1, &t);
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}

// Evaluator for an assignment node: evaluates the right-hand side, stores it into the existing
// variable of that key in the scope chain (AssignScriptVariable) and gives the value back.
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

// Evaluator for a definition node: evaluates the initial value and defines a new variable of that
// key in the innermost scope (DefineScriptVariable), giving the value back.
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
extern const char g_assertFailedMessage[];
INCLUDE_RODATA(D_00249200);

// The script's assert form: evaluates its condition and, when the value is zero, prints the failure
// message (PrintFormatted). Either way it gives back the empty result (tag 0x22).
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
        PrintFormatted(g_assertFailedMessage);
        IgnoreScriptArgument(&t, 1, w, scope);
        DestroyScriptValue(&t, 2);
    }
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

// The script's if form: evaluates the condition; if it is true (a bool value of 1) it evaluates and
// gives back the then-branch, otherwise the else-branch, or the empty result (tag 0x22) when there
// is no else.
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

// The script's or form: evaluates the operands in order and gives back the first one that is not
// boolean false, without evaluating the rest; false when none is.
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

// The script's and form: starts from true and evaluates the operands in order, stopping at the
// first boolean false (which it gives back); otherwise it gives back the last operand's value.
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

// The script's cond form: each clause is a test followed by a body. It runs the body of the first
// clause whose test is not boolean false (a clause headed by the else marker, node tag 10, always
// matches) and gives back the body's last value, or the test's own value when the body is empty; no
// clause gives the empty result.
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

// The script's case form: evaluates the key, then walks the clauses, each a list of constants and a
// body. The first clause that has a constant identical to the key (TestScriptValuesIdentical), or
// the else clause (node tag 10), has its body evaluated and the last value is the result; no match
// gives the empty result.
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

// The script's let form: when the first operand is a list of (name value) bindings, evaluates each
// value in the outer scope and defines it in a new scope whose parent is the current one; otherwise
// the body runs in the current scope. The remaining operands are evaluated in order and the last
// value is the result.
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

// The script's while form: evaluates the test and, for as long as it is not boolean false,
// evaluates the body; gives back the empty result (tag 0x22).
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

// The script's lambda form: makes a function record (tag 0x1F) holding the defining scope, the
// parameter list, the body and the parameter count; a parameter marker of node tag 0x13 ends the
// fixed parameters and says the function takes the rest of the arguments as a list.
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

// Evaluates a chain of expressions (at least one) in order and gives back the last result.
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

// Evaluator for a sequence node: evaluates each expression after the first in order and gives
// back the last result (the empty value when there are none).
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

// Evaluates a call: the operator is a built-in (tag 0x1D, an index into g_scriptBuiltins), a host
// function (0x21) or a script function (0x1F). The fixed arguments are evaluated into an array and
// extras are collected into a rest list. A built-in or host function is called directly; a script
// function's body runs in a new scope under its defining scope.
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

// The script's import form: takes the entry number written after the operator, finds that script
// entry's scope in the current world (evaluating the entry first if it has not run yet) and adds it
// as another parent of the current scope. Gives back the empty result.
ScriptValue* EvalScriptImportScope(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope)
{
    ScriptValue a;
    ScriptValue b;
    ScriptScope* found;
    s32 id;

    InitScriptValue(&a);
    id = expr->node->next->i;
    found = GetScriptEntryScope(id, (World*)g_currentWorld);
    if (found == 0) {
        EvalScriptEntry(&b, id, (World*)g_currentWorld);
        AssignScriptValue(&a, &b);
        DestroyScriptValue(&b, 2);
        found = GetScriptEntryScope(id, (World*)g_currentWorld);
    }
    AddScriptScopeParent(scope, found);
    SetScriptValueTag(&a, 0x22);
    CopyConstructScriptValue(ret, &a);
    DestroyScriptValue(&a, 2);
    return ret;
}

// The script evaluator: a constant (int, float, vector, bool, pointer, function, empty) evaluates
// to itself, a variable node is looked up in the scope, and a list is dispatched on its head's node
// tag to the form handlers (assign, define, assert, if, or, and, cond, case, let, while, sequence,
// lambda, import; tag 17 quotes its operand). Any other list is a call.
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

// Makes parent the scope's only enclosing scope.
void SetScriptScopeParent(ScriptScope* scope, ScriptScope* parent)
{
    scope->parents[0] = parent;
    scope->count = 1;
}

// Appends parent to the scope's list of enclosing scopes.
void AddScriptScopeParent(ScriptScope* scope, ScriptScope* parent)
{
    scope->parents[scope->count++] = parent;
}

// Adds a new keyed value to the front of the scope's chain and gives back the empty value.
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

// Stores value into the variable of that key found in the scope chain (nothing if there is none)
// and gives back the empty value.
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

// Finds the variable of that key in the scope chain; copies its value into out (when out is not
// null) and gives back 1, or gives back 0 when there is none.
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

// The value stored under key in scope's keyed chain, or 0. With flag set it also searches the
// parent scopes (depth first), using the scope's busy flag to avoid cycles.
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

// Copies a scope into dst: its parent list and a copy of its keyed values chain.
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

// Takes a scope from the pool and clears it (0x1C bytes).
ScriptScope* NewScriptScope(void)
{
    ScriptScope* p = (ScriptScope*)TakePoolEntry(&g_scopePool);
    FillMemory(p, 0, 0x1C);
    return p;
}
// The scope pool's remove callback (installed by value.cpp); it does nothing.
void ReleaseScriptScope(void)
{
}

MarkStacks::MarkStacks()
{
}

MarkStacks::~MarkStacks()
{
}

// Empties the collector's root array and root-list array.
void ResetMarkRoots(MarkStacks* self)
{
    self->rootCount = 0;
    self->listCount = 0;
}

// Called when the script machine shuts down; does nothing.
void ShutDownMarkRoots(MarkStacks* stacks) {}

// Adds value to the collector's root array unless it is already there.
void AddUniqueMarkRoot(MarkStacks* self, MarkEntry* value)
{
    for (int i = 0; i < self->rootCount; i++)
        if (self->roots[i] == value)
            return;
    self->roots[self->rootCount++] = value;
}

void AddMarkRootList(MarkStacks* self, R11B008List* list) { self->lists[self->listCount++] = list; }

void PushMarkObject(MarkStacks* self, MarkEntry* value) { self->objects[self->objectCount++] = value; }

// Pops the top of the collector's object stack, or gives back null when it is empty.
MarkEntry* PopMarkObject(MarkStacks* self)
{
    if (self->objectCount > 0)
        return self->objects[--self->objectCount];
    return 0;
}

void PushMarkChain(MarkStacks* self, MarkEntry* value) { self->chains[self->chainCount++] = value; }

// Pops the top of the collector's chain stack, or gives back null when it is empty.
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

// Pops the top of the collector's record stack, or gives back null when it is empty.
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

// Records the current live end of each of the five script pools (value nodes, scopes, keyed
// values, payloads, property references); a scope copy (base_object.cpp) calls it before it
// allocates.
void MarkPoolLiveEnds(MarkStacks* stacks)
{
    MarkPoolLiveEnd(&g_valueNodePool);
    MarkPoolLiveEnd(&g_scopePool);
    MarkPoolLiveEnd(&g_keyedValuePool);
    MarkPoolLiveEnd(&g_payloadPool);
    MarkPoolLiveEnd(&g_propertyRefPool);
}

// The mark phase of the script pool collector: pops entries off the object, record and chain mark
// stacks until all are empty and marks (MarkPoolEntryUsed) everything they reach, pushing each
// newly marked scope, value chain or function record on the matching stack so it is walked in turn.
void DrainMarkStacks(MarkStacks* self)
{
    MarkEntry* obj;
    MarkEntry* other;
    MarkEntry* group;
    for (;;) {
        group = PopMarkObject(self);
        if (group) {
            MarkEntry* link = group->keyedChain;
            if (link) {
                do {
                    MarkPoolEntryUsed(link);
                    MarkEntry* ev = (MarkEntry*)&link->payload;
                    switch (ev->tag) {
                    case 0x1E:
                        obj = ev->payload;
                        if (IsPoolEntryUnmarked(obj)) {
                            MarkPoolEntryUsed(obj);
                            PushMarkChain(self, obj);
                        }
                        break;
                    case 0x1F:
                        other = ev->payload;
                        if (IsPoolEntryUnmarked(other)) {
                            MarkPoolEntryUsed(other);
                            PushMarkRecord(self, (MarkRecord*)other);
                        }
                        break;
                    case 0x21:
                        MarkPoolEntryUsed(ev->payload);
                        break;
                    }
                    link = link->nextKeyed;
                } while (link);
            }
            if (group->tag > 0) {
                s32 i = 0;
                MarkEntry** p = &group->payload;
                do {
                    obj = *p;
                    if (IsPoolEntryUnmarked(obj)) {
                        MarkPoolEntryUsed(obj);
                        PushMarkObject(self, obj);
                    }
                    i++;
                    p++;
                } while (i < group->tag);
            }
            continue;
        }
        MarkRecord* b = PopMarkRecord(self);
        if (b) {
            obj = b->nodes;
            if (obj) {
                do {
                    MarkPoolEntryUsed(obj);
                    obj = obj->next;
                } while (obj);
            }
            obj = b->thirdEntry;
            if (IsPoolEntryUnmarked(obj)) {
                MarkPoolEntryUsed(obj);
                PushMarkChain(self, obj);
            }
            group = b->scope;
            if (IsPoolEntryUnmarked(group)) {
                MarkPoolEntryUsed(group);
                PushMarkObject(self, group);
            }
            continue;
        }
        obj = PopMarkChain(self);
        if (!obj)
            return;
        switch (obj->tag) {
        case 0x1E:
            other = obj->payload;
            if (IsPoolEntryUnmarked(other)) {
                MarkPoolEntryUsed(other);
                PushMarkChain(self, other);
            }
            break;
        case 0x1F:
            other = obj->payload;
            if (IsPoolEntryUnmarked(other)) {
                MarkPoolEntryUsed(other);
                PushMarkRecord(self, (MarkRecord*)other);
            }
            break;
        case 0x21:
            MarkPoolEntryUsed(obj->payload);
            break;
        }
        obj = obj->next;
        if (obj) {
            if (IsPoolEntryUnmarked(obj)) {
                MarkPoolEntryUsed(obj);
                PushMarkChain(self, obj);
            }
        }
    }
}

// The garbage collector of the script machine's pools: clears the live marks of the five pools,
// marks and walks everything reachable from the registered roots, the root lists, and the queued
// script event handlers of the current world (DrainMarkStacks), then releases every pool entry left
// unmarked.
void CollectScriptPools(MarkStacks* w) {
    ClearPoolLiveStates(&g_valueNodePool);
    ClearPoolLiveStates(&g_scopePool);
    ClearPoolLiveStates(&g_keyedValuePool);
    ClearPoolLiveStates(&g_payloadPool);
    ClearPoolLiveStates(&g_propertyRefPool);
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
    for (QueuedCall* it = (QueuedCall*)g_currentWorld->queuedCallHead; it; it = it->next) {
        if ((void*)it->fn == (void*)RunScriptEventHandler) {
            MarkEntry* e = (MarkEntry*)it->p0C;
            if (e && IsPoolEntryUnmarked(e)) {
                MarkPoolEntryUsed(e);
                PushMarkChain(w, e);
            }
        }
    }
    DrainMarkStacks(w);
    ReleaseDeadPoolEntries(&g_valueNodePool);
    ReleaseDeadPoolEntries(&g_scopePool);
    ReleaseDeadPoolEntries(&g_keyedValuePool);
    ReleaseDeadPoolEntries(&g_payloadPool);
    ReleaseDeadPoolEntries(&g_propertyRefPool);
}
