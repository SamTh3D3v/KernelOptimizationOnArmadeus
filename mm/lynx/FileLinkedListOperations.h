#ifndef FILELINKEDLISTOPERATIONS_H_INCLUDED
#define FILELINKEDLISTOPERATIONS_H_INCLUDED

#include "ElementsSructs.h"


FileNode* newFileNode(const unsigned char* name);
char* GetFileName(FileNode* node);
FileNode* GetNextFileNode(FileNode* node);
void AffectNextFile(FileNode *fileNode, FileNode *nextFileNode);
FileNode* insertFileNode(FileNode** filesListHead ,const unsigned char* fileName);
void PrintFilesList(FileNode *head);
int deleteFileNode(char* fileName);

#endif // FILELINKEDLISTOPERATIONS_H_INCLUDED
