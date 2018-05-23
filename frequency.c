#include "modified_gtree.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *readstr(FILE *fp) {
	char c;
	if (fscanf(fp, " %c", &c) != 1) return NULL; // ignore initial WS
	int maxlen = 1;
	int len = 1;
	char *str = malloc(maxlen * sizeof(char));
	if (isalpha(c))
		str[0] = c;
	while (1) {
		if (fscanf(fp, "%c", &c) != 1) break;
		if (c == ' ' || c == '\n') break;
		if (len == maxlen) {
			maxlen *= 2;
			str = realloc(str, maxlen * sizeof(char));
		}
		if (isalpha(c)) {
			++len;
			str[len - 1] = c;
		} else {
			continue;
		}
	}
	str = realloc(str, (len + 1) * sizeof(char));
	str[len] = '\0';

	if (!str)
		printf("Returning NULL.\n");

	return str;
}

void add_nodes(struct gtree *gtp) {
	char *str;
	
	struct dict *dp = NULL;
	FILE *fp = fopen("data.txt", "r");
	
	while(!feof(fp)) {
		str = readstr(fp);

		if (!str)
			printf("Trying to enter a null string.\n");
		else {
			dp = (struct dict *)malloc(sizeof(struct dict));

			dp->item = str;
			tree_insert(dp, gtp);
		}
	}

	fclose(fp);
}

int main(int argc, char *argv[], char *envp[]) {
	struct gtree *gtp = create_gtree(compare_str, print_dict);

	add_nodes(gtp);	
	print_preorder(gtp);

	datum_destroy(gtp);
	gtree_destroy(gtp);
}
	
