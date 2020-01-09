#include <stdio.h>
#include <stdlib.h>
static void do_head(FILE *f, long nlines);

int main(int argc, char const *argv[])
{
    if(argc !=2){
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        exit(1);
    }
    do_head(stdin, atol(argv[1])); //ascii to long
    return 0;
}

static void do_head(FILE *f, long nlines){
    if(nlines <= 0) return;
    int c;
    while ((c = getc(f)) != EOF){
        if(putchar(c) < 0) exit(1);
        if(c == '\n'){
            nlines--;
            if(nlines == 0) return;
        }
    }
}

