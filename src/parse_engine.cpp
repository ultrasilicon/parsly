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

  char* mobilePtr = stream + sizeof(uint32_t);
  char* end = scopeEnd<uint32_t>(stream);

  uint32_t contentSize = ((SizedMask <uint32_t>*) stream)->header;

  if(size < contentSize - sizeof(uint32_t))
    {
      std::printf("ParselyEngine: Returning - Packet Imcomplete");
      return nullptr;
    }


  //! Header detected & Packet complete
  auto msgType = redeemVal<uint8_t>(mobilePtr, end);

  switch (msgType) {
    case 0: // HeartBeat
      {
      //      __TYPE __FIELD_NAME(redeemVal<__TYPE_ARGS>(mobilePtr));

        std::string uuid(redeemVal<pe_str_len_t, char*>(mobilePtr, end));
        std::string usrName(redeemVal<pe_str_len_t, char*>(mobilePtr, end));
        std::string publicKey(redeemVal<pe_str_len_t, char*>(mobilePtr, end));
        uint32_t timestamp(redeemVal<uint32_t>(mobilePtr, end));

        break;
      }
    case 1: // ConnectionInfo
      {
        std::string uuid(redeemVal<pe_str_len_t, char*>(mobilePtr, end));
        std::string peers(redeemVal<pe_str_len_t, char*>(mobilePtr, end));

        break;
      }
    case 2: // TextMessage
      {
        std::string uuid(redeemVal<pe_str_len_t, char*>(mobilePtr, end));
        std::string msgId(redeemVal<pe_str_len_t, char*>(mobilePtr, end));
        std::string msg(redeemVal<pe_str_len_t, char*>(mobilePtr, end));

        break;
      }
    case 3: // ImageMessage
      {
        std::string uuid(redeemVal<pe_str_len_t, char*>(mobilePtr, end));
        std::string msgId(redeemVal<pe_str_len_t, char*>(mobilePtr, end));
        char* msg(redeemVal<pe_str_len_t, char*>(mobilePtr, end));

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


