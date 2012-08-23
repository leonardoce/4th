: codice-parentesi-chiusa 41 ;
: ( codice-parentesi-chiusa 
  parse drop drop 
  ; immediate

( commento per una riga )
: codice-ritorno-carrello 10 ;
: \ 
  codice-ritorno-carrello parse 
  drop drop 
  ; immediate

\ 6.1.0370 DPANS 94
: 2drop ( x1 x2 -- ) 
  drop drop ; 

\ 6.1.1990 DPANS 94
: over ( x1 x2 -- x1 x2 x1 )
  1 pick ;

\ 6.1.0380 DPANS 94
: 2dup ( x1 x2 -- x1 x2 x1 x2 )
  over over ;

\ 6.1.2165 DPANS 94
\ internal

\ 6.1.0150 DPANS 94
: , ( x -- )
  here           \ indirizzo libero
  1 cells allot  \ alloca spazio
  ! ;            \ Inizializza

\ 6.1.0860 DPANS 94
: c, ( x -- )
  here           \ indirizzo libero
  1 allot        \ alloca 1 byte
  c! ;

\ 6.1.2410 DPANS 94
: variable ( "<spaces>name" -- ) ( execution: a-addr )
  create
  0 , ;

\ 6.1.0898 DPANS 94
: chars ( n1 -- n2 )
  \ Un carattere e' un byte
  ;

\ 6.1.0897 DPANS 94
: char+ ( c-addr1 -- c-addr2 )
  1 chars + 
  ;

\ 6.1.0950 DPANS 94
: constant ( x "<spaces>name" -- ) ( execution: -- x )
  create , 
  does> @ ;

\ 6.1.1200 DPANS 94
: depth ( -- +n )
  sp@ ;

\ 6.1.2050 DPANS 94
: quit ( -- ) ( R: i*x -- )
  0 rp! stopvm ;

\ 6.1.0670 DPANS 94
: abort ( i*x -- ) ( R: j*x -- )
  0 sp! quit ;

\ 6.2.0260 DPANS 94
: 0<> ( x -- flag )
  0 = if 0 else 1 then ;

\ 6.2.0280 DPANS 94
: 0> ( x -- flag )
  0 > ;

\ 6.1.2310 DPANS 94
: (type) ( c-addr u -- )
  over + swap do 
    i c@ emit
  loop ;

: type ( c-addr u -- )
  dup 0<> if (type) else 2drop then ;

\ 6.1.0290 DPANS 94
: 1+ ( n1 -- n1+1 )
  1 + ;

\ 6.1.0270 DPANS 94
: 0= ( x -- flag )
  0 = ;

\ 6.1.1910 DPANS 94
: negate ( n1 -- n2 ) 0 1 - * ;

\ 6.1.0300 DPANS 94
: 1- ( x -- x-1 )
  1 - ;

\ 6.1.0130 DPANS 94
: +! ( n addr -- )
  dup @   \ ( n addr curval ) 
  rot     \ ( addr curval n )
  + swap  \ ( nextval addr )
  ! ;

\ 6.1.2033 DPANS 94
\ TODO: Cambiare la definizione
\ di questa parola. Infatti:
\
\ POSTPONE
\ 
\ Interpretation:  Interpretation semantics for this word are undefined.
\ 
\ Compilation: ( '<spaces>name' -- )
\ Skip leading space delimiters.  Parse name delimited by a space.
\ Find name.  Append the compilation semantics of name to the current
\ definition.  An ambiguous condition exists if name is not found.
\
\ Dato che deve aggiungere la semantica di compilazione di una
\ altra parola deve fare questo:
\
\ Se si tratta di una parola normale (forth) allora deve aggiungere
\ una istruzione che compila all'interno del chiamante una chiamata
\ alla parola in atto. (adesso e' sbagliata)
\ Se si tratta di una parola immediata allora deve aggiungere
\ una chiamata alla funzione (quello che fa adesso)

: postpone ( compilation: "<spaces>name" -- )
  ' compile, ; immediate

\ 6.2.2530 DPANS 94
: [compile] ( compilation: "<spaces>name" -- )
  ' compile, ; immediate

\ 6.1.0895 DPANS 94 
: ascii-space 32 ;

: char ( "<spaces>name" -- char )
  ascii-space parse drop c@ ;

\ 6.1.2520 DPANS 94
: [char] char postpone literal ; immediate

\ 6.1.0990 DPANS 94
: cr ( -- )
  13 emit 10 emit ;

\ 6.1.2220 DPANS 94
: space ( -- )
  32 emit ;

\ 6.1.2230 DPANS 94
: spaces ( n -- )
  dup 0 > if
    0 do space loop
  else
    drop
  then ;

\ 6.2.1930 DPANS 94
: nip ( x1 x2 -- x2 )
  swap drop ;

\ 6.1.2510 DPANS 94
: ['] 
  \ Compilation: ( "<spaces>name" -- ) 
  \ Run-time: ( -- xt ) 
  ' [compile] literal ; immediate

\ 6.1.0190 DPANS 94
: ." 
  \ Compilation: "ccc<quote>" -- 
  \ Runtime -- )
  postpone s"   
  ['] type 
  compile, ; immediate

\ 16.6.2.0715 DPANS 94
: also ( -- )
  get-order 1+ over swap set-order ;

\ 16.6.2.1590 DPANS 94
: forth ( -- )
  get-order swap drop forth-wordlist swap set-order ;

\ 16.6.2.1965 DPANS 94
: only ( -- )
  forth-wordlist 1 set-order ;

\ 16.6.2.1985 DPANS 94
: order ( -- )
  ." Search order: "
  get-order 0 do . loop 
  cr 
  ." Wordlist for new definitions: "
  get-current . 
  cr ;

\ 16.6.2.2037 DPANS 94
: previous ( -- )
  get-order dup 0<> if
    1- swap drop set-order 
  else
    drop
  then ;

\ 6.1.0680 DPANS 94
: abort" 
  \ Compilation: "ccc<quote>" --
  \ Runtime: ABORT
  postpone ."
  ['] abort compile, ; immediate

\ 17.6.1.0910 DPANS 94
: (cmove) ( caddr-orig caddr-dest u -- )
  0 do               \  caddr-orig caddr-dest
    over c@ over c!  \  caddr-orig caddr-dest 
    1+ swap 1+ swap 
  loop 2drop ;

: cmove ( caddr-orig caddr-dest u -- )
  dup 0= if 2drop drop else (cmove) then ;

\ Spazio per flag di impostazione variabile
variable (value-store)
0 (value-store) !

\ 6.2.2405 DPANS 94
: value ( x "<spaces>name" -- )
  create ,
  does> 
    (value-store) @ if !
    else @
    then
    0 (value-store) ! ;

\ 6.2.2295 DPANS 94
: to ( -- )
  1 (value-store) ! ;

\ 6.1.0750 DPANS 94
variable base
10 base ! 

\ 6.1.1170 DPANS 94
: decimal ( -- )
  10 base ! ;

\ 6.1.1660 DPANS 94
: hex ( -- )
  16 base ! ;

\ Spazio per la conversione numerica
64 constant len-spazio-conversione
create spazio-conversione len-spazio-conversione allot
0 value indirizzo-conversione

\ 6.1.0490 DPANS 94
: <# ( -- )
  spazio-conversione len-spazio-conversione + 1- 
  to indirizzo-conversione ;

\ 6.1.0040 DPANS 94
: #> ( xd -- caddr u )
  drop 
  indirizzo-conversione 1+ 
  spazio-conversione len-spazio-conversione + indirizzo-conversione - 1- ;

\ 6.1.1670 DPANS 94
: hold ( char -- )
  indirizzo-conversione c! 
  indirizzo-conversione 1- to indirizzo-conversione ;

\ 6.1.0030 DPANS 94
: # ( ud1 -- ud2 )
  base @ /mod swap 48 + hold ;

\ 6.1.1880 DPANS 94
: min ( n1 n2 -- n3 )
  2dup < if over else dup then
  nip nip ;

\ 6.1.1890 DPANS 94
: max ( n1 n2 -- n3 )
  2dup > if over else dup then
  nip nip ;

\ 6.2.2000 DPANS 94
: pad here ; 

\ 6.1.0880 DPANS 94
: cell+ 1 cells + ;

\ 6.1.0310 DPANS 94
: 2! swap over ! cell+ ! ;

\ 6.1.0350 DPANS 94
: 2@ dup cell+ @ swap @ ;

\ 8.6.1.0440 DPANS 94
: 2variable variable  1 cells allot ;

\ 10.6.2 ANS 200X
: begin-structure create here 0 0 , does> @ ;

\ 10.6.2 ANS 200X
: end-structure swap ! ;

\ 10.6.2 ANS 200X
: +field create over , + does> @ + ;

\ 10.6.2 ANS 200X
: field: 1 cells +field ;

\ 10.6.2 ANS 200X
: cfield: 1 chars +field ;
