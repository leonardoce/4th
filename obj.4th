only vocabulary obj
also obj definitions

\ Queste parole Forth sono utili per definire un semplice
\ sistema orientato agli oggetti

32 value obj-stack-max
1 cells array obj-stack obj-stack-max allot
0 value obj-ptr 

: obj-check-overflow ( -- )
  obj-ptr obj-stack-max >= if abort" Object stack overflow" then ;

: obj-check-underflow ( -- )
  obj-ptr 0= if abort" Object stack underflow" then ;

: o@ ( -- obj )
  obj-check-underflow
  obj-ptr 1- obj-stack @ ;

: >o ( obj -- )
  obj-check-overflow
  obj-ptr obj-stack !
  obj-ptr 1+ to obj-ptr ;

: o> ( -- obj )
  obj-check-underflow
  obj-ptr 1- obj-stack @
  obj-ptr 1- to obj-ptr ;

: (o.)
  obj-ptr 0 do
    i obj-stack @ . space cr
  loop ;

: o. ( -- )
  obj-ptr 0 = if ." Object stack empty" else (o.) then ;

: odrop ( -- ) o> drop ;