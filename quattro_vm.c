//@+leo-ver=4-thin
//@+node:leonardoce.20090629082550.2:@thin quattro_vm.c
//@@language c
//@@tabwidth -4
//@+others
//@+node:leonardoce.20090629082550.37:ForthWordList
#include <stdio.h>
#include <string.h>
#include "quattro_vm.h"
#include "quattro_debug.h"
#include "quattro_istruzioni.h"

//@+others
//@+node:leonardoce.20090629082550.3:New
ForthWordList *ForthWordList_New() {
  ForthWordList *self=(ForthWordList *)malloc(sizeof(ForthWordList));
  self->wordNames=DynamicVector_New();
  self->wordAddrs=DynamicVector_New();
  self->wordIsImmediate=DynamicVector_New();
  return self;
}
//@-node:leonardoce.20090629082550.3:New
//@+node:leonardoce.20090629082550.4:NewFromStream

ForthWordList *ForthWordList_NewFromStream(InputStream *in) {
  ForthWordList *self=(ForthWordList *)malloc(sizeof(ForthWordList));

  self->wordNames=DynamicVector_New();
  self->wordAddrs=DynamicVector_New();
  self->wordIsImmediate=DynamicVector_New();

  int wordCount;
  int i;

  wordCount = InputStream_ReadInt(in);
  for(i=0; i<wordCount; i++) {
    int wordLen;
    long isImmediate;
    ForthInstructionAddress addr;
    char *wordName;

    isImmediate = InputStream_ReadInt(in);
    addr = InputStream_ReadInt(in);
    wordLen = InputStream_ReadInt(in);

    wordName=(char *)malloc(sizeof(char)*(wordLen+1));
    wordName[wordLen]='\x0';
    InputStream_Read(in, wordName, sizeof(char) * wordLen);

    DynamicVector_Append(self->wordNames, wordName);
    DynamicVector_Append(self->wordAddrs, (void*)addr);
    DynamicVector_Append(self->wordIsImmediate, (void*)isImmediate);
  }  

  return self;
}
//@-node:leonardoce.20090629082550.4:NewFromStream
//@+node:leonardoce.20090629082550.5:Delete

void ForthWordList_Delete(ForthWordList* self) {
  int i;

  for(i=0;i<DynamicVector_Count(self->wordNames);i++) {
    void *addr = DynamicVector_Get(self->wordNames, i);
    if(addr!=NULL) {
      free(addr);
    }
  }

  DynamicVector_Delete(self->wordNames);
  DynamicVector_Delete(self->wordAddrs);
  DynamicVector_Delete(self->wordIsImmediate);
  free(self);
}
//@-node:leonardoce.20090629082550.5:Delete
//@+node:leonardoce.20090629082550.6:Find

ForthInstructionAddress ForthWordList_Find(ForthWordList* self, const char *wordName) {
  ForthInstructionAddress result;
  int i;

  for(i=DynamicVector_Count(self->wordNames)-1;i>=0;i--) {
    void *addr = DynamicVector_Get(self->wordNames, i);
    if(addr!=NULL && stricmp(addr, wordName)==0) {
      result=(ForthInstructionAddress)DynamicVector_Get(self->wordAddrs, i);
      return result;
    }
  }

  return FORTHCODEADDRESS_NULL;
}
//@-node:leonardoce.20090629082550.6:Find
//@+node:leonardoce.20090629082550.7:ReverseFind

const char *ForthWordList_ReverseFind(ForthWordList* self, ForthInstructionAddress addr) {
  int i;

  for(i=DynamicVector_Count(self->wordNames)-1;i>=0;i--) {
    ForthInstructionAddress tempAddr = (ForthInstructionAddress) DynamicVector_Get(self->wordAddrs, i);
    if(tempAddr==addr) {
      const char *wordName = (const char *)DynamicVector_Get(self->wordNames, i);
      return wordName;
    }
  }

  return NULL;
}
//@-node:leonardoce.20090629082550.7:ReverseFind
//@+node:leonardoce.20090629082550.8:Assoc

void ForthWordList_Assoc(ForthWordList* self, const char *wordName, ForthInstructionAddress addr) {
  DynamicVector_Append(self->wordNames, strdup(wordName));
  DynamicVector_Append(self->wordAddrs, (void*)addr);
}
//@-node:leonardoce.20090629082550.8:Assoc
//@+node:leonardoce.20090629082550.9:MarkImmediate

