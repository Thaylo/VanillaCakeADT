#include "BinaryTreeNode.h"
#include "DataContainer.h"

struct BinaryTreeNode{
    BinaryTreeNode * leftChild;
    BinaryTreeNode * rightChild;
    DataContainer * dataContainer;
};



/*-----------------------------------------------------------------------------------------------*/
BinaryTreeNode * createEmptyBinaryTreeNode()
{
    BinaryTreeNode * binaryTreeNode = (BinaryTreeNode *) malloc(sizeof(BinaryTreeNode));

    if (binaryTreeNode != NULL)
    {
        binaryTreeNode->leftChild = NULL;
        binaryTreeNode->rightChild = NULL;
        binaryTreeNode->dataContainer = NULL;
    }

    return binaryTreeNode;
}



/*-----------------------------------------------------------------------------------------------*/
BinaryTreeNode * getChild(BinaryTreeNode * binaryTreeNode, int childIndex)
{
    if(binaryTreeNode != NULL)
    {
        if(childIndex == 0)
        {
            return binaryTreeNode->leftChild;
        }
        else if(childIndex == 1)
        {
            return binaryTreeNode->rightChild;
        }
    }
}



/*-----------------------------------------------------------------------------------------------*/
void setChild(BinaryTreeNode * binaryTreeNode, int childIndex, BinaryTreeNode * child)
{
    if(binaryTreeNode != NULL)
    {
        if(childIndex == 0)
        {
            binaryTreeNode->leftChild = child;
        }
        else if(childIndex == 1)
        {
            binaryTreeNode->rightChild = child;
        }
    }
}



/*-----------------------------------------------------------------------------------------------*/
BinaryTreeNode * encapsulateDataContainerOnBinaryTreeNode(DataContainer * dataContainer)
{
    BinaryTreeNode * binaryTreeNode = createEmptyBinaryTreeNode();

    if(binaryTreeNode != NULL)
    {
        binaryTreeNode->dataContainer = dataContainer;
    }

    return binaryTreeNode;
}