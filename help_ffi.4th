\ ----------------------------------------------
doc" cmalloc
CMALLOC ( u -- c-addr )

Alloca u bytes e ritorna il loro indirizzo
in c-addr
"

\ ----------------------------------------------
doc" cfree
CFREE ( c-addr -- )

Libera la memoria allocata all'indirizzo specificato
"

\ ----------------------------------------------
doc" cmem!
CMEM! ( c c-addr -- )

Memorizza il byte passato all'indirizzo di memoria esterna
specificato.
"

\ ----------------------------------------------
doc" cmem@
CMEM@ ( c-addr -- c )

Ritorna il byte memorizzato all'indirizzo specificato.
"

\ ----------------------------------------------
doc" cmemcell!
CMEMCELL! ( c c-addr -- )

Memorizza la cella passata all'indirizzo di memoria esterna
specificato.
"

\ ----------------------------------------------
doc" cmemcell@
CMEMCELL@ ( c-addr -- c )

Ritorna la cella memorizzata all'indirizzo specificato.
"

\ ----------------------------------------------
doc" cloadlibrary
CLOADLIBRARY ( saddr -- handle )

Carica la libreria specificata dalla stringa C passata come parametro.
Se l'operazione riesce ritorna l'handle alla libreria altrimenti
ritorna 0
"

\ ----------------------------------------------
doc" cloadlibrary-check
CLOADLIBRARY-CHECK ( saddr -- handle )

Come CLOADLIBRARY ma se fallisce l'operazione intera viene abortita

Vedi CLOADLIBRARY
"

\ ----------------------------------------------
doc" cfreelibrary
CFREELIBRARY ( handle -- )

Libera la libreria specificata dall'handle passato
"

\ ----------------------------------------------
doc" cprocaddress
CPROCADDRESS ( handle procname -- ptr )

Inserisce nello stack il puntatore alla funzione il cui
nome e' specificato nella stringa c 'procname' cercandola
nella libreria con l'handle passato. Se l'operazione
non riesce ritorna 0.
"

\ ----------------------------------------------
doc" cprocaddress-check
CPROCADDRESS-CHECK ( handle procname -- ptr )

Come CPROCADDRESS ma se non riesce l'intera operazione viene
abortita.

Vedi CPROCADDRESS
"

\ ----------------------------------------------
doc" ccall
CCALL ( arg*n n procaddr -- result )

Invoca la chiamata nativa al puntatore indicato passandogli
i parametri specificati, il cuo numero e' 'n'.
"

\ ----------------------------------------------
doc" ccall
0CCALL ( procaddr -- result )

Invoca la chiamata nativa al puntatore indicato 

Vedi CCALL
"

\ ----------------------------------------------
doc" ccall
1CCALL ( a0 procaddr -- result )

Invoca la chiamata nativa al puntatore indicato con un argomento

Vedi CCALL
"

\ ----------------------------------------------
doc" ccall
2CCALL ( a1 a0 procaddr -- result )

Invoca la chiamata nativa al puntatore indicato con due argomenti

Vedi CCALL
"

\ ----------------------------------------------
doc" ccall
3CCALL ( a2 a1 a0 procaddr -- result )

Invoca la chiamata nativa al puntatore indicato con tre argomenti

Vedi CCALL
"


