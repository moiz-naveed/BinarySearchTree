/**************************************
Binary Tree API
Author:  Moiz Naveed
November, 2017
**************************************/
#include "BinarySearchTreeAPI.h"
#include <stdio.h>
#include <stdlib.h>
#include "Assistant.h"

TreeNode *createTreeNode(TreeDataPtr data)
{
	TreeNode *temp = malloc(sizeof(TreeNode));
	temp->data = data;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

Tree *createBinTree(CompareFunc compare, DeleteFunc del)
{
	Tree *newTree = malloc(sizeof(Tree));
	newTree->root = NULL;
	newTree->compareFunc = compare;
	newTree->deleteFunc = del;
	return newTree;
}

void destroyBinTree(Tree *toDestroy)
{
	deleteTreeData(toDestroy->root);
	free(toDestroy);
	toDestroy = NULL;
}
void deleteTreeData(TreeNode *node)
{
	if (node == NULL)
		return;
	if (node->left != NULL)
		deleteTreeData(node->left);
	if (node->right != NULL)
		deleteTreeData(node->right);
	deleteRule(node->data);
	free(node);
	node = NULL;
}

void addToTree(Tree *theTree, TreeDataPtr data)
{
	int x;
	if (theTree != NULL && findInTree(theTree, data) == NULL)
	{
		TreeNode *toAdd = createTreeNode(data);
		if (theTree->root == NULL)
		{
			theTree->root = toAdd;
			return;
		}
		TreeNode *temp = theTree->root, *prev;
		while (temp != NULL)
		{
			if (theTree->compareFunc(temp->data, data) > 0)
			{
				prev = temp;
				temp = temp->left;
				x = 0;
			}
			else
			{
				prev = temp;
				temp = temp->right;
				x = 1;
			}
		}
		if (x == 0)
			prev->left = toAdd;
		else
			prev->right = toAdd;
	}
	else
	{
		printf("Data already exists\nDuplicate:   ");
		printRule(data);
		free(data);
	}
}

void removeFromTree(Tree *theTree, TreeDataPtr data)
{
	TreeNode *toRemove = theTree->root, *parent = NULL;
	int right = 0;
	while (toRemove != NULL)
	{
		if (theTree->compareFunc(toRemove->data, data) > 0)
		{
			parent = toRemove;
			toRemove = toRemove->left;
			right = 0;
		}
		else if (theTree->compareFunc(toRemove->data, data) < 0)
		{
			parent = toRemove;
			toRemove = toRemove->right;
			right = 1;
		}
		else
		{
			break;
		}
	}
	if (toRemove != NULL)
	{
		if (hasTwoChildren(toRemove) > 0)
		{
			TreeNode *prev, *temp = toRemove->left;
			while (temp->right != NULL)
			{
				prev = temp;
				temp = temp->right;
			}
			if (theTree->compareFunc(toRemove->data, theTree->root->data) == 0)
			{
				temp->right = toRemove->right;
				temp->left = toRemove->left;
				theTree->root = temp;
				prev->right = NULL;
				theTree->deleteFunc(toRemove->data);
				free(toRemove);
				toRemove = NULL;
			}
			else
			{
				prev->right = NULL;
				if (right == 1)
					parent->right = temp;
				else
					parent->left = temp;
				temp->right = toRemove->right;
				temp->left = toRemove->left;
				theTree->deleteFunc(toRemove->data);
				free(toRemove);
				toRemove = NULL;
			}
		}
		else if (isLeaf(toRemove) == 1)
		{
			if (theTree->compareFunc(toRemove->data, theTree->root->data) != 0)
			{
				if (right == 1)
					parent->right = NULL;
				else
					parent->left = NULL;
			}
			else
			{
				theTree->root = NULL;
			}
			theTree->deleteFunc(toRemove->data);
			free(toRemove);
			toRemove = NULL;
		}
		else
		{
			if (theTree->compareFunc(toRemove->data, theTree->root->data) != 0)
			{
				if (toRemove->left == NULL)
				{
					if (right == 1)
						parent->right = toRemove->right;
					else
						parent->left = toRemove->right;
				}
				else
				{
					if (right == 1)
						parent->right = toRemove->left;
					else
						parent->left = toRemove->left;
				}
			}
			else
			{
				if (toRemove->left == NULL)
				{
					theTree->root = toRemove->right;
				}
				else
				{
					theTree->root = toRemove->left;
				}
			}
			theTree->deleteFunc(toRemove->data);
			free(toRemove);
			toRemove = NULL;
		}
	}
}

TreeDataPtr findInTree(Tree *theTree, TreeDataPtr data)
{
	if (theTree == NULL)
		return NULL;
	if (theTree->root == NULL)
		return NULL;
	TreeNode *temp = theTree->root;
	while (temp != NULL)
	{
		if (theTree->compareFunc(temp->data, data) > 0)
			temp = temp->left;
		if (temp != NULL)
		{
			if (theTree->compareFunc(temp->data, data) < 0)
				temp = temp->right;
		}
		if (temp != NULL)
		{
			if (theTree->compareFunc(temp->data, data) == 0)
			{
				return temp->data;
			}
		}
	}
	return NULL;
}

TreeDataPtr getRootData(Tree *theTree)
{
	return theTree->root->data;
}

void printInOrder(Tree *theTree, PrintFunc printData)
{
	if (theTree != NULL && theTree->root != NULL)
	{
		printTreeData_inOrder(theTree->root, printData);
	}
	else
	{
		printf("Binary search tree is empty\n");
	}
}
void printTreeData_inOrder(TreeNode *node, PrintFunc printData)
{
	if (node != NULL)
	{
		printTreeData_inOrder(node->left, printData);
		printData(node->data);
		printTreeData_inOrder(node->right, printData);
	}
}

void printPreOrder(Tree *theTree, PrintFunc printData)
{
	if (theTree != NULL && theTree->root != NULL)
	{
		printTreeData_preOrder(theTree->root, printData);
	}
	else
	{
		printf("Binary search tree is empty\n");
	}
}
void printTreeData_preOrder(TreeNode *node, PrintFunc printData)
{
	if (node != NULL)
	{
		printData(node->data);
		printTreeData_preOrder(node->left, printData);
		printTreeData_preOrder(node->right, printData);
	}
}

void printPostOrder(Tree *theTree, PrintFunc printData)
{
	if (theTree != NULL && theTree->root != NULL)
	{
		printTreeData_postOrder(theTree->root, printData);
	}
	else
	{
		printf("Binary search tree is empty\n");
	}
}
void printTreeData_postOrder(TreeNode *node, PrintFunc printData)
{
	if (node != NULL)
	{
		printTreeData_postOrder(node->left, printData);
		printTreeData_postOrder(node->right, printData);
		printData(node->data);
	}
}
int isTreeEmpty(Tree *theTee)
{
	if (theTee->root == NULL)
		return 1;
	return 0;
}

int isLeaf(TreeNode *treeNode)
{
	if (treeNode->left == NULL && treeNode->right == NULL)
		return 1;
	return 0;
}

int hasTwoChildren(TreeNode *treeNode)
{
	if (treeNode->left != NULL && treeNode->right != NULL)
		return 1;
	return 0;
}

int getHeight(TreeNode *treeNode)
{
	return 0;
}
