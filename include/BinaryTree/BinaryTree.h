#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "BinaryTreeNode.h"

typedef struct BinaryTree BinaryTree;

BinaryTree * createEmptyBinaryTree();

BinaryTreeNode * getRoot(BinaryTree * binaryTree);

BinaryTreeNode * getChild(BinaryTreeNode * binaryTreeNode, int childIndex);

void setChild(BinaryTreeNode * binaryTreeNode, int childIndex, BinaryTreeNode * child);

BinaryTreeNode * encapsulateDataContainerOnBinaryTreeNode(BinaryTreeNode * binaryTreeNode, void * data);

#ifdef __cplusplus
}
#endif

#endif /* BINARY_TREE_H */