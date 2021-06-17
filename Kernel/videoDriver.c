#include <stdint.h>
#include <videoDriver.h>

void draw_pixel(uint16_t x, uint16_t y, uint32_t color) {
	uint8_t * pos = ( uint8_t *) ((uint64_t)(screen->framebuffer + (y * screen->pitch) + x* (int)(screen->bpp/8)));
	pos[0] = B_MASK(color);
	pos[1] = G_MASK(color);
	pos[2] = R_MASK(color);
}
