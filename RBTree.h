#ifndef RBTREE_H
#define RBTREE_H

typedef struct rbtree {
	int key;
	char *value;
	int color;//0 - red, 1 - black
	struct rbtree *right;
	struct rbtree *left;
	struct rbtree *parent;
} rbtree;

struct rbtree *rbtree_create (struct rbtree *node, struct rbtree *parent, int key, char *value);
struct rbtree *rbtree_add (struct rbtree *tree, int key, char *value);
struct rbtree *lookup_rbtree (struct rbtree *tree, int key);
void print_tree(struct rbtree *tree);

#endif