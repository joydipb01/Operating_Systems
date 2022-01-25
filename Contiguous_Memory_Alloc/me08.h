#ifndef me08_h
#define me08_h

#define M 100

typedef struct{
    int start_addr;
    int size;
} hole;

typedef struct{
	int hole_count;
	int proc_count;
	hole *holes[M];
	int mem_req[M];
} process;

typedef struct{
	int alloc_addr[M];
	hole *alloc[M];
} allocs;

#endif