#pragma once 
/**
 * @file TcpClientSocket.hpp
 * 
 * This file declare Sockets::TcpClientSocket class
 */

#define SNJ_MAKE_NONCOPYABLE(c)\
private:                       \
  c(const c&) noexcept = delete;\
  c& operator=(const c&) noexcept = delete

#define SNJ_MAKE_NONMOVABLE(c)\
private:                      \
  c(c&&) noexcept = delete;   \
  c& operator=(c&&) noexcept = delete


#include <memory>
#include <sys/socket.h>
namespace Sockets {
  class TcpClientSocket {
   public:
    //Life cycle functions
    ~TcpClientSocket() = default;
    SNJ_MAKE_NONCOPYABLE(TcpClientSocket);
    SNJ_MAKE_NONMOVABLE(TcpClientSocket);

   public:
    //This is the constructor
    TcpClientSocket();
    
    /**
     * This function is used to bind the port number 
     * to the socket
     */
    bool Open(); 

    /**
     * This function is used to connect the client 
     * socket to the server socket
     * 
     * @param[in] t_address 
     *  address of the server to connect
     * 
     * @param[in] t_port 
     *  port number of the process on the 
     *  server to connect
     *
     * @return 
     *  boolean value indicating whether connectin
     *  to the server was sucessfull or not
     */
    bool Connect(uint32_t t_address, uint16_t t_port);

    /**
     * This function returns the socket descriptor
     *
     * @return
     *  socket descriptor integer value
     */
    inline int SocketDescriptor() {
      return _m_socket_descriptor;
    }
     
    /**
     * This function is used to set the socket 
     * to be non-blocking
     */
    void setNonBlocking();

    /**
     * This function reads the data from the socket 
     * and copy that to buffer.
     * 
     * @param[in] t_buffer 
     *  pointer to the buffer where the read 
     *  data to be copied
     * 
     * @param[in] t_read_size
     *  amount of bytes to be read from the socket
     * 
     * @return retval
     *  actual number of bytes read from the buffer
     */
    size_t ReadN(char *t_buffer, size_t t_read_size); 


    /**
     * This function closes opened socket
     */
    void Close();

  private:
    /**
     * This holds socket descriptor, when the socket 
     * is opened
     */
     int _m_socket_descriptor;
  };
}
