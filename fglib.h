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

// Check architecture and define internal types accordingly.
#if defined(__x86_64__) || defined(_M_X64) || defined(__aarch64__) || defined(__PPC64__)
    // 64-bit architecture
    typedef unsigned long long  _fglib_type_u64; // 64-bit unsigned integer
    typedef unsigned int        _fglib_type_u32; // 32-bit unsigned integer
    typedef unsigned short      _fglib_type_u16; // 16-bit unsigned integer
    typedef unsigned char       _fglib_type_u8;  // 8-bit unsigned integer

    typedef long long           _fglib_type_i64; // 64-bit signed integer
    typedef int                 _fglib_type_i32; // 32-bit signed integer
    typedef short               _fglib_type_i16; // 16-bit signed integer
    typedef char                _fglib_type_i8;  // 8-bit signed integer
#elif defined(__i386__) || defined(_M_IX86) || defined(__arm__) || defined(__PPC__)
    // 32-bit architecture
    typedef unsigned long       _fglib_type_u64; // 64-bit unsigned integer
    typedef unsigned int        _fglib_type_u32; // 32-bit unsigned integer
    typedef unsigned short      _fglib_type_u16; // 16-bit unsigned integer
    typedef unsigned char       _fglib_type_u8;  // 8-bit unsigned integer

    typedef long                _fglib_type_i64; // 64-bit signed integer
    typedef int                 _fglib_type_i32; // 32-bit signed integer
    typedef short               _fglib_type_i16; // 16-bit signed integer
    typedef char                _fglib_type_i8;  // 8-bit signed integer
#else
    #error "Unsupported architecture"
#endif

#ifndef NULL
#define NULL (void *)0
#endif

// Forward declaration of the main context structure.
typedef struct fglib_ctx fglib_ctx;

// Constants and internal definitions.
#define FGLIB_MAX_STACK    4096 // Maximum stack size for action queue.
#define FGLIB_MAX_POINTS   4096 // Maximum point count for shapes.

// Shape modes.
#define FGLIB_SHAPE_FILL    0x01
#define FGLIB_SHAPE_OUTLINE 0x02

// Framebuffer formats.
typedef enum fglib_fb_format
{
    FGLIB_FB_FORMAT_FGLIB_CUSTOM = 0x01, // Custom framebuffer format for fglib.
    FGLIB_FB_FORMAT_LIMINE       = 0x02  // Limine framebuffer format.
} fglib_fb_format;

// Framebuffer structure.
typedef struct fglib_framebuffer
{
    _fglib_type_u64 kind;             // Framebuffer kind identifier.
    _fglib_type_u64 address;          // Base address of the framebuffer.
    _fglib_type_u32 width;            // Width of the framebuffer in pixels.
    _fglib_type_u32 height;           // Height of the framebuffer in pixels.
    _fglib_type_u32 pitch;            // Number of bytes per row (line) in the framebuffer.
    _fglib_type_u16 bpp;              // Bits per pixel.
    _fglib_type_u8  red_mask_size;    // Size of the red channel mask.
    _fglib_type_u8  red_mask_shift;   // Shift for the red channel mask.
    _fglib_type_u8  green_mask_size;  // Size of the green channel mask.
    _fglib_type_u8  green_mask_shift; // Shift for the green channel mask.
    _fglib_type_u8  blue_mask_size;   // Size of the blue channel mask.
    _fglib_type_u8  blue_mask_shift;  // Shift for the blue channel mask.
} fglib_framebuffer;

// Color format enumeration.
typedef enum fglib_color_format
{
    FGLIB_COLOR_FORMAT_RGB  = 0x01,   // RGB color format.
    FGLIB_COLOR_FORMAT_RGBA = 0x02,   // RGBA color format.
    FGLIB_COLOR_FORMAT_ARGB = 0x03    // ARGB color format.
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
    void              *data; // Associated data.
} fglib_action;

// Action queue structure.
typedef struct fglib_queue
{
    _fglib_type_u64 size;                     // Current size of the queue.
    fglib_action    *stack[FGLIB_MAX_STACK];  // Stack of actions.
} fglib_queue;

// Structure representing coordinates for fglib.
typedef struct fglib_cord
{
    int x; // X coordinate.
    int y; // Y coordinate.
} fglib_cord;

// Structure representing a shape.
typedef struct fglib_shape
{
    int         mode;                          // Shape mode (e.g., fill or outline).
    int         point_count;                   // Amount of points in the shape.
    fglib_cord  points[FGLIB_MAX_POINTS];      // Points defining the shape.
} fglib_shape;

