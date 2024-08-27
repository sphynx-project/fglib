# fglib

Freestanding Graphics Library

## Idea

fglib provides utility functions for doing simple and advanced graphic functions.

## Usage

*Note: This is just an example on how it will work*

fglib is header only and to include it, initialize it and draw a simple rect (example with limine) simply do it:
```cpp
#include <limine.h>

#define FGLIB_IMPLEMENTATION
#include "fglib.h"

// Get framebuffer, using limine...

void _start() {
  // Pass the framebuffer struct pointer and specify the format. And set the color mode (not specific to framebuffer, only to the users preference).
  fglib_ctx ctx = fglib_ctx_init(framebuffer, FGLIB_FB_FORMAT_LIMINE);
  fglib_set_color_mode(&ctx, FGLIB_COLOR_FORMAT_RGB); // Just RGB and not RGBA (or ARGB) since we wont use alpha.

  // Cord's for a shape is based on the cord that we draw the points. So the fglib_cord's here act like a offset.
  fglib_cord points[4] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
  fglib_shape rect = fglib_shape_init(&ctx, points, 4);

  // Start a "queue"
  fglib_queue_begin(&ctx);

  // Draw a red rect at 0, 0 based on our shape.
  fglib_draw_shape(&ctx, &rect, 0, 0, fglib_color_rgb(255, 0, 0));

  // Finally commit our changes, this draws the things in the "queue". Commit also clears the queue, so we can draw new things.
  fglib_queue_commit(&ctx);

  for(;;);
}
``` 
