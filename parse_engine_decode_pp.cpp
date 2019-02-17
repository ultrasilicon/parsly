#include "parse_engine.h"

#include "net_stack.h"
#include "packet.h"

#include "sized_mask.h"
#include "json.hpp"


Packet* ParseEngine::decode(char* stream, const size_t &size)
{
  printf("ParselyEngine: New Data Section !!");
  if(size == 0 || size < sizeof(uint32_t))
    {
      printf("ParselyEngine: Returning - Header Not Complete / Empty Packet");
      return nullptr;
    }

  if(size < ((SizedMask <uint32_t>*) stream)->header - sizeof(uint32_t))
    {
      printf("ParselyEngine: Returning - Packet Imcomplete");
      return nullptr;
    }

  auto pos = scopeBegin<uint32_t>(stream);
  auto end = scopeEnd<uint32_t>(stream);
  auto msgType = redeemVal<uint8_t>(pos, end);
  switch (msgType) {
    case 0:{ return new Packet{{ // HeartBeat
              redeemStr<pe_str_len_t>(pos, end),
              redeemStr<pe_str_len_t>(pos, end),
              redeemStr<pe_str_len_t>(pos, end),
              redeemVal<uint32_t>(pos, end),
            }, msgType}; }
    case 1:{ return new Packet{{
              redeemStr<pe_str_len_t>(pos, end),
              redeemStr<pe_str_len_t>(pos, end),
            }, msgType}; }
    case 2:{ return new Packet{{ // TextMessage
              redeemStr<pe_str_len_t>(pos, end),
              redeemStr<pe_str_len_t>(pos, end),
              redeemStr<pe_str_len_t>(pos, end),
            }, msgType}; }
    case 3:{ return new Packet{{ // ImageMessage
              redeemStr<pe_str_len_t>(pos, end),
              redeemStr<pe_str_len_t>(pos, end),
              redeemStr<pe_str_len_t>(pos, end),
            }, msgType}; }
    default:{ return nullptr; } }
}
