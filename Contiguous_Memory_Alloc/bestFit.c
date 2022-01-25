#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "me08.h"

FILE *inp;

void best_fit(process* x){
	int ext_frag=0;
	allocs *bf=(allocs *)malloc(sizeof(allocs));
	for (int i = 0; i < x->hole_count; i++){
		bf->alloc[i] = (hole *)malloc(sizeof(hole));
		bf->alloc[i]->start_addr = x->holes[i]->start_addr;
		bf->alloc[i]->size = x->holes[i]->size;
	}
	int best;
	for (int i = 0; i < x->proc_count; i++){
		best=-1;
		for (int j = 0; j < x->hole_count; j++){
			if (x->mem_req[i] <= bf->alloc[j]->size) {
				best = j;
				break;
			}
		}
		if (best == -1) {
			bf->alloc_addr[i] = -1;
			continue;
		}        
		for (int j = 0; j < x->hole_count; j++) {
			if (bf->alloc[j]->size < bf->alloc[best]->size && bf->alloc[j]->size >= x->mem_req[i]) {
				best = j;
			}
		}
		bf->alloc_addr[i] = bf->alloc[best]->start_addr;
		bf->alloc[best]->start_addr += x->mem_req[i];
		bf->alloc[best]->size -= x->mem_req[i];
	}
    
	printf("Process\tSize\tAllocated Address\t\n");
	for (int i = 0; i < x->proc_count; i++){
		printf("%d\t%d\t%d\t\n", i+1, x->mem_req[i], bf->alloc_addr[i]);
	}
	for (int i = 0; i < x->hole_count; i++)
		ext_frag += bf->alloc[i]->size;
    
    printf("\nExternal Fragmentation: %d\n\n", ext_frag);
}

int main(int argc, char **argv)
{
    if (argc != 2){
        fprintf(stderr, "Invalid argument count!\n");
        exit(1);
    }

    char* fileName = argv[1];

    inp = fopen(fileName, "r");
    if (inp == NULL){
        fprintf(stderr, "Could not open file! (or) %s: No such file!\n", fileName);
        exit(2);
    }

    char line[64], *str, *size;
    process *proc = (process *)malloc(sizeof(process));
    int i;

    fgets(line, sizeof(line), inp);
    int mem = strtol(line, &str, 10);

    fgets(line, sizeof(line), inp);
    proc->hole_count = strtol(line, &str, 10);

    for (i = 0; i < proc->hole_count; i++){
        fgets(line, sizeof(line), inp);
        proc->holes[i] = (hole *)malloc(sizeof(hole));

        size = strchr(line, ',');
        size++;
        proc->holes[i]->start_addr = strtol(line, &str, 10);
        proc->holes[i]->size = strtol(size, &str, 10);
	if(proc->holes[i]->start_addr+proc->holes[i]->size > mem){
		fprintf(stderr, "Bad hole params: Size of hole exceeds total memory in systems\n");
		exit(3);
	}
    }

    for (i = 0; fgets(line, sizeof(line), inp); i++)
    {
        proc->mem_req[i] = strtol(line, &str, 10);
    }
    proc->proc_count = i;

    fclose(inp);

    best_fit(proc);
}