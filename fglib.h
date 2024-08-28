/*
   fglib v1.0 - Freestanding Graphics Library - Public Domain or MIT License
   -------------------------------------------------------------------------
   A minimal single-header graphics library designed for freestanding environments.
   To use, simply include this header file:

	   #define FGLIB_IMPLEMENTATION
	   #include "fglib.h"

   Licensing:
	 - You may use this library under the MIT license or as public domain.
	 - Choose whichever license best suits your project needs.

   Implementation:
	 - Define `FGLIB_IMPLEMENTATION` in exactly one source file before including
	   this header to compile the implementation:

	   #define FGLIB_IMPLEMENTATION
	   #include "fglib.h"

   Design:
	 - Written by SphynxOS Developers.
	 - Designed to be minimal with no external dependencies.

   Contributors:
	 - Kevin Alavik: Initial design.
*/

#ifndef FGLIB_H
#define FGLIB_H

// Internal type definitions.
typedef unsigned long long _fglib_type_u64;
typedef unsigned int _fglib_type_u32;
typedef unsigned short _fglib_type_u16;
typedef unsigned char _fglib_type_u8;

typedef long long _fglib_type_i64;
typedef int _fglib_type_i32;
typedef short _fglib_type_i16;
typedef char _fglib_type_i8;

#ifndef NULL
#define NULL (void *)0
#endif

// Forward declaration of the main context structure.
typedef struct fglib_ctx fglib_ctx;

// Constants and internal definitions.
#define FGLIB_MAX_STACK 4096  // Maximum stack size for action queue.
#define FGLIB_MAX_POINTS 4096 // Maximum point count for shapes.

// Shape modes.
#define FGLIB_SHAPE_FILL 0x01
#define FGLIB_SHAPE_OUTLINE 0x02

// Framebuffer formats.
typedef enum fglib_fb_format
{
	FGLIB_FB_FORMAT_FGLIB_CUSTOM = 0x01, // Custom framebuffer format for fglib.
	FGLIB_FB_FORMAT_LIMINE = 0x02		 // Limine framebuffer format.
} fglib_fb_format;

// Framebuffer structure.
typedef struct fglib_framebuffer
{
	_fglib_type_u64 kind;			 // Framebuffer kind identifier.
	_fglib_type_u64 id;				 // Framebuffer ID.
	_fglib_type_u64 address;		 // Base address of the framebuffer.
	_fglib_type_u32 width;			 // Width of the framebuffer in pixels.
	_fglib_type_u32 height;			 // Height of the framebuffer in pixels.
	_fglib_type_u32 pitch;			 // Number of bytes per row (line) in the framebuffer.
	_fglib_type_u16 bpp;			 // Bits per pixel.
	_fglib_type_u8 red_mask_size;	 // Size of the red channel mask.
	_fglib_type_u8 red_mask_shift;	 // Shift for the red channel mask.
	_fglib_type_u8 green_mask_size;	 // Size of the green channel mask.
	_fglib_type_u8 green_mask_shift; // Shift for the green channel mask.
	_fglib_type_u8 blue_mask_size;	 // Size of the blue channel mask.
	_fglib_type_u8 blue_mask_shift;	 // Shift for the blue channel mask.
} fglib_framebuffer;

// Color format enumeration.
typedef enum fglib_color_format
{
	FGLIB_COLOR_FORMAT_RGB = 0x01,	// RGB color format.
	FGLIB_COLOR_FORMAT_RGBA = 0x02, // RGBA color format.
	FGLIB_COLOR_FORMAT_ARGB = 0x03	// ARGB color format.
} fglib_color_format;

// Function to set the color mode for the context.
void fglib_set_color_mode(fglib_ctx *ctx, fglib_color_format mode);

// Action kind enumeration.
typedef enum fglib_action_kind
{
	FGLIB_ACTION_DRAW_PIXEL = 0x01 // Draw pixel action.
} fglib_action_kind;

// Structure representing an action in the queue.
typedef struct fglib_action
{
	fglib_action_kind kind; // Kind of action.
	void *data;				// Associated data.
} fglib_action;