// Main context structure.
typedef struct fglib_ctx
{
    fglib_framebuffer  *framebuffer;           // Pointer to the framebuffer.
    fglib_color_format color_mode;             // Current color mode.
    fglib_queue        queue;                  // Action queue.
    int                drawing;                // Drawing state flag.
} fglib_ctx;

// Context initialization function.
fglib_ctx fglib_ctx_init(void *framebuffer, fglib_fb_format format);

// Queue management functions.
void fglib_queue_begin(fglib_ctx *ctx);        // Begin a new drawing queue.
void fglib_queue_commit(fglib_ctx *ctx);       // Commit the current drawing queue.

// Internal functions for queue management.
void _fglib_queue_push(fglib_ctx *ctx, fglib_action *action); // Push an action to the queue.
void _fglib_queue_pop(fglib_ctx *ctx);                        // Pop an action from the queue.
void _fglib_queue_clear(fglib_ctx *ctx);                      // Clear the action queue.

// Drawing functions.
fglib_shape fglib_shape_init(fglib_ctx *ctx, fglib_cord *points, int point_count, int mode); // Creates a new shape based on points.
void fglib_draw_shape(fglib_ctx *ctx, fglib_shape *shape, int x, int y, int color);          // Draws a shape based on args.

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
        ctx->queue.size--;
}

void _fglib_queue_clear(fglib_ctx *ctx)
{
    ctx->queue.size = 0;
}

void fglib_queue_begin(fglib_ctx *ctx)
{
    ctx->drawing = 1;
}

void fglib_queue_commit(fglib_ctx *ctx)
{
    if (!ctx->drawing)
        return;

    for (_fglib_type_u64 i = 0; i < ctx->queue.size; i++)
    {
        fglib_action *action = ctx->queue.stack[i];
        switch (action->kind)
        {
        case FGLIB_ACTION_DRAW_PIXEL:
            // ToDo: Implement the draw pixel action.
            break;
        }
    }

    _fglib_queue_clear(ctx);
    ctx->drawing = 0;
}

// Implementation of the color functions.
_fglib_type_u32 fglib_color_rgb(_fglib_type_u8 red, _fglib_type_u8 green, _fglib_type_u8 blue)
{
    return (red << 16) | (green << 8) | blue;
}

_fglib_type_u32 fglib_color_rgba(_fglib_type_u8 red, _fglib_type_u8 green, _fglib_type_u8 blue, _fglib_type_u8 alpha)
{
    return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

_fglib_type_u32 fglib_color_argb(_fglib_type_u8 alpha, _fglib_type_u8 red, _fglib_type_u8 green, _fglib_type_u8 blue)
{
    return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

// Implementation of the framebuffer plotting function.
void _fglib_fb_plot(fglib_ctx *ctx, int x, int y, _fglib_type_u32 color)
{
    if (!ctx->framebuffer)
        return;

    _fglib_type_u8 *fb = (_fglib_type_u8 *)ctx->framebuffer->address;
    _fglib_type_u32 offset;

	switch(ctx->framebuffer->kind)
	{
		case FGLIB_FB_FORMAT_FGLIB_CUSTOM:
		case FGLIB_FB_FORMAT_LIMINE:
			offset = (y * ctx->framebuffer->pitch) + (x * (ctx->framebuffer->bpp / 8));
			break;
		default:
			offset = y * ctx->framebuffer->width + x;
			break;
	}
   
    // Plot the pixel based on the color mode.
    switch (ctx->color_mode)
    {
    case FGLIB_COLOR_FORMAT_RGB:
        fb[offset]     = (color >> 16) & 0xFF; // Red.
        fb[offset + 1] = (color >> 8) & 0xFF;  // Green.
        fb[offset + 2] = color & 0xFF;         // Blue.
        break;
    case FGLIB_COLOR_FORMAT_RGBA:
        fb[offset]     = (color >> 24) & 0xFF; // Alpha.
        fb[offset + 1] = (color >> 16) & 0xFF; // Red.
        fb[offset + 2] = (color >> 8) & 0xFF;  // Green.
        fb[offset + 3] = color & 0xFF;         // Blue.
        break;
    case FGLIB_COLOR_FORMAT_ARGB:
        fb[offset]     = (color >> 16) & 0xFF; // Red.
        fb[offset + 1] = (color >> 8) & 0xFF;  // Green.
        fb[offset + 2] = color & 0xFF;         // Blue.
        fb[offset + 3] = (color >> 24) & 0xFF; // Alpha.
        break;
    default:
        break;
    }
}

#endif // FGLIB_IMPLEMENTATION

#endif // FGLIB_H
