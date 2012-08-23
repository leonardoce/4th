//@+leo-ver=4-thin
//@+node:leonardoce.20090629082550.69:@thin quattro_istruzioni_ffi.c
//@@language c
//@@tabwidth -4
//@+others
//@+node:leonardoce.20090629082550.70:int
#include <stdio.h>
#include <string.h>
#include "quattro_istruzioni.h"
#include "quattro_debug.h"

#ifdef OS_WINDOWS
#include <windows.h>
#endif

#ifdef OS_LINUX
#include <dlfcn.h>
#endif

typedef int (*genericProc)();
ForthVm *currentVm;

void Instruction_CMalloc(ForthVm *self) {
  /* ( u -- addr ) */
  if( self->dataStackPtr < 1 ) {
    ForthVm_Error(self, "Data stack underflow.");
    return;
  }

  int len=self->dataStack[self->dataStackPtr-1];
  void *newMem = (void *)malloc(len+1);
  self->dataStack[self->dataStackPtr-1]=(int)newMem;
}
//@-node:leonardoce.20090629082550.70:int
//@+node:leonardoce.20090629082550.71:Instruction_CFree

void Instruction_CFree(ForthVm *self) {
  /* ( addr -- ) */
  if( self->dataStackPtr < 1 ) {
    ForthVm_Error(self, "Data stack underflow.");
    return;
  }

  self->dataStackPtr--;

  int addr=self->dataStack[self->dataStackPtr];
  free((void *)addr);
}
//@-node:leonardoce.20090629082550.71:Instruction_CFree
//@+node:leonardoce.20090629082550.72:Instruction_CMemStore

void Instruction_CMemStore(ForthVm *self) {
  /* ( data c-addr -- ) */

  if( self->dataStackPtr < 2 ) {
    ForthVm_Error(self, "Data stack underflow.");
    return;
  }

  char *addr=(char *)self->dataStack[self->dataStackPtr-1];
  int data=self->dataStack[self->dataStackPtr-2];
  self->dataStackPtr-=2;

  *addr=(char)data;
}
//@-node:leonardoce.20090629082550.72:Instruction_CMemStore
//@+node:leonardoce.20090629082550.73:Instruction_CMemCellStore

void Instruction_CMemCellStore(ForthVm *self) {
  /* ( data c-addr -- ) */

  if( self->dataStackPtr < 2 ) {
    ForthVm_Error(self, "Data stack underflow.");
    return;
  }

  int *addr=(int *)self->dataStack[self->dataStackPtr-1];
  int data=self->dataStack[self->dataStackPtr-2];
  self->dataStackPtr-=2;

  *addr=(int)data;
}
//@-node:leonardoce.20090629082550.73:Instruction_CMemCellStore
//@+node:leonardoce.20090629082550.74:Instruction_CMemFetch

void Instruction_CMemFetch(ForthVm *self) {
  /* ( c-addr -- c ) */

  if( self->dataStackPtr < 1 ) {
    ForthVm_Error(self, "Data stack overflow.");
    return;
  }

  char *addr=(char *)self->dataStack[self->dataStackPtr-1];
  self->dataStack[self->dataStackPtr-1]=*addr;
}
//@-node:leonardoce.20090629082550.74:Instruction_CMemFetch
//@+node:leonardoce.20090629082550.75:Instruction_CMemCellFetch

void Instruction_CMemCellFetch(ForthVm *self) {
  /* ( c-addr -- c ) */

  if( self->dataStackPtr < 1 ) {
    ForthVm_Error(self, "Data stack overflow.");
    return;
  }

  int *addr=(int *)self->dataStack[self->dataStackPtr-1];
  self->dataStack[self->dataStackPtr-1]=*addr;
}
//@-node:leonardoce.20090629082550.75:Instruction_CMemCellFetch
//@+node:leonardoce.20090629082550.76:Instruction_CLoadLibrary

void Instruction_CLoadLibrary(ForthVm *self) {
  /* ( libname -- modaddress ) */
  if( self->dataStackPtr < 1 ) {
    ForthVm_Error(self, "Data stack underflow.");
    return;
  }

  int result;

#ifdef OS_WINDOWS
  result=(int)LoadLibrary((char *)self->dataStack[self->dataStackPtr-1]);
#endif

#ifdef OS_LINUX
  result=(int)dlopen((char *)self->dataStack[self->dataStackPtr-1], RTLD_LAZY);
#endif

  self->dataStack[self->dataStackPtr-1]=result;
}
//@-node:leonardoce.20090629082550.76:Instruction_CLoadLibrary
//@+node:leonardoce.20090629082550.77:Instruction_CFreeLibrary

