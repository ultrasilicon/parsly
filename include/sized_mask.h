#ifndef SIZEMASK_H
#define SIZEMASK_H

#include <string.h>

#pragma pack(1)


//template <typename T>
//struct SizedMask {
//  T header;
//  char data[1];
//};

template <typename T>
struct SizedMask {
  SizedMask()
  {}

  SizedMask(char* dat)
    : data(dat)
  {
    header = (T)strlen(dat);
  }

  T header;
  char* data;
};



#endif // SIZEMASK_H
