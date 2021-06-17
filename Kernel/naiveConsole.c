#include <naiveConsole.h>
#include <font.h>
#include <videoDriver.h>
#include <window.h>
#include <process.h>

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);
static void scrollUp();
static int numlen(uint64_t val);

static char buffer[128] = { '0' };
static Pwindow window;

void initScreen(void) {
	window = initWindows();
}

void ncPrint(const char * string) {
	for (int i = 0; string[i] != 0; i++)
		ncPrintChar(string[i]);
}

void ncPrintAtt(const char * string, uint32_t frontColor, uint32_t backColor) {
	for (int i = 0; string[i] != 0; i++)
		ncPrintCharAtt(string[i], frontColor, backColor);
}

void ncPrintChar(char character) {
	ncPrintCharAtt(character, WHITE, BLACK);
}

void ncPrintCharAtt(char character, uint32_t frontColor, uint32_t backColor) {
	if (!inBoundsX(window, 0)) {
	 	setX(window, 0);
	 	if (!inBoundsY(window, CHAR_HEIGHT)) {
	 		scrollUp();
		} else {
	 		uint16_t y = getY(window);
	 		setY(window, y + CHAR_HEIGHT);
	 	}
	 }

	uint8_t * letter = getCharMapping(character);
	for(int i = 0; i < CHAR_HEIGHT; i++) {
		for(int j = 0; j < CHAR_WIDTH; j++) {
			if(letter[i] & (1 << j))
				draw_pixel(CHAR_WIDTH - 1 - j + getX(window), i + getY(window), frontColor);
			else
				draw_pixel(CHAR_WIDTH - 1 - j + getX(window), i + getY(window), backColor);
		}
	}
	shiftX(window, CHAR_WIDTH);
}

void cpyPixel(int x_dst, int y_dst, int x_src, int y_src) {
	uint8_t * from = (uint8_t *) ((uint64_t)(screen->framebuffer + screen->pitch *y_src + x_src* (int)(screen->bpp/8)));
	uint8_t * to = (uint8_t *) ((uint64_t)(screen->framebuffer + screen->pitch *y_dst + x_dst* (int)(screen->bpp/8)));
	to[0] = from[0];
	to[1] = from[1];
	to[2] = from[2];
}

void scrollUp() {
	int x = get_current_process() == 0 ? 0 : getWidth(window) + 9;
	for (int j = 0; j < getHeight(window) ; j++ ) {
		for(int i = x; i <= x + getWidth(window) ; i++) {
			cpyPixel(i, j, i, j + CHAR_HEIGHT);
		}
	}
	for(int i = x; i < x + getWidth(window); i++) {
		for(int j = getHeight(window) - CHAR_HEIGHT; j < getHeight(window); j++) {
			draw_pixel(i, j, BLACK);
		}
	}
}

void ncNewline() {
	do {
		for(int i = 0; i < CHAR_HEIGHT; i++) {
			for(int j = 0; j < CHAR_WIDTH; j++) {
					draw_pixel(CHAR_WIDTH - 1 - j + getX(window), i + getY(window), BLACK);
			}
		}
		setX(window, getX(window) + CHAR_WIDTH);
	} while(inBoundsX(window, 0));
	
	setX(window, 0);
	if (!inBoundsY(window, CHAR_HEIGHT)) {
	 	scrollUp();
	} else {
		uint16_t y = getY(window);
		setY(window, y + CHAR_HEIGHT);
	}
}

void ncPrintDec(uint64_t value) {
	ncPrintBase(value, 10);
}

void ncPrintHex(uint64_t value) {
	ncPrintBase(value, 16);
}

void ncPrintBin(uint64_t value) {
	ncPrintBase(value, 2);
}

void ncPrintBase(uint64_t value, uint32_t base) {
    uintToBase(value, buffer, base);
    ncPrint(buffer);
}

void ncClear() {
	for (int i = 0; i < getHeight(window); i++) {
		for (int j = 0; j < getWidth(window); j++) {
			draw_pixel(i, j, BLACK);
		}
	}
	setX(window, 0);
	setY(window, 0);
}

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base) {
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do {
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	} while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2) {
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}

void ncPrintReg(uint64_t reg) {
	ncPrint("0x");
	uint8_t len = numlen(reg);
	for(int i = 0; i < 16 - len; i++) {
		ncPrintChar('0');
	}
	ncPrintHex(reg);
}

static int numlen(uint64_t val) {
	int len = 0;
	while(val != 0) {
		len++;
		val /= 16;
	}
	return len + (len == 0);
}

void ncErase(uint32_t amount) {
	for (uint32_t c = 0; c < amount; c++) {
		if (inBoundsX(window, getWidth(window) - 1)) {
			if (!inBoundsY(window, getHeight(window) - 1)) {
				setPreviousLine(window);
			} else {
				return;
			}
		} else {
			shiftX(window, -CHAR_WIDTH);
		}
		for (uint16_t x = getX(window); x < getX(window) + CHAR_WIDTH ; x++) {
			for (uint16_t y = getY(window); y < getY(window) + CHAR_HEIGHT; y++){
				draw_pixel(x, y, BLACK);
			}
		}
	}
}