#include "ring_buffer.h"

#include <string.h>

int ring_buffer_create(RingBuffer *rb, uint32_t capacity, bool overwrite_allowed) {
    rb->overwrite_allowed = overwrite_allowed;
    rb->head = 0;
    rb->tail = 0;
    rb->capacity = capacity;
    rb->count = 0;
    // start with the strings cleared out
    for (uint_fast32_t i = 0; i < RING_BUFFER_CAPACITY; ++i) {
        memset(rb->data[i].value, 0, MAX_STRING_LEN);
    }
    return 0;
}

int ring_buffer_write(RingBuffer *rb, StringSpan *data) {
    if (data == NULL) {
        return -1;
    }
    // if the ring buffer has reached capacity, return an error
    if (!rb->overwrite_allowed && rb->count >= rb->capacity) {
        return -1;
    }
    // copy the data to the ring buffer
    memset(rb->data[rb->head].value, 0, MAX_STRING_LEN);
    memcpy(rb->data[rb->head].value, data->value, MAX_STRING_LEN);
    rb->data[rb->head].length = data->length;
    // record the count and move the head to the nexrt position
    if (rb->count < rb->capacity) {
        rb->count++;
    }
    rb->head = (rb->head + 1) % rb->capacity;
    return 0;
}

int ring_buffer_read(RingBuffer *rb, StringSpan *out_data) {
    if (out_data == NULL) {
        return -1;
    }
    // if there's nothing to read, return error
    // TODO change this to something else as it's not really an error
    if (rb->count == 0) {
        return -1;
    }
    // copy the data from the ring buffer into the out data
    memcpy(out_data->value, rb->data[rb->tail].value, MAX_STRING_LEN);
    out_data->length = rb->data[rb->tail].length;
    memset(rb->data[rb->tail].value, 0, MAX_STRING_LEN);
    rb->data[rb->tail].length = 0;
    // update the ring buffer's count and move the tail to the next position
    if (rb->count > 0) {
        rb->count--;
    }
    rb->tail = (rb->tail + 1) % rb->capacity;
    return 0;
}