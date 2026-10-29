// SPDX-License-Identifier: AGPL-3.0-or-later

#include "common.h"

/*
 * Attempt compiled with SN GCC 2.95.3 and -O2 -G0 -fno-exceptions.
 * func_0013C9B0 still schedules its field stores differently from retail.
 */

struct InitialState {
	s32 field_00;
	s32 field_04;
	s32 field_08;
	s32 field_0C;
	s32 field_10;
	s32 field_14;
	s32 field_18;
	s32 field_1C;
};

void func_0013C9B0(InitialState* state) {
	state->field_1C = 0;
	state->field_10 = state->field_04;
	state->field_18 = 0;
	state->field_14 = 0;
	state->field_0C = 0;
	state->field_08 = 0;
}
