\ @+leo-ver=4-thin
\ @+node:leonardoce.20090630084051.2:@thin editor.4th
\ @@language forth
\ QEditor
only definitions

1024 constant buffer-length local
create buffer buffer-length allot

64 constant line-length
32 constant space-ascii
13 constant newline-ascii

\ @+others
\ @+node:leonardoce.20090630084051.11:Schermo Singolo
\ @+others
\ @+node:leonardoce.20090630084051.4:Utili
: >offset ( l -- addr )
  line-length * buffer + ;

: parse-editor-arg ( "<space>ccc.." -- caddr u )
  newline-ascii parse line-length min ;

: get-line ( i -- ) >offset line-length ;

: cr! ( addr -- ) 10 swap c! ;
\ @-node:leonardoce.20090630084051.4:Utili
\ @+node:leonardoce.20090630084051.5:Cancellazione
: insert-cr ( -- ) 16 0 do i get-line 1- + cr! loop ;
: wipe ( -- )
  buffer dup 1024 + swap do space-ascii i c! loop 
  insert-cr ;

: wipe-line ( n -- )
  dup get-line 1- + cr! 
  get-line over + 1- swap do space-ascii i c! loop ;

\ @-node:leonardoce.20090630084051.5:Cancellazione
\ @+node:leonardoce.20090630084051.6:Modifica
: p ( i "<space>ccc.." -- )
  dup wipe-line
  >offset parse-editor-arg
  underswap cmove ;
\ @nonl
\ @-node:leonardoce.20090630084051.6:Modifica
\ @+node:leonardoce.20090701090549.3:Trattamento linee
: line-move ( orig dest -- )
  swap get-line drop 
  swap get-line cmove ;

: back-move-lines ( n -- ) 1+ 15 swap do i i 1- line-move loop ;
: forward-move-lines ( n -- ) 15 do  i 1- i line-move  0 1- +loop ;

: dd ( n -- ) dup 15 <> if  back-move-lines 15 wipe-line  then ;
: ii ( n -- ) dup forward-move-lines  wipe-line ;
\ @nonl
\ @-node:leonardoce.20090701090549.3:Trattamento linee
\ @+node:leonardoce.20090630084051.7:Stampa Schermo
: print-lineno ( i -- ) <# # # #> type space ;

: print-line ( i -- )
  dup print-lineno
  get-line over + swap do i c@ emit loop ;

: l ( -- )
  16 0 do i print-line loop ;
\ @nonl
\ @-node:leonardoce.20090630084051.7:Stampa Schermo
\ @-others
\ @nonl
\ @-node:leonardoce.20090630084051.11:Schermo Singolo
\ @+node:leonardoce.20090630084051.8:Trattamento file
0 value current-fileid
0 value blk

\ @+others
\ @+node:leonardoce.20090630084051.9:Utili
: check-file-error ( ior -- )
  0<> if abort" I/O error" then ; local

\ @-node:leonardoce.20090630084051.9:Utili
\ @+node:leonardoce.20090630084051.10:Gestione Schermi
: reposition ( n -- ) blk buffer-length * current-fileid 
  reposition-file check-file-error ; local

: write ( -- ) 
  reposition  
  buffer buffer-length current-fileid write-file
  check-file-error ; local

: read ( -- )
  reposition
  wipe
  buffer buffer-length current-fileid read-file check-file-error drop ;

: list ( n -- ) 
  to blk read l ;


\ @-node:leonardoce.20090630084051.10:Gestione Schermi
\ @+node:leonardoce.20090630084051.22:Gestione Files

: blocks-in-file ( -- )
  0 current-fileid reposition-file-from-end check-file-error 
  current-fileid file-position check-file-error buffer-length / 
  0 to blk reposition ;

: remove-last-screen ( -- )
  blocks-in-file 1- buffer-length * current-fileid resize-file drop ;

: close ( -- ) current-fileid close-file check-file-error 
  0 to current-fileid ;  

: use ( "<space>ccc.."  -- )
  parse-editor-arg r/w bin open-file check-file-error to current-fileid
  0 to blk read ;

: new ( "<space>ccc.."  -- )
  parse-editor-arg w/o bin open-file check-file-error to current-fileid  
  wipe 0 to blk write close ;

\ @-node:leonardoce.20090630084051.22:Gestione Files
\ @+node:leonardoce.20090701090549.10:Spostamento Schermi
: i-screen ( s -- )    
    dup blocks-in-file do  
      i 1- to blk read
      i to blk write

    0 1- +loop 
    to blk wipe write ;

: d-screen ( s -- )
  blocks-in-file swap do
    i 1+ to blk read
    i to blk write
  loop 

  ;
\ @-node:leonardoce.20090701090549.10:Spostamento Schermi
\ @+node:leonardoce.20090630084051.25:Indice
: read-index-line ( -- )
  pad line-length current-fileid read-file check-file-error drop
  blk <# # # #> type space 
  pad line-length type ;

: index ( -- )
  blocks-in-file 0 do
    i to blk reposition read-index-line  
  loop 
  0 to blk reposition ;
\ @-node:leonardoce.20090630084051.25:Indice
\ @+node:leonardoce.20090630084051.26:Interprete
: load ( n -- ) 
  to blk read 
  buffer buffer-length loadstring ;
\ @nonl
\ @-node:leonardoce.20090630084051.26:Interprete
\ @-others
\ @nonl
\ @-node:leonardoce.20090630084051.8:Trattamento file
\ @-others

wipe
\ @nonl
\ @-node:leonardoce.20090630084051.2:@thin editor.4th
\ @-leo
