#include "PageLinkedListOperations.h"

PageNode* newPageNode(int id){
  PageNode * node = NULL;
  node = kmalloc(sizeof(PageNode));
  node->pageId = id;
  node->pageCount = 0;
  node->listTransitions = NULL;
  node->next = NULL;
  return node;
}

int GetPageId(PageNode* node){
    if(node == NULL) return NULL;
    return node->pageId;
}

PageNode* GetNextPageNode(PageNode* node){
    if(node == NULL) return NULL;
    return node->next;
}

void AffectNextPage(PageNode *pageNode, PageNode *nextPageNode){
    pageNode->next = nextPageNode;
}

PageNode* insertPageNode(FileNode* filenode , int pageId){

     PageNode* pagesListHead = NULL;
     PageNode* parentNode=NULL;
     PageNode* node=NULL;
     pagesListHead=filenode->listPage;
     if(pagesListHead == NULL){
         node=newPageNode(pageId);
         filenode->listPage = node;
         filenode->lastPage = pageId;
         return node;
     }
     node=pagesListHead;
     parentNode=NULL;
    while(node != NULL){
       if(GetPageId(node)==pageId){
          //the Page node already exist
          return node;
       }
       parentNode=node;
       node = GetNextPageNode(node);
    }

    //insert the new Page node
    node =newPageNode(pageId);
    AffectNextPage(parentNode, node);
    return node;
}

void PrintPagesList(PageNode *head){
    PageNode* node=NULL;
    node= head;
    if(head==NULL)
        return;
    printk(KERN_INFO "\n |");
    while(node != NULL){
        printk(KERN_INFO " %ld : %ld ->", node->pageId, node->pageCount);
        node = GetNextPageNode(node);
    }
    printk(KERN_INFO "| \n");
}


int deletePageNode(int pageId){
//to do
}
