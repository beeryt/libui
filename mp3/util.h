#pragma once

template <typename T>
T ntoh(T raw) {
  uint8_t* data = reinterpret_cast<uint8_t*>(&raw);
  T out = 0;
  int size = sizeof(T);
  for (int i = 0; i < size; ++i) {
    out |= ((T)data[size-i-1] << (i*8));
  }
  return out;
}

