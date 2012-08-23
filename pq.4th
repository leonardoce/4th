\ @+leo-ver=4-thin
\ @+node:leonardoce.20090706154105.5:@thin pq.4th
\ @@language forth

only vocabulary pq
also pq definitions

\ @+others
\ @+node:leonardoce.20090706154105.7:Costanti
0 constant connection-ok
1 constant connection-bad

0 constant pgres-empty-query
1 constant pgres-command-ok
2 constant pgres-tuples-ok
\ @nonl
\ @-node:leonardoce.20090706154105.7:Costanti
\ @+node:leonardoce.20090706154105.6:Definizioni PQ
: libpq-name  oswindows if s" libpq.dll" else s" libpq.so" then ;
libpq-name defdll: pq
current-lib: pq

entrypoint" PQconnectdb" 1 func: pq-connect 
entrypoint" PQerrorMessage" 1 func: pq-error-message
entrypoint" PQstatus" 1 func: pq-status
entrypoint" PQfinish" 1 vfunc: pq-finish
entrypoint" PQexec" 2 func: pq-exec
entrypoint" PQresultStatus" 1 func: pq-result-status
entrypoint" PQresultErrorMessage" 1 func: pq-result-error-message
entrypoint" PQgetvalue" 3 func: pq-get-value
entrypoint" PQntuples" 1 func: pq-ntuples
entrypoint" PQnfields" 1 func: pq-nfields
entrypoint" PQfinish" 1 vfunc: pq-finish
entrypoint" PQclear" 1 vfunc: pq-clear






\ @-node:leonardoce.20090706154105.6:Definizioni PQ
\ @+node:leonardoce.20090706154105.8:Test
variable testpq-conn
variable testpq-res

: testpq-film
  ext" dbname=film" pq-connect testpq-conn !
  testpq-conn @ ext" select nome from film_id" pq-exec testpq-res !
  testpq-res @ pq-ntuples 0 do
    testpq-res @ i 0 pq-get-value cstring-type cr
  loop 
  testpq-res @ pq-clear
  testpq-conn @ pq-finish ;

: testpq-pazienti
  ext" dbname=milleps user=dba password=sql" pq-connect testpq-conn !
  testpq-conn @ ext" select cognome, nome from pazienti" pq-exec testpq-res !
  testpq-res @ pq-ntuples 0 do
    testpq-res @ i 0 pq-get-value cstring-type space 
    testpq-res @ i 1 pq-get-value cstring-type space cr
  loop 
  testpq-res @ pq-clear
  testpq-conn @ pq-finish ;
\ @-node:leonardoce.20090706154105.8:Test
\ @-others

\ @-node:leonardoce.20090706154105.5:@thin pq.4th
\ @-leo
