//@+leo-ver=4-thin
//@+node:leonardoce.20090629082550.163:@thin utils.c
//@@language c
//@@tabwidth -4
//@+others
//@+node:leonardoce.20090629082550.164:Framework_Assert
#include "utils.h"

/**
 * Assert
 */

void Framework_Assert(int condition, const char *fileName, int line) {
  if(!condition) {
    printf("Assertion failure in file %s:%i\n", fileName, line);
    abort();
  }
}
//@-node:leonardoce.20090629082550.164:Framework_Assert
//@+node:leonardoce.20090629082550.174:DynamicVector
//@+others
//@+node:leonardoce.20090629082550.165:DynamicVector_New


/**
 * DynamicVector
 */

DynamicVector *DynamicVector_New() {
  DynamicVector *self;
  int i;

  self = (DynamicVector *)malloc(sizeof(DynamicVector));
  self->elementsCount=0;
  self->bufferSize=10;
  self->elements=(void **)malloc(sizeof(void*) * self->bufferSize);  
  for(i=0;i<self->bufferSize;i++) {
    self->elements[i]=NULL;
  }

  return self;
}
//@-node:leonardoce.20090629082550.165:DynamicVector_New
//@+node:leonardoce.20090629082550.166:DynamicVector_Delete

void DynamicVector_Delete(DynamicVector *self) {
  free(self->elements);
  free(self);
}
//@-node:leonardoce.20090629082550.166:DynamicVector_Delete
//@+node:leonardoce.20090629082550.167:DynamicVector_Get

void *DynamicVector_Get(DynamicVector *self, int indexId) {
  if(indexId >= self->elementsCount) {
    return NULL;
  }

  return self->elements[indexId];
}
//@-node:leonardoce.20090629082550.167:DynamicVector_Get
//@+node:leonardoce.20090629082550.168:DynamicVector_Set

void DynamicVector_Set(DynamicVector *self, int indexId, void *value) {
  int oldBufferSize = self->bufferSize;
  int i;

  if(indexId >= self->bufferSize) {
    self->bufferSize = indexId+10;
    self->elements=(void **)realloc(self->elements, sizeof(void*)*self->bufferSize);

    for(i=oldBufferSize; i<self->bufferSize; i++) {
      self->elements[i]=NULL;
    }
  }

  self->elements[indexId] = value;
  if(indexId >= self->elementsCount) {
    self->elementsCount=indexId+1;
  }
}
//@-node:leonardoce.20090629082550.168:DynamicVector_Set
//@+node:leonardoce.20090629082550.169:DynamicVector_Count

int DynamicVector_Count(DynamicVector *self) {
  return self->elementsCount;
}
//@-node:leonardoce.20090629082550.169:DynamicVector_Count
//@+node:leonardoce.20090629082550.170:DynamicVector_Append

void DynamicVector_Append(DynamicVector *self, void *element) {
  DynamicVector_Set(self, self->elementsCount, element);
}
//@-node:leonardoce.20090629082550.170:DynamicVector_Append
//@+node:leonardoce.20090629082550.171:DynamicVector_Dump

void DynamicVector_Dump(DynamicVector *self) {
  int i, elements;

  elements=DynamicVector_Count(self);

  printf("<dynamicVector elementCount=\"%i\">\n", elements);
  for(i=0;i<elements;i++) {
    printf("  <element id=\"%i\" value=\"%p\"/>\n", i, DynamicVector_Get(self,i));
  }
  printf("</dynamicVector>\n");
}
//@-node:leonardoce.20090629082550.171:DynamicVector_Dump
//@+node:leonardoce.20090629082550.172:DynamicVector_SetCount

void DynamicVector_SetCount(DynamicVector *self, int count) {
  if(count<self->elementsCount) {
    self->elementsCount=count;
  }
}
//@-node:leonardoce.20090629082550.172:DynamicVector_SetCount
//@+node:leonardoce.20090629082550.173:DynamicVector_Test

