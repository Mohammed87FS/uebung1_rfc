#include <iostream>

#include "Communication.h"

void server(unsigned short port);
void client(const char *hostname, unsigned short port);

/**
 * Main function: decides whether to start a server or a client based on command line arguments.
 * If a client name is provided, it starts the client; otherwise, it starts the server.
 * Just for testing purposes. Server and client have their own main() functions in Server.cpp and Client.cpp, respectively.
 */
void main(int argc, char *argv[])
{
  unsigned short serverPort = 8000;
  const char *clientname = nullptr;


  /**
   * Kommandozeile: Network.exe [clientname] --> argc: 2, argv[0] = Network.exe, argv[1] = clientname
   * Andernfalls: Network.exe --> argc: 1, argv[0] = Network.exe und der Server wird gestartet.
   */ 
  if (argc > 1) 
  {
    clientname = argv[1];
  }

  if (clientname)
    client(clientname, serverPort);
  else
    server(serverPort);
}

// ------------------------------------------------------------------
/** 
 * Erbt von CommCallbacks und implementiert die Callbacks, die von der Communication-Klasse aufgerufen werden.
 * Pure virtual functions must be implemented in derived classes.
 */
class CallbackHandler : public CommCallbacks 
{
public:
  // got connection from host / port
  virtual void NewConnectionCB(const char *hostname)
  {
    std::cout << "got new connection from " << hostname << std::endl;
  }

  virtual void ConnectionLost()
  {
    std::cout << "connection lost" << std::endl;
  }

  virtual void DataReceived(const char *data, unsigned len)
  {
    // here we rely on the fact that the data is a string!
    std::cout << "got new data >>" << data << "<< len " << len << std::endl;
  }
};
// -------------------------------------------------------------------
/**
 * Server function: starts a server at the given port and waits for incoming connections.
 * It reads input from the console and sends it to the connected partner.
 */
void server(unsigned short port)
{
  std::shared_ptr<CommCallbacks> myCallbackHandler(new CallbackHandler());
  Communication myComm(myCallbackHandler);

  myComm.Activate(port);

  std::cout << "server started at port " << port << std::endl;

  char inputstr[100];

  do {
    memset(inputstr, 0, sizeof(inputstr));
    std::cin >> inputstr;

    std::cout << "sending >>" << inputstr << std::endl;

    myComm.WriteToPartner(inputstr, strlen(inputstr) + 1);

    myComm.ProcessMessage();
    myComm.ProcessMessage();

  } while (strcmp(inputstr, "ENDE"));

  myComm.Deactivate();
}

/**
 * Client function: connects to a server at the given hostname and port.
 * It reads input from the console and sends it to the connected server.
 */
void client(const char *hostname, unsigned short port)
{
  std::shared_ptr<CommCallbacks> myCallbackHandler(new CallbackHandler());
  Communication myComm(myCallbackHandler);

  bool res = myComm.Connect(hostname, port);

  std::cout << "client started for server " << hostname << " at port " << port << "result " << res << std::endl;
  if (res)
  {
    char inputstr[100];

    do {
      memset(inputstr, 0, sizeof(inputstr));
      std::cin.getline(inputstr, sizeof(inputstr));

      std::cout << "sending >>" << inputstr << std::endl;

      myComm.WriteToPartner(inputstr, strlen(inputstr) + 1);

      myComm.ProcessMessage();
      myComm.ProcessMessage();

    } while (strcmp(inputstr, "ENDE"));
  }
  myComm.Disconnect();
}

