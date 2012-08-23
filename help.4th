\ @+leo-ver=4-thin
\ @+node:leonardoce.20090706170537.3:@thin help.4th
\ @@language forth

\ @+others
\ @+node:leonardoce.20090706170537.6:Struttura
\ Spazio per la memorizzazione dell'help
\ L'help viene memorizzato in due celle consecutive:
\ la prima cella contiene l'xt della parola,
\ la seconda un puntatore alla stringa che contiene l'help
\ la terza la lunghezza della stringa
128 constant help-max-words

3 cells array help-buffer local
help-max-words 3 cells * allot

0 value help-first-free local
\ @-node:leonardoce.20090706170537.6:Struttura
\ @+node:leonardoce.20090706170537.7:Memorizzazione
: (doc) ( xt c-addr u -- )
  help-first-free help-buffer 2 cells + !
  help-first-free help-buffer 1 cells + !
  help-first-free help-buffer ! 
  help-first-free 1+ to help-first-free ;

: doc" ( "word<space>ccc..<quote>" -- )
  ' dup 0= if abort" Parola non conosciuta" then
  [char] " parse dup allot
  (doc) ;

: doc' ( "word<space>ccc..<quote>" -- )
  ' dup 0= if abort" Parola non conosciuta" then
  [char] ' parse dup allot
  (doc) ;
\ @-node:leonardoce.20090706170537.7:Memorizzazione
\ @+node:leonardoce.20090706170537.8:Ricerca
: (print-help) ( i -- )
  dup help-buffer 1 cells + @ 
  swap help-buffer 2 cells + @
  type cr ; local

: (help) ( xt -- )
  help-first-free 0 do
    dup i help-buffer @ = if i (print-help) then
  loop drop ; local

: help ( "space<word>space" -- )
  ' dup 0= if abort" Parola non conosciuta" then
  help-first-free 0<> if (help) else drop then ;
\ @nonl
\ @-node:leonardoce.20090706170537.8:Ricerca
\ @-others


\ @-node:leonardoce.20090706170537.3:@thin help.4th
\ @-leo
