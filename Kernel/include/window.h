#ifndef __window__H_
#define __window__H_

#include <stdint.h>

typedef struct window * Pwindow;

Pwindow initWindow();

uint8_t inBoundsX(Pwindow window, uint16_t offset);
uint8_t inBoundsY(Pwindow window, uint16_t offset);
uint16_t getHeight(Pwindow window);
uint16_t getWidth(Pwindow window);

uint16_t getX(Pwindow window);
uint16_t getY(Pwindow window);

void setX(Pwindow window, uint16_t x);
void setY(Pwindow window, uint16_t y);


void shiftX(Pwindow window, uint16_t offset);
void setPreviousLine(Pwindow window);

#endif
