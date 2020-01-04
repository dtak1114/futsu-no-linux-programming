#include <stdio.h>
#include <stdlib.h>

// cat that converts \t into "\t", \n into "$\n"
int main(int argc, char const *argv[])
{
    for(int i=1;i<argc;i++){
        FILE* f = fopen(argv[i],"r");
        if (!f){
            perror(argv[i]);
            exit(1);
        }
        int c;
        while((c = fgetc(f)) != EOF){
            if(c=='\t'){
                fputs("\\t", stdout);
            }else if(c=='\n'){
                fputs("$\n", stdout);
            } else {
                if(putchar(c) < 0 ) exit(1);
            }
        }
        fclose(f);
    }
    return 0;
}
