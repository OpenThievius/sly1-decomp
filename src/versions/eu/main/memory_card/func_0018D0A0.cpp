// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL adds a check after the switch: for 0 or 12, a state other than 2 forces 11 and f14 = 1.
s32 PollMemoryCard(MemoryCard* o)
{
    s32 r = FinishMemoryCardCall(GetCardInfo(o->port, o->slot, &o->f24, &o->freeBlocks, &o->f2C), (void*)1, 0);
    switch (r) {
    case 9:
    case 11:
        o->targetState = 1;
        r = 11;
        break;
    case 10:
    case 12:
        o->targetState = 2;
        r = 12;
        break;
    case 0:
        if (o->f2C != 0) {
            if (o->targetState < 3)
                o->targetState = 3;
            else
                break;
        } else
            o->targetState = 2;
        break;
    }
    if ((r == 0 || r == 12) && o->f24 != 2) {
        o->targetState = 1;
        r = 11;
    }
    o->nextPollTime = g_elapsedTime[0] + 0.3f;
    return r;
}
