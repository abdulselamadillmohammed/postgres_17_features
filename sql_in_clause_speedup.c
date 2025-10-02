#include <stdio.h>

int main(){
    // Seems like previous queries required O(nlogn) time assuming you have indexes applied (n^2) if you don't
    // The genius of the optimzation is that you take advantage of B+ tree structure for sequential scanning!
    // SQL server has 2 scanning versions (im guessing you manually configure this, instead of auto applied)   
    // Commands:

    // pg17_features=# create table test (id serial not null);
    // pg17_features=# create index idx on test(id);
    // pg17_features=# insert into test select * from generate_series(1,1000000);
    
    return 0;
}