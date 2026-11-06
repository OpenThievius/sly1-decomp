// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: pulls data from the ring buffer into the decoder and reports 0 (wait), 1 (more) or 2 (done).
struct Buffer_18F890_eu { u8 pad00[0x18]; s32 head; s32 base; s32 tail; s32 fEnd; };
struct Object_18F890_eu {
    u8 pad00[0x0C];
    Buffer_18F890_eu* buffer;
    u8 pad10[0x70 - 0x10];
    s32 f70;
    u8 pad74[0xE0 - 0x74];
    s32 fE0;
};
void func_00130070(StreamReaderWindow*);

s32 func_0018F890(Object_18F890* self_, s32 wait)
{
    Object_18F890_eu* self = (Object_18F890_eu*)self_;
    s32 count = self->buffer->head - self->buffer->tail;
    while (count == 0) {
        if (self->buffer->fEnd == 0) return 2;
        PumpStreamReader((StreamReaderWindow*)self->buffer);
        count = self->buffer->head - self->buffer->tail;
        if (count == 0 && !wait) return 0;
    }
    func_001F6C20(0);
    Buffer_18F890_eu* buffer = self->buffer;
    s32 result = func_0020A518(self->pad10, buffer->base + buffer->tail, count);
    ConsumeStreamBytes((StreamReaderWindow*)self->buffer, result);
    if (result != 0) return 0;
    if (self->f70 >= count) {
        if (self->fE0 >= count) return 2;
    }
    return 1;
}
