
#include <ht_network.h>
#include <ht_tcpinterface.h>
#include <ht_tcpprocessplugin.h>
#include <ht_tcpsocket.h>
#include <ht_socketaddress.h>
#include <ht_debug.h>
#include <Attack.pb.h>

#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>

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
        SocketAddress address(argv[1], std::atoi(argv[2]));
        TCPSocketPtr listen = std::make_shared<TCPSocket>();
        listen->Bind(address);
        listen->Listen();

//        EchoServer _server;
//        std::shared_ptr<TCPProcessPlugin> _plugin = std::make_shared<ConsoleOut>();
//        _server.AttachPlugin(_plugin);
//        _server.Init(argv[1], std::atoi(argv[2]), 10);

        TCPSocketPtr connection = listen->Accept();
        if (!connection) {
            HT_DEBUG_PRINTF("Failed to accept client connection.\n");
        } else {
            HT_DEBUG_PRINTF("Client[%s] connected.\n", connection->GetAddress().ToString());

            /**
             * We want to send a protobuf Attack message.
             * To do this, we need to delimit the size of this message so we know
             * if we have received the full message stream
             */
            Game::Combat::Attack attack;
            attack.set_damage(32);
            int size = attack.ByteSize()+4;
            char* pkt = new char[size];
            google::protobuf::io::ArrayOutputStream aos(pkt, size);
            google::protobuf::io::CodedOutputStream cos(&aos);
            cos.WriteVarint32(attack.ByteSize());
            attack.SerializeToCodedStream(&cos);


            uint32_t bytesSent = connection->Send((void*)pkt, size);
            HT_DEBUG_PRINTF("Bytes Sent: %d\n", bytesSent);
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