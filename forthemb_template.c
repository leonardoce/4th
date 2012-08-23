//@+leo-ver=4-thin
//@+node:leonardoce.20090629082550.219:@thin forthemb_template.c
//@@language c

#include <stdio.h>
#include <string.h>
#include "quattro_parser.h"
#include "quattro_vm.h"
#include "utils.h"

int main(int argc, char **argv) {
  ForthVm *vm = NULL;
  int displayPrompt = 1;
  int i;

  InputStream *in = InputStream_NewForBuffer((void *)forthImage, forthImageLen);
  vm=ForthVm_NewFromFile(in);
  InputStream_Delete(in);

  ForthStream *fstr = ForthStream_NewForBuffer("<line>", "");
  ForthVm_SetParser(vm, fstr);
  ForthStream_ResetForBuffer(fstr, "<line>", "main");
  vm->exitFlag=0;
  ForthVm_Feed(vm);
  ForthStream_Delete(fstr);
  ForthVm_Delete(vm);

  return 0;
}
//@-node:leonardoce.20090629082550.219:@thin forthemb_template.c
//@-leo
