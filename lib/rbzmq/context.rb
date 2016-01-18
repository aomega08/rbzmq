module ZMQ
  class Context
    def get_socket(type)
      @sockets ||= []
      @sockets << Socket.new(self, type)
      @sockets.last
    end
  end
end

