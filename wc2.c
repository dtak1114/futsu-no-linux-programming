#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

static int do_wc(FILE *f);
static void die(const char *s);

//wc command usin stdio library. should work even if there is no \n.

int main(int argc, char const *argv[])
{
    if (argc < 2){
        fprintf(stderr, "%s: no file given.", argv[0]);
        exit(1);
    }
    FILE *f = fopen(argv[1], "r");
    printf("\t%d %s\n", do_wc(f), argv[1]);
    return 0;
}

static int do_wc(FILE *f){
    if (!f) return -1;
    int lcnt = 0;
    int c;
    char last = '\n';
    while((c = getc(f)) != EOF){
        if(c == '\n') lcnt++;
        last = c;
    }
    // ++ if no \n at the end(consider it as 1line)
    if (last != '\n'){
        lcnt++;
    }
    if(fclose(f) != 0) return -1;
    return lcnt;
}

static void die(const char *s){
    perror(s);
    exit(1);
}
