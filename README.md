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

