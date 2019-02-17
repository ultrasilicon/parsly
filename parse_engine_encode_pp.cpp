#include "parse_engine.h"

#include "net_stack.h"
#include "packet.h"

#include "sized_mask.h"
#include "json.hpp"


char* ParseEngine::encode(Packet *packet)
{
    const auto msgType = packet->msgType;

//    sizeof()
//    char* stream = (char*) malloc(0
//                                  );

}
