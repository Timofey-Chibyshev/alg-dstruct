#include "TreePlus.h"

tree_t* InitNode(tree_t* brother, int key, tree_t* pointer)
{
	tree_t* res = (tree_t*)malloc(sizeof(tree_t));
	if (res)
	{
		res->full = false;
		res->key[0] = key;
		res->son[0] = pointer;
		if (brother)
		{
			if ((res->height = brother->height))
			{
				res->son[0]->parent = res;
			}
			res->parent = brother->parent;
			res->son[2] = brother->son[2];
			brother->son[2] = res;
		}
		else
		{
			res->height = 0;
			res->parent = NULL;
			res->son[2] = NULL;
		}
	}
	return res;
}

tree_t* SearchNode(tree_t* tree, int key)
{
	if (!tree)
	{
		return NULL;
	}
	tree_t* cur = tree;
	while (cur->height)
	{
		if (key <= cur->key[0])
		{
			cur = cur->son[0];
		}
		else if (cur->full && key > cur->key[1])
		{
			cur = cur->son[2];
		}
		else
		{
			cur = cur->son[1];
		}
	}
	return cur;
}

bool FindNode(tree_t* tree, int key)
{
	if (!tree)
	{
		return false;
	}
	tree_t* leaf = SearchNode(tree, key);
	if (key == leaf->key[0] || (leaf->full && key == leaf->key[1]))
	{
		return true;
	}
	return false;
}

tree_t* Root(tree_t* node)
{
	tree_t* cur = node;
	while (cur->parent)
	{
		cur = cur->parent;
	}
	return cur;
}

void LeafInsert(tree_t* node, int key, tree_t* pointer)
{
	if (key > node->key[0])
	{
		node->key[1] = key;
		node->son[1] = pointer;
	}
	else
	{
		node->key[1] = node->key[0];
		node->son[1] = node->son[0];
		node->key[0] = key;
		node->son[0] = pointer;
	}
}

tree_t* Insert(tree_t* tree, int key, tree_t* pointer)
{
	if (!tree)
	{
		return InitNode(NULL, key, pointer);
	}
	tree_t* leaf = SearchNode(tree, key);
	if (key == leaf->key[0] || (leaf->full && key == leaf->key[1]))
	{
		return tree;
	}
	if (!leaf->full)
	{
		LeafInsert(leaf, key, pointer);
		leaf->full = true;
		return tree;
	}
	else
	{
		if (key < leaf->key[0])
		{
			tree_t* next = InitNode(leaf, leaf->key[1], leaf->son[1]);
			if (!next)
			{
				DestroyTree(tree);
				return NULL;
			}
			LeafInsert(leaf, key, pointer);
			return SplitParent(leaf, leaf->key[1]);
		}
		else if (key < leaf->key[1])
		{
			tree_t* next = InitNode(leaf, leaf->key[1], leaf->son[1]);
			if (!next)
			{
				DestroyTree(tree);
				return NULL;
			}
			LeafInsert(leaf, key, pointer);
			return SplitParent(leaf, key);
		}
		else
		{
			tree_t* next = InitNode(leaf, key, pointer);
			if (!next)
			{
				DestroyTree(tree);
				return NULL;
			}
			return SplitParent(leaf, leaf->key[1]);
		}
	}
}

