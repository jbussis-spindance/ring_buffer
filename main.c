
#include "ring_buffer.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>


void test_normal_function(void) {
    StringSpan str;
    int err;
    RingBuffer rb;
    ring_buffer_create(&rb, 6, true);

    memcpy(str.value, "Hello", MAX_STRING_LEN);
    str.length = sizeof("Hello") - 1;
    err = ring_buffer_write(&rb, &str);
    assert(err == 0 && "There was an error writing data.");

    memcpy(str.value, "World", MAX_STRING_LEN);
    str.length = sizeof("World") - 1;
    err = ring_buffer_write(&rb, &str);
    assert(err == 0 && "There was an error writing data.");

    memcpy(str.value, "!", MAX_STRING_LEN);
    str.length = sizeof("!") - 1;
    err = ring_buffer_write(&rb, &str);
    assert(err == 0 && "There was an error writing data.");

    err = ring_buffer_read(&rb, &str);
    assert(err == 0 &&  "Could not read any data");
    assert(0 == strncmp(str.value, "Hello", 4));
    
    err = ring_buffer_read(&rb, &str);
    assert(err == 0 &&  "Could not read any data");
    assert(0 == strncmp(str.value, "World", 5));

    err = ring_buffer_read(&rb, &str);
    assert(err == 0 &&  "Could not read any data");
    assert(0 == strncmp(str.value, "!", 1));
}

void test_overwrite_values(void) {
    StringSpan str;
    int err;
    RingBuffer rb;
    ring_buffer_create(&rb, 3, true);

    // write 4 values, then when we read a value, it should be 
    // the fourth value that we wrote
    memcpy(str.value, "First", MAX_STRING_LEN);
    str.length = sizeof("First") - 1;
    err = ring_buffer_write(&rb, &str);
    assert(err == 0 && "There was an error writing data.");

    memcpy(str.value, "Second", MAX_STRING_LEN);
    str.length = sizeof("Second") - 1;
    err = ring_buffer_write(&rb, &str);
    assert(err == 0 && "There was an error writing data.");

    memcpy(str.value, "Third", MAX_STRING_LEN);
    str.length = sizeof("Third") - 1;
    err = ring_buffer_write(&rb, &str);
    assert(err == 0 && "There was an error writing data.");

    memcpy(str.value, "Fourth", MAX_STRING_LEN);
    str.length = sizeof("Fourth") - 1;
    err = ring_buffer_write(&rb, &str);
    assert(err == 0 && "There was an error writing data.");

    err = ring_buffer_read(&rb, &str);
    assert(err == 0 &&  "Could not read any data");
    assert(0 == strncmp(str.value, "Fourth", 6));
}

void test_no_overwrite_values(void) {
    StringSpan str;
    int err;
    RingBuffer rb;
    ring_buffer_create(&rb, 3, false);

    // write 4 values, then when we read a value, it should be 
    // the fourth value that we wrote
    memcpy(str.value, "First", MAX_STRING_LEN);
    str.length = sizeof("First") - 1;
    err = ring_buffer_write(&rb, &str);
    assert(err == 0 && "There was an error writing data.");

    memcpy(str.value, "Second", MAX_STRING_LEN);
    str.length = sizeof("Second") - 1;
    err = ring_buffer_write(&rb, &str);
    assert(err == 0 && "There was an error writing data.");

    memcpy(str.value, "Third", MAX_STRING_LEN);
    str.length = sizeof("Third") - 1;
    err = ring_buffer_write(&rb, &str);
    assert(err == 0 && "There was an error writing data.");

    memcpy(str.value, "Fourth", MAX_STRING_LEN);
    str.length = sizeof("Fourth") - 1;
    err = ring_buffer_write(&rb, &str);
    assert(err == -1 && "It did not correctly indicate and error");

    err = ring_buffer_read(&rb, &str);
    assert(err == 0 &&  "Could not read any data");
    assert(0 == strncmp(str.value, "First", 5));
}

void test_no_data_to_read(void) {
    StringSpan str;
    int err;
    RingBuffer rb;
    ring_buffer_create(&rb, 6, true);

    memcpy(str.value, "Hello", MAX_STRING_LEN);
    str.length = sizeof("Hello") - 1;
    err = ring_buffer_write(&rb, &str);
    assert(err == 0 && "There was an error writing data.");

    err = ring_buffer_read(&rb, &str);
    assert(err == 0 &&  "Could not read any data");
    assert(0 == strncmp(str.value, "Hello", 4));

    err = ring_buffer_read(&rb, &str);
    assert(err == -1 &&  "Was able to read data, but should not have been able to.");
}


int main(void) {
    printf("Testing Overwrite Ring Buffer...\n");

    printf(" 0 - Normal behavior\n");
    test_normal_function();
    printf(" 1 - Overwrite data\n");
    test_overwrite_values();
    printf(" 2 - No overwrite data\n");
    test_no_overwrite_values();
    printf(" 3 - No data to read\n");
    test_no_data_to_read();
    printf("Done testing!\n");

    RingBuffer rb;
    printf("\nSize of a RingBuffer struct: %zu\n", sizeof(rb));
    
    return 0;
}