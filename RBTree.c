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

		return tree;
}

struct rbtree *rbtree_delete(struct rbtree *tree, int key)
{
	struct rbtree *node, *parent, *left, *right;

	node = rbtree_lookup(tree, key);

	parent = node->parent;
	left = node->left;
	right = node->right;

	if (left != NULL && left->key < parent->key) {
		parent->left = left;
		left->right = right;
	} else if (right != NULL && right->key > parent->key) {
		parent->right = right;
		right->left = left;
	} else {
		if (key < parent->key) {
			parent->left = NULL;
		} else if (key > parent->key) {
			parent->right = NULL;
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

struct rbtree *rbtree_min (struct rbtree *tree) {
	struct rbtree *node = tree;

	while (node->left != NULL) {
		node = node->left;
	}

	return node;
}

struct rbtree *rbtree_max (struct rbtree *tree) {
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
		printf("%s\t", node->value);
		rbtree_print_tree(node->left);
		rbtree_print_tree(node->right);
		/*if (node->left == NULL && node->right == NULL) {
			printf("\n\t");
		}*/
	}
}