tree_t* SplitParent(tree_t* son, int key)
{
	tree_t* node = son->parent;
	if (!node)
	{
		node = InitNode(NULL, key, son);
		if (!node)
		{
			DestroyTree(son->son[2]);
			DestroyTree(son);
			return NULL;
		}
		node->height = son->height + 1;
		node->son[1] = son->son[2];
		son->son[2] = NULL;
		son->parent = node;
		node->son[1]->parent = node;
		return node;
	}
	if (!node->full)
	{
		if (key > node->key[0])
		{
			node->key[1] = key;
			node->son[2] = son->son[2];
			node->son[2]->parent = node;
			son->son[2] = NULL;
		}
		else
		{
			node->key[1] = node->key[0];
			node->son[2] = node->son[1];
			node->key[0] = key;
			node->son[1] = son->son[2];
			node->son[1]->parent = node;
			son->son[2] = NULL;
		}
		node->full = true;
	}
	else
	{
		if (key < node->key[0])
		{
			tree_t* next = InitNode(node, node->key[1], node->son[1]);
			if (!next)
			{
				DestroyTree(son->son[2]);
				DestroyTree(Root(node));
				return NULL;
			}
			node->full = false;
			node->key[1] = 0;
			next->son[1] = next->son[2];
			next->son[2] = NULL;
			next->son[1]->parent = next;
			int old_key = node->key[0];
			node->key[0] = key;
			node->son[1] = son->son[2];
			son->son[2] = NULL;
			return SplitParent(node, old_key);
		}
		else if (key < node->key[1])
		{
			tree_t* next = InitNode(node, node->key[1], son->son[2]);
			if (!next)
			{
				DestroyTree(son->son[2]);
				DestroyTree(Root(node));
				return NULL;
			}
			node->full = false;
			node->key[1] = 0;
			next->son[1] = next->son[2];
			next->son[1]->parent = next;
			next->son[2] = NULL;
			son->son[2] = NULL;
			return SplitParent(node, key);
		}
		else
		{
			tree_t* next = InitNode(node, key, node->son[2]);
			if (!next)
			{
				DestroyTree(son->son[2]);
				DestroyTree(Root(node));
				return NULL;
			}
			node->full = false;
			int old_key = node->key[1];
			node->key[1] = 0;
			next->son[1] = son->son[2];
			next->son[2] = NULL;
			next->son[1]->parent = next;
			son->son[2] = NULL;
			return SplitParent(node, old_key);
		}
	}
	return Root(node);
}

void DestroyTree(tree_t* root)
{
	if (root)
	{
		if (root->height)
		{
			DestroyTree(root->son[0]);
			DestroyTree(root->son[1]);
			if (root->full)
			{
				DestroyTree(root->son[2]);
			}
		}
		free(root);
	}
}

void PrintTree(tree_t* tree, int offset)
{
	if (!tree)
	{
		return;
	}
	if (!tree->height)
	{
		if (offset > 0)
		{
			for (int i = 0; i < offset; i++)
			{
				printf(" ");
			}
		}
		printf("[%2d", tree->key[0]);
		if (tree->full)
		{
			printf(", %2d", tree->key[1]);
		}
		printf("]\n");
	}
	else
	{
		PrintTree(tree->son[0], offset + 2);
		if (!tree->full)
		{
			if (offset > 0)
			{
				for (int i = 0; i < offset; i++)
				{
					printf(" ");
				}
			}
			printf("%2d\n", tree->key[0]);
			PrintTree(tree->son[1], offset + 2);
		}
		else
		{
			for (int i = 0; i < offset; i++)
			{
				printf(" ");
			}
			printf("%2d\n", tree->key[0]);
			PrintTree(tree->son[1], offset + 2);
			for (int i = 0; i < offset; i++)
			{
				printf(" ");
			}
			printf("%2d\n", tree->key[1]);
			PrintTree(tree->son[2], offset + 2);
		}
	}
}

