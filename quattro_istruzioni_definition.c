//@+leo-ver=4-thin
//@+node:leonardoce.20090629082550.176:@thin quattro_istruzioni_definition.c
//@@language c
//@@tabwidth -4
//@+others
//@+node:leonardoce.20090629082550.177:Instruction_Colon
#include <stdio.h>
#include <string.h>
#include "quattro_istruzioni.h"
#include "quattro_debug.h"

/**
 * Istruzioni che definiscono parole e relative al dizionario
 */
void Instruction_Colon(ForthVm *self) {
  if( self->parser == NULL ) {
    ForthVm_Error(self, "Invalid parser in colon definition");
    return;
  } 

  if( self->internalState == VM_COMPILER ) {
    ForthVm_Error(self, "Invalid colon definition in compiler mode.");
    return;
  }

  ForthWord *word = ForthStream_ParseWord(self->parser);

  if( self->lastDefinedWord != NULL ) free(self->lastDefinedWord);
  self->lastDefinedWord=strdup(word->stringValue);

  ForthWordList_Assoc((ForthWordList *)DynamicVector_Get(self->wordLists, self->compilerWordListIdx), 
                      word->stringValue, self->hereCodePtr);

  ForthWord_Delete(word);

  self->internalState=VM_COMPILER;
}
//@-node:leonardoce.20090629082550.177:Instruction_Colon
//@+node:leonardoce.20090629082550.178:Instruction_Semicolon

void Instruction_Semicolon(ForthVm *self) {
  if( self->internalState == VM_INTERPRETER ) {
    ForthVm_Error(self, "Invalid semicolon in interpreter mode.");
    return;
  }

  int newCodePtr;

  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = RET_INSTRUCTION;

  self->internalState=VM_INTERPRETER;
}
//@-node:leonardoce.20090629082550.178:Instruction_Semicolon
//@+node:leonardoce.20090629082550.179:Instruction_Create

void Instruction_Create(ForthVm *self) {
  if( self->parser == NULL ) {
    ForthVm_Error(self, "Invalid parser in create");
    return;
  } 

  ForthWord *word = ForthStream_ParseWord(self->parser);
  ForthDebugInfo *debuggerInfo = ForthDebugInfo_New(word->fileName, word->stringValue, word->row, word->col, DI_ENTER);
  int newCodePtr;

  if( self->lastDefinedWord != NULL ) {
    free(self->lastDefinedWord);
  }
  self->lastDefinedWord=strdup(word->stringValue);

  int startAddress;

  newCodePtr = ForthVm_AllocateForthInstruction(self);
  startAddress=newCodePtr;
  self->codeSpace[newCodePtr].instructionType = DEBUGGER_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = DynamicVector_Count( self->debugInfo );

  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = DATAPUSH_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = self->hereDataPtr;

  debuggerInfo = ForthDebugInfo_New(word->fileName, word->stringValue, word->row, word->col, DI_ENTER);
  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = DEBUGGER_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = DynamicVector_Count( self->debugInfo );
  DynamicVector_Append(self->debugInfo, debuggerInfo);

  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = RET_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = 0;
  DynamicVector_Append(self->debugInfo, debuggerInfo);

  ForthWordList_Assoc((ForthWordList *)DynamicVector_Get(self->wordLists, self->compilerWordListIdx), word->stringValue, startAddress);
  ForthWord_Delete(word);
}
//@-node:leonardoce.20090629082550.179:Instruction_Create
//@+node:leonardoce.20090629082550.180:Instruction_CodeDoesJump

/**
 * Il does funziona inserendo una istruzione che, a runtime, modifica il codice
 * dell'ultima definizione creata inserendoci un jump alla locazione delle
 * parole compilate dopo il does>
 */
void Instruction_CodeDoesJump(ForthVm *self) {
  /* Quando eseguo questo codice il puntatore all'istruzione corrente
  // punta diretamente alla istruzione successiva alla mia, che
  // e' il ret che esce dalla parola che ha fatto l'istruzione does> .
  // Per effettuare il codice dopo il does codifico un jump, all'interno
  // dell'ultima definizione creata, che salta alla parola successiva
  // all'istruzione corrente, che e' la prima parola compilata dopo
  // il does.
  // Questa istruzione c'e' sicuramente perche' viene generata
  // per il debugger.
  */

  if( self->lastDefinedWord == NULL ) {
    ForthVm_Error(self, "Invalid does> with no word defined with create.");
    return;
  }

  /* addr+3 e' l'indirizzo dell'istruzione ret della parola creata da "create" */

  int addr = ForthVm_Lookup(self, self->lastDefinedWord );
  self->codeSpace[addr+3].instructionType = JUMP_INSTRUCTION;
  self->codeSpace[addr+3].instructionDest = self->instructionPtr+1;
}
//@-node:leonardoce.20090629082550.180:Instruction_CodeDoesJump
//@+node:leonardoce.20090629082550.181:Instruction_Does

