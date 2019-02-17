#include "parse_engine.h"

#include "net_stack.h"
#include "packet.h"

#include "sized_mask.h"

Packet* ParseEngine::decode(char* stream, const size_t &size)
{
  if(!decodable(stream, size))
    return nullptr;

  auto pos = scopeBegin<uint32_t>(stream);
  auto end = scopeEnd<uint32_t>(stream);
  auto flag = redeemVal<uint8_t>(pos, end);

  ///[BEGIN _POP_DECODER_INJECT_POINT]////
  ///[END _POP_DECODER_INJECT_POINT]////

  decodeCleanup(pos, stream, size);
  return nullptr;
}
