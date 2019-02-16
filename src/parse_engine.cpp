#include "parse_engine.h"



ParseEngine::ParseEngine(NetStack *ns)
  : m_net_stack(ns)
{
}





void ParseEngine::message(Packet *p)
{
  m_net_stack->write(encode(p));
}


