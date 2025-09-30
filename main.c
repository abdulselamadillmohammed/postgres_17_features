#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>


int main(){
    /*
    read(2) manpage:  https://man7.org/linux/man-pages/man2/read.2.html
    */

    //ssize_t read()

    int fd = open("samsple.txt", O_RDONLY);
    if (fd < 0){
        perror("open");
        exit(1);
    }
    
    char buffer[128];
    ssize_t n = read(fd, buffer, sizeof(buffer-1));
    if (n < 0){
        perror("read");
        close(fd);
        exit(1);
    }

    buffer[n] = "\0";
    printf("Read %zd bytes");

    close(fd);
    return 0;
}