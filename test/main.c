#include <stdio.h>

#define FGLIB_IMPLEMENTATION
#include "../fglib.h"

int main()
{
	fglib_ctx ctx = fglib_ctx_init(NULL, 0);
	fglib_set_color_mode(&ctx, FGLIB_COLOR_FORMAT_RGB);

	fglib_queue_begin(&ctx);

	_fglib_type_u32 data[3];
	data[0] = fglib_color_rgb(255, 0, 0);
	data[1] = 0;
	data[2] = 0;

	fglib_action draw;
	draw.kind = FGLIB_ACTION_DRAW_PIXEL;
	draw.data = data;

	_fglib_queue_push(&ctx, &draw);

	printf("(Before commit) Drawing: %s. Actions in queue: %lld\n", ctx.drawing ? "Yes" : "No", ctx.queue.size);
	fglib_queue_commit(&ctx);
	printf("(After commit) Drawing: %s. Actions in queue: %lld\n", ctx.drawing ? "Yes" : "No", ctx.queue.size);
	return 0;
}
