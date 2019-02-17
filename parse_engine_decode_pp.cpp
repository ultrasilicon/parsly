#include "parse_engine.h"

#include "net_stack.h"
#include "packet.h"

#include "sized_mask.h"
#include "json.hpp"

#define _POP_DECODER_INJECT_POINT


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

  _POP_DECODER_INJECT_POINT

  return nullptr;
}
