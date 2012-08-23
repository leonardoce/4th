\ @+leo-ver=4-thin
\ @+node:leonardoce.20090629082550.229:@thin utils.4th
\ @@language forth

\ @+others
\ @+node:leonardoce.20090707081518.2:Salvataggio immagini
\ 4 - Salva l'immagine
: saveimage  ( -- )
  S" forth.image" saveonfile ;

\ 4 - Salva l'immagine
: saveon  ( -- )
  codice-ritorno-carrello parse saveonfile ;

\ @-node:leonardoce.20090707081518.2:Salvataggio immagini
\ @+node:leonardoce.20090707081518.3:Stack e aritmetica
\ 4 - Utile
: <>  ( a b -- flag )
  = 0= ;

\ 4 - Da stringa a C
: string>c ( addr u -- caddr )
  drop addr>c ;

\ 4 - Utile
: irot  ( a b c -- c a b )
  swap >r   \ a c -- b
  swap r>   \ c a b --
  ;

\ 4 - Utile
: underswap ( a b c -- b a c )
  >r swap r> ;

\ 4 - Marca l'ultima parola come una parola nascosta (ovvero non viene
\ scritta nell'output di WORDS )
\ per adesso non fa niente.
: local ( -- ) ;

\ @-node:leonardoce.20090707081518.3:Stack e aritmetica
\ @+node:leonardoce.20090707081518.4:Strutture dati
\ 4 - Crea una parola che e' utile per gestire
\     un vettore. Se la parola creata viene chiamata
\     con l'indice (che inizia da 0) ritorna
\     l'indirizzo dell'elemento
: array ( element-cell-size )
  create , 
  does> 
    ( idx addr -- addr )
    dup @ rot         \ addr cellsize idx
    * + 
    1 cells + ;
\ @-node:leonardoce.20090707081518.4:Strutture dati
\ @+node:leonardoce.20090707081518.5:Forth condizionale
\ Se il flag e' positivo non fa niente
\ altrimenti salta la riga. Utilizzato
\ come meccanismo per eseguire delle 
\ cose solo se siamo su linux o solo
\ su windows
: [if]:  ( flag -- )
  0= if codice-ritorno-carrello parse drop drop then ;
\ @nonl
\ @-node:leonardoce.20090707081518.5:Forth condizionale
\ @-others


\ 4 - Equivalente del DPANS 94 WORD ma con una stringa
\     non contata
: s-word ( "<spaces>ccc<space>" -- c-addr u )
  ascii-space parse ;

\ @-node:leonardoce.20090629082550.229:@thin utils.4th
\ @-leo
