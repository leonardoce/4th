//@+leo-ver=4-thin
//@+node:leonardoce.20090629082550.129:@thin quattro_istruzioni_wordlist.c
//@@language c
//@@tabwidth -4
//@+others
//@+node:leonardoce.20090629082550.130:Instruction_Definitions
#include <stdio.h>
#include <string.h>
#include "quattro_istruzioni.h"
#include "quattro_debug.h"

/**
 * Istruzioni che gestiscono le wordlists
 */

void Instruction_Definitions(ForthVm *self) {
  self->compilerWordListIdx = self->searchOrder[0];
}
//@-node:leonardoce.20090629082550.130:Instruction_Definitions
//@+node:leonardoce.20090629082550.131:Instruction_SearchAll

void Instruction_SearchAll(ForthVm *self) {
  // ( c-addr u -- c-addr u 0  |  xt 1  |  xt -1 )  

  if(self->dataStackPtr<2) {
    ForthVm_Error(self, "Data stack underflow");
    return;
  }

  if(self->dataStackPtr>=MAX_DATA_STACK) {
    ForthVm_Error(self, "Data stack overflow");
    return;
  }

  char *wordName = &self->dataSpace[self->dataStack[self->dataStackPtr-2]];
  int addr = ForthVm_Lookup(self, wordName);

  if(addr == FORTHCODEADDRESS_NULL) {
    self->dataStack[self->dataStackPtr]=0;
    self->dataStackPtr++;
  } else if( ForthVm_IsImmediate(self, wordName) ) {
    self->dataStackPtr--;
    self->dataStack[self->dataStackPtr-1]=1;
  } else {
    self->dataStackPtr--;
    self->dataStack[self->dataStackPtr-1]=-1;
  }
}
//@-node:leonardoce.20090629082550.131:Instruction_SearchAll
//@+node:leonardoce.20090629082550.132:Instruction_ForthWordList

void Instruction_ForthWordList(ForthVm *self) {
  // ( -- wid )

  if(self->dataStackPtr>=MAX_DATA_SPACE) {
    ForthVm_Error(self, "Data stack overflow");
    return;
  }

  self->dataStack[self->dataStackPtr]=0;
  self->dataStackPtr++;
}
//@-node:leonardoce.20090629082550.132:Instruction_ForthWordList
//@+node:leonardoce.20090629082550.133:Instruction_GetCurrent

void Instruction_GetCurrent(ForthVm *self) {
  // ( -- wid )

  if(self->dataStackPtr>=MAX_DATA_SPACE) {
    ForthVm_Error(self, "Data stack overflow");
    return;
  }

  self->dataStack[self->dataStackPtr]=self->compilerWordListIdx;
  self->dataStackPtr++;
}
//@-node:leonardoce.20090629082550.133:Instruction_GetCurrent
//@+node:leonardoce.20090629082550.134:Instruction_GetOrder

void Instruction_GetOrder(ForthVm *self) {
  // ( -- widn ... wid1 n )

  if(self->dataStackPtr>=(MAX_DATA_SPACE-1-self->searchOrderLen)) {
    ForthVm_Error(self, "Data stack overflow");
    return;
  }

  int i;
  self->dataStackPtr+=1+self->searchOrderLen;
  for(i=0;i<self->searchOrderLen;i++) {
    self->dataStack[self->dataStackPtr-2-i] = self->searchOrder[i];
  }

  self->dataStack[self->dataStackPtr-1]=self->searchOrderLen;
}
//@-node:leonardoce.20090629082550.134:Instruction_GetOrder
//@+node:leonardoce.20090629082550.135:Instruction_SetOrder

void Instruction_SetOrder(ForthVm *self) {
  // ( widn ... wid1 n -- )

  if(self->dataStackPtr<1 || self->dataStackPtr<=self->dataStack[self->dataStackPtr-1]) {
    ForthVm_Error(self, "Data stack underflow");
    return;
  }

  if(self->dataStack[self->dataStackPtr-1]>MAX_WORD_LISTS) {
    ForthVm_Error(self, "Word list overflow");
    return;
  }

  self->searchOrderLen=self->dataStack[self->dataStackPtr-1];
  int i;
  int trovataWordListZero = FALSE;
  for(i=0;i<self->searchOrderLen;i++) {
    self->searchOrder[i] = self->dataStack[self->dataStackPtr-2-i];
    trovataWordListZero = trovataWordListZero || self->searchOrder[i]==0;
  }

  self->dataStackPtr-=self->searchOrderLen+1;

  if(!trovataWordListZero && self->searchOrderLen<MAX_WORD_LISTS) {
    /* La forth word list deve essere sempre inclusa */
    self->searchOrder[self->searchOrderLen]=0;
    self->searchOrderLen++;
  }
}
//@-node:leonardoce.20090629082550.135:Instruction_SetOrder
//@+node:leonardoce.20090629082550.136:Instruction_WordList

void Instruction_WordList(ForthVm *self) {
  // ( -- wid )

  if(self->dataStackPtr>=MAX_DATA_STACK) {
    ForthVm_Error(self, "Data stack overflow");
    return;
  }
  if(self->searchOrderLen>=MAX_WORD_LISTS) {
    ForthVm_Error(self, "Word list overflow");
    return;
  }

  self->dataStack[self->dataStackPtr]=DynamicVector_Count(self->wordLists);
  self->dataStackPtr++;

  ForthWordList *wl=ForthWordList_New();
  DynamicVector_Append(self->wordLists, wl);
}
//@-node:leonardoce.20090629082550.136:Instruction_WordList
//@+node:leonardoce.20090629082550.137:Instruction_DoRestore

