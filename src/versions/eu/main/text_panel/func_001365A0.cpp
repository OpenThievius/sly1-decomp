// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the field is at 0x588 (US 0x2FC).
struct Obj_1365A0_eu { u8 pad[0x588]; BaseObject* f2FC; };

void SetTextPanelSubject(Obj_1365A0_eu* self, BaseObject* value) { self->f2FC = value; }
