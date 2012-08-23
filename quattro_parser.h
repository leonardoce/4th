//@+leo-ver=4-thin
//@+node:leonardoce.20090629082550.190:@thin quattro_parser.h
//@@language c
#ifndef __QUATTRO_PARSER_H
#define __QUATTRO_PARSER_H

#include <stdio.h>

//@+others
//@+node:leonardoce.20090629082550.230:ForthWord
/****c* forth/ForthWord
 * NAME
 *   ForthWord
 * FUNCTION
 *   Rappresenta una parola di forth
 * SOURCE
 */
typedef struct ForthWord ForthWord;
struct ForthWord {
  char *fileName;
  char *stringValue;
  int intValue;
  double doubleValue;

  int wordType;
  int row, col;
};

enum ForthWordType {
  UNKNOWN_WORD,
  INT_WORD,
  DOUBLE_WORD,
  EXECUTE_WORD
};

ForthWord *ForthWord_NewExecute(const char *fileName, const char *forthString, int row, int col);
ForthWord *ForthWord_NewInt(const char *fileName, int value, int row, int col);
ForthWord *ForthWord_NewDouble(const char *fileName, double value, int row, int col);
void ForthWord_Delete(ForthWord *self);
void ForthWord_Dump(ForthWord *self);
/****/
//@-node:leonardoce.20090629082550.230:ForthWord
//@+node:leonardoce.20090629082550.231:ForthStream
/****c* forth/ForthStream
 * NAME
 *   ForthStream
 * FUNCTION
 *   Stream di ingresso di parole Forth
 * SOURCE
 */
typedef struct ForthStream ForthStream;
struct ForthStream {
  char *buffer;
  int row, col;
  int index;

  int fileSize;
  char *fileName;
};


ForthStream *ForthStream_NewForFile( const char *fileName );
ForthStream *ForthStream_NewForBuffer( const char *fileName, const char *buffer );
void ForthStream_ResetForBuffer(ForthStream *self, const char *fileName, const char *buffer);
void ForthStream_Delete(ForthStream *self);
ForthWord *ForthStream_ParseWord( ForthStream *in );
void ForthStream_SkipSpaces( ForthStream *in );
int ForthStream_Eof( ForthStream *self );
char ForthStream_Getc( ForthStream *self );
void ForthStream_Ungetc( ForthStream *self );
int forthIsSpace( char c );
/****/
//@-node:leonardoce.20090629082550.231:ForthStream
//@-others

#endif
//@-node:leonardoce.20090629082550.190:@thin quattro_parser.h
//@-leo
