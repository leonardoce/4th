//@+leo-ver=4-thin
//@+node:leonardoce.20090629082550.188:@thin quattro_debug.h
//@@language c
#ifndef __QUATTRO_DEBUG
#define __QUATTRO_DEBUG

/****c* forth/ForthDebugInfo
 * NAME
 *   ForthDebugInfo
 * FUNCTION
 *   Memorizza le informazioni di debug
 * SOURCE
 */
typedef enum ForthDebugInfo_Type ForthDebugInfo_Type;
enum ForthDebugInfo_Type {
  DI_ENTER,
  DI_EXIT,
  DI_DOES,
  DI_TRACE
};

typedef struct ForthDebugInfo ForthDebugInfo;
struct ForthDebugInfo {
  char *fileName;
  char *wordName;
  int row, col;

  ForthDebugInfo_Type infoType;
};

ForthDebugInfo *ForthDebugInfo_New(const char *fileName, const char *wordName, int row, int col, int diType);
void ForthDebugInfo_Delete(ForthDebugInfo *self);
void ForthDebugInfo_Dump(ForthDebugInfo *self);
/****/

#endif
//@-node:leonardoce.20090629082550.188:@thin quattro_debug.h
//@-leo