void ForthWordList_MarkImmediate(ForthWordList* self, const char *wordName) {
  int i;

  for(i=DynamicVector_Count(self->wordNames)-1;i>=0;i--) {
    void *addr = DynamicVector_Get(self->wordNames, i);
    if(stricmp(addr, wordName)==0) {
      DynamicVector_Set(self->wordIsImmediate, i, (void*)1);
    }
  }  
}
//@-node:leonardoce.20090629082550.9:MarkImmediate
//@+node:leonardoce.20090629082550.10:IsImmediate

int ForthWordList_IsImmediate(ForthWordList* self, const char *wordName) {
  int i;

  for(i=DynamicVector_Count(self->wordNames)-1;i>=0;i--) {
    void *addr = DynamicVector_Get(self->wordNames, i);
    if(stricmp(addr, wordName)==0) {
      if(i<DynamicVector_Count(self->wordIsImmediate)) {
        return longtobool(DynamicVector_Get(self->wordIsImmediate, i));
      } else {
        return 0;
      }
    }
  }  

  return 0;
}
//@-node:leonardoce.20090629082550.10:IsImmediate
//@+node:leonardoce.20090629082550.11:SaveOnFile

void ForthWordList_SaveOnFile(ForthWordList* self, OutputStream *out) {
  int wordCount = DynamicVector_Count(self->wordNames);
  int i;

  OutputStream_WriteInt(out, wordCount);
  for(i=0; i<wordCount; i++) {
    int wordLen = strlen((char *)DynamicVector_Get(self->wordNames, i));
    int isImmediate = longtobool(DynamicVector_Get(self->wordIsImmediate, i));
    ForthDataAddress addr = DynamicVector_Get(self->wordAddrs, i);

    OutputStream_WriteInt(out, isImmediate);
    OutputStream_WriteInt(out, addr);
    OutputStream_WriteInt(out, wordLen);
    OutputStream_Write(out, DynamicVector_Get(self->wordNames, i), sizeof(char) * wordLen );
  }  
}
//@-node:leonardoce.20090629082550.11:SaveOnFile
//@+node:leonardoce.20090629082550.12:Count

int ForthWordList_Count(ForthWordList *self) {
  return DynamicVector_Count(self->wordAddrs);
}
//@-node:leonardoce.20090629082550.12:Count
//@+node:leonardoce.20090629082550.13:SetCount

void ForthWordList_SetCount(ForthWordList *self, int c) {
  DynamicVector_SetCount(self->wordNames, c);
  DynamicVector_SetCount(self->wordIsImmediate, c);
  DynamicVector_SetCount(self->wordAddrs, c);
}
//@-node:leonardoce.20090629082550.13:SetCount
//@-others
//@nonl
//@-node:leonardoce.20090629082550.37:ForthWordList
//@+node:leonardoce.20090629082550.38:ForthVm
//@+others
//@+node:leonardoce.20090629082550.14:New


/**
 * ForthVm
 */

ForthVm *ForthVm_New() {
  ForthVm *self=(ForthVm*)malloc(sizeof(ForthVm));

  self->forthWordList=ForthWordList_New();
  self->compilerWordListIdx=0;
  self->searchOrder[0]=0;
  self->searchOrderLen=1;

  self->wordLists=DynamicVector_New();
  self->debugInfo=DynamicVector_New();
  self->lastDefinedWord=NULL;

  self->hereCodePtr=1;
  self->hereDataPtr=1;
  self->dataStackPtr=0;
  self->retStackPtr=0;
  self->exitFlag=0;

  self->instructionPtr=0;
  self->nativeInstructionPtr=0;
  self->traceEnabled=0;
  self->traceMaxWidth=0;
  self->wordTraceEnabled=0;

  self->parser=NULL;
  self->internalState=VM_INTERPRETER;

  DynamicVector_Set(self->wordLists, 0, self->forthWordList);

  ForthVm_InitForthWordList(self);

  return self;
}
//@-node:leonardoce.20090629082550.14:New
//@+node:leonardoce.20090629082550.15:NewFromFile

