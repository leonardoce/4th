only
vocabulary db
also db definitions

variable querybuffer 8191 allot
0 value querybuffer-len 

: 'querybuffer-free
  ( -- ptr )
  querybuffer-len querybuffer + ;

: c-to-query-buffer ( c -- )
  'querybuffer-free c!
  querybuffer-len 1+ to querybuffer-len ;

: to-query-buffer ( addr u -- )
  over + swap do
    i c@ c-to-query-buffer
  loop ;

: sql"
  postpone s"
  ['] to-query-buffer literal
  compile, ; immediate

: apos>query ( -- )
  [char] ' c-to-query-buffer ;

: string>query ( addr u -- )
  apos>query
  over + swap do
    i c@ 
    dup [char] ' = if
      drop apos>query apos>query
    else
      c-to-query-buffer
    then 
  loop
  apos>query ;

: query-buffer-reset ( -- )
  0 to querybuffer-len ;

0 value connection

: handle-error
  ( -- )
  connection pq-errormessage 
  cstring-type
  abort ;

: check-connected ( -- )
  connection 0 = if
    ." Non connesso" cr
  then ;

: disconnect ( -- )
  check-connected
  connection pq-finish
  0 to connection ;

: test-connection ( -- )
  connection
  pq-status connection-ok <> if handle-error disconnect then ;

: connect ( addr u -- )
  string>c pq-connect to connection
  test-connection ;

: result-status-invalid ( stat -- flag )
  dup pgres-empty-query = if 0 else
  dup pgres-command-ok = if 0 else
  dup pgres-tuples-ok = if 0 else
  1 then then then swap drop ;

: check-result ( res -- )
  dup pq-result-status result-status-invalid if
    pq-result-error-message cstring-type cr
  else
    drop
  then ;

: db-exec ( -- )
  0 c-to-query-buffer
  connection querybuffer addr>c pq-exec
  dup check-result
  pq-clear 
  query-buffer-reset ;

: prova s" dbname=milleps user=dba password=sql" connect ;