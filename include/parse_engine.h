#pragma once

#include "packet.h"

#include <sys/uio.h>
#include <string>
#include <string.h>
#include <utility>
#include <tuple>
#include <functional>

class ParseEngine
{
public:
  ParseEngine();
  static iovec encode(Packet *packet);
  Packet* decode(char *stream, const size_t &size);

private:
  bool decodable(const char* stream, const size_t &size);
  void decodeCleanup(char* pos, char *stream, const size_t &size);

  std::string decode_buffer;
};

using pe_str_len_t = uint32_t;
