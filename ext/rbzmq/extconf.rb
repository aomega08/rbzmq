require 'mkmf'

abort 'missing zmq lib' unless have_library('zmq')
abort 'missing zmq header' unless have_header('zmq.h')

create_makefile('rbzmq/rbzmq')

