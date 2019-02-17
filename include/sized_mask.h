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
  T header;
  char* data;
};



