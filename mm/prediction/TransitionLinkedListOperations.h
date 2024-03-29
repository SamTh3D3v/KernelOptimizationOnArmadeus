#ifndef TRANSITIONLINKEDLISTOPERATIONS_H_INCLUDED
#define TRANSITIONLINKEDLISTOPERATIONS_H_INCLUDED

#include "ElementsSructs.h"

TransitionNode* newTransitionNode(int id);
int GetTransId(TransitionNode* node);
FileNode* GetNextTransNode(TransitionNode* node);
void AffectNextTrans(TransitionNode *transNode, TransitionNode *nextTransNode);
TransitionNode* InsertTransNode(PageNode* pageNode , int transId);
int DeleteTransitionNode(int transitionId);
void PrintTransList(PageNode *head);
void PrintTransList_seq(PageNode *head, struct seq_file *m);
#endif // TRANSITIONLINKEDLISTOPERATIONS_H_INCLUDED
