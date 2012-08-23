<?xml version="1.0" encoding="utf-8"?>
<?xml-stylesheet ekr_test?>
<leo_file>
<leo_header file_format="2" tnodes="0" max_tnode_index="0" clone_windows="0"/>
<globals body_outline_ratio="0.5">
	<global_window_position top="19" left="89" height="771" width="1268"/>
	<global_log_window_position top="0" left="0" height="0" width="0"/>
</globals>
<preferences/>
<find_panel_settings/>
<vnodes>
<v t="leonardoce.20090622083507.1" str_leo_pos="3,1"><vh>@chapters</vh></v>
<v t="leonardoce.20090622083507.5"><vh>Script per la compilazione</vh>
<v t="leonardoce.20090622083507.6" tnodeList="leonardoce.20090622083507.6"><vh>@nosent compila.bat</vh></v>
<v t="leonardoce.20090629082550.242" tnodeList="leonardoce.20090629082550.242"><vh>@nosent compila.sh</vh></v>
</v>
<v t="leonardoce.20090629082550.36"><vh>Macchina Virtuale</vh>
<v t="leonardoce.20090629082550.193"><vh>Sorgenti</vh>
<v t="leonardoce.20090629082550.2"
expanded="leonardoce.20090629082550.35,"><vh>@thin quattro_vm.c</vh></v>
<v t="leonardoce.20090629082550.141"><vh>@thin quattro_debug.c</vh></v>
<v t="leonardoce.20090629082550.147" a="E"><vh>@thin quattro_parser.c</vh></v>
<v t="leonardoce.20090629082550.163"><vh>@thin utils.c</vh></v>
<v t="leonardoce.20090629082550.68"><vh>Istruzioni</vh>
<v t="leonardoce.20090629082550.39"><vh>@thin quattro_istruzioni.c</vh></v>
<v t="leonardoce.20090629082550.51"><vh>@thin quattro_istruzioni_aritmetiche.c</vh></v>
<v t="leonardoce.20090629082550.176"><vh>@thin quattro_istruzioni_definition.c</vh></v>
<v t="leonardoce.20090629082550.69"><vh>@thin quattro_istruzioni_ffi.c</vh></v>
<v t="leonardoce.20090629082550.87" a="E"><vh>@thin quattro_istruzioni_flow.c</vh></v>
<v t="leonardoce.20090629082550.103"><vh>@thin quattro_istruzioni_mem.c</vh></v>
<v t="leonardoce.20090629082550.111"><vh>@thin quattro_istruzioni_stack.c</vh></v>
<v t="leonardoce.20090629082550.129"><vh>@thin quattro_istruzioni_wordlist.c</vh></v>
</v>
</v>
<v t="leonardoce.20090629082550.194"><vh>Headers</vh>
<v t="leonardoce.20090629082550.188"><vh>@thin quattro_debug.h</vh></v>
<v t="leonardoce.20090629082550.189"><vh>@thin quattro_istruzioni.h</vh></v>
<v t="leonardoce.20090629082550.190" a="E"><vh>@thin quattro_parser.h</vh></v>
<v t="leonardoce.20090629082550.191"><vh>@thin quattro_vm.h</vh></v>
<v t="leonardoce.20090629082550.192"><vh>@thin utils.h</vh></v>
</v>
<v t="leonardoce.20090622083507.2"><vh>Interfacce</vh>
<v t="leonardoce.20090622083507.3"><vh>@thin forthconsole.c</vh></v>
<v t="leonardoce.20090622083507.9"><vh>@thin forthtk.tcl</vh></v>
</v>
<v t="leonardoce.20090629082550.218"><vh>Embedding</vh>
<v t="leonardoce.20090629082550.219"><vh>@thin forthemb_template.c</vh></v>
<v t="leonardoce.20090629082550.220"><vh>@thin forthc.c</vh></v>
</v>
</v>
<v t="leonardoce.20090629082550.227" a="E"><vh>Kernel</vh>
<v t="leonardoce.20090701090549.2" tnodeList="leonardoce.20090701090549.2"><vh>@nosent full.4th</vh></v>
<v t="leonardoce.20090629082550.228" tnodeList="leonardoce.20090629082550.228"><vh>@nosent kernel.4th</vh></v>
<v t="leonardoce.20090629082550.229"><vh>@thin utils.4th</vh></v>
<v t="leonardoce.20090701090549.4"><vh>@thin ffi.4th</vh></v>
<v t="leonardoce.20090630084051.12" a="E"><vh>@thin file.4th</vh></v>
</v>
<v t="leonardoce.20090706170537.2"><vh>Help</vh>
<v t="leonardoce.20090706170537.3"><vh>@thin help.4th</vh></v>
<v t="leonardoce.20090707081518.7"><vh>@thin help_kernel.4th</vh></v>
</v>
<v t="leonardoce.20090623081933.2"><vh>Librerie</vh>
<v t="leonardoce.20090623081933.3"><vh>@thin socket.4th</vh></v>
<v t="leonardoce.20090623081933.7"><vh>@thin sockettest.4th</vh></v>
<v t="leonardoce.20090629082550.234"><vh>@thin gtk.4th</vh></v>
<v t="leonardoce.20090706154105.5"><vh>@thin pq.4th</vh></v>
</v>
<v t="leonardoce.20090630084051.3"><vh>Utilities</vh>
<v t="leonardoce.20090630084051.2"><vh>@thin editor.4th</vh></v>
</v>
</vnodes>
<tnodes>
<t tx="leonardoce.20090622083507.1"></t>
<t tx="leonardoce.20090622083507.2"></t>
<t tx="leonardoce.20090622083507.5"></t>
<t tx="leonardoce.20090622083507.6">@language batch

