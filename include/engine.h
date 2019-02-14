#ifndef PARSELYENGINE_H
#define PARSELYENGINE_H

#include "sized_mask.h"

#include <tuple>
#include <string>
#include <string.h>


class Engine
{
public:
  Engine();

  bool decodeScoped(char* stream, const uint32_t &size);

private:
};

using pe_str_len_t = uint32_t;

template <typename Header>
char* scopeBegin(char *stream)
{
  return stream + sizeof(Header);
}

template <typename Header>
char* scopeEnd(char *stream)
{
  Header offset = ((SizedMask<Header>*) stream)->header;
  return stream + sizeof(offset);
}

template <typename T>
T redeemVal(char *b)
{
  T r = ((SizedMask<T>*) b)->header;
  b += sizeof(T);
  return r;
}

template <typename Header, typename T>
T redeemVal(char* stream)
{
//  char *b = scopeBegin<T>(stream);
//  char *e = scopeEnd<T>(stream);
//  long scopeLen = e - b;
  long scopeLen = ((SizedMask<Header>*) stream)->header;
  auto val = (char*) malloc(scopeLen + 1);
  strcpy(val, ((SizedMask<Header>*) stream)->data);
  val[scopeLen] = '\0';
  stream += sizeof(Header) + scopeLen;
  return val;
}


#endif // PARSELYENGINE_H
