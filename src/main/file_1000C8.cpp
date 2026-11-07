// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "script_value.h"
#include "shapes.h"
#include "base_object.h"
#include "placed_object.h"
#include "collider.h"
#include "switched_collider.h"
#include "c1f.h"
#include "masked_collider.h"
#include "trigger_zone.h"
#include "zone_collider.h"
#include "object_set.h"
#include "timed_object.h"
#include "contact_tracker.h"
#include "child_group_object.h"
#include "target_follower.h"
#include "c4a.h"
#include "c4c.h"
#include "lookup_object.h"
#include "effect_spawner.h"
#include "c5d.h"
#include "c60.h"
#include "c62.h"
#include "step_sequence.h"
#include "camera.h"
#include "transform_object.h"
#include "object_sub_group.h"
#include "animation.h"
#include "state_graph.h"
#include "c8b.h"
#include "object_pool.h"
#include "oscillator.h"
#include "entry_queue.h"
#include "timeline.h"

// The kinds a property's arguments are read as (func_001C23B0's fourth argument): one word per
// argument, copied from the file's .rodata into the frame as one block.
struct Kinds2 { s32 k[2]; };
struct Kinds3 { s32 k[3]; };
struct Kinds4 { s32 k[4]; };
struct Kinds5 { s32 k[5]; };
struct Kinds6 { s32 k[6]; };

struct Obj_101D38;

void func_00123AB0(void* object, s32 mode);
s32 func_00123D08(StateTrigger* self, s32 a1, s32 a2, s32 a3, s32 a4);
void func_001250C8(void* p);
s32 func_00126CB8(void* self, f32 value);
s32 func_00126D60(void* self, f32 value);
void* func_00129B98(void* self, s32 key);
void* func_00129C20(void* self, s32 key);
void* func_00129CA8(void* self);
void func_0012A8B8(void* p);
void func_0012A8C8(void* p);
void func_0012A8D8(PlacedObject* self, s32 a, f32 x, f32 y);
void func_0012AA50(void* self, f32 a, f32 b);
void func_0012AAE8(void* self, f32 value);
void func_0012AF38(PlacedObject* self, s32 value, Quad16* src, f32 x, f32 y, f32 z);
void func_0012B010(void* p);
void func_0012B5B8(PlacedObject* x, s32 a, s32 b);
void* func_0012C7D8(Animation* self, s32 a1, f32 f1, f32 f2, s32 a2);
void* func_0012C8F8(Animation* item, s32 a, f32 x, f32 y, s32 b, s32 c);
f32 func_0012CCC0(void* obj, s32 id);
void func_0012E760(void* obj);
void func_0012E928(void* obj, s32 a, s32 b);
void func_0012F0A0(Obj_101D38* self, s32 a, f32 x, f32 y);
void func_0012F190(void* obj, s32 v);
s32 func_001300E8(void* list, s32 value);
void func_0013BE00(void* p, f32 x);
void func_0013BF68(void*);
s32 func_00140750(TriggerZone* self, s32 a1, s32 a2, s32 a3, s32 a4);
s32 func_00140770(ZoneCollider* self, s32 a1, s32 a2, s32 a3, s32 a4);
s32 func_00141170(void*,void*);
void func_001455F0(void* p);
void func_00145FB8(void*,s32);
s32 func_00145FD8(void*);
s32 func_00145FF8(void* x);
void func_00146018(Camera* obj, s32 value, f32 first, f32 second);
void func_00146028(void* x);
s32 func_00146038(void* obj, void* p, f32 x, f32 y);
void func_00150408(void*);
void func_00150418(void*,s32);
void func_00150750(void* x);
void func_00150760(void* x);
void func_001518B8(void* x);
void func_001519A8(void* x);
void func_001519E0(StepSequence* p, s32 a, s32 b);
void func_001557D0(void* self, s32 a, s32 b, f32 x, f32 y, f32 z, f32 w);
void func_00155F78(void* p, f32 x);
void func_00155F90(void* x);
void func_00155FA0(void* x);
void func_00158730(void* x);
void func_00158778(C77* self, s32 a, s32 b, Quad4* u, Quad4* v, f32 x, f32 y);
void func_00158D40(void* self, s32 a, s32 b, f32 x, f32 y, f32 z, f32 w);
void func_00159ED0(void* x);
s32 func_0015AA50(void*,void*);
void func_0016DCF0(void*);
void func_0016DD00(void*);
void func_00171F28(void* self, void* v, f32 x, f32 y);
void func_00171FE0(void*);
void func_001777F8(void*,s32);
void func_00177800(void*,s32);
void func_001781E0(void* obj, s32 v);
void func_00178258(void* obj, s32 v);
void func_00178280(void*,s32);
void func_0017AD50(void* x);
void func_0017B550(void* self, s32 index);
void func_0017B598(void* x);
void func_0017CDE0(void*);
void func_0017CE20(void* x, s32 v);
void func_0017CE80(void*);
void* func_0017CFC8(void* x, s32 v);
void* func_0017CFF0(void* x, s32 v);
void* func_0017D018(void* x, s32 v);
void func_0017D040(void* self, s32 value);
void* func_0017D078(void* self, s32 value);
void func_0017D0A0(void* self, s32 a, f32 value);
void* func_0017D0D8(EntryQueue* p, s32 a, s32 b);
void func_0017D100(EntryQueue* self, s32 b, s32 c, s32 d, s32 e);
void func_0017D148(EntryQueue* self, s32 a, s32 b, f32 value);
void func_0017D180(EntryQueue* self, s32 a, s32 b, f32 value);
void func_0017D1B8(void* self, s32 b, s32 c, s32 d);
void func_0017D1E8(void* x, f32 f);
s32 func_0017D220(void* x);
void func_00182948(void* a0, s32 a1, f32 x);
void func_00182DD8(void* p);
s32 func_00182F40(void* e, s32 v);
void* func_00183058(BaseObject* x, s32 a, s32 b);
s32 func_001833F0(void* key, s32 item);
void func_00183910(BaseObject* x, s32 a, s32 b);
void func_00183990(BaseObject* x, s32 a, s32 b);
void func_00183A10(void* a0, s32 a1, f32 x);
void func_00183A90(void* a0, s32 a1, Quad16* a2);
void func_00183B20(void* a0, s32 a1, Quad16* a2);
void func_00183BB8(BaseObject* x, s32 a, s32 b);
void func_00183C38(void* a0, s32 a1, Quad16* a2);
void func_0018AC58(C0C* st);
void func_0018DD50(void*,s32);
void func_0018DD78(void*,s32);
s32 func_00190660(void* x, s32 v);
void func_00192418(void* o);
void func_001993C0(void* x);
void func_00199AF0(void* p);
void func_0019AD30(C17* p, s32 a, s32 b);
void func_0019CE28(C8B* value, f32 x, f32 y, f32 z);
void func_0019CE38(C8B* self, f32 x, f32 y, f32 z);
s32 func_001A8150(ObjectPool* self, s32 a1, s32 a2, s32 a3, s32 a4);
void func_001A8778(void*,s32);
void func_001A87A8(void*,s32);
void func_001A87E0(ObjectPool* p, s32 a, s32 b);
void func_001A8AF8(void*);
s32 func_001A8C90(void* obj, s32 v);
void func_001A93E8(void* x);
void func_001A9438(void* x);
void func_001A9498(void*);
void func_001A9C58(C0D* self, s32 a, s32 b, s32 c);
void func_001B0470(void* p, f32 x);
void func_001B0488(void* p, f32 x);
void* func_001B6290(StateGraph* a, s32 b, s32 c, s32 d);
void func_001B6438(void* x);
void func_001B70B0(C09* p, s32 a, s32 b);
void func_001BB1E0(void* self, u32 value);
s32 func_001BC670(void* x, void* out);
void func_001C08B0(World* x, s32 a, s32 b);
void func_001C0950(void* p);
void func_001C09D8(World* x, s32 a, s32 b);
void func_001C3F68(void* self, s32 value);
void func_001C4180(void* self, s32 value);
void func_001C41A0(void* self, s32 value);
void func_001C8FD0(Agent* p, s32 a, s32 b);
void func_001CA608(Agent* self, s32 a, s32 b);
void func_001CA658(Agent* self, s32 a, s32 b);
void* func_001CA6D0(void* obj, s32 v);
void func_001CA720(Agent* self, s32 a, s32 b);
void func_001CA898(Agent* p, s32 a, s32 b);
void func_001CA960(Agent* self, s32 a, s32 b);
s32 func_001CAD60(Agent* self, s32 a1, s32 a2, s32 a3, s32 a4);
void func_001CB328(void*, s32);
void func_001D2830(void*,s32);
void func_001D31D0(void*,s32);
void func_001D32D8(C4C* self, s32 a, s32 b);
void func_001D6CB0(void* obj);
void func_001DB110(void*,s32);
void func_001DB1E8(C19* item, s32 a, f32 x, f32 y, s32 b, s32 c);
void func_001DB290(C19* st);
void func_001DBAC0(World* self, s32 a, s32 b);
s32 func_001DBAE0(void*,s32);
void* func_001DBB00(World* self, s32 a, s32 b);
s32 func_001DD690(void* self, s32 obj);
s32 func_001DD6B0(void* self, s32 obj);
s32 func_001DD6D0(void* self, s32 obj);
s32 func_001DD6F0(void* self, s32 obj);
s32 func_001DD710(void* x, s32 v);
s32 func_001DD758(void* x, s32 v);
s32 func_001DD7A0(void* x, s32 v);
void func_001DD7E8(World* self, void* obj, s32 key, s32 value);
s32 func_001DD888(World* self, s32 a, s32 b);
s32 func_001DD8E8(void* x, s32 v);
s32 func_001DD908(void* self, s32 index);
s32 func_001DD928(void* self);
void func_001DD950(World* unused, s32 a, s32 b, void* c);
void func_001DDA20(void* a);
void func_001DDA50(void*);
void func_001DDAD0(void* x);
void func_001DDB20(World* self, s32 a, s32 b);
void func_001DDB58(void* x);
void func_001DDBB8(void* x);
s32 func_001DDBF8(void*,s32);
s32 func_001DDC18(void* unused, s32 p);
void func_001DDC78(void*,s32);
void func_001DDC90(void*,s32);
void func_001EC528(void* x);
void func_001ED018(void* self, s32 value);
void func_001ED020(void* x);
void func_001ED090(C13* p, s32 a, s32 b);
void func_001ED0D8(void* self, s32 value);
void func_001ED558(Timeline* self, s32 p, f32 f, s32 q);
void func_001ED588(Timeline* self, s32 p, f32 f, s32 q);
void func_001ED5B8(Timeline* self, s32 p, f32 v);
void func_001ED5D8(Timeline* self, s32 p, f32 v);
void func_001ED5F8(Timeline* self, s32 p, f32 v);
void func_001ED618(Timeline* self, s32 p, f32 v);
void func_001EF830(void* o);
s32 func_001EF8C0(C62* self, s32 a1, s32 a2, s32 a3, s32 a4);
void func_001F36E8(void*);
void func_001F3768(void* x);
void func_001F3928(void* self, f32 a, f32 b, f32 c, f32 d);
void func_001F3990(void* self, f32 a, f32 b, f32 c, f32 d);
void func_001F4008(void* x);
s32 func_001F42D0(TransformObject* self, s32 a1, s32 a2, s32 a3, s32 a4);
void func_001F4808(void* x);
void func_001F4ED0(void*);
void func_001F4F20(void* p);
void func_001F5210(void* p);

