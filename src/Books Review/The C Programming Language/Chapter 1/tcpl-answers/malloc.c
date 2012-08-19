#include <limits.h>
#include <stddef.h>
#include <string.h>

typedef long Align;	/* for alignment to long boundary */

union header {		/* block header */
	struct {
		union header *ptr;	/* next block if on free list */
		unsigned size;		/* size of this block */
	} s;
	Align x;		/* force alignment of blocks */
};

typedef union header Header;

static Header base;		/* empty list to get started */
static Header *freep = NULL;	/* start of free list */

static int size_is_plausible(unsigned size);

/* malloc:  general-purpose storage allocator */
void *malloc(unsigned nbytes)
{
	Header *p, *prevp;
	static Header *morecore(unsigned);
	unsigned nunits;

	if (!size_is_plausible(nbytes))
		return NULL;
	nunits = (nbytes+sizeof(Header)-1)/sizeof(Header) + 1;
	if ((prevp = freep) == NULL) {	/* no free list yet */
		base.s.ptr = freep = prevp = &base;
		base.s.size = 0;
	}
	for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
		if (p->s.size >= nunits) {	/* big enough */
			if (p->s.size == nunits)	/* exactly */
				prevp->s.ptr = p->s.ptr;
			else {				/* allocate tail end */
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;
			}
			freep = prevp;
			return (void *)(p+1);
		}
		if (p == freep)	/* wrapped around free list */
			if ((p = morecore(nunits)) == NULL)
				return NULL;	/* none left */
	}
}

#define NALLOC	1024	/* minimum #units to request */

/* morecore:  ask system for more memory */
static Header *morecore(unsigned nu)
{
	void free(void *ap);
	char *cp, *sbrk(int);
	Header *up;

	if (nu < NALLOC)
		nu = NALLOC;
	cp = sbrk(nu * sizeof(Header));
	if (cp == (char *) -1)	/* no space at all */
		return NULL;
	up = (Header *) cp;
	up->s.size = nu;
	free((void *)(up+1));
	return freep;
}

/* free:  put block ap in free list */
void free(void *ap)
{
	Header *bp, *p;

	if (ap == NULL)
		return;
	bp = (Header *)ap - 1;	/* point to block header */
	for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
		if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
			break;	/* freed block at start or end of arena */

	if (p < p->s.ptr && bp < p + p->s.size)
		/* bp is inside the previous block */
		return;
	if (p < p->s.ptr && bp + bp->s.size > p->s.ptr)
		/* bp's purported size extends into the next block */
		return;
	if (bp + bp->s.size == p->s.ptr) {	/* join to upper nbr */
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	} else
		bp->s.ptr = p->s.ptr;
	if (p + p->s.size == bp) {			/* join to lower nbr */
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	} else
		p->s.ptr = bp;
	freep = p;
}

void *calloc(int n, int size)
{
	void *p;

	p = malloc(n * size);
	if (p == NULL)
		return NULL;
	memset(p, 0, n * size);

	return p;
}

void bfree(void *p, unsigned n)
{
	Header *bp;
	unsigned nunits;

	bp = (Header *) p;
	nunits = n / sizeof(Header);
	if (nunits > 1) {
		/* at least one unit after the header */
		bp->s.size = nunits;
		free(bp + 1);
	}
}

#define PLAUSIBLITY_THRESHOLD (UINT_MAX / 2)

static int size_is_plausible(unsigned size)
{
	return size < PLAUSIBLITY_THRESHOLD;
}
