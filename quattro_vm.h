//@+leo-ver=4-thin
//@+node:leonardoce.20090629082550.191:@thin quattro_vm.h
//@@language c
#ifndef __QUATTROVM_H
#define __QUATTROVM_H

#include "quattro_parser.h"
#include "utils.h"

typedef long ForthInstructionAddress;
typedef long ForthDataAddress;
typedef long ForthCell;

#define CELL_PRINTF_FORMAT "%li "

#define longtobool(x) (((x)!=0)?1:0)

#define FORTHCODEADDRESS_NULL 0
#define FORTHDATAADDRESS_NULL 0
#define MAX_WORD_LISTS 64
#define MAX_CODE_SPACE 4096
#define MAX_DATA_SPACE 1048576
#define MAX_DATA_STACK 96
#define MAX_RET_STACK 96
#define MAX_NATIVE_INSTRUCTIONS 256

//@+others
//@+node:leonardoce.20090629082550.232:Dati VM
#define LEOFORTH_VERSION "4Forth 0.1 (06/2009)"
//@nonl
//@-node:leonardoce.20090629082550.232:Dati VM
//@+node:leonardoce.20090629082550.213:ForthWordList
/****c* forth/ForthWordList
 * NAME
 *   ForthWordList
 * FUNCTION
 *   Incapsula una wordlist del forth ovvero associa il nome di una parola
 *   a un indirizzo univoco nel settore codice del dizionario forth.
 *   Le parole vengono create come parole non immediate. Possono essere marcate
 *   immediate attraverso la "MarkImmediate"
 * SOURCE
 */
typedef struct ForthWordList ForthWordList;
struct ForthWordList {
  DynamicVector *wordNames;
  DynamicVector *wordAddrs;
  DynamicVector *wordIsImmediate;
};

ForthWordList *ForthWordList_New();
ForthWordList *ForthWordList_NewFromStream(InputStream *in);
void ForthWordList_SaveOnFile(ForthWordList* self, OutputStream *out);
void ForthWordList_Delete(ForthWordList* self);
void ForthWordList_Assoc(ForthWordList* self, const char *wordName, ForthInstructionAddress addr);
void ForthWordList_MarkImmediate(ForthWordList* self, const char *wordName);
int ForthWordList_IsImmediate(ForthWordList* self, const char *wordName);
ForthInstructionAddress ForthWordList_Find(ForthWordList* self, const char *wordName);
void ForthWordList_SetCount(ForthWordList *self, int c);
int ForthWordList_Count(ForthWordList *self);

/****/
//@-node:leonardoce.20090629082550.213:ForthWordList
//@+node:leonardoce.20090629082550.214:ForthInstruction
/****c* forth/ForthInstruction
 * NAME
 *   ForthInstruction
 * FUNCTION
 *   Questa struttura rappresenta una istruzione forth gli stack e
 *   le aree di memoria. Inoltre a questo la struttura ha un riferimento
 *   ad un parser che viene utilizzato per prelevare le parole.
 * SOURCE
 */

typedef enum ForthInstructionType ForthInstructionType;
enum ForthInstructionType {
  NOP_INSTRUCTION,
  NATIVE_INSTRUCTION,
  RET_INSTRUCTION,
  CALL_INSTRUCTION,
  DEBUGGER_INSTRUCTION,
  DATAPUSH_INSTRUCTION,
  STOP_VM,
  JUMP_INSTRUCTION,
  JFALSE_INSTRUCTION,
  RET_FROM_INSTRUCTION,
  TO_RET_INSTRUCTION,
  RET_FETCH_INSTRUCTION
};

typedef struct ForthInstruction ForthInstruction;
struct ForthInstruction {
  ForthInstructionType instructionType;
  int instructionDest;
};
/****/
//@-node:leonardoce.20090629082550.214:ForthInstruction
//@+node:leonardoce.20090629082550.215:ForthVm
/****c* forth/ForthVm
 * NAME
 *   ForthVM
 * METHODS
 *   ForthVm_InitForthWordList
 *   ForthVm_AllocateForthInstruction
 *   ForthVm_Run
 *   ForthVm_RegisterNativeInstruction
 * FUNCTION
 *   Questa classe rappresenta la macchina virtuale forth
 * SOURCE
 */
typedef enum ForthVm_State ForthVm_State;
enum ForthVm_State {
  VM_INTERPRETER,
  VM_COMPILER
};

