#include "parse_engine.h"

#include "net_stack.h"
#include "packet.h"

#include "sized_mask.h"
#include "json.hpp"


Packet* ParseEngine::decode(char* stream, const size_t &size)
{
  if(size == 0 || size < sizeof(uint32_t))
    {
      printf("ParselyEngine: Returning - Header Incomplete / Empty Packet");
      return nullptr;
    }

  if(size < scopeLen<uint32_t>(stream))
    {
      printf("ParselyEngine: Returning - Packet Imcomplete");
      return nullptr;
    }

  auto pos = scopeBegin<uint32_t>(stream);
  auto end = scopeEnd<uint32_t>(stream);
  auto flag = redeemVal<uint8_t>(pos, end);
  switch (flag) {
    case 0:{ // HeartBeat
        return new Packet{{
              redeemStr<pe_str_len_t>(pos, end),
              redeemStr<pe_str_len_t>(pos, end),
              redeemStr<pe_str_len_t>(pos, end),
              redeemVal<uint32_t>(pos, end),
            }, flag};
      }
    case 1:{ // ConnectionInfo
        return new Packet{{
              redeemStr<pe_str_len_t>(pos, end),
              redeemStr<pe_str_len_t>(pos, end),
            }, flag};
      }
    case 2:{ // TextMessage
        return new Packet{{
              redeemStr<pe_str_len_t>(pos, end),
              redeemStr<pe_str_len_t>(pos, end),
              redeemStr<pe_str_len_t>(pos, end),
            }, flag};
      }
    case 3:{ // ImageMessage
        return new Packet{{
              redeemStr<pe_str_len_t>(pos, end),
              redeemStr<pe_str_len_t>(pos, end),
              redeemStr<pe_str_len_t>(pos, end),
            }, flag};
      }
    default:{ return nullptr; }
  }
}
