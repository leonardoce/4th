marker before-gui

only vocabulary gui
also gtk
also obj
also gui definitions

\ Window Widget
: window-new ( obj: -- obj ) gtk-window-toplevel gtk-window-new >o ;
: window-title! ( caddr u -- obj: obj -- obj ) o@ irot gtk-window-set-title ;
: window-default-size!  ( height width -- obj: obj -- obj  ) o@ irot gtk-window-set-default-size ;
: window-add-child ( child --  obj: obj -- obj ) o@ swap gtk-container-add ;

\ Menu bar widget
: menu-bar-new ( obj: -- obj ) gtk-menu-bar-new >o ;
: menu-bar-append ( child -- obj: obj -- obj ) o@ gtk-menu-shell-append ;

\ Menu item widget
: menu-item-new ( caddr u -- obj: -- obj ) gtk-menu-item-new-with-label >o ;

\ Menu widget
: menu-new ( caddr u -- obj: -- obj submenu ) menu-item-new >o ;
: menu-start ( ) gtk-menu-new >o ;
: menu-append o@ gtk-menu-shell-append ;
: menu-end o> o@ swap  gtk-menu-item-set-submenu ;

\ Vertical box widget
: vbox-new ( obj: -- obj ) gtk-vbox-new >o ;

: test 
  window-new
    s" Forth Console" window-title!
    400 400 window-default-size!
    vbox-new
      menu-bar-new
        s" File" menu-new 
          menu-start
          s" Open" menu-item-new  o> menu-append
          s" Close" menu-item-new  o> menu-append
          s" -" menu-item-new  o> menu-append
          s" Exit" menu-item-new  o> menu-append
          menu-end 
          o> menu-bar-append
        s" Edit" menu-new
          menu-start
          s" Copy" menu-item-new  o> menu-append
          s" Cut" menu-item-new  o> menu-append
          s" Paste" menu-item-new  o> menu-append
          menu-end
          o> menu-bar-append
        o> vbox-pack
      scrolled-window-new
        text-view-new
          o> scrolled-window-add
        o> vbox-pack-expand
          
      o> window-add-child
    show odrop ;
   
    