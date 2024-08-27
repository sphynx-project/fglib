/* fglib v1.0 - Freestanding Graphic Library - public domain or MIT license
   This is a single-header graphics library designed for freestanding environments.
   To use, simply include this header file:

       #define FGLIB_IMPLEMENTATION
       #include "fglib.h"

   You can freely use this library in your projects either under the MIT license or
   as public domain. Simply choose whichever suits your project best.

   Optionally, define `FGLIB_IMPLEMENTATION` in exactly one source file to create the
   implementation:

       #define FGLIB_IMPLEMENTATION
       #include "fglib.h"

   Written by SphynxOS Developers. This library is designed to be minimal, requiring
   no external dependencies.

   Contributors:
     - Kevin Alavik: Initial design.
*/

#ifndef FGLIB_H
#define FGLIB_H

// Internal types.
typedef unsigned long long      _fglib_type_u64;
typedef unsigned int            _fglib_type_u32;
typedef unsigned short          _fglib_type_u16;
typedef unsigned char           _fglib_type_u8;
typedef long long               _fglib_type_i64;
typedef int                     _fglib_type_i32;
typedef short                   _fglib_type_i16;
typedef char                    _fglib_type_i8;

// fglib framebuffer formats and struct.
#define FGLIB_FB_FORMAT_FGLIB_CUSTOM    0x01
#define FGLIB_FB_FORMAT_LIMINE          0x02

typedef struct fglib_framebuffer
{
    _fglib_type_u64 kind;
    _fglib_type_u64 id;
    _fglib_type_u64 address;
    _fglib_type_u32 width;
    _fglib_type_u32 height;
    _fglib_type_u32 pitch;
    _fglib_type_u16 bpp;
    _fglib_type_u8  red_mask_size;
    _fglib_type_u8  red_mask_shift;
    _fglib_type_u8  green_mask_size;
    _fglib_type_u8  green_mask_shift;
    _fglib_type_u8  blue_mask_size;
    _fglib_type_u8  blue_mask_shift;
} fglib_framebuffer;


// fglib context struct to store necessary info.
typedef struct fglib_ctx {
  fglib_framebuffer framebuffer;
} fglib_ctx;

// Function to construct the context.
fglib_ctx fglib_ctx_init(void* framebuffer, int format);

#ifdef FGLIB_IMPLEMENTATION

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