tree_t* MergeTree(tree_t* left, tree_t* right)
{
	if (!left)
	{
		return right;
	}
	if (!right)
	{
		return left;
	}
	if (left->height == right->height)
	{
		tree_t* leftParent = left->parent;
		tree_t* rightParent = right->parent;
		int lmax;
		tree_t* cur = left;
		while (cur->height)
		{
			cur = (!cur->full) ? cur->son[1] : cur->son[2];
		}
		lmax = (!cur->full) ? cur->key[0] : cur->key[1];
		if (leftParent)
		{
			right->parent = leftParent;
			if (!leftParent->full)
			{
				leftParent->key[1] = lmax;
				leftParent->son[2] = right;
				leftParent->full = true;
				return Root(leftParent);
			}
			else
			{
				tree_t* next = InitNode(leftParent, lmax, left);
				if (!next)
				{
					return NULL;
				}
				next->son[1] = right;
				right->parent = next;
				next->son[2] = NULL;
				leftParent->full = false;
				return SplitParent(leftParent, leftParent->key[1]);
			}
		}
		else if (rightParent)
		{
			left->parent = rightParent;
			if (!rightParent->full)
			{
				rightParent->key[1] = rightParent->key[0];
				rightParent->son[2] = rightParent->son[1];
				rightParent->son[1] = rightParent->son[0];

				rightParent->key[0] = lmax;
				rightParent->son[0] = left;
				rightParent->full = true;
				return Root(rightParent);
			}
			else
			{
				tree_t* next = InitNode(rightParent, rightParent->key[1], rightParent->son[1]);
				if (!next)
				{
					return NULL;
				}
				rightParent->full = false;
				next->son[1] = next->son[2];
				next->son[1]->parent = next;
				next->son[2] = NULL;
				int old_key = rightParent->key[0];
				rightParent->son[1] = rightParent->son[0];
				rightParent->son[0] = left;
				rightParent->key[0] = lmax;
				return SplitParent(rightParent, old_key);
			}
		}
		else
		{
			tree_t* tree = InitNode(NULL, lmax, left);
			if (!tree)
			{
				return NULL;
			}
			tree->height = left->height + 1;
			tree->son[1] = right;
			left->parent = tree;
			right->parent = tree;
			return tree;
		}
	}
	if (left->height < right->height)
	{
		return MergeTree(left, right->son[0]);
	}
	else
	{
		return MergeTree((!left->full) ? left->son[1] : left->son[2], right);
	}
}

tree_t* Extract(tree_t** ptr)
{
	tree_t* res = *ptr;
	*ptr = NULL;
	res->parent = NULL;
	return res;
}

tree_t* SplitTree(tree_t* tree, int key, tree_t** pLeft, tree_t** pRight)
{
	if (tree)
	{
		if (tree->height)
		{
			tree_t* left = Extract(&tree->son[0]);
			tree_t* mid = Extract(&tree->son[1]);
			tree_t* right = NULL;
			if (tree->full)
			{
				right = Extract(&tree->son[2]);
			}
			if (key <= tree->key[0])
			{
				if (right)
				{
					*pRight = MergeTree(right, *pRight);
				}
				*pRight = MergeTree(mid, *pRight);
				free(tree);
				return SplitTree(left, key, pLeft, pRight);
			}
			*pLeft = MergeTree(*pLeft, left);
			if (tree->full && key > tree->key[1])
			{
				*pLeft = MergeTree(*pLeft, mid);
				free(tree);
				return SplitTree(right, key, pLeft, pRight);
			}
			if (right)
			{
				*pRight = MergeTree(right, *pRight);
			}
			free(tree);
			return SplitTree(mid, key, pLeft, pRight);
		}
		if (key < tree->key[0])
		{
			*pRight = Insert(*pRight, tree->key[0], tree->son[0]);
			if (tree->full)
			{
				*pRight = Insert(*pRight, tree->key[1], tree->son[1]);
			}
			free(tree);
			return NULL;
		}
		if (key == tree->key[0])
		{
			if (tree->full)
			{
				*pRight = Insert(*pRight, tree->key[1], tree->son[1]);
			}
			tree->parent = NULL;
			tree->key[1] = 0;
			tree->son[1] = NULL;
			return tree;
		}
		*pLeft = Insert(*pLeft, tree->key[0], tree->son[0]);
		if (tree->full && key < tree->key[1])
		{
			*pRight = Insert(*pRight, tree->key[1], tree->son[1]);
			free(tree);
			return NULL;
		}
		if (tree->full && key == tree->key[1])
		{
			tree->parent = NULL;
			tree->key[0] = key;
			tree->son[0] = tree->son[1];
			tree->key[1] = 0;
			tree->son[1] = NULL;
			tree->full = false;
			return tree;
		}
		if (tree->full)
		{
			*pLeft = Insert(*pLeft, tree->key[1], tree->son[1]);
		}
		free(tree);
		return NULL;
	}
	return NULL;
}

tree_t* Remove(tree_t* tree, int key)
{
	tree_t* left = NULL;
	tree_t* right = NULL;
	if (!FindNode(tree, key))
	{
		return tree;
	}
	tree_t* m = SplitTree(tree, key, &left, &right);
	free(m);
	return MergeTree(left, right);
}