#include <ruby.h>
#include <stdio.h>

#include <zmq.h>

struct rbzmq_ctx {
  void *ctx;
};

static void rbzmq_context_free(void *p) {
  struct rbzmq_ctx *ptr = p;

  int error;
  error = zmq_ctx_term(ptr->ctx);
}

static VALUE rbzmq_context_alloc(VALUE klass) {
  VALUE obj;
  struct rbzmq_ctx *ptr;

  obj = Data_Make_Struct(klass, struct rbzmq_ctx, NULL, rbzmq_context_free, ptr);
  ptr->ctx = NULL;

  return obj;
}

static VALUE rbzmq_context_initialize(VALUE self) {
  struct rbzmq_ctx *ptr;

  Data_Get_Struct(self, struct rbzmq_ctx, ptr);
  ptr->ctx = zmq_ctx_new();

  return self;
}

void Init_rbzmq() {
  VALUE cZMQ;

  cZMQ = rb_const_get(rb_cObject, rb_intern("ZMQ"));

  VALUE cCtx = rb_define_class_under(cZMQ, "Context", rb_cObject);
  rb_define_alloc_func(cCtx, rbzmq_context_alloc);
  rb_define_method(cCtx, "initialize", rbzmq_context_initialize, 0);
}

