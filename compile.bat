@echo off
del *.o

gcc -c -Wall -DOS_WINDOWS -g quattro_parser.c quattro_vm.c quattro_istruzioni.c utils.c quattro_debug.c quattro_istruzioni_aritmetiche.c quattro_istruzioni_flow.c quattro_istruzioni_mem.c quattro_istruzioni_stack.c quattro_istruzioni_definition.c quattro_istruzioni_ffi.c quattro_istruzioni_wordlist.c quattro_istruzioni_repl.c

del lib4th.a
ar r lib4th.a *.o

gcc -o forthconsole -Wall -DOS_WINDOWS -g forthconsole.c -L. -l4th
gcc -o forthc -Wall -DOS_WINDOWS -g forthc.c -L. -l4th
