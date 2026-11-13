// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: calls func_eu_001387C8 where US calls func_001384A0
void ReadBufferedWideString(void* other, void* sub);
void LoadTextPointObject(TextPointObject* self, void* other)
{
    LoadPointObject(self, other);
    ReadBufferedWideString(other, &self->text);
}
