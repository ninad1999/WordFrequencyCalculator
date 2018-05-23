#ifndef _MODIFIED_GTREE_H_
#define _MODIFIED_GTREE_H_

#include "gdsutils.h"
#include "gtree.h"

struct dict {
	char *item;
	int value;
};

int print_dict(FILE *f, void *dp) ;
int compare_str(void *px, void *py) ;
void tree_insert(void *dp, struct gtree *gtp) ;
void datum_destroy(struct gtree *gtp) ;

#endif
