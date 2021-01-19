#include "DataProcessor.hpp"

namespace BrokerDataServer {
  DataProcessor::DataProcessor(std::vector<std::unique_ptr<Sockets::TcpClientSocket>> &t_sockets) 
    : _m_buffer_size(1024),
      _m_data_buffer(),
      _m_sockets(t_sockets),
      _m_socket_data_buffer(_m_sockets.size()),
      _m_data_struct(),
      _m_data_decoder(std::make_unique<DataDecoder>(_m_data_struct))
  {}

  void DataProcessor::processEvent(int t_fd_index) {
    size_t read_bytes = _m_sockets[t_fd_index]->ReadN(_m_data_buffer, _m_buffer_size);
    if (read_bytes == -1) {
      perror("socket_read");
      exit(EXIT_FAILURE);
    }

    size_t current_offset = 0;
    if (_m_socket_data_buffer[t_fd_index].second != 0 
      && read_bytes >= sizeof(BrokerDataStruct_t) - _m_socket_data_buffer[t_fd_index].second) {
      std::memcpy(_m_socket_data_buffer[t_fd_index].first + _m_socket_data_buffer[t_fd_index].second, 
                  _m_data_buffer, sizeof(BrokerDataStruct_t) - _m_socket_data_buffer[t_fd_index].second);
      _m_data_decoder->DecodeEvent(_m_socket_data_buffer[t_fd_index].first);
      current_offset += sizeof(BrokerDataStruct_t) - _m_socket_data_buffer[t_fd_index].second;
      read_bytes -= sizeof(BrokerDataStruct_t) - _m_socket_data_buffer[t_fd_index].second;
    }

    while(read_bytes >= sizeof(BrokerDataStruct_t)) {
      _m_data_decoder->DecodeEvent(_m_data_buffer + current_offset);
      current_offset += sizeof(BrokerDataStruct_t);
      read_bytes -=  sizeof(BrokerDataStruct_t);
    }

    if (read_bytes != 0) {
      std::memcpy(_m_socket_data_buffer[t_fd_index].first, _m_data_buffer + current_offset, read_bytes);
    }
    _m_socket_data_buffer[t_fd_index].second = read_bytes;
  }
}
