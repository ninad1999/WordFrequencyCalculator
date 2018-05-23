#include "modified_gtree.h"
#include "gtree.h"
#include "gdsutils.h"

int print_dict(FILE *f, void *dp) {
	struct dict *dp2 = (struct dict *)dp;
	int val = -1;

	if (f && dp) {
		val = fprintf(f, "%s: %d\n", (dp2->item), (dp2->value));
	}

	return val;
}

int compare_str(void *px, void *py) {
	char *s = px;
	char *t = py;

	if (!s)
		printf("First argument is NULL.\n");

	if (!t)
		printf("Second argument is NULL.\n");

	return strcmp(s, t);
}

struct gtnode *insert_node(void *dp, struct gtnode *node, struct gtree *gtp) {
	struct dict *dp1 = (struct dict*)dp;

	if (node == NULL) {
		node = (struct gtnode *)malloc(sizeof(struct gtnode));
		dp1->value = 1;
		node->datum = dp1;
		node->left = NULL;
		node->right = NULL;
	} else {
		struct dict *dp2 = (struct dict*)node->datum;

		if (gtp->g_compare(dp1->item, dp2->item) < 0) {
			node->left = insert_node(dp, node->left, gtp);
		} else if (gtp->g_compare(dp1->item, dp2->item) > 0) {
			node->right = insert_node(dp, node->right, gtp);
		} else {
			dp2->value++;
		}
	}

	return node;
}

void tree_insert(void *dp, struct gtree *gtp) {
	gtp->root = insert_node(dp, gtp->root, gtp);
}

void free_datum(struct gtnode *gtnp) {
	if (gtnp) {
		struct dict *dp = (struct dict *)gtnp->datum;
		free_datum(gtnp->left);
		free_datum(gtnp->right);
		free(dp->item);
		free(gtnp->datum);
	}
}

void datum_destroy(struct gtree *gtp) {
	free_datum(gtp->root);
}
