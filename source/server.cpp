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
#include <thread>

using namespace Hatchit;
using namespace Hatchit::Core;
using namespace Hatchit::Network;

int main(int argc, char* argv[])
{
    DebugPrintF("Server.\n");

    int result = std::atexit(Network::Shutdown);
    if (result != 0) {
#ifdef _DEBUG
        DebugPrintF("atexit registration failed.\n");
#endif
        std::exit(EXIT_FAILURE);
    }

    Network::Initialize();
    
    if (argc < 2) {
        DebugPrintF("usage %s port\n", argv[0]);
        std::exit(EXIT_FAILURE);
    }

    TCPSocketPtr socket = SocketUtil::CreateTCPSocket(SocketAddressFamily::INET);
    
    int port = atoi(argv[1]);
    SocketAddressPtr address = std::make_shared<SocketAddress>(port);

    socket->Bind(*address);


    while (true)
    {
        socket->Listen();

        std::thread t([](TCPSocketPtr& s){
            SocketAddressPtr client = std::make_shared<SocketAddress>();

            TCPSocketPtr clientSocket = s->Accept(*client);

            while (true)
            {
                char buffer[256] = { 0 };
                int n = clientSocket->Receive(buffer, 255);
                if (n < 0 || strlen(buffer) <= 0)
                    std::exit(EXIT_FAILURE);

                DebugPrintF("Message: %s\n", buffer);

                const char* msg = "Server received message";
                n = clientSocket->Send(msg, strlen(msg));
                if (n < 0)
                    std::exit(EXIT_FAILURE);
            }

        }, std::ref(socket));
        t.detach();
    }
   
    return 0;
}
