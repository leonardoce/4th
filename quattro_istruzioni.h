//@+leo-ver=4-thin
//@+node:leonardoce.20090629082550.189:@thin quattro_istruzioni.h
//@@language c
#ifndef __QUATTRO_ISTRUZIONI
#define __QUATTRO_ISTRUZIONI

#include "quattro_vm.h"

void Instruction_Colon(ForthVm *self);
void Instruction_Semicolon(ForthVm *self);
void Instruction_Parse(ForthVm *self);
void Instruction_Drop(ForthVm *self);
void Instruction_Rot(ForthVm *self);
void Instruction_Dup(ForthVm *self);
void Instruction_Pick(ForthVm *self);
void Instruction_Immediate(ForthVm *self);
void Instruction_Here(ForthVm *self);
void Instruction_SQuote(ForthVm *self);
void Instruction_Create(ForthVm *self);
void Instruction_Allot(ForthVm *self);
void Instruction_Store(ForthVm *self);
void Instruction_Fetch(ForthVm *self);
void Instruction_CStore(ForthVm *self);
void Instruction_CFetch(ForthVm *self);
void Instruction_Cells(ForthVm *self);
void Instruction_Does(ForthVm *self);
void Instruction_CodeDoesJump(ForthVm *self);
void Instruction_SaveOnFile(ForthVm *self);
void Instruction_LoadFile(ForthVm *self);
void Instruction_LoadString(ForthVm *self);
void Instruction_Dot(ForthVm *self);
void Instruction_DotS(ForthVm *self);
void Instruction_DotR(ForthVm *self);
void Instruction_RPStore(ForthVm *self);
void Instruction_SPStore(ForthVm *self);
void Instruction_RPFetch(ForthVm *self);
void Instruction_SPFetch(ForthVm *self);
void Instruction_Emit(ForthVm *self);
void Instruction_RFrom(ForthVm *self);
void Instruction_ToR(ForthVm *self);
void Instruction_RFetch(ForthVm *self);
void Instruction_Tick(ForthVm *self);
void Instruction_Execute(ForthVm *self);
void Instruction_Swap(ForthVm *self);
void Instruction_I(ForthVm *self);
void Instruction_J(ForthVm *self);
void Instruction_Loop(ForthVm *self);
void Instruction_TraceStore(ForthVm *self);
void Instruction_TraceWidthStore(ForthVm *self);
void Instruction_WordTraceStore(ForthVm *self);
void Instruction_Words(ForthVm *self);
void Instruction_CompileComma(ForthVm *self);
void Instruction_Literal(ForthVm *self);
void Instruction_StateFetch(ForthVm *self);
void Instruction_Bye(ForthVm *self);

void ForthVm_RegistraIstruzioniAritmetiche(ForthVm *self);
void ForthVm_RegistraIstruzioniWordlist(ForthVm *self);
void ForthVm_RegistraIstruzioniFfi(ForthVm *self);
void ForthVm_RegistraIstruzioniFlow(ForthVm *self);

#endif
//@-node:leonardoce.20090629082550.189:@thin quattro_istruzioni.h
//@-leo
