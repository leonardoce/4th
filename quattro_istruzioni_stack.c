//@+leo-ver=4-thin
//@+node:leonardoce.20090629082550.111:@thin quattro_istruzioni_stack.c
//@@language c
//@@tabwidth -4
//@+others
//@+node:leonardoce.20090629082550.112:Instruction_Drop
#include <stdio.h>
#include <string.h>
#include "quattro_istruzioni.h"
#include "quattro_debug.h"

/**
 * Manipolazione dello stack
 */
void Instruction_Drop(ForthVm *self) {
  if( self->dataStackPtr == 0 ) {
    ForthVm_Error(self, "Data stack underflow.");
    return;
  }

  self->dataStackPtr--;
}
//@-node:leonardoce.20090629082550.112:Instruction_Drop
//@+node:leonardoce.20090629082550.113:Instruction_Dup

void Instruction_Dup(ForthVm *self) {
  if( self->dataStackPtr >= MAX_DATA_STACK ) {
    ForthVm_Error(self, "Data stack overflow.");
    return;
  }

  self->dataStack[self->dataStackPtr] = self->dataStack[self->dataStackPtr-1];
  self->dataStackPtr++;
}
//@-node:leonardoce.20090629082550.113:Instruction_Dup
//@+node:leonardoce.20090629082550.114:Instruction_Pick

void Instruction_Pick(ForthVm *self) {
  if( self->dataStackPtr >= MAX_DATA_STACK ) {
    ForthVm_Error(self, "Data stack overflow.");
    return;
  }

  if( self->dataStackPtr == 0 ) {
    ForthVm_Error(self, "Data stack underflow.");
    return;
  }

  int n = self->dataStack[self->dataStackPtr-1];

  if( self->dataStackPtr < (n+1) ) {
    ForthVm_Error(self, "Data stack underflow.");
    return;
  }

  self->dataStack[self->dataStackPtr-1] = self->dataStack[self->dataStackPtr-2-n];
}
//@-node:leonardoce.20090629082550.114:Instruction_Pick
//@+node:leonardoce.20090629082550.115:Instruction_Dot

void Instruction_Dot(ForthVm *self) {
  if( self->dataStackPtr == 0 ) {
    ForthVm_Error(self, "Data stack underflow.");
    return;
  }

  char msg[1024];

  int n = self->dataStack[self->dataStackPtr-1];
  snprintf(msg, 1024, "%i ", n);
  ForthVm_Output(self, msg);
  self->dataStackPtr--;
}
//@-node:leonardoce.20090629082550.115:Instruction_Dot
//@+node:leonardoce.20090629082550.116:Instruction_DotS

void Instruction_DotS(ForthVm *self) {
  ForthVm_DumpDataStack(self);
}
//@-node:leonardoce.20090629082550.116:Instruction_DotS
//@+node:leonardoce.20090629082550.117:Instruction_DotR

void Instruction_DotR(ForthVm *self) {
  ForthVm_DumpRetStack(self);
}
//@-node:leonardoce.20090629082550.117:Instruction_DotR
//@+node:leonardoce.20090629082550.118:Instruction_RPFetch

void Instruction_RPFetch(ForthVm *self) {
  if( self->dataStackPtr >= MAX_DATA_STACK ) {
    ForthVm_Error(self, "Data stack overflow.");
    return;
  }

  self->dataStack[self->dataStackPtr] = self->retStackPtr;
  self->dataStackPtr++;
}
//@-node:leonardoce.20090629082550.118:Instruction_RPFetch
//@+node:leonardoce.20090629082550.119:Instruction_RPStore

void Instruction_RPStore(ForthVm *self) {
  if( self->dataStackPtr == 0 ) {
    ForthVm_Error(self, "Data stack underflow.");
    return;
  }

  self->dataStackPtr--;
  self->retStackPtr=self->dataStack[self->dataStackPtr];
}
//@-node:leonardoce.20090629082550.119:Instruction_RPStore
//@+node:leonardoce.20090629082550.120:Instruction_SPFetch

void Instruction_SPFetch(ForthVm *self) {
  if( self->dataStackPtr >= MAX_DATA_STACK ) {
    ForthVm_Error(self, "Data stack overflow.");
    return;
  }

  self->dataStack[self->dataStackPtr] = self->dataStackPtr;
  self->dataStackPtr++;
}
//@-node:leonardoce.20090629082550.120:Instruction_SPFetch
//@+node:leonardoce.20090629082550.121:Instruction_SPStore