ForthVm *ForthVm_NewFromFile(InputStream *in) {
  int i, count;

  ForthVm *self=(ForthVm*)malloc(sizeof(ForthVm));

  count = InputStream_ReadInt(in);
  self->wordLists = DynamicVector_New();

  for(i=0; i<count; i++) {
    DynamicVector_Append(self->wordLists, ForthWordList_NewFromStream(in));
  }

  self->forthWordList=(ForthWordList *)DynamicVector_Get(self->wordLists, 0);

  self->searchOrder[0]=0;
  self->searchOrderLen=1;
  self->compilerWordListIdx=0;

  self->debugInfo=DynamicVector_New();

  self->hereCodePtr = InputStream_ReadInt(in);
  self->hereDataPtr = InputStream_ReadInt(in);
  InputStream_Read(in, &self->codeSpace, sizeof(ForthInstruction) * self->hereCodePtr);
  InputStream_Read(in, &self->dataSpace, sizeof(char) * self->hereDataPtr);

  self->lastDefinedWord=NULL;
  self->dataStackPtr=0;
  self->retStackPtr=0;

  self->instructionPtr=0;
  self->nativeInstructionPtr=0;
  self->traceEnabled=0;
  self->traceMaxWidth=0;
  self->wordTraceEnabled=0;
  self->exitFlag=0;

  self->parser=NULL;
  self->internalState=VM_INTERPRETER;

  ForthVm_InitForthWordList(self);

  return self;
}
//@-node:leonardoce.20090629082550.15:NewFromFile
//@+node:leonardoce.20090629082550.16:SaveOnFile

void ForthVm_SaveOnFile(ForthVm *self, OutputStream *out) {
  int i, count;

  count = DynamicVector_Count(self->wordLists);
  OutputStream_WriteInt(out, count);

  for(i=0; i<DynamicVector_Count(self->wordLists); i++) {
    ForthWordList_SaveOnFile((ForthWordList*)DynamicVector_Get(self->wordLists, i), out);
  }

  OutputStream_WriteInt(out, self->hereCodePtr);
  OutputStream_WriteInt(out, self->hereDataPtr);
  OutputStream_Write(out, &self->codeSpace, sizeof(ForthInstruction) * self->hereCodePtr);
  OutputStream_Write(out, &self->dataSpace, sizeof(char) * self->hereDataPtr);
}
//@-node:leonardoce.20090629082550.16:SaveOnFile
//@+node:leonardoce.20090629082550.17:Delete

void ForthVm_Delete(ForthVm *self) {
  int i;

  for(i=0;i<DynamicVector_Count(self->wordLists);i++) {
    ForthWordList_Delete((ForthWordList*)DynamicVector_Get(self->wordLists, i));
  }

  DynamicVector_Delete(self->wordLists);
  DynamicVector_Delete(self->debugInfo);

  free(self);
}
//@-node:leonardoce.20090629082550.17:Delete
//@+node:leonardoce.20090629082550.19:InitForthWordList

