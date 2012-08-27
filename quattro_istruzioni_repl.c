#include "quattro_istruzioni_repl.h"

static int readCommandLine(char *buffer, int maxSize) {
    int i = 0;
    int realMax = maxSize-1;

    while(1) {
        if(i>realMax) {
            break;
        }

        buffer[i]=fgetc(stdin);

        if(buffer[i]==EOF) {
            return 0;
        }
        if(buffer[i]==13 || buffer[i]==10) {
            break;
        }
        i++;
    }

    buffer[i]='\x0';
    return 1;
}

void Instruction_Repl(ForthVm *vm)
{
  char maxLine[1024];
  ForthStream *fstr;

  printf("%s\n", LEOFORTH_VERSION);
  printf("Code Space: %i\n", vm->hereCodePtr);
  printf("Data Space: %i\n", vm->hereDataPtr);
  printf("----\n\n");


  fstr = ForthStream_NewForBuffer("<line>", "");
  ForthVm_SetParser(vm, fstr);

  printf("\n\n");

  while(TRUE) {
    if(vm->internalState == VM_COMPILER) {
      printf("(compiler) ");
    }

    printf("4> ");
    fflush(stdout);

    memset(maxLine, 0, 1024);
    if(!readCommandLine(maxLine, 1024)) {
      break;
    }

    ForthStream_ResetForBuffer(fstr, "<line>", maxLine);
    vm->exitFlag=0;
    ForthVm_Feed(vm);

    ForthVm_Output(vm, " ok\n");
    fflush(stdout);
  }

  ForthStream_Delete(fstr);
}

