
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
        TCPSocketPtr connection = std::make_shared<TCPSocket>();
        if(connection->Connect(address) == 0)
        {
            HT_DEBUG_PRINTF("Connected!\n");
        }
        else
        {
            HT_DEBUG_PRINTF("Failed to connect to host server.\n");
        }
    }
    else
    {
        HT_DEBUG_PRINTF("Invalid arguments.\n");
        HT_DEBUG_PRINTF("Usage: Client [address] [port]\n");
    }



    Network::Shutdown();
    return 0;
}