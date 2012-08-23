@echo off

REM E' inspiegabile ma comint non funge bene se l'eseguibile in questione
REM non e' compilato -mwindows

gcc -o prova_emacs -mwindows -Wall -DOS_WINDOWS -g prova.c quattro_parser.c quattro_vm.c quattro_istruzioni.c utils.c quattro_debug.c quattro_istruzioni_aritmetiche.c quattro_istruzioni_flow.c quattro_istruzioni_mem.c quattro_istruzioni_stack.c quattro_istruzioni_definition.c quattro_istruzioni_ffi.c quattro_istruzioni_wordlist.c

@echo on