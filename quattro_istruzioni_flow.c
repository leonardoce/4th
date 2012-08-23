//@+leo-ver=4-thin
//@+node:leonardoce.20090629082550.87:@thin quattro_istruzioni_flow.c
//@@language c
//@@tabwidth -4
//@+others
//@+node:leonardoce.20090629082550.88:Instruction_If
#include <stdio.h>
#include <string.h>
#include "quattro_istruzioni.h"
#include "quattro_debug.h"

/**
 * Istruzioni relative al controllo di flusso
 */
void Instruction_If(ForthVm *self) {
  if( self->internalState == VM_INTERPRETER ) {
    ForthVm_Error(self, "Invalid \"if\" in interpreter mode.");
    return;
  }

  if( self->dataStackPtr == MAX_DATA_STACK ) {
    ForthVm_Error(self, "Control stack overflow");
    return;
  }

  int newCodePtr;
  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = JFALSE_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = 0;  

  self->dataStack[self->dataStackPtr] = newCodePtr;
  self->dataStackPtr++;
}
//@-node:leonardoce.20090629082550.88:Instruction_If
//@+node:leonardoce.20090629082550.89:Instruction_Else

void Instruction_Else(ForthVm *self) {
  if( self->internalState == VM_INTERPRETER ) {
    ForthVm_Error(self, "Invalid \"else\" in interpreter mode.");
    return;
  }

  if( self->dataStackPtr == 0 ) {
    ForthVm_Error(self, "Control stack underflow");
    return;
  }


  // Risolve l'if
  int ifLocation = self->dataStack[self->dataStackPtr-1];
  int newCodePtr;
  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = JUMP_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = 0;  

  self->codeSpace[ifLocation].instructionDest = self->hereCodePtr;  
  self->dataStack[self->dataStackPtr-1] = newCodePtr;
}
//@-node:leonardoce.20090629082550.89:Instruction_Else
//@+node:leonardoce.20090629082550.90:Instruction_Then

void Instruction_Then(ForthVm *self) {
  if( self->internalState == VM_INTERPRETER ) {
    ForthVm_Error(self, "Invalid \"then\" in interpreter mode.");
    return;
  }

  if( self->dataStackPtr == 0 ) {
    ForthVm_Error(self, "Control stack underflow");
    return;
  }


  // Risolve l'if o l'else
  int newCodePtr;
  self->dataStackPtr--;
  newCodePtr = self->dataStack[self->dataStackPtr];

  self->codeSpace[newCodePtr].instructionDest = self->hereCodePtr;  
}
//@-node:leonardoce.20090629082550.90:Instruction_Then
//@+node:leonardoce.20090629082550.91:Instruction_Do

void Instruction_Do(ForthVm *self) {
  if( self->internalState == VM_INTERPRETER ) {
    ForthVm_Error(self, "Invalid \"do\" in interpreter mode.");
    return;
  }

  if( self->dataStackPtr >= MAX_DATA_STACK ) {
    ForthVm_Error(self, "Control stack overflow");
    return;
  }

  int newCodePtr;

  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = NATIVE_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = ForthVm_LookupNativeId(self, Instruction_Swap);  

  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = TO_RET_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = 0;

  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = TO_RET_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = 0;

  self->dataStack[self->dataStackPtr] = self->hereCodePtr;
  self->dataStackPtr++;
}
//@-node:leonardoce.20090629082550.91:Instruction_Do
//@+node:leonardoce.20090629082550.92:Instruction_Leave

void Instruction_Leave(ForthVm *self) {
  if( self->internalState == VM_INTERPRETER ) {
    ForthVm_Error(self, "Invalid \"leave\" in interpreter mode.");
    return;
  }

  int newCodePtr;
  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = RET_FROM_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = 0;

  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = RET_FROM_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = 0;

  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = NATIVE_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = ForthVm_LookupNativeId(self, Instruction_Drop);

  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = NATIVE_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = ForthVm_LookupNativeId(self, Instruction_Drop);

  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = JUMP_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = 0;
}
//@-node:leonardoce.20090629082550.92:Instruction_Leave
//@+node:leonardoce.20090629082550.93:Instruction_InternalPlusLoop

