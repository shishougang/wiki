#define BITSPERINTEGER 32
#define SHIFT 5
#define MASK 0x1F
#define MAX_BITS 10000000

int array[1 + MAX_BITS / BITSPERINTEGER];

void set_bit(int i) {
  array[i >> SHIFT] |= (1 << (i & MASK));
}

void clr_bit(int i) {
  array[i >> SHIFT] &= ~(1 << (i & MASK));
}

int test_bit(int i) {
  return array[i >> SHIFT] & (1 << (i & MASK));
}
