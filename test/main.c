#include <stdio.h>

#define FGLIB_IMPLEMENTATION
#include "../fglib.h"

int main() {
  fglib_ctx ctx = fglib_ctx_init(NULL, 0);
  fglib_queue_begin(&ctx);
  
  fglib_action ac;
  _fglib_queue_push(&ctx, &ac);
  _fglib_queue_push(&ctx, &ac);
  _fglib_queue_push(&ctx, &ac);
  _fglib_queue_push(&ctx, &ac);
  _fglib_queue_push(&ctx, &ac);
  _fglib_queue_push(&ctx, &ac);
  _fglib_queue_push(&ctx, &ac);
  _fglib_queue_push(&ctx, &ac);
  _fglib_queue_push(&ctx, &ac);
  _fglib_queue_push(&ctx, &ac);
  
  fglib_queue_commit(&ctx);

  return 0;
}