/* Giocoleria sullo stack di ritorno per i loop */
void Instruction_InternalPlusLoop(ForthVm *self) {
  if( self->dataStackPtr == 0 ) {
    ForthVm_Error(self, "Data stack underflow");
    return;
  }

  if( self->retStackPtr < 2 ) {
    ForthVm_Error(self, "Return stack underflow");
    return;
  }

  self->retStack[self->retStackPtr-1] += self->dataStack[self->dataStackPtr-1];
  self->dataStack[self->dataStackPtr-1] = (self->retStack[self->retStackPtr-1] == self->retStack[self->retStackPtr-2]);
}
//@-node:leonardoce.20090629082550.93:Instruction_InternalPlusLoop
//@+node:leonardoce.20090629082550.94:Priv_Leave_Resolve

void Priv_Leave_Resolve(ForthVm *self, int addr) {
  /* Risolve gli indirizzi dei leave */
  int i;

  for(i=addr; i<self->hereCodePtr; i++) {
    if(self->codeSpace[i].instructionType == JUMP_INSTRUCTION
       && self->codeSpace[i].instructionDest == 0 ) {
      self->codeSpace[i].instructionDest = self->hereCodePtr;
    }
  }
}
//@-node:leonardoce.20090629082550.94:Priv_Leave_Resolve
//@+node:leonardoce.20090629082550.95:Instruction_InternalUnloop

void Instruction_InternalUnloop(ForthVm *self) {
  if( self->retStackPtr < 2 ) {
    ForthVm_Error(self, "Return stack underflow.");
    return;
  }

  self->retStackPtr-=2;
}
//@-node:leonardoce.20090629082550.95:Instruction_InternalUnloop
//@+node:leonardoce.20090629082550.96:Instruction_Unloop

void Instruction_Unloop(ForthVm *self) {
  if( self->internalState == VM_INTERPRETER ) {
    ForthVm_Error(self, "Invalid unloop in interpreter mode.");
    return;
  }

  int newCodePtr;
  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = NATIVE_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = ForthVm_LookupNativeId(self, Instruction_InternalUnloop);  
}
//@-node:leonardoce.20090629082550.96:Instruction_Unloop
//@+node:leonardoce.20090629082550.97:Instruction_PlusLoop

void Instruction_PlusLoop(ForthVm *self) {
  if( self->internalState == VM_INTERPRETER ) {
    ForthVm_Error(self, "Invalid (+loop) in interpreter mode.");
    return;
  }

  if( self->dataStackPtr == 0 ) {
    ForthVm_Error(self, "Data stack underflow.");
    return;
  }

  int newCodePtr;
  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = NATIVE_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = ForthVm_LookupNativeId(self, Instruction_InternalPlusLoop);  

  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = JFALSE_INSTRUCTION;
  self->dataStackPtr--;
  self->codeSpace[newCodePtr].instructionDest = self->dataStack[self->dataStackPtr];  

  Priv_Leave_Resolve(self, self->dataStack[self->dataStackPtr]);

  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = NATIVE_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = ForthVm_LookupNativeId(self, Instruction_InternalUnloop);    
}
//@-node:leonardoce.20090629082550.97:Instruction_PlusLoop
//@+node:leonardoce.20090629082550.98:Instruction_Loop

void Instruction_Loop(ForthVm *self) {
  if( self->internalState == VM_INTERPRETER ) {
    ForthVm_Error(self, "Invalid (+loop) in interpreter mode.");
    return;
  }

  if( self->dataStackPtr == 0 ) {
    ForthVm_Error(self, "Data stack underflow.");
    return;
  }

  int newCodePtr;
  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = DATAPUSH_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = 1;

  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = NATIVE_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = ForthVm_LookupNativeId(self, Instruction_InternalPlusLoop);  

  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = JFALSE_INSTRUCTION;
  self->dataStackPtr--;
  self->codeSpace[newCodePtr].instructionDest = self->dataStack[self->dataStackPtr];  

  Priv_Leave_Resolve(self, self->dataStack[self->dataStackPtr]);

  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = NATIVE_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = ForthVm_LookupNativeId(self, Instruction_InternalUnloop);  
}
//@-node:leonardoce.20090629082550.98:Instruction_Loop
//@+node:leonardoce.20090629082550.99:Instruction_Exit

