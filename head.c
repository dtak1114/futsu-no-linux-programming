#include <stdio.h>
#include <stdlib.h>
#define _GNU_SOURCE
#include <getopt.h>

#define DEFAULT_N_LINES 5


static struct option longopts[] = {
    {"lines", required_argument, NULL, 'n'},
    {"help", no_argument, NULL, 'h'},
    {0, 0, 0, 0} // tell getopt_long that this is the end of line.
};

static void do_head(FILE *f, long nlines);

int main(int argc, char *argv[])
{
    /*
        ./head --lines 4  README.md 
        ./head -n 4  README.md 
        ./head -n 4 < README.md 
        ./head -h
        ./head --help
    */
    int opt;
    long nlines = DEFAULT_N_LINES;
    while((opt = getopt_long(argc, argv, "n:", longopts, NULL)) != -1){ 
        //3rd argument: pass only argument that needs to be parsed.(h is not required.)
        switch(opt){
            case 'n': // -n, --lines
                nlines = atol(optarg);
                break;
            case 'h': // -h, --help
                fprintf(stdout, "Usage: %s [-n LINES] [FILE...]\n", argv[0]);
                exit(0);
            case '?': // anyother
                fprintf(stderr, "Usage: %s [-n LINES] [FILE...]\n", argv[0]);
                exit(1);
        }
    }
    if(optind == argc){
        // from stdin
        do_head(stdin, nlines); 
    }else{
        // from file name given from argument
        for (int i = optind; i < argc; i++)
        {
            FILE *f;
            f = fopen(argv[i], "r");
            if(!f){
                perror(argv[i]);
                exit(1);
            }
            do_head(f, nlines);
            fclose(f);
        }
        
    }
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


