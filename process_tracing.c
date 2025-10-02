#include <stdio.h>
// strace is for linux systems
// Use: sudo dtruss ./a.out for mac os
int main(){
    int num = 0;
    printf("Here is my number: %d\n!", num);
    return 0;
}