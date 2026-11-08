// SPDX-License-Identifier: AGPL-3.0-or-later
// Only in PAL: walks a BSP tree with a point and a margin: down the side the point is on, and when it is within the margin of a plane through both sides, writing a node for the plane into the output list from what each side gave. Returns 0 or 1 when one side holds the point, 2 when it wrote a node.
struct Plane_eu_0013E730 {
    Vec02 n;                // 0x00
    f32 d;                  // 0x10
};
extern TreeNode03 D_eu_002626D0;
extern TreeNode03 D_eu_002626E0;

s32 func_eu_0013E730(TreeNode03* node, Vec02* pos, f32 eps, TreeNode03** out)
{
    f32 dist;
    s32 ret;
    while (node != 0) {
        Plane_eu_0013E730* plane = (Plane_eu_0013E730*)node->face;
        dist = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(*pos), Vu0::Q(plane->n))) - plane->d;
        if (eps < dist) {
            node = node->front;
            continue;
        }
        if (dist < -eps) {
            node = node->back;
            continue;
        }
        s32 b;
        s32 f;
        TreeNode03* bn;
        TreeNode03* fn;
        if (node->back != 0) {
            b = func_eu_0013E730(node->back, pos, eps, out);
            bn = *out - 1;
        } else {
            b = 0;
        }
        if (node->front != 0) {
            f = func_eu_0013E730(node->front, pos, eps, out);
            fn = *out - 1;
        } else {
            f = 1;
        }
        if (b == f && f != 2) {
            ret = f;
            goto done;
        }
        (*out)->face = node->face;
        switch (b) {
        case 0:
            (*out)->back = 0;
            break;
        case 1:
            (*out)->back = &D_eu_002626D0;
            break;
        case 2:
            (*out)->back = bn;
            break;
        }
        switch (f) {
        case 0:
            (*out)->front = &D_eu_002626E0;
            break;
        case 1:
            (*out)->front = 0;
            break;
        case 2:
            (*out)->front = fn;
            break;
        }
        *out += 1;
        ret = 2;
        goto done;
    }
    ret = eps < dist;
done:
    return ret;
}
