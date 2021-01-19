set(This Sockets)

set(Sources
    include/Sockets/TcpClientSocket.hpp
    src/TcpClientSocket.cpp)
    
add_library(${This} ${Sources})
set_target_properties(${This} PROPERTIES FOLDER Libraries)
target_include_directories(${This} PUBLIC include)