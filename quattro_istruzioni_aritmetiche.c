//@+leo-ver=4-thin
//@+node:leonardoce.20090629082550.51:@thin quattro_istruzioni_aritmetiche.c
//@@language c
//@@tabwidth -4
//@+others
//@+node:leonardoce.20090629082550.52:Instruction_Add
#include <stdio.h>
#include <string.h>
#include "quattro_istruzioni.h"
#include "quattro_debug.h"

/**
 * Istruzioni aritmetiche
 */

void Instruction_Add(ForthVm *self) {
  if(self->dataStackPtr<2) {
    ForthVm_Error(self, "data stack underrun");
    return;
  }

  self->dataStack[self->dataStackPtr-2]+=self->dataStack[self->dataStackPtr-1];
  self->dataStackPtr--;
}
//@-node:leonardoce.20090629082550.52:Instruction_Add
//@+node:leonardoce.20090629082550.53:Instruction_Sub

void Instruction_Sub(ForthVm *self) {
  if(self->dataStackPtr<2) {
    ForthVm_Error(self, "data stack underrun");
    return;
  }

  self->dataStack[self->dataStackPtr-2]-=self->dataStack[self->dataStackPtr-1];
  self->dataStackPtr--;
}
//@-node:leonardoce.20090629082550.53:Instruction_Sub
//@+node:leonardoce.20090629082550.54:Instruction_Mul

void Instruction_Mul(ForthVm *self) {
  if(self->dataStackPtr<2) {
    ForthVm_Error(self, "data stack underrun");
    return;
  }

  self->dataStack[self->dataStackPtr-2]*=self->dataStack[self->dataStackPtr-1];
  self->dataStackPtr--;
}
//@-node:leonardoce.20090629082550.54:Instruction_Mul
//@+node:leonardoce.20090629082550.55:Instruction_Div

void Instruction_Div(ForthVm *self) {
  if(self->dataStackPtr<2) {
    ForthVm_Error(self, "data stack underrun");
    return;
  }

  if(self->dataStack[self->dataStackPtr-1] == 0 ) {
    self->dataStack[self->dataStackPtr-2]=0xFFFF;
  } else {
    self->dataStack[self->dataStackPtr-2]/=self->dataStack[self->dataStackPtr-1];
  }

  self->dataStackPtr--;
}
//@-node:leonardoce.20090629082550.55:Instruction_Div
//@+node:leonardoce.20090629082550.56:Instruction_SlashMod

void Instruction_SlashMod(ForthVm *self) {
  if(self->dataStackPtr<2) {
    ForthVm_Error(self, "data stack underrun");
    return;
  }

  if(self->dataStack[self->dataStackPtr-1] == 0 ) {
    self->dataStack[self->dataStackPtr-2]=0xFFFF;
  } else {
    int q = self->dataStack[self->dataStackPtr-2] / self->dataStack[self->dataStackPtr-1];
    int r = self->dataStack[self->dataStackPtr-2] % self->dataStack[self->dataStackPtr-1];
    self->dataStack[self->dataStackPtr-1]=q;
    self->dataStack[self->dataStackPtr-2]=r;
  }
}
//@-node:leonardoce.20090629082550.56:Instruction_SlashMod
//@+node:leonardoce.20090629082550.57:Instruction_Less

void Instruction_Less(ForthVm *self) {
  if(self->dataStackPtr<2) {
    ForthVm_Error(self, "data stack underrun");
    return;
  }

  self->dataStack[self->dataStackPtr-2] = (self->dataStack[self->dataStackPtr-2] < self->dataStack[self->dataStackPtr-1]);
  self->dataStackPtr--;
}
//@-node:leonardoce.20090629082550.57:Instruction_Less
//@+node:leonardoce.20090629082550.58:Instruction_More

void Instruction_More(ForthVm *self) {
  if(self->dataStackPtr<2) {
    ForthVm_Error(self, "data stack underrun");
    return;
  }

  self->dataStack[self->dataStackPtr-2] = (self->dataStack[self->dataStackPtr-2] > self->dataStack[self->dataStackPtr-1]);
  self->dataStackPtr--;
}
//@-node:leonardoce.20090629082550.58:Instruction_More
//@+node:leonardoce.20090629082550.59:Instruction_LessEqual

void Instruction_LessEqual(ForthVm *self) {
  if(self->dataStackPtr<2) {
    ForthVm_Error(self, "data stack underrun");
    return;
  }

  self->dataStack[self->dataStackPtr-2] = (self->dataStack[self->dataStackPtr-2] <= self->dataStack[self->dataStackPtr-1]);
  self->dataStackPtr--;
}
//@-node:leonardoce.20090629082550.59:Instruction_LessEqual
//@+node:leonardoce.20090629082550.60:Instruction_MoreEqual

