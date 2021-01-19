#pragma once 
/**
 * @file DataAggregator.hpp
 * 
 * This file define class BrokerDataAggregator
 */

#include "BrokerDataListener.hpp" 

namespace BrokerDataServer {
  class DataAggregator : public BrokerDataListener {
   public:
    //Life cycle management
    ~DataAggregator() = default;
   public:
    DataAggregator() = default;
   
   protected:
    virtual void OnBrokerData(const BrokerDataStruct_t& t_data_) override;
   private:      
  };
}