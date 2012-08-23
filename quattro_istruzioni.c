//@+leo-ver=4-thin
//@+node:leonardoce.20090629082550.39:@thin quattro_istruzioni.c
//@@language c
//@@tabwidth -4

#include <stdio.h>
#include <string.h>
#include "quattro_istruzioni.h"
#include "quattro_debug.h"

//@+others
//@+node:leonardoce.20090629082550.40:Instruction_Parse
void Instruction_Parse(ForthVm *self) {
  if( self->parser == NULL ) {
    ForthVm_Error(self, "Invalid parser in parse");
    return;
  } 

  if( self->dataStackPtr == 0 ) {
    ForthVm_Error(self, "Data stack underflow.");
    return;
  }

  if( self->dataStackPtr == MAX_DATA_STACK ) {
    ForthVm_Error(self, "Data stack overflow.");
    return;
  }

  char terminatore = (char)self->dataStack[self->dataStackPtr-1];

  int dataPtr = self->hereDataPtr;
  while(!ForthStream_Eof(self->parser)) {
    char c = ForthStream_Getc(self->parser);
    if( self->dataStackPtr >= MAX_DATA_SPACE || c == terminatore ) {
      break;
    } else {
      self->dataSpace[dataPtr] = c;
      dataPtr++;
    }
  }

  self->dataStack[self->dataStackPtr-1] = self->hereDataPtr;
  self->dataStack[self->dataStackPtr] = dataPtr - self->hereDataPtr;
  self->dataStackPtr++;
}
//@-node:leonardoce.20090629082550.40:Instruction_Parse
//@+node:leonardoce.20090629082550.41:Instruction_SQuote

void Instruction_SQuote(ForthVm *self) {
  if( self->parser == NULL ) {
    ForthVm_Error(self, "Invalid parser in S\"");
    return;
  } 

  if( self->internalState == VM_INTERPRETER ) {
    if(self->dataStackPtr+2>=MAX_DATA_STACK) {
      ForthVm_Error(self,"Data stack overflow");
      return;
    }

    /* I dati vengono allocati a partire dal basso */
    int maxTemporaryBuffer = 100;
    int dataPtr = MAX_DATA_SPACE - maxTemporaryBuffer;
    int dataLen = 0;
    while(1) {
      char c = ForthStream_Getc(self->parser);
      if( c == EOF || ForthStream_Eof(self->parser) || dataLen >= maxTemporaryBuffer || c == '\"' ) {
	break;
      } else {
	self->dataSpace[dataPtr+dataLen] = c;
	dataLen++;
      }
    }

    self->dataStack[self->dataStackPtr++] = dataPtr;
    self->dataStack[self->dataStackPtr++] = dataLen;

    return;
  } else {
    int dataPtr = self->hereDataPtr;
    while(1) {
      char c = ForthStream_Getc(self->parser);
      if( c == EOF || ForthStream_Eof(self->parser) || self->hereDataPtr >= MAX_DATA_SPACE || c == '\"' ) {
	break;
      } else {
	self->dataSpace[self->hereDataPtr] = c;
	self->hereDataPtr ++;
      }
    }

    if( self->hereDataPtr < MAX_DATA_SPACE ) {
      self->dataSpace[self->hereDataPtr] = 0;
      self->hereDataPtr ++;
    }

    int newCodePtr;

    newCodePtr = ForthVm_AllocateForthInstruction(self);
    self->codeSpace[newCodePtr].instructionType = DATAPUSH_INSTRUCTION;
    self->codeSpace[newCodePtr].instructionDest = dataPtr;

    newCodePtr = ForthVm_AllocateForthInstruction(self);
    self->codeSpace[newCodePtr].instructionType = DATAPUSH_INSTRUCTION;
    self->codeSpace[newCodePtr].instructionDest = self->hereDataPtr - dataPtr - 1 ;
  }
}
//@-node:leonardoce.20090629082550.41:Instruction_SQuote
//@+node:leonardoce.20090629082550.42:Instruction_LoadFile

void Instruction_LoadFile(ForthVm *self) {
  if( self->internalState != VM_INTERPRETER ) {
    ForthVm_Error(self, "Invalid load in compiler mode" );
    return;
  }

  char maxFileName[256];
  int index=0;
  while(TRUE) {
    char c = ForthStream_Getc(self->parser);
    if( c == EOF || index>=254 ||  c == 10 || c == 13 ) {
      maxFileName[index]='\x0';
      break;
    } else {
      maxFileName[index] = c;
      index++;
    }
  }

  ForthStream *stream = ForthStream_NewForFile( maxFileName );
  ForthStream *oldParser = self->parser;

  self->parser=stream;
  int oldPtr = self->instructionPtr;

  ForthVm_Feed(self);

  self->parser=oldParser;
  self->instructionPtr=oldPtr;

  ForthStream_Delete(stream);
}
//@-node:leonardoce.20090629082550.42:Instruction_LoadFile
//@+node:leonardoce.20090629082550.43:Instruction_LoadString

