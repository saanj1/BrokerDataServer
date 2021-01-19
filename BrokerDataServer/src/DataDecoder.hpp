#pragma once 

/**
 * @file DataDecoder.hpp
 *
 * This file declares BrokerDataProcessor::DataDecoder class
 */

#include "Defines.hpp"
#include <arpa/inet.h>

namespace BrokerDataServer {
  class DataDecoder {
   public:
    //Life cycle management
    ~DataDecoder() = default;
   public:
    //This is the constructor
    DataDecoder(BrokerDataStruct_t &t_data_struct)
      : _m_data_struct(t_data_struct)
    {}
   public:
    /**
      * This function decodes the broker data event
      * and fills the _m_data_struct fields
      */
    void DecodeEvent(const char* t_data_buffer) {
      _m_data_struct.broker_id = ntohl((uint32_t)*(t_data_buffer + BROKER_ID_OFFSET));
      _m_data_struct.stock_id = ntohll((uint64_t)*(t_data_buffer + STOCK_ID_OFFSET));
    }
   private:
    BrokerDataStruct_t _m_data_struct;
  };
}
