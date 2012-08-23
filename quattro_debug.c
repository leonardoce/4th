//@+leo-ver=4-thin
//@+node:leonardoce.20090629082550.141:@thin quattro_debug.c
//@@language c
//@@tabwidth -4
//@+others
//@+node:leonardoce.20090629082550.142:safeStrdup
#include "quattro_debug.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *safeStrdup(const char *orig) {
  if(orig==NULL) {
    return NULL;
  } else {
    return strdup(orig);
  }
}
//@-node:leonardoce.20090629082550.142:safeStrdup
//@+node:leonardoce.20090629082550.143:safeFree

void safeFree(void *orig) {
  if(orig!=NULL) {
    free(orig);
  }
}
//@-node:leonardoce.20090629082550.143:safeFree
//@+node:leonardoce.20090629082550.144:ForthDebugInfo_New

ForthDebugInfo *ForthDebugInfo_New(const char *fileName, const char *wordName, int row, int col, int diType) {
  ForthDebugInfo *self=(ForthDebugInfo *)malloc(sizeof(ForthDebugInfo));
  self->fileName=safeStrdup(fileName);
  self->wordName=safeStrdup(wordName);
  self->row=row;
  self->col=col;
  self->infoType=diType;

  return(self);
}
//@-node:leonardoce.20090629082550.144:ForthDebugInfo_New
//@+node:leonardoce.20090629082550.145:ForthDebugInfo_Delete

void ForthDebugInfo_Delete(ForthDebugInfo *self) {
  safeFree(self->fileName);
  safeFree(self->wordName);
  safeFree(self);
}
//@-node:leonardoce.20090629082550.145:ForthDebugInfo_Delete
//@+node:leonardoce.20090629082550.146:ForthDebugInfo_Dump

void ForthDebugInfo_Dump(ForthDebugInfo *self) {
  printf("<debuginfo ");

  switch(self->infoType) {
  case DI_ENTER:
    printf("type=\"ENTER\" ");
    break;
  case DI_EXIT:
    printf("type=\"EXIT\" ");
    break;
  case DI_DOES:
    printf("type=\"DOES\" ");
    break;
  case DI_TRACE:
    printf("type=\"TRACE\" ");
    break;
  default:
    printf("type=\"UNKNOWN\" ");
    break;
  }

  if(self->fileName!=NULL) {
    printf("fileName=\"%s\" ", self->fileName);
  }

  if(self->wordName!=NULL) {
    printf("wordName=\"%s\" ", self->wordName);
  }

  printf("row=\"%i\" col=\"%i\"/>", self->row, self->col);
}
//@-node:leonardoce.20090629082550.146:ForthDebugInfo_Dump
//@-others
//@-node:leonardoce.20090629082550.141:@thin quattro_debug.c
//@-leo
