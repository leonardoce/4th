//@+leo-ver=4-thin
//@+node:leonardoce.20090622083507.3:@thin forthconsole.c
//@@language c

#include <stdio.h>
#include <string.h>
#include "quattro_parser.h"
#include "quattro_vm.h"
#include "utils.h"

//@<<linea comando>>
//@+node:leonardoce.20090622083507.11:<<linea comando>>
int readCommandLine(char *buffer, int maxSize) {
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
//@-node:leonardoce.20090622083507.11:<<linea comando>>
//@nl

int main(int argc, char **argv) {
  ForthVm *vm = NULL;
  char maxLine[1024];
  char kernelFile[1024];
  char startupFile[1024];
  int displayPrompt = 1;
  int i;

  strcpy(kernelFile, "full.4th");

  //@  <<argomenti cmd>>
  //@+node:leonardoce.20090622083507.12:<<argomenti cmd>>
  startupFile[0]='\x0';

  for(i=1;i<argc;i++) {
      if(strcmp(argv[i], "--noprompt")==0) {
          displayPrompt = 0;
      } else if(strcmp(argv[i],"--image")==0) {
          InputStream *in = InputStream_NewForFile(argv[i+1]);
          vm=ForthVm_NewFromFile(in);
          InputStream_Delete(in);
          i++;
      } else if(strcmp(argv[i],"--kernel")==0) {
          strcpy(kernelFile, argv[i+1]);
          i++;
      } else if(strcmp(argv[i],"--exec")==0) {
          strcpy(startupFile, argv[i+1]);
      } else if(strcmp(argv[i],"--help")==0 || strcmp(argv[i],"-h")==0 || strcmp(argv[i],"-?")==0) {
          printf("%s\n", LEOFORTH_VERSION);
          printf("Uso: %s [opzioni]\n\n", argv[0]);
          printf("Opzioni: \n");
          printf("--kernel <nomefile>   Utilizza il kernel specificato\n");
          printf("--image <nomefile>    Carica l'immagine specificata\n");
          printf("--exec <nomefile>     Esegue il file specificato\n");
          printf("--help                Mostra questo messaggio\n");
          printf("-?\n");
          printf("-h\n");
          printf("\n");
          return(0);
      }

  }
  //@-node:leonardoce.20090622083507.12:<<argomenti cmd>>
  //@nl

  if(vm==NULL) {
    vm=ForthVm_New();
  }

  ForthStream *fstr;

  //@  <<kernel>>
  //@+node:leonardoce.20090630084051.24:<<kernel>>
  fstr = ForthStream_NewForFile(kernelFile);
  ForthVm_SetParser(vm, fstr);
  ForthVm_Feed(vm);
  ForthStream_Delete(fstr);
  //@nonl
  //@-node:leonardoce.20090630084051.24:<<kernel>>
  //@nl
  //@  <<informazioni benvenuto>>
  //@+node:leonardoce.20090629082550.233:<<informazioni benvenuto>>
  printf("%s\n", LEOFORTH_VERSION);
  printf("Code Space: %i\n", vm->hereCodePtr);
  printf("Data Space: %i\n", vm->hereDataPtr);
  printf("----\n\n");

  printf("kernel %s\n", kernelFile);
  //@-node:leonardoce.20090629082550.233:<<informazioni benvenuto>>
  //@nl
  //@  <<file startup>>
  //@+node:leonardoce.20090630084051.23:<<file startup>>
  if(strlen(startupFile)!=0) {
    printf("carico %s\n", startupFile);

    fstr = ForthStream_NewForFile(startupFile);
    ForthVm_SetParser(vm, fstr);
    ForthVm_Feed(vm);
    ForthStream_Delete(fstr);  
  }
  //@nonl
  //@-node:leonardoce.20090630084051.23:<<file startup>>
  //@nl

  fstr = ForthStream_NewForBuffer("<line>", "");
  ForthVm_SetParser(vm, fstr);

  printf("\n\n");

  while(TRUE) {
    if(displayPrompt) {
      if(vm->internalState == VM_COMPILER) {
        printf("(compiler) ");
      }

      printf("4> ");
      fflush(stdout);
    }

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
  ForthVm_Delete(vm);

  return 0;
}
//@-node:leonardoce.20090622083507.3:@thin forthconsole.c
//@-leo
