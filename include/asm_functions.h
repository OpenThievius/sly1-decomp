// SPDX-License-Identifier: AGPL-3.0-or-later
// The functions of retail's original assembly (config/us/original_asm.tsv) that several files
// call, declared once, so that every caller names the same symbol with the same parameters. The
// types are the ones their callers' code shows.
#ifndef ASM_FUNCTIONS_H
#define ASM_FUNCTIONS_H

#include "common.h"

typedef unsigned int u128 __attribute__((mode(TI)));

struct Collider;
struct FacePoint;
struct ImpulseRow;
struct LookSource;
struct Mat3;
struct Mat4A;
struct RangeRecord;
struct TreeNode03;
struct Vec4;
struct World5ModeCollider;

// main/script_machine.cpp's window (0x118D30): a quadword scaled by another.
u128 ScaleQuadword(u128 a, u128 b);
// The plane tree's node a point falls in.
s32 FindPlaneTreeNodeForPoint(Vec4* pos, TreeNode03* nodes);
// Fills the look-direction block out from its source.
void FillLookDirectionBlock(void* out, LookSource* src);
void ComputeWorld5ModeColliderAnchors(World5ModeCollider* self, Vec4* a, Vec4* b);
Mat3 MultiplyByTransposedMatrix3x3(const Mat3& a, const Mat3& b);
s32 ScaleMatrix(Mat4A* out, const Mat4A* in, u128 scale);
u128 TransformVector4(void* m, u128 v);
s32 RangeRecordReachesSphere(RangeRecord* node, void* sphere, f32 radius);
void ApplyColliderInverseInertia(Collider* self, Vec4* in, Vec4* out);
void AddColliderForce(Collider* self, Vec4* force);
void AddColliderTorque(Collider* self, Vec4* torque);
void ComputeColliderPointVelocity(Collider* body, Vec4* point, ImpulseRow* row, Vec4* out);
s32 IsPointInsideFaceTree(TreeNode03* self, FacePoint* value);
f32 SplitVectorAlongAxis(const Vec4* v, const Vec4* axis, Vec4* along, Vec4* rest);
void BuildPerpendicularPair(Vec4* in, Vec4* out, const Vec4* a, const Vec4* b);

// The library's memory, string and thread functions.
s32 CompareMemory(const void* a, const void* b, s32 n);
void* MoveMemory(void* dst, void* src, s32 size);
void RunThread(s32 thread, void* arg);
char* CopyStringBounded(char* dst, const char* src, s32 max);

#endif
