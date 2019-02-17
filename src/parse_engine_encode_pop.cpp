#include "parse_engine.h"

#include "net_stack.h"
#include "packet.h"

#include "sized_mask.h"


char* ParseEngine::encode(Packet *packet)
{
    std::vector<char> stream(sizeof(uint32_t)); // vector as memory management helper
    size_t pos = decltype (stream)::size_type{};
    const auto flag = packet->msgType;

    ///[BEGIN _POP_ENCODER_INJECT_POINT]///
    ///[END _POP_ENCODER_INJECT_POINT]///

    size_t ss = stream.size() - sizeof(uint32_t); // total size excluding main header
    memcpy(&((SizedMask<uint32_t>*) &stream.front())->header, &ss, sizeof(uint32_t)); // set main header

    auto* enc = new char[stream.size()]; // to return
    memcpy(enc, stream.data(), stream.size());
    return enc;
}
