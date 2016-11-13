
#include <ht_network.h>
#include <ht_tcpsocket.h>
#include <ht_socketaddress.h>
#include <ht_debug.h>
#include <istream>
#include <ostream>
#include <Attack.pb.h>

#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>

using namespace Hatchit;
using namespace Hatchit::Network;


uint32_t ParseHeader(char* buffer)
{
    uint32_t size;
    google::protobuf::io::ArrayInputStream ais(buffer, 4);
    google::protobuf::io::CodedInputStream cis(&ais);
    cis.ReadVarint32(&size);
    HT_DEBUG_PRINTF("Packet Size: %d\n", size);

    return size;
}

void ParseBody(char* buffer, uint32_t size)
{
    Game::Combat::Attack attack;
    google::protobuf::io::ArrayInputStream ais(buffer, size);
    google::protobuf::io::CodedInputStream cis(&ais);
    cis.ReadVarint32(&size);

    google::protobuf::io::CodedInputStream::Limit limit = cis.PushLimit(size);
    attack.ParseFromCodedStream(&cis);
    cis.PopLimit(limit);

    HT_DEBUG_PRINTF("Attack: %s\n", attack.DebugString());
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
        TCPSocketPtr connection = std::make_shared<TCPSocket>();
        if(connection->Connect(address) == 0)
        {
            HT_DEBUG_PRINTF("Connected!\n");
            char buffer[4];
            uint32_t bytesRead = connection->Receive(buffer, 4, MSG_PEEK);
            HT_DEBUG_PRINTF("First read count: %d\n", bytesRead);
            uint32_t size = ParseHeader(buffer);

            char body[size + 4];
            bytesRead = connection->Receive(body, size+4);
            HT_DEBUG_PRINTF("Second read count: %d\n", bytesRead);
            ParseBody(body, size+4);
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