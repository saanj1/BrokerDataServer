#include "SocketEventLoop.hpp"

#define MAX_EVENTS  5

namespace BrokerDataServer {

  SocketEventLoop::SocketEventLoop(std::vector<std::unique_ptr<Sockets::TcpClientSocket>>& t_sockets)
  : _m_keep_me_running(true),
    _m_sockets(t_sockets)
  {}

  void SocketEventLoop::RunLive() {
    int epoll_fd = epoll_create1(0);
    if( epoll_fd == -1) {
      perror("epoll_create1");
      exit(EXIT_FAILURE);
    }
    struct epoll_event ev, events[MAX_EVENTS];
  
    for(uint32_t t_i = 0; t_i < _m_sockets.size(); t_i++) {
      ev.events = EPOLLIN;
      ev.data.fd = t_i;

      if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, _m_sockets[t_i]->SocketDescriptor(), &ev)) {
        perror("epoll_ctl");
        exit(EXIT_FAILURE);
      }
    }

    while(_m_keep_me_running) {
      int nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, 500);
      if (nfds == -1) {
        perror("epoll_wait");
        exit(EXIT_FAILURE);
      }

      for(int t_fd = 0; t_fd < nfds; ++t_fd) {
        _m_data_processor->processEvent(events[t_fd].data.fd);
      }
    }
  }
}
