// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: case 54 reads its third value as a plain integer instead of calling func_001384A0, and cases 38, 45 and 47 are written apart.
void ReadAnimationEvents(void* unused, Stream83* r, s32 flag, s32* count, AnimEvent** out)
{
    AnimEvent* e;
    s32 i;
    s32 merged;
    *count = ReadBufferedS8(r);
    *out = (AnimEvent*)AllocateZeroedFrontMemory(*count * 16);
    for (i = 0; i < *count; i++) {
        e = &(*out)[i];
        e->kind = ReadBufferedS8(r);
        if (flag) e->a0.f = (f32)ReadBufferedS16(r) * 0.016666668f;
        switch (e->kind) {
        case 44:
        case 51:
            ReadOptionalBufferedBlock(r, &e->a8.i);
            break;
        case 0: {
            SoundChoice t;
            SoundChoice* g;
            s32 j;
            s32 k;
            AnimEvent* q;
            merged = 0;
            t.ids[0] = ReadBufferedS16(r);
            t.target = ReadBufferedS16(r);
            t.f14 = ReadBufferedS32(r);
            t.f18 = ReadBufferedS32(r);
            t.f24 = ReadBufferedFloat(r);
            t.f1C = ReadBufferedFloat(r);
            t.f20 = ReadBufferedFloat(r);
            t.count = 1;
            t.cur = 0;
            k = i - 1;
            do {
                j = k;
                goto test;
            ins:
                g->ids[g->count++] = t.ids[0];
                goto done;
            } while (0);
        test:
            q = &(*out)[j];
            if (q->a0.f != e->a0.f) goto done;
            if (j < 0) goto done;
            if (q->kind != 0) {
                j--;
                goto test;
            }
            *count = *count - 1;
            i = k;
            merged = 1;
            g = (SoundChoice*)q->a8.i;
            if (g->count < 6) goto ins;
        done:
            if (!merged) {
                e->a8.i = (s32)AllocateFrontMemory(0x28);
                *(SoundChoice*)e->a8.i = t;
            }
            break;
        }
        case 4:
        case 7:
            F32(e->a8.i) = (f32)ReadBufferedS16(r) * 0.016666668f;
            F32(e->aC.i) = ReadBufferedFloat(r);
            break;
        case 19:
        case 20:
            e->a8.i = ReadBufferedS16(r);
            e->aC.i = ReadBufferedU8(r);
            break;
        case 16:
            e->a8.i = ReadBufferedS16(r);
            H0(e->aC.i) = ReadBufferedS8(r);
            H2(e->aC.i) = ReadBufferedS8(r);
            break;
        case 21:
        case 23:
            e->a8.i = (s32)AllocateZeroedFrontMemory(0xC);
            ((EventAttachmentDrive*)e->a8.i)->owner = ReadBufferedS16(r);
            ((EventAttachmentDrive*)e->a8.i)->f4 = ReadBufferedFloat(r);
            ((EventAttachmentDrive*)e->a8.i)->f8 = ReadBufferedFloat(r);
            break;
        case 25:
        case 26:
            H0(e->a8.i) = ReadBufferedS16(r);
            e->aC.i = (s32)AllocateZeroedFrontMemory(0x14);
            ((FadeRequest*)e->aC.i)->kind = 1;
            ((FadeRequest*)e->aC.i)->f08 = ReadBufferedS16(r);
            ((FadeRequest*)e->aC.i)->f0C = -1;
            ((FadeRequest*)e->aC.i)->flags = 0;
            ((FadeRequest*)e->aC.i)->text = (u8*)AllocateZeroedFrontMemory(0x20);
            ReadBufferedStreamBytes(r, 0x20, ((FadeRequest*)e->aC.i)->text);
            break;
        case 27:
            e->a8.i = ReadBufferedU8(r);
            e->aC.i = ReadBufferedS16(r);
            break;
        case 28:
            e->a8.i = (s32)AllocateZeroedFrontMemory(0x10);
            ((EventObjectPair*)e->a8.i)->f0 = ReadBufferedS16(r);
            ((EventObjectPair*)e->a8.i)->f4 = ReadBufferedS16(r);
            F32(((EventObjectPair*)e->a8.i)->f8) = ReadBufferedFloat(r);
            ((EventObjectPair*)e->a8.i)->fC = ReadBufferedFloat(r);
            break;
        case 37:
            H0(e->a8.i) = ReadBufferedS16(r);
            H2(e->a8.i) = ReadBufferedS16(r);
            break;
        case 38:
            e->a8.i = ReadBufferedS16(r);
            e->aC.i = ReadBufferedS16(r);
            break;
        case 6: case 12: case 13: case 17: case 18: case 22: case 24:
        case 29: case 30: case 31: case 32: case 35: case 36: case 39:
        case 41: case 59:
            e->a8.i = ReadBufferedS16(r);
            break;
        case 40:
            e->a8.i = ReadBufferedU16(r);
            break;
        case 45:
            e->a8.i = ReadBufferedS16(r);
            e->aC.i = ReadBufferedS16(r);
            break;
        case 47:
            e->a8.i = ReadBufferedS16(r);
            e->aC.i = ReadBufferedS16(r);
            break;
        case 48:
            e->a8.i = (s32)AllocateZeroedFrontMemory(0x10);
            ((EventObjectPair*)e->a8.i)->f0 = ReadBufferedS16(r);
            ((EventObjectPair*)e->a8.i)->f4 = ReadBufferedS16(r);
            ((EventObjectPair*)e->a8.i)->f8 = ReadBufferedS16(r);
            ((EventObjectPair*)e->a8.i)->fC = ReadBufferedFloat(r);
            break;
        case 9:
        case 10:
            e->a8.i = ReadBufferedS16(r);
            F32(e->aC.i) = ReadBufferedFloat(r);
            break;
        case 46:
        case 52:
            H0(e->a8.i) = ReadBufferedS16(r);
            H2(e->a8.i) = ReadBufferedS16(r);
            H0(e->aC.i) = ReadBufferedS16(r);
            break;
        case 54:
            H0(e->a8.i) = ReadBufferedS16(r);
            H2(e->a8.i) = ReadBufferedS16(r);
            e->aC.i = ReadBufferedS16(r);
            break;
        case 5:
        case 33:
        case 57:
        case 58:
            F32(e->a8.i) = ReadBufferedFloat(r);
            break;
        }
    }
}
