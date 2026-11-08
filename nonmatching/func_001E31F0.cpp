// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 4984/4996, checked 2026-11-08
// NEAR (2026-11-08, large-1E31F0): python3 tools/check.py nonmatching/func_001E31F0.cpp func_001E31F0 -- 1246 instructions against 1249; regdiff "code", 1053/1249 equal ignoring registers. The frame is 0x30 short: retail's locals end at 0xE0 before the nine cylindrical floats (E0..100, given their slots last by purge_addressof, as ours are at B0..D0), three 16-byte slots (0xB0..0xDF) nothing in retail reads or writes; every vector local (0x00..0xA0: blended, sum, goal/frame, dir, two orbits, offset, d/stick/polar, Scalar and FromFloats slots/toCam/pos, axis/Scalar, fwd/prof) already sits at retail's offset.
// Still differs: (1) the 48-byte gap is CLOSED (2026-11-08, frame-1E31F0): an unused `Mat02 basis;` declared after `Vec02 fwd;` in the else block that reads target->m110 gives frame 0x210 and the floats at E0 (before it: 1178 equal, after: 1183/1249 equal ignoring registers). Declared before fwd it scores worse. (2) Registers: the stick vector from FromFloats stays in a VU0 register (retail keeps it in a0 and reloads it into vf1 and vf3), the cam spill reload uses a0 for v1, t1 takes f1 for f12 in the hold test, w in case 4 takes f5 for f7. (3) Order: the switch cases' pitch loads (block +0x5C) are cross-jumped into the join (retail keeps one per case), case 4's interpolation loads block +0x58 late, the tail's spring for +0x48/+0x4C schedules its second +0x80 load differently.
// In the context of its file, src/main/file_1E08F8.cpp: its declarations before the function, bodies cut.
#include "common.h"
#include "asm_func.h"
#include "on_off_object.h"
#include "collider.h"
#include "world.h"
#include "camera_controller.h"
#include "camera.h"
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
#include "pad_record.h"
#include "ramp_profile.h"
#include "value_range.h"

extern f32 g_gameClock[];
struct CameraPlacement { Vec02 q[5]; };
void* GetOnOffObjectBlock(void* self);
void func_001E30E8(OnOffCameraController* self, CameraPlacement* eye);
void BlendOnOffCameraPoint(void* block, CameraPlacement* eye, Vec02* out, OnOffObject* object);
void PlaceOnOffCameraFrame(OnOffObject* object, Vec02* eye, Vec02* x, Vec02* dir);
void PlaceOnOffCameraOrbit(f32 angle, f32 offset, OnOffObject* self, f32* x, f32* poly, f32* range, s32 mode, Vec02* out);
void ConvertOffsetToCylindrical(void* camera, Vec02* point, f32* a, f32* b, f32* c);
void ComputePolarOffset(Vec02* out, f32 a, f32 b, f32 c);
struct OnOffCameraView {
    u8 pad00[0x0C];
    f32 f0C;
    f32 f10;
    f32 f14;
    s32 f18;
    f32 f1C;
    s32 f20;
    s32 active24;
    s32 f28;
    f32 f2C;
    f32 f30;
    f32 f34;
    f32 f38;
    f32 f3C;
    f32 f40;
    f32 f44;
    f32 f48;
    f32 f4C;
    Vec02 v50;
    f32 f60;
};

extern s32 D_0026FA64;
extern f32 D_00261920;
extern f32 D_00261924;
extern s32 D_00275978;
extern f32 D_00275A28;
extern f32 D_00275A2C;
extern f32 D_00275A30[4];
extern f32 D_00275A40[4];
extern f32 D_00275A50[2];
extern f32 D_00275A58[6];
extern f32 D_00275A70[4];
extern RampProfile D_00275A80;
extern RampProfile D_00275A90;
extern ValueRange g_unitRange;
f32 WrapAngle(f32 a);
f32 ClampToMagnitude(f32 a, f32 b);
f32 ClampToRange(ValueRange* range, f32 v);
f32 ApproachValueWithRamp(f32 value, f32 target, f32 dt, RampProfile* profile, f32* speed);
f32 ApproachAngleWithRamp(f32 angle, f32 target, f32 dt, RampProfile* profile, f32* speed);
f32 ApproachAngleClampingVelocity(f32 angle, f32 speed, f32 target, f32 dt, RampProfile* profile, f32* out);
void SpringCameraVector(Camera* cam, Vec02* pos, Vec02* vel, Vec02* goal, f32 a, f32 b, f32 dt);
void StartSoundEffect(s32 id, s32 a, s32 b, s32 c, f32 f0, f32 f1, f32 f2, f32 f3, f32 f4, s32 d, s32 e);
void ClearPadPressedBits(PadRecord* self, s32 mask);
void TransformDirectionBetweenFrames(void* from, void* to, Vec02* in, Vec02* out);
void FindFreeOnOffCameraAngle(OnOffCameraController* self, Vec02* center, Vec02* in, Vec02* out);
void FindFreeOnOffCameraScreenSpan(OnOffCameraController* self, Vec02* center);
void func_00145E68(Camera* cam, Vec02* from, Vec02* in, Vec02* out);
void func_00145718(Camera* cam, Vec02* center, Vec02* pos, f32 a, f32 b);
void func_00143BE0(Camera* cam);

