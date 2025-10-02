// #define _XOPEN_SOURCE 700 // request X/Open and POSIX extensions. -- Linux version
#define _DARWIN_C_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/uio.h> // required for <sys/uio.h>


int main(){
    /*
    read(2) manpage:  https://man7.org/linux/man-pages/man2/read.2.html
    */

    //ssize_t read(int fd, void *buf, size_t count);
    // int fd → the file descriptor you get from open func
    // void *buf -> the pointer to the bugger where your bytes should be stored
    // size_t count -> the max num of bytes you want to place in buffer (type as char since it takes bytes)

    char buffer[128];
    char buffer2[128];
    
    // This only fails at run time!!
    int fd = open("sample.txt", O_RDONLY);
    if (fd < 0){
        perror("error on read open");
        exit(1);
    }
    //                             leave last byte fro /0
    ssize_t n = read(fd, buffer, sizeof(buffer) - 1 );
    if (n < 0){
        perror("read");
        close(fd);
        exit(1);
    }

    buffer[n] = '\0';
    printf("Read %zd bytes. What was read: \" %s \" \n", n, buffer);

    close(fd);


    // --- pread(2) ---
    // Only difference is that p read takes an index
    int fd2 = open("sample.txt", O_RDONLY);
    if (fd2 < 0){
        perror("error on pread open");
        exit(1);
    }
    //                                                           offset by num bytes 
    // If offset == 4, skip 4 chars  
    ssize_t buffer_2_size = pread(fd2, buffer2, sizeof(buffer2) - 1, 4);
    printf("Read %zd bytes. Offseted read: \" %s \" \n", buffer_2_size, buffer2);
    close(fd2);


    // preadv (takes an array of offets )
    // Apparently not, it does not take an array of offsets, it takes 
    // an array of buffers for sequential reads?


    /*
    The data transfers performed by readv() and writev() are atomic: 
    the data written by writev() is written as a single block that is not 
    intermingled with output from writes in other processes (but see 
    pipe(7) for an exception); analogously, readv() is guaranteed to read 
    a contiguous block of data from the file, regardless of read operations 
    performed in other threads or processes that have file descriptors 
    referring to the same open file description (see open(2)).

    -- How does the linux OS implement atomic transactions? If postgres wraps around it to 
       create locks...?
    
    */

    // From man page: ssize_t preadv(int fd, const struct iovec *iov, int iovcnt, off_t offset);
    int fd3 = open("sample.txt", O_RDONLY);
    if (fd3 < 0){
        perror("error on preadv open");
        exit(1);
    }
    
    // Buffers to read into
    /*
    
    struct iovec {
        void  *iov_base;   // start address of buffer
        size_t iov_len;    // number of bytes
    };

    */

    char buf1[6], buf2[6];
    buf1[5] = '\0';
    buf2[5] = '\0';
    struct iovec iov[2];
    iov[0].iov_base = buf1;
    iov[0].iov_len = sizeof(buf1) - 1;
    iov[1].iov_base = buf2;
    iov[1].iov_len = sizeof(buf2) - 1;

    ssize_t preadv_n = preadv(fd3, iov, 2, 0);
    if (preadv_n < 0){
        perror("Failed to perform multiple reads");
        exit(1);

    }
    printf("buf1: \"%s\"\n", buf1);
    printf("buf2: \"%s\"\n", buf2);
    
    // Optimization visble with syscall: strace, pg_stat_io
    // Slide show over pg17 changes:https://www.postgresql.eu/events/pgconfeu2024/sessions/session/5720/slides/608/Streaming%20I_O.pdf?utm_source=chatgpt.com
    
    /*
    Instruction on how to configure db to handle n number of kb:

    # postgresql.conf
    # allow up to 512kB combined reads (typ. max is 1MB on Unix, 128kB on Windows)
    io_max_combine_limit = '512kB'
    
    # Need to reload 
    SELECT pg_reload_conf();

    */
    
    
    return 0;
}