typedef struct ForthVm ForthVm;
typedef void (*NativeInstruction)(ForthVm *self);
struct ForthVm {
  /* word lists */

  DynamicVector *wordLists;
  int compilerWordListIdx;
  ForthWordList *forthWordList;
  int searchOrder[MAX_WORD_LISTS];
  int searchOrderLen;

  char *lastDefinedWord;

  /* native instructions */

  NativeInstruction nativeInstructionTable[MAX_NATIVE_INSTRUCTIONS];
  const char *nativeInstructionTableDesc[MAX_NATIVE_INSTRUCTIONS];
  int nativeInstructionPtr;

  /* debug info */

  DynamicVector *debugInfo;

  /* memory spaces */

  ForthInstruction codeSpace[MAX_CODE_SPACE];
  ForthInstructionAddress hereCodePtr;
  ForthInstructionAddress instructionPtr;

  ForthStream *parser;

  char dataSpace[MAX_DATA_SPACE];
  ForthDataAddress hereDataPtr;

  /* stacks */

  ForthCell dataStack[MAX_DATA_STACK];
  int dataStackPtr;

  ForthCell retStack[MAX_DATA_STACK];
  int retStackPtr;

  /* state */

  ForthVm_State internalState;
  int traceEnabled;
  int traceMaxWidth;
  int wordTraceEnabled;
  int exitFlag;
};


ForthVm *ForthVm_New();
ForthVm *ForthVm_NewFromFile(InputStream *in);
void ForthVm_SaveOnFile(ForthVm *self, OutputStream *out);
void ForthVm_Error(ForthVm *self, const char *msg);
void ForthVm_Output(ForthVm *self, const char *msg);
void ForthVm_Delete(ForthVm *self);
void ForthVm_DumpDataStack(ForthVm *self);
void ForthVm_DumpRetStack(ForthVm *self);
ForthInstructionAddress ForthVm_Lookup(ForthVm *self, const char *wordName);
void ForthVm_SetParser(ForthVm *self, ForthStream *value);
ForthStream *ForthVm_GetParser(ForthVm *self);
void ForthVm_Feed(ForthVm *self);
ForthInstructionAddress ForthVm_IsImmediate(ForthVm *self, const char *wordName);
void ForthVm_MarkImmediate(ForthVm *self, const char *wordName);
const char *ForthVm_ReverseLookup(ForthVm *self, ForthInstructionAddress addr);
/****/

/****m* forth/ForthVm_InitForthWordList
 * NAME
 *   ForthVm_InitForthWordList
 * FUNCTION
 *   Inizializza la wordlist principale del forth
 * SOURCE
 */
void ForthVm_InitForthWordList(ForthVm *self);
/****/

/****m* forth/ForthVm_AllocateForthInstruction
 * NAME
 *   ForthVm_AllocateForthInstruction
 * FUNCTION
 *   Alloca spazio per una nuova istruzione forth
 * NOTES
 *   Se non c'e' piu' spazio disponibile la vm abortisce.
 * SOURCE
 */
ForthInstructionAddress ForthVm_AllocateForthInstruction(ForthVm *self);
/****/

/****m* forth/ForthVm_Run
 * NAME
 *   ForthVm_Run
 * FUNCTION
 *   Esegue la macchina virtuale finche' non trova una istruzione
 *   di stop
 * SOURCE
 */
void ForthVm_Run(ForthVm* self);
/****/

/****m* forth/ForthVm_RegisterNativeInstruction
 * NAME
 *   ForthVm_RegisterNativeInstruction
 * FUNCTION
 *   Compila una chiamata all'istruzione nativa specificata
 *   nei parametri e inserisce, nella forth wordlist, il
 *   richiamo al codice compilato.
 * SOURCE
 */
void ForthVm_RegisterNativeInstruction(ForthVm* self, const char *wordName, NativeInstruction instr);
/****/

/****m* forth/ForthVm_LookupNativeId
 * NAME
 *   ForthVm_LookupNativeId
 * FUNCTION
 *   Ritorna l'identificativo nativo, da usarsi all'interno
 *   del bytecode, di una certa funzione che implementa una primitiva
 * SOURCE
 */
int ForthVm_LookupNativeId(ForthVm *self, NativeInstruction ni);
/****/
//@-node:leonardoce.20090629082550.215:ForthVm
//@-others

#endif
//@-node:leonardoce.20090629082550.191:@thin quattro_vm.h
//@-leo
