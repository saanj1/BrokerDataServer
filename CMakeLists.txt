cmake_minimum_required(VERSION 3.16)
project(BrokerDataServer
        LANGUAGES C CXX)

set(C_STANDARD 99)
set(CXX_STANDARD 14)

add_subdirectory(Sockets)
add_subdirectory(BrokerDataServer)

