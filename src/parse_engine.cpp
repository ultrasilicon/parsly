#include "parse_engine.h"



ParseEngine::ParseEngine(NetStack *ns)
  : m_net_stack(ns)
{
}

char* ParseEngine::encode(Packet *packet)
{

}


Packet* ParseEngine::decode(char* stream, const uint32_t &size) //<< WARN return value is nulled
{
  std::printf("ParselyEngine: New Data Section !!");
  if(size == 0 || size < (int) sizeof (uint32_t))
    {
      std::printf("ParselyEngine: Returning - Header Not Complete / Empty Packet");
      return nullptr;
    }

  uint32_t contentSize = ((SizedMask <uint32_t>*) stream)->header;

  if(size < contentSize - sizeof(uint32_t))
    {
      std::printf("ParselyEngine: Returning - Packet Imcomplete");
      return nullptr;
    }


  //! Header detected & Packet complete

  char* mobilePtr = stream + sizeof(uint32_t);

  auto msgType = redeemVal<uint8_t>(mobilePtr);

  switch (msgType) {
    case 0: // HeartBeat
      {
        std::string uuid(redeemVal<pe_str_len_t, char*>(mobilePtr));
        std::string usrName(redeemVal<pe_str_len_t, char*>(mobilePtr));
        std::string publicKey(redeemVal<pe_str_len_t, char*>(mobilePtr));
        uint32_t timestamp(redeemVal<uint32_t>(mobilePtr));

        break;
      }
    case 1: // ConnectionInfo
      {
        std::string uuid(redeemVal<pe_str_len_t, char*>(mobilePtr));
        std::string peers(redeemVal<pe_str_len_t, char*>(mobilePtr));

        break;
      }
    case 2: // TextMessage
      {
        std::string uuid(redeemVal<pe_str_len_t, char*>(mobilePtr));
        std::string msgId(redeemVal<pe_str_len_t, char*>(mobilePtr));
        std::string msg(redeemVal<pe_str_len_t, char*>(mobilePtr));

        break;
      }
    case 3: // ImageMessage
      {
        std::string uuid(redeemVal<pe_str_len_t, char*>(mobilePtr));
        std::string msgId(redeemVal<pe_str_len_t, char*>(mobilePtr));
        char* msg(redeemVal<pe_str_len_t, char*>(mobilePtr));

        break;
      }
    default:
      {
        break;
      }
    }
  return nullptr;
}

void ParseEngine::message(Packet *p)
{
  m_net_stack->write(encode(p));
}


