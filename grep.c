#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
static void do_grep(regex_t *pat, FILE *src) {
    char buf[4096];
    while(fgets(buf, sizeof buf, src)){
        if(regexec(pat, buf, 0, NULL, 0) == 0){
            fputs(buf, stdout);
        }
    }
}

int main(int argc, char const *argv[])
{
    /*
    argv[1] pattern
    stdin file
    */
    regex_t pat;
    int err;
    int i;
    if(argc < 2){
        printf("%s usage:[pattern] [file1] [file2]...\n", argv[0]);
        exit(1);
    }
    err = regcomp(&pat, argv[1], REG_EXTENDED|REG_NOSUB|REG_NEWLINE);
    if(err != 0){
        char buf[1024];
        regerror(err, &pat, buf, sizeof buf);
        puts(buf);
        exit(1);
    }
    if (argc ==2){
        // assuming that file path are given as stdin.
        do_grep(&pat, stdin);
    } else {
        // assuming file paths are given as argv[2:]
        for (size_t i = 2; i < argc; i++)
        {
            FILE *f;
            f = fopen(argv[i], "r");
            if(!f){
                perror(argv[i]);
                exit(1);
            }
            do_grep(&pat, f);
            fclose(f);
        }
        
    }
    regfree(&pat);
    return 0;
}