void ForthVm_InitForthWordList(ForthVm *self) {
  int newCodePtr;

  /* costruisce la word list di default */
  ForthVm_RegisterNativeInstruction(self, ":", Instruction_Colon);
  ForthVm_RegisterNativeInstruction(self, ";", Instruction_Semicolon);
  ForthVm_RegisterNativeInstruction(self, "parse", Instruction_Parse);
  ForthVm_RegisterNativeInstruction(self, "rot", Instruction_Rot);
  ForthVm_RegisterNativeInstruction(self, "drop", Instruction_Drop);
  ForthVm_RegisterNativeInstruction(self, "dup", Instruction_Dup);
  ForthVm_RegisterNativeInstruction(self, "pick", Instruction_Pick);
  ForthVm_RegisterNativeInstruction(self, "immediate", Instruction_Immediate);
  ForthVm_RegisterNativeInstruction(self, "here", Instruction_Here);
  ForthVm_RegisterNativeInstruction(self, "s\"", Instruction_SQuote);
  ForthVm_RegisterNativeInstruction(self, "create", Instruction_Create);
  ForthVm_RegisterNativeInstruction(self, "allot", Instruction_Allot);
  ForthVm_RegisterNativeInstruction(self, "!", Instruction_Store);
  ForthVm_RegisterNativeInstruction(self, "@", Instruction_Fetch);
  ForthVm_RegisterNativeInstruction(self, "c!", Instruction_CStore);
  ForthVm_RegisterNativeInstruction(self, "c@", Instruction_CFetch);
  ForthVm_RegisterNativeInstruction(self, "cells", Instruction_Cells);
  ForthVm_RegisterNativeInstruction(self, "does>", Instruction_Does);
  ForthVm_RegisterNativeInstruction(self, "saveonfile", Instruction_SaveOnFile);
  ForthVm_RegisterNativeInstruction(self, "loadfile", Instruction_LoadFile);
  ForthVm_RegisterNativeInstruction(self, "loadstring", Instruction_LoadString);
  ForthVm_RegisterNativeInstruction(self, ".", Instruction_Dot);
  ForthVm_RegisterNativeInstruction(self, ".s", Instruction_DotS);
  ForthVm_RegisterNativeInstruction(self, ".r", Instruction_DotR);
  ForthVm_RegisterNativeInstruction(self, "rp@", Instruction_RPFetch);
  ForthVm_RegisterNativeInstruction(self, "rp!", Instruction_RPStore);
  ForthVm_RegisterNativeInstruction(self, "sp@", Instruction_SPFetch);
  ForthVm_RegisterNativeInstruction(self, "sp!", Instruction_SPStore);
  ForthVm_RegisterNativeInstruction(self, "emit", Instruction_Emit);
  ForthVm_RegisterNativeInstruction(self, ">r", Instruction_ToR);
  ForthVm_RegisterNativeInstruction(self, "r@", Instruction_RFetch);
  ForthVm_RegisterNativeInstruction(self, "r>", Instruction_RFrom);
  ForthVm_RegisterNativeInstruction(self, "'", Instruction_Tick);
  ForthVm_RegisterNativeInstruction(self, "execute", Instruction_Execute);
  ForthVm_RegisterNativeInstruction(self, "(codedoes>)", Instruction_CodeDoesJump);
  ForthVm_RegisterNativeInstruction(self, "swap", Instruction_Swap);
  ForthVm_RegisterNativeInstruction(self, "i", Instruction_I);
  ForthVm_RegisterNativeInstruction(self, "j", Instruction_J);
  ForthVm_RegisterNativeInstruction(self, "trace!", Instruction_TraceStore);
  ForthVm_RegisterNativeInstruction(self, "tracewidth!", Instruction_TraceWidthStore);
  ForthVm_RegisterNativeInstruction(self, "wordtrace!", Instruction_WordTraceStore);
  ForthVm_RegisterNativeInstruction(self, "words", Instruction_Words);
  ForthVm_RegisterNativeInstruction(self, "compile,", Instruction_CompileComma);
  ForthVm_RegisterNativeInstruction(self, "literal", Instruction_Literal);
  ForthVm_RegisterNativeInstruction(self, "state@", Instruction_StateFetch);
  ForthVm_RegisterNativeInstruction(self, "bye", Instruction_Bye);

  ForthVm_RegistraIstruzioniAritmetiche(self);
  ForthVm_RegistraIstruzioniWordlist(self);
  ForthVm_RegistraIstruzioniFfi(self);
  ForthVm_RegistraIstruzioniFlow(self);

  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = STOP_VM;
  self->codeSpace[newCodePtr].instructionDest = 0;
  ForthWordList_Assoc(self->forthWordList, "stopvm", newCodePtr);

  ForthVm_MarkImmediate(self, ";");
  ForthVm_MarkImmediate(self, "immediate");
  ForthVm_MarkImmediate(self, "s\"");
  ForthVm_MarkImmediate(self, "does>");
  ForthVm_MarkImmediate(self, "r>");
  ForthVm_MarkImmediate(self, "r@");
  ForthVm_MarkImmediate(self, ">r");
  ForthVm_MarkImmediate(self, "literal");
}
//@-node:leonardoce.20090629082550.19:InitForthWordList
//@+node:leonardoce.20090629082550.20:AllocateForthInstruction

