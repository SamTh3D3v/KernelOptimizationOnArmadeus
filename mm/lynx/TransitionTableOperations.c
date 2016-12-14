#include "TransitionTableOperations.h"
#include "PageLinkedListOperations.h"
#include "TransitionLinkedListOperations.h"

int insertInTransitionTable(FileNode* filenode , int sourcePage, int destPage){

     PageNode* pagesListHead = NULL;
     PageNode* parentNode=NULL;
     PageNode* node=NULL;
     PageNode* sourcePageNode=NULL;
     TransitionNode* destTranNode=NULL;
     pagesListHead=filenode->listPage;


    if(sourcePage == -1){           
        //insert the page directly
         //look for the node
           node=newPageNode(destPage);
           filenode->listPage=node;
           return node;
    }
    //look for the source page node
    sourcePageNode = insertPageNode(filenode , sourcePage);
    destTranNode = InsertTransNode(sourcePageNode, destPage);         
    return 0;  //every thing went well other wise send -1
}

void PrintTransTable(FileNode *fNode){
    TransitionNode* node = NULL;
    FileNode* fileshead = NULL;

    printk(KERN_INFO "\n File : %s ", fNode->filename);
    node= fNode->listPage;
    if(node==NULL)
        return;
    printk(KERN_INFO "\n -> ");
    while(node != NULL){
        PrintTransList(node);
        node = GetNextPageNode(node);

    }
}


