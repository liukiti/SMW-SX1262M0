#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include "Arduino.h"

void convertLongInt2HexArray(long int, char *);
uint8_t *convertHexString2HexArray(char *, size_t, uint8_t *);
uint8_t dallas_crc8(const uint8_t *, const uint32_t);
void removeChar(char *, char);

#endif //__UTILS_HPP__