void Instruction_CFreeLibrary(ForthVm *self) {
  /* ( modaddress -- ) */
  if( self->dataStackPtr < 1 ) {
    ForthVm_Error(self, "Data stack underflow.");
    return;
  }

  int result;

#ifdef OS_WINDOWS
  result=(int)FreeLibrary((void *)self->dataStack[self->dataStackPtr-1]);
#endif

#ifdef OS_LINUX
  result=(int)dlclose((void *)self->dataStack[self->dataStackPtr-1]);
#endif

  self->dataStackPtr--;
}
//@-node:leonardoce.20090629082550.77:Instruction_CFreeLibrary
//@+node:leonardoce.20090629082550.78:Instruction_CGetProcAddress

void Instruction_CGetProcAddress(ForthVm *self) {
  /* ( libaddr procname -- ) */
  if( self->dataStackPtr < 2 ) {
    ForthVm_Error(self, "Data stack underflow.");
    return;
  }

  int result;

#ifdef OS_WINDOWS
  result=(int)GetProcAddress((void *)self->dataStack[self->dataStackPtr-2], (char *)(void *)self->dataStack[self->dataStackPtr-1]);
#endif

#ifdef OS_LINUX
  result=(int)dlsym((void *)self->dataStack[self->dataStackPtr-2], (char *)(void *)self->dataStack[self->dataStackPtr-1]);
#endif
  self->dataStackPtr--;
  self->dataStack[self->dataStackPtr-1]=result;
}
//@-node:leonardoce.20090629082550.78:Instruction_CGetProcAddress
//@+node:leonardoce.20090629082550.79:Instruction_CCall

void Instruction_CCall(ForthVm *self) {
  /* ( arg*n n procaddr -- result ) */
  if( self->dataStackPtr < 2 ) {
    ForthVm_Error(self, "Data stack underflow.");
    return;
  }

  int procaddr = self->dataStack[self->dataStackPtr-1];
  int argscount = self->dataStack[self->dataStackPtr-2];
  int result = 0;

  if( self->dataStackPtr < (2+argscount) ) {
    ForthVm_Error(self, "Data stack underflow.");
    return;
  }

  genericProc myProc = (genericProc) procaddr;

  if( myProc != NULL ) {
    if( argscount == 0 ) {
      result = myProc( );
    } else if( argscount == 1 ) {
      result = myProc( self->dataStack[self->dataStackPtr-3] );
    } else if( argscount == 2 ) {
      result = myProc( self->dataStack[self->dataStackPtr-4], self->dataStack[self->dataStackPtr-3] );
    } else if( argscount == 3 ) {
      result = myProc( self->dataStack[self->dataStackPtr-5], self->dataStack[self->dataStackPtr-4], self->dataStack[self->dataStackPtr-3] );
    } else if( argscount == 4 ) {
      result = myProc( self->dataStack[self->dataStackPtr-6], self->dataStack[self->dataStackPtr-5], self->dataStack[self->dataStackPtr-4], self->dataStack[self->dataStackPtr-3] );
    } else if( argscount == 5 ) {
      result = myProc( self->dataStack[self->dataStackPtr-7], self->dataStack[self->dataStackPtr-6], self->dataStack[self->dataStackPtr-5], self->dataStack[self->dataStackPtr-4], self->dataStack[self->dataStackPtr-3] );
    } else if( argscount == 6 ) {
      result = myProc( self->dataStack[self->dataStackPtr-8], self->dataStack[self->dataStackPtr-7], self->dataStack[self->dataStackPtr-6], self->dataStack[self->dataStackPtr-5], self->dataStack[self->dataStackPtr-4], self->dataStack[self->dataStackPtr-3] );
    } else {
      ForthVm_Error(self, "Call not supported.");
      return;
    }
  }

  self->dataStackPtr-=2+argscount;
  self->dataStackPtr++;
  self->dataStack[self->dataStackPtr-1] = result;
}
//@-node:leonardoce.20090629082550.79:Instruction_CCall
//@+node:leonardoce.20090629082550.80:Instruction_AddrToC

void Instruction_AddrToC(ForthVm *self) {
  // ( addr -- caddr )
  if( self->dataStackPtr < 1 ) {
    ForthVm_Error(self, "Data stack underflow.");
    return;
  }

  self->dataStack[self->dataStackPtr-1]+=(int)&self->dataSpace;
}
//@-node:leonardoce.20090629082550.80:Instruction_AddrToC
//@+node:leonardoce.20090629082550.81:Instruction_OsLinux

