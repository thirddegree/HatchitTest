/**
**    Hatchit Engine
**    Copyright(c) 2015 Third-Degree
**
**    GNU Lesser General Public License
**    This file may be used under the terms of the GNU Lesser
**    General Public License version 3 as published by the Free
**    Software Foundation and appearing in the file LICENSE.LGPLv3 included
**    in the packaging of this file. Please review the following information
**    to ensure the GNU Lesser General Public License requirements
**    will be met: https://www.gnu.org/licenses/lgpl.html
**
**/

#include <ht_network.h>
#include <ht_debug.h>
#include <ht_socketutil.h>
#include <cstdlib>
#include <cstring>

using namespace Hatchit;
using namespace Hatchit::Core;
using namespace Hatchit::Network;

int main(int argc, char* argv[])
{
    DebugPrintF("Server.\n");
    
    if(argc < 2) {
#ifdef _DEBUG
        DebugPrintF("ERROR: no port provided. Exiting.\n");
#endif
        std::exit(EXIT_FAILURE);
    }

    TCPSocketPtr socket = SocketUtil::CreateTCPSocket(SocketAddressFamily::INET);
    
    SocketAddressPtr address = std::make_shared<SocketAddress>(atoi(argv[1]));

    socket->Bind(*address);

    socket->Listen();

    SocketAddressPtr client = std::make_shared<SocketAddress>();
    
    TCPSocketPtr clientSocket = socket->Accept(*client);    

    while(true)
    {
        char buffer[256] = {0};
        int n = clientSocket->Receive(buffer, 255);
        if(n < 0)
            std::exit(EXIT_FAILURE);

        DebugPrintF("Message: %s\n", buffer);

        const char* msg = "Server received message";
        n = clientSocket->Send(msg, strlen(msg));
        if(n < 0)
            std::exit(EXIT_FAILURE);        
    }
 
    return 0;
}
