#include "RBTree.h"
#include <stdio.h>
#include <stdlib.h>

struct rbtree *rbtree_create_node (struct rbtree *node, struct rbtree *parent, int key, char *value) 
{
	node = malloc(sizeof(rbtree));
	if (node == NULL) {
		return NULL;
	}
	node->key = key;
	node->value = value;
	node->color = 0;
	node->left = NULL;
	node->right = NULL;
	node->parent = parent;
	return node;
}

struct rbtree *rbtree_add (struct rbtree *tree, int key, char *value)
{
		struct rbtree *node = tree, *parent = NULL;
		
		while (node != NULL) {
			parent = node;
			if (key < node->key) {
				node = node->left;
			} else if (key > node->key) {
				node = node->right;
			} else {
				return tree;
			}
		}

		node = rbtree_create_node(node, parent, key, value);
		if (node == NULL) {
			return tree;
		}

		if (tree == NULL) {
			tree = node;
		} else if (key < parent->key) {
			parent->left = node;
		} else if (key > parent->key) {
			parent->right = node;
		}

		tree = rbtree_fixup(tree, node);
		rbtree_print_tree(tree);
		printf("\n");

		return tree;
}

struct rbtree *rbtree_delete(struct rbtree *tree, int key)
{
	struct rbtree *node;//, *parent, *left, *right, *node_old;

	node = rbtree_lookup(tree, key);

	if (node->left == NULL && node->right == NULL) {
		if (node->parent != NULL && key < node->parent->key) {
			node->parent->left = NULL;
		} else if (node->parent!= NULL && key > node->parent->key) {
			node->parent->right = NULL;
		} else if (node->parent == NULL) {
			tree = NULL;
		}
	} else if (node->left != NULL && node->right == NULL) {
		if (node->parent != NULL && key < node->parent->key) {
			node->parent->left = node->left;
		} else if (node->parent != NULL && key > node->parent->key) {
			node->parent->right = node->left;
		} else if (node->parent == NULL) {
			tree = node->left;
		}
		node->left->parent = node->parent;
	} else if (node->right != NULL && node->left == NULL) {
		if (node->parent != NULL && key < node->parent->key) {
			node->parent->left = node->right;
		} else if (node->parent!= NULL && key > node->parent->key) {
			node->parent->right = node->right;
		} else if (node->parent == NULL) {
			tree = node->right;
		}
		node->right->parent = node->parent;
	} else if (node->left != NULL && node->right != NULL) {
		struct rbtree *node_old = node;
		node = node->right;

		while (node->left != NULL) {
			node = node->left;
		}

		node->left = node_old->left;
		if (node->parent != node_old) {
			node->parent->left = node->right;
			node->right = node_old->right;
		}

		if (node_old->parent != NULL && key < node_old->parent->key) {
			node_old->parent->left = node;
		} else if (node_old->parent!= NULL && key > node_old->parent->key) {
			node_old->parent->right = node;
		} else if (node_old->parent == NULL) {
			tree = node;
		}
	}
	return tree;
}

struct rbtree *rbtree_lookup (struct rbtree *tree, int key)
{
	struct rbtree *node = tree;

	while (node != NULL) {
		if (key == node->key) {
			return node;
		} else if (key < node->key) {
			node = node->left;
		} else if (key > node->key) {
			node = node->right;
		}
	}
	
	return node;
}

struct rbtree *rbtree_min (struct rbtree *tree)
{
	struct rbtree *node = tree;
	while (node->left != NULL) {
		node = node->left;
	}
	return node;
}

struct rbtree *rbtree_max (struct rbtree *tree)
{
	struct rbtree *node = tree;
	while (node->right != NULL) {
		node = node->right;
	}
	return node;
}

void rbtree_print_tree(struct rbtree *tree)
{
	struct rbtree *node = tree;
	if (node != NULL) {
		printf("%s\t%p\t", node->value, node);
		printf("%p\t", node->parent);
		if (node->parent == NULL) {
			printf("\t");
		}
		printf("%p\t", node->left);
		if (node->left == NULL) {
			printf("\t");
		}
		printf("%p\t", node->right);
		if (node->right == NULL) {
			printf("\t");
		}
		printf("%d\n", node->color);
		rbtree_print_tree(node->left);
		rbtree_print_tree(node->right);
	}
}

struct rbtree *rbtree_fixup(struct rbtree *tree, struct rbtree *node)
{
	struct rbtree *fix;
	while (node->parent != NULL && node->parent->color == 0) {
		if (node->parent == node->parent->parent->left) {
			struct rbtree *uncle = node->parent->parent->right;
			if (uncle != NULL && uncle->color == 0) {
				node->parent->color = 1;
				uncle->color = 1;
				node->parent->parent->color = 0;
				node = node->parent->parent;
			} else {
				if (node == node->parent->right) {
					node = node->parent;
					fix = rbtree_left_rotate(node);
					if (fix->parent == NULL) {
						tree = fix;
						//printf("%d\n", tree->key);
					}
				}
				node->parent->color = 1;
				node->parent->parent->color = 0;
				fix = rbtree_right_rotate(node->parent->parent);
				if (fix->parent == NULL) {
					tree = fix;
					//printf("%d\n", tree->key);
				}
			}
		} else {
			struct rbtree *uncle = node->parent->parent->left;
			if (uncle != NULL && uncle->color == 0) {
				node->parent->color = 1;
				node->parent->parent->color = 0;
				uncle->color = 1;
				node = node->parent->parent;
			} else {
				if (node == node->parent->left) {
					node = node->parent;
					fix = rbtree_right_rotate(node);

					if (fix->parent == NULL) {
						tree = fix;
						//printf("%d\n", tree->key);
					}
				}
				node->parent->color = 1;
				node->parent->parent->color = 0;
				fix = rbtree_left_rotate(node->parent->parent);
				if (fix->parent == NULL) {
					tree = fix;
					//printf("%d\n", tree->key);
				}
			}
		}
	}
	tree->color = 1;
	return tree;
}

struct rbtree *rbtree_left_rotate(struct rbtree *node)
{
	struct rbtree *node_right;

	node_right = node->right;
	node->right = node_right->left;

	if (node_right->left != NULL) {
		node_right->left->parent = node;
	}

	node_right->parent = node->parent;

	if (node->parent != NULL) {
		if (node == node->parent->left) {
			node->parent->left = node_right;
		} else if (node == node->parent->right) {
			node->parent->right = node_right;
		}
	}

	node_right->left = node;
	node->parent = node_right;

	return node_right;
}

struct rbtree *rbtree_right_rotate(struct rbtree *node)
{
	struct rbtree *node_left;

	node_left = node->left;
	node->left = node_left->right;

	if (node_left->right != NULL) {
		node_left->right->parent = node;
	}

	node_left->parent = node->parent;

	if (node->parent != NULL) {
		if (node == node->parent->left) {
			node->parent->left = node_left;
		} else if (node == node->parent->right) {
			node->parent->right = node_left;
		}
	}

	node_left->right = node;
	node->parent = node_left;

	return node_left;
}
