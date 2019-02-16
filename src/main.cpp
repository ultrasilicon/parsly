#include <iostream>


#include "gtest/gtest.h"

#include "json.hpp"
#include "string.h"

#include "parse_engine.h"

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

  uint32_t header;

  header =
      sizeof(uint32_t) + strlen(s) // first cell
      ;
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

TEST(TestRedeemVal, MultiLayerMultiCellPacket)
{
  //! [19:[6:hello?][5:world]]
  char* s1 = "hello?";
  char* s2 = "world";
  char* stream = (char*) malloc(sizeof(uint32_t) // main header
                                + sizeof(uint32_t) + strlen(s1) // cell1 total
                                + sizeof(uint32_t) + strlen(s2) // cell2 total
                                );
  char* pos = stream;

  uint32_t header;

  header = // main header
      sizeof(uint32_t) + strlen(s1) // cell1 total
      + sizeof(uint32_t) + strlen(s2) // cell2 total
      ;
  memcpy(pos, (char*)&header, sizeof(uint32_t));
  pos += sizeof(header);

  // cell1 header
  header = strlen(s1);
  memcpy(pos,  (char*)&header, sizeof(uint32_t));
  pos += sizeof(header);

  // cell1 data
  strcpy(pos, s1);
  pos += strlen(s1);

  // cell2 header
  header = strlen(s2);
  memcpy(pos,  (char*)&header, sizeof(uint32_t));
  pos += sizeof(header);

  // cell1 data
  strcpy(pos, s2);
  pos += strlen(s2);


  auto p = scopeBegin<uint32_t>(stream);
  EXPECT_EQ(string("hello?"), string(redeemVal<uint32_t, char*>(p)));
  EXPECT_EQ(string("world"), string(redeemVal<uint32_t, char*>(p)));
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