ForthInstructionAddress ForthVm_AllocateForthInstruction(ForthVm *self) {
  ForthInstructionAddress res = self->hereCodePtr;

  if(self->hereCodePtr >= MAX_CODE_SPACE) {
    printf("Spazio del codice esaurito.\n");
    abort();
  }

  self->hereCodePtr++;
  return res;
}
//@-node:leonardoce.20090629082550.20:AllocateForthInstruction
//@+node:leonardoce.20090629082550.21:RegisterNativeInstruction

void ForthVm_RegisterNativeInstruction(ForthVm* self, const char *wordName, NativeInstruction instr) {
  int newCodePtr, instructionStartAddress;

  if(self->nativeInstructionPtr >= MAX_NATIVE_INSTRUCTIONS) {
    ForthVm_Error(self, "Native instruction table overflow");
  } else {
    self->nativeInstructionTable[self->nativeInstructionPtr]=instr;
    self->nativeInstructionTableDesc[self->nativeInstructionPtr] = wordName;

    if(wordName!=NULL && ForthVm_Lookup(self, wordName)==FORTHCODEADDRESS_NULL) {
      /* cosi' se viene da un file non duplica il codice */
      newCodePtr = ForthVm_AllocateForthInstruction(self);
      instructionStartAddress = newCodePtr;
      self->codeSpace[newCodePtr].instructionType = NATIVE_INSTRUCTION;
      self->codeSpace[newCodePtr].instructionDest = self->nativeInstructionPtr;

      newCodePtr = ForthVm_AllocateForthInstruction(self);
      self->codeSpace[newCodePtr].instructionType = RET_INSTRUCTION;
      self->codeSpace[newCodePtr].instructionDest = 0;
      ForthWordList_Assoc(self->forthWordList, wordName, instructionStartAddress);
    }

    self->nativeInstructionPtr++;
  }
}
//@-node:leonardoce.20090629082550.21:RegisterNativeInstruction
//@+node:leonardoce.20090629082550.203:Output
//@+others
//@+node:leonardoce.20090629082550.22:Error

void ForthVm_Error(ForthVm *self, const char *msg) {
  printf("%s", msg);
  fflush(stdout);
  self->dataStackPtr=0;
  self->retStackPtr=0;
  self->internalState = VM_INTERPRETER;
  self->exitFlag=1;
}
//@-node:leonardoce.20090629082550.22:Error
//@+node:leonardoce.20090629082550.23:Output

void ForthVm_Output(ForthVm *self, const char *msg) {
  fprintf(stdout, "%s", msg);
  fflush(stdout);
}
//@-node:leonardoce.20090629082550.23:Output
//@+node:leonardoce.20090629082550.24:DumpDataStack

void ForthVm_DumpDataStack(ForthVm *self) {
  int i;

  for(i=0;i<self->dataStackPtr;i++) {
    printf(CELL_PRINTF_FORMAT, self->dataStack[i]);
  }
  printf("<sp ");
}
//@-node:leonardoce.20090629082550.24:DumpDataStack
//@+node:leonardoce.20090629082550.25:DumpRetStack

void ForthVm_DumpRetStack(ForthVm *self) {
  int i;

  printf("<ReturnStack>\n");
  for(i=0;i<self->retStackPtr;i++) {
    printf("  <StackItem id=\"%i\" value=\"", i);
    printf(CELL_PRINTF_FORMAT "\"/>\n", self->retStack[i]);
  }
  printf("</ReturnStack>\n");
}
//@-node:leonardoce.20090629082550.25:DumpRetStack
//@-others
//@nonl
//@-node:leonardoce.20090629082550.203:Output
//@+node:leonardoce.20090629082550.26:Run

