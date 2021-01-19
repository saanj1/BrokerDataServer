#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <Sockets/TcpClientSocket.hpp>

namespace Sockets {
  TcpClientSocket::TcpClientSocket()
  : _m_socket_descriptor(-1)
  {}
  
  bool TcpClientSocket::Open() {
    _m_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (_m_socket_descriptor == -1) {
      fprintf(stderr, "Failed to create socket: ");
      return false;
    }
    return true;
  }

  bool TcpClientSocket::Connect(uint32_t t_address, uint16_t t_port) {
    struct sockaddr_in socket_address;
    (void)memset(&socket_address, 0, sizeof(socket_address));
    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = htonl(t_address);
    socket_address.sin_port = htons(t_port);
    if (connect(_m_socket_descriptor, 
      (const sockaddr*)&socket_address, sizeof(sockaddr_in)) < 0) {
      fprintf(stderr, "Failed to connect to the server: ");
      return false;
    }
    return true;
  }
  

  void TcpClientSocket::setNonBlocking() {
    if ( fcntl(_m_socket_descriptor, O_NONBLOCK) < 0) {
      fprintf(stderr, "Failed to set socket %d nonblocking",
      _m_socket_descriptor);
    }
  }


  size_t TcpClientSocket::ReadN(char *t_buffer, size_t read_size_) {
    size_t size_read = read(_m_socket_descriptor, t_buffer, read_size_);
    if (size_read < 0 ) {
      fprintf(stderr, "Failed to read the data from %d : ", _m_socket_descriptor);
      return -1;
    }
    return size_read;
  }

  
  void TcpClientSocket::Close() {
    if (_m_socket_descriptor != -1) {
      if (close(_m_socket_descriptor) != 0) {
        fprintf(stderr, "Failed to close the socket %d: ", _m_socket_descriptor);
      }
    }
  }
}