// Action queue structure.
typedef struct fglib_queue
{
	_fglib_type_u64 size;				  // Current size of the queue.
	fglib_action *stack[FGLIB_MAX_STACK]; // Stack of actions.
} fglib_queue;

// Structure representing coordinates for fglib.
typedef struct fglib_cord
{
	int x;
	int y;
} fglib_cord;

// Structure representing a shape.
typedef struct fglib_shape
{
	int mode;							 // Shape mode (e.g., fill or outline).
	int point_count;					 // Ammount of points in the shape.
	fglib_cord points[FGLIB_MAX_POINTS]; // Points defining the shape.
} fglib_shape;

// Main context structure.
typedef struct fglib_ctx
{
	fglib_framebuffer *framebuffer; // Pointer to the framebuffer.
	fglib_color_format color_mode;	// Current color mode.
	fglib_queue queue;				// Action queue.
	int drawing;					// Drawing state flag.
} fglib_ctx;

// Context initialization function.
fglib_ctx fglib_ctx_init(void *framebuffer, fglib_fb_format format);

// Queue management functions.
void fglib_queue_begin(fglib_ctx *ctx);	 // Begin a new drawing queue.
void fglib_queue_commit(fglib_ctx *ctx); // Commit the current drawing queue.

// Internal functions for queue management.
void _fglib_queue_push(fglib_ctx *ctx, fglib_action *action); // Push an action to the queue.
void _fglib_queue_pop(fglib_ctx *ctx);						  // Pop an action from the queue.
void _fglib_queue_clear(fglib_ctx *ctx);					  // Clear the action queue.

// Drawing functions.
fglib_shape fglib_shape_init(fglib_ctx *ctx, fglib_cord *points, int point_count, int mode); // Creates a new shape based on points.
void fglib_draw_shape(fglib_ctx *ctx, fglib_shape *shape, int x, int y, int color);			 // Draws a shape based on args.

// Color functions.
_fglib_type_u32 fglib_color_rgb(_fglib_type_u8 red, _fglib_type_u8 green, _fglib_type_u8 blue);
_fglib_type_u32 fglib_color_rgba(_fglib_type_u8 red, _fglib_type_u8 green, _fglib_type_u8 blue, _fglib_type_u8 alpha);
_fglib_type_u32 fglib_color_argb(_fglib_type_u8 alpha, _fglib_type_u8 red, _fglib_type_u8 green, _fglib_type_u8 blue);

// Internal functions for framebuffer management.
void _fglib_fb_plot(fglib_ctx *ctx, int x, int y, _fglib_type_u32 color);

#ifdef FGLIB_IMPLEMENTATION

// Implementation of the context initialization function.
fglib_ctx fglib_ctx_init(void *framebuffer, fglib_fb_format format)
{
	fglib_ctx ctx;

	switch (format)
	{
	case FGLIB_FB_FORMAT_FGLIB_CUSTOM:
		ctx.framebuffer = (fglib_framebuffer *)framebuffer;
		break;
	default:
		ctx.framebuffer = NULL;
		break;
	}

	ctx.color_mode = FGLIB_COLOR_FORMAT_RGBA; // Default color mode.

	return ctx;
}

// Implementation of the color mode setting function.
void fglib_set_color_mode(fglib_ctx *ctx, fglib_color_format mode)
{
	ctx->color_mode = mode;
}

// Implementation of the queue management functions.
void _fglib_queue_push(fglib_ctx *ctx, fglib_action *action)
{
	ctx->queue.stack[ctx->queue.size++] = action;
}

void _fglib_queue_pop(fglib_ctx *ctx)
{
	if (ctx->queue.size > 0)
	{
		ctx->queue.stack[--ctx->queue.size] = NULL;
	}
}

void _fglib_queue_clear(fglib_ctx *ctx)
{
	while (ctx->queue.size > 0)
	{
		_fglib_queue_pop(ctx);
	}
}