void ForthVm_Run(ForthVm* self) {
  NativeInstruction nativeInstr;
  ForthInstruction *forthInstr;
  int vmRunning=TRUE;
  char msg[1024];
  int i;

  int shouldTrace;

  while(vmRunning) {
    if(self->exitFlag) {
      break;
    }

    forthInstr=&self->codeSpace[self->instructionPtr];
    shouldTrace = self->traceEnabled && (self->traceMaxWidth==0 || 
                                         self->retStackPtr<self->traceMaxWidth);

    if(shouldTrace) {
      printf("(r: ");
      for(i=0;i<self->retStackPtr;i++) {
        printf(CELL_PRINTF_FORMAT, self->retStack[i]);
      }
      printf(") ");

      printf("(d: ");
      for(i=0;i<self->dataStackPtr;i++) {
        printf(CELL_PRINTF_FORMAT, self->dataStack[i]);
      }
      printf(") ");
      printf(CELL_PRINTF_FORMAT, self->instructionPtr);
    }

    self->instructionPtr++;

    switch(forthInstr->instructionType)  {
    case RET_FROM_INSTRUCTION:
      if(shouldTrace) {
        printf("retfrom ");
      }

      if(self->retStackPtr==0) {
        ForthVm_Error(self, "Return stack underflow");
      } else if(self->dataStackPtr>=MAX_DATA_STACK) {
        ForthVm_Error(self, "Data stack overflow");
      } else {
        self->retStackPtr--;
        self->dataStack[self->dataStackPtr] = self->retStack[self->retStackPtr];
        self->dataStackPtr++;
      }
      break;
    case RET_FETCH_INSTRUCTION:
      if(shouldTrace) {
        printf("retfetch ");
      }

      if(self->retStackPtr==0) {
        ForthVm_Error(self, "Return stack underflow");
      } else if(self->dataStackPtr>=MAX_DATA_STACK) {
        ForthVm_Error(self, "Data stack overflow");
      } else {
        self->dataStack[self->dataStackPtr] = self->retStack[self->retStackPtr-1];
        self->dataStackPtr++;
      }
      break;
    case TO_RET_INSTRUCTION:
      if(shouldTrace) {
        printf("toret ");
      }

      if(self->dataStackPtr==0) {
        ForthVm_Error(self, "Data stack underflow");
      } else if(self->retStackPtr>=MAX_RET_STACK) {
        ForthVm_Error(self, "Return stack overflow");
      } else {
        self->dataStackPtr--;
        self->retStack[self->retStackPtr] = self->dataStack[self->dataStackPtr];
        self->retStackPtr++;
      }
      break;
    case NATIVE_INSTRUCTION:
      if(shouldTrace) {
        printf("native %s", self->nativeInstructionTableDesc[forthInstr->instructionDest]);
      }

      nativeInstr=self->nativeInstructionTable[forthInstr->instructionDest];
      nativeInstr(self);
      break;
    case STOP_VM:
      if(shouldTrace) {
        printf("stop ");
      }

      vmRunning=FALSE;
      self->exitFlag=TRUE;
      break;
    case RET_INSTRUCTION:
      if(shouldTrace) {
        printf("ret ");
      }

      if(self->retStackPtr==0) {
        vmRunning=FALSE;
      } else {
        self->retStackPtr--;
        self->instructionPtr=self->retStack[self->retStackPtr];
      }
      break;
    case CALL_INSTRUCTION:
      if(shouldTrace) {
        printf("call %i", forthInstr->instructionDest);

	const char *wordName = ForthVm_ReverseLookup(self, forthInstr->instructionDest);
	if(wordName!=NULL) {
	  printf(" (%s)", wordName);
	}
      }

      if(self->retStackPtr>=MAX_RET_STACK) {
        ForthVm_Error(self, "return stack overflow");
        vmRunning=FALSE;
      } else {
        self->retStack[self->retStackPtr]=self->instructionPtr;
        self->retStackPtr++;
        self->instructionPtr=forthInstr->instructionDest;
      }
      break;
    case NOP_INSTRUCTION:
      if(shouldTrace) {
        printf("nop ");
      }
      break;
    case DEBUGGER_INSTRUCTION:
      if(shouldTrace) {
        printf("debugger ");

        if(forthInstr->instructionDest >=0 && forthInstr->instructionDest < DynamicVector_Count(self->debugInfo)) {
          ForthDebugInfo *deb = (ForthDebugInfo *) DynamicVector_Get(self->debugInfo, forthInstr->instructionDest);
          ForthDebugInfo_Dump(deb);
        }
      }

      break;
    case JUMP_INSTRUCTION:
      if(shouldTrace) {
        printf("jump to %i", forthInstr->instructionDest);
      }

      self->instructionPtr = forthInstr->instructionDest;
      break;
    case JFALSE_INSTRUCTION:
      if(shouldTrace) {
        printf("jfalse ");
      }

      if(self->dataStackPtr==0) {
        ForthVm_Error(self, "data stack underflow");
      }
      self->dataStackPtr--;
      if(!self->dataStack[self->dataStackPtr]) {
        self->instructionPtr = forthInstr->instructionDest;
      }
      break;
    case DATAPUSH_INSTRUCTION:
      if(shouldTrace) {
        printf("push %i ", forthInstr->instructionDest);
      }

      if(self->dataStackPtr>=MAX_DATA_STACK) {
        ForthVm_Error(self, "data stack overflow");
      } else {
        self->dataStack[self->dataStackPtr]=forthInstr->instructionDest;
        self->dataStackPtr++;
      }
      break;
    default:
      snprintf(msg, 1024, "unknown vm instruction %i...", forthInstr->instructionType );
      ForthVm_Error(self, msg);
      vmRunning=FALSE;
    }

    if(shouldTrace) {
      printf("\n");
    }
  }
}
//@-node:leonardoce.20090629082550.26:Run
//@+node:leonardoce.20090629082550.204:Lookup
//@+others
//@+node:leonardoce.20090629082550.27:Lookup

