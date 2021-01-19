#pragma once 
/**
 * @file BrokerDataListener.hpp
 *
 * This file declares BrokerDataServer::BrokerDataListener
 */

#include "Defines.hpp"

namespace BrokerDataServer {
  class BrokerDataListener {
   protected:
    virtual void OnBrokerData(const BrokerDataStruct_t& t_data_) = 0; 
  };
}
