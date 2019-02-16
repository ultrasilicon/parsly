#pragma once

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



