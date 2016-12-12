#ifndef ELEMENTSSTRUCTS_H_INCLUDED
#define ELEMENTSSTRUCTS_H_INCLUDED
#include <stddef.h>
#include <linux/slab.h>

typedef struct FileNode FileNode;
typedef struct PageNode PageNode;
typedef struct TransitionNode TransitionNode;
struct FileNode{
   FileNode* next;
   char* filename;
   int lastPage;
   PageNode* listPage;
};

struct PageNode{
 PageNode* next;
 int pageId;
 int pageCount;
 TransitionNode* listTransitions;
};

struct TransitionNode{
  TransitionNode* next;
  int pageId;
  int transCount;
};

#endif // ELEMENTSSRUCTS_H_INCLUDED
