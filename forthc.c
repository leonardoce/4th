//@+leo-ver=4-thin
//@+node:leonardoce.20090629082550.220:@thin forthc.c
//@@language c

#define EXE_TEMPLATE "forthemb_template.c"
#define BUFFER_LEN 1024

#include <stdio.h>
#include <string.h>
#include "utils.h"

int main(int argc, char **argv) {
    if(argc!=3) {
        printf("Uso: %s <nomeimmagine> <eseguibile>", argv[0]);
        return 1;
    }

    char *nomeFileC = (char *)malloc(strlen(argv[2])+3);
    strcpy(nomeFileC, argv[2]);
    strcat(nomeFileC, ".c");

    InputStream *in = InputStream_NewForFile(argv[1]);
    InputStream *inTemplate = InputStream_NewForFile(EXE_TEMPLATE);
    OutputStream *out = OutputStream_NewForFile(nomeFileC);
    char pad[BUFFER_LEN];

    if(in==NULL) {
        printf("Errore in apertura file immagine.\n");
    } else if(inTemplate==NULL) {
        printf("Errore in apertura file template (%s).\n", EXE_TEMPLATE);        
    } else {    
        printf("genero: %s\n", nomeFileC);

        //@        @+others
        //@+node:leonardoce.20090629082550.223:Scrittura immagine
        OutputStream_WriteString(out, "char forthImage[] = {\n");
        while(!InputStream_Eof(in)) {
            sprintf(pad, "%i,", InputStream_ReadByte(in));
            OutputStream_WriteString(out, pad);
        }
        OutputStream_WriteString(out,"};\n\n");

        sprintf(pad, "int forthImageLen = %i;\n\n", in->bufferLen);
        OutputStream_WriteString(out, pad);
        //@nonl
        //@-node:leonardoce.20090629082550.223:Scrittura immagine
        //@+node:leonardoce.20090629082550.225:Scrittura template
        while(!InputStream_Eof(inTemplate)) {
            int letti = InputStream_Read(inTemplate, pad, BUFFER_LEN);
            OutputStream_Write(out, pad, letti );
        }
        //@-node:leonardoce.20090629082550.225:Scrittura template
        //@-others

        InputStream_Delete(in);
        InputStream_Delete(inTemplate);
        OutputStream_Delete(out);

        //@        <<compilazione>>
        //@+node:leonardoce.20090629082550.226:<<compilazione>>
        #ifdef OS_WINDOWS
        sprintf(pad, "gcc -o %s -DOS_WINDOWS %s -L. -l4th", argv[2], nomeFileC);
        #else
        sprintf(pad, "gcc -o %s -DOS_LINUX %s -L. -l4th -ldl", argv[2], nomeFileC);
        #endif
        printf("eseguo: %s\n", pad);
        system(pad);

        #ifdef OS_WINDOWS
            sprintf(pad, "strip -s %s.exe", argv[2]);
        #else
            sprintf(pad, "strip -s %s", argv[2]);
        #endif
        printf("eseguo: %s\n", pad);
        system(pad);
        //@nonl
        //@-node:leonardoce.20090629082550.226:<<compilazione>>
        //@nl
    }
    return 0;
}
//@-node:leonardoce.20090629082550.220:@thin forthc.c
//@-leo
