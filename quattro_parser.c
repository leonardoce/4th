//@+leo-ver=4-thin
//@+node:leonardoce.20090629082550.147:@thin quattro_parser.c
//@@language c
//@@tabwidth -4
//@+others
//@+node:leonardoce.20090629082550.148:ForthWord_NewExecute
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quattro_parser.h"

#define TRUE 1
#define FALSE 0

/**
 * FORTHWORD 
 */

ForthWord *ForthWord_NewExecute(const char *fileName, const char *forthString, int row, int col) {
  ForthWord *self = (ForthWord *)malloc(sizeof(ForthWord));
  self->fileName=strdup( fileName );
  self->stringValue=strdup( forthString );
  self->intValue=0;
  self->doubleValue=0;
  self->wordType = EXECUTE_WORD;
  self->row=row;
  self->col=col;
  return self;
}
//@-node:leonardoce.20090629082550.148:ForthWord_NewExecute
//@+node:leonardoce.20090629082550.149:ForthWord_NewInt

ForthWord *ForthWord_NewInt(const char *fileName, int value, int row, int col) {
  ForthWord *self = (ForthWord *)malloc(sizeof(ForthWord));
  self->fileName=strdup( fileName );
  self->stringValue=NULL;
  self->intValue=value;
  self->doubleValue=0;
  self->wordType = INT_WORD;
  self->row=row;
  self->col=col;
  return self;
}
//@-node:leonardoce.20090629082550.149:ForthWord_NewInt
//@+node:leonardoce.20090629082550.150:ForthWord_NewDouble

ForthWord *ForthWord_NewDouble(const char *fileName, double value, int row, int col) {
  ForthWord *self = (ForthWord *)malloc(sizeof(ForthWord));
  self->fileName=strdup( fileName );
  self->stringValue=NULL;
  self->intValue=0;
  self->doubleValue=value;
  self->wordType = DOUBLE_WORD;
  self->row=row;
  self->col=col;
  return self;
}
//@-node:leonardoce.20090629082550.150:ForthWord_NewDouble
//@+node:leonardoce.20090629082550.151:ForthWord_Delete

void ForthWord_Delete(ForthWord *self) {
  if( self->stringValue!=NULL ) {
    free(self->stringValue);
    free(self->fileName);
  }

  free(self);
}
//@-node:leonardoce.20090629082550.151:ForthWord_Delete
//@+node:leonardoce.20090629082550.152:ForthWord_Dump

void ForthWord_Dump(ForthWord *self) {
  if(self->wordType==EXECUTE_WORD) {
    printf("<execute filename=\"%s\" value=\"%s\"/>", self->fileName, self->stringValue);
  } else if(self->wordType==INT_WORD) {
    printf("<int filename=\"%s\" value=\"%i\"/>", self->fileName, self->intValue);
  } else if(self->wordType==DOUBLE_WORD) {
    printf("<double filename=\"%s\" value=\"%f\"/>", self->fileName, self->doubleValue);
  } else {
    printf("<unknownWord filename=\"%s\" />", self->fileName);
  }
}
//@-node:leonardoce.20090629082550.152:ForthWord_Dump
//@+node:leonardoce.20090629082550.153:forthIsSpace

/**
 * FORTHSTREAM 
 */

int forthIsSpace( char c ) {
  if( c != ' ' && c != '\t' && c != '\n' && c != '\r' ) {
    return FALSE;
  } else {
    return TRUE;
  }
}
//@-node:leonardoce.20090629082550.153:forthIsSpace
//@+node:leonardoce.20090629082550.154:ForthStream_NewForFile

ForthStream *ForthStream_NewForFile( const char *fileName ) {
  ForthStream *self=(ForthStream*)malloc(sizeof(ForthStream));
  FILE *in;

  self->index=0;
  self->row=1;
  self->col=1;
  self->fileName=strdup(fileName);

  in=fopen(fileName,"rb");
  if(in==NULL) {
    self->fileSize=0;
    self->buffer=NULL;
    printf("Open error: %s",fileName);
  } else {
    /* read file in buffer */
    fseek(in, 0, SEEK_END);
    self->fileSize=ftell(in);
    self->buffer=(char *)malloc(sizeof(char)*self->fileSize);

    rewind(in);
    fread(self->buffer, 1, self->fileSize, in);
    fclose(in);
  }

  return self;
}
//@-node:leonardoce.20090629082550.154:ForthStream_NewForFile
//@+node:leonardoce.20090629082550.155:ForthStream_NewForBuffer

