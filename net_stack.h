#ifndef NET_STACK_H
#define NET_STACK_H

#include "packet.h"

class NetStack
{
public:
  NetStack();
  virtual int write(char* data);

protected:
};

#endif // NET_STACK_H
