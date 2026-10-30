// Server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "ServerCallbackHandler.h"

int main()
{
    std::cout << "Hello World!\n";

    unsigned short serverPort = 8000;

    ServerCallbackHandler *serverCallbackHandler = new ServerCallbackHandler();
    std::shared_ptr<CommCallbacks> myCallbackHandler(serverCallbackHandler);
	Communication myComm(myCallbackHandler); // create communication layer and link it to callback handler

    // link communication to callback handler
    serverCallbackHandler->SetCommunicationLayer(&myComm);

	myComm.Activate(serverPort); // start server at port 8000

    std::cout << "server started at port " << serverPort << std::endl;

    while (true) 
    {
      // wait some time - msecs
      OS_Sleep(100);

      // check for answers
      while (myComm.IsMessagePending())
        myComm.ProcessMessage();

    } 

	// This section will never be reached in this example, but is here for completeness.
    myComm.Deactivate();

}

