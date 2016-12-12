#include "FileLinkedListOperations.h"


FileNode* newFileNode(char* name){
  FileNode* node = NULL;
  node = malloc(sizeof(FileNode));
  node->filename = name;
  node->lastPage = -1;
  node->listPage = NULL;
  node->next = NULL;
  return node;
}

char* GetFileName(FileNode* node){
    if(node == NULL) return NULL;
    return node->filename;
}


FileNode* GetNextFileNode(FileNode* node){
    if(node == NULL) return NULL;
    return node->next;
}

void AffectNextFile(FileNode *fileNode, FileNode *nextFileNode){
    fileNode->next = nextFileNode;

}

//look for a file node, insert a new one if it didn't exist
FileNode* insertFileNode(FileNode** filesListHead , char* fileName){
    FileNode* node = NULL;
    FileNode* parentNode=NULL;
    //search the node
     if(*filesListHead == NULL){
           node=newFileNode(fileName);
           *filesListHead=node;
           return node;
     }
     node = *filesListHead;
    while(node != NULL){
       if(strcmp(GetFileName(node),fileName)==0){
         return node;

       }
       parentNode=node;
       node = GetNextFileNode(node);

    }

    //insert the node
    node=newFileNode(fileName);
    AffectNextFile(parentNode,node);

    return node;
}

void PrintFilesList(FileNode *head){
    FileNode* node=NULL;
    node= head;

    if(head==NULL)
        return;
    printf("\n |");
    while(node != NULL){
        printf(" %s ->", node->filename);
        node=GetNextFileNode(node);
    }
    printf("| \n");
}

int deleteFileNode(char* fileName){
//to do
}
