#ifndef PARSELYENGINE_H
#define PARSELYENGINE_H

#include "sized_mask.h"

#include <tuple>
#include <string>
#include <string.h>
#include <utility>

class Engine
{
public:
  Engine();

  bool decodeScoped(char* stream, const uint32_t &size);

private:
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
_ValT redeemVal(char *b)
{
  _ValT r = ((SizedMask<_ValT>*) b)->header;
//  b += sizeof(_ValT);
  return r;
}

template <typename _HeaderT, typename _ValT>
/*constexpr*/ _ValT redeemVal(char* stream)
{
  return (_ValT)constructStr(stream + sizeof(_HeaderT),
                             scopeLen<_HeaderT>(stream));
}

#endif // PARSELYENGINE_H
