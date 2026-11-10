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
    InvertRigidTransform(&self->m.m[3], &self->m, &b.m40);
    b.f80 = part->f40;
    n300 = 0;
    n304 = 0;
    if (part->f18 != 0) {
        if (part->light != 0) {
            n304 = 1;
            n300 = 1;
            lights[0] = ((LightEu_166690*)part->light)->f58C;
            b.fA0 = self->f60;
            b.mode = 4;
            b.f9C = 2;
        } else if (part->f28 != 0) {
            b.f9C = CollectLightsForSphere(g_currentWorld, &self->f60, part->f10, 1, 0x80, &n300, &n304, (s32*)lights);
            b.fA0 = self->f60;
            b.mode = 4;
        } else if (cache == 0) {
            b.f9C = CollectLightsForSphere(g_currentWorld, &self->f60, part->f10, 3, 0x80, &n300, &n304, (s32*)lights);
            b.mode = 2;
        } else if (cache->f8 >= g_lightingChangeFrame) {
            if (g_lightCount != 0) {
                b.f9C = CollectLightsForSphere(g_currentWorld, &self->f60, part->f10, 2, 0x80, 0, &n304, (s32*)lights);
            }
            if (n304 != 0) {
                b.mode = 1;
                if (b.f9C < cache->fC) {
                    b.f9C = cache->fC;
                }
            } else {
                b.mode = 0;
                b.f9C = cache->fC;
            }
        } else {
            b.f9C = CollectLightsForSphere(g_currentWorld, &self->f60, part->f10, 7, 0x80, &n300, &n304, (s32*)lights);
            if (n300 == 0 && n304 > 0) {
                b.mode = 2;
            } else {
                b.mode = 3;
                cache->f8 = g_frameCount;
            }
            cache->fC = b.f9C;
        }
    } else {
        b.mode = -1;
        b.f9C = 2;
    }

    useCache = cache != 0 && (owner->cls->flags & 2) && owner->f410 != 0;
    n308 = 0;
    if (!useCache && (part->flags & 3)) {
        CollectRangeRecordsInReach(g_currentWorld, &self->f60, 0x10, &n308, nodes, part->f10);
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
                if (t->count != 0 && t->f18 == g_gameClock[1]) {
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
            u32 addr = e->slots->f4;
            for (k = 0; k < e->nbones; k++) {
                Vif_166690::UnpackAt(&g_vifPacketWriter, &skin->bones[e->bones[k]].m, 0x40, 0x6C04C000, addr);
                addr += 4;
            }
        }
        n = skin->count;
        if (n > 0) {
            Vif_166690::UnpackAt(&g_vifPacketWriter, skin->words, n << 2, (n << 16) | 0x6000C000, e->slots->f6);
        }
        Vif_166690::Pad(&g_vifPacketWriter);
        Vif_166690::Close(&g_vifPacketWriter, tag);

        switch (*e->kind) {
        case 0:
            Vif_166690::Refs(&g_vifPacketWriter, e->f38, e->f44);
            switch (b.mode) {
            case 0:
                if (part->f54) {
                    Vif_166690::Call(&g_vifPacketWriter, e->f4C);
                } else {
                    Vif_166690::Refs(&g_vifPacketWriter, e->f40, e->f4C);
                }
                Vif_166690::Refs(&g_vifPacketWriter, c->f00, c->f04);
                Vif_166690::Refs(&g_vifPacketWriter, c->f0C, c->f10);
                break;
            case 1:
                Vif_166690::Refs(&g_vifPacketWriter, c->f0C, c->f10);
                Vif_166690::Refs(&g_vifPacketWriter, e->f3C, e->f48);
                for (k = 0; k < n304; k++) {
                    u8* l = (u8*)lights[k];
                    Vif_166690::Refs(&g_vifPacketWriter, *(s32*)(l + 0x418), (s32)(l + 0x420));
                }
                Vif_166690::Cnt1(&g_vifPacketWriter);
                Vif_166690::Mscal(&g_vifPacketWriter, D_00001210);
                Vif_166690::Word(&g_vifPacketWriter, 0x10000000);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                if (part->f54) {
                    Vif_166690::Call(&g_vifPacketWriter, e->f4C);
                } else {
                    Vif_166690::Refs(&g_vifPacketWriter, e->f40, e->f4C);
                }
                Vif_166690::Cnt1(&g_vifPacketWriter);
                Vif_166690::Mscal(&g_vifPacketWriter, D_00000010);
                Vif_166690::Word(&g_vifPacketWriter, 0x10000000);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                break;
            case 2:
            case 4:
                Vif_166690::Refs(&g_vifPacketWriter, e->f3C, e->f48);
                for (k = 0; k < n304; k++) {
                    u8* l = (u8*)lights[k];
                    Vif_166690::Refs(&g_vifPacketWriter, *(s32*)(l + 0x418), (s32)(l + 0x420));
                }
                Vif_166690::Cnt1(&g_vifPacketWriter);
                Vif_166690::Mscal(&g_vifPacketWriter, D_00001210);
                Vif_166690::Word(&g_vifPacketWriter, 0x10000000);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                if (part->f54) {
                    Vif_166690::Call(&g_vifPacketWriter, e->f4C);
                } else {
                    Vif_166690::Refs(&g_vifPacketWriter, e->f40, e->f4C);
                }
                Vif_166690::Cnt1(&g_vifPacketWriter);
                Vif_166690::Mscalf(&g_vifPacketWriter, D_00000010);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                break;
            case 3: {
                Vif_166690::Refs(&g_vifPacketWriter, e->f3C, e->f48);
                for (k = 0; k < n300; k++) {
                    u8* l = (u8*)lights[k];
                    Vif_166690::Refs(&g_vifPacketWriter, *(s32*)(l + 0x418), (s32)(l + 0x420));
                }
                Vif_166690::Cnt1(&g_vifPacketWriter);
                Vif_166690::Mscal(&g_vifPacketWriter, D_00001210);
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
                    Vif_166690::Refs(&g_vifPacketWriter, e->f3C, e->f48);
                    for (k = 0; k < n304; k++) {
                        u8* l = (u8*)lights[k];
                        Vif_166690::Refs(&g_vifPacketWriter, *(s32*)(l + 0x418), (s32)(l + 0x420));
                    }
                    Vif_166690::Cnt1(&g_vifPacketWriter);
                    Vif_166690::Mscal(&g_vifPacketWriter, D_00001210);
                    Vif_166690::Word(&g_vifPacketWriter, 0);
                    Vif_166690::Word(&g_vifPacketWriter, 0);
                    Vif_166690::Word(&g_vifPacketWriter, 0);
                }
                if (part->f54) {
                    Vif_166690::Call(&g_vifPacketWriter, e->f4C);
                } else {
                    Vif_166690::Refs(&g_vifPacketWriter, e->f40, e->f4C);
                }
                Vif_166690::Cnt1(&g_vifPacketWriter);
                Vif_166690::Mscalf(&g_vifPacketWriter, D_00000010);
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
            if (part->f54) {
                Vif_166690::Call(&g_vifPacketWriter, e->f44);
            } else {
                Vif_166690::Refs(&g_vifPacketWriter, e->f38, e->f44);
            }
            break;
        case 4:
            if (part->f54) {
                Vif_166690::Call(&g_vifPacketWriter, e->f44);
            } else {
                Vif_166690::Refs(&g_vifPacketWriter, e->f38, e->f44);
            }
            continue;
        case 5:
            if (part->f54) {
                Vif_166690::Call(&g_vifPacketWriter, e->f44);
            } else {
                Vif_166690::Refs(&g_vifPacketWriter, e->f38, e->f44);
            }
            continue;
        default:
            continue;
        }

        if (useCache) {
            if (c->f18 == g_gameTime) {
                n308 = c->count;
            } else {
                n308 = 0;
            }
        }
        if (n308 != 0) {
            TransformByMatrixWithW(&b, 1.0f, e, &q);
            r = e->f10 * part->f50;
        }
        for (j = 0; j < n308; j++) {
            void* node;
            if (useCache) {
                node = c->nodes[j];
            } else {
                node = nodes[j];
                if (RangeRecordMatchesKinds(node, part->flags) == 0) {
                    continue;
                }
            }
            if (RangeRecordReachesSphere(node, &q, r) != 0) {
                QueueRangeRecordPacket(node);
            }
        }
    }

    if (skin != 0 && (skin->flags & 1)) {
        return;
    }
    if (self->f54 <= 0.0f) {
        return;
    }
    for (t = 0; t < part->nstrips; t++) {
        Strip_166690* s = &part->strips[t];
        s32 n;
        if (skin != 0 && (skin->flags & 2)) {
            u8 a = Alpha_166690((s32)(skin->a * self->f54));
            q.hi = 1;
            q.lo = Rgbaq_166690(a, skin->r, skin->g, skin->b);
        } else {
            q.lo = Rgbaq_166690(Alpha_166690((s32)(D_002623E0.a * self->f54)), D_002623E0.r, D_002623E0.g, D_002623E0.b);
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
            u32 addr = s->slots->f8;
            s32 k;
            for (k = 0; k < s->nbones; k++) {
                Vif_166690::UnpackAt(&g_vifPacketWriter, &skin->bones[s->bones[k]].m, 0x40, 0x6C04C000, addr);
                addr += 4;
            }
        }
        n = skin->count;
        if (n > 0) {
            Vif_166690::UnpackAt(&g_vifPacketWriter, skin->words, n << 2, (n << 16) | 0x6000C000, s->slots->fA);
        }
        Vif_166690::UnpackV4(&g_vifPacketWriter, &q, 1, 0x1A);
        Vif_166690::Pad(&g_vifPacketWriter);
        Vif_166690::Close(&g_vifPacketWriter, tag);
        Vif_166690::Refs(&g_vifPacketWriter, s->f18, s->f1C);
    }
}

