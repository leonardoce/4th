\ @+leo-ver=4-thin
\ @+node:leonardoce.20090630084051.12:@thin file.4th
\ @@language forth

\ @+others
\ @+node:leonardoce.20090630084051.13:Interfaccia a basso livello
: crt-library ( -- caddr u )  oswindows if s" msvcrt.dll" else s" libc.so.6" then ;
crt-library defdll: crt
current-lib: crt

entrypoint" fopen" 2 func: fopen ( caddr fam -- fileid )
entrypoint" fclose" 1 vfunc: fclose ( fileid -- )
entrypoint" ferror" 1 func: ferror ( fileid -- flag )
entrypoint" fflush" 1 vfunc: fflush ( fileid -- )
entrypoint" ftell" 1 func: ftell ( fileid -- ud )
entrypoint" fread" 4 func: fread ( ptr size count fileid -- n )
entrypoint" fwrite" 4 func: fwrite ( ptr size count fileid -- n )
entrypoint" fseek" 3 func: fseek ( fileid offset origin -- flag )


oswindows [if]: entrypoint" _chsize" 
oslinux   [if]: entrypoint" ftruncate"
2 func: chsize ( ifileid length -- flag )

oswindows [if]: entrypoint" _fileno" 
oslinux   [if]: entrypoint" fileno"
1 func: fileno ( fileid -- ifileid )

\ @-node:leonardoce.20090630084051.13:Interfaccia a basso livello
\ @+node:leonardoce.20090630084051.14:Costanti
0 constant seek-set local
1 constant seek-cur local
2 constant seek-end local
\ @-node:leonardoce.20090630084051.14:Costanti
\ @+node:leonardoce.20090630084051.15:Buffer Stringhe C
0 value temp-buf
: with-cstring ( caddr u -- )
  cstring-new to temp-buf ;

: wo-cstring ( -- )
  temp-buf cstring-delete
  0 to temp-buf ;

: get-cstring ( -- addr )
  temp-buf ;

\ @-node:leonardoce.20090630084051.15:Buffer Stringhe C
\ @+node:leonardoce.20090630084051.17:Interfaccia DPANS94
\ @+others
\ @+node:leonardoce.20090630084051.18:Modalita' di apertura
\ 11.6.1.2064 DPANS 94
: r/o ( -- fam )
  s" r" string>c ;

\ 11.6.1.2066 DPANS 94
: r/w ( -- fam )
  s" r+" string>c ;

\ 11.6.1.2425 DPANS 94
: w/o ( -- fam )
  s" w" string>c ;

\ 11.6.1.0765 DPANS 94
: bin-w/o ( -- fam )
  s" wb" string>c ;

: bin-r/w ( -- fam )
  s" rb+" string>c ;

: bin-r/o ( -- fam )
  s" rb" string>c ;

: bin ( fam -- fam )
  dup r/o = if drop bin-r/o else
  dup r/w = if drop bin-r/w else
  dup w/o = if drop bin-w/o 
  then then then ; 
\ @-node:leonardoce.20090630084051.18:Modalita' di apertura
\ @+node:leonardoce.20090630084051.19:Apertura, chiusura e flush
\ 11.6.1.1970 DPANS 94
: open-file ( caddr u fam -- fileid ior )
  >r with-cstring r> 
  get-cstring swap fopen
  wo-cstring 
  dup 0= ;

\ 11.6.1.0900 DPANS 94
: close-file ( fileid -- ior )
  fclose 0 ;

\ 11.6.2.1560 DPANS 94
: flush-file ( fileid -- ior )
  fflush 0 ;
\ @-node:leonardoce.20090630084051.19:Apertura, chiusura e flush
\ @+node:leonardoce.20090630084051.20:Lettura e scrittura
\ 11.6.1.2080 DPANS 94
: read-file ( c-addr u1 fileid -- u2 ior )
  >r >r addr>c 1 r> r> 
  dup >r fread r> ferror ;

\ 11.6.1.2480 DPANS 94
: write-file ( c-addr u fileid -- ior )
  >r >r addr>c 1 r> r>
  dup >r fwrite drop r> ferror ;
\ @-node:leonardoce.20090630084051.20:Lettura e scrittura
\ @+node:leonardoce.20090630084051.21:Riposizionamento e stato

\ 11.6.1.2142 DPANS 94
: reposition-file ( ud fileid -- ior )
  swap seek-set fseek ;

\ 11.6.1.2142 DPANS 94
: reposition-file-from-end ( ud fileid -- ior )
  swap seek-end fseek ;  

\ 11.6.1.1520 DPANS 94
: file-position ( fileid -- ud ior )
  ftell dup 0 < if 1 else 0 then ;
\ @nonl
\ @-node:leonardoce.20090630084051.21:Riposizionamento e stato
\ @+node:leonardoce.20090707081518.6:Ridimensionamento
\ 11.6.1.2147
: resize-file ( ud fileid -- ior )
  fileno swap chsize ;
\ @nonl
\ @-node:leonardoce.20090707081518.6:Ridimensionamento
\ @-others
\ @-node:leonardoce.20090630084051.17:Interfaccia DPANS94
\ @-others
\ @nonl
\ @-node:leonardoce.20090630084051.12:@thin file.4th
\ @-leo
