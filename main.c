#include <stdio.h>
#include <stdlib.h>
#include "RBTree.h"

int main(int argc, char *argv[])
{
	struct rbtree *tree = NULL;//, *node = NULL;
	int key_del = atoi(argv[1]);

	tree = rbtree_add(tree, 10, "10");
	tree = rbtree_add(tree, 5, "5");
	tree = rbtree_add(tree, 3, "3");
	tree = rbtree_add(tree, 12, "12");
	tree = rbtree_add(tree, 11, "11");
	tree = rbtree_add(tree, 6, "6");
	tree = rbtree_add(tree, 8, "8");
	tree = rbtree_add(tree, 9, "9");

	printf("Delete:\n");
	tree = rbtree_delete(tree, key_del);
	rbtree_print_tree(tree);
	printf("\n");
	printf("key\tnode\t\tparent\t\tleft\t\treght\t\tcolor\n");

	return 0;
}