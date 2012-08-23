: crea-campo-input ( obj nome label -- | hbox entry gtk-lab | box )
    0 0 gtk-hbox-new 'hbox set!
    gtk-label-new 'gtk-lab set!
    gtk-entry-new 
      dup 'entry set!
      object-set!
    'hbox @ 'gtk-lab @ 0 0 0 gtk-box-pack-start
    'hbox @ 'entry @ 1 1 1 gtk-box-pack-start ;

: finestra-input
  { obj } {
    new-object 'obj set!
    gtk-window-new 0
      dup 400 400 gtk-window-set-default-size      
      dup "Ciao da Leonardo" gtk-window-set-title
      'obj @ 'wnd object-set!

  } local-vars ;

