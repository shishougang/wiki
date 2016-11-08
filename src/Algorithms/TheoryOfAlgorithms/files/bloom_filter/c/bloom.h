#ifndef __BLOOM_H__
#define __BLOOM_H__

#include <stdlib.h>
typedef unsigned int (*hashfunc_t)(const char *);

typedef struct{
  size_t size;
  unsigned char *a;
  size_t nhashfuncs;
  hashfunc_t *hashfuncs;
} BLOOM;

BLOOM *bloom_create(size_t size, size_t nhashfuncs, ...);
int bloom_destroy(BLOOM *bloom);
int bloom_add(BLOOM *bloom, const char *s);
int bloom_check(BLOOM *bloom, const char *s);

#endif
