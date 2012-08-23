only vocabulary cinvoke
also cinvoke definitions

marker before

\ ---------------
\ Mapping CInvoke 
\ ---------------

: cinvoke-lib ( -- caddr u )
  oslinux if s" cinvoke.so" else s" cinvoke-dll.dll" then ;

\ ----------------
\ Utilizzo cinvoke
\ ----------------
0 value h-cinvoke
0 value h-cinv-context-create
0 value h-cinv-library-create
0 value h-cinv-library-delete
0 value h-cinv-library-load-entrypoint
0 value cinvoke-context

: (cinvoke-entrypoint-load) ( caddr u -- ptr )
  with-cstring
  h-cinvoke get-cstring cprocaddress-check 
  wo-cstring ;

: (cinvoke-lib-init) ( -- )
  cinvoke-lib with-cstring  get-cstring cloadlibrary-check  to h-cinvoke 
  s" cinv_context_create" (cinvoke-entrypoint-load)  to h-cinv-context-create
  s" cinv_library_create" (cinvoke-entrypoint-load)  to h-cinv-library-create
  s" cinv_library_delete" (cinvoke-entrypoint-load)  to h-cinv-library-delete
  s" cinv_library_load_entrypoint" (cinvoke-entrypoint-load)  to h-cinv-library-load-entrypoint
  ;

: (cinvoke-create-context) ( -- )
  cinvoke-context 0= if h-cinv-context-create 0ccall  to cinvoke-context then 
  cinvoke-context 0= if abort" Failed cinvoke context creation" then ;

: cinvoke-init ( -- )
  cinvoke-context 0= if (cinvoke-lib-init) (cinvoke-create-context) then ;
  
: cinv-library-create ( caddr u -- h )
  with-cstring  cinvoke-context get-cstring h-cinv-library-create 2ccall  wo-cstring ;

: cinv-library-delete ( h -- )
  cinvoke-context swap  h-cinv-library-delete 2ccall  drop ;

: cinv-library-load-entrypoint ( hlib c-addr u -- ptr )
  with-cstring  cinvoke-context swap get-cstring  h-cinv-library-load-entrypoint 3ccall wo-cstring ;

\ ------------------
\ Gestione callbacks
\ ------------------