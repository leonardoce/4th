//@+leo-ver=4-thin
//@+node:leonardoce.20090629082550.192:@thin utils.h
//@@language c
#ifndef __UTILS_H
#define __UTILS_H

#define TRUE 1
#define FALSE 0

#define stricmp strcasecmp

#define MIN(x,y) ((x)<(y)?(x):(y))
#define MAX(x,y) ((x)>(y)?(x):(y))

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//@+others
//@+node:leonardoce.20090629082550.195:Asserzioni
/****f* framework/F_ASSERT
 * NAME
 *   F_ASSERT
 * FUNCTION
 *   Macro per il controllo delle asserzioni. Se la condizione passata fallisce
 *   viene riportato un errore indicando il nome del file sorgente e il numero
 *   di riga.
 * EXAMPLE
 *   F_ASSERT(1!=3);
 * SOURCE
 */
#define F_ASSERT(cond) Framework_Assert((cond), __FILE__, __LINE__)
void Framework_Assert(int condition, const char *fileName, int line);
/****/
//@-node:leonardoce.20090629082550.195:Asserzioni
//@+node:leonardoce.20090629082550.206:InputStream
typedef struct InputStream InputStream;
struct InputStream {
    void *buffer;
    int bufferLen;
    int ptr;
};

InputStream *InputStream_NewForBuffer(void *buffer, int bufferLen);
InputStream *InputStream_NewForFile(const char *nomeFile);
long InputStream_ReadInt(InputStream *self);
int InputStream_Read(InputStream *self, void *buffer, int bufferLen);
void InputStream_Delete(InputStream *self);
int InputStream_Eof(InputStream *self);
char InputStream_ReadByte(InputStream *self);
//@nonl
//@-node:leonardoce.20090629082550.206:InputStream
//@+node:leonardoce.20090629082550.197:OutputStream
typedef struct OutputStream OutputStream;
struct OutputStream {
    FILE *out;
};

OutputStream *OutputStream_NewForFile(const char *fileName);
void OutputStream_Write(OutputStream *self, void *buffer, int len);
void OutputStream_WriteInt(OutputStream *self, int i);
int OutputStream_Status(OutputStream *self);
void OutputStream_Delete(OutputStream *self);
void OutputStream_WriteString(OutputStream *self, const char *str);
//@nonl
//@-node:leonardoce.20090629082550.197:OutputStream
//@+node:leonardoce.20090629082550.196:DynamicVector

/****c* framework/DynamicVector
 * NAME
 *   DynamicVector
 * FUNCTION
 *   Implementa un vettore dinamico che contiene elementi di tipo (void *). 
 * NOTES
 *   Il buffer degli elementi e' tenuto in "elements" mentre "bufferSize" specifica
 *   la sua dimensione in elementi.
 *   "elementsCount" invece e' il numero di elementi fisicamente occupati.
 *   All'inizio il vettore ha posto per 10 elementi.
 *   Gli elementi, inizialmente e nelle nuove allocazioni, sono posti a NULL.
 * SOURCE
 */
typedef struct DynamicVector DynamicVector;
struct DynamicVector {
  void **elements;
  int elementsCount;
  int bufferSize;
};

DynamicVector *DynamicVector_New();
void DynamicVector_Delete(DynamicVector *self);
void *DynamicVector_Get(DynamicVector *self, int indexId);
void DynamicVector_Set(DynamicVector *self, int indexId, void *value);
void DynamicVector_SetCount(DynamicVector *self, int count);
int DynamicVector_Count(DynamicVector *self);
void DynamicVector_Append(DynamicVector *self, void *element);
void DynamicVector_Dump(DynamicVector *self);
void DynamicVector_Test();
/****/
//@-node:leonardoce.20090629082550.196:DynamicVector
//@-others

#endif
//@-node:leonardoce.20090629082550.192:@thin utils.h
//@-leo
