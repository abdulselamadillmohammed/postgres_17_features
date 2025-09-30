#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>


int main(){
    /*
    read(2) manpage:  https://man7.org/linux/man-pages/man2/read.2.html
    */

    //ssize_t read(int fd, void *buf, size_t count);
    // int fd → the file descriptor you get from open func
    // void *buf -> the pointer to the bugger where your bytes should be stored
    // size_t count -> the max num of bytes you want to place in buffer (type as char since it takes bytes)

    // This only fails at run time!!
    int fd = open("sample.txt", O_RDONLY);
    if (fd < 0){
        perror("open");
        exit(1);
    }
    
    char buffer[128];
    //                             leave last byte fro /0
    ssize_t n = read(fd, buffer, sizeof(buffer) -1 );
    if (n < 0){
        perror("read");
        close(fd);
        exit(1);
    }

    buffer[n] = '\0';
    printf("Read %zd bytes. What was read: \" %s \" \n", n, buffer);

    close(fd);
    return 0;
}