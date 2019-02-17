#pragma once
#include "json.hpp"

#include "net_stack.h"
#include "packet.h"

#include <string>
#include <string.h>
#include <utility>
#include <tuple>

#include "sized_mask.h"




class ParseEngine
{
public:
  ParseEngine(NetStack* ns);

  void message(Packet* p);
  void (*onMessage)(Packet* p);

private:
  char *encode(Packet *packet);             //! Weipu
  Packet* decode(char* stream, const uint32_t &size); //! Tim

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
constexpr _HeaderT scopeLen(char *stream)
{
  return ((SizedMask<_HeaderT>*) stream)->header;
}

template <typename _HeaderT>
constexpr char* scopeBegin(char *stream)
{
  return stream + sizeof(_HeaderT);
}

template <typename _HeaderT>
constexpr char* scopeEnd(char *stream)
{
  return scopeBegin<_HeaderT>(stream) + scopeLen<_HeaderT>(stream);
}

template <typename _HeaderT>
constexpr std::pair<char*, char*> getScope(char *stream)
{
  return std::make_pair(scopeBegin<_HeaderT>(stream), scopeEnd<_HeaderT>(stream));
}

template <typename _ValT>
_ValT redeemVal(char* &stream, char* end)
{
  if(stream == end)
    return _ValT();
  _ValT r = ((SizedMask<_ValT>*) stream)->header;
  stream += sizeof(_ValT);
  return r;
}

//template <typename _HeaderT, typename _ValT>
//_ValT redeemStr(char* &stream, char* end)
//{
//  if(stream == end)
//    return "";
//  _ValT r = (_ValT)constructStr(stream + sizeof(_HeaderT),
//                                 scopeLen<_HeaderT>(stream));
//  stream += sizeof(_HeaderT) + scopeLen<_HeaderT>(stream);
//  return r;
//}

template <typename _HeaderT>
std::string redeemStr(char* &stream, char* end)
{
  if(stream == end)
    return "";
  std::string r(stream + sizeof(_HeaderT), scopeLen<_HeaderT>(stream));
  stream += sizeof(_HeaderT) + scopeLen<_HeaderT>(stream);
  return r;
}















