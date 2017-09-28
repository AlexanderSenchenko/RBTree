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
	struct rbtree *node, *parent, *left, *right, *node_look, *node_look_left, *node_look_right;
	int flag = 1;

	node = rbtree_lookup(tree, key);

	left = node->left;
	right = node->right;

	while (flag == 1) {
		flag = 0;
		parent = node->parent;

		if (left == NULL && right == NULL) {
			if (parent != NULL && key < parent->key) {
				parent->left = NULL;
			} else if (parent!= NULL && key > parent->key) {
				parent->right = NULL;
			} else if (parent == NULL) {
				tree = NULL;
			}
		} else if (left != NULL && right == NULL) {
			if (parent != NULL && key < parent->key) {
				parent->left = left;
			} else if (parent!= NULL && key > parent->key) {
				parent->right = left;
			} else if (parent == NULL) {
				tree = left;
			}
			left->parent = parent;
		} else if (right != NULL && left == NULL) {
			if (parent != NULL && key < parent->key) {
				parent->left = right;
			} else if (parent!= NULL && key > parent->key) {
				parent->right = right;
			} else if (parent == NULL) {
				tree = right;
			}
			right->parent = parent;
		} else if (left != NULL && right != NULL && right->left == NULL) {
			if (parent != NULL && key < parent->key) {
				parent->left = right;
			} else if (parent!= NULL && key > parent->key) {
				parent->right = right;
			} else if (parent == NULL) {
				tree = right;
			}
			right->left = left;
			left->parent = right;
			right->parent = parent;
		} else if (left != NULL && right != NULL) {
			node_look = right;
			while (node_look->left == NULL) {
				node_look = node_look->right;
			}
			node = node_look->left;

			if (parent != NULL && key < parent->key) {
				parent->left = node;
			} else if (parent!= NULL && key > parent->key) {
				parent->right = node;
			} else if (parent == NULL) {
				tree = node;
			}

			node_look_left = node_look->left->left;
			node_look_right = node_look->left->right;

			node_look->left->left = left;
			node_look->left->right = right;

			left = node_look_left;
			right = node_look_right;
			flag = 1;
		}
	}

	tree = rbtree_fixup(tree, node);
	//rbtree_print_tree(tree);
	//printf("\n");

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
		printf("%s\t%p\t%p\t%p\t%p\t%d\n", node->value, node, node->parent, node->left, node->right, node->color);
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
