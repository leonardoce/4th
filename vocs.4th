\ DA DPANS 94 A.16.6.2.0715

1024 constant vocs-names-max local
create vocs-names local vocs-names-max allot 
0 value vocs-names-len local

: space-in-vocs-names ( -- )
  32 vocs-names vocs-names-len + !
  vocs-names-len 1+ to vocs-names-len ; local

: vocs-names-free ( -- l )
  vocs-names-max vocs-names-len - ; local

: last-len ( -- l )
  last nip ; local

: (register-voc) ( -- )
  last-len 1+ vocs-names-free > if 
    abort" Max vocabulary space" 
  else
    last vocs-names vocs-names-len + swap cmove
    last-len vocs-names-len + to vocs-names-len
    space-in-vocs-names 
  then ; local

: vocabulary ( name -- )
  wordlist create , (register-voc) 
  does> @ >r 
  get-order swap drop 
  r> swap set-order ;

: vocs ( -- )
  ." forth "
  vocs-names vocs-names-len type ;