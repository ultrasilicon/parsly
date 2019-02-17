#include "parse_engine.h"

#include "net_stack.h"
#include "packet.h"

#include "sized_mask.h"
#include "json.hpp"


char* ParseEngine::encode(Packet *packet)
{
    std::vector<char> stream(sizeof(uint32_t)); // memory management helper
    size_t pos = decltype (stream)::size_type{};

    const auto msgType = packet->msgType;
    switch (msgType) {
    // BEGIN CASE
      case __TYPE : {
        // BEGIN DATA FETCH
        insertStr(stream, pos, packet->data[0].get<std::string>());
        insertStr(stream, pos, packet->data[1].get<std::string>());
        insertStr(stream, pos, packet->data[2].get<std::string>());
        insertVal(stream, pos, packet->data[3].get<uint32_t>());
        // END DATA FETCH
      } break;
    // END CASE
      default:{ return nullptr; }
    }

    size_t ss = stream.size() - sizeof(uint32_t);
    memcpy(&((SizedMask<uint32_t>*) &stream.front())->header, &ss, sizeof(uint32_t));

    auto* enc = new char[stream.size()];
    memcpy(enc, stream.data(), stream.size());
    return enc;
}
