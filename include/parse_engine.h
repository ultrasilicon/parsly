#pragma once

#include "net_stack.h"
#include "packet.h"

#include <sys/uio.h>
#include <string>
#include <string.h>
#include <utility>
#include <tuple>
#include <functional>

#include "sized_mask.h"


class ParseEngine
{
public:
  ParseEngine(NetStack* ns);

  void message(Packet* p, const char *ip);

  std::function<void(Packet* p)> onMessage;


private:
  iovec encode(Packet *packet);
  Packet* decode(char *stream, const size_t &size);

  bool decodable(char *stream, const size_t &size);
  void decodeCleanup(char* pos, char *stream, const size_t &size);


  std::string decode_buffer;
  NetStack *m_net_stack;

};

using pe_str_len_t = uint32_t;


template <typename _HeaderT>
_HeaderT scopeLen(const char *stream)
{
  return (reinterpret_cast<SizedMask<_HeaderT>*>(const_cast<char*>(stream)))->header;
}

template <typename _HeaderT>
char* scopeBegin(char *stream)
{
  return stream + sizeof(_HeaderT);
}

template <typename _HeaderT>
const char* scopeEnd(char *stream)
{
  return scopeBegin<_HeaderT>(stream) + scopeLen<_HeaderT>(stream);
}

template <typename _HeaderT>
std::pair<char*, char*> getScope(char *stream)
{
  return std::make_pair(scopeBegin<_HeaderT>(stream), scopeEnd<_HeaderT>(stream));
}

template <typename _ValT>
_ValT redeemVal(char* &stream, const char* end)
{
  if(stream == end)
    return _ValT();
  _ValT r = (reinterpret_cast<SizedMask<_ValT>*>(stream))->header;
  stream += sizeof(_ValT);
  return r;
}

//template <typename _HeaderT, typename _ValT>
//_ValT redeemStr(char* &stream, const char* end)
//{
//  if(stream == end)
//    return "";
//  _ValT r = (_ValT)constructStr(stream + sizeof(_HeaderT),
//                                 scopeLen<_HeaderT>(stream));
//  stream += sizeof(_HeaderT) + scopeLen<_HeaderT>(stream);
//  return r;
//}

template <typename _HeaderT>
std::string redeemStr(char* &stream, const char* end)
{
  if(stream == end)
    return "";
  std::string r(stream + sizeof(_HeaderT), scopeLen<_HeaderT>(stream));
  stream += sizeof(_HeaderT) + scopeLen<_HeaderT>(stream);
  return r;
}

template <typename _ValT>
void insertVal(std::vector<char>& stream, size_t& pos, const _ValT& v)
{
    stream.resize(stream.size() + sizeof(_ValT));
    memcpy(&((SizedMask<_ValT>*) &stream[pos])->header, &v, sizeof(_ValT));
    pos += sizeof(_ValT);
}

void insertStr(std::vector<char>& stream, size_t& pos, const std::string& s);












