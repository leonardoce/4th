\ @+leo-ver=4-thin
\ @+node:leonardoce.20090623081933.3:@thin socket.4th
\ @@language forth
only vocabulary socket
also socket definitions

\ @+others
\ @+node:leonardoce.20090623081933.5:Costanti
2 constant af_inet
af_inet constant pf_inet

1 constant sock_stream
2 constant sock_dgram

begin-structure addrinfo 
    1 cells +field ai_flags
    1 cells +field ai_family
    1 cells +field ai_socktype
    1 cells +field ai_protocol
    1 cells +field ai_addrlen
    1 cells +field ai_addr
    1 cells +field ai_canonname
    1 cells +field ai_next
end-structure
\ @-node:leonardoce.20090623081933.5:Costanti
\ @+node:leonardoce.20090623081933.8:Variabili
0 value sock-handle local
0 value h-bind local
0 value h-socket local
0 value h-select local
0 value h-listen local
0 value h-recv local
0 value h-send local
0 value h-closesocket local
0 value h-getaddrinfo local
\ @nonl
\ @-node:leonardoce.20090623081933.8:Variabili
\ @+node:leonardoce.20090623081933.9:Inizializzazione winsock
2 constant winsock-ver

create winsock-data 512 allot
0 value h-wsastartup

: init-winsock 
  sock-handle ext" WSAStartup" cprocaddress-check to h-wsastartup
  winsock-ver winsock-data addr>c h-wsastartup 2ccall 
  0<> if abort" Winsock startup error" then ;
\ @nonl
\ @-node:leonardoce.20090623081933.9:Inizializzazione winsock
\ @+node:leonardoce.20090623081933.4:Interfaccia di basso livello
: sock-library ( -- caddr u )
  oswindows if s" wsock32.dll" else s" libc.so" then ;

: sock-init
  sock-library string>c cloadlibrary-check to sock-handle

  sock-handle
  dup ext" socket" cprocaddress-check to h-socket
  dup ext" select" cprocaddress-check to h-select
  dup ext" bind" cprocaddress-check to h-select
  dup ext" listen" cprocaddress-check to h-listen
  dup ext" recv" cprocaddress-check to h-recv
  dup ext" send" cprocaddress-check to h-send
  dup ext" closesocket" cprocaddress-check to h-closesocket
  dup ext" getaddrinfo" cprocaddress-check to h-getaddrinfo
  drop

  oswindows if init-winsock then ;
\ @-node:leonardoce.20090623081933.4:Interfaccia di basso livello
\ @+node:leonardoce.20090623081933.6:Mapping Forth
: socket ( domain type -- sock ) 0 h-socket 3ccall 
  dup 0 invert = if abort" Socket creation error" then ;
: closesocket ( sock -- ) h-closesocket 1ccall drop ;
\ @nonl
\ @-node:leonardoce.20090623081933.6:Mapping Forth
\ @-others

only definitions
\ @nonl
\ @-node:leonardoce.20090623081933.3:@thin socket.4th
\ @-leo
