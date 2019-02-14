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
    EXPECT_EQ("ell", string(constructStr(s + 1, 3)));
}


TEST(TestRedeemVal, SingleLayerPacket)
{
  //! [6:hello?]
  char* s = "hello?";
  char* stream = (char*) malloc( sizeof(uint32_t) + strlen(s) );
  char* pos = stream;

  auto header = strlen(s);
  memcpy(pos, (char*)&header, sizeof(uint32_t));
  pos += sizeof(uint32_t);

  strcpy(pos, s);
  pos += strlen(s);

  EXPECT_EQ("hello?", string(redeemVal<uint32_t, char*>(stream)));
}

TEST(TestRedeemVal, MultiLayerPacket)
{
  //! [10:[6:hello?]]
  char* s = "hello?";
  char* stream = (char*) malloc( sizeof(uint32_t) + sizeof(uint32_t) + strlen(s) );
  char* pos = stream;

  long header;

  header = sizeof(uint32_t) + strlen(s);
  memcpy(pos, (char*)&header, sizeof(uint32_t));
  pos += sizeof(uint32_t);

  header = strlen(s);
  memcpy(pos,  (char*)&header, sizeof(uint32_t));
  pos += sizeof(uint32_t);

  strcpy(pos, s);
  pos += strlen(s);

  auto begin = scopeBegin<uint32_t>(stream);
  EXPECT_EQ(string("hello?"), string(redeemVal<uint32_t, char*>(begin)));
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
