
rm -f *.o
gcc -Wall -DOS_LINUX -DSYSTEM_64 -c quattro_parser.c quattro_vm.c quattro_istruzioni.c utils.c quattro_debug.c quattro_istruzioni_aritmetiche.c quattro_istruzioni_flow.c quattro_istruzioni_mem.c quattro_istruzioni_stack.c quattro_istruzioni_definition.c quattro_istruzioni_ffi.c quattro_istruzioni_wordlist.c

rm -f lib4th.a
ar r lib4th.a *.o

gcc -o forthconsole -Wall -DOS_LINUX -g forthconsole.c -L. -l4th -ldl
gcc -o forthc -Wall -DOS_LINUX -g forthc.c -L. -l4th -ldl