@echo off
del *.o

gcc -c -Wall -DOS_WINDOWS -g quattro_parser.c quattro_vm.c quattro_istruzioni.c utils.c quattro_debug.c quattro_istruzioni_aritmetiche.c quattro_istruzioni_flow.c quattro_istruzioni_mem.c quattro_istruzioni_stack.c quattro_istruzioni_definition.c quattro_istruzioni_ffi.c quattro_istruzioni_wordlist.c

del lib4th.a
ar r lib4th.a *.o

gcc -o forthconsole -Wall -DOS_WINDOWS -g forthconsole.c -L. -l4th
gcc -o forthc -Wall -DOS_WINDOWS -g forthc.c -L. -l4th
</t>
<t tx="leonardoce.20090623081933.2"></t>
<t tx="leonardoce.20090629082550.36"></t>
<t tx="leonardoce.20090629082550.68"></t>
<t tx="leonardoce.20090629082550.193"></t>
<t tx="leonardoce.20090629082550.194"></t>
<t tx="leonardoce.20090629082550.218">@doc
LeoForth gia' compila in bytecode. E' comunque possibile creare un file eseguibile
a partire da una immagine scritta con la parola "saveimage".

Per fare questo la procedura e' la seguente:
    
1) Viene preso il contenuto del file forthemb_template.c e, in testa, 
viene aggiunta la dichiarazione del vettore "forthImage", che viene 
riempito con i dati letti dall'immagine
2) Il file forthemb_template.c crea una macchina virtuale leggendo 
l'immagine del vettore e avvia la parola "main".
3) Il file creato viene compilato assieme alla libreria della macchina virtuale </t>
<t tx="leonardoce.20090629082550.227"></t>
<t tx="leonardoce.20090629082550.228">@language forth
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
: variable ( "&lt;spaces&gt;name" -- ) ( execution: a-addr )
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
: constant ( x "&lt;spaces&gt;name" -- ) ( execution: -- x )
  create , 
  does&gt; @ ;

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
: 0&lt;&gt; ( x -- flag )
  0 = if 0 else 1 then ;

\ 6.2.0280 DPANS 94
: 0&gt; ( x -- flag )
  0 &gt; ;

\ 6.1.2310 DPANS 94
: (type) ( c-addr u -- )
  over + swap do 
    i c@ emit
  loop ;

: type ( c-addr u -- )
  dup 0&lt;&gt; if (type) else 2drop then ;

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
\ Compilation: ( '&lt;spaces&gt;name' -- )
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

: postpone ( compilation: "&lt;spaces&gt;name" -- )
  ' compile, ; immediate

\ 6.2.2530 DPANS 94
: [compile] ( compilation: "&lt;spaces&gt;name" -- )
  ' compile, ; immediate

\ 6.1.0895 DPANS 94 
: ascii-space 32 ;

: char ( "&lt;spaces&gt;name" -- char )
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
  dup 0 &gt; if
    0 do space loop
  else
    drop
  then ;

\ 6.2.1930 DPANS 94
: nip ( x1 x2 -- x2 )
  swap drop ;

\ 6.1.2510 DPANS 94
: ['] 
  \ Compilation: ( "&lt;spaces&gt;name" -- ) 
  \ Run-time: ( -- xt ) 
  ' [compile] literal ; immediate

\ 6.1.0190 DPANS 94
: ." 
  \ Compilation: "ccc&lt;quote&gt;" -- 
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
  get-order dup 0&lt;&gt; if
    1- swap drop set-order 
  else
    drop
  then ;

\ 6.1.0680 DPANS 94
: abort" 
  \ Compilation: "ccc&lt;quote&gt;" --
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
: value ( x "&lt;spaces&gt;name" -- )
  create ,
  does&gt; 
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
: &lt;# ( -- )
  spazio-conversione len-spazio-conversione + 1- 
  to indirizzo-conversione ;

\ 6.1.0040 DPANS 94
: #&gt; ( xd -- caddr u )
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
  2dup &lt; if over else dup then
  nip nip ;

\ 6.1.1890 DPANS 94
: max ( n1 n2 -- n3 )
  2dup &gt; if over else dup then
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
: begin-structure create here 0 0 , does&gt; @ ;

\ 10.6.2 ANS 200X
: end-structure swap ! ;

\ 10.6.2 ANS 200X
: +field create over , + does&gt; @ + ;

\ 10.6.2 ANS 200X
: field: 1 cells +field ;

\ 10.6.2 ANS 200X
: cfield: 1 chars +field ;</t>
<t tx="leonardoce.20090629082550.242">@language shell

rm -f *.o
gcc -Wall -DOS_LINUX -c quattro_parser.c quattro_vm.c quattro_istruzioni.c utils.c quattro_debug.c quattro_istruzioni_aritmetiche.c quattro_istruzioni_flow.c quattro_istruzioni_mem.c quattro_istruzioni_stack.c quattro_istruzioni_definition.c quattro_istruzioni_ffi.c quattro_istruzioni_wordlist.c

rm -f lib4th.a
ar r lib4th.a *.o

gcc -o forthconsole -Wall -DOS_LINUX -g forthconsole.c -L. -l4th -ldl
gcc -o forthc -Wall -DOS_LINUX -g forthc.c -L. -l4th -ldl
</t>
<t tx="leonardoce.20090630084051.3"></t>
<t tx="leonardoce.20090701090549.2">@language forth
loadfile base.4th
loadfile help.4th
loadfile help_kernel.4th
loadfile help_ffi.4th
loadfile obj.4th
loadfile gtk.4th
loadfile glade.4th
loadfile editor.4th

only
definitions</t>
<t tx="leonardoce.20090706170537.2"></t>
</tnodes>
</leo_file>
