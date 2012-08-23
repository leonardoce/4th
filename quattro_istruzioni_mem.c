//@+leo-ver=4-thin
//@+node:leonardoce.20090629082550.103:@thin quattro_istruzioni_mem.c
//@@language c
//@@tabwidth -4
//@+others
//@+node:leonardoce.20090629082550.104:Instruction_Here
#include <stdio.h>
#include <string.h>
#include "quattro_istruzioni.h"
#include "quattro_debug.h"

/**
 * Manipolazione dell'area dati
 */
void Instruction_Here(ForthVm *self) {
  if( self->dataStackPtr >= MAX_DATA_STACK ) {
    ForthVm_Error(self, "Data stack overflow.");
    return;
  }

  self->dataStack[self->dataStackPtr] = self->hereDataPtr;
  self->dataStackPtr++;
}
//@-node:leonardoce.20090629082550.104:Instruction_Here
//@+node:leonardoce.20090629082550.105:Instruction_Allot

void Instruction_Allot(ForthVm *self) {
  if(self->dataStackPtr==0) {
    ForthVm_Error(self, "Data stack underflow.");
    return;
  }

  int reqSpace = self->dataStack[self->dataStackPtr-1];

  if( (self->hereDataPtr + reqSpace) >= MAX_DATA_SPACE ) {
    ForthVm_Error(self, "Data space overflow.");
    return;
  }

  self->hereDataPtr += reqSpace;
  self->dataStackPtr--;
}
//@-node:leonardoce.20090629082550.105:Instruction_Allot
//@+node:leonardoce.20090629082550.106:Instruction_Store

void Instruction_Store(ForthVm *self) {
  if(self->dataStackPtr<2) {
    ForthVm_Error(self, "Data stack underflow.");
    return;
  }

  int addr = self->dataStack[self->dataStackPtr-1];
  int value = self->dataStack[self->dataStackPtr-2];
  self->dataStackPtr-=2;

  if( addr >= self->hereDataPtr ) {
    ForthVm_Error(self, "Data store address error.");
    return;
  }

  memcpy( self->dataSpace+addr, &value, sizeof(value));
}
//@-node:leonardoce.20090629082550.106:Instruction_Store
//@+node:leonardoce.20090629082550.107:Instruction_Fetch

void Instruction_Fetch(ForthVm *self) {
  if(self->dataStackPtr<1) {
    ForthVm_Error(self, "Data stack underflow.");
    return;
  }

  int addr = self->dataStack[self->dataStackPtr-1];
  if( addr >= MAX_DATA_SPACE ) {
    ForthVm_Error(self, "Data fetch address error.");
    return;
  }

  memcpy( self->dataStack + self->dataStackPtr -1, self->dataSpace+addr, sizeof(int) );
}
//@-node:leonardoce.20090629082550.107:Instruction_Fetch
//@+node:leonardoce.20090629082550.108:Instruction_CStore

void Instruction_CStore(ForthVm *self) {
  if(self->dataStackPtr<2) {
    ForthVm_Error(self, "Data stack underflow.");
    return;
  }

  int addr = self->dataStack[self->dataStackPtr-1];
  int value = self->dataStack[self->dataStackPtr-2];
  self->dataStackPtr-=2;

  if( addr >= self->hereDataPtr ) {
    ForthVm_Error(self, "Data store address error.");
    return;
  }

  self->dataSpace[addr] = (char)value;
}
//@-node:leonardoce.20090629082550.108:Instruction_CStore
//@+node:leonardoce.20090629082550.109:Instruction_CFetch

void Instruction_CFetch(ForthVm *self) {
  if(self->dataStackPtr<1) {
    ForthVm_Error(self, "Data stack underflow.");
    return;
  }

  int addr = self->dataStack[self->dataStackPtr-1];
  if( addr >= MAX_DATA_SPACE ) {
    ForthVm_Error(self, "Data fetch address error.");
    return;
  }

  self->dataStack[self->dataStackPtr-1] = self->dataSpace[addr];
}
//@-node:leonardoce.20090629082550.109:Instruction_CFetch
//@+node:leonardoce.20090629082550.110:Instruction_Cells

void Instruction_Cells(ForthVm *self) {
  if(self->dataStackPtr<1) {
    ForthVm_Error(self, "Data stack underflow.");
    return;
  }

  self->dataStack[self->dataStackPtr-1] *= sizeof(int); 
}
//@-node:leonardoce.20090629082550.110:Instruction_Cells
//@-others

//@-node:leonardoce.20090629082550.103:@thin quattro_istruzioni_mem.c
//@-leo
