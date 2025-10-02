#include <stdio.h>

int main(){
    // Seems like previous queries required O(nlogn) time assuming you have indexes applied (n^2) if you don't
    // The genius of the optimzation is that you take advantage of B+ tree structure for sequential scanning!
    // SQL server has 2 scanning versions (im guessing you manually configure this, instead of auto applied)   
    // Commands:

    // pg17_features=# create table test (id serial not null);
    // pg17_features=# create index idx on test(id);
    // pg17_features=# insert into test select * from generate_series(1,1000000);
    
    // pg17_features=# vacuum full test;
    // pg17_features=# explain (analyze,buffers) select * from test where id in (1,2,3,5,6,7,8,9,10);
    // pg17_features=# select idx_scan from pg_stat_user_tables where relname = 'test';


    // OUTPUT: 
    /*

                                                   QUERY PLAN                                                   
----------------------------------------------------------------------------------------------------------------
 Index Only Scan using idx on test  (cost=0.42..43.98 rows=9 width=4) (actual time=5.009..5.016 rows=9 loops=1)
   Index Cond: (id = ANY ('{1,2,3,5,6,7,8,9,10}'::integer[]))
   Heap Fetches: 9
   Buffers: shared read=4
 Planning:
   Buffers: shared hit=46 read=1
 Planning Time: 2.700 ms
 Execution Time: 5.093 ms
(8 rows)

~
pg17_features=# explain (analyze,buffers) select * from test where id in (1,2,3,5,6,7,8,9,10);
                                                   QUERY PLAN                                                   
----------------------------------------------------------------------------------------------------------------
 Index Only Scan using idx on test  (cost=0.42..43.98 rows=9 width=4) (actual time=0.038..0.043 rows=9 loops=1)
   Index Cond: (id = ANY ('{1,2,3,5,6,7,8,9,10}'::integer[]))
   Heap Fetches: 9
   Buffers: shared hit=4
 Planning Time: 0.144 ms
 Execution Time: 0.064 ms
(6 rows)

pg17_features=# 

        
pg17_features=# select idx_scan from pg_stat_user_tables where relname = 'test';
 idx_scan 
----------
        2
(1 row)

    */

    return 0;
}