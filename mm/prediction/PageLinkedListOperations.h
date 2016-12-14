#ifndef PAGELINKEDLISTOPERATIONS_H_INCLUDED
#define PAGELINKEDLISTOPERATIONS_H_INCLUDED

#include "ElementsSructs.h"

PageNode* newPageNode(int id);
int GetPageId(PageNode* node);
PageNode* GetNextPageNode(PageNode* node);
void AffectNextPage(PageNode *pageNode, PageNode *nextPageNode);
PageNode* insertPageNode(FileNode* filenode , int pageId);
int deletePageNode(int pageId);
void PrintPagesList(PageNode *head);


#endif // PAGELINKEDLISTOPERATIONS_H_INCLUDED
