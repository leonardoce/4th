\
\ Quelli che seguono sono tutti test per il funzionamento.
\ Quelli sopra invece sono definizioni del kernel
\

: doppia 2 * ;
: somma-tre + + ;

: prova-squote s" leonardo" ;

( prova per prova )

\ 10 20 30 somma-tre
\ dup 
\ 1 2 2dup
\ prova-squote

\ variable pluto
\ pluto
\ 123123 pluto !
\ pluto @


31415 constant pi-esteso

pi-esteso

: salva-su-file S" forth.image" saveonfile ;

salva-su-file
