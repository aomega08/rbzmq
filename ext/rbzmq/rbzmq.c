#include <ruby.h>
#include <stdio.h>

#include <zmq.h>

#include "rbzmq.h"

static void rbzmq_context_mark(void *p) {
  struct rbzmq_context *ptr = p;
printf("Marking phase on context\n");
//  for (int i = 0; i < 256 && ptr->socks[i]; i++) {
    printf("Marking sock %d\n", 1);
    rb_gc_mark(ptr->socks[0]);
 // }
}

static void rbzmq_context_free(void *p) {
  struct rbzmq_context *ptr = p;

  printf("GC on ctx\n");

  rb_funcall(ptr->socks[0], rb_intern("close"), 0);

  int error;
  error = zmq_ctx_term(ptr->ctx);
}

static VALUE rbzmq_context_alloc(VALUE klass) {
  VALUE obj;
  struct rbzmq_context *ptr;

  obj = Data_Make_Struct(klass, struct rbzmq_context, rbzmq_context_mark, rbzmq_context_free, ptr);
  ptr->ctx = NULL;

  return obj;
}

static VALUE rbzmq_context_initialize(VALUE self) {
  struct rbzmq_context *ptr;

  Data_Get_Struct(self, struct rbzmq_context, ptr);
  ptr->ctx = zmq_ctx_new();

  return self;
}

void Init_rbzmq() {
  VALUE cZMQ;

  cZMQ = rb_const_get(rb_cObject, rb_intern("ZMQ"));

  init_rbzmq_socket();

  VALUE cCtx = rb_define_class_under(cZMQ, "Context", rb_cObject);
  rb_define_alloc_func(cCtx, rbzmq_context_alloc);
  rb_define_method(cCtx, "initialize", rbzmq_context_initialize, 0);
}