void Instruction_SPStore(ForthVm *self) {
  if( self->dataStackPtr == 0 ) {
    ForthVm_Error(self, "Data stack underflow.");
    return;
  }

  self->dataStackPtr--;
  self->dataStackPtr=self->dataStack[self->dataStackPtr];
}
//@-node:leonardoce.20090629082550.121:Instruction_SPStore
//@+node:leonardoce.20090629082550.122:Instruction_ToR

void Instruction_ToR(ForthVm *self) {
  if( self->internalState == VM_INTERPRETER ) {
    ForthVm_Error(self, "Invalid >r in interpreter mode.");
    return;
  }

  int newCodePtr;

  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = TO_RET_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = 0;
}
//@-node:leonardoce.20090629082550.122:Instruction_ToR
//@+node:leonardoce.20090629082550.123:Instruction_RFrom

void Instruction_RFrom(ForthVm *self) {
  if( self->internalState == VM_INTERPRETER ) {
    ForthVm_Error(self, "Invalid r> in interpreter mode.");
    return;
  }

  int newCodePtr;

  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = RET_FROM_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = 0;
}
//@-node:leonardoce.20090629082550.123:Instruction_RFrom
//@+node:leonardoce.20090629082550.124:Instruction_RFetch

void Instruction_RFetch(ForthVm *self) {
  if( self->internalState == VM_INTERPRETER ) {
    ForthVm_Error(self, "Invalid r@ in interpreter mode.");
    return;
  }

  int newCodePtr;

  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = RET_FETCH_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = 0;
}
//@-node:leonardoce.20090629082550.124:Instruction_RFetch
//@+node:leonardoce.20090629082550.125:Instruction_Swap

void Instruction_Swap(ForthVm *self) {
  if( self->dataStackPtr < 2 ) {
    ForthVm_Error(self, "Data stack underflow.");
    return;
  }

  int t = self->dataStack[self->dataStackPtr-2];
  self->dataStack[self->dataStackPtr-2]=self->dataStack[self->dataStackPtr-1];
  self->dataStack[self->dataStackPtr-1]=t;
}
//@-node:leonardoce.20090629082550.125:Instruction_Swap
//@+node:leonardoce.20090629082550.126:Instruction_Rot

void Instruction_Rot(ForthVm *self) {
  if( self->dataStackPtr < 3 ) {
    ForthVm_Error(self, "Data stack underflow.");
    return;
  }

  int t = self->dataStack[self->dataStackPtr-3];
  self->dataStack[self->dataStackPtr-3]=self->dataStack[self->dataStackPtr-2];
  self->dataStack[self->dataStackPtr-2]=self->dataStack[self->dataStackPtr-1];
  self->dataStack[self->dataStackPtr-1]=t;
}
//@-node:leonardoce.20090629082550.126:Instruction_Rot
//@+node:leonardoce.20090629082550.127:Instruction_I

void Instruction_I(ForthVm *self) {
  if( self->dataStackPtr >= MAX_DATA_STACK ) {
    ForthVm_Error(self, "Data stack overflow.");
    return;
  }

  if( self->retStackPtr < 2 ) {
    ForthVm_Error(self, "Return stack underflow.");
    return;
  }

  self->dataStack[self->dataStackPtr]=self->retStack[self->retStackPtr-2];
  self->dataStackPtr++;
}
//@-node:leonardoce.20090629082550.127:Instruction_I
//@+node:leonardoce.20090629082550.128:Instruction_J

void Instruction_J(ForthVm *self) {
  if( self->dataStackPtr >= MAX_DATA_STACK ) {
    ForthVm_Error(self, "Data stack overflow.");
    return;
  }

  if( self->retStackPtr < 4 ) {
    ForthVm_Error(self, "Return stack underflow.");
    return;
  }

  self->dataStack[self->dataStackPtr]=self->retStack[self->retStackPtr-4];
  self->dataStackPtr++;
}
//@-node:leonardoce.20090629082550.128:Instruction_J
//@-others

//@-node:leonardoce.20090629082550.111:@thin quattro_istruzioni_stack.c
//@-leo
