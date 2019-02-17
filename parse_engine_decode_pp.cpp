#include "parse_engine.h"

#include "net_stack.h"
#include "packet.h"

#include "sized_mask.h"
#include "json.hpp"


Packet* ParseEngine::decode(char* stream, const uint32_t &size) //<< WARN return value is nulled
{
  printf("ParselyEngine: New Data Section !!");
  if(size == 0 || size < (int) sizeof (uint32_t))
    {
      printf("ParselyEngine: Returning - Header Not Complete / Empty Packet");
      return nullptr;
    }

  char* mobilePtr = stream + sizeof(uint32_t);

  uint32_t contentSize = ((SizedMask <uint32_t>*) stream)->header;

  if(size < contentSize - sizeof(uint32_t))
    {
      printf("ParselyEngine: Returning - Packet Imcomplete");
      return nullptr;
    }


  //! Header detected & Packet complete
  auto end = scopeEnd<uint32_t>(stream);
  auto msgType = redeemVal<uint8_t>(mobilePtr, end);

//  redeemVal<__TYPE_ARGS>(mobilePtr);
  switch (msgType) {
    case 0:{ return new Packet{{ // HeartBeat
              redeemStr<pe_str_len_t>(mobilePtr, end),
              redeemStr<pe_str_len_t>(mobilePtr, end),
              redeemStr<pe_str_len_t>(mobilePtr, end),
              redeemVal<uint32_t>(mobilePtr, end),
            }, msgType}; }
    case 1:{ return new Packet{{
              redeemStr<pe_str_len_t>(mobilePtr, end),
              redeemStr<pe_str_len_t>(mobilePtr, end),
            }, msgType}; }
    case 2:{ return new Packet{{ // TextMessage
              redeemStr<pe_str_len_t>(mobilePtr, end),
              redeemStr<pe_str_len_t>(mobilePtr, end),
              redeemStr<pe_str_len_t>(mobilePtr, end),
            }, msgType}; }
    case 3:{ return new Packet{{ // ImageMessage
              redeemStr<pe_str_len_t>(mobilePtr, end),
              redeemStr<pe_str_len_t>(mobilePtr, end),
              redeemStr<pe_str_len_t>(mobilePtr, end),
            }, msgType}; }
    default:{ return nullptr; }
    }
}
