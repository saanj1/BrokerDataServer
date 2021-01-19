#include <signal.h>
#include <string.h>
#include <memory>
#include <fstream>
#include <Sockets/TcpClientSocket.hpp>
#include "SocketEventLoop.hpp"

// This is the file which will have all the the broker ip's
// and port details
// format : 198.0.0.1(ip address) 90(port)
#define  BROKER_DATA_IP_LIST_FILE "broker_data_ip_details.txt"

namespace {
  
  std::unique_ptr<BrokerDataServer::SocketEventLoop> server_event_loop;   

  //SIGINT signal handler 
  void onSigInt(int) {
    if (!(server_event_loop)) server_event_loop->StopEvenLoop();
  }


  /**
   * This is the function called from the main program in order 
   * to read the passed string, while the SIGINT is set to control
   * when the program should terminate
   */ 
  int InterruptibleMain(int argc, char *argv[]) {
    if (argc != 2) {
      fprintf(stdout, "Invalid number of arguments, Ex. <Exec> <Port Number>");
      return EXIT_FAILURE;
    }
    std::vector<std::unique_ptr<Sockets::TcpClientSocket>> sockets;
    std::ifstream ifs;
    ifs.open(BROKER_DATA_IP_LIST_FILE, std::ifstream::in);
    std::string line;
    while(std::getline(ifs, line)) {
      char *token_ip = strtok((char*)line.c_str(), "-");
      char *token_port = strtok(NULL, "-"); 
      uint32_t ipaddr  = inet_aton(token_ip, (struct in_addr*)(&ipaddr));
      uint32_t port = atoi(token_port);
      sockets.push_back(std::make_unique<Sockets::TcpClientSocket>());
      if (sockets.back()->Open() && sockets.back()->Connect(ipaddr, port)) {
        return EXIT_FAILURE;
      }
    }
    server_event_loop = std::make_unique<BrokerDataServer::SocketEventLoop>(sockets);

    server_event_loop->RunLive();
    return EXIT_SUCCESS;
  }
}

int main(int argc, char *argv[]) {
  // Catch SIGINT (interrupt signal, typically sent when the user presses
  // <Ctrl>+<C> on the terminal) during program execution.
  const auto prevSigIntHandler = signal(SIGINT, onSigInt);
  const auto returnValue = InterruptibleMain(argc, argv); 
  (void)signal(SIGINT, prevSigIntHandler);
  return returnValue;
}

