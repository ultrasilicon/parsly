#pragma once

#include "net_stack.h"
#include "packet.h"

#include <string>
#include <string.h>
#include <utility>
#include <tuple>
#include <functional>

#include "sized_mask.h"


#define __TYPE 100
#define _DATA_IDX -1
#define __TYPE_ARGS int


class ParseEngine
{
public:
  ParseEngine(NetStack* ns);

  void message(Packet* p, std::string &ip);

  std::function<void(Packet* p)> onMessage;

private:
  char *encode(Packet *packet);             //! Weipu
  Packet* decode(char *stream, const size_t &size); //! Tim

  bool decodable(char *stream, const size_t &size);
  bool decodeCleanup(char* pos, char *stream, const size_t &size);

  std::string decode_buffer;
  NetStack *m_net_stack;

};

using pe_str_len_t = uint32_t;

static char* constructStr(char* b, size_t len)
{
  auto val = (char*) malloc(len + 1);
  for(long c = 0; c < len; ++ c, ++ b) {
        val[c] = *b;
     }
  val[len] = '\0';
  return val;
}

template <typename _HeaderT>
_HeaderT scopeLen(const char *stream)
{
  return ((SizedMask<_HeaderT>*) stream)->header;
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
  _ValT r = ((SizedMask<_ValT>*) stream)->header;
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












