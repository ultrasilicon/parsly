#include <iostream>


#include "gtest/gtest.h"
#include "json.hpp"

#include "engine.h"

using namespace std;
using namespace nlohmann;

TEST(redeemVal, SingleLayerPacket)
{
  char s[] = "hello?";
  SizedMask<uint32_t> *m = new SizedMask<uint32_t>(s);
  char* stream = (char*) malloc(sizeof(m));
  EXPECT_EQ("hello?", string(redeemVal<uint32_t, char*>((char*) m)));
}

TEST(redeemVal, MultiLayerPacket)
{
  char* s = "hello?";
  int Ssize = strlen(s);
  char* stream = (char*) malloc(sizeof(uint32_t) + sizeof(uint32_t) + strlen(s));
  int data = sizeof(uint32_t) + strlen(s);
  memcpy(stream, (char*)&data, sizeof(uint32_t));
  stream += sizeof(uint32_t);
  int data2 = strlen(s);
  memcpy(stream,  (char*)&data2, sizeof(uint32_t));
  stream += sizeof(uint32_t);
  memcpy(stream, s, strlen(s));

//  printf("Data: %s\n\n", redeemVal<uint32_t, char*>(redeemVal<uint32_t, char*>((char*) m2)));
//  EXPECT_EQ(string("hello?"), string(redeemVal<uint32_t, char*>((char*) m1)));
}

TEST(Playground, Playground)
{
  //! JSON example
  json field1Json = json::array({"time", "uuid", "content", "pubkey"});
  json packetJson = json::array({0, field1Json});
}


int main(int argc, char **argv  )
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