// Reads a property call's arguments: count values of args, each as its kind in kinds, through
// the pointers that follow (func_001C1BF8, src/main/file_1C05D0.cpp); gives back a value.
ScriptValue* func_001C23B0(ScriptValue* ret, s32 count, ScriptValue* args, const void* kinds, ...);

// The file's .rodata: the argument signatures its functions copy, in retail's order.
extern const s32 D_00248D80[2] = { 0x2000, 0x2000 };
extern const s32 D_00248D88[2] = { 0x14, 0 };
extern const s32 D_00248D90[2] = { 0x14, 5 };
extern const s32 D_00248D98[2] = { 0x14, 1 };
extern const s32 D_00248DA0[2] = { 0x14, 9 };
extern const s32 D_00248DA8[2] = { 0x14, 10 };
extern const s32 D_00248DB0[2] = { 0x14, 6 };
extern const s32 D_00248DB8[2] = { 0x14, 2 };
extern const s32 D_00248DC0[4] = { 1, 1, 0x1000, 0 };
extern const s32 D_00248DD0[2] = { 1, 1 };
extern const s32 D_00248DD8[6] = { 14, 1, 1, 1, 10, 0 };
extern const s32 D_00248DF0[4] = { 0, 6, 6, 6 };
extern const s32 D_00248E00[4] = { 0x2000, 1, 1, 0x1000 };
extern const s32 D_00248E10[6] = { 0x2000, 0x1000, 1, 1, 0x1000, 0 };
extern const s32 D_00248E28[4] = { 0x1000, 1, 1, 0 };
extern const Kinds2 D_00248E38 = { { 6, 0x1000 } };
extern const s32 D_00248E40[6] = { 6, 6, 1, 1, 1, 1 };
extern const s32 D_00248E58[6] = { 0x1000, 0x2000, 2, 2, 1, 1 };
extern const s32 D_00248E70[4] = { 0x2000, 6, 0x1000, 0 };
extern const s32 D_00248E80[4] = { 5, 5, 2, 0 };
extern const s32 D_00248E90[2] = { 0x1000, 5 };
extern const s32 D_00248E98[4] = { 15, 6, 5, 0 };
extern const Kinds2 D_00248EA8 = { { 0xF, 6 } };
extern const Kinds2 D_00248EB0 = { { 0x1000, 0x2000 } };
extern const s32 D_00248EB8[2] = { 5, 5 };
extern const s32 D_00248EC0[2] = { 5, 0 };
extern const s32 D_00248EC8[4] = { 0x2000, 1, 1, 0 };
extern const s32 D_00248ED8[4] = { 2, 1, 1, 0 };
extern const s32 D_00248EE8[2] = { 0x1000, 6 };
extern const s32 D_00248EF0[4] = { 6, 6, 6, 6 };
extern const s32 D_00248F00[4] = { 1, 1, 1, 0 };
extern const s32 D_00248F10[4] = { 6, 5, 0, 0 };
extern const s32 D_00248F20[2] = { 6, 5 };
extern const s32 D_00248F28[4] = { 1, 1, 1, 1 };
extern const s32 D_00248F38[6] = { 0x2000, 1, 1, 0x2000, 0x2000, 0 };
extern const s32 D_00248F50[2] = { 0x2000, 1 };
extern const s32 D_00248F58[2] = { 6, 1 };
extern const s32 D_00248F60[4] = { 6, 0x1000, 0x1000, 0 };
extern const s32 D_00248F70[4] = { 6, 1, 0, 0 };
extern const s32 D_00248F80[4] = { 6, 0x1000, 0, 0 };
extern const s32 D_00248F90[2] = { 6, 0 };
extern const s32 D_00248F98[2] = { 0x2000, 5 };
extern const s32 D_00248FA0[4] = { 5, 1, 0x1000, 0 };
extern const s32 D_00248FB0[4] = { 5, 1, 6, 0 };
extern const s32 D_00248FC0[2] = { 5, 1 };
extern const s32 D_00248FC8[4] = { 0x2000, 0x2000, 0x2000, 0 };
extern const s32 D_00248FD8[2] = { 0x2000, 0 };