void Instruction_Exit(ForthVm *self) {
  if( self->internalState == VM_INTERPRETER ) {
    ForthVm_Error(self, "Invalid exit in interpreter mode.");
    return;
  }

  int newCodePtr;
  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = RET_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = 0;
}
//@-node:leonardoce.20090629082550.99:Instruction_Exit
//@+node:leonardoce.20090629082550.100:Instruction_Begin

void Instruction_Begin(ForthVm *self) {
  if( self->internalState == VM_INTERPRETER ) {
    ForthVm_Error(self, "Invalid begin in interpreter mode.");
    return;
  }

  if( self->dataStackPtr >= MAX_DATA_STACK ) {
    ForthVm_Error(self, "Data stack overflow");
    return;
  }

  self->dataStack[self->dataStackPtr] = self->hereCodePtr;
  self->dataStackPtr++;
}
//@-node:leonardoce.20090629082550.100:Instruction_Begin
//@+node:leonardoce.20090629082550.101:Instruction_Until

void Instruction_Until(ForthVm *self) {
  if( self->internalState == VM_INTERPRETER ) {
    ForthVm_Error(self, "Invalid until in interpreter mode.");
    return;
  }

  if( self->dataStackPtr == 0 ) {
    ForthVm_Error(self, "Data stack underflow");
    return;
  }

  self->dataStackPtr--;

  int newCodePtr;
  newCodePtr = ForthVm_AllocateForthInstruction(self);
  self->codeSpace[newCodePtr].instructionType = JFALSE_INSTRUCTION;
  self->codeSpace[newCodePtr].instructionDest = self->dataStack[self->dataStackPtr];

}
//@-node:leonardoce.20090629082550.101:Instruction_Until
//@+node:leonardoce.20090629082550.102:ForthVm_RegistraIstruzioniFlow

void ForthVm_RegistraIstruzioniFlow(ForthVm *self) {
  ForthVm_RegisterNativeInstruction(self, "if", Instruction_If);
  ForthVm_RegisterNativeInstruction(self, "then", Instruction_Then);
  ForthVm_RegisterNativeInstruction(self, "else", Instruction_Else);
  ForthVm_RegisterNativeInstruction(self, "do", Instruction_Do);
  ForthVm_RegisterNativeInstruction(self, "+loop", Instruction_PlusLoop);
  ForthVm_RegisterNativeInstruction(self, "loop", Instruction_Loop);
  ForthVm_RegisterNativeInstruction(self, "(+loop)", Instruction_InternalPlusLoop);
  ForthVm_RegisterNativeInstruction(self, "exit", Instruction_Exit);
  ForthVm_RegisterNativeInstruction(self, "begin", Instruction_Begin);
  ForthVm_RegisterNativeInstruction(self, "until", Instruction_Until);
  ForthVm_RegisterNativeInstruction(self, "leave", Instruction_Leave);
  ForthVm_RegisterNativeInstruction(self, "(unloop)", Instruction_InternalUnloop);
  ForthVm_RegisterNativeInstruction(self, "unloop", Instruction_Unloop);

  ForthVm_MarkImmediate(self, "if");
  ForthVm_MarkImmediate(self, "then");
  ForthVm_MarkImmediate(self, "else");
  ForthVm_MarkImmediate(self, "do");
  ForthVm_MarkImmediate(self, "+loop");
  ForthVm_MarkImmediate(self, "leave");
  ForthVm_MarkImmediate(self, "loop");
  ForthVm_MarkImmediate(self, "unloop");
  ForthVm_MarkImmediate(self, "begin");
  ForthVm_MarkImmediate(self, "until");
  ForthVm_MarkImmediate(self, "exit");
}
//@-node:leonardoce.20090629082550.102:ForthVm_RegistraIstruzioniFlow
//@-others
//@-node:leonardoce.20090629082550.87:@thin quattro_istruzioni_flow.c
//@-leo
