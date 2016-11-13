
#include <ht_network.h>
#include <ht_tcpsocket.h>
#include <ht_socketaddress.h>
#include <ht_debug.h>

using namespace Hatchit;
using namespace Hatchit::Network;

int main(int argc, char* argv[])
{
    Network::Initialize();

    /**
     * Check command arguments.
     * [param] Host address
     * [param] Port number
     */
    if(argc > 2)
    {
        SocketAddress address(argv[1], std::atoi(argv[2]));
        TCPSocketPtr listen = std::make_shared<TCPSocket>();
        listen->Bind(address);
        listen->Listen();

        TCPSocketPtr connection = listen->Accept();
        if (!connection) {
            HT_DEBUG_PRINTF("Failed to accept client connection.\n");
        } else {
            HT_DEBUG_PRINTF("Client[%s] connected.\n", connection->GetAddress().ToString());
            HT_DEBUG_PRINTF("Listen[%s]\n", address.ToString());
        }
    }
    else
    {
        HT_DEBUG_PRINTF("Invalid arguments.\n");
        HT_DEBUG_PRINTF("Usage: Server [address] [port]\n");
    }

    Network::Shutdown();
    return 0;
}