void Instruction_MoreEqual(ForthVm *self) {
  if(self->dataStackPtr<2) {
    ForthVm_Error(self, "data stack underrun");
    return;
  }

  self->dataStack[self->dataStackPtr-2] = (self->dataStack[self->dataStackPtr-2] >= self->dataStack[self->dataStackPtr-1]);
  self->dataStackPtr--;
}
//@-node:leonardoce.20090629082550.60:Instruction_MoreEqual
//@+node:leonardoce.20090629082550.61:Instruction_Equal

void Instruction_Equal(ForthVm *self) {
  if(self->dataStackPtr<2) {
    ForthVm_Error(self, "data stack underrun");
    return;
  }

  self->dataStack[self->dataStackPtr-2] = (self->dataStack[self->dataStackPtr-2] == self->dataStack[self->dataStackPtr-1]);
  self->dataStackPtr--;
}
//@-node:leonardoce.20090629082550.61:Instruction_Equal
//@+node:leonardoce.20090629082550.62:Instruction_And

void Instruction_And(ForthVm *self) {
  if(self->dataStackPtr<2) {
    ForthVm_Error(self, "data stack underrun");
    return;
  }

  self->dataStack[self->dataStackPtr-2] = (self->dataStack[self->dataStackPtr-2] & self->dataStack[self->dataStackPtr-1]);
  self->dataStackPtr--;
}
//@-node:leonardoce.20090629082550.62:Instruction_And
//@+node:leonardoce.20090629082550.63:Instruction_Or

void Instruction_Or(ForthVm *self) {
  if(self->dataStackPtr<2) {
    ForthVm_Error(self, "data stack underrun");
    return;
  }

  self->dataStack[self->dataStackPtr-2] = (self->dataStack[self->dataStackPtr-2] | self->dataStack[self->dataStackPtr-1]);
  self->dataStackPtr--;
}
//@-node:leonardoce.20090629082550.63:Instruction_Or
//@+node:leonardoce.20090629082550.64:Instruction_Invert

void Instruction_Invert(ForthVm *self) {
  if(self->dataStackPtr<1) {
    ForthVm_Error(self, "data stack underrun");
    return;
  }

  self->dataStack[self->dataStackPtr-1] = (~self->dataStack[self->dataStackPtr-1]);
}
//@-node:leonardoce.20090629082550.64:Instruction_Invert
//@+node:leonardoce.20090629082550.65:Instruction_LShift

void Instruction_LShift(ForthVm *self) {
  if(self->dataStackPtr<2) {
    ForthVm_Error(self, "data stack underrun");
    return;
  }

  self->dataStack[self->dataStackPtr-2]=self->dataStack[self->dataStackPtr-2] << self->dataStack[self->dataStackPtr-1];
  self->dataStackPtr--;
}
//@-node:leonardoce.20090629082550.65:Instruction_LShift
//@+node:leonardoce.20090629082550.66:Instruction_RShift

void Instruction_RShift(ForthVm *self) {
  if(self->dataStackPtr<2) {
    ForthVm_Error(self, "data stack underrun");
    return;
  }

  self->dataStack[self->dataStackPtr-2]=self->dataStack[self->dataStackPtr-2] >> self->dataStack[self->dataStackPtr-1];
  self->dataStackPtr--;
}
//@-node:leonardoce.20090629082550.66:Instruction_RShift
//@+node:leonardoce.20090629082550.67:ForthVm_RegistraIstruzioniAritmetiche

void ForthVm_RegistraIstruzioniAritmetiche(ForthVm *self) {
  ForthVm_RegisterNativeInstruction(self, "+", Instruction_Add);
  ForthVm_RegisterNativeInstruction(self, "-", Instruction_Sub);
  ForthVm_RegisterNativeInstruction(self, "*", Instruction_Mul);
  ForthVm_RegisterNativeInstruction(self, "/", Instruction_Div);
  ForthVm_RegisterNativeInstruction(self, "<", Instruction_Less);
  ForthVm_RegisterNativeInstruction(self, ">", Instruction_More);
  ForthVm_RegisterNativeInstruction(self, "<=", Instruction_LessEqual);
  ForthVm_RegisterNativeInstruction(self, ">=", Instruction_MoreEqual);
  ForthVm_RegisterNativeInstruction(self, "=", Instruction_Equal);
  ForthVm_RegisterNativeInstruction(self, "and", Instruction_And);
  ForthVm_RegisterNativeInstruction(self, "or", Instruction_Or);
  ForthVm_RegisterNativeInstruction(self, "invert", Instruction_Invert);
  ForthVm_RegisterNativeInstruction(self, "/mod", Instruction_SlashMod);
  ForthVm_RegisterNativeInstruction(self, "lshift", Instruction_LShift);
  ForthVm_RegisterNativeInstruction(self, "rshift", Instruction_RShift);
}
//@-node:leonardoce.20090629082550.67:ForthVm_RegistraIstruzioniAritmetiche
//@-others

//@-node:leonardoce.20090629082550.51:@thin quattro_istruzioni_aritmetiche.c
//@-leo
