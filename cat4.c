#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

// cat using fread and fwrite
int main(int argc, char const *argv[])
{
    for(int i=1;i<argc;i++){
        FILE* f = fopen(argv[i],"r");
        if (!f){
            perror(argv[i]);
            exit(1);
        }
        unsigned char buf[BUFFER_SIZE];
        for(;;){
            int n_read = fread(buf, sizeof(unsigned char), sizeof buf, f);
            if(ferror(f) != 0) {
                perror(argv[i]);
                exit(1);
            }
            int n_written = fwrite(buf, sizeof(unsigned char), n_read, stdout);
            if(n_written < n_read){
                //failed to write some buffer
                perror(argv[i]);
                exit(1);
            }
            // read all file
            if(n_read < sizeof buf) break;
        }
        fclose(f);
    }
    return 0;
}