ForthInstructionAddress ForthVm_Lookup(ForthVm *self, const char *wordName) {
  int i;
  ForthInstructionAddress result;

  for(i=0;i<self->searchOrderLen;i++) {
    if(self->searchOrder[i] < DynamicVector_Count(self->wordLists)) {
      ForthWordList *wordList = (ForthWordList*)DynamicVector_Get(self->wordLists, self->searchOrder[i]);
      result=ForthWordList_Find(wordList, wordName);
      if(result!=FORTHCODEADDRESS_NULL) {
	return result;
      }
    }
  }

  return FORTHCODEADDRESS_NULL;
}
//@-node:leonardoce.20090629082550.27:Lookup
//@+node:leonardoce.20090629082550.28:ReverseLookup

const char *ForthVm_ReverseLookup(ForthVm *self, ForthInstructionAddress addr) {
  int i;
  const char *result;

  for(i=0;i<self->searchOrderLen;i++) {
    if(self->searchOrder[i] < DynamicVector_Count(self->wordLists)) {
      ForthWordList *wordList = (ForthWordList*)DynamicVector_Get(self->wordLists, self->searchOrder[i]);
      result=ForthWordList_ReverseFind(wordList, addr);
      if(result!=NULL) {
	return result;
      }
    }
  }

  return NULL;
}
//@-node:leonardoce.20090629082550.28:ReverseLookup
//@+node:leonardoce.20090629082550.29:IsImmediate

ForthInstructionAddress ForthVm_IsImmediate(ForthVm *self, const char *wordName) {
  int i;
  ForthInstructionAddress result;

  for(i=0;i<self->searchOrderLen;i++) {
    if(self->searchOrder[i] < DynamicVector_Count(self->wordLists)) {
      ForthWordList *wordList = (ForthWordList*)DynamicVector_Get(self->wordLists, self->searchOrder[i]);
      result=ForthWordList_Find(wordList, wordName);
      if(result!=FORTHCODEADDRESS_NULL) {
	return ForthWordList_IsImmediate(wordList, wordName);
      }
    }
  }

  return FALSE;
}
//@-node:leonardoce.20090629082550.29:IsImmediate
//@+node:leonardoce.20090629082550.30:MarkImmediate

void ForthVm_MarkImmediate(ForthVm *self, const char *wordName) {
  int i;
  ForthInstructionAddress result;

  for(i=0;i<self->searchOrderLen;i++) {
    if(self->searchOrder[i] < DynamicVector_Count(self->wordLists)) {
      ForthWordList *wordList = (ForthWordList*)DynamicVector_Get(self->wordLists, self->searchOrder[i]);
      result=ForthWordList_Find(wordList, wordName);
      if(result!=FORTHCODEADDRESS_NULL) {
	ForthWordList_MarkImmediate(wordList, wordName);
      }
    }
  }
}
//@-node:leonardoce.20090629082550.30:MarkImmediate
//@+node:leonardoce.20090629082550.18:LookupNativeId

