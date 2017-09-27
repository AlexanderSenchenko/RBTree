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
struct rbtree *rbtree_delete(struct rbtree *tree, int key);
struct rbtree *rbtree_lookup (struct rbtree *tree, int key);
struct rbtree *rbtree_min (struct rbtree *tree);
struct rbtree *rbtree_max (struct rbtree *tree);
void rbtree_print_tree(struct rbtree *tree);
struct rbtree *rbtree_left_rotate(struct rbtree *node);
struct rbtree *rbtree_right_rotate(struct rbtree *node);
struct rbtree *rbtree_fixup(struct rbtree *tree, struct rbtree *node);

#endif
