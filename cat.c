#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int do_cat(const int fd);
static void die(const char *s);

int main(int argc, char const *argv[])
{
    if (argc < 2){
        //read from stdin
        if(do_cat(STDIN_FILENO)<0) die("STDIN");
    }else{
        for (int i=1; i<argc; i++){
            int fd = open(argv[i], O_RDONLY);
            if (do_cat(fd) < 0) die(argv[i]);
        }
    }
    return 0;
}

#define BUFFER_SIZE 4096
static int do_cat(const int fd){
    unsigned char buf[BUFFER_SIZE];
    if (fd<0) return -1;
    for(;;){
        int ret = read(fd, buf, sizeof buf); //read sizeof(buf) from file stream
        if(ret < 0) return -1;
        if(ret == 0) break; // reached to end of file
        if(write(STDOUT_FILENO, buf, ret) < 0) return -1; // write to stdout
    }
    if(close(fd)<0) return -1;
}

static void die(const char *s){
    perror(s);
    exit(1);
}
