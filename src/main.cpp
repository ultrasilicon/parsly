#include <iostream>

#include "engine.h"

#include "json.hpp"

using namespace std;
using namespace nlohmann;


int main()
{
  //! JSON example
  json field1Json = json::array({"time", "uuid", "content", "pubkey"});
  json packetJson = json::array({0, field1Json});

  //! Playground
  char s[] = "hello?";
  SizedMask<uint32_t> *scp = new SizedMask<uint32_t>(s);
  char* stream = (char*) malloc(sizeof(scp));
  printf("Data: %s\n\n", redeemVal<uint32_t, char*>((char*) scp));

  return 0;
}
