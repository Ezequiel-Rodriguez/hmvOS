#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <stdint.h>
#include <stddef.h>

#define BUFFER_LENGTH 256
typedef uint8_t BufferPtr;

static uint8_t buffer[BUFFER_LENGTH]={0};
static BufferPtr w_pointer = 0, r_pointer = 0;

uint8_t kbRead();
void keyboard_handler();

long copy_from_buffer(char * buf, size_t count);

#endif
