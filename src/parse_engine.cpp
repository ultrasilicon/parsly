#include "parse_engine.h"



ParseEngine::ParseEngine(NetStack *ns)
  : m_net_stack(ns)
{
}


void ParseEngine::message(Packet *p, std::string &ip)
{
  m_net_stack->write(encode(p), ip);
}

bool ParseEngine::decodable(char *stream, const size_t &size)
{
  decode_buffer += std::string(stream, size);
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

bool ParseEngine::decodeCleanup(char *pos, char *stream, const size_t &size)
{
  if(pos != stream + size)
      decode_buffer += std::string(pos, stream + size - pos);
  if(stream)
    free(stream);
}

void insertStr(std::vector<char>& stream, size_t& pos, const std::string& s)
{
    stream.resize(stream.size() + sizeof(pe_str_len_t) + s.length());
    auto len = s.length();
    memcpy(&((SizedMask<std::string>*) &stream[pos])->header, &len, sizeof(pe_str_len_t));
    pos += sizeof(pe_str_len_t);
    memcpy(&stream[pos], s.c_str(), s.length());
    pos += s.length();
}
