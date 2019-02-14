#include <iostream>


#include "gtest/gtest.h"
#include "json.hpp"

#include "engine.h"

using namespace std;
using namespace nlohmann;

TEST(SizedMask, SingleLayerPacket)
{
  char s[] = "hello?";
  SizedMask<uint32_t> *m = new SizedMask<uint32_t>(s);
  char* stream = (char*) malloc(sizeof(m));
  EXPECT_EQ("hello?", string(redeemVal<uint32_t, char*>((char*) m)));
}

TEST(SizedMask, MultiLayerPacket)
{
  char s[] = "hello?";
  SizedMask<uint32_t> *m1 = new SizedMask<uint32_t>(s);
  SizedMask<uint32_t> *m2 = new SizedMask<uint32_t>();
  m2->data = (char*) malloc(sizeof (m1));
  strcpy(m2->data, (char*)m1);
  m2->header = sizeof (m1);
  printf("Data: %s\n\n", redeemVal<uint32_t, char*>(redeemVal<uint32_t, char*>((char*) m2)));
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
