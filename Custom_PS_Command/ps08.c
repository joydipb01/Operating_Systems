#include <stdio.h>
#include <stdlib.h>
#include "ps08.h"

int main(){
    printf("%-8s%-8s%-15s%-14s%s\n", "PID", "PPID", "STATE", "Files Open", "CMD");
    dirs *d = getpidinfo();
    for (int i = 0; i < d->count; i++){
        info *in = getInfo(d->larr[i]);
        printInfo(in);
    }
    free(d);
}