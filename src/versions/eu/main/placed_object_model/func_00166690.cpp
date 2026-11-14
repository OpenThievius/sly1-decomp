// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the part's light record keeps its light at +0x58C (US +0x27C).
struct LightEu_166690 { u8 pad0[0x58C]; void* f58C; };
void DrawModelPart(Frame_166690* self)
{
    Batch_166690 b;
    void* lights[128];
    void* nodes[16];
    Qw_166690 q;
    s32 n300;
    s32 n304;
    s32 n308;
    Part_166690* part = self->part;
    Owner_166690* owner = self->owner;
    CacheSet_166690* cache = self->cache;
    Skin_166690* skin = self->skin;
    s32 useCache;
    s32 count;
    s32 i;
    s32 t;
    u32* tag;
    Mesh_166690* e;
    Cache_166690* c;
    f32 r;

    b.m = self->m;
    InvertRigidTransform(&self->m.m[3], &self->m, (Quad16*)&b.m40);
    b.fog = part->fog;
    n300 = 0;
    n304 = 0;
    if (part->lit != 0) {
        if (part->light != 0) {
            n304 = 1;
            n300 = 1;
            lights[0] = ((LightEu_166690*)part->light)->f58C;
            b.center = self->center;
            b.mode = 4;
            b.lightCount = 2;
        } else if (part->skinned != 0) {
            b.lightCount = CollectLightsForSphere(g_currentWorld, (const Vec02*)&self->center, part->radius, 1, 0x80, &n300, &n304, (LightObject**)lights);
            b.center = self->center;
            b.mode = 4;
        } else if (cache == 0) {
            b.lightCount = CollectLightsForSphere(g_currentWorld, (const Vec02*)&self->center, part->radius, 3, 0x80, &n300, &n304, (LightObject**)lights);
            b.mode = 2;
        } else if (cache->lightFrame >= g_lightingChangeFrame) {
            if (g_lightCount != 0) {
                b.lightCount = CollectLightsForSphere(g_currentWorld, (const Vec02*)&self->center, part->radius, 2, 0x80, 0, &n304, (LightObject**)lights);
            }
            if (n304 != 0) {
                b.mode = 1;
                if (b.lightCount < cache->lightCount) {
                    b.lightCount = cache->lightCount;
                }
            } else {
                b.mode = 0;
                b.lightCount = cache->lightCount;
            }
        } else {
            b.lightCount = CollectLightsForSphere(g_currentWorld, (const Vec02*)&self->center, part->radius, 7, 0x80, &n300, &n304, (LightObject**)lights);
            if (n300 == 0 && n304 > 0) {
                b.mode = 2;
            } else {
                b.mode = 3;
                cache->lightFrame = g_frameCount;
            }
            cache->lightCount = b.lightCount;
        }
    } else {
        b.mode = -1;
        b.lightCount = 2;
    }

    useCache = cache != 0 && (owner->cls->flags & 2) && owner->f410 != 0;
    n308 = 0;
    if (!useCache && (part->flags & 3)) {
        CollectRangeRecordsInReach(g_currentWorld, &self->center, 0x10, &n308, (RangeRecord**)nodes, part->radius);
    }
    b.f90 = self->f50;
    b.f98 = 1;
    if (part->flags & 4) {
        b.w.fAC = 1.0f;
    } else {
        b.w.fAC = ((World_166690*)g_currentWorld)->f234C;
    }
    count = 0;

    if (cache != 0 && cache->f18 != 0 && (b.mode == -1 || b.mode == 0)
        && (useCache || n308 == 0) && !(skin->flags & 3)) {
        if (useCache) {
            for (i = 0; i < part->nmeshes; i++) {
                Cache_166690* t = &cache->items[i];
                if (t->count != 0 && t->lastTime == g_gameClock[1]) {
                    goto slow;
                }
            }
        }
        {
            s32 half = D_00262474 != 0x28;
            D_00262474 = 0x23C - D_00262474;
            tag = Vif_166690::Open(&g_vifPacketWriter);
            Vif_166690::Word(&g_vifPacketWriter, D_00262474 | 0x03000000);
            Vif_166690::Word(&g_vifPacketWriter, 0x02000000);
            Vif_166690::UnpackV4(&g_vifPacketWriter, &b, 0xB, 0);
            Vif_166690::Pad(&g_vifPacketWriter);
            Vif_166690::Close(&g_vifPacketWriter, tag);
            Vif_166690::Call(&g_vifPacketWriter, cache->refs[half]);
            if ((part->nmeshes + part->nstrips) & 1) {
                return;
            }
            D_00262474 = 0x23C - D_00262474;
            return;
        }
    }
slow:
    for (i = 0; i < part->nmeshes; i++) {
        s32 k;
        s32 j;
        s32 n;
        e = &part->meshes[i];
        if (cache != 0) {
            c = &cache->items[i];
        } else {
            c = 0;
        }
        D_00262474 = 0x23C - D_00262474;
        tag = Vif_166690::Open(&g_vifPacketWriter);
        count++;
        Vif_166690::Word(&g_vifPacketWriter, D_00262474 | 0x03000000);
        Vif_166690::Word(&g_vifPacketWriter, 0x02000000);
        if (count == 1) {
            Vif_166690::UnpackV4(&g_vifPacketWriter, &b, 0xB, 0);
        }
        if (e->nbones > 0) {
            u32 addr = e->slots->meshBoneSlot;
            for (k = 0; k < e->nbones; k++) {
                Vif_166690::UnpackAt(&g_vifPacketWriter, &skin->bones[e->bones[k]].m, 0x40, 0x6C04C000, addr);
                addr += 4;
            }
        }
        n = skin->count;
        if (n > 0) {
            Vif_166690::UnpackAt(&g_vifPacketWriter, skin->words, n << 2, (n << 16) | 0x6000C000, e->slots->meshSkinSlot);
        }
        Vif_166690::Pad(&g_vifPacketWriter);
        Vif_166690::Close(&g_vifPacketWriter, tag);

        switch (*e->kind) {
        case 0:
            Vif_166690::Refs(&g_vifPacketWriter, e->qwc0, e->addr0);
            switch (b.mode) {
            case 0:
                if (part->link) {
                    Vif_166690::Call(&g_vifPacketWriter, e->addr2);
                } else {
                    Vif_166690::Refs(&g_vifPacketWriter, e->qwc2, e->addr2);
                }
                Vif_166690::Refs(&g_vifPacketWriter, c->f00, c->f04);
                Vif_166690::Refs(&g_vifPacketWriter, c->f0C, c->f10);
                break;
            case 1:
                Vif_166690::Refs(&g_vifPacketWriter, c->f0C, c->f10);
                Vif_166690::Refs(&g_vifPacketWriter, e->qwc1, e->addr1);
                for (k = 0; k < n304; k++) {
                    u8* l = (u8*)lights[k];
                    Vif_166690::Refs(&g_vifPacketWriter, *(s32*)(l + 0x418), (s32)(l + 0x420));
                }
                Vif_166690::Cnt1(&g_vifPacketWriter);
                Vif_166690::Mscal(&g_vifPacketWriter, g_litBatchSecondProgram);
                Vif_166690::Word(&g_vifPacketWriter, 0x10000000);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                if (part->link) {
                    Vif_166690::Call(&g_vifPacketWriter, e->addr2);
                } else {
                    Vif_166690::Refs(&g_vifPacketWriter, e->qwc2, e->addr2);
                }
                Vif_166690::Cnt1(&g_vifPacketWriter);
                Vif_166690::Mscal(&g_vifPacketWriter, g_litBatchFinishProgram);
                Vif_166690::Word(&g_vifPacketWriter, 0x10000000);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                break;
            case 2:
            case 4:
                Vif_166690::Refs(&g_vifPacketWriter, e->qwc1, e->addr1);
                for (k = 0; k < n304; k++) {
                    u8* l = (u8*)lights[k];
                    Vif_166690::Refs(&g_vifPacketWriter, *(s32*)(l + 0x418), (s32)(l + 0x420));
                }
                Vif_166690::Cnt1(&g_vifPacketWriter);
                Vif_166690::Mscal(&g_vifPacketWriter, g_litBatchSecondProgram);
                Vif_166690::Word(&g_vifPacketWriter, 0x10000000);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                if (part->link) {
                    Vif_166690::Call(&g_vifPacketWriter, e->addr2);
                } else {
                    Vif_166690::Refs(&g_vifPacketWriter, e->qwc2, e->addr2);
                }
                Vif_166690::Cnt1(&g_vifPacketWriter);
                Vif_166690::Mscalf(&g_vifPacketWriter, g_litBatchFinishProgram);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                break;
            case 3: {
                Vif_166690::Refs(&g_vifPacketWriter, e->qwc1, e->addr1);
                for (k = 0; k < n300; k++) {
                    u8* l = (u8*)lights[k];
                    Vif_166690::Refs(&g_vifPacketWriter, *(s32*)(l + 0x418), (s32)(l + 0x420));
                }
                Vif_166690::Cnt1(&g_vifPacketWriter);
                Vif_166690::Mscal(&g_vifPacketWriter, g_litBatchSecondProgram);
                Vif_166690::Word(&g_vifPacketWriter, 0x90000000);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                {
                    s32 base = D_00262474;
                    u32* p = (u32*)g_buildFrameData++;
                    p[0] = ((base + e->slots->f0) << 4) + 0x1100C000;
                    p[1] = ((base + e->slots->f2) << 4) + 0x1100C000;
                    p[2] = ((base + e->slots->fE) << 4) + 0x1100C000;
                    p[3] = (u32)c;
                }
                if (k < n304) {
                    Vif_166690::Refs(&g_vifPacketWriter, e->qwc1, e->addr1);
                    for (k = 0; k < n304; k++) {
                        u8* l = (u8*)lights[k];
                        Vif_166690::Refs(&g_vifPacketWriter, *(s32*)(l + 0x418), (s32)(l + 0x420));
                    }
                    Vif_166690::Cnt1(&g_vifPacketWriter);
                    Vif_166690::Mscal(&g_vifPacketWriter, g_litBatchSecondProgram);
                    Vif_166690::Word(&g_vifPacketWriter, 0);
                    Vif_166690::Word(&g_vifPacketWriter, 0);
                    Vif_166690::Word(&g_vifPacketWriter, 0);
                }
                if (part->link) {
                    Vif_166690::Call(&g_vifPacketWriter, e->addr2);
                } else {
                    Vif_166690::Refs(&g_vifPacketWriter, e->qwc2, e->addr2);
                }
                Vif_166690::Cnt1(&g_vifPacketWriter);
                Vif_166690::Mscalf(&g_vifPacketWriter, g_litBatchFinishProgram);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                break;
            }
            }
            break;
        case 1:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            if (part->link) {
                Vif_166690::Call(&g_vifPacketWriter, e->addr0);
            } else {
                Vif_166690::Refs(&g_vifPacketWriter, e->qwc0, e->addr0);
            }
            break;
        case 4:
            if (part->link) {
                Vif_166690::Call(&g_vifPacketWriter, e->addr0);
            } else {
                Vif_166690::Refs(&g_vifPacketWriter, e->qwc0, e->addr0);
            }
            continue;
        case 5:
            if (part->link) {
                Vif_166690::Call(&g_vifPacketWriter, e->addr0);
            } else {
                Vif_166690::Refs(&g_vifPacketWriter, e->qwc0, e->addr0);
            }
            continue;
        default:
            continue;
        }

        if (useCache) {
            if (c->lastTime == g_gameTime) {
                n308 = c->count;
            } else {
                n308 = 0;
            }
        }
        if (n308 != 0) {
            TransformByMatrixWithW((const Quad16*)&b, (const Vec02*)e, 1.0f, (Vec02*)&q);
            r = e->radius * part->radiusScale;
        }
        for (j = 0; j < n308; j++) {
            void* node;
            if (useCache) {
                node = c->nodes[j];
            } else {
                node = nodes[j];
                if (RangeRecordMatchesKinds((RangeRecord*)node, part->flags) == 0) {
                    continue;
                }
            }
            if (RangeRecordReachesSphere(node, &q, r) != 0) {
                QueueRangeRecordPacket((RangeRecord*)node);
            }
        }
    }

    if (skin != 0 && (skin->flags & 1)) {
        return;
    }
    if (self->alpha <= 0.0f) {
        return;
    }
    for (t = 0; t < part->nstrips; t++) {
        Strip_166690* s = &part->strips[t];
        s32 n;
        if (skin != 0 && (skin->flags & 2)) {
            u8 a = Alpha_166690((s32)(skin->a * self->alpha));
            q.hi = 1;
            q.lo = Rgbaq_166690(a, skin->r, skin->g, skin->b);
        } else {
            q.lo = Rgbaq_166690(Alpha_166690((s32)(D_002623E0.a * self->alpha)), D_002623E0.r, D_002623E0.g, D_002623E0.b);
            q.hi = 1;
        }
        D_00262474 = 0x23C - D_00262474;
        tag = Vif_166690::Open(&g_vifPacketWriter);
        count++;
        Vif_166690::Word(&g_vifPacketWriter, D_00262474 | 0x03000000);
        Vif_166690::Word(&g_vifPacketWriter, 0x02000000);
        if (count == 1) {
            Vif_166690::UnpackV4(&g_vifPacketWriter, &b, 0xB, 0);
        }
        if (s->nbones > 0) {
            u32 addr = s->slots->stripBoneSlot;
            s32 k;
            for (k = 0; k < s->nbones; k++) {
                Vif_166690::UnpackAt(&g_vifPacketWriter, &skin->bones[s->bones[k]].m, 0x40, 0x6C04C000, addr);
                addr += 4;
            }
        }
        n = skin->count;
        if (n > 0) {
            Vif_166690::UnpackAt(&g_vifPacketWriter, skin->words, n << 2, (n << 16) | 0x6000C000, s->slots->stripSkinSlot);
        }
        Vif_166690::UnpackV4(&g_vifPacketWriter, &q, 1, 0x1A);
        Vif_166690::Pad(&g_vifPacketWriter);
        Vif_166690::Close(&g_vifPacketWriter, tag);
        Vif_166690::Refs(&g_vifPacketWriter, s->qwc, s->addr);
    }
}

