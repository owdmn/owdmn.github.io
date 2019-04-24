/**
 * delegate.h - c preprocessor macros introducing C#-ish delegate functionality
 * author: Oliver Wiedemann
 */

#ifndef __delegate_h__
#define __delegate_h__ 

#ifdef __GNUC__		/* GCC statement expressions */

#include <err.h>	/* err() */
#include <stddef.h>	/* NULL  */
#include <stdlib.h>	/* malloc() */

/* declare a <name>_t struct and a <name>_instance NULL pointer */
#define delegate(rtype, name, ...) typedef struct name ## _t {\
	rtype (*p)(__VA_ARGS__);\
	struct name ## _t *next;\
	} name ## _t;\
	name ## _t * name ## _instance = NULL;

/* append function pointer fp to linked list of delegate functions */
#define delegate_append(name, fp) do {\
		name ## _t **s = & name ## _instance;\
		for (; *s != NULL; s = &(*s)->next);\
		*s = malloc(sizeof( name ## _t));\
		if(!*s)\
			err(1, "malloc() failed appending name\n");\
		(*s)->p = fp;\
		(*s)->next = NULL;\
	} while(0)

/* remove the delgate at the end of the list in a clean way */
#define delegate_remove(name) do{\
		name ## _t **s = & name ## _instance;\
		name ## _t **t = s;\
		for (; (*s)->next != NULL; s = &(*s)->next)\
			t = s;\
		(*t)->next = NULL;\
		free(*s);\
	} while(0)


/** 
 * run all delegates - evaluates to return value of the last
 * enlisted delegate function
 */
#define delegate_run(name, ...) ({\
	name ## _t **s = & name ## _instance;\
	for (; *s != NULL; s = &(*s)->next) {\
		if((*s)->next)\
			(*s)->p(__VA_ARGS__);\
		else\
			break;\
	}\
	(*s)->p(__VA_ARGS__);\
	})

/* sequentially free the whole linked list */
#define delegate_free(name) do {\
	name ## _t *s = name ## _instance;\
	name ## _t *t;\
	for(;s != NULL; s = t) {\
		t = s->next;\
		free(s);\
	}\
	} while(0)


#endif //__GNUC__
#endif //__delegate_h__

