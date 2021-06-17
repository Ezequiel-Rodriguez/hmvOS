#include <window.h>
#include <process.h>
#include <videoDriver.h>
#include <font.h>

typedef struct window {
    uint16_t x;
    uint16_t y;
} Window;

static Window window[AMMOUNT_FDS];

void split(){
	uint16_t mid = screen->width/2;
	for(uint16_t i = mid ; i < mid + 1; i++)
		for(uint16_t j = 0; j < screen->height; j++)
			draw_pixel(i, j, 0xFFFFFF);
}

Pwindow initWindows() {
	split();
    for (int i = 0; i < AMMOUNT_FDS; i++) {
        window[i].x = 0; window[i].y = 0;
    }
    return window;
}

uint8_t inBoundsX(Pwindow window, uint16_t offset) {
    return (window[get_current_process()].x + offset) < ((screen->width/2) - 8);
}

uint8_t inBoundsY(Pwindow window, uint16_t offset) {
    return window[get_current_process()].y + offset < screen->height;
}

uint16_t getHeight(Pwindow window) {
    return screen->height;
}

uint16_t getWidth(Pwindow window) {
    return (screen->width/2) - 8;
}

uint16_t getX(Pwindow window) {
    return window[get_current_process()].x + ((get_current_process() == 1) ? (screen->width/2) + 2: 0);
}

uint16_t getY(Pwindow window) {
    return window[get_current_process()].y + ((get_current_process() == 1)? 0 : 0);
}

void setX(Pwindow window, uint16_t x) {
    window[get_current_process()].x = x;
}

void setY(Pwindow window, uint16_t y){
    window[get_current_process()].y = y;
}

void shiftX(Pwindow window, uint16_t offset) {
    window[get_current_process()].x += offset;
}


void setPreviousLine(Pwindow window) {
	setY(window, getY(window) - CHAR_HEIGHT);
    setX(window, (get_current_process == 1 ? ((screen->width/2) + 2) : 0) + getWidth(window) - CHAR_WIDTH);
}