ForthStream *ForthStream_NewForBuffer( const char *fileName, const char *buffer ) {
  ForthStream *self=(ForthStream*)malloc(sizeof(ForthStream));

  self->index=0;
  self->row=1;
  self->col=1;
  self->fileName=strdup(fileName);
  self->buffer=strdup(buffer);
  self->fileSize=strlen(self->buffer);

  return self;
}
//@-node:leonardoce.20090629082550.155:ForthStream_NewForBuffer
//@+node:leonardoce.20090629082550.156:ForthStream_ResetForBuffer

void ForthStream_ResetForBuffer(ForthStream *self, const char *fileName, const char *buffer) {
  self->index=0;
  self->row=1;
  self->col=1;

  if(self->fileName!=NULL) {
    free(self->fileName);
  }

  self->fileName=strdup(fileName);

  if(self->buffer!=NULL) {
    free(self->buffer);
  }

  self->buffer=strdup(buffer);
  self->fileSize=strlen(self->buffer);
}
//@-node:leonardoce.20090629082550.156:ForthStream_ResetForBuffer
//@+node:leonardoce.20090629082550.157:ForthStream_Eof

int ForthStream_Eof( ForthStream *self ) {
  if(self->index >= self->fileSize) {
    return TRUE;
  } else {
    return FALSE;
  }
}
//@-node:leonardoce.20090629082550.157:ForthStream_Eof
//@+node:leonardoce.20090629082550.158:ForthStream_Getc

char ForthStream_Getc( ForthStream *self ) {
  char result;

  if(self->index >= self->fileSize) {
    result=EOF;
  } else {
    result=self->buffer[self->index];
    self->index++;
    self->col++;
    if(result==10) {
      self->row++;
      self->col=1;
    }
  }

  return result;
}
//@-node:leonardoce.20090629082550.158:ForthStream_Getc
//@+node:leonardoce.20090629082550.159:ForthStream_Ungetc

void ForthStream_Ungetc( ForthStream *self ) {
  if(self->index > 0 ) {
    self->index--;
  }
} 
//@-node:leonardoce.20090629082550.159:ForthStream_Ungetc
//@+node:leonardoce.20090629082550.160:ForthStream_SkipSpaces

void ForthStream_SkipSpaces( ForthStream *in ) {
  while( !ForthStream_Eof(in) ) {
    char c = ForthStream_Getc(in);
    if( !forthIsSpace(c) ) {
      ForthStream_Ungetc( in );
      break;
    }
  }
}
//@-node:leonardoce.20090629082550.160:ForthStream_SkipSpaces
//@+node:leonardoce.20090629082550.161:ForthStream_Delete

void ForthStream_Delete(ForthStream *self) {
  if(self->buffer != NULL) {
    free(self->buffer);
  }
  if(self->fileName != NULL) {
    free(self->fileName);
  }

  free(self);
}
//@-node:leonardoce.20090629082550.161:ForthStream_Delete
//@+node:leonardoce.20090629082550.162:ForthStream_ParseWord

ForthWord *ForthStream_ParseWord( ForthStream *self ) {
  char firstChar = 0;
  char c;
  char maxString[4096];    
  int stringPtr = 0;
  int onlyNumbers=TRUE;
  int onlyNumbersAndDot=TRUE;
  int dotsFound=0;

  if(ForthStream_Eof(self)) {
    return NULL; 
  }

  for( stringPtr=0; stringPtr<4096; stringPtr++ ) {
    maxString[stringPtr]=0;
  }

  stringPtr=0;

  ForthStream_SkipSpaces(self);
  firstChar = ForthStream_Getc( self );

  if( firstChar==EOF ) {
    return NULL;
  }

  onlyNumbers = '0'<=firstChar && firstChar<='9';
  onlyNumbersAndDot = onlyNumbers || firstChar=='.';

  maxString[stringPtr] = firstChar;
  stringPtr++;

  while(!ForthStream_Eof(self)) {
    c = ForthStream_Getc(self);
    if(c==EOF) {
      break;
    }

    if(forthIsSpace(c)) {
      break;
    } else {
      onlyNumbers = onlyNumbers && '0'<=c && c<='9';
      onlyNumbersAndDot = onlyNumbersAndDot && (('0'<=c && c<='9') || c=='.');

      if(c=='.') {
	dotsFound++;
      }

      if(stringPtr<4095) {
	maxString[stringPtr]=c;
	stringPtr++;
      }
    }
  }

  if(onlyNumbers) {
    return ForthWord_NewInt(self->fileName, atoi(maxString), self->row, self->col);
  } else if(onlyNumbersAndDot && dotsFound==1) {
    return ForthWord_NewDouble(self->fileName, atof(maxString), self->row, self->col);
  } else {
    return ForthWord_NewExecute(self->fileName, maxString, self->row, self->col );
  }
}
//@-node:leonardoce.20090629082550.162:ForthStream_ParseWord
//@-others


//@-node:leonardoce.20090629082550.147:@thin quattro_parser.c
//@-leo
