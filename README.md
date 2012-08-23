4th Forth System
================

This is a forth system based on a VM-architecture. The bytecode
interpreter can be compiled in Windows and in Linux with a simple ANSI
C compiler. The system in designed to be simple and solid.

The system has primitives to call external code, which must be located
in a external shared library. You can also add additional primitives.

You can save the system state in a "dump" which can be translated to a
C file and then linked to the runtime to generate a turnkey
application.

How to compile
==============

Under Linux use the shell script `compila.sh` and under Windows you
can use `compila.bat`.

You will find a `forthconsole` executable which is a Forth REPL that
you can use to develop in a interactive way. 

Examples
========

Under the `examples` directory you can find some example of what you
can do with this Forth system.

Editor support
==============

There is a minimal editor support for editing Forth files under Emacs
under the `emacs` directory.

How to generate turnkey applications
====================================

To generate turnkey applications you must:

Load your application in the interactive environment and create a
`main` word that will be called by the application.

```
C> forth
4Forth 0.1 (06/2009)
Code Space: 2434
Data Space: 23489
----
 
kernel full.4th
 
 
4> : main ." turnkey application example!" cr ;
 ok
```

Generate a forth image (`forth.image`) with the word `saveimage`:

```
4> saveimage
 ok
4>  
```

Execute `forthc` that will embed your image in a C file and will
compile that file with the forth runtime:

```
C> forthc forth.image myexample
genero: myexample.c
eseguo: gcc -o myexample -DOS_WINDOWS myexample.c -L. -l4th
eseguo: strip -s myexample.exe

C> dir myexample.exe
23/08/12  15.29           128.014 myexample.exe
```
     
You are ready to run:

```
C> myexample.exe
turnkey application example!
```

As you see a turnkey application with all the forth libraries and the
VM is something like 128K, which is not terribly big in this days.

License
=======

Copyright (c) 2012, Leonardo Cecchi
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met: 

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer. 
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

