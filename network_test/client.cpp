
#include <ht_network.h>
#include <ht_tcpsocket.h>
#include <ht_socketaddress.h>
#include <ht_debug.h>

using namespace Hatchit;
using namespace Hatchit::Network;

int main(int argc, char* argv[])
{
    Network::Initialize();

    SocketAddress addr("127.0.0.1", 1111);
    TCPSocketPtr connection = std::make_shared<TCPSocket>();
    if(connection->Connect(addr) == 0)
    {
        HT_DEBUG_PRINTF("Connected!\n");
    }
    else
    {
        HT_DEBUG_PRINTF("Failed to connect to host server.\n");
    }

    Network::Shutdown();
    return 0;
}