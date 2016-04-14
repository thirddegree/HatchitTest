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

#define _SCL_SECURE_NO_WARNINGS

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

    int result = std::atexit(Network::Shutdown);
    if (result != 0) {
#ifdef _DEBUG
        DebugPrintF("atexit registration failed.\n");
#endif
        std::exit(EXIT_FAILURE);
    }

    Network::Initialize();

    if(argc < 2) {
        DebugPrintF("usage %s destination:port\n", argv[0]);
        std::exit(EXIT_FAILURE);
    }

    SocketAddressPtr server = SocketUtil::CreateIPv4Address(argv[1]);
    
    TCPSocketPtr socket = SocketUtil::CreateTCPSocket(SocketAddressFamily::INET);

    result = socket->Connect(*server);
    if (result < 0) {
        std::exit(EXIT_FAILURE);
    }
       
    while(true)
    {
        std::string msg;
        DebugPrintF("Please enter a message: ");
        std::getline(std::cin, msg);
        if (msg.length() <= 0)
            std::exit(EXIT_FAILURE);

        char sbuffer[256] = {0};
        msg.copy(sbuffer, static_cast<size_t>(255));
        int n = socket->Send(sbuffer, 255);
        if (n < 0)
            std::exit(EXIT_FAILURE);

        char buffer[256] = {0};
        n = socket->Receive(buffer, 255);
        if (n < 0)
            std::exit(EXIT_FAILURE);

        DebugPrintF("%s\n", buffer);
    }

    return 0;
}
