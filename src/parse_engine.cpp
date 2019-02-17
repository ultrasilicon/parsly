#include "parse_engine.h"



ParseEngine::ParseEngine(NetStack *ns)
  : m_net_stack(ns)
{
}





void ParseEngine::message(Packet *p)
{
  m_net_stack->write(encode(p));
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
