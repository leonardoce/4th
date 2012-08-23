\ @+leo-ver=4-thin
\ @+node:leonardoce.20090629082550.234:@thin gtk.4th
\ @@language forth
marker pregtk

only definitions
vocabulary gtk
also gtk definitions

\ @+others
\ @+node:leonardoce.20090629082550.235:Costanti
0 constant gtk-window-toplevel
1 constant gtk-window-popup

1 constant g-connect-after
2 constant g-connect-swapped
\ @nonl
\ @-node:leonardoce.20090629082550.235:Costanti
\ @+node:leonardoce.20090629082550.236:Utili
: ep-tag 4 cells ;
: ep-hlib 3 cells + ;
: ep-fname-c 2 cells + ;
: ep-fname-a 1 cells + ;
: ep-handle ;

: ep-try-loading ( ep -- )
  >r
  r@ ep-fname-a @
  r@ ep-fname-c @
  with-cstring
    r@ ep-hlib @ get-cstring cprocaddress-check
    r@ ep-handle !
  wo-cstring 
  r> drop ;

: ep-runtime ( ep -- handle )
  dup ep-handle @ 0= if ep-try-loading then
  ep-handle @ ;

: extproc: ( hlib c-addr u -- )
  create 
    here ep-tag allot >r
    r@ ep-fname-c !
    r@ ep-fname-a !
    0 r@ ep-handle !
    r> ep-hlib !
      does>
    ep-runtime
  ;
\ @-node:leonardoce.20090629082550.236:Utili
\ @+node:leonardoce.20090629082550.237:Basso Livello

0 value gtk-handle
0 value gobject-handle

0 value h-g-signal-connect-data
0 value h-gtk-button-new-with-label
0 value h-gtk-container-add
0 value h-gtk-get-current-event
0 value h-gtk-hbox-new
0 value h-gtk-init
0 value h-gtk-main
0 value h-gtk-main-quit
0 value h-gtk-menu-new
0 value h-gtk-menu-bar-new
0 value h-gtk-menu-item-new-with-label
0 value h-gtk-menu-shell-append
0 value h-gtk-vbox-new
0 value h-gtk-text-buffer-place-cursor
0 value h-gtk-text-buffer-insert
0 value h-gtk-text-buffer-get-end-iter
0 value h-gtk-text-view-get-buffer
0 value h-gtk-text-view-new
0 value h-gtk-widget-destroy
0 value h-gtk-widget-show-all
0 value h-gtk-window-new
0 value h-gtk-window-set-default-size
0 value h-gtk-window-set-title

: gtk-library-name
  oslinux if ext" libgtk-x11-2.0.so" else ext" libgtk-win32-2.0-0.dll" then ;

: gobject-library-name
  oslinux if ext" libgobject-2.0.so" else ext" libgobject-2.0-0.dll" then ;

: load-gtk-library
  gtk-library-name cloadlibrary-check to gtk-handle
  gobject-library-name cloadlibrary-check to gobject-handle

  gobject-handle ext" g_signal_connect_data" cprocaddress-check to h-g-signal-connect-data
  gtk-handle ext" gtk_button_new_with_label" cprocaddress-check to h-gtk-button-new-with-label
  gtk-handle ext" gtk_container_add" cprocaddress-check to h-gtk-container-add
  gtk-handle ext" gtk_get_current_event" cprocaddress-check to h-gtk-get-current-event
  gtk-handle ext" gtk_hbox_new" cprocaddress-check to h-gtk-hbox-new
  gtk-handle ext" gtk_init" cprocaddress-check to h-gtk-init
  gtk-handle ext" gtk_main" cprocaddress-check to h-gtk-main
  gtk-handle ext" gtk_menu_new" cprocaddress-check to h-gtk-menu-new
  gtk-handle ext" gtk_menu_bar_new" cprocaddress-check to h-gtk-menu-bar-new
  gtk-handle ext" gtk_menu_item_new_with_label" cprocaddress-check to h-gtk-menu-item-new-with-label
  gtk-handle ext" gtk_menu_shell_append" cprocaddress-check to h-gtk-menu-shell-append
  gtk-handle ext" gtk_main_quit" cprocaddress-check to h-gtk-main-quit
  gtk-handle ext" gtk_vbox_new" cprocaddress-check to h-gtk-vbox-new
  gtk-handle ext" gtk_text_buffer_place_cursor" cprocaddress-check to h-gtk-text-buffer-place-cursor
  gtk-handle ext" gtk_text_buffer_insert" cprocaddress-check to h-gtk-text-buffer-insert
  gtk-handle ext" gtk_text_buffer_get_end_iter" cprocaddress-check to h-gtk-text-buffer-get-end-iter
  gtk-handle ext" gtk_text_view_new" cprocaddress-check to h-gtk-text-view-new
  gtk-handle ext" gtk_text_view_get_buffer" cprocaddress-check to h-gtk-text-view-get-buffer
  gtk-handle ext" gtk_widget_destroy" cprocaddress-check to h-gtk-widget-destroy
  gtk-handle ext" gtk_widget_show_all" cprocaddress-check to h-gtk-widget-show-all
  gtk-handle ext" gtk_window_new" cprocaddress-check to h-gtk-window-new
  gtk-handle ext" gtk_window_set_title" cprocaddress-check to h-gtk-window-set-title
