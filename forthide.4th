only definitions
vocabulary forthide

also gtk 
also glade
also forthide definitions

\ Glade file

0 value h-gladefile
: (init-gladefile) s" forthide.glade" glade-xml-new  dup 0= if abort" Glade file load error" then  to h-gladefile ;
: (glade-get-widget) ( c-addr u -- wid ) h-gladefile irot glade-xml-get-widget  dup 0= if abort" Glade widget loading error" then ;
: (glade-store-widget) ( xt c-addr u -- ) (glade-get-widget) to swap execute ;

\ Console window

0 value h-console
0 value h-text-buffer

: (console-insert-text) ( c-addr u -- )
  h-text-buffer irot gtk-text-buffer-insert-end ;

: (console-prompt)
  s" 4> " (console-insert-text) ;

: (console-exit-menu)
  h-console gtk-widget-destroy
  gtk-main-quit stopvm ;

: (console-go-to-bottom)
  h-text-buffer gtk-text-iter-new
  2dup gtk-text-buffer-get-end-iter
  2dup gtk-text-buffer-place-cursor
  gtk-text-iter-destroy drop ;

: (testo-insert) 
  gtk-get-current-event gdk-eventkey-keyval . cr
  (console-go-to-bottom)
  stopvm ;

: (console-window)
  ['] h-console s" wndConsole" (glade-store-widget) 
  h-console  s" delete-event" ['] (console-exit-menu)   g-signal-connect
  s" miExit" (glade-get-widget)  s" activate" ['] (console-exit-menu)   g-signal-connect
  s" tvArea" (glade-get-widget)  s" key-press-event" ['] (testo-insert)  g-signal-connect 
  s" tvArea" (glade-get-widget)  gtk-text-view-get-buffer  to h-text-buffer 

  (console-prompt) 
  h-console gtk-widget-show-all ;

\ Init

: forthide gtk-init glade-init (init-gladefile) (console-window) gtk-main ;