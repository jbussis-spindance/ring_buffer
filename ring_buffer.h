/**
 * @file ringbuffer.h
 * @author Joshua Bussis (joshua.bussis@spindance.com)
 * @brief   An implementation of a string ring buffer that 
 *          does not rely on dynamic memory allocation.
 * @version 0.1
 * @date 2023-03-13
 */

#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_

#include <inttypes.h>
#include <stdbool.h>

#define MAX_STRING_LEN 32
#define RING_BUFFER_CAPACITY 16

typedef struct {
    char value[MAX_STRING_LEN];
    uint32_t length; // length of string (not including NULL termination)
} StringSpan;

typedef struct RingBuffer {
    bool overwrite_allowed;
    uint32_t head;
    uint32_t tail;
    uint32_t capacity;
    uint32_t count;
    StringSpan data[RING_BUFFER_CAPACITY];
} RingBuffer;

/**
 * @brief   Create a new RingBuffer
 * 
 * @param   overwrite_allowed Whether or not overwritting data is allowed
 * @param   capacity The total capacity of the RingBuffer
 * @return  int 0 on success, -1 on failure
 */
int ring_buffer_create(RingBuffer *rb, uint32_t capacity, bool overwrite_allowed);

/**
 * @brief   Write data to the RingBuffer
 * 
 * @param   rb The RingBuffer to push to 
 * @param   data The data to write
 * @return  int 0 on success, -1 on failure
 */
int ring_buffer_write(RingBuffer *rb, StringSpan *data);

/**
 * @brief   Read data from the RingBuffer
 * @param   rb The RingBuffer to read from 
 * @param   out_data The data that is read
 * @return  0 on success, -1 on failure
 */
int ring_buffer_read(RingBuffer *rb, StringSpan *out_data);


#endif /* RING_BUFFER_H_ */
