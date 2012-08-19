#include <stdio.h>

#define UINT_BIT	32

void uint_to_binary(unsigned int n, char s[UINT_BIT + 1]);

unsigned getbits(unsigned x, int p, int n);

unsigned setbits(unsigned x, int p, int n, unsigned y);

unsigned invert(unsigned x, int p, int n);

unsigned rightrot(unsigned x, int n);

int bitcount(unsigned x);

main()
{
	char binary[UINT_BIT + 1];
	unsigned int a, b, n;

	a = 0x01234567;
	b = 0xFEDCBA98;

	uint_to_binary(a, binary);
	printf("a\n%s\n", binary);
	uint_to_binary(b, binary);
	printf("b\n%s\n", binary);
	printf("getbits(a, 15, 6);\n");
	n = getbits(a, 15, 6);
	uint_to_binary(n, binary);
	printf("%s\n", binary);
	printf("setbits(a, 30, 10, b);\n");
	n = setbits(a, 30, 10, b);
	uint_to_binary(n, binary);
	printf("%s\n", binary);
	printf("invert(b, 29, 13);\n");
	n = invert(b, 29, 13);
	uint_to_binary(n, binary);
	printf("%s\n", binary);
	printf("rightrot(b, 5);\n");
	n = rightrot(b, 5);
	uint_to_binary(n, binary);
	printf("%s\n", binary);
	printf("%d 1 bits in a.\n", bitcount(a));
	printf("%d 1 bits in b.\n", bitcount(b));

	return 0;
}

void uint_to_binary(unsigned int n, char s[UINT_BIT + 1])
{
	unsigned int mask;
	int i;

	mask = 0x01 << UINT_BIT - 1;
	i = 0;
	while (mask != 0 && i < UINT_BIT) {
		if (n & mask)
			s[i] = '1';
		else
			s[i] = '0';
		mask >>= 1;
		i++;
	}
	s[i] = '\0';

	return;
}

/* getbits:  get n bits from position p */
unsigned getbits(unsigned x, int p, int n)
{
	return (x >> (p + 1 - n)) & ~(~0 << n);
}

/* setbits:  return x with the n bits at position p set to the
	rightmost n bits of y */
unsigned setbits(unsigned x, int p, int n, unsigned y)
{
	return (x & ~(~(~0 << n) << (p - n + 1)))
	       | ((y & ~(~0 << n)) << (p - n + 1));
}

/* invert:  return x with the n bits at position p inverted */
unsigned invert(unsigned x, int p, int n)
{
	return x ^ (~(~0 << n) << (p - n + 1));
}

/* rightrot:  return x rotated to the right n positions */
unsigned rightrot(unsigned x, int n)
{
	while (n > 0) {
		x = (x >> 1) | ((x & 1) << UINT_BIT - 1);
		n--;
	}

	return x;
}

/* bitcount:  count 1 bits in x */
int bitcount(unsigned x)
{
	int b;

	for (b = 0; x != 0; x &= (x - 1))
		b++;

	return b;
}
