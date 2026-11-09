// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: after a failed code checksum the choice is given up when RandomIntInRange(0, 100) is
// over 20, where US waits for the game clock to pass a random time (RandomFloatInRange).
s32 RandomIntInRange(s32 lo, s32 hi);

s32 ChoosePlayerTargetByCost(Chooser* self, TargetCand* keep)
{
    Vec02 cur0;
    Vec02 best0;
    Vec02 cur1;
    Vec02 best1;
    Vec02 from;
    Vec02 at;
    f32 t;
    f32 cost;
    f32 tPath;
    f32 tPathBest;
    f32 tVector;
    f32 tVectorBest;
    f32 tPoint;
    f32 tCurve;
    f32 tCurveBest;
    s32 kind = -1;
    TargetCand* bestObject;
    TargetCand* bestPath;
    TargetCand* bestPoint;
    TargetCand* bestCurve;
    TargetCand* bestClass75;
    TargetCand* bestVector;
    f32 bestCost;
    f32 bestT;
    f32 bestPathT;
    f32 bestPointT;
    f32 bestCurveT;
    f32 bestVectorT;
    TargetCand* o;

    if (keep != 0) {
        bestCost = -3.40282347e+38f;
    } else {
        bestCost = 3.40282347e+38f;
    }
    bestT = 0.0f;
    func_0017FC48(self, &from);
    for (o = self->world->objects; o != 0; o = o->next50) {
        ConvertPositionToWorld(o, &at);
        if (o != keep && o->f58 < self->pos.z - at.z) {
            continue;
        }
        ScorePlayerTargetPlacement(self, &from, o->frame, &at, 0, &t, &cost, &cur0, &cur1);
        cur1.z = from.z + t * self->f358;
        if (o != keep) {
            if (cost >= D_00274E20) {
                continue;
            }
            cost = AddRepeatTargetPenalty(self, o, cost, D_00274E24);
            if (bestCost <= cost) {
                continue;
            }
            if (AddTargetObstructionCost(t, self, 0, 0, self->f6D4, &from, &cur0, &cur1, 0)) {
                continue;
            }
        }
        best0 = cur0;
        best1 = cur1;
        bestObject = o;
        kind = 3;
        bestCost = bestCost <? cost;
        bestT = t;
    }
    for (TargetCand* path = self->world->paths; path != 0; path = path->next38) {
        Vec02 at2;
        CostContext ctx;
        Vec02 q;
        TransformPointBetweenFrames(0, path->frame, self->f6D4, &at);
        if (path->shape->desc->m10) {
            path->shape->desc->m10(path->shape, &at, 0, &at2, 0, &tPath, 0);
        }
        TransformPointBetweenFrames(path->frame, 0, &at2, &at2);
        if (path != keep && path->f4C < self->pos.z - at2.z) {
            continue;
        }
        ctx.self = self;
        ctx.target = path;
        ctx.v = from;
        CostContext* c = &ctx;
        f32 start = tPath;
        f32 step = GetPathCurveSearchStep(path->shape);
        f32 lo = path->shape->desc->m6(path->shape, D_00274E04);
        FindLocalMinimum((void*)ScoreTargetObjectAt, c, start, step, lo,
                         path->shape->desc->m6(path->shape, path->shape->desc->m8(path->shape) - D_00274E04),
                         &tPathBest, &cost);
        if (path != keep) {
            if (cost >= D_00274E20) {
                continue;
            }
            cost = AddRepeatTargetPenalty(self, path, cost, D_00274E28);
            if (bestCost <= cost) {
                continue;
            }
        }
        PlaceOnTargetObject(self, path, &at2, &q, tPathBest);
        ScorePlayerTargetPlacement(self, &from, path->frame, &at2, &q, &t, 0, &cur0, &cur1);
        cur1.z = from.z + t * self->f358;
        if (path != keep && AddTargetObstructionCost(t, self, 0, 0, self->f6D4, &from, &cur0, &cur1, 0)) {
            continue;
        }
        best0 = cur0;
        best1 = cur1;
        bestPath = path;
        kind = 4;
        bestCost = bestCost <? cost;
        bestT = t;
        bestPathT = tPathBest;
    }
    for (o = (TargetCand*)g_class75List.head; o != 0; o = o->next80) {
        if (o != keep) {
            if (keep != 0) {
                continue;
            }
            if (o == self->f2210) {
                continue;
            }
            if ((o->flags88 & 1) == 0) {
                continue;
            }
            if (!IsObjectOfKind(o, 0x76)) {
                continue;
            }
        }
        GetObjectWorldPosition(o, &at);
        if (o != keep) {
            if (o->fB4 < self->pos.z - at.z) {
                continue;
            }
            s32 far = D_00274E0C * D_00274E0C < DistanceSquared(at, self->v140);
            if (far) {
                continue;
            }
        }
        PathArgs args;
        Vec02 p;
        args.self = self;
        args.frame = o->frame;
        args.c = o->v40;
        FindLocalMinimum((void*)ScoreTargetPathAt, &args, 0.5f, 0.25f, 0.25f, 3.0f, &t, &cost);
        func_001CEB18(self, args.frame, &args.c, 0, &cur0, &cur1, t);
        if (o != keep) {
            if (cost >= D_00274E20) {
                continue;
            }
            cost = AddRepeatTargetPenalty(self, o, cost, D_00274E2C);
            if (bestCost <= cost) {
                continue;
            }
            TransformPointBetweenFrames(args.frame, 0, &args.c, &p);
            if (AddTargetObstructionCost(t, self, 0, 0, &self->v140, &self->v150, &cur0, &cur1, &p)) {
                continue;
            }
        }
        best0 = cur0;
        best1 = cur1;
        best0.z -= 75.0f;
        bestClass75 = o;
        kind = 6;
        bestCost = cost <? bestCost;
        bestT = t;
    }
    for (o = (TargetCand*)g_targetVectors.list.head; o != 0; o = o->next38) {
        Vec02 at2;
        NearestContext near;
        PathArgs args;
        Vec02 p;
        TransformPointBetweenFrames(0, o->frame, &self->v140, &at);
        if (o->shape->desc->m10) {
            o->shape->desc->m10(o->shape, &at, 0, &at2, 0, 0, &tVector);
        }
        TransformPointBetweenFrames(o->frame, 0, &at2, &at2);
        if (o != keep) {
            if (o->f5C < self->pos.z - at2.z) {
                continue;
            }
            s32 far = D_00274E0C < Distance(at2, self->v140);
            if (far) {
                continue;
            }
        }
        NearestContext* n = &near;
        near.self = self;
        near.target = o;
        f32 start = tVector;
        FindLocalMinimum((void*)ScoreTargetPathNearest, n, start, 100.0f, 50.0f, o->shape->desc->m8(o->shape) - 50.0f,
                         &tVectorBest, &cost);
        if (o != keep) {
            if (cost >= D_00274E20) {
                continue;
            }
            cost = AddRepeatTargetPenalty(self, o, cost, D_00274E30);
            if (bestCost <= cost) {
                continue;
            }
        }
        args.self = self;
        args.frame = o->frame;
        if (o->shape->desc->m2) {
            o->shape->desc->m2(o->shape, &args.c, tVectorBest, 0);
        }
        FindLocalMinimum((void*)ScoreTargetPathAt, &args, 0.5f, 0.25f, 0.25f, 3.0f, &t, 0);
        func_001CEB18(self, args.frame, &args.c, 0, &cur0, &cur1, t);
        if (o != keep) {
            TransformPointBetweenFrames(o->frame, 0, &args.c, &p);
            if (AddTargetObstructionCost(t, self, 0, 0, &self->v140, &self->v150, &cur0, &cur1, &p)) {
                continue;
            }
        }
        best0 = cur0;
        kind = 7;
        best0.z -= 75.0f;
        best1 = cur1;
        bestVector = o;
        bestCost = cost <? bestCost;
        bestT = t;
        bestVectorT = tVectorBest;
    }
    for (o = (TargetCand*)g_targetPointList.head; o != 0; o = o->next50) {
        CostContext ctx;
        Vec02 d;
        // The point and curve searches weigh their cost and test it against the limit, both
        // named here (bound by reference: their %hi parts are formed at the top of the body).
        const f32& weight = D_00274E10;
        const f32& maxCost = D_00274E20;
        ConvertPositionToWorld(o, &at);
        if (o->f70 < self->pos.z - at.z) {
            continue;
        }
        CostContext* c = &ctx;
        void* fn = (void*)ScoreTargetPointAt;
        Vu0::Set(d, Vu0::Sub(Vu0::Vec::Of(self->v140), Vu0::Vec::Of(at)).q);
        ctx.v = self->v150;
        ctx.self = self;
        ctx.target = o;
        f32 lo = -3.40282347e+38f;
        f32 hi = 3.40282347e+38f;
        FindLocalMinimum(fn, c, ArctangentOfRatio(d.y, d.x) * o->f5C, D_00274E40, lo, hi, &tPoint, &cost);
        cost = cost * weight;
        if (o != keep) {
            if (cost >= maxCost) {
                continue;
            }
            cost = AddRepeatTargetPenalty(self, o, cost, D_00274E38);
            if (bestCost <= cost) {
                continue;
            }
        }
        PlaceOnTargetPoint(o, &at, 0, tPoint);
        ScorePlayerTargetPlacement(self, &self->v150, o->frame, &at, 0, &t, 0, &cur0, &cur1);
        cur1.z = self->v150.z + t * self->f358;
        if (o != keep && AddTargetObstructionCost(t, self, 0, 0, self->f6D4, &self->v150, &cur0, &cur1, 0)) {
            continue;
        }
        best0 = cur0;
        best1 = cur1;
        bestPoint = o;
        kind = 1;
        bestCost = cost <? bestCost;
        bestT = t;
        bestPointT = tPoint;
    }
    for (o = (TargetCand*)g_targetCurveList.head; o != 0; o = o->next38) {
        Vec02 at2;
        CostContext ctx;
        const f32& weight = D_00274E10;
        const f32& maxCost = D_00274E20;
        TransformPointBetweenFrames(0, o->frame, self->f6D4, &at);
        if (o->shape->desc->m10) {
            o->shape->desc->m10(o->shape, &at, 0, &at2, 0, 0, &tCurve);
        }
        TransformPointBetweenFrames(o->frame, 0, &at2, &at2);
        if (o->f58 < self->pos.z - at2.z) {
            continue;
        }
        CostContext* c = &ctx;
        ctx.self = self;
        ctx.v = self->v150;
        ctx.target = o;
        f32 start = tCurve;
        FindLocalMinimum((void*)ScoreTargetCurveAt, c, start, D_00274E44, 30.0f, o->shape->desc->m8(o->shape) - 30.0f,
                         &tCurveBest, &cost);
        cost = cost * weight;
        if (o != keep) {
            if (cost >= maxCost) {
                continue;
            }
            cost = AddRepeatTargetPenalty(self, o, cost, D_00274E34);
            if (bestCost <= cost) {
                continue;
            }
        }
        PlaceOnTargetCurve(o, &at2, 0, tCurveBest);
        ScorePlayerTargetPlacement(self, &self->v150, o->frame, &at2, 0, &t, 0, &cur0, &cur1);
        cur1.z = self->v150.z + t * self->f358;
        if (o != keep && AddTargetObstructionCost(t, self, 0, 0, self->f6D4, &self->v150, &cur0, &cur1, 0)) {
            continue;
        }
        bestCost = cost <? bestCost;
        best0 = cur0;
        best1 = cur1;
        bestCurve = o;
        kind = 0;
        bestT = t;
        bestCurveT = tCurveBest;
    }
    if (g_codeChecksumFailed != 0 && RandomIntInRange(0, 100) > 20) {
        return self->f2228;
    }
    s32 state;
    switch (kind) {
    case 3:
        self->f23B8 = bestObject;
        state = 0xA;
        break;
    case 4:
        self->f23BC = bestPath;
        self->f23C0 = bestPathT;
        self->f23C4 = bestPath->shape->desc->m5(bestPath->shape, bestPathT);
        state = 0xB;
        break;
    case 1:
        self->f23A8 = bestPoint;
        self->f23AC = bestPointT;
        state = 0xD;
        break;
    case 0:
        self->f23A0 = bestCurve;
        self->f23A4 = bestCurveT;
        state = 0xC;
        break;
    case 6:
        self->f2208 = 0;
        self->f2204 = bestClass75;
        self->f2200 = bestClass75;
        func_001C61E0(self, 0);
        UpdatePlayerAimTarget(self);
        state = 0xE;
        break;
    case 7:
        self->f2208 = bestVector;
        self->f220C = bestVectorT;
        self->f2204 = 0;
        self->f2200 = 0;
        func_001C61E0(self, 0);
        UpdatePlayerAimTarget(self);
        state = 0xF;
        break;
    default:
        StartSoundEffect(0x7E, 0, 0, &self->v140, 3000.0f, 300.0f, D_00262E24, 0.0f, 0.0f, 0, 0);
        state = self->f2228;
        break;
    }
    TargetRecord* r = self->f2514;
    r->time = g_gameClock.time + bestT;
    self->f2514->a = best0;
    self->f2514->a.z += 75.0f;
    self->f2514->b = best1;
    return state;
}