void DynamicVector_Test() {
  DynamicVector *prova;
  int i;

  prova=DynamicVector_New();
  F_ASSERT(prova!=NULL);
  F_ASSERT(DynamicVector_Count(prova)==0);
  F_ASSERT(DynamicVector_Get(prova, 4)==NULL);

  DynamicVector_Set(prova, 22, (void*)0x123);
  F_ASSERT(DynamicVector_Count(prova)==23);
  F_ASSERT(DynamicVector_Get(prova,22)==(void*)0x123);

  for(i=0;i<22;i++) {
    F_ASSERT(DynamicVector_Get(prova,i)==NULL);
  }

  F_ASSERT(DynamicVector_Count(prova)==23);
  DynamicVector_Append(prova, (void*)21);
  DynamicVector_Append(prova, (void*)22);
  DynamicVector_Append(prova, (void*)23);
  F_ASSERT(DynamicVector_Count(prova)==26);

  DynamicVector_Delete(prova);
}
//@-node:leonardoce.20090629082550.173:DynamicVector_Test
//@-others
//@-node:leonardoce.20090629082550.174:DynamicVector
//@+node:leonardoce.20090629082550.207:Inputstream
//@+others
//@+node:leonardoce.20090629082550.208:NewForBuffer
InputStream *InputStream_NewForBuffer(void *buffer, int bufferLen) {
    InputStream *self = (InputStream *)malloc(sizeof(InputStream));

    self->bufferLen=bufferLen;
    self->buffer=malloc(bufferLen);
    self->ptr=0;
    memcpy(self->buffer, buffer, bufferLen);

    return self;
}
//@-node:leonardoce.20090629082550.208:NewForBuffer
//@+node:leonardoce.20090629082550.209:NewForFile
InputStream *InputStream_NewForFile(const char *nomeFile) {
    FILE *in = fopen(nomeFile, "rb");
    if(in == NULL) {
        return NULL;
    }

    fseek(in, 0, SEEK_END);

    int bufferLen = ftell(in);
    void *buffer = malloc(bufferLen);

    fseek(in, 0, SEEK_SET);
    fread(buffer, bufferLen, 1, in);
    fclose(in);

    InputStream *self = (InputStream *)malloc(sizeof(InputStream));
    self->buffer = buffer;
    self->bufferLen = bufferLen;
    self->ptr = 0;

    return self;
}
//@-node:leonardoce.20090629082550.209:NewForFile
//@+node:leonardoce.20090629082550.210:Delete
void InputStream_Delete(InputStream *self) {
    if(self==NULL) {
        return;
    }

    free(self->buffer);
    free(self);
}
//@-node:leonardoce.20090629082550.210:Delete
//@+node:leonardoce.20090629082550.211:Read
int InputStream_Read(InputStream *self, void *buffer, int bufferLen) {
    int remainingBytes = self->bufferLen - self->ptr;
    int bytesToRead = MIN(remainingBytes, bufferLen);

    memcpy(buffer, ((char *)self->buffer)+self->ptr, bytesToRead);
    self->ptr = self->ptr + bytesToRead;

    return bytesToRead;
}
//@-node:leonardoce.20090629082550.211:Read
//@+node:leonardoce.20090629082550.212:ReadInt
long InputStream_ReadInt(InputStream *self) {
    int buffer;
    InputStream_Read(self, &buffer, sizeof(long));
    return buffer;
}
//@nonl
//@-node:leonardoce.20090629082550.212:ReadInt
//@+node:leonardoce.20090629082550.222:ReadByte
char InputStream_ReadByte(InputStream *self) {
    char buffer;
    InputStream_Read(self, &buffer, sizeof(char));
    return buffer;
}
//@nonl
//@-node:leonardoce.20090629082550.222:ReadByte
//@+node:leonardoce.20090629082550.221:Eof
int InputStream_Eof(InputStream *self) {
    if(self->ptr >= self->bufferLen) {
        return 1;
    } else {
        return 0;
    }
}
//@-node:leonardoce.20090629082550.221:Eof
//@-others
//@nonl
//@-node:leonardoce.20090629082550.207:Inputstream
//@+node:leonardoce.20090629082550.175:OutputStream
//@+others
//@+node:leonardoce.20090629082550.198:NewForFile
OutputStream *OutputStream_NewForFile(const char *fileName) {
    OutputStream *self = (OutputStream *) malloc(sizeof(OutputStream));

    self->out = fopen(fileName, "wb");

    return self;
}
//@-node:leonardoce.20090629082550.198:NewForFile
//@+node:leonardoce.20090629082550.199:Write
void OutputStream_Write(OutputStream *self, void *buffer, int len) {
    if(self->out!=NULL) {
        fwrite(buffer, len, 1, self->out);
    }
}
//@nonl
//@-node:leonardoce.20090629082550.199:Write
//@+node:leonardoce.20090629082550.224:WriteString
void OutputStream_WriteString(OutputStream *self, const char *str) {
    OutputStream_Write(self, (void *)str, strlen(str));
}
//@nonl
//@-node:leonardoce.20090629082550.224:WriteString
//@+node:leonardoce.20090629082550.202:NewHeadline
void OutputStream_WriteInt(OutputStream *self, int i) {
    OutputStream_Write(self, &i, sizeof(int));
}
//@nonl
//@-node:leonardoce.20090629082550.202:NewHeadline
//@+node:leonardoce.20090629082550.201:Status
int OutputStream_Status(OutputStream *self) {
    if(self->out!=NULL) {
        return 1;
    } else {
        return 0;
    }
}
//@nonl
//@-node:leonardoce.20090629082550.201:Status
//@+node:leonardoce.20090629082550.200:Delete
void OutputStream_Delete(OutputStream *self) {
    if(self==NULL) {
        return;
    }

    if(self->out!=NULL) {
        fclose(self->out);
    }
    free(self);
}
//@nonl
//@-node:leonardoce.20090629082550.200:Delete
//@-others
//@nonl
//@-node:leonardoce.20090629082550.175:OutputStream
//@-others
//@-node:leonardoce.20090629082550.163:@thin utils.c
//@-leo
