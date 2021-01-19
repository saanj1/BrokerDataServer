#pragma once 
/**
 * @file DataProcessor.hpp
 * 
 */

#include <memory>
#include <vector>
#include <cstring>
#include "Defines.hpp"
#include "DataDecoder.hpp" 
#include <Sockets/TcpClientSocket.hpp>

namespace BrokerDataServer {
  class DataProcessor {
   public:
    //Life cycle management
    ~DataProcessor() = default;
        
   public:
    //This is default constructor of the class
    DataProcessor(std::vector<std::unique_ptr<Sockets::TcpClientSocket>>&);
    /**
     * This function process events from the file
     * descriptor and 
     */
    void processEvent(int fd);
   private:
    /**
     * This is the size of the tcp data buffer
     */
    size_t _m_buffer_size;

    /**
     * This is the buffer that stores read data 
     * from tcp socket
     */
    char *_m_data_buffer;


    /**
     * This stores the reference to the socket 
     * descriptos vector
     */
    std::vector<std::unique_ptr<Sockets::TcpClientSocket>> &_m_sockets;

    /**
     * This vector stores the the pair of partial data 
     * that's not decoded for the socket and 
     * the size of not remaining bytes.
     */
    std::vector<std::pair<char[sizeof(BrokerDataStruct_t)], int>> _m_socket_data_buffer;

    /**
     * This is structure get filled when 
     * decoder decodes the events
     */
    BrokerDataStruct_t _m_data_struct;

    /**
     * This holds the pointer to the data decoder
     * which decodes the events
     */
    std::unique_ptr<DataDecoder> _m_data_decoder;
  };
}
