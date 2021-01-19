set(This BrokerDataServer)

set(Header
    src/Defines.hpp
    src/SocketEventLoop.hpp
    src/DataProcessor.hpp
    src/DataDecoder.hpp)


set(Sources
    src/SocketEventLoop.cpp
    src/DataProcessor.cpp
    src/BrokerDataServer.cpp)


add_executable(${This} ${Headers} ${Sources})

target_link_libraries(${This} Sockets)