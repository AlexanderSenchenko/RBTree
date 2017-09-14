#ifndef "RBTREE"
#define "RBTREE"

typedef struct rbtree {
	int key;
	char *value;
	int color;//0 - red, 1 - black
	struct tree *right;
	struct tree *left;
	struct tree *parent;
} rbtree;

#endif
