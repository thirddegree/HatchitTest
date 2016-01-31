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
#include <ht_socketaddress.h>
#include <ht_socketutil.h>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace Hatchit;
using namespace Hatchit::Core;
using namespace Hatchit::Network;

int main(int argc, char* argv[])
{
    DebugPrintF("Client.\n");

    if(argc < 3) {
        DebugPrintF("usage %s hostname port\n", argv[0]);
        std::exit(EXIT_FAILURE);
    }

    uint16_t port = atoi(argv[2]);
    
    hostent* _server;
    _server = gethostbyname(argv[1]);
    if(!_server) {
#ifdef _DEBUG
        ReportError("no such host available");
#endif
        std::exit(EXIT_FAILURE);
    }

    SocketAddressPtr server = std::make_shared<SocketAddress>(_server, port);
    
    TCPSocketPtr socket = SocketUtil::CreateTCPSocket(SocketAddressFamily::INET);

    int result = socket->Connect(*server);
    if(result < 0)
        std::exit(EXIT_FAILURE);

    while(true)
    {
        std::string msg;
        DebugPrintF("Please enter a message: ");
        std::getline(std::cin, msg);

        char sbuffer[256] = {0};
        msg.copy(sbuffer, 255);
        int n = socket->Send(sbuffer, 255);
        if(n < 0)
            std::exit(EXIT_FAILURE);

        char buffer[256] = {0};
        n = socket->Receive(buffer, 255);
        if(n < 0)
            std::exit(EXIT_FAILURE);

        DebugPrintF("%s\n", buffer);
    }

    return 0;
}
