#include "parse_engine.h"
#include <iostream>

ParseEngine::ParseEngine()
{
}

bool ParseEngine::decodable(char *stream, const size_t &size)
{
  decode_buffer.append(stream, size);
  if(decode_buffer.size() < sizeof(uint32_t))
    {
      printf("ParselyEngine: Returning - Header Incomplete / Empty Packet");
      return false;
    }
  if(decode_buffer.size() < scopeLen<uint32_t>(decode_buffer.c_str()))
    {
      printf("ParselyEngine: Returning - Packet Imcomplete");
      return false;
    }
  return true;
}

void ParseEngine::decodeCleanup(char *pos, char *stream, const size_t &size)
{
  if(pos == stream + size)
    decode_buffer.clear();
  else
    decode_buffer.erase(decode_buffer.begin(), decode_buffer.begin() + (pos - stream));
  if(stream)
    free(stream);
}

