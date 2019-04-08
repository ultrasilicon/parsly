#pragma once

#pragma pack(1)

template <typename T>
struct SizedMask {
  T header;
  char* data;
};

#pragma pack()



