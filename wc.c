#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int do_wc(const int fd);
static void die(const char *s);

int main(int argc, char const *argv[])
{
    if (argc < 2){
        fprintf(stderr, "%s: no file given.", argv[0]);
        exit(1);
    }
    int fd = open(argv[1], O_RDONLY);
    printf("\t%d %s\n", do_wc(fd), argv[1]);
    return 0;
}

#define BUFFER_SIZE 4096
static int do_wc(const int fd){
    if (fd<0) return -1;
    unsigned char buf[BUFFER_SIZE];
    int lcnt = 0;
    for(;;){
        int ret = read(fd, buf, sizeof buf); //read sizeof(buf) from file stream
        if(ret < 0) return -1;
        if(ret == 0) break; // reached to end of file
        for(int i=0;i<ret; i++){
            if(buf[i] == '\n') lcnt++;
        }
    }
    if(close(fd)<0) return -1;
    return lcnt;
}

static void die(const char *s){
    perror(s);
    exit(1);
}
