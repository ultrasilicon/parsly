#pragma once

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
  ParseEngine();
  static iovec encode(Packet *packet);
  Packet* decode(char *stream, const size_t &size);

private:
  bool decodable(const char* stream, const size_t &size);
  void decodeCleanup(char* pos, char *stream, const size_t &size);

  std::string decode_buffer;
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
_ValT redeemVal(char*& stream, const char* end)
{
  if(stream == end)
    return _ValT();
  SizedMask<_ValT>* p = (reinterpret_cast<SizedMask<_ValT>*>(stream));
  _ValT r = p->header;
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
  auto ptr = stream + sizeof(_HeaderT);
  auto size = scopeLen<_HeaderT>(stream);
  std::string r(ptr, size);
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

/*!
 * \brief: If this funciton is not a template, it will have compile errors, because it's not in any class.
 * Put it here for now as in the future it all these parsing functions will be moved to a pre-compile module.
 * \arg _std_string must be std::string.
 */
template <typename _std_string>
void insertStr(std::vector<char>& stream, size_t& pos, const _std_string& s)
{
    stream.resize(stream.size() + sizeof(pe_str_len_t) + s.length());
    auto len = s.length();
    memcpy(&((SizedMask<std::string>*) &stream[pos])->header, &len, sizeof(pe_str_len_t));
    pos += sizeof(pe_str_len_t);
    memcpy(&stream[pos], s.c_str(), s.length());
    pos += s.length();
}











