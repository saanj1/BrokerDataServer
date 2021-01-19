#pragma once 
/**
 * @file SocketEventLoop.hpp
 * 
 * This file declares the class BrokerDataServer::SocketEventLoop
 */

#include <vector>
#include <memory>
#include <sys/epoll.h>
#include "DataProcessor.hpp"
#include <Sockets/TcpClientSocket.hpp>

namespace BrokerDataServer {
  class SocketEventLoop {
  public:
    //Life cycle management
    ~SocketEventLoop() = default;
  public:
    /**
     * This is the constructor 
     *
     * @param[in] t_sockets
     * 		 this is the reference to the vector that 
     * 		 contains all the tcpclientsockets	 
     */ 
    SocketEventLoop(std::vector<std::unique_ptr<Sockets::TcpClientSocket>>& __sockets);

    /**
     * This is the main function, will wait for the 
     * any read events in the given sockets and dispatches
     * the even to the DataProcessor
     */
    void RunLive();

    inline void StopEvenLoop() {
      if (_m_keep_me_running) _m_keep_me_running = false;
    }

  private:
    /**
     * This holds whether SocketEventLoop should 
     * be running or not
     */
    bool _m_keep_me_running;

    /**
     * This holds the pointer to the DataProcessor
     * that process the event from the socket
     */
    std::unique_ptr<DataProcessor> _m_data_processor;

    /**
     * This contains the reference to the vector of
     * client sockets that are connected to the broker 
     * servers 
     */
    std::vector<std::unique_ptr<Sockets::TcpClientSocket>> &_m_sockets; 
  };
}
