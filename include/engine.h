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

//template <typename T>
//T redeemVal(char *b, char *e)
//{
//  long scopeLen = e - b;
//  auto data = (char*) malloc(scopeLen + 1);
//  memcpy(data, b, scopeLen);
//  data[scopeLen] = '\0';
//  return (T) data;
//}

template <typename Header, typename T>
T redeemVal(char* stream)
{
//  char *b = scopeBegin<T>(stream);
//  char *e = scopeEnd<T>(stream);
//  long scopeLen = e - b;
  long scopeLen = ((SizedScope<Header>*) stream)->header;
//  SizedMask<Header>* test = ((SizedMask<Header>*) stream);

  auto val = (char*) malloc(scopeLen + 1);
  strcpy(val, ((SizedScope<Header>*) stream)->data);
  val[scopeLen] = '\0';
  stream += sizeof(Header) + scopeLen;
  return val;
}

//template<class T>
//std::string dynamicAlloc(T& t)
//{
//}

//template<>
//std::string dynamicAlloc(int8_t& t)
//{
//  return "Int8";
//}

//template<>
//std::string dynamicAlloc(uint8_t& t)
//{
//  return "UnsignedInt8";
//}


#endif // PARSELYENGINE_H