int ForthVm_LookupNativeId(ForthVm *self, NativeInstruction ni) {
  int i;

  for(i=0;i<self->nativeInstructionPtr;i++) {
    if(self->nativeInstructionTable[i]==ni) {
      return i;
    }
  }

  return -1;
}
//@-node:leonardoce.20090629082550.18:LookupNativeId
//@-others
//@nonl
//@-node:leonardoce.20090629082550.204:Lookup
//@+node:leonardoce.20090629082550.205:Input
//@+others
//@+node:leonardoce.20090629082550.31:SetParser

void ForthVm_SetParser(ForthVm *self, ForthStream *value) {
  self->parser=value;
}
//@-node:leonardoce.20090629082550.31:SetParser
//@+node:leonardoce.20090629082550.32:GetParser

ForthStream *ForthVm_GetParser(ForthVm *self) {
  return self->parser;
}
//@-node:leonardoce.20090629082550.32:GetParser
//@-others
//@nonl
//@-node:leonardoce.20090629082550.205:Input
//@+node:leonardoce.20090629082550.35:Feed
//@+others
//@+node:leonardoce.20090629082550.33:ForthVm_FeedInterpreter

void ForthVm_FeedInterpreter(ForthVm *self, ForthWord *word) {
  ForthInstructionAddress addr;
  char msg[1024];

  switch(word->wordType) {
  case INT_WORD:
    if(self->dataStackPtr>=MAX_DATA_STACK) {
      ForthVm_Error(self, "data stack overflow");
    } else {
      self->dataStack[self->dataStackPtr]=word->intValue;
      self->dataStackPtr++;
    }
    break;
  case EXECUTE_WORD:
    addr=ForthVm_Lookup(self, word->stringValue);
    if(addr==FORTHCODEADDRESS_NULL) {
      snprintf(msg, 1024, "unknown word %s", word->stringValue);
      ForthVm_Error(self, msg);
    } else {
      self->instructionPtr = addr;
      ForthVm_Run(self);
    }
    break;
  }
}
//@-node:leonardoce.20090629082550.33:ForthVm_FeedInterpreter
//@+node:leonardoce.20090629082550.34:ForthVm_FeedCompiler

void ForthVm_FeedCompiler(ForthVm *self, ForthWord *word) {
  ForthInstructionAddress addr;
  char msg[1024];
  int newCodePtr;

  switch(word->wordType) {
  case INT_WORD:
    newCodePtr = ForthVm_AllocateForthInstruction(self);
    self->codeSpace[newCodePtr].instructionType = DATAPUSH_INSTRUCTION;
    self->codeSpace[newCodePtr].instructionDest = word->intValue;
    break;
  case EXECUTE_WORD:
    addr=ForthVm_Lookup(self, word->stringValue);
    if(addr==FORTHCODEADDRESS_NULL) {
      snprintf(msg, 1024, "unknown word %s", word->stringValue);
      ForthVm_Error(self, msg);
    } else {
      if(ForthVm_IsImmediate(self, word->stringValue)) {
        self->instructionPtr = addr;
        ForthVm_Run(self);
      } else {
        newCodePtr = ForthVm_AllocateForthInstruction(self);
        self->codeSpace[newCodePtr].instructionType = CALL_INSTRUCTION;
        self->codeSpace[newCodePtr].instructionDest = addr;
      }
    }
    break;
  }
}
//@-node:leonardoce.20090629082550.34:ForthVm_FeedCompiler
//@-others

void ForthVm_Feed(ForthVm *self) {
  if(self->parser==NULL) {
    return;
  }

  while(!self->exitFlag && !ForthStream_Eof(self->parser)) {
    ForthWord *word=ForthStream_ParseWord(self->parser);

    if(word!=NULL) { 
      if(self->wordTraceEnabled) {
        printf("state=%i ", self->internalState);
        ForthWord_Dump(word);
        printf("\n");
      }

      if( self->internalState == VM_INTERPRETER) {
        ForthVm_FeedInterpreter(self, word);
      } else if( self->internalState == VM_COMPILER ) {
        ForthVm_FeedCompiler(self, word);
      } else { 
        printf("Unknown state %i\n", self->internalState);
      }
      ForthWord_Delete(word);
    }
  }
}
//@-node:leonardoce.20090629082550.35:Feed
//@-others
//@nonl
//@-node:leonardoce.20090629082550.38:ForthVm
//@-others
//@-node:leonardoce.20090629082550.2:@thin quattro_vm.c
//@-leo
