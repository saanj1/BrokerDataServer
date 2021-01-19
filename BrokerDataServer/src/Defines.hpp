#pragma once 
/**
 * This file defines the constants
 * and structs that represents the 
 * broker data
 */

#include <stdint.h>
#include <arpa/inet.h>

namespace BrokerDataServer {
  
  /**
   * This is the format of the data send by
   * the broker servers
   */
  typedef struct {
    uint32_t broker_id;
    uint64_t stock_id;
  } BrokerDataStruct_t;
  
  /**
   * These defines the offset and length of 
   * the data member of the BrokerDataStruct
   */
  #define BROKER_ID_OFFSET 0
  #define BROKER_ID_LENGTH sizeof(uint32_t)
  #define STOCK_ID_OFFSET (BROKER_ID_OFFSET + BROKER_ID_LENGTH)
  #define STOCK_ID_LENGTH sizeof(uint64_t)

  /**
   * This function converts uint64_t network byte order to 
   * host byte order
   *
   * @param[in] t_value
   * 	value represented in network byte order
   *
   * @return 
   * 	value represented in host byte order
   */
  static inline uint64_t ntohll(uint64_t t_value) {
    uint32_t high_part = htonl((uint32_t)(t_value >> 32));
    uint32_t low_part = htonl((uint32_t)(t_value & 0xFFFFFFFFLL));
    return (((uint64_t)low_part) << 32) | high_part;
  }
}