; local

: gtk-init
  load-gtk-library 
  0 0 2 h-gtk-init ccall drop ;

\ @-node:leonardoce.20090629082550.237:Basso Livello
\ @+node:leonardoce.20090629082550.238:Gestione Segnali
variable temp-handler
variable temp-instance
: g-signal-connect ( instance c-addr u handler -- )
  temp-handler !
  with-cstring
    temp-instance !

    temp-instance @     \ instance
    get-cstring         \ detailed_signal
    1 getcallback       \ handler
    temp-handler @      \ data
    0                   \ destroy_data
    g-connect-swapped   \ connect_flags

    6 h-g-signal-connect-data ccall
  wo-cstring drop ;
\ @-node:leonardoce.20090629082550.238:Gestione Segnali
\ @+node:leonardoce.20090629082550.239:Interfaccia C
: gtk-button-new-with-label 
  with-cstring get-cstring h-gtk-button-new-with-label 1ccall wo-cstring ;
: gtk-container-add h-gtk-container-add 2ccall ;
: gtk-get-current-event h-gtk-get-current-event 0ccall ;
: gtk-hbox-new 2ccall ;
: gtk-main-quit h-gtk-main-quit 0ccall drop ;
: gtk-main h-gtk-main 0ccall drop ;
: gtk-menu-item-new-with-label with-cstring get-cstring h-gtk-menu-item-new-with-label 1ccall wo-cstring ;
: gtk-menu-shell-append h-gtk-menu-shell-append 2ccall ;
: gtk-text-buffer-insert with-cstring get-cstring 1 negate h-gtk-text-buffer-insert 4ccall drop wo-cstring ;
: gtk-text-buffer-place-cursor h-gtk-text-buffer-place-cursor 2ccall drop ;
: gtk-text-buffer-get-end-iter h-gtk-text-buffer-get-end-iter 2ccall drop ;
: gtk-text-iter-new 16 cells cmalloc ;
: gtk-text-iter-destroy cfree ;
: gtk-text-view-get-buffer h-gtk-text-view-get-buffer 1ccall ;
: gtk-text-view-new 0ccall ;
: gtk-vbox-new 2ccall ;
: gtk-window-new h-gtk-window-new 1ccall ;
: gtk-window-set-title 
  with-cstring get-cstring h-gtk-window-set-title 2ccall wo-cstring drop ;
: gtk-window-set-default-size h-gtk-window-set-default-size 3ccall drop ;
: gtk-widget-destroy h-gtk-widget-destroy 1ccall drop ;
: gtk-widget-show-all h-gtk-widget-show-all 1ccall drop ;

\ @-node:leonardoce.20090629082550.239:Interfaccia C
\ @+node:leonardoce.20090629082550.240:Utili Alto livello

: gtk-text-buffer-insert-end ( buf c-addr u -- ) 
  with-cstring 
    gtk-text-iter-new 
    2dup gtk-text-buffer-get-end-iter
    2dup get-cstring 1 negate h-gtk-text-buffer-insert 4ccall drop
    gtk-text-iter-destroy drop
  wo-cstring ;

: gdk-eventkey-keyval ( evtptr -- code )
  5 cells + cmemcell@ ; 
\ @-node:leonardoce.20090629082550.240:Utili Alto livello
\ @+node:leonardoce.20090629082550.241:Test
0 value wnd
0 value bt

: handler-test 
  ." Ciao da Leonardo!" cr
  gtk-main-quit
  wnd gtk-widget-destroy
  stopvm ;

: gtk-test
  gtk-window-toplevel gtk-window-new to wnd
  s" Clicca qua!" gtk-button-new-with-label to bt

  wnd s" ciao da 4Forth" gtk-window-set-title
  bt s" clicked" ['] handler-test g-signal-connect

  wnd bt gtk-container-add

  wnd gtk-widget-show-all
  gtk-main
;
\ @nonl
\ @-node:leonardoce.20090629082550.241:Test
\ @-others


\ @-node:leonardoce.20090629082550.234:@thin gtk.4th
\ @-leo
