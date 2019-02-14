#include <iostream>


#include "gtest/gtest.h"
#include "json.hpp"
#include "string.h"

#include "engine.h"

using namespace std;
using namespace nlohmann;

TEST(TestConstructStr, Cons1)
{
    char* s = "hello?";
    EXPECT_EQ("ell", string(constructStr(s + 1, s + 4)));
}


TEST(TestRedeemVal, SingleLayerPacket)
{
  char* s = "hello?";
  SizedMask<uint32_t> *m = new SizedMask<uint32_t>(s);
  char* stream = (char*) malloc(sizeof(m));
  EXPECT_EQ("hello?", string(redeemVal<uint32_t, char*>((char*) m)));
}

TEST(TestRedeemVal, MultiLayerPacket)
{
  char* s = "hello?";
  char* stream = (char*) malloc(sizeof(uint32_t) + sizeof(uint32_t) + strlen(s));
  char* pos = stream;

  int data = sizeof(uint32_t) + strlen(s);
  memcpy(pos, (char*)&data, sizeof(uint32_t));
  pos += sizeof(uint32_t);

  int data2 = strlen(s);
  memcpy(pos,  (char*)&data2, sizeof(uint32_t));
  pos += sizeof(uint32_t);

  strcpy(pos, s);
  pos += strlen(s);

  auto scope = getScope<uint32_t>((char*) stream);
  EXPECT_EQ(string("hello?"), string(redeemVal<uint32_t, char*>(scope)));
}

TEST(TestPlayground, Playground)
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