void fglib_queue_begin(fglib_ctx *ctx)
{
	_fglib_queue_clear(ctx);
	ctx->drawing = 1;
}

void fglib_queue_commit(fglib_ctx *ctx)
{
	if (ctx->drawing)
	{
		ctx->drawing = 0;
	}

	if(ctx->framebuffer == NULL) {
		_fglib_queue_clear(ctx);
		return;
	}

	// TODO: Implement drawing logic here.
	for (int i = 0; i < ctx->queue.size; i++)
	{
		fglib_action *action = ctx->queue.stack[ctx->queue.size];

		switch (action->kind)
		{
		case FGLIB_ACTION_DRAW_PIXEL:
			_fglib_type_u32 data[3];
			_fglib_fb_plot(ctx, data[1], data[2], data[0]);
		default:
			break;
		}

		_fglib_queue_pop(ctx);
	}

	_fglib_queue_clear(ctx);
}

// Impelementation of the drawing functions.
fglib_shape fglib_shape_init(fglib_ctx *ctx, fglib_cord *points, int point_count, int mode)
{
	fglib_shape shape;

	for (int i = 0; i < point_count; i++)
	{
		shape.points[i] = points[i];
	}

	shape.point_count = point_count;
	shape.mode = mode;

	return shape;
}

void fglib_draw_shape(fglib_ctx *ctx, fglib_shape *shape, int x, int y, int color)
{
	if (!ctx->drawing)
	{
		return;
	}

	// TODO: Create actions based on shape cords.
}

// Convert RGB values to a uint32 color.
_fglib_type_u32 fglib_color_rgb(_fglib_type_u8 red, _fglib_type_u8 green, _fglib_type_u8 blue)
{
	return (red << 16) | (green << 8) | blue;
}

// Convert RGBA values to a uint32 color.
_fglib_type_u32 fglib_color_rgba(_fglib_type_u8 red, _fglib_type_u8 green, _fglib_type_u8 blue, _fglib_type_u8 alpha)
{
	return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

// Convert ARGB values to a uint32 color.
_fglib_type_u32 fglib_color_argb(_fglib_type_u8 alpha, _fglib_type_u8 red, _fglib_type_u8 green, _fglib_type_u8 blue)
{
	return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

// Framebuffer functions.
void _fglib_fb_plot(fglib_ctx *ctx, int x, int y, _fglib_type_u32 color)
{
	if (!ctx->drawing || ctx->framebuffer == NULL)
	{
		return;
	}

	fglib_framebuffer *framebuffer = ctx->framebuffer;
	_fglib_type_u8 r = (color >> 16) & 0xFF;
	_fglib_type_u8 g = (color >> 8) & 0xFF;
	_fglib_type_u8 b = color & 0xFF;
	_fglib_type_u8 a = (color >> 24) & 0xFF;

	_fglib_type_u32 *pixel = (_fglib_type_u32 *)(framebuffer->address + x * (framebuffer->bpp >> 3) + y * framebuffer->pitch);
	_fglib_type_u32 current_color = *pixel;

	_fglib_type_u8 current_r = (current_color >> 16) & 0xFF;
	_fglib_type_u8 current_g = (current_color >> 8) & 0xFF;
	_fglib_type_u8 current_b = current_color & 0xFF;
	_fglib_type_u8 current_alpha = (current_color >> 24) & 0xFF;

	_fglib_type_u16 final_alpha = current_alpha + ((255 - current_alpha) * a) / 255;

	_fglib_type_u8 final_r = ((r * a) / 255) + ((current_r * current_alpha * (255 - a)) / 255);
	_fglib_type_u8 final_g = ((g * a) / 255) + ((current_g * current_alpha * (255 - a)) / 255);
	_fglib_type_u8 final_b = ((b * a) / 255) + ((current_b * current_alpha * (255 - a)) / 255);

	*pixel = (final_alpha << 24) | (final_r << 16) | (final_g << 8) | final_b;
}

#endif // FGLIB_IMPLEMENTATION

#endif // FGLIB_H

/* MIT License

Copyright (c) 2024 SphynxOS Developers

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. */