// The file's .data: the property descriptors, filled at startup by func_00109488.
struct Prop_2505D8 { s32 f0; s32 flags; u8 body[24]; };
Prop_2505D8 D_002505D8[1179];

ScriptValue* func_001000C8(ScriptValue* ret, void* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00100178(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00100218(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001002C0(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00100368(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00100438(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001004F0(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001005A0(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00100650(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00100720(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001007F0(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001008B8(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00100998(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00100A78(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00100B48(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00100C28(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00100CC8(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00100D68(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00100E08(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00100EE0(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00100FA8(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00101058(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00101168(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00101208(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001012B8(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00101368(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00101418(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001014C8(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00101568(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00101620(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001016F0(ScriptValue* ret, Collider* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001017A0(ScriptValue* ret, Collider* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00101860(ScriptValue* ret, TransformObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00101950(ScriptValue* ret, TransformObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001019F0(ScriptValue* ret, ObjectSubGroup* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00101A90(ScriptValue* ret, Animation* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00101B80(ScriptValue* ret, Animation* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00101C88(ScriptValue* ret, Animation* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00101D38(ScriptValue* ret, Obj_101D38* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00101E10(ScriptValue* ret, void* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00101EB0(ScriptValue* ret, void* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00101F60(ScriptValue* ret, void* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00102030(ScriptValue* ret, C1F* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001020D0(ScriptValue* ret, MaskedCollider* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00102178(ScriptValue* ret, TriggerZone* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00102268(ScriptValue* ret, ZoneCollider* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00102358(ScriptValue* ret, SwitchedCollider* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001023F8(ScriptValue* ret, SwitchedCollider* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001024B0(ScriptValue* ret, StateTrigger* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00102560(ScriptValue* ret, StateTrigger* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00102650(ScriptValue* ret, TimedObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00102710(ScriptValue* ret, TimedObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001027C0(ScriptValue* ret, TimedGroup* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00102870(ScriptValue* ret, TimedGroup* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00102920(ScriptValue* ret, EffectSpawner* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001029D0(ScriptValue* ret, EffectSpawner* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00102A70(ScriptValue* ret, EffectSpawner* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00102B10(ScriptValue* ret, EffectSpawner* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00102C28(ScriptValue* ret, C79* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00102D40(ScriptValue* ret, C7A* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00102DE0(ScriptValue* ret, C7A* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00102F10(ScriptValue* ret, C78* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00102FB0(ScriptValue* ret, C78* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001030E0(ScriptValue* ret, StateGraph* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001031C0(ScriptValue* ret, void* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00103260(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00103350(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00103420(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001034F0(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00103590(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00103640(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001036F0(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001037A0(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00103850(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00103900(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001039B0(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00103A60(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00103B40(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00103C10(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00103CC0(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00103D70(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00103E10(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00103EB0(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00103F80(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00104020(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001040C0(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00104170(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00104220(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001042F0(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001043A0(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00104470(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00104510(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001045B0(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00104660(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00104710(ScriptValue* ret, Camera* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001047C0(ScriptValue* ret, Camera* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00104860(ScriptValue* ret, Camera* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00104900(ScriptValue* ret, Camera* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001049D8(ScriptValue* ret, Camera* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00104A78(ScriptValue* ret, Camera* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00104B18(ScriptValue* ret, Camera* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00104C00(ScriptValue* ret, LookupObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00104CA0(ScriptValue* ret, LookupObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00104D40(ScriptValue* ret, ContactTracker* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00104DE0(ScriptValue* ret, C2E* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00104E80(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00104F50(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00105020(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001050D0(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001051C0(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00105290(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00105360(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00105430(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00105500(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001055A8(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00105658(ScriptValue* ret, C09* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00105728(ScriptValue* ret, ChildGroupObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001057D8(ScriptValue* ret, ChildGroupObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00105878(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00105960(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00105A00(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00105AB0(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00105B60(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00105C10(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00105CC0(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00105D60(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00105E10(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00105EC0(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00105F70(ScriptValue* ret, C8B* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00106048(ScriptValue* ret, C8B* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00106120(ScriptValue* ret, C23* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001061C0(ScriptValue* ret, C23* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00106270(ScriptValue* ret, C3C* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00106320(ScriptValue* ret, C3C* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001063D0(ScriptValue* ret, C62* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001064C0(ScriptValue* ret, TargetFollower* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00106560(ScriptValue* ret, TargetFollower* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00106600(ScriptValue* ret, ObjectPool* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001066F0(ScriptValue* ret, ObjectPool* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001067A0(ScriptValue* ret, ObjectPool* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00106850(ScriptValue* ret, ObjectPool* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00106920(ScriptValue* ret, ObjectPool* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001069C0(ScriptValue* ret, ObjectPool* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00106A70(ScriptValue* ret, ObjectPool* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00106B10(ScriptValue* ret, ObjectPool* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00106BB0(ScriptValue* ret, ObjectPool* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00106C50(ScriptValue* ret, StepSequence* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00106CF0(ScriptValue* ret, StepSequence* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00106D90(ScriptValue* ret, StepSequence* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00106E60(ScriptValue* ret, StepSequence* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00106F00(ScriptValue* ret, StepSequence* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00106FA0(ScriptValue* ret, C5D* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00107040(ScriptValue* ret, Oscillator* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001070E0(ScriptValue* ret, Oscillator* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00107180(ScriptValue* ret, Oscillator* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00107268(ScriptValue* ret, Oscillator* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00107350(ScriptValue* ret, C0C* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001073F0(ScriptValue* ret, C17* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001074C0(ScriptValue* ret, C19* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00107570(ScriptValue* ret, C19* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00107678(ScriptValue* ret, C19* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00107718(ScriptValue* ret, TransformObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001077D8(ScriptValue* ret, C60* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00107898(ScriptValue* ret, C0E* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00107948(ScriptValue* ret, C24* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00107A10(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00107AB0(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00107B60(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00107C00(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00107CB0(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00107D60(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00107E10(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00107EC0(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00107F70(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00108038(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00108128(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00108208(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001082E8(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001083C8(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00108498(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00108548(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001085E8(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00108688(ScriptValue* ret, C4A* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00108728(ScriptValue* ret, C4A* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001087D8(ScriptValue* ret, C1B* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00108878(ScriptValue* ret, C13* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00108928(ScriptValue* ret, C13* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001089C8(ScriptValue* ret, C13* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00108A98(ScriptValue* ret, C13* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00108B48(ScriptValue* ret, C13* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00108BE8(ScriptValue* ret, Timeline* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00108CC8(ScriptValue* ret, Timeline* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00108DA8(ScriptValue* ret, Timeline* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00108E70(ScriptValue* ret, Timeline* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00108F38(ScriptValue* ret, Timeline* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00109000(ScriptValue* ret, Timeline* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001090C8(ScriptValue* ret, C0D* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001091A8(ScriptValue* ret, C1D* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00109258(ScriptValue* ret, C1D* obj, s32 unused, ScriptValue* args);
ScriptValue* func_00109308(ScriptValue* ret, C1D* obj, s32 unused, ScriptValue* args);
ScriptValue* func_001093B8(ScriptValue* ret, C4C* obj, s32 unused, ScriptValue* args);

ScriptValue* func_001000C8(ScriptValue* ret, void* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 7;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValueBool(&q, IsObjectOfKind(obj, out));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00100178(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddObjectKeyToOwner(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00100218(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    obj->desc->m03(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001002C0(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    obj->desc->m02(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00100368(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)&D_00248D80;
    StoreScriptArgumentsVa(&t, 2, args, &kinds, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValuePointerB(&q, CreateObjectCopy(obj, o1, o2));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00100438(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    BaseObject* out;
    InitScriptValue(&q);
    kinds = 0x2000;
    (void)StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    obj->desc->m15(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001004F0(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x2000;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    s32 flag = IsObjectDescendantOf(obj, out);
    SetScriptValueBool(&q, flag);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001005A0(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x6;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    s32 flag = MatchesObjectId(obj, out);
    SetScriptValueBool(&q, flag);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00100650(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)&D_00248D88;
    StoreScriptArgumentsVa(&t, 2, args, &kinds, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)SetExtraObjectPropertyBool(obj, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00100720(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)&D_00248D90;
    StoreScriptArgumentsVa(&t, 2, args, &kinds, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)SetExtraObjectPropertyInt(obj, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001007F0(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 a;
    f32 b;
    InitScriptValue(&q);
    kinds = *(Kinds2*)&D_00248D98;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &a, &b);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetExtraObjectPropertyFloat(obj, a, b);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001008B8(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    Quad16 vec;
    ScriptValue t;
    s32 out;
    InitScriptValue(&q);
    kinds = *(Kinds2*)&D_00248DA0;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &out, &vec);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetExtraObjectPropertyVectorB(obj, out, &vec);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00100998(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    Quad16 vec;
    ScriptValue t;
    s32 out;
    InitScriptValue(&q);
    kinds = *(Kinds2*)&D_00248DA8;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &out, &vec);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetExtraObjectPropertyPair(obj, out, &vec);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00100A78(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)&D_00248DB0;
    StoreScriptArgumentsVa(&t, 2, args, &kinds, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)SetExtraObjectPropertyWord(obj, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00100B48(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    Quad16 vec;
    ScriptValue t;
    s32 out;
    InitScriptValue(&q);
    kinds = *(Kinds2*)&D_00248DB8;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &out, &vec);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetExtraObjectPropertyVectorA(obj, out, &vec);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00100C28(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ClearObjectRecordValues(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00100CC8(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ClearAimHold(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00100D68(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetAimHold(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00100E08(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds3 kinds;
    ScriptValue t;
    f32 o0;
    f32 o1;
    s32 o2;
    Kinds3* np;
    f32* o0p;
    f32* o1p;
    s32* o2p;
    InitScriptValue(&q);
    np = &kinds;
    o0p = &o0;
    o1p = &o1;
    o2p = &o2;
    kinds = *(Kinds3*)&D_00248DC0;
    (void)StoreScriptArgumentsVa(&t, 3, args, np, o0p, o1p, o2p);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetValueAttachment(obj, o2, o0, o1);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00100EE0(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    f32 x;
    f32 y;
    InitScriptValue(&q);
    kinds = *(Kinds2*)&D_00248DD0;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &x, &y);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetElementsScrollScale(obj, x, y);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00100FA8(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    f32 f0;
    InitScriptValue(&q);
    kinds = 1;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &f0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)SetCrossfadeRatioDeep(obj, f0);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00101058(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds5 kinds;
    Quad16 vec;
    ScriptValue t;
    s32 i0;
    f32 f0, f1, f2;
    InitScriptValue(&q);
    kinds = *(Kinds5*)&D_00248DD8;
    StoreScriptArgumentsVa(&t, 5, args, &kinds, &i0, &f0, &f1, &f2, &vec);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    StartSoundWithParams(obj, i0, &vec, f0, f1, f2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00101168(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    StopPlayingSound(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00101208(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    f32 f0;
    InitScriptValue(&q);
    kinds = 1;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &f0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)func_00126CB8(obj, f0);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001012B8(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    f32 f0;
    InitScriptValue(&q);
    kinds = 1;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &f0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)func_00126D60(obj, f0);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00101368(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x6;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValuePointerB(&q, FindObjectHandle(obj, out));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00101418(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 y;
    InitScriptValue(&q);
    s32* px = &kinds;
    s32* py = &y;
    *px = 6;
    StoreScriptArgumentsVa(&t, 1, args, px, py);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValuePointerB(&q, FindObjectAnimationPlayer(obj, y));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001014C8(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValuePointerB(&q, FindTrackPlayer(obj));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00101568(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    PlacedObject* y;
    InitScriptValue(&q);
    s32* px = &kinds;
    PlacedObject** py = &y;
    *px = 0x2000;
    (void)StoreScriptArgumentsVa(&t, 1, args, px, py);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    obj->desc02()->m1F(obj, y);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00101620(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)&D_00248D80;
    StoreScriptArgumentsVa(&t, 2, args, &kinds, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)SetFollowObjects(obj, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001016F0(ScriptValue* ret, Collider* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 y;
    InitScriptValue(&q);
    s32* px = &kinds;
    s32* py = &y;
    *px = 0x1000;
    (void)StoreScriptArgumentsVa(&t, 1, args, px, py);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    func_001BB1E0(obj, y);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001017A0(ScriptValue* ret, Collider* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Quad4 vec;
    ScriptValue t;
    s32 kinds;
    InitScriptValue(&q);
    kinds = 2;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &vec);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    s32 r = func_001BC670(obj, &vec);
    SetScriptValueBool(&q, r);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00101860(ScriptValue* ret, TransformObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds4 kinds;
    ScriptValue t;
    s32 o0;
    s32 o1;
    s32 o2;
    s32 o3;
    InitScriptValue(&q);
    kinds = *(Kinds4*)D_00248DF0;
    StoreScriptArgumentsVa(&t, 4, args, &kinds, &o0, &o1, &o2, &o3);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    s32 r = func_001F42D0(obj, o0, o1, o2, o3);
    (void)r;
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00101950(ScriptValue* ret, TransformObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    func_001F4008(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001019F0(ScriptValue* ret, ObjectSubGroup* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    func_001F4808(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00101A90(ScriptValue* ret, Animation* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds4 kinds;
    ScriptValue t;
    s32 o0;
    f32 o1;
    f32 o2;
    s32 o3;
    InitScriptValue(&q);
    kinds = *(Kinds4*)&D_00248E00;
    StoreScriptArgumentsVa(&t, 4, args, &kinds, &o0, &o1, &o2, &o3);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    void* r = CreateAnimationPlayerReturned(obj, o0, o1, o2, o3);
    SetScriptValuePointerB(&q, r);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00101B80(ScriptValue* ret, Animation* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds5 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    f32 o3;
    f32 o4;
    s32 o5;
    InitScriptValue(&q);
    kinds = *(Kinds5*)&D_00248E10;
    (void)StoreScriptArgumentsVa(&t, 5, args, &kinds, &o1, &o2, &o3, &o4, &o5);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValuePointerB(&q, FindOrCreateSeekedAnimationPlayer(obj, o1, o3, o4, o2, o5));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00101C88(ScriptValue* ret, Animation* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 v;
    InitScriptValue(&q);
    kinds = 6;
    (void)StoreScriptArgumentsVa(&t, 1, args, &kinds, &v);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    f32 r = func_0012CCC0(obj, v);
    SetScriptValueFloat(&q, r);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00101D38(ScriptValue* ret, Obj_101D38* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds3 kinds;
    ScriptValue t;
    s32 o0;
    f32 o1;
    f32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds3*)&D_00248E28;
    (void)StoreScriptArgumentsVa(&t, 3, args, &kinds, &o0, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SeekAnimationPlayer(obj, o0, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00101E10(ScriptValue* ret, void* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    StopAnimationPlayer(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00101EB0(ScriptValue* ret, void* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 5;
    (void)StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ApplyListedPoseSources(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00101F60(ScriptValue* ret, void* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = D_00248E38;
    StoreScriptArgumentsVa(&t, 2, args, &kinds, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)ReleasePlayerAttachment(obj, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00102030(ScriptValue* ret, C1F* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    func_001EF830(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001020D0(ScriptValue* ret, MaskedCollider* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    obj->desc20()->m48(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00102178(ScriptValue* ret, TriggerZone* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds4 kinds;
    ScriptValue t;
    s32 o0;
    s32 o1;
    s32 o2;
    s32 o3;
    InitScriptValue(&q);
    kinds = *(Kinds4*)D_00248DF0;
    StoreScriptArgumentsVa(&t, 4, args, &kinds, &o0, &o1, &o2, &o3);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    s32 r = SetTriggerZoneEntry(obj, o0, o1, o2, o3);
    (void)r;
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00102268(ScriptValue* ret, ZoneCollider* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds4 kinds;
    ScriptValue t;
    s32 o0;
    s32 o1;
    s32 o2;
    s32 o3;
    InitScriptValue(&q);
    kinds = *(Kinds4*)D_00248DF0;
    StoreScriptArgumentsVa(&t, 4, args, &kinds, &o0, &o1, &o2, &o3);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    s32 r = SetZoneColliderEntry(obj, o0, o1, o2, o3);
    (void)r;
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00102358(ScriptValue* ret, SwitchedCollider* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ActivateSwitchedColliderUnlessActive(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001023F8(ScriptValue* ret, SwitchedCollider* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x1000;
    (void)StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    s32 flag = obj->desc05()->m4B(obj, out);
    SetScriptValueBool(&q, flag);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001024B0(ScriptValue* ret, StateTrigger* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x1000;
    (void)StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetStateTriggerStateFromMessage(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00102560(ScriptValue* ret, StateTrigger* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds4 kinds;
    ScriptValue t;
    s32 o0;
    s32 o1;
    s32 o2;
    s32 o3;
    InitScriptValue(&q);
    kinds = *(Kinds4*)D_00248DF0;
    StoreScriptArgumentsVa(&t, 4, args, &kinds, &o0, &o1, &o2, &o3);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    s32 r = AddStateTriggerTableEntry(obj, o0, o1, o2, o3);
    (void)r;
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00102650(ScriptValue* ret, TimedObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x1000;
    (void)StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    void (*fn)(TimedObject*, s32) = obj->desc30()->m49;
    if (fn != 0) {
        fn(obj, out);
    }
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00102710(ScriptValue* ret, TimedObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    void (*fn)(TimedObject*) = obj->desc30()->m4A;
    if (fn != 0) {
        fn(obj);
    }
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001027C0(ScriptValue* ret, TimedGroup* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    f32 out;
    InitScriptValue(&q);
    kinds = 1;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)SetTimedGroupFadeInTime(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00102870(ScriptValue* ret, TimedGroup* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    f32 out;
    InitScriptValue(&q);
    kinds = 1;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)SetTimedGroupFadeOutTime(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00102920(ScriptValue* ret, EffectSpawner* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    f32 out;
    InitScriptValue(&q);
    kinds = 1;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)SetEffectSpawnerActiveFor(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001029D0(ScriptValue* ret, EffectSpawner* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetEffectSpawnerActiveForever(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00102A70(ScriptValue* ret, EffectSpawner* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetEffectSpawnerInactive(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00102B10(ScriptValue* ret, EffectSpawner* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds6 kinds;
    ScriptValue t;
    s32 i0, i1;
    f32 f0, f1, f2, f3;
    InitScriptValue(&q);
    kinds = *(Kinds6*)&D_00248E40;
    (void)StoreScriptArgumentsVa(&t, 6, args, &kinds, &i0, &i1, &f0, &f1, &f2, &f3);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddSpawnRangeEntry(obj, i0, i1, f0, f1, f2, f3);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00102C28(ScriptValue* ret, C79* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds6 kinds;
    ScriptValue t;
    s32 i0, i1;
    f32 f0, f1, f2, f3;
    InitScriptValue(&q);
    kinds = *(Kinds6*)&D_00248E40;
    (void)StoreScriptArgumentsVa(&t, 6, args, &kinds, &i0, &i1, &f0, &f1, &f2, &f3);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddRecordMemberRangeEntry(obj, i0, i1, f0, f1, f2, f3);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00102D40(ScriptValue* ret, C7A* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SendEmptyMessage(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00102DE0(ScriptValue* ret, C7A* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds6 kinds;
    Quad4 vec0;
    Quad4 vec1;
    ScriptValue t;
    s32 i0;
    s32 i1;
    f32 f0;
    f32 f1;

    InitScriptValue(&q);
    s32* pi0 = &i0;
    s32* pi1 = &i1;
    kinds = *(Kinds6*)&D_00248E58;
    (void)StoreScriptArgumentsVa(&t, 6, args, &kinds, pi0, pi1, &vec0, &vec1, &f0, &f1);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SendTwoVectorMessage(obj, i0, i1, &vec0, &vec1, f0, f1);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00102F10(ScriptValue* ret, C78* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SendEmptyMessage(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00102FB0(ScriptValue* ret, C78* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds6 kinds;
    Quad4 vec0;
    Quad4 vec1;
    ScriptValue t;
    s32 i0;
    s32 i1;
    f32 f0;
    f32 f1;

    InitScriptValue(&q);
    kinds = *(Kinds6*)&D_00248E58;
    (void)StoreScriptArgumentsVa(&t, 6, args, &kinds, &i0, &i1, &vec0, &vec1, &f0, &f1);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SendTwoVectorMessage(obj, i0, i1, &vec0, &vec1, f0, f1);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001030E0(ScriptValue* ret, StateGraph* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds3 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    s32 o3;
    InitScriptValue(&q);
    kinds = *(Kinds3*)&D_00248E70;
    (void)StoreScriptArgumentsVa(&t, 3, args, &kinds, &o1, &o2, &o3);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    void* v = CreateStateWalker(obj, o1, o2, o3);
    SetScriptValuePointerB(&q, v);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001031C0(ScriptValue* ret, void* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    DestroyStateWalker(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00103260(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds3 kinds;
    Quad4 vec;
    ScriptValue t;
    s32 a;
    s32 b;
    InitScriptValue(&q);
    kinds = *(Kinds3*)&D_00248E80;
    (void)StoreScriptArgumentsVa(&t, 3, args, &kinds, &a, &b, &vec);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ScatterRandomObjects(obj, a, b, &vec);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00103350(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)&D_00248E90;
    StoreScriptArgumentsVa(&t, 2, args, &kinds, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)SetIopChannel2Setting(obj, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00103420(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)&D_00248E90;
    StoreScriptArgumentsVa(&t, 2, args, &kinds, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)PushIopChannel2Setting(obj, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001034F0(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    PopIopChannel2Setting(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00103590(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0xF;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValueBool(&q, func_001DD690(obj, out));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00103640(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0xF;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValueBool(&q, func_001DD6B0(obj, out));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001036F0(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0xF;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValueBool(&q, func_001DD6D0(obj, out));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001037A0(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0xF;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValueBool(&q, func_001DD6F0(obj, out));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00103850(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0xF;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValueBool(&q, func_001DD710(obj, out));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00103900(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0xF;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValueBool(&q, CheckEntryTwoBitRequirement(obj, out));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001039B0(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0xF;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValueBool(&q, CheckEntryThreeBitRequirement(obj, out));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00103A60(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds3 kinds;
    ScriptValue t;
    void* o1;
    s32 o2;
    s32 o3;
    InitScriptValue(&q);
    kinds = *(Kinds3*)&D_00248E98;
    (void)StoreScriptArgumentsVa(&t, 3, args, &kinds, &o1, &o2, &o3);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetEntrySlotValue(obj, o1, o2, o3);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00103B40(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 out1;
    s32 out2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)&D_00248EA8;
    StoreScriptArgumentsVa(&t, 2, args, &kinds, &out1, &out2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    s32 r = GetEntrySlotValue(obj, out1, out2);
    SetScriptValueInt(&q, r);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00103C10(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x1000;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValueBool(&q, func_001DD8E8(obj, out));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00103CC0(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x1000;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValueBool(&q, func_001DD908(obj, out));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00103D70(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValueInt(&q, RecomputeSaveCompletion(obj));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00103E10(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    PopActiveSequenceElement(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00103EB0(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 out1;
    s32 out2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)&D_00248EB0;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &out1, &out2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ShowPauseMenuPageWith(obj, out1, out2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00103F80(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ShowCountedScreenElement(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00104020(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    HideCountedScreenElement(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001040C0(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 5;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    s32 v = PushSoundLevelBuiltin(obj, out);
    SetScriptValueInt(&q, v);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00104170(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x5;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)RemoveSoundLevelBuiltin(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00104220(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 out1;
    s32 out2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)D_00248EB8;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &out1, &out2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetCachedVoiceParamBuiltin(obj, out1, out2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001042F0(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 5;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    s32 v = GetCachedVoiceParamBuiltin(obj, out);
    SetScriptValueInt(&q, v);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001043A0(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 out1;
    s32 out2;
    Kinds2* pp;
    s32* o1;
    s32* o2;
    InitScriptValue(&q);
    pp = &kinds;
    o1 = &out1;
    o2 = &out2;
    kinds = *(Kinds2*)D_00248EC0;
    (void)StoreScriptArgumentsVa(&t, 2, args, pp, o1, o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    RefreshCachedVoiceParamBuiltin(obj, out1, out2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00104470(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AcquirePadSelectFlag(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00104510(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ReleasePadSelectFlag(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001045B0(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x1000;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ClearWorldFlagBit(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00104660(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x1000;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetWorldFlagBit(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00104710(ScriptValue* ret, Camera* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x1000;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    PushCameraStackValue(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001047C0(ScriptValue* ret, Camera* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValueInt(&q, PopCameraStackValue(obj));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00104860(ScriptValue* ret, Camera* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    s32 v = PeekCameraStackValue(obj);
    SetScriptValueInt(&q, v);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00104900(ScriptValue* ret, Camera* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds3 kinds;
    ScriptValue t;
    s32 o0;
    f32 o1;
    f32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds3*)D_00248EC8;
    StoreScriptArgumentsVa(&t, 3, args, &kinds, &o0, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    func_00146018(obj, o0, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001049D8(ScriptValue* ret, Camera* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    func_00146028(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00104A78(ScriptValue* ret, Camera* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    func_001455F0(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00104B18(ScriptValue* ret, Camera* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds3 kinds;
    Quad4 vec;
    ScriptValue t;
    f32 fx;
    f32 fy;
    InitScriptValue(&q);
    kinds = *(Kinds3*)D_00248ED8;
    StoreScriptArgumentsVa(&t, 3, args, &kinds, &vec, &fx, &fy);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValueBool(&q, func_00146038(obj, &vec, fx, fy));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00104C00(ScriptValue* ret, LookupObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    PushObjectCameraController(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00104CA0(ScriptValue* ret, LookupObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    RemoveObjectCameraController(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00104D40(ScriptValue* ret, ContactTracker* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ClearTrackedNodes(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00104DE0(ScriptValue* ret, C2E* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    func_00199AF0(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00104E80(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 out1;
    s32 out2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)D_00248EE8;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &out1, &out2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetAgentStateClipId(obj, out1, out2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00104F50(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 out1;
    s32 out2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)D_00248EE8;
    StoreScriptArgumentsVa(&t, 2, args, &kinds, &out1, &out2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetAgentStateClip(obj, out1, out2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00105020(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x1000;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValuePointerB(&q, GetAgentStateClip(obj, out));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001050D0(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds4 kinds;
    ScriptValue t;
    s32 o0;
    s32 o1;
    s32 o2;
    s32 o3;
    InitScriptValue(&q);
    kinds = *(Kinds4*)D_00248EF0;
    StoreScriptArgumentsVa(&t, 4, args, &kinds, &o0, &o1, &o2, &o3);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    s32 r = AddAgentClipGroup(obj, o0, o1, o2, o3);
    (void)r;
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001051C0(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 out1;
    s32 out2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)&D_00248E38;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &out1, &out2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddAgentMeshKey(obj, out1, out2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00105290(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 out1;
    s32 out2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)D_00248EE8;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &out1, &out2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddAgentExtraClip(obj, out1, out2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00105360(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = D_00248EB0;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    func_001C8FD0(obj, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00105430(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    Kinds2* kp;
    s32* o1p;
    s32* o2p;
    InitScriptValue(&q);
    kp = &kinds;
    o1p = &o1;
    o2p = &o2;
    kinds = *(Kinds2*)D_00248EE8;
    (void)StoreScriptArgumentsVa(&t, 2, args, kp, o1p, o2p);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetAgentSecondaryClipId(obj, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00105500(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ((void (*)(void*))obj->desc08()->m61)(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001055A8(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x2000;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetAgentMainClip(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00105658(ScriptValue* ret, C09* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)D_00248EE8;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    func_001B70B0(obj, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00105728(ScriptValue* ret, ChildGroupObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    f32 out;
    InitScriptValue(&q);
    kinds = 1;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)StartChildGroupDelay(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001057D8(ScriptValue* ret, ChildGroupObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    func_0013BF68(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00105878(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds3 kinds;
    Quad4 vec;
    ScriptValue t;
    f32 fx;
    f32 fy;
    Kinds3* kp;
    Quad4* vecp;
    f32* fxp;
    f32* fyp;
    InitScriptValue(&q);
    kp = &kinds;
    vecp = &vec;
    fxp = &fx;
    fyp = &fy;
    kinds = *(Kinds3*)D_00248ED8;
    (void)StoreScriptArgumentsVa(&t, 3, args, kp, vecp, fxp, fyp);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    PlacePlayerOnGround(obj, &vec, fx, fy);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00105960(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ReleasePlayerToState2(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00105A00(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    func_001777F8(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00105AB0(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x2000;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    func_001D2830(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00105B60(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    func_00177800(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00105C10(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SeekObjects105Animations(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00105CC0(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    func_001D6CB0(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00105D60(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x2000;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)func_001781E0(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00105E10(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x2000;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)func_00178258(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00105EC0(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x2000;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    func_00178280(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00105F70(ScriptValue* ret, C8B* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds3 kinds;
    ScriptValue t;
    f32 o0;
    f32 o1;
    f32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds3*)D_00248F00;
    (void)StoreScriptArgumentsVa(&t, 3, args, &kinds, &o0, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    func_0019CE28(obj, o0, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00106048(ScriptValue* ret, C8B* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds3 kinds;
    ScriptValue t;
    f32 o0;
    f32 o1;
    f32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds3*)D_00248F00;
    (void)StoreScriptArgumentsVa(&t, 3, args, &kinds, &o0, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    func_0019CE38(obj, o0, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00106120(ScriptValue* ret, C23* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ResetCollectedItems(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001061C0(ScriptValue* ret, C23* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x2000;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    RecordCollectedItem(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00106270(ScriptValue* ret, C3C* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 6;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddContactListId(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00106320(ScriptValue* ret, C3C* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 7;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddContactListKind(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001063D0(ScriptValue* ret, C62* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds4 kinds;
    ScriptValue t;
    s32 o0;
    s32 o1;
    s32 o2;
    s32 o3;
    InitScriptValue(&q);
    kinds = *(Kinds4*)D_00248DF0;
    StoreScriptArgumentsVa(&t, 4, args, &kinds, &o0, &o1, &o2, &o3);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    s32 r = func_001EF8C0(obj, o0, o1, o2, o3);
    (void)r;
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001064C0(ScriptValue* ret, TargetFollower* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetCurrentTargetFollower(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00106560(ScriptValue* ret, TargetFollower* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ClearCurrentTargetFollower(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00106600(ScriptValue* ret, ObjectPool* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds4 kinds;
    ScriptValue t;
    s32 o0;
    s32 o1;
    s32 o2;
    s32 o3;
    InitScriptValue(&q);
    kinds = *(Kinds4*)D_00248F10;
    StoreScriptArgumentsVa(&t, 4, args, &kinds, &o0, &o1, &o2, &o3);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    s32 r = AddObjectPoolEntry(obj, o0, o1, o2, o3);
    (void)r;
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001066F0(ScriptValue* ret, ObjectPool* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 6;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    EnableObjectPoolEntry(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001067A0(ScriptValue* ret, ObjectPool* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 6;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    DisableObjectPoolEntry(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00106850(ScriptValue* ret, ObjectPool* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)D_00248F20;
    StoreScriptArgumentsVa(&t, 2, args, &kinds, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetObjectPoolEntryCount(obj, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00106920(ScriptValue* ret, ObjectPool* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ChooseObjectPoolItem(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001069C0(ScriptValue* ret, ObjectPool* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    s32 flag = func_001A8C90(obj, out);
    SetScriptValueBool(&q, flag);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00106A70(ScriptValue* ret, ObjectPool* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    func_001A93E8(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00106B10(ScriptValue* ret, ObjectPool* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    func_001A9438(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00106BB0(ScriptValue* ret, ObjectPool* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    func_001A9498(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00106C50(ScriptValue* ret, StepSequence* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetStepSequenceModeOne(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00106CF0(ScriptValue* ret, StepSequence* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetStepSequenceCameraMode(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00106D90(ScriptValue* ret, StepSequence* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = D_00248EA8;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddSequenceExtraTarget(obj, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00106E60(ScriptValue* ret, StepSequence* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ChooseStepSequenceState(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00106F00(ScriptValue* ret, StepSequence* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ResetStepSequence(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00106FA0(ScriptValue* ret, C5D* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    func_001993C0(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00107040(ScriptValue* ret, Oscillator* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddOscillatorXEntry(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001070E0(ScriptValue* ret, Oscillator* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddOscillatorYZEntry(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00107180(ScriptValue* ret, Oscillator* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds4 kinds;
    ScriptValue t;
    f32 x;
    f32 y;
    f32 z;
    f32 w;
    InitScriptValue(&q);
    kinds = *(Kinds4*)D_00248F28;
    (void)StoreScriptArgumentsVa(&t, 4, args, &kinds, &x, &y, &z, &w);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    func_001F3928(obj, x, y, z, w);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00107268(ScriptValue* ret, Oscillator* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds4 kinds;
    ScriptValue t;
    f32 x;
    f32 y;
    f32 z;
    f32 w;
    InitScriptValue(&q);
    kinds = *(Kinds4*)D_00248F28;
    StoreScriptArgumentsVa(&t, 4, args, &kinds, &x, &y, &z, &w);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    func_001F3990(obj, x, y, z, w);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00107350(ScriptValue* ret, C0C* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AdvanceGaugeAgentPhase(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001073F0(ScriptValue* ret, C17* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)D_00248EE8;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddEntryRecordKey(obj, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001074C0(ScriptValue* ret, C19* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x2000;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddPathFollowerEntry(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00107570(ScriptValue* ret, C19* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds5 kinds;
    ScriptValue t;
    s32 o1;
    f32 o2;
    f32 o3;
    s32 o4;
    s32 o5;
    InitScriptValue(&q);
    kinds = *(Kinds5*)D_00248F38;
    (void)StoreScriptArgumentsVa(&t, 5, args, &kinds, &o1, &o2, &o3, &o4, &o5);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddPathFollowerActiveEntry(obj, o1, o2, o3, o4, o5);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00107678(ScriptValue* ret, C19* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ResetPathFollower(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00107718(ScriptValue* ret, TransformObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Quad4 vec;
    ScriptValue t;
    s32 kinds;
    InitScriptValue(&q);
    kinds = 2;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &vec);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValueBool(&q, func_00141170(obj, &vec));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001077D8(ScriptValue* ret, C60* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Quad4 vec;
    ScriptValue t;
    s32 kinds;
    InitScriptValue(&q);
    kinds = 2;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &vec);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValueBool(&q, func_0015AA50(obj, &vec));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00107898(ScriptValue* ret, C0E* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x2000;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValueBool(&q, AddSeekingAgentObject(obj, out));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00107948(ScriptValue* ret, C24* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 a;
    f32 b;
    InitScriptValue(&q);
    kinds = *(Kinds2*)D_00248F50;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &a, &b);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    func_00182948(obj, a, b);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00107A10(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q, t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ResetEntryQueue(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00107AB0(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x2000;
    (void)StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    BindEntryQueueToObject(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00107B60(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q, t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    UnbindEntryQueue(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00107C00(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x6;
    (void)StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddQueueEntryKind0(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00107CB0(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x6;
    (void)StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddQueueEntryKind1(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00107D60(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x6;
    (void)StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddQueueEntryKind10(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00107E10(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 6;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)AddQueueEntryKind2(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00107EC0(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 6;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)AddQueueEntryKind3(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00107F70(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 a;
    f32 b;
    InitScriptValue(&q);
    kinds = *(Kinds2*)D_00248F58;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &a, &b);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddQueueEntryKind4(obj, a, b);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00108038(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds4 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    s32 o3;
    s32 o4;
    InitScriptValue(&q);
    kinds = *(Kinds4*)D_00248F60;
    (void)StoreScriptArgumentsVa(&t, 4, args, &kinds, &o1, &o2, &o3, &o4);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddQueueEntryKind5(obj, o1, o2, o3, o4);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00108128(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds3 kinds;
    ScriptValue t;
    s32 o1;
    f32 o2;
    s32 o3;
    InitScriptValue(&q);
    kinds = *(Kinds3*)D_00248F70;
    (void)StoreScriptArgumentsVa(&t, 3, args, &kinds, &o1, &o2, &o3);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddQueueEntryKind6(obj, o1, o3, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00108208(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds3 kinds;
    ScriptValue t;
    s32 o1;
    f32 o2;
    s32 o3;
    InitScriptValue(&q);
    kinds = *(Kinds3*)D_00248F70;
    (void)StoreScriptArgumentsVa(&t, 3, args, &kinds, &o1, &o2, &o3);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddQueueEntryKind7(obj, o1, o3, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001082E8(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds3 kinds;
    ScriptValue t;
    s32 o0;
    s32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds3*)D_00248F80;
    StoreScriptArgumentsVa(&t, 3, args, &kinds, &o0, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddQueueEntryKind8(obj, o0, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001083C8(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)D_00248F90;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddQueueEntryKind9(obj, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00108498(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    f32 out;
    InitScriptValue(&q);
    kinds = 1;
    (void)StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddQueueEntryKind11(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00108548(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddQueueEntryKind12(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001085E8(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    StartColorFade(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00108688(ScriptValue* ret, C4A* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    PlayGaugeModeObjectTarget(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00108728(ScriptValue* ret, C4A* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 6;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)SetGaugeModeObjectTarget(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001087D8(ScriptValue* ret, C1B* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    PlaceModeColliderAtAnchor(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00108878(ScriptValue* ret, C13* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x2000;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)func_001ED018(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00108928(ScriptValue* ret, C13* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    EndHeldTimeline(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001089C8(ScriptValue* ret, C13* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)D_00248F98;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddTempoAgentEntry(obj, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00108A98(ScriptValue* ret, C13* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x2000;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)func_001ED0D8(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00108B48(ScriptValue* ret, C13* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    func_001EC528(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00108BE8(ScriptValue* ret, Timeline* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds3 kinds;
    ScriptValue t;
    s32 o0;
    f32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds3*)D_00248FA0;
    (void)StoreScriptArgumentsVa(&t, 3, args, &kinds, &o0, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AppendTimelineKind0Entry(obj, o0, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00108CC8(ScriptValue* ret, Timeline* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds3 kinds;
    ScriptValue t;
    s32 o0;
    f32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds3*)D_00248FB0;
    (void)StoreScriptArgumentsVa(&t, 3, args, &kinds, &o0, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AppendTimelineKind1Entry(obj, o0, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00108DA8(ScriptValue* ret, Timeline* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 n;
    f32 out;
    InitScriptValue(&q);
    kinds = *(Kinds2*)D_00248FC0;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &n, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AppendTimelineKind2Entry(obj, n, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00108E70(ScriptValue* ret, Timeline* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 n;
    f32 out;
    InitScriptValue(&q);
    kinds = *(Kinds2*)D_00248FC0;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &n, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AppendTimelineKind3Entry(obj, n, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00108F38(ScriptValue* ret, Timeline* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 n;
    f32 out;
    InitScriptValue(&q);
    kinds = *(Kinds2*)D_00248FC0;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &n, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AppendTimelineKind4Entry(obj, n, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00109000(ScriptValue* ret, Timeline* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 n;
    f32 out;
    InitScriptValue(&q);
    kinds = *(Kinds2*)D_00248FC0;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &n, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AppendTimelineKind5Entry(obj, n, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001090C8(ScriptValue* ret, C0D* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds3 kinds;
    ScriptValue t;
    s32 o0;
    s32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds3*)D_00248FC8;
    (void)StoreScriptArgumentsVa(&t, 3, args, &kinds, &o0, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetGaugeBarAgentValues(obj, o0, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001091A8(ScriptValue* ret, C1D* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x2000;
    (void)StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)func_001C3F68(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00109258(ScriptValue* ret, C1D* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x2000;
    (void)StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)func_001C4180(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_00109308(ScriptValue* ret, C1D* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x2000;
    (void)StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)func_001C41A0(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* func_001093B8(ScriptValue* ret, C4C* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 o0;
    s32 o1;
    InitScriptValue(&q);
    (void)StoreScriptArgumentsVa(&t, 2, args, (kinds = *(Kinds2*)D_00248FD8, &kinds), &o0, &o1);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    TakeCountedColliderTouch(obj, o0, o1);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

INCLUDE_ASM(func_00109488);
