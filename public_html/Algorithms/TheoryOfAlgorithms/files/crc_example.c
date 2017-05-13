#include <stdio.h>
#include <stdint.h>
#include <string.h>


// typedef unsigned long  crc;
typedef uint32_t crc;

#define CRC_NAME			"CRC-32"
#define POLYNOMIAL			0x04C11DB7
#define INITIAL_REMAINDER	0xFFFFFFFF
#define FINAL_XOR_VALUE		0xFFFFFFFF
#define REFLECT_DATA		TRUE
#define REFLECT_REMAINDER	TRUE
#define CHECK_VALUE			0xCBF43926


#define WIDTH    (8 * sizeof(crc))
#define TOPBIT   (1 << (WIDTH - 1))

#if (REFLECT_DATA == TRUE)
#undef  REFLECT_DATA
#define REFLECT_DATA(X)			((unsigned char) reflect((X), 8))
#else
#undef  REFLECT_DATA
#define REFLECT_DATA(X)			(X)
#endif

#if (REFLECT_REMAINDER == TRUE)
#undef  REFLECT_REMAINDER
#define REFLECT_REMAINDER(X)	((crc) reflect((X), WIDTH))
#else
#undef  REFLECT_REMAINDER
#define REFLECT_REMAINDER(X)	(X)
#endif

unsigned long reflect(unsigned long data, unsigned char n_bits) {
  unsigned long  reflection = 0x00000000;
  unsigned char  bit;
  for (bit = 0; bit < n_bits; ++bit) {
    if (data & 0x1) {
      reflection |= (1 <<((n_bits - 1) - bit));
    }
    data >>= 1;
  }
  return (reflection);
}

crc  crc_table[256];

void CrcInit() {
  crc remainder;
  int dividend;
  unsigned char bit;
  // Compute the remainder of each possible dividend.
  for (dividend = 0; dividend < 256; ++dividend) {
    remainder = dividend << (WIDTH - 8);
    for (bit = 8; bit > 0; --bit) {
      if (remainder & TOPBIT) {
        remainder = (remainder << 1) ^ POLYNOMIAL;
      } else {
        remainder <<= 1;
      }
    }
    crc_table[dividend] = remainder;
  }
}

crc CrcFast(unsigned char const message[], int n_bytes) {
  crc remainder = INITIAL_REMAINDER;
  unsigned char data;
  int byte;
  for (byte = 0; byte < n_bytes; ++byte) {
    data = REFLECT_DATA(message[byte]) ^ (remainder >> (WIDTH - 8));
    remainder = crc_table[data] ^ (remainder << 8);
  }
  return (REFLECT_REMAINDER(remainder) ^ FINAL_XOR_VALUE);
}

int main() {
  printf("wid=%ld, top=0x%x\n", WIDTH, TOPBIT);
  unsigned char  test[] = "123456789";
  CrcInit();
  printf("The crcFast() of \"123456789\" is 0x%X\n", CrcFast(test, strlen(test)));
  return 0;
}
