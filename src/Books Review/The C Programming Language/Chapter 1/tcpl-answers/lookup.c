#include <stdlib.h>
#include <string.h>

unsigned hash(char *s);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
void undef(char *);

struct nlist {		/* table entry: */
	struct nlist *next;	/* next entry in chain */
	char *name;			/* defined name */
	char *defn;			/* replacement text */
};

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE];	/* pointer table */

/* hash:  form hash value for string s */
unsigned hash(char *s)
{
	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

/* lookup:  look for s in hashtab */
struct nlist *lookup(char *s)
{
	struct nlist *np;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np;	/* found */
	return NULL;		/* not found */
}

/* install:  put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL) {	/* not found */
		np = (struct nlist *) malloc(sizeof(*np));
		if (np == NULL || (np->name = strdup(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else		/* already there */
		free((void *) np->defn);	/* free previous defn */
	if ((np->defn = strdup(defn)) == NULL)
		return NULL;
	return np;
}

/* undef:  remove name from hashtab */
void undef(char *name)
{
	struct nlist *np, **prev;
	unsigned hashval;

	hashval = hash(name);
	for (np = hashtab[hashval], prev = &hashtab[hashval]; np != NULL; prev = &np->next, np = np->next) {
		if (strcmp(name, np->name) == 0) {
			*prev = np->next;
			free(np->name);
			free(np->defn);
			free(np);
			break;
		}
	}

	return;
}
