only definitions
vocabulary glade
also glade definitions
\ Utilizzo di glade

0 value h-glade
0 value h-glade-init
0 value h-glade-xml-new
0 value h-glade-xml-get-widget

: gladelibname ( -- caddr u ) oslinux if s" libglade-2.0.so" else s" libglade-2.0-0.dll" then ;
: (glade-entry-point) ( xt caddr u -- ) with-cstring  h-glade get-cstring cprocaddress-check  wo-cstring swap to execute ;
: (glade-entry-points) ( -- ) 
  ['] h-glade-init s" glade_init" (glade-entry-point)
  ['] h-glade-xml-new s" glade_xml_new" (glade-entry-point)
  ['] h-glade-xml-get-widget s" glade_xml_get_widget" (glade-entry-point) ;
: (glade-lib-init) ( -- ) gladelibname with-cstring  get-cstring cloadlibrary-check  wo-cstring  to h-glade ;
: glade-init ( -- ) (glade-lib-init) (glade-entry-points)  h-glade-init 0ccall drop ;
: glade-xml-new ( c-addr r -- handle ) with-cstring  get-cstring 0 0 h-glade-xml-new 3ccall wo-cstring ;
: glade-xml-get-widget ( self c-addr u -- handle ) with-cstring  get-cstring h-glade-xml-get-widget 2ccall  wo-cstring ;
