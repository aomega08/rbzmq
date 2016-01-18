#pragma once

void init_rbzmq_context();

struct rbzmq_context {
  void *ctx;
  VALUE socks[256];
};

struct rbzmq_socket {
  void *socket;
};

