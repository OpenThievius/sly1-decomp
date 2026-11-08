// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the walkers all get the first target only when the level record holds no more than the
// host has and a flag only PAL has is clear (D_eu_0027F3A4); US tests the first alone.
extern s32 D_eu_0027F3A4;
void HandlePlayerNotification(Player* self, s32 kind, PlayerNotification* msg)
{
    HandleSwitchedColliderNotification(self, kind, msg);
    switch (kind) {
    case 5:
        if ((void*)msg == PS(void*, 0x2244)) {
            self->f2254 |= 2;
            if (self->f223C == 10) {
                self->f2260 = 2;
            } else {
                self->f2260 = -1;
            }
        } else if ((void*)msg == self->watched2230) {
            switch (self->f2220) {
            case 7:
                if (self->f2228 == 0x1B || self->f2228 == 0x17) {
                    self->f2258 = 7;
                    self->f225C = 0x18;
                    self->f2254 |= 1;
                }
                break;
            case 2:
                if (self->f2228 != 7) {
                    if (self->f2228 != 8) {
                        break;
                    }
                }
                self->f2258 = 2;
                self->f225C = 2;
                self->f2254 |= 1;
                break;
            case 0xC:
                if (self->f2228 == 0x21) {
                    self->f2258 = 0xC;
                    self->f225C = 0x22;
                    self->f2254 |= 1;
                    break;
                }
                if (self->f2228 != 0x23) {
                    break;
                }
            case 9:
            case 0xA:
            case 0xE:
            case 0xF:
            case 0x10:
                self->f225C = -1;
                self->f2258 = 0;
                self->f2254 |= 1;
                break;
            case 4:
                self->f2254 |= 0x10;
                break;
            }
        }
        break;
    case 7:
        if ((void*)msg == self->watched2230) {
            switch (self->f2220) {
            case 5:
            case 6:
                self->fA14 = -1;
                break;
            }
        }
        break;
    case 0x13: {
        PlayerNoticePlayer* src = (PlayerNoticePlayer*)msg->source;
        if (src != (void*)self->watched2230 && src != PS(void*, 0x2244)) {
            void* other = self->f2234;
            if (other == 0 || src != *(void**)((u8*)other + 0x24)) {
                break;
            }
        }
        switch (msg->code) {
        case 0x138: {
            Vec02 v;
            Track83* track = src->anim->f9C;
            if (track == 0) {
                break;
            }
            PositionCurve* c = track->pos;
            c->vt->eval(c, self, 0, src->time, src->speed, 0, &v);
            Vu0::Q(v) = Vu0::Rotate(self->m660, Vu0::Q(v));
            self->desc02()->m20(self, &v);
            if (src == (void*)self->watched2230) {
                Vec02 w;
                u128 s = Vu0::FromFloat(-1.0f);
                Vu0::Q(self->v640) = Vu0::MulX(Vu0::Q(v), s);
                Vu0::Q(w) = s;
            }
            break;
        }
        case 0x13C:
            if (self->f2228 == 8) {
                self->f242C = (f32)D_002637D4;
            } else {
                self->f242C = (f32)D_002637D0;
            }
            break;
        case 0x13D:
            self->f242C = 0;
            break;
        case 0x13A:
            self->f554 = 1;
            break;
        case 0x13B:
            Vu0::Q(self->v2530) = Vu0::Sub(Vu0::Q(self->v560), Vu0::Q(self->pos));
            self->f554 = 0;
            self->v2530.z = 0.0f;
            break;
        case 0x13E: {
            f32 left = GetAnimationMarkerTime(((PlayerNoticePlayer*)self->watched2230)->anim, 0x140) - msg->time;
            self->f5D0 = 0;
            s32 most = g_currentLevelRecord->f438;
            s32 count = ((WalkerHost*)self->f26D4)->count;
            s32 n = MinOfCounts(count, most);
            for (s32 i = 0; i < n; i++) {
                WalkerHost* h = ((WalkerHost*)self->f26D4)->list[i];
                PlayerNoticeEffect* fx = CreateEffect(0x1A, 0);
                self->f5AC[self->f5D0++] = fx;
                if (fx != 0) {
                    f32 nearest = 300.0f;
                    fx->vt->m00(fx, (u8*)self->f59C + 0x140, D_002637CC, 0);
                    AddEffectListener(fx, self);
                    PlacedObject* to = (PlacedObject*)h->f2D8;
                    f32 d = Vu0::ToFloatMoved(Vu0::Length(Vu0::Sub(Vu0::Q(to->v140), Vu0::Q(((PlacedObject*)self->f59C)->v140))));
                    fx->p20 = to;
                    d = nearest >? d;
                    fx->life = left <? (d * 0.00055555557f);
                    fx->vC0 = g_currentWorld->gravity;
                    fx->p134 = (void*)self->f59C;
                }
            }
            break;
        }
        case 0x140: {
            s32 i;
            s32 all = !(g_currentLevelRecord->f438 < ((WalkerHost*)self->f26D4)->count) && D_eu_0027F3A4 == 0;
            for (i = 0; i < ((WalkerHost*)self->f26D4)->count; i++) {
                WalkerHost* h = ((WalkerHost*)self->f26D4)->list[i];
                if (i < g_currentLevelRecord->f438) {
                    if (all) {
                        SetStateWalkerTarget(h->f2D4, 0x22F);
                    } else {
                        SetStateWalkerTarget(h->f2D4, 0x230);
                    }
                } else {
                    SetStateWalkerTarget(h->f2D4, 0x231);
                }
            }
            if (all) {
                SetStateWalkerTarget(((WalkerHost*)self->f26D4)->f2D8, 0x22F);
                g_currentLevelRecord->f448 |= ((WalkerHost*)self->f26D4)->f2D0;
            } else {
                SetStateWalkerTarget(((WalkerHost*)self->f26D4)->f2D8, 0x230);
            }
            f32* e = FindAnimationMarkerEvent(((PlayerNoticePlayer*)self->watched2230)->anim, 0x13F);
            if (e == 0) {
                break;
            }
            f32 left = e[0] - ((PlayerNoticePlayer*)self->watched2230)->time;
            self->f5D0 = 0;
            s32 most = g_currentLevelRecord->f438;
            s32 count = ((WalkerHost*)self->f26D4)->count;
            s32 n = MinOfCounts(count, most);
            for (i = 0; i < n; i++) {
                WalkerHost* h = ((WalkerHost*)self->f26D4)->list[i];
                PlayerNoticeEffect* fx = CreateEffect(0x1A, 0);
                self->f5AC[self->f5D0++] = fx;
                if (fx != 0) {
                    f32 nearest = 300.0f;
                    fx->vt->m00(fx, (u8*)h->f2D8 + 0x140, 1.0f / D_002637CC, 0);
                    AddEffectListener(fx, self);
                    f32 d = Vu0::ToFloatMoved(Vu0::Length(Vu0::Sub(Vu0::Q(((PlacedObject*)h->f2D8)->v140), Vu0::Q(((PlacedObject*)self->f59C)->v140))));
                    fx->p20 = (void*)self->f59C;
                    d = nearest >? d;
                    f32 life = left <? (d * 0.0016666667f);
                    fx->life = life;
                    fx->vC0 = g_currentWorld->gravity;
                    fx->p134 = h->f2D8;
                    fx->start = g_gameClock[1] + (left - life);
                }
            }
            break;
        }
        case 0x15E:
            PS(s32, 0x2738) = 1;
            break;
        case 0x15F:
            PS(s32, 0x2738) = 0;
            break;
        case 0x144:
            self->f2254 |= 0x10;
            break;
        case 0x143:
            self->f2248 = 1;
            break;
        }
        break;
    }
    case 0xA:
        if (msg->obj == self) {
            self->f2438 = (Collider*)msg->source;
            for (u32 k = 0; k < 8; k++) {
                self->f26D8[k].time = 0;
            }
        }
        break;
    case 0xB:
        if (msg->obj == self && msg->source == self->f2438) {
            self->f2438 = 0;
        }
        break;
    case 2: {
        void* held;
        switch (self->f2220) {
        case 3:
            held = (void*)self->f2204;
            goto check;
        case 7:
            held = (void*)self->f2208;
            goto check;
        case 6:
            if (self->f239C == 4) {
                goto pushed;
            }
            if (self->f239C != 5) {
                break;
            }
            held = PS(void*, 0x23B8);
        check:
            if (held == (void*)msg) {
                ReleasePlayerToState2(self);
            }
            break;
        pushed:
            if (self->f23BC == (void*)msg) {
                ReleasePlayerToState2(self);
            }
            break;
        }
        break;
    }
    }
}
