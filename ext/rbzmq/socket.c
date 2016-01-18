#include <ruby.h>

#include <zmq.h>

#include "rbzmq.h"

VALUE get_class(const char *klass) {
  VALUE zmq;
  zmq = rb_const_get(rb_cObject, rb_intern("ZMQ"));

  return rb_const_get(zmq, rb_intern(klass));
}

static void rbzmq_socket_free(void *p) {
  struct rbzmq_socket *ptr = p;

  printf("GC on sock\n");

  if (ptr->socket != NULL) {
    zmq_close(ptr->socket);
  }
}

static VALUE rbzmq_socket_alloc(VALUE klass) {
  VALUE obj;
  struct rbzmq_socket *ptr;

  obj = Data_Make_Struct(klass, struct rbzmq_socket, NULL, rbzmq_socket_free, ptr);
  ptr->socket = NULL;

  return obj;
}

static VALUE rbzmq_socket_initialize(VALUE self, VALUE context, VALUE type) {
  struct rbzmq_context *ptr;
  struct rbzmq_socket *sock_ptr;

  Data_Get_Struct(context, struct rbzmq_context, ptr);
  Data_Get_Struct(self, struct rbzmq_socket, sock_ptr);

  void *socket = zmq_socket(ptr->ctx, type);
  if (!socket) {
    printf("Error: %d\n", errno);
  }
  sock_ptr->socket = socket;
  printf("Sock addr: 0x%08X\n", sock_ptr->socket);

  ptr->socks[0] = self;

  return self;
}

static VALUE rbzmq_socket_close(VALUE self) {
  struct rbzmq_socket *ptr;
  Data_Get_Struct(self, struct rbzmq_socket, ptr);

  int error = zmq_close(ptr->socket);
  ptr->socket = NULL;
  if (error != 0) {
    printf("Error while closing socket: %d\n", errno);
  }

  return self;
}

void init_rbzmq_socket() {
  VALUE cSocket;

  cSocket = get_class("Socket");
  rb_define_alloc_func(cSocket, rbzmq_socket_alloc);
  rb_define_method(cSocket, "initialize", rbzmq_socket_initialize, 2);
  rb_define_method(cSocket, "close", rbzmq_socket_close, 0);
}

