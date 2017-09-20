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

struct rbtree *lookup_rbtree (struct rbtree *tree, int key)
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

void print_tree(struct rbtree *tree)
{
	struct rbtree *node = tree;

	if (node != NULL) {
		printf("%s\t", node->value);
		print_tree(node->left);
		print_tree(node->right);
		if (node->left == NULL && node->right == NULL) {
			printf("\n\t");
		}
	}
}