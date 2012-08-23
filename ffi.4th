\ @+leo-ver=4-thin
\ @+node:leonardoce.20090701090549.4:@thin ffi.4th
\ @@language forth

\ @+others
\ @+node:leonardoce.20090701090549.5:Buffer di uso generico C
variable c-buffer-orig 1 cells allot
variable c-buffer 1 cells allot

: init-buffer
  ( caddr -- )
  dup c-buffer-orig ! 
  c-buffer ! ;

: get-buffer
  ( -- caddr )
  c-buffer-orig @ ;

: c-in-buffer
  ( c -- )
  c-buffer @ cmem! 
  c-buffer @ 1+ c-buffer ! ;

: c-from-buffer
  ( -- c )
  c-buffer @ cmem@
  c-buffer @ 1+ c-buffer ! ;
\ @-node:leonardoce.20090701090549.5:Buffer di uso generico C
\ @+node:leonardoce.20090701090549.6:Utili
: emit-if-not-zero
  ( c -- )
  dup 0<> if emit else drop then ;

: 0! ( addr -- )
  0 swap ! ;

: 1+! ( addr -- )
  1 swap +! ;
\ @nonl
\ @-node:leonardoce.20090701090549.6:Utili
\ @+node:leonardoce.20090701090549.7:Gestione stringhe C
: cstring-new
  ( c-addr u -- newaddr )
  dup 1+ cmalloc                    \ ( s: c-addr u nuova-memoria ) 
  init-buffer                       \ ( s: c-addr u )
  over + swap do 
    i c@ c-in-buffer 
  loop 
  0 c-in-buffer
  get-buffer ;

variable temp-len 1 cells allot
: cstring-len
  ( c-addr -- len )
  temp-len 0!
  begin
    temp-len 1+!
    dup cmem@ 0=
    swap 1+ swap
  until 
  drop 
  temp-len @ 1- ;

: cstring-type
  ( c-addr -- )
  begin
    dup cmem@               \ ( s: caddr   c )
    swap 1+ swap            \ ( s: caddr+1 c )
    dup emit-if-not-zero    \ ( s: caddr+1 c )
    0=
  until 
  drop ;

: cstring-delete
  ( c-addr -- )
  cfree ;
\ @nonl
\ @-node:leonardoce.20090701090549.7:Gestione stringhe C
\ @+node:leonardoce.20090701090549.8:Utili FFI
\ Ci sono impazzito ma funziona alla
\ grande.
: ext"
  ( compile: "cccc<quote>" -- ) ( runtime: -- caddr )
  state@ if 
    [char] " parse allot             \ ( addr )
    0 c,                             \ zero terminator 
    postpone literal                 \ compile address into defining function
    ['] addr>c                       \ compile address translation
    postpone literal
    ['] execute                      \ compile exec
    compile,
    \ postpone execute
  then ; immediate

: cloadlibrary-check ( saddr -- handle )
  cloadlibrary dup 0= if abort" Errore in caricamento libreria native" then ;

: cprocaddress-check ( handle procname -- handle )
  dup >r
  cprocaddress dup 0= if ." Errore in caricamento entrypoint: '" r@ cstring-type ." '" abort then 
  r> drop ;

: 0ccall ( procaddr -- result ) 0 swap ccall ;
: 1ccall ( procaddr -- result ) 1 swap ccall ;
: 2ccall ( procaddr -- result ) 2 swap ccall ;
: 3ccall ( procaddr -- result ) 3 swap ccall ;
: 4ccall ( procaddr -- result ) 4 swap ccall ;
\ @-node:leonardoce.20090701090549.8:Utili FFI
\ @+node:leonardoce.20090706154105.2:Database FFI
\ @+others
\ @+node:leonardoce.20090706154105.3:Stato
0 value current-lib
0 value current-entrypoint

: current-lib: ' to current-lib ;
: entrypoint" [char] " parse dup allot drop to current-entrypoint 
  0 here 1 allot c! ;
\ @nonl
\ @-node:leonardoce.20090706154105.3:Stato
\ @+node:leonardoce.20090701090549.9:Definizioni DLL
begin-structure dllstructure
1 cells +field dll-handle
1 cells +field dll-name
end-structure

: runtime-defdll  dup @ 0=
  if dup 1 cells + @ addr>c cloadlibrary-check  over ! then  @ ;
: defdll:  drop create
    here dllstructure allot    
    0 over dll-handle !
    dll-name !
  does> runtime-defdll ;



\ @-node:leonardoce.20090701090549.9:Definizioni DLL
\ @+node:leonardoce.20090701090549.11:Definizioni Proc
begin-structure procstructure
1 cells +field ps-dll-xt
1 cells +field ps-handle
1 cells +field ps-name
1 cells +field ps-nparams
end-structure

: func-execute ( args addr )  dup ps-nparams @   swap ps-handle @ ccall ;

: func-create ( addr ) 
  dup ps-dll-xt @ execute  
  over ps-name @ addr>c  
  cprocaddress-check 
  swap ps-handle ! ;

: func-runtime ( args -- ret ) dup ps-handle @ 0= if dup func-create then func-execute ;

0 value func-temp
: func-compile
  here procstructure allot to func-temp
  current-lib func-temp ps-dll-xt !
  0 func-temp ps-handle !
  current-entrypoint func-temp ps-name !
  func-temp ps-nparams ! ;

: vfunc: create func-compile does> func-runtime drop ;
: func: create func-compile does> func-runtime ;




\ @-node:leonardoce.20090701090549.11:Definizioni Proc
\ @+node:leonardoce.20090706154105.4:Test
\ @+at
\  
\  : sdldll s" sdl.dll" ;
\  sdldll defdll: sdl
\  current-lib: sdl
\  
\  entrypoint" SDL_Init" 1 vfunc: sdl_init
\ @-at
\ @nonl
\ @-node:leonardoce.20090706154105.4:Test
\ @-others



\ @+doc
\  
\  Uso tipico:
\  
\  : sdl.dll s" sdl.dll" ;
\  sdl.dll defdll: sdl
\  
\ @-doc
\ @+at
\ @-at
\ @nonl
\ @-node:leonardoce.20090706154105.2:Database FFI
\ @-others
\ @nonl
\ @-node:leonardoce.20090701090549.4:@thin ffi.4th
\ @-leo
