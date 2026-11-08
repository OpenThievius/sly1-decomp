// SPDX-License-Identifier: AGPL-3.0-or-later
// A copy of words: the odd ones one at a time, then four at a time, each four read before they
// are written. Retail's packet builders inline it (FlushVertexBatch in file_15F678.cpp,
// UploadLightVolumes in main_loop.cpp): with a constant count the first loop folds away and the
// second counts down by four to a `bgez`. Written for this project from what retail's code does.
#ifndef WORD_COPY_H
#define WORD_COPY_H

#include "common.h"

struct WordCopy {
    static void Words(void* to, void* from, s32 n)
    {
        s32* dst = (s32*)to;
        s32* src = (s32*)from;
        s32 rem = n & 3;
        s32 bulk = n - rem;
        s32 i;
        for (i = 0; i < rem; i++) {
            *dst++ = *src++;
        }
        for (i = 0; i < bulk; i += 4) {
            s32 a = src[0];
            s32 b = src[1];
            s32 c = src[2];
            s32 d = src[3];
            dst[0] = a;
            dst[1] = b;
            dst[2] = c;
            dst[3] = d;
            src += 4;
            dst += 4;
        }
    }
};

#endif
