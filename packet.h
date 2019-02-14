#ifndef PACKET_H
#define PACKET_H

#include <unordered_map>
#include <variant>

class Packet;

using variant_t = std::variant<
    int8_t
    , int16_t
    , int32_t
    , int64_t
    , uint8_t
    , uint16_t
    , uint32_t
    , uint64_t
    , std::string
//    , Packet*
>;

class Packet
{
public:
    Packet();
    std::unordered_map<std::string, variant_t> data;
};



#endif // PACKET_H