void Instruction_LoadString(ForthVm *self) {
  if( self->internalState != VM_INTERPRETER ) {
    ForthVm_Error(self, "Invalid load in compiler mode" );
    return;
  }

  if(self->dataStackPtr<2) {
    ForthVm_Error(self, "Data stack underflow");
    return;
  }

  char *buffer = malloc(self->dataStack[self->dataStackPtr-1]+1);
  memcpy(buffer, &self->dataSpace[self->dataStack[self->dataStackPtr-2]], self->dataStack[self->dataStackPtr-1]);
  buffer[self->dataStack[self->dataStackPtr-1]]='\x0';
  self->dataStackPtr-=2;

  ForthStream *stream = ForthStream_NewForBuffer( "<buffer>",  buffer);
  ForthStream *oldParser = self->parser;

  self->parser=stream;
  int oldPtr = self->instructionPtr;

  ForthVm_Feed(self);

  self->parser=oldParser;
  self->instructionPtr=oldPtr;

  ForthStream_Delete(stream);
  free(buffer);
}
//@-node:leonardoce.20090629082550.43:Instruction_LoadString
//@+node:leonardoce.20090629082550.44:Instruction_Emit


/**
 * I/O
 */

void Instruction_Emit(ForthVm *self) {
  if(self->dataStackPtr<1) {
    ForthVm_Error(self, "Data stack underflow.");
    return;
  }

  self->dataStackPtr--;
  printf("%c", self->dataStack[self->dataStackPtr]);
}
//@-node:leonardoce.20090629082550.44:Instruction_Emit
//@+node:leonardoce.20090629082550.45:Instruction_SaveOnFile

/**
 * Manipolazione della VM
 */
void Instruction_SaveOnFile(ForthVm *self) {
  // ( c-addr n -- )

  if(self->dataStackPtr<2) {
    ForthVm_Error(self, "Data stack underflow.");
    return;
  }

  char *fileName = (char *)malloc(self->dataStack[self->dataStackPtr-1]+1);
  memcpy(fileName, self->dataSpace + self->dataStack[self->dataStackPtr-2], self->dataStack[self->dataStackPtr-1]+1);
  fileName[self->dataStack[self->dataStackPtr-1]+1]='\x0';
  OutputStream *out = OutputStream_NewForFile(fileName);

  if(!OutputStream_Status(out)) {
    ForthVm_Error(self, "File open error.");
    OutputStream_Delete(out);
    return;
  }

  ForthVm_SaveOnFile(self, out);
  OutputStream_Delete(out);
  self->dataStackPtr-=2;

  free(fileName);
}
//@-node:leonardoce.20090629082550.45:Instruction_SaveOnFile
//@+node:leonardoce.20090629082550.46:Instruction_TraceStore

void Instruction_TraceStore(ForthVm *self) {
  if(self->dataStackPtr<1) {
    ForthVm_Error(self, "Data stack underflow.");
    return;
  }

  self->dataStackPtr--;
  self->traceEnabled = self->dataStack[self->dataStackPtr];
}
//@-node:leonardoce.20090629082550.46:Instruction_TraceStore
//@+node:leonardoce.20090629082550.47:Instruction_TraceWidthStore

void Instruction_TraceWidthStore(ForthVm *self) {
  if(self->dataStackPtr<1) {
    ForthVm_Error(self, "Data stack underflow.");
    return;
  }

  self->dataStackPtr--;
  self->traceMaxWidth = self->dataStack[self->dataStackPtr];
}
//@-node:leonardoce.20090629082550.47:Instruction_TraceWidthStore
//@+node:leonardoce.20090629082550.48:Instruction_WordTraceStore

void Instruction_WordTraceStore(ForthVm *self) {
  if(self->dataStackPtr<1) {
    ForthVm_Error(self, "Data stack underflow.");
    return;
  }

  self->dataStackPtr--;
  self->wordTraceEnabled = self->dataStack[self->dataStackPtr];
}
//@-node:leonardoce.20090629082550.48:Instruction_WordTraceStore
//@+node:leonardoce.20090629082550.49:Instruction_StateFetch

void Instruction_StateFetch(ForthVm *self) {
  if(self->dataStackPtr>=MAX_DATA_STACK) {
    ForthVm_Error(self, "Data stack overflow.");
    return;
  }

  if( self->internalState == VM_INTERPRETER ) {
    self->dataStack[self->dataStackPtr] = 0;
  } else {
    self->dataStack[self->dataStackPtr] = 1;
  }
  self->dataStackPtr++;
}
//@-node:leonardoce.20090629082550.49:Instruction_StateFetch
//@+node:leonardoce.20090629082550.50:Instruction_Bye

void Instruction_Bye(ForthVm *self) {
  exit(0);
}
//@-node:leonardoce.20090629082550.50:Instruction_Bye
//@-others
//@-node:leonardoce.20090629082550.39:@thin quattro_istruzioni.c
//@-leo
