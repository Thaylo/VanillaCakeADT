#include "DataContainer.h"
#include "BinaryTree.h"
#include "BinaryTreeNode.h"
#include <stdlib.h>

struct BinaryTree {
    BinaryTreeNode * root;
};



/*-----------------------------------------------------------------------------------------------*/
BinaryTree * createEmptyBinaryTree()
{
    BinaryTree * binaryTree = (BinaryTree *) malloc(sizeof(BinaryTree));

    if (binaryTree != NULL)
    {
        binaryTree->root = NULL;
    }

    return binaryTree;
}



/*-----------------------------------------------------------------------------------------------*/
BinaryTreeNode * getRoot(BinaryTree * binaryTree)
{
    return binaryTree->root;
}

