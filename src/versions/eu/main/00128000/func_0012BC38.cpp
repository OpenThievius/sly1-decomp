// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: case 54 reads its third value as a plain integer instead of calling func_001384A0, and cases 38, 45 and 47 are written apart.
void func_0012BC38(void* unused, Rd_12BC38* r, s32 flag, s32* count, Rec_12BC38** out)
{
    Rec_12BC38* e;
    s32 i;
    s32 merged;
    *count = func_00137CC0(r);
    *out = (Rec_12BC38*)func_0018D5C0(*count * 16);
    for (i = 0; i < *count; i++) {
        e = &(*out)[i];
        e->kind = func_00137CC0(r);
        if (flag) e->t = (f32)func_00137D10(r) * 0.016666668f;
        switch (e->kind) {
        case 44:
        case 51:
            func_00138550(r, &e->w8);
            break;
        case 0: {
            Ev_12BC38 t;
            Grp_12BC38* g;
            s32 j;
            s32 k;
            Rec_12BC38* q;
            merged = 0;
            t.h2 = func_00137D10(r);
            t.h10 = func_00137D10(r);
            t.w14 = func_00137D78(r);
            t.w18 = func_00137D78(r);
            t.f24 = func_00137DF8(r);
            t.f1C = func_00137DF8(r);
            t.f20 = func_00137DF8(r);
            t.h0 = 1;
            t.hE = 0;
            k = i - 1;
            do {
                j = k;
                goto test;
            ins:
                g->h[g->n++] = t.h2;
                goto done;
            } while (0);
        test:
            q = &(*out)[j];
            if (q->t != e->t) goto done;
            if (j < 0) goto done;
            if (q->kind != 0) {
                j--;
                goto test;
            }
            *count = *count - 1;
            i = k;
            merged = 1;
            g = (Grp_12BC38*)q->w8;
            if (g->n < 6) goto ins;
        done:
            if (!merged) {
                e->w8 = (s32)func_0018D500(0x28);
                *(Ev_12BC38*)e->w8 = t;
            }
            break;
        }
        case 4:
        case 7:
            F32(e->w8) = (f32)func_00137D10(r) * 0.016666668f;
            F32(e->wC) = func_00137DF8(r);
            break;
        case 19:
        case 20:
            e->w8 = func_00137D10(r);
            e->wC = func_00137B90(r);
            break;
        case 16:
            e->w8 = func_00137D10(r);
            H0(e->wC) = func_00137CC0(r);
            H2(e->wC) = func_00137CC0(r);
            break;
        case 21:
        case 23:
            e->w8 = (s32)func_0018D5C0(0xC);
            ((Sub_12BC38*)e->w8)->w0 = func_00137D10(r);
            F32(((Sub_12BC38*)e->w8)->w4) = func_00137DF8(r);
            F32(((Sub_12BC38*)e->w8)->w8) = func_00137DF8(r);
            break;
        case 25:
        case 26:
            H0(e->w8) = func_00137D10(r);
            e->wC = (s32)func_0018D5C0(0x14);
            ((Sub_12BC38*)e->wC)->w0 = 1;
            ((Sub_12BC38*)e->wC)->w8 = func_00137D10(r);
            ((Sub_12BC38*)e->wC)->wC = -1;
            ((Sub_12BC38*)e->wC)->w10 = 0;
            ((Sub_12BC38*)e->wC)->w4 = (s32)func_0018D5C0(0x20);
            func_00137A60(r, 0x20, (void*)((Sub_12BC38*)e->wC)->w4);
            break;
        case 27:
            e->w8 = func_00137B90(r);
            e->wC = func_00137D10(r);
            break;
        case 28:
            e->w8 = (s32)func_0018D5C0(0x10);
            ((Sub_12BC38*)e->w8)->w0 = func_00137D10(r);
            ((Sub_12BC38*)e->w8)->w4 = func_00137D10(r);
            F32(((Sub_12BC38*)e->w8)->w8) = func_00137DF8(r);
            F32(((Sub_12BC38*)e->w8)->wC) = func_00137DF8(r);
            break;
        case 37:
            H0(e->w8) = func_00137D10(r);
            H2(e->w8) = func_00137D10(r);
            break;
        case 38:
            e->w8 = func_00137D10(r);
            e->wC = func_00137D10(r);
            break;
        case 6: case 12: case 13: case 17: case 18: case 22: case 24:
        case 29: case 30: case 31: case 32: case 35: case 36: case 39:
        case 41: case 59:
            e->w8 = func_00137D10(r);
            break;
        case 40:
            e->w8 = func_00137BE0(r);
            break;
        case 45:
            e->w8 = func_00137D10(r);
            e->wC = func_00137D10(r);
            break;
        case 47:
            e->w8 = func_00137D10(r);
            e->wC = func_00137D10(r);
            break;
        case 48:
            e->w8 = (s32)func_0018D5C0(0x10);
            ((Sub_12BC38*)e->w8)->w0 = func_00137D10(r);
            ((Sub_12BC38*)e->w8)->w4 = func_00137D10(r);
            ((Sub_12BC38*)e->w8)->w8 = func_00137D10(r);
            F32(((Sub_12BC38*)e->w8)->wC) = func_00137DF8(r);
            break;
        case 9:
        case 10:
            e->w8 = func_00137D10(r);
            F32(e->wC) = func_00137DF8(r);
            break;
        case 46:
        case 52:
            H0(e->w8) = func_00137D10(r);
            H2(e->w8) = func_00137D10(r);
            H0(e->wC) = func_00137D10(r);
            break;
        case 54:
            H0(e->w8) = func_00137D10(r);
            H2(e->w8) = func_00137D10(r);
            e->wC = func_00137D10(r);
            break;
        case 5:
        case 33:
        case 57:
        case 58:
            F32(e->w8) = func_00137DF8(r);
            break;
        }
    }
}
