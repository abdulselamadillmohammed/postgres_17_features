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

    return 0;
}