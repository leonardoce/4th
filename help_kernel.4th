\ @+leo-ver=4-thin
\ @+node:leonardoce.20090707081518.7:@thin help_kernel.4th
\ @@language forth
\ --------------------------------------------------------------------------------------------------
\ - Documentazione del kernel
\ --------------------------------------------------------------------------------------------------

\ --------------------------------------------------------------------------------------------------
doc" (
( 

Compilation:  Perform the execution semantics given below. 
Execution: ( 'ccc<paren>' -- ) 
Parse ccc delimited by ) (right parenthesis).  
( is an immediate word. The number of characters in ccc may be 
zero to the number of characters in the parse area. 
"

\ --------------------------------------------------------------------------------------------------
doc" 2drop
2DROP ( x1 x2 -- ) 

Drop cell pair x1 x2 from the stack
"

\ --------------------------------------------------------------------------------------------------
doc" over
OVER ( x1 x2 -- x1 x2 x1 ) 

Place a copy of x1 on top of the stack.
"

\ --------------------------------------------------------------------------------------------------
doc" 2dup
2DUP ( x1 x2 -- x1 x2 x1 x2 ) 

Duplicate cell pair x1 x2.
"

\ --------------------------------------------------------------------------------------------------
doc" ,
, ( x -- ) 

Reserve one cell of data space and store x in the cell.  
If the data-space pointer is aligned when 
, begins execution, it will remain aligned when, 
finishes execution.  
An ambiguous condition exists if the data-space pointer is 
not aligned prior to execution of ,. 
"

\ --------------------------------------------------------------------------------------------------
doc" !
! ( x a-addr -- ) 

Store x at a-addr.
"

\ --------------------------------------------------------------------------------------------------
doc" @
@@ ( a-addr -- x ) 

x is the value stored at a-addr.
"

\ --------------------------------------------------------------------------------------------------
doc" c@
C@ ( c-addr -- char ) 

Fetch the character stored at c-addr.  When the cell size 
is greater than character size, the 
unused high-order bits are all zeroes.
"

\ --------------------------------------------------------------------------------------------------
doc" c!
C! ( char c-addr -- ) 

Store char at c-addr.  When character size is smaller than 
cell size, only the number of low-order bits corresponding 
to character size are transferred. 
"

\ --------------------------------------------------------------------------------------------------
doc" c,
C, ( char -- ) 

Reserve space for one character in the data space and store 
char in the space.  If the data-space pointer is character 
aligned when C, begins execution, it will remain character 
aligned when C, finishes execution.  
An ambiguous condition exists if the data-space pointer 
is not character-aligned prior to execution of C,. 
"

\ --------------------------------------------------------------------------------------------------
doc" variable
VARIABLE ( '<spaces>name' -- ) 

Skip leading space delimiters. Parse name delimited by a 
space.  Create a definition for name with the execution 
semantics defined below.  Reserve one cell of data space at an aligned 
address. 

name is referred to as a 'variable'.

name Execution: ( -- a-addr ) 
a-addr is the address of the reserved cell. A program is 
responsible for initializing the contents 
of the reserved cell. 
"

\ --------------------------------------------------------------------------------------------------
doc" chars
CHARS ( n1 -- n2 ) 

n2 is the size in address units of n1 characters.
"

\ --------------------------------------------------------------------------------------------------
doc" char+
CHAR+ ( c-addr1 -- c-addr2 ) 

Add the size in address units of a character to c-addr1, giving c-addr2. 
"

\ --------------------------------------------------------------------------------------------------
doc" constant
CONSTANT ( x '<spaces>name' -- ) 

Skip leading space delimiters.  Parse name delimited by a space.  
Create a definition for name with the execution semantics defined below. 
name is referred to as a 'constant'.

name Execution: ( -- x ) 
Place x on the stack. 
"

\ --------------------------------------------------------------------------------------------------
doc" depth
DEPTH ( -- +n ) 

+n is the number of single-cell values contained in the data stack 
before +n was placed on the stack.
"

\ --------------------------------------------------------------------------------------------------
doc" quit
QUIT ( -- )  ( R:  i*x -- ) 

Empty the return stack, make the user input device the 
input source, and enter interpretation state.  
Do not display a message.  Repeat the following: 
-  Accept a line from the input source into the 
   input buffer, set >IN to zero, and interpret. 
-  Display the implementation-defined system 
   prompt if in interpretation state, all 
   processing has been completed, and no ambiguous 
   condition exists.   
"

\ --------------------------------------------------------------------------------------------------
doc" abort
ABORT ( i*x -- ) ( R: j*x -- ) 

Empty the data stack and perform the function of QUIT, 
which includes emptying the return 
stack, without displaying a message. 
"

\ --------------------------------------------------------------------------------------------------
doc" 0<> 
0<>    ( x -- flag ) 

flag is true if and only if x is not equal to zero. 
"

\ --------------------------------------------------------------------------------------------------
doc" 0>
0>    ( n -- flag ) 

flag is true if and only if n is greater than zero.
"

\ --------------------------------------------------------------------------------------------------
doc" type
TYPE ( c-addr u -- ) 

If u is greater than zero, display the character string specified by
c-addr and u. When passed a character in a character string whose 
character-defining bits have a value between hex 20 and 7E 
inclusive, the corresponding standard character, specified by 3.1.2.1 
graphic characters, is displayed.  Because different output devices 
can respond differently to control characters, programs that use 
control characters to perform specific functions have an 
environmental dependency. 
"

\ --------------------------------------------------------------------------------------------------
doc" 1+
1+ ( n1|u1 -- n2|u2 ) 

Add one (1) to n1|u1 giving the sum n2|u2. 
"

\ --------------------------------------------------------------------------------------------------
doc" 0=
0= ( x -- flag ) 

flag is true if and only if x is equal to zero. 
"

\ --------------------------------------------------------------------------------------------------
doc" negate
negate ( n1 -- n2 ) 

Negate n1, giving its arithmetic inverse n2.   
"

\ --------------------------------------------------------------------------------------------------
doc" +!
+! ( n|u a-addr -- ) 

Add n|u to the single-cell number at a-addr. 
"

\ --------------------------------------------------------------------------------------------------
doc" postpone
POSTPONE

Interpretation:  Interpretation semantics for this word are undefined. 

Compilation: ( '<spaces>name' -- ) 
Skip leading space delimiters.  Parse name delimited by a space. 
Find name.  Append the compilation semantics of name to the current 
definition.  An ambiguous condition exists if name is not found. 
"

\ --------------------------------------------------------------------------------------------------
doc" [compile]
[COMPILE]
Interpretation:  Interpretation semantics for this word are undefined. 

Compilation: ( '<spaces>name' -- ) 
Skip leading space delimiters.  Parse name delimited by a space.  
Find name.  If name has other than default compilation semantics, 
append them to the current definition; otherwise append the 
execution semantics of name.  An ambiguous condition exists if 
name is not found.
"

\ --------------------------------------------------------------------------------------------------
doc" [char]
[CHAR]

Interpretation:  Interpretation semantics for this word are undefined. 

Compilation: ( '<spaces>name' -- ) 
Skip leading space delimiters.  Parse name delimited by a space.  
Append the run-time semantics given below to the current definition. 

Run-time: ( -- char ) 
"

\ --------------------------------------------------------------------------------------------------
doc" cr
CR ( -- ) 

Cause subsequent output to appear at the beginning of the next line.
"

\ --------------------------------------------------------------------------------------------------
doc" space
SPACE ( -- ) 

Display one space. 
"

\ --------------------------------------------------------------------------------------------------
doc" spaces
SPACES ( n -- ) 

If n is greater than zero, display n spaces. 
"

\ --------------------------------------------------------------------------------------------------
doc" nip
NIP ( x1 x2 -- x2 ) 


Drop the first item below the top of stack. 
"

\ --------------------------------------------------------------------------------------------------
doc' ."
." 

Interpretation:  Interpretation semantics for this word are undefined. 

Compilation: ( "ccc<quote>" -- ) 
Parse ccc delimited by " (double-quote).  Append the run-time semantics 
given below to the current definition. 

Run-time:  ( -- ) 
Display ccc. 

See:  .(
'

\ --------------------------------------------------------------------------------------------------
doc" also
ALSO ( -- ) 

Transform the search order consisting of widn, ... wid2, wid1 (where 
wid1 is searched first) into widn, ... wid2, wid1, wid1.  An ambiguous 
condition exists if there are too many word lists in the search order. 
"

\ --------------------------------------------------------------------------------------------------
doc" forth
FORTH ( -- ) 

Transform the search order consisting of widn, ... wid2, wid1 (where 
wid1 is searched first) into widn, ... wid2, widFORTH-WORDLIST.  
"

\ --------------------------------------------------------------------------------------------------
doc" only
ONLY ( -- ) 

Set the search order to the implementation-defined minimum search order. 
The minimum search order shall include the words FORTH-WORDLIST and 
SET-ORDER.
"

\ --------------------------------------------------------------------------------------------------
doc" order
ORDER ( -- ) 

Display the word lists in the search order in their search order sequence, 
from first searched to last searched.  Also display the word list into 
which new definitions will be placed.  The display format is 
implementation dependent. ORDER may be implemented using pictured numeric 
output words.  Consequently, its use may corrupt the transient region 
identified by #>. 
"

\ --------------------------------------------------------------------------------------------------
doc" previous
PREVIOUS ( -- ) 

Transform the search order consisting of widn, ... wid2, wid1 (where wid1 
is searched first) into widn, ... wid2.  An ambiguous condition exists 
if the search order was empty before PREVIOUS was executed.
"

\ --------------------------------------------------------------------------------------------------
doc' abort"
ABORT"    

Interpretation:  Interpretation semantics for this word are undefined. 

Compilation: ( "ccc<quote>" -- ) 
Parse ccc delimited by a " (double-quote).  Append the run-time semantics given below to the 
current definition.   

Run-time: ( i*x x1 --  | i*x ) ( R: j*x --  | j*x ) 
Remove x1 from the stack.  If any bit of x1 is not zero, display ccc and perform an 
implementation-defined abort sequence that includes the function of ABORT. 

See:  3.4.1 Parsing, 9.6.2.0680 ABORT". 
'

\ --------------------------------------------------------------------------------------------------
doc" cmove
CMOVE ( c-addr1 c-addr2 u -- ) 

If u is greater than zero, copy u consecutive characters from the data space starting at c-addr1 to 
that starting at c-addr2, proceeding character-by-character from lower addresses to higher 
addresses. 

Contrast with:  17.6.1.0920 CMOVE>. 
"

\ --------------------------------------------------------------------------------------------------
doc" to
TO

Interpretation: ( x '<spaces>name' -- ) 
Skip leading spaces and parse name delimited by a space.  Store x in name.  An ambiguous 
condition exists if name was not defined by VALUE. 

Compilation: ( '<spaces>name' -- ) 
Skip leading spaces and parse name delimited by a space.  Append the run-time semantics given 
below to the current definition.  An ambiguous condition exists if name was not defined by 
VALUE. 

Run-time: ( x -- ) 
Store x in name. 
"

\ --------------------------------------------------------------------------------------------------
doc" value
VALUE ( x '<spaces>name' -- ) 

Skip leading space delimiters.  Parse name delimited by a space.  Create a definition for name 
with the execution semantics defined below, with an initial value equal to x. 
name is referred to as a 'value'. 

name Execution: ( -- x ) 
Place x on the stack.  The value of x is that given when name was created, until the phrase x TO 
name is executed, causing a new value of x to be associated with name. 
"

\ --------------------------------------------------------------------------------------------------
doc" <#
<# ( -- ) 

Initialize the pictured numeric output conversion process. 
"

\ --------------------------------------------------------------------------------------------------
doc" #>
#> ( xd -- c-addr u ) 

Drop xd.  Make the pictured numeric output string available as a character string.  c-addr and u 
specify the resulting character string.  A program may replace characters within the string. 
"

\ --------------------------------------------------------------------------------------------------
doc" #>
# ( ud1 -- ud2 ) 

Divide ud1 by the number in BASE giving the quotient ud2 and the remainder n.  (n is the least-
significant digit of ud1.)  Convert n to external form and add the resulting character to the 
beginning of the pictured numeric output string.  An ambiguous condition exists if # executes 
outside of a <# #> delimited number conversion. 
"

\ --------------------------------------------------------------------------------------------------
doc" hold
HOLD ( char -- ) 

Add char to the beginning of the pictured numeric output string.  An ambiguous condition exists 
if HOLD executes outside of a <# #> delimited number conversion. 
"



\ --------------------------------------------------------------------------------------------------
\ --------------------------------------------------------------------------------------------------
\ --------------------------------------------------------------------------------------------------
\ --------------------------------------------------------------------------------------------------

\ --------------------------------------------------------------------------------------------------
doc" +
+ ( n1 n2 -- n3 )
Somma due numeri dallo stack
"

\ --------------------------------------------------------------------------------------------------
doc" *
* ( n1 n2 -- n3 )
Moltiplicazione fra due numeri
"

\ --------------------------------------------------------------------------------------------------
doc" open-file 
OPEN-FILE ( c-addr u fam -- fileid ior ) 

Open the file named in the character string specified by c-addr u, with file access method 
indicated by fam.  The meaning of values of fam is implementation defined. 
If the file is successfully opened, ior is zero, fileid is its identifier, and the file has been 
positioned to the start of the file. 
Otherwise, ior is the implementation-defined I/O result code and fileid is undefined. 
"

\ --------------------------------------------------------------------------------------------------
doc" read-file
READ-FILE ( c-addr u1 fileid -- u2 ior ) 

Read u1 consecutive characters to c-addr from the current position of the file identified by 
fileid. 
If u1 characters are read without an exception, ior is zero and u2 is equal to u1. 
If the end of the file is reached before u1 characters are read, ior is zero and u2 is the number of 
characters actually read. 
If the operation is initiated when the value returned by FILE-POSITION is equal to the value 
returned by FILE-SIZE for the file identified by fileid, ior is zero and u2 is zero. 
If an exception occurs, ior is the implementation-defined I/O result code, and u2 is the number 
of characters transferred to c-addr without an exception. 
An ambiguous condition exists if the operation is initiated when the value returned by FILE-
POSITION is greater than the value returned by FILE-SIZE for the file identified by fileid, or 
if the requested operation attempts to read portions of the file not written. 
At the conclusion of the operation, FILE-POSITION returns the next file position after the 
last character read. 
"

\ --------------------------------------------------------------------------------------------------
doc" close-file
CLOSE-FILE ( fileid -- ior ) 

Close the file identified by fileid.  ior is the implementation-defined I/O result code. 
"

\ --------------------------------------------------------------------------------------------------
doc" flush-file
FLUSH-FILE ( fileid -- ior ) 

Attempt to force any buffered information written to the file referred to by fileid to be written to 
mass storage, and the size information for the file to be recorded in the storage directory if 
changed.  If the operation is successful, ior is zero.  Otherwise, it is an implementation-defined 
I/O result code. 
" 

\ --------------------------------------------------------------------------------------------------
doc" write-file
WRITE-FILE ( c-addr u fileid -- ior ) 

Write u characters from c-addr to the file identified by fileid starting at its current position.  ior 
is the implementation-defined I/O result code. 
At the conclusion of the operation, FILE-POSITION returns the next file position after the 
last character written to the file, and FILE-SIZE returns a value greater than or equal to the 
value returned by FILE-POSITION. 
"

\ -------------------------------------------------------------------------------------------------- 
doc" reposition-file
REPOSITION-FILE ( ud fileid -- ior ) 

Reposition the file identified by fileid to ud.  ior is the implementation-defined I/O result code.  
An ambiguous condition exists if the file is positioned outside the file boundaries. 
At the conclusion of the operation, FILE-POSITION returns the value ud. 
"

\ -------------------------------------------------------------------------------------------------- 
doc" file-position
FILE-POSITION ( fileid -- ud ior ) 

ud is the current file position for the file identified by fileid.  ior is the implementation-defined 
I/O result code.  ud is undefined if ior is non-zero. 
"

\ -------------------------------------------------------------------------------------------------- 
doc" resize-file
( ud fileid -- ior ) 
Set the size of the file identified by fileid to ud.  ior is the implementation-defined I/O result 
code. 
If the resultant file is larger than the file before the operation, the portion of the file added as a 
result of the operation might not have been written. 
At the conclusion of the operation, FILE-SIZE returns the value ud and FILE-POSITION 
returns an unspecified value. 
 See:  11.6.1.2080 READ-FILE, 11.6.1.2090 READ-LINE. 
"

\ --------------------------------------------------------------------------------------------------
doc" saveimage
saveimage ( --  )

Salva l'immagine che comprende il dizionario, lo spazio dati e lo spazio codice all'interno
di un file 'forth.image'
"

\ --------------------------------------------------------------------------------------------------
doc" r@
R@

Interpretation:  Interpretation semantics for this word are undefined. 

Execution: ( -- x )  ( R:  x -- x ) 
Copy x from the return stack to the data stack.
"

\ --------------------------------------------------------------------------------------------------
doc" pad
PAD ( -- c-addr ) 

c-addr is the address of a transient region that can be used to hold data for intermediate 
processing. 
 See:  3.3.3.6 Other transient regions. 
"

\ --------------------------------------------------------------------------------------------------
doc" :
:    'colon'  CORE 
( C: '<spaces>name' -- colon-sys ) 

Skip leading space delimiters.  Parse name delimited by a space.  Create a definition for name, 
called a 'colon definition'.  Enter compilation state and start the current definition, producing 
colon-sys.  Append the initiation semantics given below to the current definition. 
The execution semantics of name will be determined by the words compiled into the body of the 
definition.  The current definition shall not be findable in the dictionary until it is ended (or until 
the execution of DOES> in some systems). 

Initiation: ( i*x -- i*x )  ( R:  -- nest-sys ) 
Save implementation-dependent information nest-sys about the calling definition.  The stack 
effects i*x represent arguments to name. 

name Execution: ( i*x -- j*x ) 
Execute the definition name.  The stack effects i*x and j*x represent arguments to and results 
from name, respectively. 

See:  3.4 The Forth text interpreter, 3.4.1 Parsing, 3.4.5 Compilation, 6.1.1250 DOES>, 6.1.2500 
[, 6.1.2540 ], 15.6.2.0470 ;CODE. 
"


\ --------------------------------------------------------------------------------------------------
doc" ;
;    'semicolon'  CORE 
Interpretation:  Interpretation semantics for this word are undefined. 

Compilation: ( C: colon-sys -- ) 
Append the run-time semantics below to the current definition.  End the current definition, 
allow it to be found in the dictionary and enter interpretation state, consuming colon-sys.  If the 
data-space pointer is not aligned, reserve enough data space to align it. 

Run-time:  ( -- )  ( R:  nest-sys -- ) 
Return to the calling definition specified by nest-sys. 

See:  3.4 The Forth text interpreter, 3.4.5 Compilation. 
"

\ --------------------------------------------------------------------------------------------------
doc" ;
PARSE      ( char 'ccc<char>' -- c-addr u ) 
Parse ccc delimited by the delimiter char. 
c-addr is the address (within the input buffer) and u is the length of the parsed string.  If the 
parse area was empty, the resulting string has a zero length. 
See:  3.4.1 Parsing. 
"

\ --------------------------------------------------------------------------------------------------
doc" ;
ROT    'rote' ( x1 x2 x3 -- x2 x3 x1 ) 
Rotate the top three stack entries. 
"

\ --------------------------------------------------------------------------------------------------
doc" ;
DROP ( x -- ) 
Remove x from the stack. 
"

\ --------------------------------------------------------------------------------------------------
doc" begin-structure
BEGIN-STRUCTURE ( 'hspacesiname' - struct-sys 0 )

Skip leading space delimiters. Parse name delimited by a space. Create a definition for
name with the execution semantics defined below. Return a struct-sys (zero or more
implementation dependent items) that will be used by END-STRUCTURE and an initial
offset of 0.

name Execution: ( - +n )
+n is the size in memory expressed in address units of the data structure. An ambiguous
condition exists if name is executed prior to the associated END-STRUCTURE being
executed.
See: 10.6.2.0 +FIELD and 10.6.2.0 END-STRUCTURE.DROP ( x -- ) 
Remove x from the stack. 
"

\ --------------------------------------------------------------------------------------------------
doc" end-structure
END-STRUCTURE ( struct-sys +n - )
Terminate definition of a structure started by BEGIN-STRUCTURE.
See: 10.6.2.0 +FIELD and 10.6.2.0 BEGIN-STRUCTURE.
Implementation: Terminate definition of a structure.
"


\ --------------------------------------------------------------------------------------------------
doc" +field
+FIELD ( n1 n2 'hspacesiname' - n3 )
Skip leading space delimiters. Parse name delimited by a space. Create a definition for
name with the execution semantics defined below. Return n3 = n1 + n2 where n1 is the
offset in the data structure before +FIELD executes, and n2 is the size of the data to be
added to the data structure. n1 and n2 are in address units.
name Execution: ( addr1 - addr2 )
Add n1 to addr1 giving addr2.
"
\ @nonl
\ @-node:leonardoce.20090707081518.7:@thin help_kernel.4th
\ @-leo