void Instruction_Does(ForthVm *self) {
  if( self->internalState == VM_INTERPRETER ) {
    ForthVm_Error(self, "Invalid does> in interpreter mode.");
    return;
  }

  ForthDebugInfo *debuggerInfo;
  int newCodePtr;

  debuggerInfo = ForthDebugInfo_New(NULL, NULL, 0, 0, DI_EXIT);
  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = DEBUGGER_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = DynamicVector_Count( self->debugInfo );
  DynamicVector_Append(self->debugInfo, debuggerInfo);

  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = NATIVE_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = ForthVm_LookupNativeId(self, Instruction_CodeDoesJump);
  DynamicVector_Append(self->debugInfo, debuggerInfo);

  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = RET_INSTRUCTION;

  debuggerInfo = ForthDebugInfo_New(NULL, NULL, 0, 0, DI_DOES);
  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = DEBUGGER_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = DynamicVector_Count( self->debugInfo );
  DynamicVector_Append(self->debugInfo, debuggerInfo);

}
//@-node:leonardoce.20090629082550.181:Instruction_Does
//@+node:leonardoce.20090629082550.182:Instruction_Immediate


void Instruction_Immediate(ForthVm *self) {
  if( self->lastDefinedWord == NULL ) {
    ForthVm_Error(self, "Invalid semicolon in interpreter mode.");
    return;
  }

  ForthVm_MarkImmediate( self, self->lastDefinedWord );
}
//@-node:leonardoce.20090629082550.182:Instruction_Immediate
//@+node:leonardoce.20090629082550.183:Instruction_Tick

void Instruction_Tick(ForthVm *self) {
  if( self->parser == NULL ) {
    ForthVm_Error(self, "Invalid parser in tick");
    return;
  } 

  if( self->dataStackPtr >= MAX_DATA_STACK ) {
    ForthVm_Error(self, "data stack overflow");
    return;
  } 

  ForthWord *word = ForthStream_ParseWord(self->parser);
  int addr;

  if( word!=NULL ) {
    addr = ForthVm_Lookup(self, word->stringValue);
    ForthWord_Delete(word);
  } else {
    addr = 0;
  }

  self->dataStack[self->dataStackPtr]=addr;
  self->dataStackPtr++;
}
//@-node:leonardoce.20090629082550.183:Instruction_Tick
//@+node:leonardoce.20090629082550.184:Instruction_Execute

void Instruction_Execute(ForthVm *self) {
  if( self->dataStackPtr == 0 ) {
    ForthVm_Error(self, "data stack underflow");
    return;
  } 

  self->retStack[self->retStackPtr]=self->instructionPtr;
  self->retStackPtr++;
  self->dataStackPtr--;
  self->instructionPtr=self->dataStack[self->dataStackPtr];
}
//@-node:leonardoce.20090629082550.184:Instruction_Execute
//@+node:leonardoce.20090629082550.185:Instruction_Words

void Instruction_Words(ForthVm *self) {
  ForthWordList *wordList = DynamicVector_Get(self->wordLists, self->searchOrder[0]);
  int i;

  for(i=0; i<DynamicVector_Count(wordList->wordNames); i++) {
    ForthVm_Output(self, (char *)DynamicVector_Get(wordList->wordNames, i));
    ForthVm_Output(self, " ");
  }
  ForthVm_Output(self, "\n");
}
//@-node:leonardoce.20090629082550.185:Instruction_Words
//@+node:leonardoce.20090629082550.186:Instruction_CompileComma

void Instruction_CompileComma(ForthVm *self) {
  if( self->internalState == VM_INTERPRETER ) {
    ForthVm_Error(self, "Invalid compile-comma in interpreter mode.");
    return;
  }

  if( self->dataStackPtr == 0 ) {
    ForthVm_Error(self, "data stack underflow");
    return;
  } 

  int newCodePtr;
  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = CALL_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = self->dataStack[self->dataStackPtr-1];
  self->dataStackPtr--;
}
//@-node:leonardoce.20090629082550.186:Instruction_CompileComma
//@+node:leonardoce.20090629082550.187:Instruction_Literal

void Instruction_Literal(ForthVm *self) {
  if( self->internalState == VM_INTERPRETER ) {
    ForthVm_Error(self, "Invalid compile-comma in interpreter mode.");
    return;
  }

  if( self->dataStackPtr == 0 ) {
    ForthVm_Error(self, "data stack underflow");
    return;
  } 

  int newCodePtr;
  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = DATAPUSH_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = self->dataStack[self->dataStackPtr-1];
  self->dataStackPtr--;
}
//@-node:leonardoce.20090629082550.187:Instruction_Literal
//@-others


//@-node:leonardoce.20090629082550.176:@thin quattro_istruzioni_definition.c
//@-leo
