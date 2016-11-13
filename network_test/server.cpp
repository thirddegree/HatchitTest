
#include <ht_network.h>
#include <ht_tcpsocket.h>
#include <ht_socketaddress.h>
#include <ht_debug.h>

using namespace Hatchit;
using namespace Hatchit::Network;

int main(int argc, char* argv[])
{
    Network::Initialize();

    SocketAddress addr("129.21.90.242", 4040);
    TCPSocketPtr listen = std::make_shared<TCPSocket>();
    listen->Bind(addr);
    listen->Listen();

    TCPSocketPtr connection = listen->Accept();
    if(!connection)
    {
        HT_DEBUG_PRINTF("Failed to accept client connection.\n");
    }
    else
    {
        HT_DEBUG_PRINTF("Client[%s] connected.\n", connection->GetAddress().ToString());
        HT_DEBUG_PRINTF("Listen[%s]\n", addr.ToString());
    }

    Network::Shutdown();
    return 0;
}