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

  printf("(Before commit) Drawing: %s. Actions in queue: %lld\n", ctx.drawing ? "Yes" : "No", ctx.queue.size);  
  fglib_queue_commit(&ctx);
  printf("(After commit) Drawing: %s. Actions in queue: %lld\n", ctx.drawing ? "Yes" : "No", ctx.queue.size);
  return 0;
}
