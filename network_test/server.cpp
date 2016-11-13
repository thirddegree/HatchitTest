
#include <ht_network.h>
#include <ht_tcpinterface.h>
#include <ht_tcpprocessplugin.h>
#include <ht_tcpsocket.h>
#include <ht_socketaddress.h>
#include <ht_debug.h>

using namespace Hatchit;
using namespace Hatchit::Network;

class ConsoleOut : public TCPProcessPlugin
{
public:
    ConsoleOut();

    virtual void OnAttach() override;

    virtual void OnDetach() override;

    virtual void OnUpdate() override;

    virtual void OnReceive(std::shared_ptr<Packet> &packet) override;

    virtual void OnAcceptConnection(const SocketAddress &address) override;

    virtual void OnFailedConnection() override;

public:

};

ConsoleOut::ConsoleOut() : TCPProcessPlugin() {

}

void ConsoleOut::OnAttach() {
    HT_DEBUG_PRINTF("ConsoleOut: Attached\n");
}

void ConsoleOut::OnDetach() {

}

void ConsoleOut::OnUpdate() {

}

void ConsoleOut::OnReceive(std::shared_ptr<Packet> &packet) {

}

void ConsoleOut::OnAcceptConnection(const SocketAddress &address) {
    HT_DEBUG_PRINTF("Client[%s] connected.\n", address.ToString());
}

void ConsoleOut::OnFailedConnection() {

}

class EchoServer : public TCPInterface
{
public:
    EchoServer();

    ~EchoServer();
};

EchoServer::EchoServer()
    : TCPInterface()
{

}

EchoServer::~EchoServer()
{

}

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
//        SocketAddress address(argv[1], std::atoi(argv[2]));
//        TCPSocketPtr listen = std::make_shared<TCPSocket>();
//        listen->Bind(address);
//        listen->Listen();

        EchoServer _server;
        std::shared_ptr<TCPProcessPlugin> _plugin = std::make_shared<ConsoleOut>();
        _server.AttachPlugin(_plugin);
        _server.Init(argv[1], std::atoi(argv[2]), 10);

//        TCPSocketPtr connection = listen->Accept();
//        if (!connection) {
//            HT_DEBUG_PRINTF("Failed to accept client connection.\n");
//        } else {
//            HT_DEBUG_PRINTF("Client[%s] connected.\n", connection->GetAddress().ToString());
//            HT_DEBUG_PRINTF("Listen[%s]\n", address.ToString());
//        }
    }
    else
    {
        HT_DEBUG_PRINTF("Invalid arguments.\n");
        HT_DEBUG_PRINTF("Usage: Server [address] [port]\n");
    }

    Network::Shutdown();
    return 0;
}