#ifndef __CURSOR__H_
#define __CURSOR__H_

#include <stdint.h>

typedef struct cursor * Pcursor;

Pcursor initCursor();

uint16_t getX(Pcursor cursor);
uint16_t getY(Pcursor cursor);

void setX(Pcursor cursor, uint16_t x);
void setY(Pcursor cursor, uint16_t y);

#endif