void UpdateOnOffCameraController(OnOffCameraController* self, CameraPlacement* eye, PadRecord* pad, f32 dt)
{
    OnOffCameraView* view = (OnOffCameraView*)self;
    f32 step;
    if (D_0026FA64 != 0) {
        step = g_gameClock[2];
    } else {
        step = g_gameClock[5];
    }
    Camera* cam = self->owner;
    OnOffObject* object = (OnOffObject*)self->ptr;
    Player* target = (Player*)cam->stack[0].target;
    s32 flags;
    s32 hold;
    s32 limit;
    if (object != 0) {
        flags = object->i414;
        hold = object->f418;
        limit = object->f41C;
    } else {
        limit = 0;
        flags = 4;
        hold = 0;
    }
    func_001E30E8(self, eye);
    f32* block = (f32*)GetOnOffObjectBlock(object);
    Vec02 blended;
    Vec02 sum;
    BlendOnOffCameraPoint(block, eye, &blended, object);
    if (target == g_player && target->f268C == 2) {
        Vec02 goal;
        Vu0::Q(goal) = Vu0::Sub(Vu0::Q(target->v2690), Vu0::Q(blended));
        SpringCameraVector(g_camera, (Vec02*)((u8*)g_camera + 0x270), (Vec02*)((u8*)g_camera + 0x280), &goal, 8.0f, -6.0f, dt);
    }
    Vu0::Q(sum) = Vu0::Add(Vu0::Q(blended), Vu0::Q(*(Vec02*)((u8*)g_camera + 0x270)));
    view->f44 = ApproachValueWithRamp(view->f44, (*(s32*)&eye->q[0] & 1) ? 0.0f : block[25], dt, &D_00275A80, 0);
    view->f40 = eye->q[3].z >? view->f40;
    Vec02 frame;
    Vec02 dir;
    Vec02 orbit1;
    Vec02 orbit2;
    f32 angle1, dist1, height1;
    f32 angle2, dist2, height2;
    if (object != 0 && (flags & 3)) {
        PlaceOnOffCameraFrame(object, &blended, &frame, &dir);
        if (object->f380 != 0) {
            ConvertOffsetToCylindrical(&frame, (Vec02*)&D_00248D30, &frame.x, &frame.y, &frame.z);
            if (view->active24 == 0) {
                frame.x += ClampToMagnitude(WrapAngle(view->f34 - frame.x), *(f32*)&object->f390);
            }
            view->f34 = frame.x;
        }
        if (flags & 1) {
            PlaceOnOffCameraOrbit(object->angle3A0, *(f32*)&object->block2F0, object, &frame.x,
                                  (f32*)((u8*)object + 0x300), (f32*)((u8*)object + 0x330), 1, &orbit1);
            ConvertOffsetToCylindrical(&orbit1, &sum, &angle1, &dist1, &height1);
        }
        if (object->i414 & 2) {
            PlaceOnOffCameraOrbit(object->angle3A0, *(f32*)&object->block2F0, object, &frame.x,
                                  (f32*)((u8*)object + 0x300), (f32*)((u8*)object + 0x330), 2, &orbit2);
            ConvertOffsetToCylindrical(&orbit2, &sum, &angle2, &dist2, &height2);
        }
    }
    if (view->active24 != 0) {
        view->f20 = 4;
    }
    if (cam->f224 != 0) {
        if (cam->f228 != 0) {
            view->f20 = 4;
            view->f0C = cam->f22C;
        } else if (!(flags & 3)) {
            view->f20 = 4;
            view->f0C = eye->q[3].x;
        } else if (!(flags & 2)) {
            view->f20 = 1;
        } else if (flags & 1) {
            f32 a = WrapAngle(angle1 - eye->q[3].x);
            f32 b = WrapAngle(angle2 - eye->q[3].x);
            if (__builtin_fabsf(a) < __builtin_fabsf(b)) {
                view->f20 = 1;
            } else {
                view->f20 = 2;
            }
        } else {
            view->f20 = 2;
        }
        view->f40 = g_gameClock[1];
        view->f30 = g_gameClock[1] - 10.0f;
    }
    if ((view->f20 & flags) == 0 && 0 < view->f20 && view->f20 < 3) {
        view->f20 = 4;
    }
    Vec02 offset;
    if (object != 0 && *(PlacedObject**)((u8*)object + 0x444) != 0) {
        Vec02 d;
        Vu0::Q(d) = Vu0::Sub(Vu0::Q((*(PlacedObject**)((u8*)object + 0x444))->v140), Vu0::Q(eye->q[1]));
        d.z = 0.0f;
        const u128& zero = Vu0::Q(D_00248D30);
        Vu0::Vec v = Vu0::Vec::Of(d);
        Vu0::Vec l = Vu0::Length(v);
        if (Vu0::ToFloat(l) < 0.0001f) {
            Vu0::Set(d, zero);
        } else {
            Vu0::Set(d, Vu0::DivX(v, l).q);
        }
        f32 x = Vu0::ToFloat(l);
        f32* poly = (f32*)&object->quad450;
        f32 p = poly[0] + x * (poly[1] + x * poly[2]);
        f32 s = ((ValueRange*)&object->pack460)->Clamp(p);
        Vu0::Set(offset, Vu0::MulX(Vu0::Vec::Of(d).q, Vu0::Scalar(s)));
    } else {
        offset = eye->q[2];
    }
    f32 angle = view->f0C;
    if (pad->flags & 0x400) {
        if (flags & 4) {
            ClearPadPressedBits(pad, 0x400);
            StartSoundEffect(3, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            view->f18 = 1;
            view->f1C = WrapAngle(eye->q[3].x);
            view->f30 = g_gameClock[1];
            view->f28 = 1;
            goto done;
        }
    } else if (flags & 4) {
        if (0.0f < pad->f7C || view->f2C != 0.0f || view->f18 != 0) {
            if (view->f20 != 4) {
                StartSoundEffect(3, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            }
            if (0.0f < pad->f7C) {
                view->f18 = 0;
            }
            if (view->f18 != 0) {
                angle = ApproachAngleClampingVelocity(view->f0C, view->f2C, view->f1C, step, &D_00275A90, &view->f2C);
                if (angle == view->f1C) {
                    view->f18 = 0;
                }
            } else {
                f32 x = pad->f74;
                f32 lim = D_00275A30[0] * step;
                f32 v = view->f2C;
                f32 lo = v - lim;
                f32 hi = v + lim;
                f32 want = x * __builtin_fabsf(x) * D_00275A2C;
                f32 nv = (want < lo) ? lo : ((hi < want) ? hi : want);
                view->f2C = nv;
                angle = WrapAngle(view->f0C + nv * step);
            }
            view->f20 = 4;
            view->f30 = g_gameClock[1];
            view->f28 = 1;
            goto done;
        }
    }
    if (view->f20 == 4) {
        Vec02 stick;
        Vu0::Set(stick, Vu0::FromFloats(pad->f40, pad->f44, 0.0f));
        Vu0::Set(stick, Vu0::NormalizeOr(Vu0::Vec::Of(stick).q, Vu0::Q(g_unitXVector)));
        Vec02 toCam;
        Vu0::Q(toCam) = Vu0::Sub(Vu0::Q(sum), Vu0::Q(cam->f40));
        toCam.z = 0.0f;
        const u128& unitX = Vu0::Q(g_unitXVector);
        Vu0::Vec v = Vu0::Vec::Of(toCam);
        Vu0::Vec l = Vu0::Length(v);
        if (Vu0::ToFloat(l) < 0.0001f) {
            Vu0::Set(toCam, unitX);
        } else {
            Vu0::Set(toCam, Vu0::DivX(v, l).q);
        }
        f32 dist = Vu0::ToFloat(l);
        s32 sel;
        if (object == 0 || (sel = object->f430) == -1) {
            sel = *(s32*)&eye->q[3].w;
        }
        Vec02 axis;
        switch (sel) {
        case 0:
            Vu0::Q(axis) = Vu0::Cross(Vu0::Q(g_unitZVector), Vu0::Q(toCam));
            break;
        case 1:
            axis = toCam;
            break;
        }
        f32 turn = ClampToMagnitude(Vu0::ToFloat(Vu0::Dot(Vu0::Q(offset), Vu0::Q(axis))) / dist, D_00275A28) * view->f44;
        f32 y = stick.y;
        turn *= ((ValueRange*)D_00275A50)->Clamp(D_00275A40[0] + y * (D_00275A40[1] + y * D_00275A40[2]));
        f32 t = g_gameClock[1] - view->f30;
        turn *= g_unitRange.Clamp(D_00275A70[0] + t * (D_00275A70[1] + t * D_00275A70[2]));
        f32 next = WrapAngle(angle + turn * dt);
        if (!(flags & 3)) {
            angle = next;
            goto done;
        }
        f32 weight;
        f32 goal;
        if (object->obj == 0 && object->f38C == 0) {
            weight = 1.0f;
            goal = angle1;
        } else if (target == g_player && object == target->f2678) {
            weight = 3.0f;
            goal = angle1;
        } else if (view->f20 == 1) {
            weight = 1.0f;
            goal = angle1;
        } else if (view->f20 == 2) {
            weight = 1.0f;
            goal = angle2;
        } else {
            Vec02 fwd;
            Mat02 basis;
            if (target == g_player && target->f2220 == 13) {
                fwd = target->v150;
            } else {
                fwd = target->m110.r[0];
            }
            fwd.z = 0.0f;
            Vu0::Set(fwd, Vu0::NormalizeOr(Vu0::Vec::Of(fwd).q, Vu0::Q(g_unitXVector)));
            TransformDirectionBetweenFrames(object, 0, &dir, &dir);
            f32 d = Vu0::ToFloat(Vu0::Dot(Vu0::Vec::Of(fwd).q, Vu0::Vec::Of(dir).q));
            weight = d * d * (3.0f - __builtin_fabsf(d));
            if (!(flags & 2) || 0.0f < d) {
                goal = angle1;
            } else {
                goal = angle2;
            }
        }
        f32 speed;
        if (g_player != 0) {
            if (g_player->f2220 == 6 && g_player->f239C == 0) {
                f32 one = 1.0f;
                speed = one <? Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(offset), Vu0::Q(offset)))) * 0.005f;
            } else {
                f32 one = 1.0f;
                speed = one <? Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(offset), Vu0::Q(offset)))) * 0.0016666667f;
            }
        } else {
            speed = 0.0f;
        }
        speed *= block[26];
        if (limit != 0) {
            f32 t1 = g_gameClock[1] - (view->f40 + 0.75f);
            f32 t2 = g_gameClock[1] - (view->f30 + 10.0f);
            f32 s = 0.0f;
            if (0.0f < object->f428) {
                s = ClampToRange(&g_unitRange, t1 / object->f428);
                s *= ClampToRange(&g_unitRange, t2 / object->f428);
            } else if (0.0f < t1 && 0.0f < t2) {
                s = 1.0f;
            }
            s *= object->f42C;
            if (speed * weight < s) {
                weight = 1.0f;
                speed = s;
            }
        }
        if (hold != 0 && view->f28 == 0) {
            f32 s;
            if (0.0f < object->f420) {
                s = ClampToRange(&g_unitRange, (g_gameClock[1] - object->f39C) / object->f420);
            } else {
                s = 1.0f;
            }
            s *= object->f424;
            if (speed * weight < s) {
                weight = 1.0f;
                speed = s;
            }
        }
        RampProfile prof;
        prof.maxSpeed = D_00275A58[0] * speed;
        prof.endSpeed = D_00275A58[1] * speed;
        prof.rampTime = D_00275A58[2];
        f32 a = ApproachAngleWithRamp(angle, WrapAngle(angle + WrapAngle(goal - angle)), dt, &prof, 0);
        f32 da = __builtin_fabsf(WrapAngle(goal - a));
        if (__builtin_fabsf(WrapAngle(goal - next)) < da) {
            a = next;
        }
        f32 e1 = WrapAngle(next - angle);
        f32 e2 = WrapAngle(a - angle);
        angle = WrapAngle(angle + (1.0f - weight) * e1 + weight * e2);
        if (view->active24 == 0) {
            if ((flags & 1) &&
                (WrapAngle(view->f0C - view->f38) * WrapAngle(angle - angle1) <= 0.0f ||
                 __builtin_fabsf(WrapAngle(angle - angle1)) < 0.0001f) &&
                __builtin_fabsf(WrapAngle(angle - angle1)) < 1.5707964f) {
                view->f28 = 1;
                view->f20 = 1;
            } else if ((flags & 2) &&
                       (WrapAngle(view->f0C - view->f3C) * WrapAngle(angle - angle2) <= 0.0f ||
                        __builtin_fabsf(WrapAngle(angle - angle2)) < 0.0001f) &&
                       __builtin_fabsf(WrapAngle(angle - angle2)) < 1.5707964f) {
                view->f20 = 2;
                view->f28 = 1;
            }
        }
    }
