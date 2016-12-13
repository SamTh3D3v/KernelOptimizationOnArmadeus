#include "TransitionLinkedListOperations.h"

TransitionNode* newTransitionNode(int id){

  TransitionNode * node = NULL;
  node = kmalloc(sizeof(TransitionNode), GFP_KERNEL);
  node->pageId = id;
  node->transCount=1;
  node->next = NULL;
  return node;
}


int GetTransId(TransitionNode* node){
    if(node == NULL) return NULL;
    return node->pageId;
}

FileNode* GetNextTransNode(TransitionNode* node){
    if(node == NULL) return NULL;
    return node->next;
}

void AffectNextTrans(TransitionNode *transNode, TransitionNode *nextTransNode){
    transNode->next = nextTransNode;
}

TransitionNode* InsertTransNode(PageNode* pageNode , int transId){
   TransitionNode* node=NULL;
   TransitionNode* parentTrans=NULL;

    TransitionNode* tranHead = pageNode->listTransitions;
    //Look for the trans node
    if(tranHead == NULL){
        node =newTransitionNode(transId);
        pageNode->listTransitions = node;
        pageNode->pageCount +=1;
        return node;
    }
    node = tranHead;
    while(node != NULL){
     if(GetTransId(node) == transId){
        node->transCount +=1;
        pageNode->pageCount +=1;
        return node;
     }
     parentTrans = node;
     node = GetNextTransNode(node);
    }
    node= newTransitionNode(transId);
    AffectNextTrans(parentTrans, node);
    pageNode->pageCount +=1;
    return node;
}

void PrintTransList(PageNode *head){
    TransitionNode* node=NULL;
    printk(KERN_INFO "\n Page %ld :", head->pageId);
    node= head->listTransitions;
    if(node==NULL)
        return;
    printk(KERN_INFO "\n |");
    while(node != NULL){
        printk(KERN_INFO " %ld : %ld->", node->pageId, node->transCount);
        node = GetNextTransNode(node);
    }
    printk(KERN_INFO "| \n");
}

void PrintTransList_seq(PageNode *head, struct seq_file *m){
    TransitionNode* node=NULL;
    seq_printf(m,"\n Page %ld :", head->pageId);
    node= head->listTransitions;
    if(node==NULL)
        return;
    seq_printf(m,"\n |");
    while(node != NULL){
        seq_printf(m," %ld : %ld->", node->pageId, node->transCount);
        node = GetNextTransNode(node);
    }
    seq_printf(m,"| \n");
}


int DeleteTransitionNode(int transitionId){
 //to do
}

