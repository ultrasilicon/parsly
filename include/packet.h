#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include <libagio/variant.h>
#include <type_traits>

using variant_t = Agio::Variant<
    bool
    , int8_t
    , int16_t
    , int32_t
    , int64_t
    , uint8_t
    , uint16_t
    , uint32_t
    , uint64_t
    , std::string
>;

struct Packet
{
  std::vector<variant_t> data;
  uint8_t msgType;
};