done:
    f32 placeAngle, placeDist, placeHeight;
    f32 roll;
    f32 pitch;
    switch (view->f20) {
    case 1:
        placeAngle = angle1;
        placeDist = dist1;
        placeHeight = height1;
        roll = block[22];
        pitch = block[23];
        break;
    case 2:
        placeAngle = angle2;
        placeDist = dist2;
        placeHeight = height2;
        roll = -block[22];
        pitch = block[23];
        break;
    case 4:
        placeAngle = angle;
        if (!(flags & 3)) {
            placeDist = __builtin_fabsf(block[0]);
            placeHeight = block[12];
            roll = block[22];
            pitch = block[23];
        } else {
            f32 w;
            if (!(flags & 2)) {
                w = 1.0f;
            } else if ((flags & 1) == 0) {
                w = 0.0f;
            } else {
                if (angle1 > view->f0C && angle2 > view->f0C) {
                    if (angle2 < angle1) {
                        angle1 -= 6.2831855f;
                    } else {
                        angle2 -= 6.2831855f;
                    }
                } else if (angle1 < view->f0C && angle2 < view->f0C) {
                    if (angle1 < angle2) {
                        angle1 += 6.2831855f;
                    } else {
                        angle2 += 6.2831855f;
                    }
                }
                w = (view->f0C - angle2) / (angle1 - angle2);
                w = w * w * (3.0f - (w + w));
            }
            f32 iw = 1.0f - w;
            f32 r = block[22];
            placeDist = w * dist1 + iw * dist2;
            placeHeight = w * height1 + iw * height2;
            roll = w * r + iw * -r;
            pitch = block[23];
        }
        break;
    }
    if (cam->f224 == 0) {
        view->f48 = (block[33] * D_00261924 * dt + 1.0f) * view->f48 + (placeDist - view->f10) * block[32] * D_00261920 * dt;
        placeDist = view->f10 + view->f48 * dt;
        view->f4C = (block[33] * D_00261924 * dt + 1.0f) * view->f4C + (placeHeight - view->f14) * block[32] * D_00261920 * dt;
        placeHeight = view->f14 + view->f4C * dt;
    } else {
        view->f4C = view->f48 = 0.0f;
    }
    Vec02 polar;
    ComputePolarOffset(&polar, placeAngle, placeDist, placeHeight);
    Vec02 pos;
    Vu0::Q(pos) = Vu0::Add(Vu0::Q(sum), Vu0::Q(polar));
    if (object == 0 || *(s32*)((u8*)object + 0x440) == 0) {
        if (cam->f224 != 0) {
            if (cam->f228 == 0) {
                FindFreeOnOffCameraAngle(self, &sum, &pos, &pos);
            }
        } else if (D_00275978 == 0) {
            func_00145E68(cam, &view->v50, &pos, &pos);
        }
    }
    ConvertOffsetToCylindrical(&pos, &sum, &placeAngle, &placeDist, &placeHeight);
    view->v50 = pos;
    ComputePolarOffset(&polar, placeAngle, placeDist, placeHeight);
    u128 len = Vu0::Length(Vu0::Q(polar));
    f32 l = Vu0::ToFloat(len);
    Vu0::Q(pos) = Vu0::Add(Vu0::Q(sum), Vu0::MulX(Vu0::Q(polar), Vu0::Scalar((l + cam->f1E4) / l)));
    func_00145718(cam, &sum, &pos, roll, pitch);
    view->f0C = placeAngle;
    view->f10 = placeDist;
    view->f14 = placeHeight;
    view->f38 = angle1;
    view->f3C = angle2;
    func_00143BE0(cam);
    view->active24 = 0;
    FindFreeOnOffCameraScreenSpan(self, &sum);
}
