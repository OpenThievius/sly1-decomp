// SPDX-License-Identifier: AGPL-3.0-or-later
// The symmetric solve, 0x14B0C0 to 0x14B550 (no .rodata, .data or .bss of its own):
// FactorSymmetricMatrix and SolveFactoredSystem, the factor and the forward and back
// substitution the active-set solver (active_set_solver.cpp) runs each round. Its edges are not
// proved by retail, only by the change of role from the item column (item_column.cpp) and to
// the class 0x10 and 0x11 methods (agent_registration.cpp): none of these functions reads .rodata or
// .data, so the cut before could lie from 0x14AF38 to 0x14B0C0 and the one after at 0x14B550 or
// later, up to 0x14B6A8. The name is ours, after its role.
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "state_notifier.h"
#include "world.h"
#include "camera.h"
#include "game_progress.h"
#include "effect.h"
#include "screen_element.h"
#include "font.h"
#include "gauge_manager.h"
#include "pooled_object.h"
#include "masked_collider.h"
#include "object_link.h"
#include "scatter_controller.h"
#include "shapes.h"
#include "object_pool.h"
#include "owner_message.h"
#include "vu0.h"
#include "scope_marker.h"
#include "mul_rotation.h"
#include "pad_record.h"
#include "ramp_profile.h"


void FactorSymmetricMatrix(s32 n, f32* a, f32* l)
{
    s32 i;
    s32 j;
    s32 k;
    f32 sum;

    if (n == 0)
    {
        return;
    }
    for (i = 0; i < n; i++)
    {
        l[i] = a[i];
    }
    if (__builtin_fabsf(l[0]) < 1e-8f)
    {
        for (j = 0; j < n; j++)
        {
            l[j * n] = 0.0f;
        }
    }
    else
    {
        for (j = 1; j < n; j++)
        {
            l[j * n] = a[j * n] / l[0];
        }
    }
    for (j = 1; j < n - 1; j++)
    {
        for (i = j; i < n; i++)
        {
            sum = 0.0f;
            for (k = 0; k < j; k++)
            {
                sum += l[i + k * n] * l[j * n + k];
            }
            l[j * n + i] = a[j * n + i] - sum;
        }
        if (__builtin_fabsf(l[j * n + j]) < 1e-8f)
        {
            for (k = j; k < n; k++)
            {
                l[k * n + j] = 0.0f;
            }
        }
        else
        {
            for (k = j + 1; k < n; k++)
            {
                sum = 0.0f;
                for (i = 0; i < j; i++)
                {
                    sum += l[j + i * n] * l[k * n + i];
                }
                l[k * n + j] = (a[k * n + j] - sum) / l[j * n + j];
            }
        }
    }
    sum = 0.0f;
    for (k = 0; k < n - 1; k++)
    {
        sum += l[(n - 1) + k * n] * l[(n - 1) * n + k];
    }
    l[(n - 1) * n + (n - 1)] = a[(n - 1) * n + (n - 1)] - sum;
    if (__builtin_fabsf(l[(n - 1) * n + (n - 1)]) < 1e-8f)
    {
        l[(n - 1) * n + (n - 1)] = 0.0f;
    }
}

void SolveFactoredSystem(s32 n, f32* m, f32* b, f32* x)
{
    s32 i;
    s32 k;
    f32 sum;

    for (i = 0; i < n; i++) {
        if (m[i * n + i] == 0.0f) {
            x[i] = 0.0f;
        } else {
            sum = 0.0f;
            for (k = 0; k < i; k++) {
                sum += m[k * n + i] * x[k];
            }
            x[i] = (b[i] - sum) / m[i * n + i];
        }
    }

    for (i = n - 2; i >= 0; i--) {
        if (m[i * n + i] != 0.0f) {
            sum = 0.0f;
            for (k = i + 1; k < n; k++) {
                sum += m[k * n + i] * x[k];
            }
            x[i] -= sum;
        }
    }
}
