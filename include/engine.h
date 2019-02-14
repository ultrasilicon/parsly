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

static char* constructStr(char* b, char* e)
{
  char *p = b;
  long len = e - b;
  auto val = (char*) malloc(len + 1);
  for(long c = 0; c < len; ++ c, ++ p) {
        val[c] = *p;
     }
  val[len] = '\0';
  return val;
}

template <typename _HeaderT>
char* scopeBegin(char *stream)
{
  return stream + sizeof(_HeaderT);
}

template <typename _HeaderT>
char* scopeEnd(char *stream)
{
  return stream + sizeof(_HeaderT) + sizeof(((SizedMask<_HeaderT>*) stream)->header);
}

template <typename _HeaderT>
_HeaderT scopeLen(char *stream)
{
  return ((SizedMask<_HeaderT>*) stream)->header;
}

template <typename _HeaderT>
std::pair<char*, char*> getScope(char *stream)
{
  return std::make_pair(scopeBegin<_HeaderT>(stream), scopeEnd<_HeaderT>(stream));
}

template <typename _ValT>
_ValT redeemVal(char *b)
{
  _ValT r = ((SizedMask<_ValT>*) b)->header;
  b += sizeof(_ValT);
  return r;
}

template <typename _HeaderT, typename _ValT>
_ValT redeemVal(std::pair<char*, char*> scope)
{
  _HeaderT len = scopeLen<_HeaderT>(scope.first);
  char *p = scope.first + sizeof(_HeaderT);
  auto val = (char*) malloc(len + 1);
  for(_HeaderT c = 0; c < len; ++ c, ++ p) {
        val[c] = *p;
     }
  val[len] = '\0';
  return (_ValT)val;
}

template <typename _HeaderT, typename _ValT>
_ValT redeemVal(char* stream)
{
  _HeaderT scopeLen = ((SizedMask<_HeaderT>*) stream)->header;
  auto val = (char*) malloc(scopeLen + 1);
  strcpy(val, ((SizedMask<_HeaderT>*) stream)->data);
  val[scopeLen] = '\0';
  stream += sizeof(_HeaderT) + scopeLen;
  return (_ValT)val;
}


#endif // PARSELYENGINE_H