void Instruction_DoRestore(ForthVm *self) {
  int i;

  // Restore word lists
  DynamicVector_SetCount(self->wordLists, self->dataStack[--self->dataStackPtr]);
  for(i=0;i<DynamicVector_Count(self->wordLists);i++) {
    ForthWordList_SetCount((ForthWordList *)DynamicVector_Get(self->wordLists, i),
			   self->dataStack[--self->dataStackPtr]);
  }

  // Restore search order
  self->searchOrderLen=self->dataStack[--self->dataStackPtr];
  for(i=0;i<self->searchOrderLen;i++) {
    self->searchOrder[i]=self->dataStack[--self->dataStackPtr];
  }

  self->compilerWordListIdx=self->dataStack[--self->dataStackPtr];

  // Restore dictionary
  self->hereDataPtr=self->dataStack[--self->dataStackPtr];
  self->hereCodePtr=self->dataStack[--self->dataStackPtr];
}
//@-node:leonardoce.20090629082550.137:Instruction_DoRestore
//@+node:leonardoce.20090629082550.138:Instruction_Marker

void Instruction_Marker(ForthVm *self) {
  if( self->parser == NULL ) {
    ForthVm_Error(self, "Invalid parser in create");
    return;
  } 

  ForthWord *word = ForthStream_ParseWord(self->parser);
  int newCodePtr;

  if( self->lastDefinedWord != NULL ) {
    free(self->lastDefinedWord);
  }
  self->lastDefinedWord=strdup(word->stringValue);

  int startAddress = self->hereCodePtr;
  int i;

  // Dictionary

  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = DATAPUSH_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = startAddress;
  startAddress=newCodePtr;

  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = DATAPUSH_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = self->hereDataPtr;

  // Search Order

  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = DATAPUSH_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = self->compilerWordListIdx;

  for(i=self->searchOrderLen-1;i>=0;i--) {
    newCodePtr = ForthVm_AllocateForthInstruction(self);
    self->codeSpace[newCodePtr].instructionType = DATAPUSH_INSTRUCTION;
    self->codeSpace[newCodePtr].instructionDest = self->searchOrder[i];    
  }

  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = DATAPUSH_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = self->searchOrderLen;    

  // WordLists

  for(i=DynamicVector_Count(self->wordLists)-1;i>=0;i--) {
    newCodePtr = ForthVm_AllocateForthInstruction(self);
    self->codeSpace[newCodePtr].instructionType = DATAPUSH_INSTRUCTION;
    self->codeSpace[newCodePtr].instructionDest = ForthWordList_Count((ForthWordList *)DynamicVector_Get(self->wordLists, i));
  }

  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = DATAPUSH_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = DynamicVector_Count(self->wordLists);    

  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = NATIVE_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = ForthVm_LookupNativeId(self, Instruction_DoRestore);

  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = RET_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = 0;

  ForthWordList_Assoc((ForthWordList *)DynamicVector_Get(self->wordLists, self->compilerWordListIdx), word->stringValue, startAddress);
  ForthWord_Delete(word);
}
//@-node:leonardoce.20090629082550.138:Instruction_Marker
//@+node:leonardoce.20090629082550.139:Instruction_Last

void Instruction_Last(ForthVm *self) {
  if(self->dataStackPtr+1>=MAX_DATA_STACK) {
    ForthVm_Error(self, "Data stack overflow");
    return;
  }

  self->dataStack[self->dataStackPtr++]=self->hereDataPtr;
  if(self->lastDefinedWord==NULL) {
    self->dataStack[self->dataStackPtr++]=0;
  } else {
    self->dataStack[self->dataStackPtr++] = strlen(self->lastDefinedWord);
    strcpy((char *)&self->dataSpace + self->hereDataPtr, self->lastDefinedWord);
  }

  self->compilerWordListIdx = self->searchOrder[0];
}
//@-node:leonardoce.20090629082550.139:Instruction_Last
//@+node:leonardoce.20090629082550.140:ForthVm_RegistraIstruzioniWordlist

void ForthVm_RegistraIstruzioniWordlist(ForthVm *self) {
  ForthVm_RegisterNativeInstruction(self, "definitions", Instruction_Definitions);
  ForthVm_RegisterNativeInstruction(self, "search-all", Instruction_SearchAll);
  ForthVm_RegisterNativeInstruction(self, "forth-wordlist", Instruction_ForthWordList);
  ForthVm_RegisterNativeInstruction(self, "get-current", Instruction_GetCurrent);
  ForthVm_RegisterNativeInstruction(self, "get-order", Instruction_GetOrder);
  ForthVm_RegisterNativeInstruction(self, "set-order", Instruction_SetOrder);
  ForthVm_RegisterNativeInstruction(self, "wordlist", Instruction_WordList);
  ForthVm_RegisterNativeInstruction(self, "(dorestore)", Instruction_DoRestore);
  ForthVm_RegisterNativeInstruction(self, "marker", Instruction_Marker);
  ForthVm_RegisterNativeInstruction(self, "last", Instruction_Last);
}
//@-node:leonardoce.20090629082550.140:ForthVm_RegistraIstruzioniWordlist
//@-others
//@-node:leonardoce.20090629082550.129:@thin quattro_istruzioni_wordlist.c
//@-leo
