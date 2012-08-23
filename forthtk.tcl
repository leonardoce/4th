#@+leo-ver=4-thin
#@+node:leonardoce.20090622083507.9:@thin forthtk.tcl
#@@language tcl
package require Tk

#@<<comunicazione forth>>
#@+node:leonardoce.20090622083507.14:<<comunicazione forth>>
set forthChannel {}
set lastIndex "1.0"

proc scorriInFondo {} {
    global lastIndex
    set lastChar [.consoleState count -chars "1.0" end ]
    set lastIndex "1.0 + $lastChar chars - 1 chars"
    .consoleState see end
}

proc riceviDaForth {} {
    global forthChannel
    global lastIndex

    set linea [read $forthChannel]
    .consoleState insert end $linea

    scorriInFondo    
}

proc apriForth {} {
    global forthChannel

    switch $::tcl_platform(platform) {
      windows {
         set forthExe "forthconsole.exe"
      }
      unix {
         set forthExe "./forthconsole"
      }
    }


    set forthChannel [ open "| $forthExe --image forth.image" r+ ]
    fconfigure $forthChannel -buffering none
    fconfigure $forthChannel -blocking 0
    fileevent $forthChannel readable riceviDaForth
}

proc invioComando {} {
    global lastIndex
    global forthChannel

    set testo [.consoleState get $lastIndex end]
    scorriInFondo    

    puts $forthChannel [string trim $testo]
}
#@-node:leonardoce.20090622083507.14:<<comunicazione forth>>
#@nl
#@<<pulsanti>>
#@+node:leonardoce.20090622083507.15:<<pulsanti>>
#@+others
#@+node:leonardoce.20090622083507.16:pulisci
proc pulisci {} {
    .consoleState delete "1.0" end
    .consoleState insert end "-- clear --\n"
    scorriInFondo
}
#@nonl
#@-node:leonardoce.20090622083507.16:pulisci
#@+node:leonardoce.20090622083507.17:carica
proc carica {} {
    set fileName [tk_getOpenFile -filetypes [list [list "Forth Files" ".4th"]] ]
    if {$fileName != ""} {
        .pulsanti.txtFile delete 0 end
        .pulsanti.txtFile insert end $fileName
    }
}
#@-node:leonardoce.20090622083507.17:carica
#@+node:leonardoce.20090622083507.18:rileggi
proc rileggi {} {
    global forthChannel

    set fileName [ .pulsanti.txtFile get ]
    if {$fileName != ""} {
        pulisci

        close $forthChannel
        apriForth

        .consoleState insert end "loadfile $fileName\n"
        invioComando
    }
}
#@-node:leonardoce.20090622083507.18:rileggi
#@-others
#@nonl
#@-node:leonardoce.20090622083507.15:<<pulsanti>>
#@nl

proc interfacciaGrafica {} {
    apriForth

    wm title . "LeoForth - Tk Frontend"    
    text .consoleState -font "Courier 12" -yscrollcommand {.scroll set}
    scrollbar .scroll -command {.consoleState yview}
    bind .consoleState <Key-Return> invioComando

    frame .pulsanti
    entry .pulsanti.txtFile 
    button .pulsanti.carica -text {Carica} -command carica
    button .pulsanti.rileggi -text {Rileggi} -command rileggi
    button .pulsanti.pulisci -text {Pulisci} -command pulisci

    grid .pulsanti.txtFile .pulsanti.carica .pulsanti.rileggi .pulsanti.pulisci  -sticky nsew
    grid columnconfigure .pulsanti 0 -weight 1

    grid .pulsanti -sticky nsew
    grid .consoleState .scroll -sticky nsew
    grid columnconfigure . 0 -weight 1
    grid rowconfigure . 1 -weight 1
}

interfacciaGrafica
#@-node:leonardoce.20090622083507.9:@thin forthtk.tcl
#@-leo
