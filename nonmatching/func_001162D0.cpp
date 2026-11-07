// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 295/300 (98.3%), checked 2026-11-07
// NEAR (2026-11-08, vu0w3-e1): all of it but arm 1's branch: retail's bc1tl (the fallback's lq in its delay slot, the tail shared with arm 2) where this has bc1f and its own tail
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


struct MarkEntry {
    s32 f0;                 // 0x00
    MarkEntry* f4;          // 0x04
    MarkEntry* f8;          // 0x08
    MarkEntry* fC;          // 0x0C
    MarkEntry* f10;         // 0x10
    MarkEntry* f14;         // 0x14
};

struct MarkRecord {
    MarkEntry* f0;          // 0x00
    MarkEntry* f4;          // 0x04
    s32 f8;                 // 0x08
    s32 fC;                 // 0x0C
    MarkEntry* f10;         // 0x10
};

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

typedef f32 (*MathFn_259938)(f32 x);

f32* AcquireVectorAPayload(void);
f32* AcquireMatrixPayload(void);
f32* AcquireVectorBPayload(void);
f32* AcquirePairPayload(void);
f32* AcquireTriplePayload(void);
R11B008Key* NewKeyedValue(void);
void CopyKeyedValueChain(R11B008Key* src, R11B008Key* dst, s32 first);

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

extern ScriptBuiltin g_scriptBuiltins[];
extern s32 D_00259DE8;

s32 IsPoolEntryUnmarked(MarkEntry* e);
void MarkPoolEntryUsed(MarkEntry* e);

s32 FindNearestSpanObject(Quad16* z, s32 a, s32 b, s32 c, void** d, ColliderSpan* e);

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

typedef u64 Quad_118D10 __attribute__((mode(TI)));

typedef u64 Quad_118D20 __attribute__((mode(TI)));

Quad_118D10* CopyQuadword(Quad_118D10* out, void* src);
Quad_118D20* StoreQuadword(Quad_118D20* out, Quad_118D20 v);

ScriptValue* EvalScriptVariable(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope);
ScriptValue* EvalScriptAssign(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope);
ScriptValue* EvalScriptDefine(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope);
ScriptValue* EvalScriptAssert(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope);
ScriptValue* EvalScriptIf(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope);
ScriptValue* EvalScriptOr(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope);
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

void SetScriptScopeParent(ScriptScope* scope, ScriptScope* parent);
void AddScriptScopeParent(ScriptScope* scope, ScriptScope* parent);
ScriptValue* DefineScriptVariable(ScriptValue* ret, ScriptScope* scope, s32 key, ScriptValue* value);
ScriptValue* AssignScriptVariable(ScriptValue* ret, ScriptScope* scope, s32 key, ScriptValue* value);
s32 LookupScriptVariable(ScriptScope* scope, s32 key, s32 flag, ScriptValue* out);
ScriptValue* FindScriptVariable(ScriptScope* scope, s32 key, s32 flag);
void CopyScriptScope(ScriptScope* src, ScriptScope* dst);
ScriptScope* NewScriptScope(void);
void ReleaseScriptScope(void);

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


ScriptValue* NormalizeScriptVector(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue obj;
    InitScriptValue(&obj);
    Vec02* out = (Vec02*)AcquireVectorAPayload();
    u128 a = Vu0::Q(*(Vec02*)args[0].v);
    Vu0::Q(*out) = a;
    if (args[1].tag == 0) {
        u128 fb = *(u128*)&D_00248D30;
        u128 len = Vu0::Length(a);
        if (Vu0::ToFloat(len) < 0.0001f) {
            *(u128*)out = fb;
        } else {
            Vu0::Q(*out) = Vu0::DivX(a, len);
        }
    } else {
        Vec02* fb = (Vec02*)args[1].node->v;
        u128 len = Vu0::Length(a);
        if (Vu0::ToFloat(len) < 0.0001f) {
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

