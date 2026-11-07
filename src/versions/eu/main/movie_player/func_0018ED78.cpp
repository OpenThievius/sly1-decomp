// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: also calls func_0018EB98 on the block at a2 + 0x80
s32 func_0018ED78(void* a0, s32 a1, MoviePlayer* a2)
{
    FeedMovieDecoder(a2, 0);
    UpdateMovieStream(&a2->stream);
    return 1;
}