void Instruction_OsLinux(ForthVm *self) {
  // ( -- flag )
  if( self->dataStackPtr >= MAX_DATA_STACK ) {
    ForthVm_Error(self, "Data stack underflow.");
    return;
  }

  int result=0;
#ifdef OS_LINUX
  result=1;
#endif

  self->dataStack[self->dataStackPtr]=result;
  self->dataStackPtr++;
}
//@-node:leonardoce.20090629082550.81:Instruction_OsLinux
//@+node:leonardoce.20090629082550.82:Instruction_OsWindows

void Instruction_OsWindows(ForthVm *self) {
  // ( -- flag )
  if( self->dataStackPtr >= MAX_DATA_STACK ) {
    ForthVm_Error(self, "Data stack underflow.");
    return;
  }

  int result=0;
#ifdef OS_WINDOWS
  result=1;
#endif

  self->dataStack[self->dataStackPtr]=result;
  self->dataStackPtr++;
}
//@-node:leonardoce.20090629082550.82:Instruction_OsWindows
//@+node:leonardoce.20090629082550.83:cdeclOneParams

int cdeclOneParams(int p0) {
  ForthVm *self = currentVm;

  int oldPtr = self->instructionPtr;

  self->instructionPtr=p0;
  ForthVm_Run(self);
  self->instructionPtr=oldPtr;
  self->exitFlag=FALSE;
  self->retStackPtr--;

  return 0;
}
//@-node:leonardoce.20090629082550.83:cdeclOneParams
//@+node:leonardoce.20090629082550.84:cdeclTwoParams

int cdeclTwoParams(int p0, int p1) {
  ForthVm *self = currentVm;

  if( self->dataStackPtr >= MAX_DATA_STACK ) {
    ForthVm_Error(self, "Data stack underflow.");
    return 0;
  }
  self->dataStack[self->dataStackPtr++] = p1;

  int oldPtr = self->instructionPtr;

  self->instructionPtr=p0;
  ForthVm_Run(self);
  self->instructionPtr=oldPtr;
  self->exitFlag=FALSE;
  self->retStackPtr--;

  return 0;
}
//@-node:leonardoce.20090629082550.84:cdeclTwoParams
//@+node:leonardoce.20090629082550.85:Instruction_GetCallback

void Instruction_GetCallback(ForthVm *self) {
  // ( nargs -- addr )
  if( self->dataStackPtr < 1 ) {
    ForthVm_Error(self, "Data stack underflow.");
    return;
  }

  currentVm = self;
  int nargs = self->dataStack[self->dataStackPtr-1];

  if( nargs == 1 ) {
    self->dataStack[self->dataStackPtr-1]=(int)&cdeclOneParams;
  } else if( nargs == 1 ) {
    self->dataStack[self->dataStackPtr-2]=(int)&cdeclTwoParams;
  } else {
    ForthVm_Error(self, "Unsupported callback");
    return;
  }
}
//@-node:leonardoce.20090629082550.85:Instruction_GetCallback
//@+node:leonardoce.20090629082550.86:ForthVm_RegistraIstruzioniFfi

void ForthVm_RegistraIstruzioniFfi(ForthVm *self) {
  ForthVm_RegisterNativeInstruction(self, "cmalloc", Instruction_CMalloc);
  ForthVm_RegisterNativeInstruction(self, "cfree", Instruction_CFree);
  ForthVm_RegisterNativeInstruction(self, "cmem!", Instruction_CMemStore);
  ForthVm_RegisterNativeInstruction(self, "cmem@", Instruction_CMemFetch);
  ForthVm_RegisterNativeInstruction(self, "cmemcell!", Instruction_CMemCellStore);
  ForthVm_RegisterNativeInstruction(self, "cmemcell@", Instruction_CMemCellFetch);
  ForthVm_RegisterNativeInstruction(self, "cloadlibrary", Instruction_CLoadLibrary);
  ForthVm_RegisterNativeInstruction(self, "cfreelibrary", Instruction_CFreeLibrary);
  ForthVm_RegisterNativeInstruction(self, "cprocaddress", Instruction_CGetProcAddress);
  ForthVm_RegisterNativeInstruction(self, "ccall", Instruction_CCall);
  ForthVm_RegisterNativeInstruction(self, "addr>c", Instruction_AddrToC);
  ForthVm_RegisterNativeInstruction(self, "oswindows", Instruction_OsWindows);
  ForthVm_RegisterNativeInstruction(self, "oslinux", Instruction_OsLinux);
  ForthVm_RegisterNativeInstruction(self, "getcallback", Instruction_GetCallback);
}
//@-node:leonardoce.20090629082550.86:ForthVm_RegistraIstruzioniFfi
//@-others
//@-node:leonardoce.20090629082550.69:@thin quattro_istruzioni_ffi.c
//@-leo
